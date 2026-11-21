#include <iostream>

int main() {
    long long n = 0;
    if (!(std::cin >> n)) return 0;
    std::cout << n * (n + 1) / 2 << '\n';
    return 0;
}
