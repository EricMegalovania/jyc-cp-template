#include <iostream>

int main() {
    long long n = 0;
    if (!(std::cin >> n)) return 0;
    long long ans = n * (n + 1) / 2;
    if (n >= 2) ans += 1;
    std::cout << ans << '\n';
    return 0;
}
