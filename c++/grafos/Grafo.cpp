#include <Grafo.h>

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

void Graph::insertEdge(Vertex *origen, Vertex *destiny, int weight)
{
    Edge *newEdge = new Edge;
    newEdge->weight = weight;
    newEdge->next = NULL;
    newEdge->adjacent = NULL;

    Edge *aux = origen->adjacent;

    if (!aux)
    {
        origen->adjacent = newEdge;
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

void Graph::removeEdge(Vertex *origen, Vertex *destiny)
{
    Edge *current = origen->adjacent;
    bool flag = false;

    if (!current)
    {
        cout << "The origen vertex have no edges" << endl;
    }
    else if (current->adjacent == destiny)
    {
        origen->adjacent = current->next;

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

void Graph::widthtravel(Vertex *origen)
{
    Vertex *current;
    queue<Vertex *> currentQueu;
    list<Vertex *> currentList;
    list<Vertex *>::iterator i;
    bool flag;
    bool flag2;

    currentQueu.push(origen);

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

void Graph::depthTravel(Vertex *origen)
{
    Vertex *current;
    stack<Vertex *> currentStack;
    list<Vertex *> currentList;
    list<Vertex *>::iterator i;
    bool flag;
    bool flag2;

    currentStack.push(origen);

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

void Graph::firstWidth(Vertex *origen, Vertex *destiny)
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

    currentQueu.push(origen);

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
    }

    if (!flag)
    {
        if (current = destiny)
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
            //break;
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

    if (!flag3)
    {
        cout << "There is no path between these two vertices" << endl;
    }
}