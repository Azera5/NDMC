#ifndef AUXILIARY_FUNKTIONS_H
#define AUXILIARY_FUNKTIONS_H

#include <iostream>
#include <vector>

template <typename T>
void printRow(const std::vector<T>& row) {
    for (const auto& item : row) std::cout << std::left << std::setw(15) << item;
    std::cout << std::endl; 
}
#endif