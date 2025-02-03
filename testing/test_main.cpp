#include <gtest/gtest.h>
#include <boost/program_options.hpp>

#include "test_functions.hpp"
#include "keys.hpp"

#ifndef PROJECT_PATH
#define PROJECT_PATH ""
#endif

class Input_params{
private:
    std::string FILE_PRIME;
    std::string ALPHABET;
    unsigned int PASSPHRASE_LENGTH;

public:
    //constructor
    Input_params(int argc, char *argv[]){
        namespace prog_opts = boost::program_options;

        prog_opts::options_description desc("Allowed options");

        std::string default_file_prime = "/prime_numbers/prime_numbers_up_to_10_6.txt";
        desc.add_options()
            ("file_prime", prog_opts::value<std::string>()->default_value(PROJECT_PATH + default_file_prime), "file with prime numbers by which would be generated keys")
            ("alphabet", prog_opts::value<std::string>()->default_value("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"), "alphabet for generated passphrases")
            ("passphrase_length", prog_opts::value<unsigned int>()->default_value(5), "max len of passphrase")

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
        if(vm.count("alphabet")){
            ALPHABET = vm["alphabet"].as<std::string>();
        }
        if(vm.count("passphrase_length")){
            PASSPHRASE_LENGTH = vm["passphrase_length"].as<unsigned int>();
        }

    }

    //getter
    std::string get_FILE_PRIME() const{
        return this->FILE_PRIME;
    }
    std::string get_ALPHABET() const{
        return this->ALPHABET;
    }
    unsigned int get_PASSPHRASE_LENGTH() const{
        return this->PASSPHRASE_LENGTH;
    }
};



//----------------TODO  в TEST не прокинуть параметры cmd просто так
struct TestParams {
    int argc;
    char** argv;
};
class MyTest : public ::testing::TestWithParam<TestParams> {};


//encode and then decode numbers with all possible strings, check decode number equal to original
TEST_P(MyTest, ERAT) {
    TestParams params = GetParam();
    Input_params input = Input_params(params.argc, params.argv);

    std::vector<std::string> all_strings = {};

    generate_strings(input.get_PASSPHRASE_LENGTH(), input.get_ALPHABET(), all_strings);

    for(auto& passphrase : all_strings){
        bool scfl = true;
    
        Keys k = Keys(passphrase, input.get_FILE_PRIME());
        unsigned int cipher = 0, ans = 0;

        for(unsigned int i = 0; i < 10000; i++){
            k.encrypt_block(i, cipher);
            k.decrypt_block(cipher, ans);
            EXPECT_EQ(i, ans);
        }
        ASSERT_TRUE(scfl);
    }
}






int main(int argc, char *argv[]) {
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
