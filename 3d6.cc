#include "s.h"
#include <random>

int main() {
    auto eng = default_random_engine{ static_cast<unsigned>(time(nullptr))};
    auto die = bind(uniform_int_distribution<>{1,6}, eng);
            
    //vector<int> hist{20}; doesn't work... oh, setting to the single
    //element 20
    vector<int> hist(20);
    for (int i=0; i<100000; i++) {
        auto sum = die()+die()+die();
        hist[sum]++;
    }
    for (int i=2; i<=19; i++) {
        cout << i << ":" << hist[i] << "\n";
    }

}
