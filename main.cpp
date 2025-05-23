#include "functions.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        int32_t size{};
        std::string* strings = FillStringArray(size);
        ProcessAndSortStrings(strings, size);
        DeleteStrings(strings);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Ошибка выделения памяти: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Произошла неизвестная ошибка" << std::endl;
    }
    return 0;
}
