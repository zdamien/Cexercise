#include <iostream>
using namespace std;

template <unsigned long N>
struct Factorial 
{
        enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0> 
{
        enum { value = 1 };
};

// Factorial<4>::value == 24
// Factorial<0>::value == 1
int main()
{
        unsigned long x = Factorial<40>::value; // == 24
            unsigned long y = Factorial<0>::value; // == 1
            cout << x << " " << y << "\n";
}

