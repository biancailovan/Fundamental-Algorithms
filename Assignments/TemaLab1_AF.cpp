/*
	Tema nr. 1: Analiza si Compararea Metodelor Directe de Sortare;
	
	BUBBLE SORT: comparatii BEST CASE: n-1; O(n)
							WORST CASE: n*(n-1)/2; O(n^2)
				asignari BEST CASE: 0; O(c)
						 WORST CASE: n*(n-1)/2; O(n^2)
	-Algoritm stabil
	-Algoritmul este adaptabil, pentru ca se adapteaza in functie de INTRAREA pe care o primeste.
	De exemplu, daca la intrare primeste un sir ordonat crescator, complexitatea lui scade, pentru ca nu face la fel de multe operatii ca pe un sir nesortat.

	INSERTION SORT: comparatii BEST CASE: n-1; O(n)
							   WORST CASE: n-1+n*(n-1)/2; O(n^2)
					asignari BEST CASE: 2*(n-1); O(n)
							 WORST CASE: 2*(n-1)+n*(n-1)/2; O(n^2)
	-Algoritm stabil
	-Algoritm adaptabil

	SELECTION SORT: comparatii BEST CASE: n*(n-1)/2; O(n^2)
							   WORST CASE: n*(n-1)/2; O(n^2)
					asignari BEST CASE: 0; O(c), unde c-const
							 WORST CASE: 3(n-1); O(n)
	-Algoritm instabil (cazul in care am in sirul meu elementul care se repeta primul si elementul minim ultimul)
	-Algoritm neadaptabil datorita faptului ca complexitatea acestuia nu se schimba in functie de intrarea pe care o primeste, ramane O(n^2) in fiecare din cele 3 cazuri

*/

#include <iostream>
#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"
#define MAX_SIZE 2000
Profiler profiler("Analiza si Compararea Metodelor Directe de Sortare");

/*void BubbleSort(int a[], int n)
{
	int i, j;
	int aux = 0;
	Operation asign0 = profiler.createOperation("BubbleSort_asign", n);
	Operation comp0 = profiler.createOperation("BubbleSort_comp", n);
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{	comp0.count();
			if (a[j] > a[j + 1])
			{
				asign0.count(3);
				aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
			}
		}
	}
}*/

//Bubble sort
void BubbleSort(int a[], int n)
{
	int sort = 0;
	int aux;
	int k = 0;
	int i;
	while (sort == 0)
	{
		sort = 1;
		Operation asign1 = profiler.createOperation("BubbleSort_asign", n);
		Operation comp1 = profiler.createOperation("BubbleSort_comp", n);
		for (i = 1; i < n - k - 1; i++)
		{
			comp1.count();
			if (a[i] > a[i + 1])
			{
				asign1.count(3);
				aux = a[i];
				a[i] = a[i + 1];
				a[i + 1] = aux;

				sort = 0;
			}
		}
		k++;
	}
}

void print_Array(int a[], int k)
{
	int i;
	for (i = 0; i < k; i++)
		printf("%d ", a[i]);
	printf("\n");
}

//Selection Sort
void SelectionSort(int a[], int n)
{
	int i, j, min;
	int aux;
	Operation asign2 = profiler.createOperation("SelectionSort_asign", n);
	Operation comp2 = profiler.createOperation("SelectionSort_comp", n);

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			comp2.count();
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			asign2.count(3);
			aux = a[i];
			a[i] = a[min];
			a[min] = aux;
		}

	}
}

//Insertion Sort
void InsertionSort(int a[], int n)
{
	int i, key, j;
	Operation asign3 = profiler.createOperation("InsertionSort_asign", n);
	Operation comp3 = profiler.createOperation("InsertionSort_comp", n);
	for (i = 0; i < n; i++)
	{
		asign3.count();
		key = a[i];
		j = i - 1;

		comp3.count();
		while (j >= 0 && a[j] > key)
		{
			asign3.count();
			a[j + 1] = a[j];
			j = j - 1;
			//comp3.count();
		}
		asign3.count();
		a[j + 1] = key;
	}
}

//La toti cei 3 algoritmi de sortare, cazul favorabil este atunci cand sirul este deja gata sortat. 
void Best_Case()
{
	int x[10000];
	int a[10000];
	int n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");
		FillRandomArray(a, n, 10, 50000, false, ASCENDING);
		memcpy(x, a, n * sizeof(a[0]));//memoreaza in vectorul x, vectorul a pentru a putea lucra pe acelasi sir de numere
		BubbleSort(a, n);
		memcpy(x, a, n * sizeof(a[0]));
		SelectionSort(a, n);
		memcpy(x, a, n * sizeof(a[0]));
		InsertionSort(a, n);
	}
	profiler.addSeries("Bubble", "BubbleSort_asign", "BubbleSort_comp");//asign+comp bubble
	profiler.addSeries("Selection", "SelectionSort_asign", "SelectionSort_comp");//asign+comp selection
	profiler.addSeries("Insertion", "InsertionSort_asign", "InsertionSort_comp");//asign+comp insertion
	profiler.createGroup("BubbleSort_Best_case", "Bubble", "BubbleSort_asign", "BubbleSort_comp");//best case bubble
	profiler.createGroup("SelectionSort_Best_case", "Selection", "SelectionSort_asign", "SelectionSort_comp");//best case selection
	profiler.createGroup("InsertionSort_Best_case", "Insertion", "InsertionSort_asign", "InsertionSort_comp");//best case insertion

	profiler.showReport();

}

//Exemplu de caz defavorabil=> Daca am sirul {3,1,2,6,4,8,7,5}=> 8 1 2 3 4 5 6 7. Pentru worst case a luat cazul cand sirul este ordonat descrescator
void Worst_Case()
{
	int x[10000];
	int a[10000];
	int n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");
		FillRandomArray(a, n, 10, 5000, false, DESCENDING);
		memcpy(x, a, n * sizeof(a[0])); //memoreaza in vectorul x, vectorul a pentru a putea lucra pe acelasi sir de numere; memcpy(sursa,destinatie,dimensiune)
		BubbleSort(a, n);
		memcpy(x, a, n * sizeof(a[0]));
		SelectionSort(a, n);
		memcpy(x, a, n * sizeof(a[0]));
		InsertionSort(a, n);
	}
	profiler.addSeries("Bubble", "BubbleSort_asign", "BubbleSort_comp"); //asign+comp bubble
	profiler.addSeries("Selection", "SelectionSort_asign", "SelectionSort_comp");//asign+comp selection
	profiler.addSeries("Insertion", "InsertionSort_asign", "InsertionSort_comp");//asign+comp insertion
	profiler.createGroup("BubbleSort_Worst_case", "Bubble", "BubbleSort_asign", "BubbleSort_comp");//grafic pt worst case bubble
	profiler.createGroup("SelectionSort_Worst_case", "Selection", "SelectionSort_asign", "SelectionSort_comp");//grafic pentru worst case selection
	profiler.createGroup("InsertionSort_Worst_case", "Insertion", "InsertionSort_asign", "InsertionSort_comp");//grafic pentru worst case insertion

	profiler.showReport();

}

//Cazul mediu statistic, asemanator cu cazul defavorabil. Aveam nevoie de 5 masuratori, dupa care, folosind functia divideValues am calculat media, impartind la 5
void Average_case()
{
	int x[10000];
	int a[10000];
	int n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("n=");
		printf("%d", n);
		printf("\n");
		for (int i = 0; i < 5; i++)
		{
			FillRandomArray(a, n, 10, 5000, false, 0);
			memcpy(x, a, n * sizeof(a[0]));
			BubbleSort(a, n);
			memcpy(x, a, n * sizeof(a[0]));
			SelectionSort(a, n);
			memcpy(x, a, n * sizeof(a[0]));
			InsertionSort(a, n);
		}
	}
	profiler.divideValues("Bubble", 5);
	profiler.divideValues("Selection", 5);
	profiler.divideValues("Insertion", 5);
	profiler.divideValues("BubbleSort_asign", 5);
	profiler.divideValues("SelectionSort_asign", 5);
	profiler.divideValues("InsertionSort_asign", 5);
	profiler.divideValues("BubbleSort_comp", 5);
	profiler.divideValues("SelectionSort_comp", 5);
	profiler.divideValues("InsertionSort_comp", 5);
	profiler.addSeries("Bubble", "BubbleSort_asign", "BubbleSort_comp");//asign+comp bubble
	profiler.addSeries("Selection", "SelectionSort_asign", "SelectionSort_comp");//asign+comp selection
	profiler.addSeries("Insertion", "InsertionSort_asign", "InsertionSort_comp");//asign+comp insertion
	profiler.createGroup("BubbleAverage_case", "Bubble", "BubbleSort_asign", "BubbleSort_comp");//average case bubble
	profiler.createGroup("SelectionAverage_case", "Selection", "SelectionSort_asign", "SelectionSort_comp");//average case selection
	profiler.createGroup("InsertionAverage_case", "Insertion", "InsertionSort_asign", "InsertionSort_comp");//average case insertion

	profiler.showReport();
}

int main()
{
	//int a[] = { 3, 1, 25, 5, 7, 11, 8 };
	int a[15];
	int n = sizeof(a) / sizeof(a[0]);
	//int n = 15;
	FillRandomArray(a, n, 1, 150, false, 0);
	print_Array(a, n);
	BubbleSort(a, n);
	//SelectionSort(a, n);
	//InsertionSort(a, n);
	printf("Sorted array is: \n");
	print_Array(a, n);
	Best_Case();
	profiler.reset("Analiza si Compararea Metodelor Directe de Sortare");
	Worst_Case();
	profiler.reset("Analiza si Compararea Metodelor Directe de Sortare");
	Average_case();
	profiler.showReport();
	return 0;
	//getchar();
}



