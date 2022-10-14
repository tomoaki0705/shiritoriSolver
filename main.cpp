#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct edge_
{
    unsigned int s;
    unsigned int d;
    unsigned int index; // low priority?
    edge_(unsigned int s_, unsigned int d_, unsigned int index_)
        : s(s_), d(d_), index(index_) {} 
};

typedef struct edge_ edge;

unsigned int addAndGetIndex(std::vector<std::string>& list, const std::string& needle)
{
    auto it = std::find(list.begin(), list.end(), needle);
    if (it == list.end())
    {
        list.push_back(needle);
        return list.size() - 1;
    }
    unsigned int index = 0;
    for (size_t i = 0; i < list.size(); i++)
    {
        if (list[i] == needle)
        {
            return i;
        }
    }
}

void readEdges(const char* filename, std::vector<std::string>& nameOfVertex, std::vector<edge>& edges)
{
    std::ifstream ifs(filename);
    if (ifs.is_open() == false)
    {
        return;
    }
    unsigned int lineCount = 0;
    while (ifs.eof() == false)
    {
        std::string stub;
        ifs >> stub;
        unsigned int indexSrc = addAndGetIndex(nameOfVertex, stub);
        ifs >> stub;
        unsigned int indexDst = addAndGetIndex(nameOfVertex, stub);
        edge station(indexSrc, indexDst, lineCount); // edge stands for station
        edges.push_back(station);
        lineCount++;
    }
#ifdef _DEBUG && 0
    size_t i = 0;
    for ( auto&& it : nameOfVertex )
    {
        std::cout << i << ":" << it << std::endl;
        i++;
    }
    for ( auto&& it :  edges )
    {
        std::cout << it.index << ":" << nameOfVertex[it.s] << "->" << nameOfVertex[it.d] << std::endl;
    }
#endif
    return;
}

int main(int argc, char**argv)
{
    std::vector<std::string> nameOfVertex;
    std::vector<edge> edges;
    readEdges("./graph.txt", nameOfVertex, edges);
    return 0;
}
