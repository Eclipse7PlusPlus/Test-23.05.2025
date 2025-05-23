#include "functions.h"
#include <iostream>
#include <string>
#include <climits>
#include <stdexcept>

void PrintStrings(const std::string* strings, int32_t size) {
    for (int32_t i = 0; i < size; ++i) {
        std::cout << strings[i] << std::endl;
    }
}

void DeleteStrings(std::string* strings) {
    delete[] strings;
}

std::string* FillStringArray(int32_t& size) {
    std::cout << "Введите количество строк: ";
    std::cin >> size;
    
    while (std::cin.fail() || size <= 0) {
        std::cin.clear();
        std::cin.ignore(); 
        std::cout << "Ошибка! Введите положительное число: ";
        std::cin >> size;
    }
    std::cin.ignore();

    std::string* arr = nullptr;
    try {
        arr = new std::string[size];
    } catch (const std::bad_alloc& e) {
        std::cerr << "Ошибка выделения памяти для массива строк: " << e.what() << std::endl;
        throw;
    }

    for (int32_t i = 0; i < size; ++i) {
        try {
            std::cout << "Введите строку " << (i + 1) << " (формат: <слово> <число>): ";
            std::getline(std::cin, arr[i]);
            if (std::cin.fail()) {
                throw std::runtime_error("Ошибка!");
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при вводе строки " << (i + 1) << ": " << e.what() << std::endl;
            DeleteStrings(arr);
            throw;
        }
    }

    return arr;
}

void ProcessAndSortStrings(std::string* strings, int32_t size) {
    if (strings == nullptr || size <= 0) {
        throw std::invalid_argument("Некорректные входные данные");
    }

    int32_t* numbers = nullptr;
    std::string* original_strings = nullptr;
    
    try {
        numbers = new int32_t[size]();
        original_strings = new std::string[size];
    } catch (const std::bad_alloc& e) {
        delete[] numbers;
        throw std::runtime_error("Ошибка выделения памяти для обработки строк");
    }

    int32_t sum = 0;
    int32_t min_num = 0;
    int32_t max_num = 0;
    bool first_number = true;

    for (int i = 0; i < size; ++i) {
        try {
            size_t space_pos = strings[i].find(' ');
            std::string num_str = "0";

            if (space_pos != std::string::npos) {
                num_str = strings[i].substr(space_pos + 1);
            }

            int32_t number = 0;
            bool is_number = true;
            
            if (!num_str.empty()) {
                size_t start_pos = (num_str[0] == '-') ? 1 : 0;
                is_number = !num_str.empty();
                
                for (size_t j = start_pos; j < num_str.size(); ++j) {
                    if (!isdigit(num_str[j])) {
                        is_number = false;
                        break;
                    }
                }

                if (is_number) {
                    try {
                        number = std::stoi(num_str);
                    } catch (const std::invalid_argument&) {
                        is_number = false;
                    } catch (const std::out_of_range&) {
                        number = (num_str[0] == '-') ? INT32_MIN : INT32_MAX;
                    }
                }
            }

            numbers[i] = number;
            original_strings[i] = strings[i];
            sum += number;

            if (first_number) {
                min_num = number;
                max_num = number;
                first_number = false;
            } else {
                if (number < min_num) min_num = number;
                if (number > max_num) max_num = number;
            }
        } catch (const std::exception& e) {
            delete[] numbers;
            delete[] original_strings;
            throw std::runtime_error ("Ошибка обработки строки ");
        }
    }

    try {
        for (int32_t i = 0; i < size - 1; ++i) {
            for (int32_t j = 0; j < size - i - 1; ++j) {
                if (numbers[j] > numbers[j + 1]) {
                    std::swap(numbers[j], numbers[j + 1]);
                    std::swap(original_strings[j], original_strings[j + 1]);
                }
            }
        }

        std::cout << "\nОтсортированные строки:" << std::endl;
        PrintStrings(original_strings, size);

        std::cout << "\nSum: " << sum << std::endl;
        std::cout << "Min: " << min_num << std::endl;
        std::cout << "Max: " << max_num << std::endl;
    } catch (const std::exception& e) {
        delete[] numbers;
        delete[] original_strings;
        throw;
    }

    delete[] numbers;
    delete[] original_strings;
}
