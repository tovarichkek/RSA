cmake_minimum_required(VERSION 3.10)

project(RSA_keys)
add_definitions(-DPATH)

find_package(GTest)
find_package(Boost COMPONENTS program_options)

if(NOT Boost_FOUND)
    message(WARNING "Did not find boost LIBS")
else()
    ###RSA
    add_executable(RSA src/main.cpp src/keys.cpp src/hash.cpp src/arithmetic_functions.cpp)
    target_link_libraries(RSA Boost::program_options)
    target_compile_definitions(RSA PRIVATE PROJECT_PATH="${CMAKE_SOURCE_DIR}")
    
    ###RSA testing
    if(NOT GTest_FOUND)
        message(WARNING "Did not find GTEST LIBS")
    else()
        add_executable(RSA_testing src/keys.cpp src/hash.cpp src/arithmetic_functions.cpp testing/test_main.cpp testing/test_functions.cpp)
        target_include_directories(RSA_testing PRIVATE "${CMAKE_SOURCE_DIR}/src")
        target_compile_definitions(RSA_testing PRIVATE PROJECT_PATH="${CMAKE_SOURCE_DIR}")
        target_link_libraries(RSA_testing GTest::gtest GTest::gtest_main Boost::program_options)
    endif()

endif()