#pragma once

#include <string>

unsigned int djb2_hash(std::string str);
unsigned int sdbm_hash(std::string str);