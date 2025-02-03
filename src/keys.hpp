#pragma once

#include <cstdlib>
#include <utility>
#include <string>
#include <limits.h>

#include "arithmetic_functions.hpp"
#include "hash.hpp"

typedef unsigned int KeY_T;  //is part_KeY_T * part_KeY_T
typedef unsigned short part_KeY_T;

class Key{
    private:
        std::pair<KeY_T, KeY_T> key;
    public: 
        Key(){}  //keys has to be initialised in Keys ctor
        Key(KeY_T first, KeY_T second): key(std::make_pair(first, second)){}
        std::pair<KeY_T, KeY_T> get_key(){
            return key;
        }
};

class Keys{
    private:
        Key private_key;
        Key public_key;
    public:
        Key get_public_key(){
            return public_key;
        }
        Key get_private_key(){
            return private_key;
        }

        //generating keys from two prime numbers - unsigned short
        Keys(part_KeY_T p, part_KeY_T q, std::string file_primes);

        //generating keys by passphrase and txt-file with prime numbers
        Keys(std::string passphrase, std::string file_primes, unsigned int(* hash_function)(std::string) = djb2_hash);

        void encrypt_block(const unsigned int& data, unsigned int& dest);
        void decrypt_block(const unsigned int& data, unsigned int& dest);

};