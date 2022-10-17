#include "CBitPattern.hpp"

void bitPattern::setMaxIndex(unsigned int maxIndex)
{
    unsigned int length = (maxIndex >> 6) + 1;
    for (size_t i = 0; i < length; i++)
    {
        status.push_back(0);
    }
}

bool bitPattern::isVisited(unsigned int index) const
{
    size_t vectorIndex = 0;
    while (index >= 64)
    {
        index -= 64;
        vectorIndex++;
    }
    return ((status[vectorIndex] & (1ULL << index)) != 0);
}

void bitPattern::setVisited(unsigned int index)
{
    size_t vectorIndex = 0;
    while (index >= 64)
    {
        index -= 64;
        vectorIndex++;
    }
    status[vectorIndex] = status[vectorIndex] | (1ULL << index);
}
