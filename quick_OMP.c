#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 

#define MAX 1000

int partition (int array[], int baixo, int alto)
{
    int i,j,pivot = array[alto],temp;    // pivo
    i = baixo - 1;  // indice de um menor elemento
 
    for(j = baixo; j <= alto - 1; j++)
    {
        // se o elemento atual for menor ou igual ao pivo
        if (array[j] <= pivot)
        {
            i++;    // incrementa um indice menor
            // realiza a troca (swap)      
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i + 1];
    array[i + 1] = array[alto];
    array[alto] = temp;
    return (i + 1);
}
void quickSort(int array[], int baixo, int alto)
{
    if (baixo < alto)
    {
        int pi = partition(array, baixo, alto);
 
        // classifica separadamente os elementos antes
        // de particionar e depois particiona
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section 
                quickSort(array, baixo, pi - 1);
            #pragma omp section
                quickSort(array, pi + 1, alto);
        }
    }
}

void printArray(int array[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int array[MAX],i;
    
    srand(time(NULL));
    
    // add elementos no array
    for(i=0;i<MAX;i++) {
        array[i] = rand() % MAX;
    }
    clock_t t1,t2;
    t1 = clock();
    quickSort(array, 0, MAX-1);
    t2 = clock();
    double t_time = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("Sorted array: n");
    printArray(array, MAX);
    printf("\t\tTime Elapsed: %.5f\n",t_time);
    return 0;
}
