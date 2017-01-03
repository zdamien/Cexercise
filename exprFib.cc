#include <iostream>

// doesn't seem to be working at compile time

constexpr int fib(const int n) {
    int val=0;
    if (n==0) val=0;
    else if (n==1) val=1;
    else
    val= fib(n-1) + fib(n-2);
    return val;
}

int main() {
    std::cout << fib(55) << "\n";

}
