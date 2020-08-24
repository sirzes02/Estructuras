#include <iostream>
#include <stdlib.h>
#include "Grafo.h"

using namespace std;

int main()
{
    Graph G;
    G.initialize();
    int option;

    G.insertVertex("afghanistan");
    G.insertVertex("albania");
    G.insertVertex("algeria");
    G.insertVertex("andorra");
    G.insertVertex("angola");
    G.insertVertex("argentina");
    G.insertVertex("armenia");
    G.insertVertex("australia");
    G.insertVertex("austria");
    G.insertVertex("azerbaijan");

    G.insertEdge(G.getVertex("afghanistan"), G.getVertex("albania"), 800);
    G.insertEdge(G.getVertex("algeria"), G.getVertex("afghanistan"), 400);
    G.insertEdge(G.getVertex("algeria"), G.getVertex("andorra"), 300);
    G.insertEdge(G.getVertex("albania"), G.getVertex("andorra"), 700);
    G.insertEdge(G.getVertex("andorra"), G.getVertex("argentina"), 900);
    G.insertEdge(G.getVertex("andorra"), G.getVertex("armenia"), 400);
    G.insertEdge(G.getVertex("andorra"), G.getVertex("australia"), 350);
    G.insertEdge(G.getVertex("angola"), G.getVertex("algeria"), 500);
    G.insertEdge(G.getVertex("angola"), G.getVertex("albania"), 450);
    G.insertEdge(G.getVertex("angola"), G.getVertex("BJX"), 250);
    G.insertEdge(G.getVertex("angola"), G.getVertex("australia"), 500);
    G.insertEdge(G.getVertex("argentina"), G.getVertex("azerbaijan"), 1200);
    G.insertEdge(G.getVertex("armenia"), G.getVertex("azerbaijan"), 450);
    G.insertEdge(G.getVertex("australia"), G.getVertex("azerbaijan"), 450);
    G.insertEdge(G.getVertex("australia"), G.getVertex("austria"), 650);
    G.insertEdge(G.getVertex("austria"), G.getVertex("angola"), 650);

    do
    {
        system("clear");

        cout << "\n1. Insert Vertex" << endl;
        cout << "2. Insert Edge" << endl;
        cout << "3. Adjacent list" << endl;
        cout << "4. Size" << endl;
        cout << "5. Remove Vertex" << endl;
        cout << "6. Remove Edge" << endl;
        cout << "7. Cancel" << endl;
        cout << "8. Width travel" << endl;
        cout << "9. Depth travel" << endl;
        cout << "10. First Width" << endl;
        cout << "11. First depth" << endl;
        cout << "12. First better" << endl;
        cout << "13. Exit" << endl;
        cout << endl
             << "Choose one: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            string name;

            system("clear");

            cout << "Insert the Vertex's name: ";
            cin.ignore();
            getline(cin, name, '\n');
            G.insertVertex(name);
            cin.get();
            cin.get();

            break;
        }
        case 2:
        {
            string origin, destiny;
            int weight;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the orign vertex name: ";
                cin.ignore();
                getline(cin, origin, '\n');
                cout << "Insert the destiny vertex name: ";
                getline(cin, destiny, '\n');
                cout << "Insert the weight: ";
                cin >> weight;

                if (!G.getVertex(origin) || !G.getVertex(destiny))
                {
                    cout << "One of the vertex is invalid" << endl;
                }
                else
                {
                    G.insertEdge(G.getVertex(origin), G.getVertex(destiny), weight);
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 3:
        {
            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                G.adjacencyList();
            }
            cin.get();
            cin.get();

            break;
        }
        case 4:
        {
            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Size: " << G.size() << endl;
            }
            cin.get();
            cin.get();

            break;
        }
        case 5:
        {
            string name;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the vertex name to remove: ";
                cin.ignore();
                getline(cin, name, '\n');

                if (!G.getVertex(name))
                {
                    cout << "Invalid vertex" << endl;
                }
                else
                {
                    G.removeVertex(G.getVertex(name));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 6:
        {
            string origin, destiny;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the origin vertex name: ";
                cin.ignore();
                getline(cin, origin, '\n');
                cout << "Insert the destiny vertex name: ";
                getline(cin, destiny, '\n');

                if (!G.getVertex(origin) || !G.getVertex(destiny))
                {
                    cout << "Invalid vertices" << endl;
                }
                else
                {
                    G.removeEdge(G.getVertex(origin), G.getVertex(destiny));
                }
            }
            cin.get();
            cin.get();
            break;
        }
        case 7:
        {
            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                G.cancel();
            }
            cin.get();
            cin.get();

            break;
        }
        case 8:
        {
            string name;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the inicial vertice name: ";
                cin.ignore();
                getline(cin, name, '\n');

                if (!G.getVertex(name))
                {
                    cout << "That vertex is invalid" << endl;
                }
                else
                {
                    G.widthtravel(G.getVertex(name));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 9:
        {
            string name;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the inicial vertex name: ";
                cin.ignore();
                getline(cin, name, '\n');

                if (!G.getVertex(name))
                {
                    cout << "That vertex is invalid" << endl;
                }
                else
                {
                    G.depthTravel(G.getVertex(name));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 10:
        {
            string origin, destiny;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the origin vertex name: ";
                cin.ignore();
                getline(cin, origin, '\n');
                cout << "Insert the destiny vertex name: ";
                getline(cin, destiny, '\n');

                if (!G.getVertex(origin) || !G.getVertex(destiny))
                {
                    cout << "Invalid vertices" << endl;
                }
                else
                {
                    G.firstWidth(G.getVertex(origin), G.getVertex(destiny));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 11:
        {
            string origin, destiny;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the origin vertex name: ";
                cin.ignore();
                getline(cin, origin, '\n');
                cout << "Insert the destiny vertex name: ";
                getline(cin, destiny, '\n');

                if (!G.getVertex(origin) || !G.getVertex(destiny))
                {
                    cout << "Invalid vertices" << endl;
                }
                else
                {
                    G.firstDepth(G.getVertex(origin), G.getVertex(destiny));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 12:
        {
            string origin, destiny;

            system("clear");

            if (G.empty())
            {
                cout << "The graph is empty" << endl;
            }
            else
            {
                cout << "Insert the origin vertex name: ";
                cin.ignore();
                getline(cin, origin, '\n');
                cout << "Insert the destiny vertex name: ";
                getline(cin, destiny, '\n');

                if (!G.getVertex(origin) || !G.getVertex(destiny))
                {
                    cout << "Invalid vertices" << endl;
                }
                else
                {
                    G.firstBest(G.getVertex(origin), G.getVertex(destiny));
                }
            }
            cin.get();
            cin.get();

            break;
        }
        case 13:
        {
            break;
        }
        default:
        {
            cout << "Error, choose a correct option" << endl;
        }
        }
    } while (option != 13);

    return EXIT_SUCCESS;
}
