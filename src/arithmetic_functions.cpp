#include "arithmetic_functions.hpp"

bool is_prime(unsigned long long n){
    for(int i = 2; i <= std::sqrt(n); i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

unsigned int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    unsigned int gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

unsigned int mod_inverse(unsigned int a, unsigned int m) {
    int x, y;
    unsigned int gcd = extended_gcd(a, m, x, y);
    
    //GCD is not 1, no reciprocal number
    if (gcd != 1) {
        std::cerr << "No reciprocal number" << std::endl;
        return 0;
    }

    if(x < 0){
        return m + x;
    }
    return x;

/*
    // Сделаем x положительным
    unsigned int result = (x % m + m) % m;
    std::cout << result << std::endl;
    return result;
*/
}




unsigned long long find_nearest_lower_prime(const std::string& filename, unsigned long long target) {
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "File opening error" << std::endl;
        return 0;
    }

    unsigned long long buff, lower = 0;
    bool find = false;

    while (file >> buff) {
        if(buff <= target){
            find = true;
            lower = buff;
        } 
        else{
            break;
        }
    }
    //if hash make target equal 0 or 1, there must be default value
    if(!find){
        lower = 2;
    }
    file.close();
    return lower;
}

//a ^ b mod c
unsigned int fast_pow_mod(unsigned int num, unsigned int pow, unsigned int mod){
    unsigned int result = 1;
    while(pow > 0){
        if(pow % 2 == 0){
            pow /= 2;
            num = (((unsigned long long)(num)) * num) % mod;    
        }
        else{
            pow--;
            result = (result * ((unsigned long long)(num))) % mod;
            pow /= 2;
            num = (((unsigned long long)(num)) * num) % mod;    
        }
    }
    return result;

}