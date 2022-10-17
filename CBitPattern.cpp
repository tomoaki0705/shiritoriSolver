#include "CBitPattern.hpp"

const unsigned int kbitLength = sizeof(uint64_t) * 8;

inline unsigned int indexOfVector(unsigned int index)
{
    return (index / kbitLength);
}

bool bitPattern::isVisited(unsigned int index) const
{
    size_t vectorIndex = indexOfVector(index);
    if (status.size() <= vectorIndex)
    {
        return false;
    }
    return ((status[vectorIndex] & (1ULL << index)) != 0);
}

void bitPattern::setVisited(unsigned int index)
{
    size_t vectorIndex = indexOfVector(index);
    while (status.size() <= vectorIndex)
    {
        status.push_back(0);
    }
    status[vectorIndex] = status[vectorIndex] | (1ULL << index);
}

bool bitPattern::operator == (const bitPattern& a) const
{
    if (status.size() != a.status.size())
    {
        return false;
    }

    bool result = true;
    for (size_t i = 0; i < status.size(); i++)
    {
        if (status[i] != a.status[i])
        {
            result = false;
            break;
        }
    }
    return result;
}
