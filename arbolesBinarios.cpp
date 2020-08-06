#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;

    Node *father;
    Node *right;
    Node *left;
};

void insert(Node *&, int, Node *);
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

            // If doesn't exist a node with this data
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
            // If the tree isn't empty
            if (root)
            {
                show(root, 0);
            }
            else
            {
                printf("The tree is empty.\n\n");
            }

            break;
        case 3:
            // If the tree isn't empty
            if (root)
            {
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
            }
            else
            {
                printf("The tree is empty.\n\n");
            }

            break;
        case 4:
            // If the tree isn't empty
            if (root)
            {
                preOrder(root);
            }
            else
            {
                printf("The tree is empty.\n\n");
            }

            break;
        case 5:
            // If the tree isn't empty
            if (root)
            {
                inOrder(root);
            }
            else
            {
                printf("The tree is empty.\n\n");
            }

            break;
        case 6:
            // If the tree isn't empty
            if (root)
            {
                postOrder(root);
            }
            else
            {
                printf("The tree is empty.\n\n");
            }

            break;
        case 7:
            return;
        default:
            printf("\nWrong data, please try again.\n");
        }

        system("read -p 'Press Enter to continue...' var");
    } while (option != 7);

    return EXIT_SUCCESS;
}

void insert(Node *&root, int data, Node *father)
{
    /*
        this proccess depends of the node's data-number.  
        You have to know if the data-number of the node that you want to save is lowero higher than current node,
        don't forget that these functions are recursive, so, if the number is lower, you have to go to the current's left node ,
        and repit until find a null, then, save the new node there; if the number is higher, is the same thing but to the right.
    */

    // If the node doesn't exists
    if (!root)
    {
        Node *newNode = new Node();

        newNode->data = data;
        newNode->father = father;

        root = newNode;
    }
    else
    {
        // If data is lower than current node
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

void show(Node *root, int count)
{
    // If the node doesn't exists
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
    // If the node doesn't exists
    if (!root)
    {
        return NULL;
    }
    // If the data of the current node is equals to data
    else if (root->data == data)
    {
        return root;
    }
    // If the data of the current node is lower than data
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
    // If the node has no children
    if (!node->right && !node->left)
    {
        /*
            Just change the parent pointer to null. If the node is the root, change it to null.
        */

        // If the node has a father (Not is the root)
        if (node->father)
        {
            // If the node's left child is the node
            if (node->father->left == node)
            {
                node->father->left = NULL;
            }
            else
            {
                node->father->right = NULL;
            }
        }
        else
        {
            node = NULL;
        }
    }
    // If the node has children
    else if (node->right && node->left)
    {
        /*
            Finds the leftmost node of the current node's right child, change the data of the current node with the data of the leftmost,
            call again the function remove but this time send the leftmost.
        */

        // Call function to find the last node to the left of the node's right child
        Node *leftmost = foundLeft(node->right);

        node->data = leftmost->data;

        remove(leftmost);
    }
    else
    {
        /*
            Change the parent's pointers with the current node's children.
            This depends if the node that exist is the left or the right. Respect the hierarchy.
        */

        // CurrentSon depends of the child that exists
        Node *currentSon = node->left ? node->left : node->right;

        // If the node isn't the root
        if (node->father)
        {
            // If the node's left child is the node
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