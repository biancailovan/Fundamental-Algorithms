#include <stdio.h>
#include <stdlib.h>

int time;

/*****************************************************
  Tema nr. 10
  Reprezentarea grafului este prin liste de adiacenta dinamice.
  Graful se parcurge in maniera DFS si se salveaza arborele (arborii)
  de parcurgere, in vectorul pi; de asemenea, la varianta recursiva se
  inregistreaza si informatia de culoare si timpii de descoperire si
  finalizare.
******************************************************/

typedef struct nod {
    int val;
    struct nod* next;
} NodeT;

typedef struct {
    int n;      // numar de varfuri
    NodeT** t;  // tabloul de liste (va fi alocat dinamic)
    int* pi; //vectorul de parinti
    int* d; //timpii de descoperire
    int* f; //timpii de finalizare
    int* color; //informatia de culoare
} Graf;      // structura pentru memorarea grafului prin liste de adiacenta dinamice; tine si informatia de parcurgere

enum { WHITE, GRAY, BLACK };

//Insert first in a linked list
void push(NodeT** stiva, int val)
{ 
    NodeT* el = (NodeT*)malloc(sizeof(NodeT));
    el->val = val;
    el->next = (*stiva);
    *stiva = el;
}

/* sterge elementul din varful stivei si returneaza valoarea lui */
int pop(NodeT** stiva)
{
    int n = -1;
    if (*stiva != NULL) 
    {
        NodeT* firstElement = (*stiva);
        *stiva = (*stiva)->next;
        n = firstElement->val;
        free(firstElement);
    }
    return n;
}

/* returneaza 1 daca stiva este goala */
int empty(NodeT* stiva)
{
    return stiva == NULL;
}

//Initializeaza stiva
void init(NodeT** stiva)
{
    *stiva = NULL;
}

void printErr() 
{
    printf("Memorie insuficienta!\n");
    exit(1);
}

// Dfs cu colorarea nodurilor si marcaje de timp
void dfsVisit(int v, Graf* G)
{
    G->color[v] = GRAY;
    printf("%d ", v);
    G->d[v] = ++time;
    NodeT* p;
    for (p = G->t[v]; p != NULL; p = p->next)
        if (G->color[p->val] == WHITE)
        {
            G->pi[p->val] = v;
            //printf("%d ", p->val);
            dfsVisit(p->val, G);
        }
    G->color[v] = BLACK;
    G->f[v] = ++time;

}

void dfsRecursiv(Graf* G)
{

    int time = 0, i;

    for (i = 0; i < G->n; i++)
    {
        if (G->color[i] == WHITE)
        {
            dfsVisit(i, G);
        }
    }
}

void afisare(Graf* G)
{
    NodeT* p;
    for (int i = 0; i < G->n; i++)
    {
        printf("\r\n%d: ", i);
        for (p = G->t[i]; p != NULL; p = p->next)
            printf("%d ", p->val);
    }
}


void citesteGraf(Graf* pG) 
{
    //Citesc nr de noduri
    printf("\nIntroduceti numarul de noduri:\n");
    scanf_s("%d", &pG->n);  // citeste nr. de varfuri

    pG->t = (NodeT**)calloc(pG->n, sizeof(NodeT*));
    if (pG->t == NULL) printErr();  // alocare esuata

    pG->pi = (int*)calloc(pG->n, sizeof(int));
    pG->d = (int*)calloc(pG->n, sizeof(int));
    pG->f = (int*)calloc(pG->n, sizeof(int));
    pG->color = (int*)calloc(pG->n, sizeof(int));

    int i;
    for (i = 0; i < pG->n; i++)
    {
        pG->t[i] = NULL;
        pG->pi[i] = -1;
    }

    //Citesc muchiile
    printf("\nIntroduceti muchiile:\n");
    int v, w;
    for (int i = 0; i < pG->n; i++)
    {
        printf("v=");
        scanf_s("%d", &v);
        printf("w=");
        scanf_s("%d", &w);

        //graful va fi neorientat, se adauga atat arcul (v,w) cat si (w,v)
        push(&pG->t[w], v);
        push(&pG->t[v], w);
    }

}

void print(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void reInitTraversalData(Graf* G)
{
    for (int i = 0; i < G->n; i++)
    {
        G->d[i] = -1;
        G->pi[i] = -1;
        G->f[i] = -1;
        G->color[i] = WHITE;
    }

}


void checkDFS()
{
    Graf G;
    citesteGraf(&G);

    printf("\nDFS visit:\n");
    dfsRecursiv(&G);
    printf("\nVectorul de parinti:");
    print(G.pi, G.n);
    printf("Timpii de descoperire:");
    print(G.d, G.n);
    printf("Timpii de finalizare:");
    print(G.f, G.n);
    printf("Afisare graf:\n");
    afisare(&G);
    printf("\n");

    //Eliberez memoria
    free(G.color);
    free(G.d);
    free(G.f);
    free(G.t);

}

int main()
{
    checkDFS();
    return 0;
}

