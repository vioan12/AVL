
#include "AVL.h"
#include<stdio.h>
int max( int a, int b)
{
	return ( a>b ? a:b );
}

//calculates the longest path from a current node to a leaf
int maxPathLength (struct NodeAVL *node)
{
	if( node == NULL )
		return 0;
	return ( max( maxPathLength( node->right ), maxPathLength( node->left) ) +1 );
}

//calculates the balance indicator of each node of the tree
void computeBalanceFactor (struct NodeAVL *node)
{
	int maxLeft = 0, maxRight = 0;

	if( node->left!=NULL )
		maxLeft = maxPathLength ( node->left );
	else
		maxLeft = 0;

	if( node->right!=NULL )
		maxRight = maxPathLength ( node->right );
	else
		maxRight = 0;

	node->echi = maxRight - maxLeft;
}

//simple left rotation
struct NodeAVL* leftRotation (struct NodeAVL *node)	//p is critical node
{
	struct NodeAVL *heavyChild;

	heavyChild = node->right;
	node->right = heavyChild->left;
	heavyChild->left = node;

	computeBalanceFactor(node);
	computeBalanceFactor(heavyChild);

	node = heavyChild;
	return node;
}

//simple right rotation
struct NodeAVL* rightRotation (struct NodeAVL *node)
{
	struct NodeAVL *heavyChild;

	heavyChild = node->left;
	node->left = heavyChild->right;
	heavyChild->right = node;

	computeBalanceFactor(node);
	computeBalanceFactor(heavyChild);

	node = heavyChild;
	return node;
}

//double left rotation
struct NodeAVL* doubleLeftRotation (struct NodeAVL *node)
{
	node->right = rightRotation( node->right );
	printf("\nRotaie stanga la nivelul %d ",cautare_nod(root,node));
	node = leftRotation(node);
	return node;
}

//double right rotation
struct NodeAVL* doubleRightRotation (struct NodeAVL *node)
{
	node->left = leftRotation( node->left );
	printf("\nRotaie dreapta la nivelul %d ",cautare_nod(root,node));
	node = rightRotation(node);
	return node;
}

//tree balancing function
struct NodeAVL* balance(struct NodeAVL *node)
{
	struct NodeAVL *heavyChild;

	computeBalanceFactor(node);

	if( node->echi == -2 )	// if p is a critical junction (LEFT hanging)
	{
		heavyChild = node->left;	// heavyChild - left child of p

		if ( heavyChild->echi == 1 )
			node = doubleRightRotation(node);
		else
            printf("\nRotaie dreapta la nivelul %d ",cautare_nod(root,node));
			node = rightRotation(node);
	}
	else
		if( node->echi == 2)		// // if p is a critical junction (RIGHT hanging)
		{
			heavyChild = node->right;	// heavyChild - right child of p

			if ( heavyChild->echi == -1 )
				node = doubleLeftRotation(node);
			else
                printf("\nRotaie stanga la nivelul %d ",cautare_nod(root,node));
				node = leftRotation(node);
		}

	return node;
}

//function for inserting a node
struct NodeAVL* insertAVLNode( struct NodeAVL* node, int value)
{
	if( node == NULL )
	{
		node = malloc(sizeof(struct NodeAVL));
		node->key = value;
		node->echi = 0;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	else
		if ( value < node->key )
			node->left = insertAVLNode( node->left, value );
		else
			if ( value > node->key )
				node->right = insertAVLNode( node->right, value );
			else
				printf("The key %d already exists! \n", value);

	node = balance(node);

	return node;
}

//printing function
void displayAVLTree( struct NodeAVL *node, int level )
{
    int i;
	if( node !=NULL )
	{
		displayAVLTree( node->right, level+7 );
		for(i = 0; i < level; i++ )
			printf(" ");

		printf("%d(%d) \n", node->key, node->echi);
		displayAVLTree( node->left, level+7 );
	}
}

//function for deleting a node
struct NodeAVL* deleteAVLNode( struct NodeAVL *node, int value)
{
	if (node == NULL)
	{
		printf("Can't delete key %d, it is not in AVL tree!\n", value);
		return node;
	}

	if ( value < node->key )
		node->left = deleteAVLNode(node->left, value);

	else if( value > node->key )
		node->right = deleteAVLNode(node->right, value);

	else
	{
        // node with only one child or no child
		if( (node->left == NULL) || (node->right == NULL) )
		{
			struct NodeAVL *temp;

			if( node->left != NULL )
				temp = node->left;
			else
				temp = node->right;

            // No child case
			if(temp == NULL)
				node = NULL;

			else // One child case
			{
				*node = *temp;
				free(temp);
			}
        }
		else
		{
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
			struct NodeAVL * temp = node->right;

			while (temp->left != NULL)
				temp = temp->left;

            // Copy the inorder successor's data to this node
			node->key = temp->key;

            // Delete the inorder successor
			node->right = deleteAVLNode(node->right, temp->key);
		}
	}

    // If the tree had only one node then return
    if (node != NULL)
		node = balance(node);

	return node;
}

int cautare_nod(struct NodeAVL *node, struct NodeAVL *p)
{
    return maxPathLength(node)-maxPathLength(p);
}
