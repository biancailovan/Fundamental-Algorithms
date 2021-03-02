/*
	Tema nr. 7: Arbori multicai
	Am implementat pretty print pentru R1 => reprezentarea pãrinte: pentru fiecare index, 
	valoarea din vector reprezintã indexul pãrintelui.

*/

#include <iostream>

struct parentNode
{
	int value;
	int count;
	int children[15];
};

struct multiNode
{
	int value;
	int count;
	struct multiNode* child[15];
};

struct binaryNode
{
	int value;
	struct binaryNode* firstChild;
	struct binaryNode* rightBrother;
};


void prettyPrintR1(int v[], int n, int root, int level)
{
	for (int i = 1; i <=3*level; i++) //Pt spatii intre levele
	{
		printf(" ");
	}

	printf("%d", root);
	printf("\n");

	for (int i = 1; i <= n ; i++)
	{
		if (v[i] == root)
		{
			prettyPrintR1(v, n, i, level + 1);
		}

	}
	
}

int R1toR2(multiNode** r2, parentNode r1[])
{
	int root = (*r2)->value;

	if (r1[root].value != 0)
		for (int i = 0; i < r1[root].count; i++)
		{
			(*r2)->child[i] = (multiNode*)malloc(sizeof(struct multiNode));
			//(*r2)->child[i]->value = r1[root].children[i];
			R1toR2(&(*r2)->child[i], r1);
		}
	else
		return 0;
}



int main()
{
	//int v[] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 }; 
	//int n = sizeof(v) / sizeof(int);
	int v[10];
	int n = 9;

	//Citire sir
	for (int i = 1; i <= n; i++)
	{
		scanf_s("%d", &v[i]);
	}
	
	//Afisare
	prettyPrintR1(v, n, 7, 0);
	printf("\n");
	

	return 0;
}