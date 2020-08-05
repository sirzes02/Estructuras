#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definitions of structures - global variables
struct Node
{
	char idPerson[24];
	char namePerson[24];
	short agePerson;

	struct Node *next;
	struct Node *before;
} * tile, *head;

// Function prototypes
void menu();
void insert();
void show(short);
void update();
void searchByAge();
void remove();
void error();
struct Node *searchId(char[24]);

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
		printf("5. Search Person by age.\n");
		printf("6. Delete Person.\n");
		printf("7. Exit.\n");
		printf("Choose a option:\n");
		scanf("%hi", &option);

		system("clear");

		switch (option)
		{
		case 1:
			insert();
			break;
		case 2:
			show(0);
			break;
		case 3:
			show(1);
			break;
		case 4:
			update();
			break;
		case 5:
			searchByAge();
			break;
		case 6:
			remove();
			break;
		case 7:
			break;
		default:
			printf("\nWrong data, please try again.\n");
			break;
		}

		system("read -p 'Press Enter to continue...' var");
	} while (option != 7);

	return EXIT_SUCCESS;
}

void insert()
{
	char auxId[24];

	printf("Insert a id:\n");
	scanf("%s", auxId);

	// If doesn't exist a Node with the ID
	if (!searchId(auxId))
	{
		struct Node *newPerson = new Node;

		// Copy the auxId content in the properti of the Node
		strcpy(newPerson->idPerson, auxId);
		printf("Insert the name:\n");
		scanf("%s", newPerson->namePerson);

		printf("Insert the age:\n");
		scanf("%hi", &newPerson->agePerson);
		while (newPerson->agePerson < 0 || newPerson->agePerson > 100)
		{
			error();
			printf("Insert the age:\n");
			scanf("%hi", &newPerson->agePerson);
		}

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
	}
	else
	{
		printf("This Id already exists.\n\n");
	}
}

void show(short option)
{
	// If the list isn't empty
	if (head)
	{
		// If the parameter is 0, the travel is ASC else DSC
		struct Node *current = option == 0 ? head : tile;

		while (current)
		{
			printf("The id: %s.\n", current->idPerson);
			printf("The name: %s.\n", current->namePerson);
			printf("The age: %hi.\n\n\n", current->agePerson);

			// If the parameter is 0, continue with the next else otherwise
			current = option == 0 ? current->next : current->before;
		}
	}
	else
	{
		printf("The list is empty.\n\n");
	}
}

void update()
{
	// If the list isn't empty
	if (head)
	{
		short option;
		char aux[24];

		printf("Insert the person's id to update.\n");
		scanf("%s", aux);

		struct Node *searchPerson = searchId(aux);

		// If the person with the ID exists
		if (searchPerson)
		{
			do
			{
				system("clear");

				printf("Update menu:\n");
				printf("1. Name.\n");
				printf("2. Age.\n");
				printf("3. Exit.\n");
				scanf("%hi", &option);

				switch (option)
				{
				case 1:
					printf("\n\nInsert the new name:\n");
					scanf("%s", searchPerson->namePerson);
					break;
				case 2:
					printf("\n\nInsert the new age:\n");
					scanf("%hi", &searchPerson->agePerson);
					while (searchPerson->agePerson < 0 || searchPerson->agePerson > 100)
					{
						error();
						printf("Insert the age:\n");
						scanf("%hi", &searchPerson->agePerson);
					}
					break;
				case 3:
					return;
				default:
					error();
				}
				printf("\n");
				system("read -p 'Press Enter to continue...' var");
			} while (true);
		}
		else
		{
			printf("Exist no one person with the id %s.\n\n", aux);
		}
	}
	else
	{
		printf("The list is empty.\n\n");
	}
}

void searchByAge()
{
	// If the list isn't empty
	if (head)
	{
		struct Node *current = head;
		short age;
		bool flag = false;

		printf("Insert the age to search:\n");
		scanf("%hi", &age);
		while (age < 0 || age > 100)
		{
			error();
			printf("Insert the age:\n");
			scanf("%hi", &age);
		}

		system("clear");
		printf("%hi years old are:\n\n", age);
		while (current)
		{
			if (current->agePerson == age)
			{
				printf("The person's id: %s.\n", current->idPerson);
				printf("The person's name: %s.\n", current->namePerson);
				printf("The person's age: %hi.\n\n\n", current->agePerson);

				flag = true;
			}
			current = current->next;
		}

		if (!flag)
		{
			printf("0.\n\n");
		}
	}
	else
	{
		printf("The list is empty.\n\n");
	}
}

void remove()
{
	// If the list isn't empty
	if (head)
	{
		char aux[24];

		printf("Insert the person's id to delete.\n");
		scanf("%s", aux);

		struct Node *searchPerson = searchId(aux);

		// If the person with the ID exists
		if (searchPerson)
		{
			if (!searchPerson->before && !searchPerson->next)
			{
				// If the Node is the only one
				head = NULL;
			}
			else if (searchPerson->next && !searchPerson->before)
			{
				// If the Node is the firts one
				searchPerson = head;
				head = head->next;
				head->before = NULL;
			}
			else if (!searchPerson->next && searchPerson->before)
			{
				// If the Node is the last one
				searchPerson = tile;
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
		}
		else
		{
			printf("Exist no one person with the id %s.\n\n", aux);
		}
	}
	else
	{
		printf("The list is empty.\n\n");
	}
}

void error()
{
	printf("\nWrong data, please try again.\n");
	system("read -p 'Press Enter to continue...' var");
	system("clear");
}

struct Node *searchId(char auxId[24])
{
	struct Node *current = head;

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
