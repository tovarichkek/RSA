#include "keys.hpp"

Keys::Keys(part_KeY_T p, part_KeY_T q, std::string file_primes){
    KeY_T N, fi, e, d;
    //keys are: public{e, N} and private{d, N}
    //where 
    //N = p * q
    //fi = (p - 1) * (q - 1) is result`s function Euler to N 
    //e - nearest lower prime to fi
    //d - mod inverse to e by mod fi
    
    N = p * q;
    fi = (p - 1) * (q - 1);

    //prime_numbers are limited, its hard to achieve value, what hash gives
    //so we should take fi modulo MAX_PRIME in finding e
    const unsigned int MAX_PRIME = find_nearest_lower_prime(file_primes, UINT_MAX);
    e = find_nearest_lower_prime(file_primes, fi % MAX_PRIME);
    //this function implies a different base as a list of prime numbers so that finding the MAX_PRIME must be done anew each time
    //it cant be given as a macros or global constant


    d = mod_inverse(e, fi);

    //keys made with copy ctor
    public_key = Key(e, N);
    private_key = Key(d, N);
}

Keys::Keys(std::string passphrase, std::string file_primes, unsigned int(* hash_function)(std::string)){
    unsigned short int first, second;
    unsigned int hash = djb2_hash(passphrase);

    //two bytes from hash - first, two bytes - second
    first = (hash & 0xFFFF);
    second = ((hash >> 16) & 0xFFFF);

    //----------TODO Плохо, что и для p, и для q нужно открывать + закрывать файл
    //p and q will be nearest lower prime by first and second
    part_KeY_T p = find_nearest_lower_prime(file_primes, first);
    part_KeY_T q = find_nearest_lower_prime(file_primes, second);
    
    //to prevent case p = q
    while(p == q){
        first += 1;    
        p = find_nearest_lower_prime(file_primes, first);
    }
    *this = Keys(p, q, file_primes);
}

void Keys::encrypt_block(const unsigned int& data, unsigned int& dest){
    dest = fast_pow_mod(data, this->public_key.get_key().first, this->public_key.get_key().second);
}

void Keys::decrypt_block(const unsigned int& data, unsigned int& dest){
    dest = fast_pow_mod(data, this->private_key.get_key().first, this->private_key.get_key().second);
}