#include <iostream>

int main() {
    long long n = 0;
    if (!(std::cin >> n)) return 0;
    if (n >= 4) {
        volatile int *p = nullptr;
        *p = 1;
    }
    std::cout << n * (n + 1) / 2 << '\n';
    return 0;
}
