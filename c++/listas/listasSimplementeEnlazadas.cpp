#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definitions of structures - global variables
struct Node
{
    char idPerson[24];

    Node *next;
} * list;

// Function prototypes
void menu();
void insert(char[24]);
void show();
void update(char[24]);
void remove(char[24]);
Node *search(char[24]);

// Functions
int main(void)
{
    short option = 0;

    do
    {
        system("clear");

        printf("Menu:\n");
        printf("1. Insert person.\n");
        printf("2. Show people.\n");
        printf("3. Update Person.\n");
        printf("4. Delete Person.\n");
        printf("5. Exit.\n");
        printf("Choose a option:\n");
        scanf("%hi", &option);

        system("clear");

        switch (option)
        {
        case 1:
            char auxId[24];

            printf("Insert a id:\n");
            scanf("%s", auxId);

            insert(auxId);
            break;
        case 2:
            // If the list isn't empty
            if (list)
            {
                show();
            }
            else
            {
                printf("The list is empty.\n\n");
            }
            break;
        case 3:
            // If the list isn't empty
            if (list)
            {
                char aux[24];

                printf("Insert the person's id to update.\n");
                scanf("%s", aux);

                update(aux);
            }
            else
            {
                printf("The list is empty.\n\n");
            }
            break;
        case 4:
            // If the list isn't empty
            if (list)
            {
                char aux[24];

                printf("Insert the person's id to update.\n");
                scanf("%s", aux);

                remove(aux);
            }
            else
            {
                printf("The list is empty.\n\n");
            }
            break;
        case 5:
            break;
        default:
            printf("\nWrong data, please try again.\n");
        }

        system("read -p 'Press Enter to continue...' var");
    } while (option != 5);

    return EXIT_SUCCESS;
}

void insert(char auxId[24])
{
    // If doesn't exist a Node with the ID
    if (!search(auxId))
    {
        Node *newPerson = new Node;

        // Copy the auxId content in the properti of the Node
        strcpy(newPerson->idPerson, auxId);

        /////////////////////////////
        // If the list is empty
        if (!list)
        {
            list = newPerson;
            list->next = NULL;
        }
        else
        {
            Node *aux = list;
            list = newPerson;
            list->next = aux;
        }
        //////////////////////////////
    }
    else
    {
        printf("This Id already exists.\n\n");
    }
}

void show()
{
    ///////////////////////////////////////////////////////
    Node *current = list;

    while (current)
    {
        printf("The id: %s.\n", current->idPerson);

        current = current->next;
    }
    ///////////////////////////////////////////////////////
}

void update(char aux[24])
{
    Node *searchPerson = search(aux);
    char auxNew[24];

    // If the person with the ID exists
    if (searchPerson)
    {
        printf("\n\nInsert the new id:\n");
        scanf("%s", auxNew);

        if (!search(auxNew))
        {
            strcpy(searchPerson->idPerson, auxNew);
        }
        else
        {
            printf("Already exist a person with this id %s.\n\n", aux);
        }
    }
    else
    {
        printf("Exist no one person with the id %s.\n\n", aux);
    }
}

void remove(char aux[24])
{

    Node *searchPerson = search(aux);

    // If the person with the ID exists
    if (searchPerson)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        // If the Node is the first one
        if (searchPerson == list)
        {
            Node *aux = new Node();
            aux = list->next;
            list = aux;
        }
        else
        {
            Node *current = list;
            // This variable will be used as an auxiliary to save the node immediately previous the current one
            Node *before = new Node();

            while (current)
            {
                // If the ID of the current Node is equals to auxID
                if (strcmp(aux, current->idPerson) == 0)
                {
                    before->next = current->next;
                    break;
                }
                before = current;
                current = current->next;
            }
        }
        free(searchPerson);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else
    {
        printf("Exist no one person with the id %s.\n\n", aux);
    }
}

Node *search(char auxId[24])
{
    Node *current = list;

    while (current)
    {
        // If the ID of the current Node is equals to auxID
        if (strcmp(auxId, current->idPerson) == 0)
        {
            return current;
        }

        current = current->next;
    }
    return NULL;
}
