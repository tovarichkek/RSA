#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "keys.hpp"

//-------------TODO чет надо задать по умолчанию вроде, хотя project_path передается в cmake
#ifndef PROJECT_PATH
#define PROJECT_PATH "../"
#endif

//if alphabet or passphrase_length is big, it works toooooooo long
#ifndef PASSPHRASE_LENGTH
#define PASSPHRASE_LENGTH 5
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
        std::cout << passphrase << std::endl;
        bool scfl = false;

        Keys k = Keys(passphrase, FILE_PRIME);
        unsigned int cipher = 0, ans = 0;

        for(unsigned int i = 4; i < 10000; i++){
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
