#include <fstream>
#include <iostream>

int main() {
    int i = 0;
    {
        std::ifstream f("gen_count.txt");
        if (f) f >> i;
    }
    ++i;
    {
        std::ofstream f("gen_count.txt");
        f << i;
    }
    std::cout << i << '\n';
    return 0;
}
