#include "s.h"

// constexpr function, template function

template<typename T>
void echo (T value) { cout << value << "\n"; }

constexpr auto tri(int n) {
    int sum=0;
    for (int i=1; i<n; i++)
        sum+=i;
    return sum;
}

auto v = tri(10);

int main() {

    echo<int>(v);
    echo<string>("fourty two");

}
