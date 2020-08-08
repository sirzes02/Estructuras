#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>

using namespace std;

class Edge;

class Vertex
{
    Vertex *next;
    Edge *adjacent;
    string name;
    friend class Graph;
};

class Edge
{
    Edge *next;
    Vertex *adjacent;
    int weight;
    friend class Graph;
};

class Graph
{
    Vertex *h;

public:
    void initialize();
    bool empty();
    int size();
    Vertex *getVertex(string);
    void insertEdge(Vertex *, Vertex *, int);
    void insertVertex(string);
    void adjacencyList();
    void removeEdge(Vertex *, Vertex *);
    void cancel();
    void removeVertex(Vertex *);
    void widthtravel(Vertex *);
    void depthTravel(Vertex *);
    void firstWidth(Vertex *, Vertex *);
    void firstDepth(Vertex *, Vertex *);
    void firstBest(Vertex *, Vertex *);
};
#endif