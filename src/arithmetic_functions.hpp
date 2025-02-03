#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

bool is_prime(unsigned long long n);
unsigned int extended_gcd(unsigned int a, unsigned int b, int &x, int &y);

unsigned int mod_inverse(unsigned int a, unsigned int m);

unsigned long long find_nearest_lower_prime(const std::string& filename, unsigned long long target);

//a ^ b mod c
unsigned int fast_pow_mod(unsigned int num, unsigned int pow, unsigned int mod);