// C++ hashtable exercise.  Goal: to go through getting the basics
// working, not to create something library-ready.
//
// started 12:29, spent fair bit of time on hash function
// inset, get, in done, 1:10.  insert doesn't check for existing values
// though.
// fixed, 13:35.  Ran into heisen bug from unitialized local variables,
// oops. 
// refactoring (get_bucket) 13:45

#include <string>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

using Key = string;
using Value = string;
using Entry = pair<Key, Value>;
using Bucket = vector<Entry>;

unsigned mhash(const Key& k) {
    //cout << "mhash " << k << "\n";
    unsigned int h=0;
    unsigned int high=0;
    for (unsigned char c : k)  {
        high = h & 0xfff80000;
        h = h << 13;
        h ^= (high >> 19);
        h ^= c;
        h ^= c << 24;
    }
    return h;
}

class Htbl {
    vector<Bucket> buckets;
    int num_elem;
    unsigned get_buck_ind(const Key& k) const {
        return mhash(k) % buckets.capacity();
    }
    unsigned get_buck_ind(const Entry& e) const {
        return get_buck_ind(e.first);
    }
    Bucket& get_bucket(const Key& k) {
        return buckets[mhash(k) % buckets.capacity()];
    }
    Bucket& get_bucket(const Entry& e) {
        return get_bucket(e.first);
    }
    const Bucket& get_bucket(const Key& k) const {
        return buckets[mhash(k) % buckets.capacity()];
    }
    const Bucket& get_bucket(const Entry& e) const {
        return get_bucket(e.first);
    }
public:
    Htbl(int cap=10) : buckets(cap), num_elem{0} {}
    void insert(const Entry& e);
    void del(const Key& k);
    Value get (const Key& k) const;
    auto get_it (const Key& k);
    auto get_it (const Key& k) const;
    bool in (const Key& k) const;
    void clear() { buckets.clear(); num_elem=0; }
    int size() const noexcept { return num_elem; }

};

void Htbl::insert (const Entry& e) {
    Bucket& buck = get_bucket(e);
    if (not in(e.first)) {
        buck.push_back(e);
        ++num_elem;
    }
    else {
        del(e.first);
        insert(e);
    }
}

class not_found {};

auto Htbl::get_it (const Key& k) {
    Bucket& buck = get_bucket(k);
    for (auto it = buck.begin(); it != buck.end(); it++) {
        if (k == it->first)
            return it;
    }
    throw not_found();
}

auto Htbl::get_it (const Key& k) const {
    const Bucket& buck = get_bucket(k);
    for (auto it = buck.cbegin(); it != buck.cend(); it++) {
        if (k == it->first)
            return it;
    }
    throw not_found();
}

Value Htbl::get (const Key& k) const {
    auto it = get_it(k);
    return it->second;
}


void Htbl::del (const Key& k) {
    Bucket& buck = get_bucket(k);
    auto it = get_it(k);
    buck.erase(it);
    --num_elem;
}

bool Htbl::in (const Key& k) const {
    try {
        auto v = get(k);
        return true;
    }
    catch (not_found e) {
        return false;
    }
}

int main() {
    Htbl ht(2);
    ht.insert(make_pair("one","One"));
    ht.insert(make_pair("two","zwei"));
    ht.insert(make_pair("three","drei"));
    ht.insert(make_pair("ono","yoko"));
    ht.insert(make_pair("one","Onee"));
    cout << ht.in("zne") << ht.get("one") << "\n";
    cout << ht.get("two") << "\n";
    cout << ht.get("three") << "\n";
    cout << ht.get("ono") << "\n";
    cout << ht.size() << "\n";

    /*
    cout << mhash("hell") << "\n";
    cout << mhash("hello") << "\n";
    cout << mhash("hellp") << "\n";
    cout << mhash("Hello") << "\n";
    cout << mhash("Hellp") << "\n";
    cout << mhash("hellO") << "\n";
    cout << mhash("iello") << "\n";
    */

}
