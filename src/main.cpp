#include <iostream>
#include <boost/program_options.hpp>

#include "keys.hpp"

//-------------TODO чет надо сделать вроде
#ifndef PROJECT_PATH
#define PROJECT_PATH ""
#endif

//PROJECT_PATH given in cmake

#define IS_GOOD_INPUT \
    if(!std::cin.good()){ \
        std::cout << "Input error" << std::endl; \
        return 0; \
    } \

class Input_params{
private:
    std::string FILE_PRIME;
public:
    //constructor
    Input_params(int argc, char *argv[]){
        namespace prog_opts = boost::program_options;

        prog_opts::options_description desc("Allowed options");

        std::string default_file_prime = "prime_numbers/prime_numbers_up_to_10_6.txt";
        desc.add_options()
            ("file_prime", prog_opts::value<std::string>()->default_value(PROJECT_PATH + default_file_prime), "file with prime numbers by which would be generated keys")
            ("help", "help message")
        ;
    
        prog_opts::variables_map vm;
        prog_opts::store(prog_opts::parse_command_line(argc, argv, desc), vm);
        prog_opts::notify(vm);
    
        if(vm.count("help")){
            std::cout << desc << "\n";
            exit(1);
        }
        if(vm.count("file_prime")){
            FILE_PRIME = vm["file_prime"].as<std::string>();
        }
    }

    //getter
    std::string get_FILE_PRIME() const{
        return this->FILE_PRIME;
    }
};



int main(int argc, char *argv[]){

    Input_params input = Input_params(argc, argv);

    unsigned int message;
    unsigned int cipher, ans;

    char phrase[100];
    std::cout << "Phrase by which, would be generated keys" << std::endl;
    std::cin >> phrase;

    //TODO кодировать строчку вместо int, преобразовывая в unsigned int и кодируя по блокам 4 байта
    std::cout << "Number, which should be encoded" << std::endl;
    std::cin >> message;

    
    //simple_hash_function can be changed on other hash function
    Keys k = Keys(phrase, input.get_FILE_PRIME());
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