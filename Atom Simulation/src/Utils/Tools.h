#pragma once

#include <string>
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << value;
    return std::move(out).str();
}
