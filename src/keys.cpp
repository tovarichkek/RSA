#include "keys.hpp"



//--------------TODO может быть в одной строчке через списки инициализации, тогда не нужен пустой конструктор в key, но эт неудобно нифига
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
    e = find_nearest_lower_prime(file_primes, fi);
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

    //---------------TODO дважды лезем в файл взять по одному числу, в идеале на ходу не закрывая
    //p and q will be nearest lower prime by first and second
    part_KeY_T p = find_nearest_lower_prime(file_primes, first);
    part_KeY_T q = find_nearest_lower_prime(file_primes, second);
    *this = Keys(p, q, file_primes);
}

void Keys::encrypt_block(const unsigned int& data, unsigned int& dest){
    dest = fast_pow_mod(data, this->public_key.get_key().first, this->public_key.get_key().second);
}

void Keys::decrypt_block(const unsigned int& data, unsigned int& dest){
    dest = fast_pow_mod(data, this->private_key.get_key().first, this->private_key.get_key().second);
}