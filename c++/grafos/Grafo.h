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

void Graph::initialize()
{
    h = NULL;
}

bool Graph::empty()
{
    return !h;
}

int Graph::size()
{
    int cont = 0;
    Vertex *aux = h;

    while (aux)
    {
        cont++;
        aux = aux->next;
    }

    return cont;
}

Vertex *Graph::getVertex(string name)
{
    Vertex *aux = h;

    while (aux)
    {
        if (aux->name == name)
        {
            return aux;
        }

        aux = aux->next;
    }

    return NULL;
}

void Graph::insertVertex(string name)
{
    Vertex *newVertex = new Vertex;

    newVertex->name = name;
    newVertex->next = NULL;
    newVertex->adjacent = NULL;

    if (empty())
    {
        h = newVertex;
    }
    else
    {
        Vertex *aux = h;

        while (aux->next)
        {
            aux = aux->next;
        }

        aux->next = newVertex;
    }
}

void Graph::insertEdge(Vertex *origin, Vertex *destiny, int weight)
{
    Edge *newEdge = new Edge;
    newEdge->weight = weight;
    newEdge->next = NULL;
    newEdge->adjacent = NULL;

    Edge *aux = origin->adjacent;

    if (!aux)
    {
        origin->adjacent = newEdge;
        newEdge->adjacent = destiny;
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = newEdge;
        newEdge->adjacent = destiny;
    }
}

void Graph::adjacencyList()
{
    Vertex *verticeAux = h;
    Edge *aristaAux;

    while (verticeAux)
    {
        cout << verticeAux->name << "->";
        aristaAux = verticeAux->adjacent;

        while (aristaAux)
        {
            cout << aristaAux->adjacent->name << "->";

            aristaAux = aristaAux->next;
        }

        verticeAux = verticeAux->next;

        cout << endl;
    }
}

void Graph::cancel()
{
    Vertex *aux;

    while (h)
    {
        aux = h;
        h = h->next;
        delete (aux);
    }
}

void Graph::removeEdge(Vertex *origin, Vertex *destiny)
{
    Edge *current = origin->adjacent;
    bool flag = false;

    if (!current)
    {
        cout << "The origin vertex have no edges" << endl;
    }
    else if (current->adjacent == destiny)
    {
        origin->adjacent = current->next;

        delete (current);
    }
    else
    {
        Edge *before;

        while (current)
        {
            if (current->adjacent == destiny)
            {
                flag = true;
                before->next = current->next;
                delete (current);
                break;
            }

            before = current;
            current = current->next;
        }

        if (!flag)
        {
            cout << "Those two vertices aren't connected" << endl;
        }
    }
}

void Graph::removeVertex(Vertex *vert)
{
    Vertex *current = h;
    Edge *aux;

    while (current)
    {
        aux = current->adjacent;

        while (aux)
        {
            if (aux->adjacent == vert)
            {
                removeEdge(current, aux->adjacent);
                break;
            }

            aux = aux->next;
        }

        current = current->next;
    }

    current = h;

    if (vert == h)
    {
        h = h->next;

        delete (current);
    }
    else
    {

        Vertex *before;

        while (current != vert)
        {
            before = current;
            current = current->next;
        }

        before->next = current->next;
        delete (current);
    }
}

void Graph::widthtravel(Vertex *origin)
{
    Vertex *current;
    queue<Vertex *> currentQueu;
    list<Vertex *> currentList;
    list<Vertex *>::iterator i;
    bool flag;
    bool flag2;

    currentQueu.push(origin);

    while (!currentQueu.empty())
    {
        flag = false;
        current = currentQueu.front();
        currentQueu.pop();

        for (i = currentList.begin(); i != currentList.end(); i++)
        {
            if (*i == current)
            {
                flag = true;
            }
        }

        if (!flag)
        {
            cout << current->name << ", ";
            currentList.push_back(current);

            Edge *aux = current->adjacent;

            while (aux)
            {
                flag2 = false;

                for (i = currentList.begin(); i != currentList.end(); i++)
                {
                    if (aux->adjacent == *i)
                    {
                        flag2 = true;
                    }
                }

                if (!flag2)
                {
                    currentQueu.push(aux->adjacent);
                }

                aux = aux->next;
            }
        }
    }
}

void Graph::depthTravel(Vertex *origin)
{
    Vertex *current;
    stack<Vertex *> currentStack;
    list<Vertex *> currentList;
    list<Vertex *>::iterator i;
    bool flag;
    bool flag2;

    currentStack.push(origin);

    while (!currentStack.empty())
    {
        flag = false;
        current = currentStack.top();
        currentStack.pop();

        for (i = currentList.begin(); i != currentList.end(); i++)
        {
            if (*i == current)
            {
                flag = true;
            }
        }

        if (!flag)
        {
            cout << current->name << ", ";
            currentList.push_back(current);

            Edge *aux = current->adjacent;

            while (aux)
            {
                flag2 = false;

                for (i = currentList.begin(); i != currentList.end(); i++)
                {
                    if (aux->adjacent == *i)
                    {
                        flag2 = true;
                    }
                }

                if (!flag2)
                {
                    currentStack.push(aux->adjacent);
                }

                aux = aux->next;
            }
        }
    }
}

void Graph::firstWidth(Vertex *origin, Vertex *destiny)
{
    typedef pair<Vertex *, Vertex *> VertexVertex;
    queue<Vertex *> currentQueu;
    stack<VertexVertex> currentStack;
    list<Vertex *> currentList;
    list<Vertex *>::iterator i;
    Vertex *current;
    Vertex *destinyActual;
    Edge *aux;
    bool flag;
    bool flag2;
    bool flag3 = false;

    currentQueu.push(origin);

    while (!currentQueu.empty())
    {
        flag = false;
        current = currentQueu.front();
        currentQueu.pop();

        for (i = currentList.begin(); i != currentList.end(); i++)
        {
            if (*i == current)
            {
                flag = true;
            }
        }

        if (!flag)
        {
            if (current == destiny)
            {
                flag3 = true;
                destinyActual = destiny;

                while (!currentStack.empty())
                {
                    cout << destinyActual->name << "<-";

                    while (!currentStack.empty() && currentStack.top().second != destinyActual)
                    {
                        currentStack.pop();
                    }

                    if (!currentStack.empty())
                    {
                        destinyActual = currentStack.top().first;
                    }
                }

                break;
            }

            currentList.push_back(current);

            aux = current->adjacent;

            while (aux)
            {
                flag2 = false;

                for (i = currentList.begin(); i != currentList.end(); i++)
                {
                    if (aux->adjacent == *i)
                    {
                        flag2 = true;
                    }
                }

                if (!flag)
                {
                    currentQueu.push(aux->adjacent);
                    currentStack.push(VertexVertex(current, aux->adjacent));
                }

                aux = aux->next;
            }
        }
    }

    if (!flag3)
    {
        cout << "There is no path between these two vertices" << endl;
    }
}

void Graph::firstDepth(Vertex *origin, Vertex *destiny)
{
    typedef pair<Vertex *, Vertex *> VertexVertex;
    Vertex *currentVertex;
    Vertex *currentDestiny;
    stack<Vertex *> currentStack;
    list<Vertex *> currentList;
    stack<VertexVertex> currentStackPar;
    list<Vertex *>::iterator i;
    Edge *aux;
    bool flag;
    bool flag2;
    bool flag3 = false;

    currentStack.push(origin);

    while (!currentStack.empty())
    {
        flag = false;
        currentVertex = currentStack.top();
        currentStack.pop();

        for (i = currentList.begin(); i != currentList.end(); i++)
        {
            if (currentVertex == *i)
            {
                flag = true;
            }
        }

        if (!flag)
        {
            if (currentVertex == destiny)
            {
                flag3 = true;
                currentDestiny = destiny;

                while (!currentStackPar.empty())
                {
                    cout << currentDestiny->name << "<-";

                    while (!currentStackPar.empty() && currentStackPar.top().second != currentDestiny)
                    {
                        currentStackPar.pop();
                    }

                    if (!currentStackPar.empty())
                    {
                        currentDestiny = currentStackPar.top().first;
                    }
                }
                break;
            }

            currentList.push_back(currentVertex);

            aux = currentVertex->adjacent;

            while (aux)
            {
                flag2 = false;

                for (i = currentList.begin(); i != currentList.end(); i++)
                {
                    if (aux->adjacent == *i)
                    {
                        flag2 = true;
                    }
                }

                if (!flag2)
                {
                    currentStack.push(aux->adjacent);
                    currentStackPar.push(VertexVertex(currentVertex, aux->adjacent));
                }
            }
        }
    }

    if (!flag3)
    {
        cout << "There is no path between these two vertices" << endl;
    }
}

bool comparation(pair<Vertex *, int> a, pair<Vertex *, int> b)
{
    return a.second < b.second;
}

void Graph::firstBest(Vertex *origin, Vertex *destiny)
{
    typedef pair<Vertex *, int> costeVertex;
    typedef pair<Vertex *, Vertex *> VertexVertex;
    list<costeVertex> costesList;
    list<costeVertex> orderList;
    list<costeVertex>::iterator i;
    list<costeVertex>::iterator j;
    stack<VertexVertex> currentStack;
    Vertex *currentVertex;
    Vertex *currentDestiny;
    Edge *aux;
    int currentCoste = 0;
    bool flag;
    bool flag2 = false;

    costesList.push_back(costeVertex(origin, 0));
    orderList.push_back(costeVertex(origin, 0));

    while (!orderList.empty())
    {
        currentVertex = orderList.front().first;
        currentCoste = orderList.front().second;

        orderList.pop_front();

        if (currentVertex == destiny)
        {
            cout << "Coste: " << currentCoste << endl;

            flag2 = true;
            currentDestiny = destiny;

            while (!currentStack.empty())
            {
                cout << currentDestiny->name << "<-";

                while (!currentStack.empty() && currentStack.top().second != currentDestiny)
                {
                    currentStack.pop();
                }

                if (!currentStack.empty())
                {
                    currentDestiny = currentStack.top().first;
                }
            }
            break;
        }

        aux = currentVertex->adjacent;

        while (aux)
        {
            flag = false;
            currentCoste += aux->weight;

            for (i = costesList.begin(); i != costesList.end(); i++)
            {
                if (aux->adjacent == i->first)
                {
                    flag = true;

                    if (currentCoste < i->second)
                    {
                        (*i).second = currentCoste;

                        for (j = orderList.begin(); j != orderList.end(); j++)
                        {
                            if (j->first == aux->adjacent)
                            {
                                (*j).second = currentCoste;
                            }
                        }

                        orderList.sort(comparation);
                        currentStack.push(VertexVertex(currentVertex, aux->adjacent));
                        currentCoste -= aux->weight;
                    }
                }
            }

            if (!flag)
            {
                costesList.push_back(costeVertex(aux->adjacent, currentCoste));
                orderList.push_back(costeVertex(aux->adjacent, currentCoste));
                orderList.sort(comparation);

                currentStack.push(VertexVertex(currentVertex, aux->adjacent));
                currentCoste -= aux->weight;
            }

            aux = aux->next;
        }
    }

    if (!flag2)
    {
        cout << "There is no path between these two vertices" << endl;
    }
}
#endif
