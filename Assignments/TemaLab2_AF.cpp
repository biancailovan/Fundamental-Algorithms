/*
Tema Nr. 2: Analiza și Compararea a două metode de construire a structurii de date Heap: “De jos în sus” (Bottom­up) vs. “De sus în jos” (Top­down)
Varianta BOTTOM UP incepe de la dimensiunea heap-ului/2=>MAX_HEAPIFY: Input: un vector a si un indice i din vector.
La fiecare pas se determina cel mai mare element dintre:
a[i], a[Left[i]], a[Right[i]]
Daca a[i] este cel mai mare atunci subarborele avand ca radacina nodul i este un heap si procedura se termina.
Altfel, cel mai mare element este unul dintre cei doi descendenti si este interschimbat cu a[max], si se apeleaza recusiv MAX-Heapify pentru indicele max
COMPLEXITATE BOTTOM UP: pentru construct heap=> O(n);
COMPLEXITATE HEAP SORT: O(n*lgn)-ordoneaza un vector in spatiul alocat acestuia
COMPLEXITATE TOP DOWN: O(n*lgn);

Metoda de constructie TOP DOWN este mai putin eficienta decat metoda de constructie BOTTOM UP
*/


#include <iostream> 
#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"

using namespace std;

Profiler profiler("Bottom Up & Top Down construct heap");

void max_heapify(int a[], int n, int i) //Pentru varianta Bottom Up
{
	int max = i; 
	int l = 2 * i + 1; //fiul stang
	int r = 2 * i + 2; //fiul drept

	Operation asign1 = profiler.createOperation("BottomUp_asign", n);
	Operation comp1 = profiler.createOperation("BottomUp_comp", n);

	comp1.count();
	if (l < n && a[l] > a[max]) //daca copilul stang este mai mare decat radacina
		max = l;
	
	comp1.count();
	if (r < n && a[r] > a[max]) //daca copilul drept este mai mare decat cel mai mare de pana acum
		max = r;
 
	comp1.count();
	if (max != i) //in cazul in care cel mai mare nod nu este radacina
	{
		asign1.count(3);
		int aux;
		aux = a[i];
		a[i] = a[max];
		a[max] = aux;
		//asign1.count(3);

		max_heapify(a, n, max);
	}
}


void buildHeap_BottomUp(int a[], int n)
{
	int start = (n / 2) - 1;

	for (int i = start; i>=0; i--)
	{
		max_heapify(a, n, i);
	}
}

void heapSort(int a[], int n)
{
	//for (int i = n / 2 - 1; i >= 0; i--) //Echivalent cu max HEAP
		//max_heapify(a, n, i);
	buildHeap_BottomUp(a, n);

	for (int i = n - 1; i >= 0; i--) //Extrage elemente unul cate unul
	{
		//Se muta radacina la final(implicit, radaina fiind nodul care are valoarea cea mai mare)
		int aux;
		aux = a[0];
		a[0] = a[i];
		a[i] = aux;

		max_heapify(a, i, 0);
	}
}

//Varianta CORMEN dupa pseudocod
int parent(int i)
{
	return (i-1) / 2;
}

void heapIncrease_key(int a[], int i, int key,int n)
{
	Operation asign2 = profiler.createOperation("TopDown_asign", n);
	Operation comp2 = profiler.createOperation("TopDown_comp", n);
	
	asign2.count();
	a[i] = key;

	comp2.count();
	while ((i>0) && (a[parent(i)] < a[i]))
	{
		int aux;
		comp2.count();
		asign2.count(3);
		aux = a[i];
		a[i] = a[parent(i)];
		a[parent(i)] = aux;
		//asign2.count(3);
		i = parent(i);
	}

}

void buildHeap_TopDown(int a[], int n)
{
	int k=-1;
	for (int i = 0; i < n; i++)
	{
		k++;
		heapIncrease_key(a, k, a[i],n);
	}
	
}

/*void heapify_TD(int a[], int n, int i) //Pentru varianta TopDown
{
	int aux;
	int max = i;
	int parent = i / 2;

	Operation asign2 = profiler.createOperation("TopDown_asign", n);
	Operation comp2 = profiler.createOperation("TopDown_comp", n);

	if (max > 0)
	{
		comp2.count();
		if (a[max] > a[parent])
		{
			asign2.count(3);
			aux = a[max];
			a[max] = a[parent];
			a[parent] = aux;
			//asign2.count(3);

			heapify_TD(a, n, parent);
		}
	}

}

void buildHeap_TopDown(int a[], int n)
{
	for (int i = 0; i < n; i++)
		heapify_TD(a,n, i);
}*/

void printHeap(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void Average_case()
{
	int x[10000];
	int a[10000];
	int u[10000];
	int n;
	for (n = 100; n <= 10000; n = n + 500)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");
		for (int i = 0; i < 5; i++)
		{
			FillRandomArray(a, n,10,5000,false,0);
			memcpy(x, a, n * sizeof(a[0])); //pt a putea lucra pe acelasi sir
			buildHeap_BottomUp(a, n);

			//memcpy(x, a, n * sizeof(a[0]));
			buildHeap_TopDown(x, n);

		}
	}

	profiler.divideValues("BottomUp_asign", 5);
	profiler.divideValues("BottomUp_comp", 5);
	profiler.divideValues("TopDown_asign", 5);
	profiler.divideValues("TopDown_comp", 5);
	
	profiler.addSeries("BottomUp", "BottomUp_asign", "BottomUp_comp"); //asign+comp
	profiler.addSeries("TopDown", "TopDown_asign", "TopDown_comp"); //asign+comp

	profiler.createGroup("BottomUpAverage_case", "BottomUp", "BottomUp_asign", "BottomUp_comp"); //average case for BottomUp
	profiler.createGroup("TopDownAverage_case", "TopDown", "TopDown_asign", "TopDown_comp"); //average case for TopDown
	profiler.createGroup("ComparareMetode", "BottomUp", "TopDown"); //BottomUp vs TopDown

	profiler.showReport();

}

void Worst_case()
{
	int x[10000];
	int a[10000];
	int u[10000];
	int n;
	for (n = 100; n <= 10000; n = n + 500)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");

			FillRandomArray(a, n, 10, 5000, false, ASCENDING);
			memcpy(x, a, n * sizeof(a[0])); //pt a putea lucra pe acelasi sir
			buildHeap_BottomUp(a, n);

			//memcpy(x, a, n * sizeof(a[0]));
			buildHeap_TopDown(x, n);

	}


	profiler.addSeries("BottomUp", "BottomUp_asign", "BottomUp_comp"); //asign+comp
	profiler.addSeries("TopDown", "TopDown_asign", "TopDown_comp"); //asign+comp

	profiler.createGroup("BottomUpWorst_case", "BottomUp", "BottomUp_asign", "BottomUp_comp"); //worst case for BottomUp
	profiler.createGroup("TopDownWorst_case", "TopDown", "TopDown_asign", "TopDown_comp"); //worst case for TopDown
	
	profiler.createGroup("Worst_Case", "BottomUp", "TopDown");
	profiler.createGroup("Worst_Case_comparison", "TopDown_asign", "BottomUp_asign");
	profiler.createGroup("Worst_Case_asignation", "TopDown_comp","BottomUp_comp");

	profiler.showReport();
}

int main()
{
	
	int a[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	//int b[] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	int u[20];
	int n = sizeof(a) / sizeof(a[0]);
	
	//buildHeap_BottomUp(a, n);
	//printf("Bottom Up construction of the Heap:\n");
	//printHeap(a, n);

	//heapSort(a, n);
	//printf("The sorted array is:\n");
	//printHeap(a, n);

	buildHeap_TopDown(a, n);
	printf("Top Down construction of the Heap:\n");
	printHeap(a, n);

	profiler.reset("Bottom Up & Top Down construct heap");
	Average_case();
	profiler.showReport();

	profiler.reset("Bottom Up & Top Down construct heap");
	Worst_case();
	profiler.showReport();

	return 0;
}