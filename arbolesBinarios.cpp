#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;

    Node *father;
    Node *right;
    Node *left;
};

void menu();
void insert(Node *&, int, Node *);
Node *create(int, Node *);
void show(Node *, int);
void remove(Node *);
Node *foundLeft(Node *);
Node *search(Node *, int);
void preOrder(Node *);
void inOrder(Node *);
void postOrder(Node *);
//bool compare(Node *, Node *);
void error();

int main(void)
{
    menu();
    return EXIT_SUCCESS;
}

void menu()
{
    Node *root = NULL;
    bool flag;
    short option;
    int data;

    do
    {
        system("clear");

        printf("Menu\n");
        printf("1. Insert.\n");
        printf("2. Show.\n");
        printf("3. Remove.\n");
        printf("4. Show pre-order.\n");
        printf("5. Show in-order.\n");
        printf("6. Show post-order.\n");
        printf("7. Exit.\n");
        printf("Escoja:\n");
        scanf("%hi", &option);

        system("clear");

        switch (option)
        {
        case 1:
            printf("\nInsert new element:\n");
            scanf("%d", &data);

            if (!search(root, data))
            {
                insert(root, data, NULL);
            }
            else
            {
                error();
            }

            break;
        case 2:
            show(root, 0);

            break;
        case 3:
            printf("\nInsert element to remove:\n");
            scanf("%d", &data);

            // This would be the best way, but i have a problem... jeje
            //Node *toRemove = search(root, data);

            if (search(root, data))
            {
                remove(search(root, data));
            }
            else
            {
                error();
            }

            break;
        case 4:
            preOrder(root);

            break;
        case 5:
            inOrder(root);

            break;
        case 6:
            postOrder(root);

            break;
        case 7:
            return;
        default:
            printf("\nERROR...");
        }

        system("read -p 'Press Enter to continue...' var");
    } while (option != 7);
}

void insert(Node *&root, int data, Node *father)
{
    if (!root)
    {
        root = create(data, father);
    }
    else
    {
        if (data < root->data)
        {
            insert(root->left, data, root);
        }
        else
        {
            insert(root->right, data, root);
        }
    }
}

Node *create(int data, Node *father)
{
    Node *newNode = new Node();

    newNode->data = data;
    newNode->father = father;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

void show(Node *root, int count)
{
    if (!root)
    {
        return;
    }
    else
    {
        show(root->right, count + 1);

        for (int i = 0; i < count; i++)
        {
            printf("   ");
        }
        printf("%d\n", root->data);

        show(root->left, count + 1);
    }
}

Node *search(Node *root, int data)
{
    if (!root)
    {
        return NULL;
    }
    else if (root->data == data)
    {
        return root;
    }
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}

void remove(Node *node)
{
    if (!node->right && !node->left)
    {
        if (node->father)
        {
            if (node->father->left == node)
            {
                node->father->left = NULL;
            }
            else if (node->father->right == node)
            {
                node->father->right = NULL;
            }
        }
        else
        {
            node = NULL;
        }
    }
    else if (node->right && node->left)
    {
        Node *leftNode = foundLeft(node->right);

        node->data = leftNode->data;

        remove(leftNode);
    }
    else
    {
        Node *currentSon = node->left ? node->left : node->right;

        if (node->father)
        {
            if (node->father->left == node)
            {
                node->father->left = currentSon;
            }
            else
            {
                node->father->right = currentSon;
            }

            currentSon->father = node->father;
        }
        else
        {
            node->data = currentSon->data;

            if (node->left)
            {
                node->left = currentSon->left;
            }
            else
            {
                node->right = currentSon->right;
            }
        }
    }
}

Node *foundLeft(Node *node)
{
    if (node->left)
    {
        return foundLeft(node->left);
    }

    return node;
}

void preOrder(Node *root)
{
    if (!root)
    {
        return;
    }
    else
    {
        printf(" %d << - >>", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root)
{
    if (!root)
    {
        return;
    }
    else
    {
        preOrder(root->left);
        printf(" %d << - >>", root->data);
        preOrder(root->right);
    }
}

void postOrder(Node *root)
{
    if (!root)
    {
        return;
    }
    else
    {
        preOrder(root->left);
        preOrder(root->right);
        printf(" %d << - >>", root->data);
    }
}

/*
bool compare(Node *root_1, Node *root_2){
	if(root_1 == root_2)
    {
		return true;
	}
    if(root_1 == NULL || root_2 == NULL)
    {
		return false;
    }
	return (root_1->data == root_2->data && compare(root_1->right, root_2->right) && compare(root_1->left, root_2->left));
}
*/

void error()
{
    printf("\nWrong data, please try again.\n");
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}