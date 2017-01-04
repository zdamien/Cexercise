#include <iostream>

// -O0: no compile time execution
// -O1 made it take 7G of RAM; I infer compile time execution without
// memoization
// -O2 works fine, though, fast compile and execution

template<int N>
int fib() {
    return fib<N-1>() + fib<N-2>();
}

template<>
int fib<0>() {
    return 0;
}
template<>
int fib<1>() {
    return 1;
}

int main() {
    int val = fib<45>();

    std::cout << val << "\n";

}
