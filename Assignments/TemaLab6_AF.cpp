// TemaLab6_AF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Tema nr. 6: Statistici dinamice de ordine

Am implementat -algoritmul de construire al unui arbore PBT(perfect balanced tree)
			   - OS select: cauta al i-lea cel mai mic element
			   - OS delete: stergerea unui nod

*/

#include <iostream>
#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"

Profiler profiler("Tema laborator 6");

//Structura unui nod
typedef struct NodeT {
	int key;
	struct NodeT* left;
	struct NodeT* right;
	int size;
	int height;
} NodeT;

//Nod nou
NodeT* newNode(int key, int size)
{
	NodeT* temp = (NodeT*)malloc(sizeof(NodeT));

	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	temp->size = size;

	return temp;

}

//Size-ul unui nod(rang-ul)
int size(NodeT* x)
{
	if (x != NULL)
		return x->size;
	else
		return 0;
}

//Inaltime
int height(struct NodeT* x)
{
	if (x == NULL)
		return 0;
	return x->height;
}

//Inserare nod
NodeT* insertNode(NodeT* root, int key, int size) 
{
	if (root == NULL)
		return newNode(key, size);
	else if (root->key == key)
		return root;
	if (root->key < key)
		root->right = insertNode(root->right, key, size);
	else if (root->key > key) root->left = insertNode(root->left, key, size);
	return root;

}

//Construire arbore PBT(Perfect Balanced Tree)
NodeT* buildTreePBT(int a[], int low, int high)
{
	if (low > high)
	{
		return NULL;
	}

	else
	{
		int mid = (low + high) / 2;

		NodeT* root = newNode(a[mid], high - low + 1);
		root->left = buildTreePBT(a, low, mid - 1);
		root->right = buildTreePBT(a, mid + 1, high);
		return root;

	}
}

//Afisare preordine: radacina, stanga dreapta
void printPreOrder(NodeT* root)
{
	if (root == NULL)
	{
		return;
	}

	printf("\n(Node: %d->its size: %d)", root->key, root->size);
	printPreOrder(root->left);
	printPreOrder(root->right);

}

//Afisare inordine: stanga, radacina, dreapta
void printInOrder(NodeT* root) 
{
	if (root != NULL)
	{
		printInOrder(root->left);
		printf("Node:%d, its size: %d)\n", root->key, root->size);
		printInOrder(root->right);
	}

}

void prettyPrint(NodeT* root, int n)
{
	if (root != NULL)
	{
		prettyPrint(root->right, n + 1);

		for (int i = 0; i < n; i++)
			printf("\t");
		printf("(%d; %d)\n", root->key, root->size);
		prettyPrint(root->left, n + 1);
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			printf("\t");
		}
		
	}
}

//Al i-lea cel mai mic element
NodeT* OS_select(NodeT* x, int i, int n)
{
	Operation op1 = profiler.createOperation("OS_Select", n);

	op1.count();
	int rank = size(x->left) + 1;

	op1.count();
	if (i == rank)
	{
		return x;
	}
	else
		op1.count(2);
		if (i < rank)
		{
			return OS_select(x->left, i, n);
		}
		else
		{
			return OS_select(x->right, i - rank, n);
		}

}

//Gasirea minimului
NodeT* findMin(NodeT* root) 
{
	if (root->left == NULL)
		return root;
	return findMin(root->left);
}

//Stergerea unui nod
NodeT* OS_delete(NodeT* root, int key, int n) 
{
	Operation op2 = profiler.createOperation("OS_Delete", n);
	
	NodeT* p;

	op2.count();
	if (root == NULL) 
		return root;
	op2.count();
	if (key < root->key)
		root->left = OS_delete(root->left, key, n);

	else
		op2.count();
		if (key > root->key)
			root->right = OS_delete(root->right, key, n);

		else
		{
			op2.count();
			if (root->left == NULL)
			{
				op2.count();
				p = root->right;
				//free(root);
				return p;

			}
			else
				op2.count();
				if (root->right == NULL)
				{
					op2.count();
					p = root->left;
					free(root);
					return p;

				}

			op2.count(3);
			p = findMin(root->right);
			root->key = p->key;
			root->right = OS_delete(root->right, p->key, n);
		}
		/*p = findMin(root->right);
		root->key = p->key;
		root->right = OS_delete(root->right, p->key);*/
	
	root->size--;
	return root;
}

//Cazul mediu statistic
void Average_case()
{
	int x[10000];
	int a[10000];
	int n;
	int key;
	for (n = 100; n <= 10000; n = n + 500)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");
		for (int i = 0; i < 5; i++)
		{
			FillRandomArray(a, n, 1, n-1, false, ASCENDING);
			memcpy(x, a, n);

			NodeT* root1;
			NodeT* root2;
			root1 = buildTreePBT(a, 0, n - 1);
			root2 = buildTreePBT(a, 0, n - 1);

			for (int m = 0; m <= 99; m++)
			{
				NodeT* f;
				NodeT* g;
				f = OS_select(root1, a[m], n);
				g = OS_delete(root2, a[m], n);
			}

		}
	}

	profiler.divideValues("OS_Select", 5);
	profiler.divideValues("OS_Delete", 5);

	profiler.createGroup("Average case", "OS_Select", "OS_delete");

	profiler.showReport();
	
}

int main()
{

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int n = sizeof(a) / sizeof(a[0]);
	NodeT* x;

	NodeT* root = buildTreePBT(a, 0, n - 1);

	printf("\nPreorder listing for constructed PBT:\n");
	printPreOrder(root);

	printf("\nPretty print:\n");
	prettyPrint(root, n);

	printf("\nOS_Select=>\n");
	for (int i = 1; i <= 3; i++)
	{
		int ind = rand() % (n+1);
	    x = OS_select(root, ind, n);
		printf("\nNode %d its the: %d node\n", ind, x->key);
	}

	//int key = 6;
	int key = rand() % (n + 1);
	printf("\n");
	printf("\nNode to be deleted: %d\n", key);
	root = OS_delete(root, key, n);
	printInOrder(root);

	Average_case();
	
	return 0;

}
