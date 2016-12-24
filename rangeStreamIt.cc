// creates an infinite stream of numbers according to a step value. Or
// rather, creates iterators such that "it == end()" is never true.

#include "s.h"

class Range {
public:
    const long FROM, STEP;
    Range(long f=0, long s=1) : FROM(f), STEP(s) {}
    // member typedefs provided through inheriting from std::iterator
    class iterator: public std::iterator<
                        std::input_iterator_tag,   // iterator_category
                        long,                      // value_type
                        long,                      // difference_type
                        const long*,               // pointer
                        long                       // reference
                                      >{
        long num = 0;
        const long STEP=1;
        bool end = false;
    public:
        explicit iterator(long _num = 0, long _step=1, bool _end =
                false) : num(_num), STEP(_step), end(_end) {}
        iterator& operator++() {num += STEP; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(const iterator& other) const {return !end && !(other.end) && num == other.num;}
        bool operator!=(const iterator& other) const {return !(*this == other);}
        reference operator*() const {return num;}
    };
    iterator begin() {return iterator(FROM, STEP);}
    iterator end() {return iterator(0,0,true); }
};
 
int main() {
    int step;
    cout << "Enter step size\n";
    cin >> step;
 
    // Range::iterator satisfies range-based for requirements
    for(long l : Range(3, step)) {
        std::cout << l << ' '; 
    }
    std::cout << '\n';
}
