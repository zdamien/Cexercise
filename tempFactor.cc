#include <iostream>

template<int N>
int factor() {
    return N*factor<N-1>();
}

template<>
int factor<0>() {
    return 1;
}

int main() {
    std::cout << factor<5>() << "\n";

}
