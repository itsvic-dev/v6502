#pragma once

#include <format>
#include <iostream>

#define print(...) std::cout << std::format(__VA_ARGS__) << std::flush
#define print_err(...) std::cerr << std::format(__VA_ARGS__) << std::flush
