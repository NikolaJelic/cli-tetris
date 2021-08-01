#include <iostream>

namespace util {
inline void clear_screen() { std::cout << "\033[H\033[2J\033[3J"; }
} // namespace util
