#pragma once

#include "Sort.hpp"

class SelectionSort : public Sort
{
public:
    SelectionSort();
    void sort(sf::RenderWindow&, std::vector<int>&) override;
};
