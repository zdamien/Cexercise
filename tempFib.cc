#include <iostream>

// doesn't seem to be working at compile time

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
    std::cout << fib<45>() << "\n";

}
