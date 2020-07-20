// Phong Nguyenho - ph094398

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

int isReflection(node *a, node *b)
{
	if (a == NULL && b == NULL)
		return 1;
	if (a == NULL || b == NULL)
		return 0;

	// If the tree data are equal return 1 * 1 = 1
	// If the tree data are not equal return 0 * whatever = 0
	return (a->data == b->data) ? (isReflection(a->left, b->right) * isReflection(a->right, b->left)) : 0;
}

node *makeReflection(node *root)
{
	if (root == NULL)
		return NULL;

	node *root2 = malloc(sizeof(node));
	if (root2 == NULL)
		return NULL;

	// Inserts nodes in the respective opposite side of the subtrees
	root2->data = root->data;
	root2->left = makeReflection(root->right);
	root2->right = makeReflection(root->left);

	// Returns newly created reflected tree
	return root2;
}

int kindredSpirits(node *a, node *b)
{
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	else if (a == NULL || b == NULL)
	{
		return 0;
	}

	// Checks if the first trees preorder is equal to second trees postorder
	// If not then checks if the second trees preorder is equal to the first trees postorder
	if (a->data == b->data)
	{
		return (kindredSpirits(a->left, b->right)) || (kindredSpirits(a->right, b->left));
	}
	else
		return (kindredSpirits(a, b->left) + kindredSpirits(a, b->right)) || 
		(kindredSpirits(a->left, b) + kindredSpirits(a->right, b));
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 90.0;
}