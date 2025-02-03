#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "keys.hpp"

#ifndef PROJECT_PATH
#define PROJECT_PATH ".."
#endif

//if alphabet or passphrase_length is big, it works toooooooo long
#ifndef PASSPHRASE_LENGTH
#define PASSPHRASE_LENGTH 7
#endif

#ifndef ALPHABET
#define ALPHABET "abcde"
#endif

#ifndef FILE_PRIME
#define FILE_PRIME (PROJECT_PATH + std::string("/prime_numbers/prime_numbers_up_to_10_6.txt"))
#endif


//encode and then decode numbers with all possible strings, check decode number equal to original
TEST(MyTest, ERAT) {

    std::vector<std::string> all_strings = {};

    generate_strings(PASSPHRASE_LENGTH, ALPHABET, all_strings);
    
    for(auto& passphrase : all_strings){
        bool scfl = true;

        Keys k = Keys(passphrase, FILE_PRIME);
        unsigned int cipher = 0, ans = 0;

        for(unsigned int i = 3; i < 30; i++){
            k.encrypt_block(i, cipher);
            k.decrypt_block(cipher, ans);
            if(i != ans){
                scfl = false;
            }
            EXPECT_EQ(i, ans);
        }
        if(scfl){
            std::cout << "Succesfull: " << passphrase << std::endl;
        }
        else{
            std::cout << "FAIL: " << passphrase << std::endl;
        }
        ASSERT_TRUE(scfl);
    }
}


int main(int argc, char *argv[]) {
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
