#include "test_functions.hpp"

void generate_strings(int maxLength, const std::string& alphabet, std::vector<std::string>& result, std::string current) {
    //Add the current row to the result if it is not empty
    if(!current.empty()){
        result.push_back(current);
    }
    
    //If the length of the current line is less than the maximum, we continue generating
    if(current.length() < maxLength){
        for (char c: alphabet) {
            generate_strings(maxLength, alphabet, result, current + c);
        }
    }
}
