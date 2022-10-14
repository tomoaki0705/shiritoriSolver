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

class bitPattern
{
public:
    void setMaxIndex(unsigned int maxIndex)
    {
        unsigned int length = (maxIndex >> 6) + 1;
        for (size_t i = 0; i < length; i++)
        {
            status.push_back(0);
        }
    }
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
    bool isVisited(unsigned int index) const
    {
        size_t vectorIndex = 0;
        while (index >= 64)
        {
            index = index >> 6;
            vectorIndex++;
        }
        return (status[vectorIndex] & (1ULL << index));
    }
    void setVisited(unsigned int index)
    {
        size_t vectorIndex = 0;
        while (index >= 64)
        {
            index = index >> 6;
            vectorIndex++;
        }
        status[vectorIndex] = status[vectorIndex] | (1ULL << index);
    }
    std::vector<uint64_t> status;
};

class vertex_
{
public:
    unsigned int currentVertex;
    struct vertex_* previous;
    bitPattern visitedEdges;
    vertex_(unsigned int currentVertex_, unsigned int maxIndex)
        : currentVertex(currentVertex_)
        , previous(NULL)
    {
        visitedEdges = bitPattern(maxIndex);
    };
    vertex_(unsigned int currentVertex_, unsigned int currentEdge, bitPattern visitedEdges_)
        : currentVertex(currentVertex_)
        , visitedEdges(visitedEdges_)
        , previous(NULL)
    {
        visitedEdges.setVisited(currentEdge);
    };
};

typedef class vertex_ vertex;


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

unsigned int recursiveHop(const std::vector<std::string>& nameOfVertex, const std::vector<edge>& edges, std::vector<std::vector<vertex*> >& history, unsigned int currentHop)
{
    std::vector<vertex*> currentVerteces;
    for (auto&& it : history[currentHop - 1])
    {
        for (size_t i = 0; i < edges.size(); i++)
        {
            if (edges[i].s == it->currentVertex && (it->visitedEdges.isVisited(edges[i].index) == false))
            {
                vertex* v = new vertex(edges[i].d, edges[i].index, it->visitedEdges);
                currentVerteces.push_back(v);
            }
        }
    }
    if (currentVerteces.empty() == false)
    {
        history.push_back(currentVerteces);
        recursiveHop(nameOfVertex, edges, history, currentHop + 1);
    }
    return 0;
}

unsigned int searchMaxHop(const std::vector<std::string>& nameOfVertex, const std::vector<edge>& edges, unsigned int startIndex)
{
    std::vector<std::vector<vertex*>> history;
    unsigned int maxIndex = edges.size();

    // list
    vertex *init = new vertex(startIndex, maxIndex);
    std::vector<vertex*> stub;
    stub.push_back(init);
    history.push_back(stub);
    auto result = recursiveHop(nameOfVertex, edges, history, 1);
    delete init;
    return 0;
}

int main(int argc, char**argv)
{
    std::vector<std::string> nameOfVertex;
    std::vector<edge> edges;
    readEdges("./graph.txt", nameOfVertex, edges);
    searchMaxHop(nameOfVertex, edges, 0);
    return 0;
}
