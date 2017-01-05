// interview question: what's the difference between pass by reference,
// and passing a reference?  I blanked.  Time to experiment!

// Answer: it's what I thought.  Not much difference.

#include "s.h"

void foo (int &v) {
    v=4;
}

int main() {
    int x =3;
    int z=2;
    int &y=z;
    cout << x << y << z << "\n";
    foo(x); // pass by reference
    foo(y); // pass a reference
    cout << x << y << z << "\n";
}
