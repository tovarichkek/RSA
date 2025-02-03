#include <iostream>
#include <boost/program_options.hpp>

#include "keys.hpp"

//-------------TODO чет надо задать по умолчанию вроде
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

        std::string default_file_prime = "/prime_numbers/prime_numbers_up_to_10_6.txt";
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

    std::string phrase;
    std::cout << "Phrase by which, would be generated keys" << std::endl;
    std::cin >> phrase;
    IS_GOOD_INPUT;

    //TODO кодировать строчку вместо int, преобразовывая в unsigned int и кодируя по блокам 4 байта
    std::cout << "Number, which should be encoded" << std::endl;
    std::cin >> message;
    IS_GOOD_INPUT;
    
    //simple_hash_function can be changed on other hash function
    Keys k = Keys(phrase, input.get_FILE_PRIME());
    
    k.encrypt_block(message, cipher);
    k.decrypt_block(cipher, ans);

    std::cout << "Encoded data: " << cipher << std::endl;
    std::cout << "Decoded data: " << ans << std::endl;


}