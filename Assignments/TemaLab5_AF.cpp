#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "C:\\Users\\Bianca\\Desktop\\AF\\Profiler\\Profiler2.1\Profiler.h"
/*
	Tema nr. 5 Tabele de dispersie - Open Addressing
	
	-In cazul adresarii deschise functia de dispersie este cea care ajuta la rezolvarea coliziunii
	-Am implementat urmatoarele operatii intr-o tabela de dispersie: cautare, stergere, inserare de cheie.
	-Demo pentru factor de umplere 0.96
	-Evaluare cautare pentru factorii de umplere 0.80, 0.85, 0,90, 0.95. Am observat ca odata cu cresterea 
	factorului de umplere creste si numarul de operatii

*/

using namespace std;

Profiler profiler("Tabela de dispersie - Adresare deschisa");

typedef struct cell {
	int val;
	int status;
}Cell;

enum { FREE, OCCUPIED, DELETED };

void afisare(Cell* T, int m)
{
	int i;
	printf("\n\nTabela de dispersie este:\n");
	for (i = 0; i < m; i++)
	{
		if (T[i].status == OCCUPIED)
			printf("T[%d]=%d\n", i, T[i]);
		else
			printf("T[%d]=--\n", i);
	}

}

//Verificam daca toata tabela e ocupata
int hash_table_occupied(Cell* T, int m)
{
	int i;
	for (i = 0; i < m; i++)
	{
		if (T[i].status == FREE)
			return 0;
	}
	return 1;
}

//Functia de dispersie
int h_prime(int k, int m)
{
	return k % m;
}

//Returneaza pozitia la care se va verifica tabela de dispersie folosind verificarea liniara
int linear_probing(int k, int m, int i)
{
	//h(k, i) = (h’(k)+i) mod m
	int val = (h_prime(k, m) + i) % m; //i-ul creste atata timp cat avem coliziuni. Scopul este de a le evita
	return val;
}

//Verificare patratica, la fel ca si in cazul de mai sus, se returneaza pozitia la care se va verifica tabela de dispersie folosind verificare patratica de aceasta data.
int quadratic_probing(int k, int m, int i)
{
	int c1, c2 = c1 = 1;
	int val = (h_prime(k, m) + c1 * i + c2 * i * i) % m;
	return val;
}

//Inserare cheie in tabela de dispersie
void insert_quadratic_probing(int k, Cell* T, int m)
{
	if (hash_table_occupied(T, m))
	{
		printf("Nu se mai poate insera cheia %d, tabela este plina. \n", k);
		return;
	}

	int i = 0;
	int collision = 1;
	int h = 0;

	do {
		h = quadratic_probing(k, m, i);
		if (T[h].status == FREE)
			collision = 0;
		else i++;
	} while (collision);

	T[h].status = OCCUPIED;
	T[h].val = k;

}

//Eliberare
void set_table_free(Cell* T, int m)
{
	//Initializam tabela
	int i;
	for (i = 0; i < m; i++)
	{
		T[i].status = FREE;
	}

}

//Cautare cheie in tabela de dispersie
int search_quadratic_probing(int k, Cell* T, int m, int* i)
{
	*i = 0;
	int h = 0;

	do {
		h = quadratic_probing(k, m, *i);
		if (T[h].val == k)
			return h;
		else (*i)++;
	} while (*i < m && T[h].status == OCCUPIED);

	return NULL;
}

//Stergere cheie in tabela de dispersie
void delete_quadratic_probing(int k, Cell* T, int m)
{
	//int i = 0;
	int aux;
	int h = search_quadratic_probing(k, T, m, &aux);

	if (h != NULL)
	{
		T[h].status = FREE;
	}
}

//Demo pentru o tabela cu 7 elemente
int dummy_demo()
{
	int m = 7;
	Cell* T = (Cell*)malloc(m * sizeof(Cell)); //tabela de dispersie - se aloca dinamic

	//Resetam tabela
	set_table_free(T, m);

	//Inserez elemente in tabela de dispersie. 
	//Dimensiunea tabelei mele este 7, dar inserez 8 elemente.Un element nu va fi inserat.
	insert_quadratic_probing(19, T, m);
	insert_quadratic_probing(36, T, m);
	insert_quadratic_probing(5, T, m);
	insert_quadratic_probing(21, T, m);
	insert_quadratic_probing(4, T, m);
	insert_quadratic_probing(26, T, m);
	insert_quadratic_probing(14, T, m);
	insert_quadratic_probing(17, T, m);
	afisare(T, m);

	//Stergere cheie
	printf("\nDupa stergerere: ");
	delete_quadratic_probing(21, T, m);
	afisare(T, m);

	//Cautare in tabela de dispersie
	set_table_free(T, m);
	int aux;
	int f = search_quadratic_probing(24, T, m, &aux);
	if (f == NULL)
		printf("\nNu s-a gasit in tabela elementul 24 dupa operatia de cautare.\n");
	else
		printf("\nElement gasit in tabela.\n");

	//set_table_free(T, m);
	//delete_quadratic_probing(21, T, m);
	//afisare(T, m);

	return 0;
}

//Demo pentru factor de umplere 0.95
void demo_95()
{
	//In acest caz factorul de umplere este 0.95
	int v[100];
	int m = 95;
	int N = 101;
	int a = m / N; //factor de umplere, a<=1 tot timpul
	int n;
	Cell* T = (Cell*)malloc(N * sizeof(Cell)); //tabela de dispersie - se aloca dinamic

	set_table_free(T, N);
	printf("\nFactor de umplere 0.95\n");
	FillRandomArray(v, 95, 1, 200, false, 0);
	for (int i = 0; i < 95; i++)
	{
		insert_quadratic_probing(v[i], T, N);
	}
	afisare(T, N);

}

void evaluate(int n)
{
	int a[100000], b[10000];
	int m = 10007;
	Cell* T = (Cell*)malloc(m * sizeof(Cell));

	int max_found = 0;
	int max_Notfound = 0;
	int i1, i2;
	float avg_found = 0;
	float avg_Notfound = 0;
	float k1 = 0;
	float k2 = 0;

	set_table_free(T, m);

	//int alfa = int(f / 100700);

	FillRandomArray(a, n, 1, 30000, false, 0);
	FillRandomArray(b, 1500, 30001, 40000, false, 0);

	for (int i = 0; i < n; i++)
		insert_quadratic_probing(a[i], T, m);

	//Not found
	for (int i = 0; i < 1500; i++)
	{
		search_quadratic_probing(b[i], T, m, &i1);
		k1 = k1 + i1; //numar i-urile pentru care not found

		if (max_Notfound < i1)
			max_Notfound = i1;
	}

	//Found
	for (int i = n - 3000; i < n - 1500; i++)
	{
		search_quadratic_probing(a[i], T, m, &i2);
		k2 = k2 + i2; //numar i-urile pentru care found

		if (max_found < i2)
			max_found = i2;
	}

	//Average
	avg_found = (float)k2 / 1500;
	avg_Notfound = (float)k1 / 1500;

	//Afisare
	printf("\nMAX FOUND: %d\n", max_found);
	printf("MAX NOT FOUND: %d\n", max_Notfound);
	printf("Average FOUND: %f\n", avg_found);
	printf("Average NOT FOUND: %f\n", avg_Notfound);

}

//Demo pentru factor de umplere 0.80
void demo_80()
{
	int v[10000];
	int m = 80;
	int N = 101;
	int a = m / N; //factor de umplere, a<=1 tot timpul
	int n;
	Cell* T = (Cell*)malloc(N * sizeof(Cell)); //tabela de dispersie - se aloca dinamic

	set_table_free(T, N);
	printf("\nFactor de umplere 0.80\n");
	FillRandomArray(v, 80, 1, 20000, false, 0);
	for (int i = 0; i < 80; i++)
	{
		insert_quadratic_probing(v[i], T, N);
	}
	afisare(T, N);

}

//Demo pentru factor de umplere 0.85
void demo_85()
{
	int v[10000];
	int m = 85;
	int N = 101;
	int a = m / N; //factor de umplere, a<=1 tot timpul
	int n;
	Cell* T = (Cell*)malloc(N * sizeof(Cell)); //tabela de dispersie - se aloca dinamic

	set_table_free(T, N);
	printf("\nFactor de umplere 0.85\n");
	FillRandomArray(v, 85, 1, 20000, false, 0);
	for (int i = 0; i < 80; i++)
	{
		insert_quadratic_probing(v[i], T, N);
	}
	afisare(T, N);

}

//Demo pentru factor de umplere 0.90
void demo_90()
{
	int v[10000];
	int m = 90;
	int N = 101;
	int a = m / N; //factor de umplere, a<=1 tot timpul
	int n;
	Cell* T = (Cell*)malloc(N * sizeof(Cell)); //tabela de dispersie - se aloca dinamic

	set_table_free(T, N);
	printf("\nFactor de umplere 0.90\n");
	FillRandomArray(v, 90, 1, 20000, false, 0);
	for (int i = 0; i < 80; i++)
	{
		insert_quadratic_probing(v[i], T, N);
	}
	afisare(T, N);

}


int main()
{
	dummy_demo();
	demo_95();

	//printf("Introdu factor de umplere: ");
	//scanf_s("%d", &f);
	//set_table_free(T, m); 

	demo_80();
	demo_85();
	demo_90();
	
	//alfa=n/M; Mai mic decat 1 tot timpul.

	//Factor de umplere 0.80
	printf("\nEvaluare cautare, alfa = 0.80:\n ");
	evaluate(8007);

	//Factor de umplere 0.85
	printf("\nEvaluare cautare, alfa = 0.85:\n ");
	evaluate(8507);

	//Factor de umplere 0.90
	printf("\nEvaluare cautare, alfa = 0.90:\n ");
	evaluate(9007);

	//Factor de umplere 0.95
	printf("\nEvaluare cautare, alfa = 0.95:\n ");
	evaluate(9507);

	return 0;
}
