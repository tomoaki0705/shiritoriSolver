#include <vector>

class bitPattern
{
public:
    void setMaxIndex(unsigned int maxIndex);
    bitPattern() {};
    bitPattern(unsigned int maxIndex)
    {
        setMaxIndex(maxIndex);
    }
    bitPattern(const bitPattern& b)
    {
        for (auto&& it : b.status)
        {
            status.push_back(it);
        }
    }
    bool isVisited(unsigned int index) const;
    void setVisited(unsigned int index);
    std::vector<uint64_t> status;
};
