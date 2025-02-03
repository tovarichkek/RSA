#include "test_functions.hpp"

void generate_strings(int maxLength, const std::string& alphabet, std::vector<std::string>& result, std::string current) {
    // Добавляем текущую строку в результат, если она не пустая
    if (!current.empty()) {
        result.push_back(current);
    }
    
    // Если длина текущей строки меньше максимальной, продолжаем генерировать
    if (current.length() < maxLength) {
        for (char c : alphabet) {
            generate_strings(maxLength, alphabet, result, current + c);
        }
    }
}
