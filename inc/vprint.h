#pragma once

#include <format>
#include <iostream>

#define print(...) std::cout << std::format(__VA_ARGS__)
