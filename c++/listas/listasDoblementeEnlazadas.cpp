#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definitions of structures - global variables
struct Node
{
	char idPerson[24];

	Node *next;
	Node *before;
} * tile, *head;

// Function prototypes
void menu();
void insert(char[24]);
void show(short);
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
		printf("2. Show people ASC.\n");
		printf("3. Show people DSC.\n");
		printf("4. Update Person.\n");
		printf("5. Delete Person.\n");
		printf("6. Exit.\n");
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
			if (head)
			{
				show(0);
			}
			else
			{
				printf("The list is empty.\n\n");
			}

			break;
		case 3:
			if (head)
			{
				show(1);
			}
			else
			{
				printf("The list is empty.\n\n");
			}

			break;
		case 4:
			if (head)
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
		case 5:
			// If the list isn't empty
			if (head)
			{
				char aux[24];

				printf("Insert the person's id to delete.\n");
				scanf("%s", aux);

				remove(aux);
			}
			else
			{
				printf("The list is empty.\n\n");
			}

			break;
		case 6:
			break;
		default:
			printf("\nWrong data, please try again.\n");
		}

		system("read -p 'Press Enter to continue...' var");
	} while (option != 6);

	return EXIT_SUCCESS;
}

void insert(char auxId[24])
{
	// If doesn't exist a Node with the ID
	if (!search(auxId))
	{
		///////////////////////////////////////////////////////
		Node *newPerson = new Node;

		// Copy the auxId content in the properti of the Node
		strcpy(newPerson->idPerson, auxId);

		// If the list is empty
		if (!head)
		{
			head = newPerson;
			head->next = NULL;
			head->before = NULL;
			tile = head;
		}
		else
		{
			tile->next = newPerson;
			newPerson->next = NULL;
			newPerson->before = tile;
			tile = newPerson;
		}
		//////////////////////////////////////////////////////}
	}
	else
	{
		printf("Already exist a person with this id %s.\n\n", auxId);
	}
}

void show(short option)
{
	////////////////////////////////////////////////////////////////////
	// If the parameter is 0, the travel is ASC else DSC
	Node *current = option == 0 ? head : tile;

	while (current)
	{
		printf("The id: %s.\n", current->idPerson);

		// If the parameter is 0, continue with the next else otherwise
		current = option == 0 ? current->next : current->before;
	}
	////////////////////////////////////////////////////////////////////
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
		///////////////////////////////////////////////////////
		if (!searchPerson->before && !searchPerson->next)
		{
			// If the Node is the only one
			head = NULL;
		}
		else if (searchPerson->next && !searchPerson->before)
		{
			// If the Node is the firts one
			head = head->next;
			head->before = NULL;
		}
		else if (!searchPerson->next && searchPerson->before)
		{
			// If the Node is the last one
			tile = tile->before;
			tile->next = NULL;
		}
		else
		{
			// If the Node is in the middle
			searchPerson->before->next = searchPerson->next;
			searchPerson->next->before = searchPerson->before;
		}
		free(searchPerson);
		////////////////////////////////////////////////////////
	}
	else
	{
		printf("Exist no one person with the id %s.\n\n", aux);
	}
}

Node *search(char auxId[24])
{
	Node *current = head;

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
