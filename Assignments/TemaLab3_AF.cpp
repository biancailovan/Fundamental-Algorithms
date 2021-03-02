#include <iostream>
#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"
/*
TEMA NR. 3: Analiza și compararea metodelor avansate de sortare – HeapSort și QuickSort

Algoritmi implementati: QuickSort, QuickSelect, HeapSort

QUICKSORT este o metoda de sortare care se bazeaza pe Divide et Impera. Ideea de baza a algoritmului: se alege un element ca pivot, dupa care compar fiecare element al sirului meu initial cu acesta.
Daca elementul este mai mic decat pivotul meu ales, acesta va fi pozitionat in partea stanga, altfel va fi pozitionat in dreapta. Este vorba despre partitionarea sirului, care va fi apelata recursiv pana in momentul in care sirul va fi ordonat complet

COMPLEXITATE QUICKSORT: *Average case: am considerat un sir nesortat ca input, pivotul fiind ales pe ultima pozitie. Complexitatea in acest caz este O(n*logn)
						*Worst case: se poate considera fie un sir sortat crescator, fie unul sortat descrescator. Complexitatea in acest caz este O(n^2)
						*Best case: sir nesortat, ales random, pivotul fiind considerat la jumatatea sirului. Complexitatea este aceeasi ca si in cazul mediu statistic, O(n*logn)
Folosind implementarea QUICKSORT cu random partition, pentru nicio intrare nu vom avea comportarea cea mai defavorabila.
QUICKSELECT este o procedura ce va afisa cel mai mic k element din sirul meu; valoarea lui k va fi precizata.

COMPLEXITATE HEAPSORT: O(n*logn)

Daca ar fi sa observam din grafic diferentele dintre cele 2 metode de sortare in cazul mediu statistic, 
se poate observa ca HeapSort este mai ineficient decat QuickSort, QuickSort avand un domeniu mult mai mic in comparatie cu acesta.
Avantaje QuickSort:
-Un avantaj la QuickSort in spre deosebire de HeapSort este ca elementele deja ordonate nu vor mai fi interschimbate.
-Un alt avantaj poate fi faptul ca sorteaza pe loc in spatiul alocat acestuia;nu are nevoie de spatiu aditional de memorie
*/

Profiler profiler("QuickSort vs HeapSort");

int partition(int a[], int low, int high, int n)
{
	
	Operation asign1 = profiler.createOperation("QuickSort_asign", n);
	Operation comp1 = profiler.createOperation("QuickSort_comp", n);

	asign1.count();
	int pivot = a[high];

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{

		comp1.count();
		//in cazul in care elementul este mai mic decat pivotul
		if (a[j] < pivot)
		{
			asign1.count(3);
			i++; //incrementam indexul elementului mai mic
			int aux1;
			aux1 = a[i];
			a[i] = a[j];
			a[j] = aux1;

		}
	}

	asign1.count(3);
	int aux2;
	aux2 = a[i + 1];
	a[i + 1] = a[high];
	a[high] = aux2;

	return (i + 1);
}

int partitionRand(int a[], int low, int high,int n)
{
	//genereaza un numar random din intervalul(low, high)
	srand(time(NULL));
	int random = low + rand() % (high - low);

	Operation asign = profiler.createOperation("QuickSortRand_asign", n);
	Operation comp = profiler.createOperation("QuickSortRand_comp", n);

	asign.count(3);
	int aux;
	aux = a[random];
	a[random] = a[high];
	a[high] = aux;

	return partition(a, low, high, n);
}

void quickSort(int a[], int low, int high, int n)
{
	if (low < high)
	{
		int pi; //indexul de partitionare al vectorului
		pi = partition(a, low, high, n);
		quickSort(a, low, pi - 1, n);  
		quickSort(a, pi + 1, high, n); 
	}
}

//Metoda pentru a gasi al k-lea cel mai mic element din sir
int quickSelect(int a[], int low, int high, int i, int n)
{
	if (low == high)
		return a[low];
	int q = partitionRand(a, low, high,n); //partitioneaza sirul in 2 parti
	int k = q - low + 1; //nr k de elemente in partea stanga
	if (i == k) //se verifica daca pivotul e k cel mai mic element
		return a[q]; //pivot
	if (i < k) //se verifica in care din cele 2 partitii am elementul meu
	{
		return quickSelect(a, low, q - 1, i,n); 
	}
	else return quickSelect(a, q + 1, high, i - k,n);
}

//QuickSort cu pivot ales random
//La fiecare pas al sortarii, inainte de partitionarea vectorului, interschimbam elementul A[low] cu un element ales aleator din vectorul A[low]...A[high].
//Se asigura ca elementul pivot sa fie, cu aceeasi probabilitate, orice element dintre cele high - low + 1 elemente ale vectorului.
void quickSortRand(int a[], int low, int high, int n)
{
	if (low < high)
	{
		//pi repezinta indexul de partitionare a vectorului 
		int pi = partitionRand(a, low, high, n);
		quickSortRand(a, low, pi - 1, n);
		quickSortRand(a, pi + 1, high, n);
	}
}

//Heap Sort
void max_heapify(int a[], int n, int i) 
{
	int max = i;
	int l = 2 * i + 1; //fiul stang
	int r = 2 * i + 2; //fiul drept

	Operation asign2 = profiler.createOperation("MaxHeap_asign", n);
	Operation comp2 = profiler.createOperation("MaxHeap_comp", n);

	comp2.count();
	if (l < n && a[l] > a[max]) //daca copilul stang este mai mare decat radacina
		max = l;

	comp2.count();
	if (r < n && a[r] > a[max]) //daca copilul drept este mai mare decat cel mai mare de pana acum
		max = r;

	//comp2.count();
	if (max != i) //in cazul in care cel mai mare nod nu este radacina
	{
		asign2.count(3);
		int aux;
		aux = a[i];
		a[i] = a[max];
		a[max] = aux;

		max_heapify(a, n, max);

	}
}

void buildHeap_BottomUp(int a[], int n)
{
	int start = (n / 2) - 1;

	for (int i = start; i >= 0; i--)
	{
		max_heapify(a, n, i);
	}
}

void heapSort(int a[], int n)
{
	Operation asign3 = profiler.createOperation("HeapSort_asign", n);
	Operation comp3 = profiler.createOperation("HeapSort_comp", n);
	
	//for (int i = n / 2 - 1; i >= 0; i--) //echivalent buildHeap_BottomUp
		//max_heapify(a, n, i);
	buildHeap_BottomUp(a, n);

	for (int i = n - 1; i >= 0; i--) //Extrage elemente unul cate unul
	{
		//Se muta radacina la final(implicit, radaina fiind nodul care are valoarea cea mai mare)
		asign3.count(3);
		int aux;
		aux = a[0];
		a[0] = a[i];
		a[i] = aux;

		max_heapify(a, n, 0);
		//max_heapify(a,i,0);
	}
}

void printArray(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
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
			FillRandomArray(a, n, 10, 5000, false, 0);
			memcpy(x, a, n * sizeof(a[0])); //pt a putea lucra pe acelasi sir
			heapSort(a, n);

			//memcpy(x, a, n * sizeof(a[0]));
			quickSort(x,0, n-1,n);

		}
	}

	profiler.divideValues("QuickSort_asign", 5);
	profiler.divideValues("QuickSort_comp", 5);
	profiler.divideValues("HeapSort_asign", 5);
	profiler.divideValues("HeapSort_comp", 5);
	profiler.divideValues("MaxHeap_asign", 5);
	profiler.divideValues("MaxHeap_comp", 5);

	profiler.addSeries("HeapSortAsign", "HeapSort_asign","MaxHeap_asign"); //asignari pentru HeapSort
	profiler.addSeries("HeapSortComp", "HeapSort_comp", "MaxHeap_comp"); //comparatii pentru HeapSort
	profiler.addSeries("HeapSort", "HeapSortAsign", "HeapSortComp"); //asign+comp pentru HeapSort
	profiler.addSeries("QuickSort", "QuickSort_asign", "QuickSort_comp"); //asign+comp pentru quicksort

	profiler.createGroup("HeapSortAverage_case", "HeapSort", "HeapSortAsign", "HeapSortComp"); //grafic average pentru HeapSort
	profiler.createGroup("QuickSortAverage_case", "QuickSort", "QuickSort_asign", "QuickSort_comp"); //grafic average pentru QuickSort
	profiler.createGroup("Average_Case", "QuickSort", "HeapSort"); //grafic pentru compararea celor 2 metode de sortare in cazul mediu statistic

	profiler.showReport();

}

void Average_case1()
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
			FillRandomArray(a, n, 10, 5000, false, 0);
			memcpy(x, a, n * sizeof(a[0])); //pt a putea lucra pe acelasi sir
			heapSort(a, n);

			memcpy(x, a, n * sizeof(a[0]));
			quickSortRand(a, 0, n, n);

		}
	}

	profiler.divideValues("QuickSortRand_asign", 5);
	profiler.divideValues("QuickSortRand_comp", 5);
	profiler.divideValues("HeapSort_asign", 5);
	profiler.divideValues("HeapSort_comp", 5);
	profiler.divideValues("MaxHeap_asign", 5);
	profiler.divideValues("MaxHeap_comp", 5);

	profiler.addSeries("HeapSortAsign", "HeapSort_asign", "MaxHeap_asign"); //asignari pentru HeapSort
	profiler.addSeries("HeapSortComp", "HeapSort_comp", "MaxHeap_comp"); //comparatii pentru HeapSort
	profiler.addSeries("HeapSort", "HeapSortAsign", "HeapSortComp"); //asign+comp pentru HeapSort
	profiler.addSeries("QuickSortRand_Asign", "QuickSortRand_asign", "QuickSort_asign"); //asign+comp pentru quicksort
	profiler.addSeries("QuickSortRand_Comp", "QuickSortRand_comp", "QuickSort_comp");
	profiler.addSeries("QuickSortRand", "QuickSortRand_Asign", "QuickSortRand_Comp");

	profiler.createGroup("HeapSortAverage_case", "HeapSort", "HeapSortAsign", "HeapSortComp"); //grafic average pentru HeapSort
	profiler.createGroup("QuickSortRandAverage_case", "QuickSortRand", "QuickSortRand_Asign", "QuickSortRand_Comp"); //grafic average pentru QuickSort
	profiler.createGroup("Average_Case_Rand", "QuickSortRand", "HeapSort"); //grafic pentru compararea celor 2 metode de sortare in cazul mediu statistic

	profiler.showReport();

}

void Best_case()
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

			FillRandomArray(a, n, 10, 5000, false, 0); //am considerat pentru Best Case un sir nesortat
			memcpy(x, a, n * sizeof(a[0])); 
			quickSort(a, 0, n/2, n); //pivotul sa fie la jum sirului

	}
	
	profiler.addSeries("QuickSort", "QuickSort_asign", "QuickSort_comp"); //asign+comp QuickSort
	profiler.createGroup("QuickSortBest_case", "QuickSort", "QuickSort_asign", "QuickSort_comp"); //grafic Best Case pentru Quicksort

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

		FillRandomArray(a, n, 10, 5000, false, ASCENDING); //am considerat pentru cazul cel mai defavorabil un sir ordonat
		memcpy(x, a, n * sizeof(a[0])); 
		quickSort(a, 0, n - 1, n);

	}

	profiler.addSeries("QuickSort", "QuickSort_asign", "QuickSort_comp"); //asign+comp pentru QuickSort
	profiler.createGroup("QuickSortWorst_case", "QuickSort", "QuickSort_asign", "QuickSort_comp"); //grafic Worst Case pentru QuickSort

	profiler.showReport();

}

int main()
{
	int a[] = { 10, 7, 8, 9, 1, 5 };
	//int a[] = { 10, 4, 5, 8, 6, 11, 26 };
	int n = sizeof(a) / sizeof(a[0]);
	int k=3;

	quickSort(a, 0, n - 1, n);
	printf("Sorted array is:\n");
	printArray(a, n);

	printf("The smallest k element is:\n");
	printf("%d",quickSelect(a, 0, n - 1, k,n));
	printf("\n");

	//heapSort(a, n);
	//printf("The sorted array is:\n");
	//printArray(a, n);

	profiler.reset("QuickSort vs HeapSort");
	Average_case();
	profiler.showReport();

	//profiler.reset("QuickSort vs HeapSort");
	//Average_case1();
	//profiler.showReport();

	profiler.reset("QuickSort vs HeapSort");
	Best_case();
	profiler.showReport();

	profiler.reset("QuickSort vs HeapSort");
	Worst_case();
	profiler.showReport();

	return 0;
}