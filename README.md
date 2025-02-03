# RSA
Project of course - introduction in the programming
Implementation of RSA key generation, encryption and decoding using them.

# Running
Before running you need to make sure that Google Test(https://github.com/google/googletest), Google Benchmark(https://github.com/google/benchmark) and Boost(https://www.boost.org/) are installed on the system
To be short, you should Cmake
```bash
cmake -B build/
cd build
make

#Only keys + encrypt/decrypt
./RSA

#running tests
./RSA_testing
```
