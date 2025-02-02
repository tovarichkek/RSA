#include <iostream>

#include "keys.hpp"


int main(){

    unsigned int message;
    unsigned int cipher, ans;

    char phrase[100];
    std::cout << "Phrase by which, would be generated keys" << std::endl;
    std::cin >> phrase;

    //TODO кодировать строчку вместо int, преобразовывая в unsigned int и кодируя по блокам 4 байта
    std::cout << "Number, which should be encoded" << std::endl;
    std::cin >> message;

    
    //simple_hash_function can be changed on other hash function
    Keys k = Keys(phrase);
    //Keys k = Keys(11,23);

    /*
    std::cout << "mess: " << message << "  publ: " << k.get_public_key().get_key().first << ' ' << k.get_public_key().get_key().second << std::endl;
    std::cout << "priv: " << k.get_private_key().get_key().first << ' ' << k.get_private_key().get_key().second << std::endl;
    k.encrypt_block(&message, &cipher);
    std::cout << "Encoded data: " << cipher << std::endl;

    k.decrypt_block(&cipher, &ans);
    std::cout << "Decoded data :" << ans << std::endl;
    */


    for(unsigned int i = 5; i < 10000; i++){
        k.encrypt_block(i, cipher);
        k.decrypt_block(cipher, ans);
        if(i != ans){
            std::cout << "NOOOOOOO" << ' ';
            std::cout << i << std::endl;
        }

   }

}