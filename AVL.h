#include<stdio.h>
#include<stdlib.h>

typedef struct NodeAVL{
	int key;
	int echi;
	struct NodeAVL *left, *right;
};
struct NodeAVL *root;
int max( int a, int b);
int maxPathLength(struct NodeAVL *p);
void computeBalanceFactor (struct NodeAVL *p);
struct NodeAVL* leftRot (struct NodeAVL *p);
struct NodeAVL* rightRot (struct NodeAVL *p);
struct NodeAVL* doubleLeftRot (struct NodeAVL *p);
struct NodeAVL* doubleRightRot (struct NodeAVL *p);
struct NodeAVL* balance (struct NodeAVL *p);
struct NodeAVL* insertAVLNode (struct NodeAVL *p, int x);
struct NodeAVL* deleteAVLNode (struct NodeAVL *p, int x);
void displayAVLTree (struct NodeAVL *p, int level);
int cautare_nod(struct NodeAVL *node, struct NodeAVL *p);
