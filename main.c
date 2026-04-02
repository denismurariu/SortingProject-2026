#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubbleSort(int v[], int n)
{
    int i, j, aux;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void insertionSort(int v[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
    }
}

void interclaseaza(int v[], int st, int m, int dr)
{
    int i, j, k;
    int n1 = m - st + 1;
    int n2 = dr - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    if (!L || !R)
    {
        printf("RAM FULL!\n");
        exit(1);
    }
    for (i = 0; i < n1; i++)
        L[i] = v[st + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];
    i = 0;
    j = 0;
    k = st;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            v[k++] = L[i++];
        else
            v[k++] = R[j++];
    }
    while (i < n1)
        v[k++] = L[i++];
    while (j < n2)
        v[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int v[], int st, int dr)
{
    if (st < dr)
    {
        int m = st + (dr - st) / 2;
        mergeSort(v, st, m);
        mergeSort(v, m + 1, dr);
        interclaseaza(v, st, m, dr);
    }
}

void genereaza(int v[], int n, int tip)
{
    if (tip == 0)
        for (int i = 0; i < n; i++)
            v[i] = rand();
    else if (tip == 1)
        for (int i = 0; i < n; i++)
            v[i] = i;
    else if (tip == 2)
        for (int i = 0; i < n; i++)
            v[i] = n - i;
    else if (tip == 3)
    {
        for (int i = 0; i < n; i++)
            v[i] = i;
        for (int i = 0; i < n / 20; i++)
        {
            int idx1 = rand() % n, idx2 = rand() % n;
            int aux = v[idx1];
            v[idx1] = v[idx2];
            v[idx2] = aux;
        }
    }
}

void copiaza(int sursa[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = sursa[i];
}

int main()
{
    srand(time(NULL));
    FILE *f = fopen("rezultate.csv", "w");
    fprintf(f, "N,TipDate,Algoritm,TimpSec\n");
    fclose(f);

    int n = 100;
    char *tipuri[] = {"Random", "Sortat", "Inversat", "AproapeSortat"};
    clock_t s, e;

    while (1)
    {
        printf("--- TEST N = %d ---\n", n);
        int *orig = malloc(n * sizeof(int));
        int *lucru = malloc(n * sizeof(int));
        if (!orig || !lucru)
        {
            printf("CRASH: RAM GATA la N=%d\n", n);
            break;
        }

        f = fopen("rezultate.csv", "a");
        for (int t = 0; t < 4; t++)
        {
            genereaza(orig, n, t);

            printf("  [%s] Bubble...", tipuri[t]);
            fflush(stdout);
            copiaza(orig, lucru, n);
            s = clock();
            bubbleSort(lucru, n);
            e = clock();
            fprintf(f, "%d,%s,BubbleSort,%f\n", n, tipuri[t], (double)(e - s) / CLOCKS_PER_SEC);

            printf(" Insertion...");
            fflush(stdout);
            copiaza(orig, lucru, n);
            s = clock();
            insertionSort(lucru, n);
            e = clock();
            fprintf(f, "%d,%s,InsertionSort,%f\n", n, tipuri[t], (double)(e - s) / CLOCKS_PER_SEC);

            printf(" Merge...\n");
            fflush(stdout);
            copiaza(orig, lucru, n);
            s = clock();
            mergeSort(lucru, 0, n - 1);
            e = clock();
            fprintf(f, "%d,%s,MergeSort,%f\n", n, tipuri[t], (double)(e - s) / CLOCKS_PER_SEC);
        }
        fclose(f);
        free(orig);
        free(lucru);

        if (n < 1000)
            n += 100;
        else if (n < 10000)
            n += 1000;
        else
            n += 5000;
    }
    return 0;
}