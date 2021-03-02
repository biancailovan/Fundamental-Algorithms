// TemaBFS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
	Tema nr 9: BFS.
	Am implementat algoritmul BFS, demo pt acesta si pretty print.
*/

#include <iostream>
#include <stdio.h>
#include "C:\\Users\\bianc\\Desktop\\Facultate\\An2\\AF\\lab_bfs\Profiler.h"
#define INFINITE 99999
#define CAPACITY 30

Profiler profiler("Tema BFS");

//Structura nod
typedef struct NodeT {
	int key;
	struct NodeT* next;
}NodeT;

NodeT* v[INFINITE];

enum { White, Gray, Black } color;

//Structura graf
typedef struct Graph {
	int v; //nr vf
	int* color;
	NodeT** lists;
	int* parent;
	int* distance;

}Graph;

//Structura coada
struct queue
{
	int array[CAPACITY];
	int nrElemente;
	int head;
	int tail;

};

void initializeaza(struct queue* myQueue)
{
	myQueue->nrElemente = 0;
	myQueue->head = 0;
	myQueue->tail = 0;
}

int goala(struct queue myQueue)
{
	if (myQueue.nrElemente == 0)
		return 1;
	return 0;
}

NodeT* newNode(int givenkey)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = givenkey;
	p->next = NULL;
	return p;
}

//Creare graf
Graph* newGraph(int v)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->v = v;
	graph->parent = (int*)malloc(v*sizeof(int));
	graph->distance = (int*)malloc(v*sizeof(int));
	graph->color = (int*)malloc(v*sizeof(int));
	graph->lists = (NodeT**)malloc(v*sizeof(NodeT*));

	return graph;
}

void enqueue(NodeT** first, NodeT** last, int key)
{
	NodeT* p = newNode(key);
	if ((*first) == NULL)
	{
		(*first) = p;
		(*last) = p;
	}
	else
	{
		if ((*last) != NULL)
		{
			(*last)->next = p;
			(*last) = p;
		}
	}
}

int dequeue(NodeT** first, NodeT** last)
{
	NodeT* aux = (NodeT*)malloc(sizeof(NodeT));
	int k;

	if ((*first) != NULL)
	{
		aux = (*first);
		(*first) = (*first)->next;
		k = aux->key;
		free(aux);
	}
	return k;
}

void printList(NodeT* first)
{
	while (first != NULL)
	{
		printf("%d ", first->key);
		first = first->next;
	}
	printf("\n");
}

void insertFirst(NodeT** first, int key)
{
	NodeT* p = newNode(key);
	if ((*first) == NULL)
	{
		(*first) = p;
	}
	else
	{
		p->next = (*first);
		(*first) = p;
	}
}


void BFS(Graph* G, int nodeSource, int n)
{
	//initializare
	NodeT* first = NULL;
	NodeT* last = NULL;

	Operation op = profiler.createOperation("OperatiiBFS", n);

	int* vizitate; //pt noduri vizitate
	vizitate = (int*)malloc((G->v)*sizeof(int));
	int k = 0; //pt vect de noduri vizitate

	op.count(3);
	G->color[nodeSource] = Gray; //nodul sursa se considera a fi descoperit
	G->parent[nodeSource] = -1;
	G->distance[nodeSource] = 0;

	enqueue(&first, &last, nodeSource); //pun in coada nodul sursa

	while (first != NULL)
	{
		int Q = dequeue(&first, &last);
		//Parcurg vecinii nodului curent
		printf("%d ", Q);
		vizitate[k++] = Q;
		NodeT* p = G->lists[Q];
		while (p != NULL)
		{
			//daca nodul este alb, el nu a fost inca descoperit, alg il descopera in liniile urmatoare
			op.count();

			if (G->color[p->key] == White)
			{
				G->color[p->key] = Gray; //la inceput este colorat cu gri
				G->parent[p->key] = Q;
				G->distance[p->key] = G->distance[Q] + 1;

				op.count(3);
				enqueue(&first, &last, p->key); //in final este plasat la finalul cozii

			}
			p = p->next; //trec la urmatorul

		}
		//dupa ce am verificat toate vf din lista de adiacenta a nodului curent, il coloram negru
		G->color[Q] = Black;
		op.count();

	}

}

void bfs2(int source, int n, int* vizitate, NodeT* a[], int* b)
{
	int i, v;
	NodeT* first = NULL;
	NodeT* last = NULL;

	for (i = 0; i < n; i++)
		vizitate[i] = White;
	enqueue(&first, &last, source);
	vizitate[source] = Black;

	printf("\nParcurgere BFS: ");
	printf("%d ", source);
	b[source] = -1;

	while (first != NULL)
	{

		v = dequeue(&first, &last);
		while (a[v] != NULL)
		{

			if (vizitate[a[v]->key] == White)
			{
				b[a[v]->key] = v;
				vizitate[a[v]->key] = Black;
				printf("%d ", a[v]->key);

				enqueue(&first, &last, a[v]->key);
			}

			a[v] = a[v]->next;
		}
	}

}


void readGraph(Graph* G, int nr)
{
	G->v = nr;
	G->lists = (NodeT**)calloc(G->v, sizeof(NodeT*));

	for (int i = 0; i < nr; i++)
	{
		G->lists[i] = NULL;

		int a, b; //(a, b) - muchie
		printf("a=");
		scanf_s("%d", &a);
		printf("b=");
		scanf_s("%d", &b);

		insertFirst(&G->lists[a], b);
		insertFirst(&G->lists[b], a);

	}

	for (int i = 0; i < G->v; i++)
	{
		G->color[i] = White;
		G->parent[i] = -1;
		G->distance[i] = 0;

	}

}

void showAdj(NodeT* v[], int n)
{
	int i = 0;
	printf("\nLista de adiacenta:\n");

	while (i < n)
	{
		printf("%d: ", i);
		printList(v[i]);
		i++;
	}
}

void prettyprint(int root, int level, int n, int v[])
{

	int i, j;
	for (i = 0; i < n; i++)
	{
		if (v[i] == root)
		{
			for (j = 0; j < level; j++)
				printf(" ");
			printf("%d", i);
			printf("\n");

			prettyprint(i, level + 2, n, v);
		}
	}

}

void checkBFS()
{
	int* viz;
	int k = 5, m = 7, * a, i;
	viz = (int*)malloc(sizeof(int) * k);
	a = (int*)malloc(sizeof(int) * k);

	int n = 7;
	Graph* G = newGraph(n);
	readGraph(G, n);

	int nodeSource=3;
	printf("\nNodul sursa ales este: %d\n ", nodeSource);

	int* vizitate = (int*)malloc((G->v)* sizeof(int)); //vector de noduri vizitate

	printf("\nParcurgere BFS:\n");
	BFS(G, nodeSource, n);

	for (int i = 0; i < G->v; i++)
	{
		if (G->color[i] == White)
		{
			BFS(G, i, n);
		}
	}

}


void demo()
{
	int n = 7, m = 7, i;
	int root = 0;

	int *vizitate = (int*)malloc(sizeof(int) * n);
	int *a = (int*)malloc(sizeof(int) * n);

	//Verificare BFS
	checkBFS();

	//Pt a vedea lista de adiacenta
	insertFirst(&v[0], 1);
	insertFirst(&v[1], 0);

	insertFirst(&v[0], 2);
	insertFirst(&v[2], 0);

	insertFirst(&v[0], 3);
	insertFirst(&v[3], 0);

	insertFirst(&v[1], 3);
	insertFirst(&v[3], 1);

	insertFirst(&v[2], 5);
	insertFirst(&v[5], 2);

	insertFirst(&v[5], 4);
	insertFirst(&v[4], 5);

	insertFirst(&v[5], 6);
	insertFirst(&v[6], 5);

	printf("\n");
	//Lista de adiacenta
	showAdj(v, n);

	bfs2(3, n, vizitate, v, a);


	for (i = 0; i < n; i++)
	{
		if (a[i] == -1)
		{
			root = i;
			break;
		}
	}

	printf("\n");
	printf("\n");

	printf("Pretty print:\n");

	printf("%d", root);

	printf("\n");
	prettyprint(root, 2, n, a);

}

int main()
{
	demo();
	return 0;
}