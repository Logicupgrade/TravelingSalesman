#include "Graph.h"

Graph::Graph()
: m_adjacencymatrix(nullptr),m_vertexcount(0)
{
}

Graph::Graph(int vertexnum,std::string *vertexnames,int** adjmatrix)
: m_vertexcount(vertexnum)
{
    for(int i=0;i<vertexnum;i++)    //Fill name vector
    {
        m_vertices.push_back(vertexnames[i]);
    }
    m_adjacencymatrix = new int*[vertexnum];
    for(int i=0;i<vertexnum;i++)  //create and fill adj matrix
    {
        m_adjacencymatrix[i] = new int[vertexnum];
        for(int j=0;j<vertexnum;j++)
        {
            m_adjacencymatrix[i][j] = adjmatrix[i][j];
        }
    }
}

Graph::Graph(const Graph& other)
: m_vertexcount(other.m_vertexcount)
{
    m_vertices = other.m_vertices;
    m_adjacencymatrix = new int*[other.m_vertexcount];
    for(int i=0;i<m_vertexcount;i++)  //create and fill adj matrix
    {
        m_adjacencymatrix[i] = new int[m_vertexcount];
        for(int j=0;j<m_vertexcount;j++)
        {
            m_adjacencymatrix[i][j] = other.m_adjacencymatrix[i][j];
        }
    }
}

Graph::~Graph()
{
    clear();
}

void Graph::clear()
{
    m_vertices.clear();
    for(int i=0;i<m_vertexcount;i++)
    {
        delete m_adjacencymatrix[i];
    }
    delete[] m_adjacencymatrix;
    m_adjacencymatrix = nullptr;
    m_vertexcount = 0;
}


int Graph::getEdgeCost(int v1, int v2)
{
    if(m_adjacencymatrix)
    {
        return m_adjacencymatrix[v1][v2];
    }

    //wrote this to get rid of compiler warning
    else
    {
    	return -1;
    }
}

int Graph::traversePath(Path &currentPath)
{
    int total=0;
    for(int i=0;i<currentPath.getPathArraySize()-1;i++)
    {
        total+= getEdgeCost(currentPath.getCityIndexAt(i),currentPath.getCityIndexAt(i+1));
    }
    currentPath.setTraversalCost(total);
    return total;
}



void Graph::addVertex(std::string newEntry)
{
    if(m_adjacencymatrix)
    {
        int **newmatrix = new int*[m_vertexcount+1];
        for(int i=0;i<m_vertexcount+1;i++)  //create 2d array one larger than m_adjacencymatrix
        {
            newmatrix[i] = new int[m_vertexcount+1];
        }
        for(int i=0;i<m_vertexcount+1;i++)  //fill new array with m_adjacencymatrix, no edges to new vertex
        {
             for(int j=0;j<m_vertexcount+1;j++)
             {
                 if(i>=m_vertexcount||j>=m_vertexcount)
                 {
                     newmatrix[i][j] = 999999;
                 }
                 else
                 {
                     newmatrix[i][j] = m_adjacencymatrix[i][j];
                 }
             }
        }
        int newsize = m_vertexcount+1;
        std::vector<std::string> newvertices = m_vertices;
        newvertices.push_back(newEntry);
        clear();
        m_adjacencymatrix = newmatrix;
        m_vertexcount = newsize;
        m_vertices = newvertices;
    }
    else    //if matrix has 0 elements
    {
         int **newmatrix = new int*[m_vertexcount+1];
         newmatrix[0] = new int[m_vertexcount+1];
         newmatrix[0][0] = 999999;
         m_adjacencymatrix = newmatrix;
         m_vertexcount = 1;
         m_vertices.push_back(newEntry);
    }

}

void Graph::addEdge(std::string v1, std::string v2,int weight)
{
    m_adjacencymatrix[getIndex(v1)][getIndex(v2)] = weight;
}

void Graph::removeEdge(std::string v1, std::string v2)
{
    m_adjacencymatrix[getIndex(v1)][getIndex(v2)] = 999999;
}

std::string Graph::getVertex(int index)
{
    return m_vertices[index];
}

int Graph::getIndex(std::string s)
{
    for(int i=0;i<m_vertexcount;i++)
    {
        if(m_vertices[i]==s)
        {
            return i;
        }
    }
    return -1;
}

void Graph::displayMatrix()
{
	for(int i=0; i<m_vertexcount; i++)
	{
		for(int j=0; j<m_vertexcount; j++)
		{
			std::cout<<"["<<i<<"]["<<j<<"]="<<m_adjacencymatrix[i][j]<<" , ";
		}
		std::cout<<std::endl;
	}
}