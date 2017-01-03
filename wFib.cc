#include <iostream>
using namespace std;

// this works, why this and not the function templates?

template <unsigned long N>
struct Fib 
{
enum : unsigned long{ value = Fib<N - 1>::value + Fib<N-2>::value };
};

template <>
struct Fib<0> 
{
enum : unsigned long{ value = 0 };
};

template <>
struct Fib<1> 
{
enum : unsigned long{ value = 1 };
};

// Factorial<4>::value == 24
// Factorial<0>::value == 1
int main()
{
        unsigned long x = Fib<45>::value; // == 24
            unsigned long y = Fib<0>::value; // == 1
            cout << x << " " << y << "\n";
}

