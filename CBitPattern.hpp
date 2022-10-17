#include <vector>

class bitPattern
{
public:
    bitPattern() { status.push_back(0); };
    bitPattern(const bitPattern& b)
    {
        for (auto&& it : b.status)
        {
            status.push_back(it);
        }
    };
    bool isVisited(unsigned int index) const;
    void setVisited(unsigned int index);
    bool operator == (const bitPattern& a) const;
protected:
    std::vector<uint64_t> status;
};
