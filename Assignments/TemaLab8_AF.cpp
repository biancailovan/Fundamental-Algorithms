// TemaLab8_AF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

typedef struct NodeT {
	int rank;
	int info;
	NodeT* parent;
} NodeT;

// Muchie intr-un graf
struct Edge
{
	NodeT* v1;
	//int v1,v2;
	NodeT* v2;
	int weight;
};

struct Edge2
{
	int src,dest;
	int weight;
};

//Structura pentru un graf
struct Graph
{
	struct NodeT** V; //vertices
	struct Edge** edge;
};

struct Graph2
{
	// V-> Number of vertices, E-> Number of edges 
	int V2, E2;
	struct Edge* edge2;

};

struct Graph2* createGraph(int V2, int E2)
{
	struct Graph2* graph = new Graph2;
	graph->V2 = V2;
	graph->E2 = E2;

	graph->edge2 = new Edge[E2];

	return graph;
}


NodeT* makeSet2(int givenInfo)
{
	NodeT* x = (NodeT*)malloc(sizeof(NodeT));
	x->parent = x;
	x->rank = 0;
	x->info = givenInfo;
	return x;
}

void makeSet(NodeT* x)
{
	x->parent = x;
	x->rank = 0;
}

void link(NodeT* x, NodeT* y)
{
	if (x->rank > y->rank)
		y->parent = x;
	else
	{
		x->parent = y;
		if (x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}

NodeT* findSet(NodeT* x)
{
	if (x != x->parent)
		x->parent = findSet(x->parent);
		return x->parent;
}

void Union(NodeT* x, NodeT* y)
{
	link(findSet(x), findSet(y));
}

int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}

int partition(Edge* a[], int low, int high, int n)
{
	Edge* pivot = a[high];

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		
		//in cazul in care elementul este mai mic decat pivotul
		if (a[j]->weight<=pivot->weight)
		{
			i++; //incrementam indexul elementului mai mic
			Edge* aux1;
			aux1 = a[i];
			a[i] = a[j];
			a[j] = aux1;

		}
	}

	Edge* aux2;
	aux2 = a[i + 1];
	a[i + 1] = a[high];
	a[high] = aux2;

	return (i + 1);
}

//Pentru sortarea muchiilor
void quickSort(Edge* a[], int low, int high,int n)
{
	if (low < high)
	{
		int pi; //indexul de partitionare al vectorului
		pi = partition(a, low, high, n);
		quickSort(a, low, pi - 1, n);
		quickSort(a, pi + 1, high, n);
	}
}

//Algoritmul lui Kruskal
//Initial sortez muchiile in functie de costul lor. Imi aleg muchia cu costul cel mai mic si verific
//tot timpul daca formeaza un ciclu sau nu, iar daca nu va forma un ciclu, aceasta va face parte din MST.
Edge** Kruskal(Graph* graph, int n)
{
	Edge** a = (Edge**)malloc(sizeof(Edge));

	for (int i = 0; i < n; i++)
		makeSet(graph->V[i]);
	
	quickSort(graph->edge, 0, n - 1, n);

	int k = 0;
	int i = 0;

	while (k < (n - 1))
	{
		Edge* nextEdge = graph->edge[i++];
		NodeT* u;
		u = findSet(nextEdge->v1);
		NodeT* v;
		v = findSet(nextEdge->v2);

		if (u != v)
		{
			a[k++] = nextEdge;
			Union(u, v);
		}
	}

	return a;

}



/*void demo()
{
	NodeT* a = new NodeT;
	NodeT* b = new NodeT;
	NodeT* c = new NodeT;
	NodeT* d = new NodeT;
	NodeT* e = new NodeT;
	NodeT* f = new NodeT;
	NodeT* g = new NodeT;
	NodeT* h = new NodeT;
	NodeT* i = new NodeT;
	NodeT* j = new NodeT;
	

	a->info = 1;
	b->info = 2;
	c->info = 3;
	d->info = 4;
	e->info = 5;
	f->info = 6;
	g->info = 7;
	h->info = 8;
	i->info = 9;


	makeSet(a);
	makeSet(b);
	makeSet(c);
	makeSet(d);
	makeSet(e);
	makeSet(f);

}*/

void demo2()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	NodeT** lista = (NodeT**)malloc(11 * sizeof(NodeT*)); 

	printf("Make set: ");
	printf("\n");


	for (int i = 0; i < 10; i++) 
	{

		lista[i] = makeSet2(a[i]);

		printf("%d, its parent: %d", lista[i]->info, findSet(lista[i])->info);
		printf("\n");

	}


	NodeT* list[10];
	
	for (int i = 0; i < 10; i++)
		list[i] = makeSet2(i);
	for (int i = 0; i < 5; i++)
		link(list[i], list[i + 5]);
	printf("\n");
	printf("Link:\n");
	printf("%d, its parent: %d", list[0]->info, findSet(list[0])->info);
	printf("\n");
	printf("%d, its parent: %d", list[1]->info, findSet(list[1])->info);
	printf("\n");
	printf("%d, its parent: %d", list[2]->info, findSet(list[2])->info);
	printf("\n");
	printf("%d, its parent: %d", list[3]->info, findSet(list[3])->info);
	printf("\n");
	printf("%d, its parent: %d", list[4]->info, findSet(list[4])->info);
	printf("\n");
	printf("%d, its parent: %d", list[5]->info, findSet(list[5])->info);
	printf("\n");
	printf("%d, its parent: %d", list[6]->info, findSet(list[6])->info);
	printf("\n");
	printf("%d, its parent: %d", list[7]->info, findSet(list[7])->info);
	printf("\n");
	printf("%d, its parent: %d", list[8]->info, findSet(list[8])->info);
	printf("\n");
	printf("%d, its parent: %d", list[9]->info, findSet(list[9])->info);
	printf("\n");


	Union(list[1], list[7]);
	Union(list[4], list[5]);
	Union(list[3], list[6]);

	printf("\n");
	printf("Union:\n");
	printf("The biggest element after union & findSet(list[1]): ");
	printf("%d", findSet(list[1])->info);
	printf("\n");
	//printf("The biggest element after findSet(list[4]): ");
	//printf("%d", findSet(list[4])->info);
	//printf("\n");
		
}

NodeT* createNode(int info)
{
	NodeT* x = (NodeT*)malloc(sizeof(NodeT));
	x->info = info;
	x->rank = 0;
	x->parent = NULL;
	return x;
}

Edge* makeEdge(NodeT* v1, NodeT* v2, int weight)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = v1;
	e->v2 = v2;
	e->weight = weight;

	return e;
}

void demoKruskal()
{
	Graph* G = NULL;
	Edge** rez = NULL;
	int V2 = 4;  // Number of vertices in graph 
	int E2 = 5;  // Number of edges in graph 
	//struct Graph2* graph = createGraph(V2, E2);

	G = (Graph*)malloc(sizeof(Graph));
	G->V = (NodeT**)malloc(10 * sizeof(NodeT*));
	G->edge = (Edge**)malloc(40 * sizeof(Edge*));

	G->edge[1] = makeEdge(G->V[1], G->V[2], 8);
	G->edge[2] = makeEdge(G->V[2], G->V[3], 7);
	G->edge[3] = makeEdge(G->V[3], G->V[4], 9);
	G->edge[4] = makeEdge(G->V[4], G->V[5], 10);
	G->edge[5] = makeEdge(G->V[5], G->V[6], 2);
	G->edge[6] = makeEdge(G->V[6], G->V[7], 1);
	G->edge[7] = makeEdge(G->V[7], G->V[8], 7);
	

	rez = Kruskal(G, 10);
	printf("The MST is:\n");
	for (int i = 0; i < 9; i++)
		printf("v1 = %d, v2 = %d, weight = %d\n", rez[i]->v1->info, rez[i]->v2->info, rez[i]->weight);
	

}


int main()
{
	//demo();
	//demo2();
	//demo();


	demo2();
	//demoKruskal();
	//demoK();
	
}