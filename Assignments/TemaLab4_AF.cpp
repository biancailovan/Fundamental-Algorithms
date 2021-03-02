// TemaLab4_AF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Tema nr. 4: Interclasarea eficienta a k siruri/liste ordonate

Algoritmul implementat: MergeKLists(interclasarea a k liste ordonate de n elemente), complexitate O(nlogk)

Algoritmul genereaza un array de k liste simplu inlantuite si ordonate. Ne asiguram la fiecare pas, inainte
de a extrage un element din array-ul de liste ca este cel mai mic element (min heap) ca mai pe urma sa-l
inseram in lista finala sortata. 
Algoritmul de min_heapify ne ajuta sa avem in varful heap-ului cel mai mic element ca mai pe urma sa-l putem 
insera in lista finala care va fi sortata. De fiecare data cand vom extrage elementul minim si il vom adauga
in lista sortata, dimensiunea heap-ului va trebui micsorata.

Algoritmul este implementat cu liste simplu inlantuite si cu structura de HEAP.
*/

#include <iostream>
#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"

using namespace std;

Profiler profiler("MergeSort K Lists");

typedef struct node 
{
	int key;
	struct node* next;
} NodeT;

typedef struct ListT
{
	NodeT* first;
	NodeT* last;
	int size;
}ListT;

NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));

	n->next = NULL;
	n->key = key;

	return n;
}

ListT* createList()
{
	ListT* list = (ListT*)malloc(sizeof(ListT));

	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

ListT** createArrayList(int k)
{
	ListT** a = (ListT**)malloc(k * sizeof(ListT*));

	for (int i = 0; i < k; i++)
	{
		a[i] = createList();
	}
	return a;
}

void push(ListT* list, int key) 
{
	NodeT* p = createNode(key);

	if (list->last == NULL)
	{
		list->first = list->last = p;
	}
	else
	{
		list->last->next = p;
		list->last = p;
	}
	list->size++;
}

int pop(ListT* list) 
{
	int aux;
	NodeT* k = list->first;

	if (k == NULL)
		return NULL;
	if (k == list->last)
	{
		list->first = list->last = NULL;
	}
	if (k->next == list->last)
	{
		list->first = list->last;
	}
	else
	{
		list->first = list->first->next;
	}

	list->size--;
	aux = k->key;
	return aux;
}

//Array de liste
//Am alocat dinamic un vector ca sa pot sa folosesc FillRandomArray pentru ca am nevoie sa generez o lista aleatoare, nu un vector aleator
//Parcurgere vector + push de fiecare element din listele respective
ListT** generateKLists(int n, int k)
{
	ListT** Array = createArrayList(k); //Array => vectorul de liste
	int* v = (int*)malloc((n / k + 1) * sizeof(int)); 

	for (int i = 0; i < k; i++)
		//Daca n nu se imparte exact la k atunci primele n mod k elemente sa aiba un element in plus=>
		//generez un vector aleator de lungime n/k+1, iar altfel generez doar un vector aleator de lungime n/k.
		if (i < n % k)
		{
			FillRandomArray(v, n / k + 1, 1, 300, false, ASCENDING);
			for (int p = 0; p < n / k + 1; p++) 
				push(Array[i], v[p]); //Array[i] => lista cu nr i
		}
		else
		{
			FillRandomArray(v, n / k, 1, 300, false, ASCENDING);
			for (int q = 0; q < n / k; q++)
				push(Array[i], v[q]);
		}
	return Array;
}

void delete_first(NodeT** head, NodeT** tail)
{
	NodeT* p;
	p = (NodeT*)malloc(sizeof(NodeT));

	if (*head != NULL)
	{
		p = *head;
		*head = (*head)->next;
		free(p);
		if (*head == NULL)
			*tail = NULL;
	}

}

void insert_first(NodeT** head, NodeT** tail, int givenKey) 
{

	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = givenKey;
	p->next = NULL;

	if (*head != NULL)
	{
		p->next = *head;
		*head = p;
	}
	else 
	{ 
		*head = p; 
		*tail = p; 
	}

}

void insert_last(NodeT** head, NodeT** tail, int givenKey)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = givenKey;
	p->next = NULL;

	if (*tail != NULL)
	{
		(*tail)->next = p;
		*tail = p;
	}
}


void printList(ListT* list)
{
	NodeT* k = list->first;

	while (k != NULL)
	{
		printf("%d ", k->key);
		k = k->next;
	}
}

void min_heapify(ListT* a[], int n, int i) 
{
	int min = i;
	int l = 2 * i + 1; //fiul stang
	int r = 2 * i + 2; //fiul drept

	if (l < n && a[l]->first->key < a[min]->first->key) //daca copilul stang este mai mic decat radacina
		min = l;

	if (r < n && a[r]->first->key < a[min]->first->key) //daca copilul drept este mai mic decat cel mai mic de pana acum
		min = r;

	if (min != i) //in cazul in care cel mai mic nod nu este radacina
	{
		ListT* aux;
		aux = a[i];
		a[i] = a[min];
		a[min] = aux;

		min_heapify(a, n, min);
	}
}

//Construire Heap cu Bottom Up
void buildHeap_BottomUp(ListT* a[], int n)
{
	int start = (n / 2) - 1;

	for (int i = start; i >= 0; i--)
	{
		min_heapify(a, n, i);
	}
}

void printHeap(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

//Algoritmul pentru interclasarea a K liste sortate de n elemente
void MergeKLists(ListT** List, ListT* Lout, int k)
{
	int heapsize = k;
	buildHeap_BottomUp(List, k);

	while (heapsize > 0)
	{
		int key = pop(List[0]);
		push(Lout, key);

		if (List[0]->first == NULL)
		{
			ListT* aux;
			aux = List[0];
			List[0] = List[heapsize-1];
			List[heapsize-1] = aux;
			heapsize--;
		}

		if (heapsize > 0)
		{
			min_heapify(List, heapsize, 0);
		}

	}
}

int main()
{
	//ListT** List;
	//int r = 20;
	//int b[] = { 5,6,7,2,4,9,13,11 };

	//buildHeap_BottomUp(List, r);
	//printf("Bottom Up construction of the Heap:\n");
	//printHeap(b, r);

	//Cazul in care n nu se imparte exact la k
	int n = 16;
	int k = 5;
	ListT** List = generateKLists(n, k);

	printf("After generating K Lists, K sorrted lists to be sorrted in one list are: ");
	printf("\n");
	for (int i = 0; i < k; i++)
	{
		printList(List[i]);
		printf("\n");
	}
	printf("\n");

	ListT* Lout = createList();

	MergeKLists(List, Lout, k);
	
	printf("Sorrted List after MergeKLists is: ");
	printList(Lout);
	printf("\n");

	return 0;
}



