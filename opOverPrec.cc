// a friend said C++ operator overloading broke precedence.  This code
// indicates he was not correct.
// OTOH overloading is said to break short-circuiting for && and ||

#include <cstdio>

struct dummy {
    int val;
    dummy operator-() const { printf("op-: %d\n", val); return dummy(-val); }
    dummy(int v): val{v} {}
};

dummy operator* (const dummy& left, const dummy& right) {
    printf("op*: %d %d\n",left.val, right.val);
    return dummy(left.val * right.val);
}
dummy operator+ (const dummy& left, const dummy& right) {
    printf("op+: %d %d\n",left.val, right.val);
    return dummy(left.val + right.val);
}

int main() {
    dummy d{4};
    d=-d;
    d=-d;
    dummy a{2},b{3};
    printf("%d\n", a+b*d);
    printf("%d\n", a*b+d);
}
