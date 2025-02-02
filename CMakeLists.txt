cmake_minimum_required(VERSION 3.10)

project(RSA_keys)
add_definitions(-DPATH)


find_package(Boost COMPONENTS program_options)

if(NOT Boost_FOUND)
    message(WARNING "Did not find boost LIBS")
else()
    ###RSA
    add_executable(RSA src/main.cpp src/keys.cpp src/hash.cpp src/arithmetic_functions.cpp)
    target_link_libraries(RSA Boost::program_options)
    target_compile_definitions(RSA PRIVATE PROJECT_PATH="${CMAKE_SOURCE_DIR}")
    

endif()