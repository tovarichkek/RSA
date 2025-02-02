#include "hash.hpp"

unsigned int djb2_hash(std::string str){
    unsigned int hash = 5381;
    int c;
    int i = 0;

    while (c = str[i]){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        i++;
    }

    return hash;
}

unsigned int sdbm_hash(std::string str){
    
    unsigned int hash = 0;
    int c;
    int i = 0;
    
    while (c = str[i]){
        hash = c + (hash << 6) + (hash << 16) - hash;
        i++;
    }

    return hash;
}


