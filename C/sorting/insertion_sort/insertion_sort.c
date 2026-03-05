/**
 * @brief Insertion sort
 * Insertion sort is efficient method for sorting a small number of elements.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int data_t;

void insertion_at_sorting_position(data_t a[], size_t N, int(*cmp)(const void*, const void*));
void insertion_sort(data_t a[], size_t N, int(*cmp)(const void*, const void*));
void regrous_testing();

void input(data_t a[], size_t N);
void output(data_t a[], size_t N, const char* msg);

int cmp_int(const void* p, const void* q)
{
    int x = *(int*)p;
    int y = *(int*)q;

    return x - y;
}

int main()
{
    regrous_testing();
}

/**
 * Pre-condition (1) : N >= 2
 * Pre-condition (2) : a[0]...a[N-2] are sorted but a[0]...a[N-1] are not necessarily sorted
 * Post-condition : a[0]...a[N-1] entire array is sorted  
*/
void insertion_at_sorting_position(data_t* a, size_t N, int(*cmp)(const void*, const void*))
{
    data_t key;
    size_t i;

    key = a[N-1];
    i = N-2;

    for(; (i >= 0) && ((cmp ? cmp((void*)(a+i), (void*)(&key)) : (a[i] - key)) > 0); --i)
    {
        a[i+1] = a[i];
    }
    a[i+1] = key; 
}

void insertion_sort(data_t* a, size_t N, int(*cmp)(const void*, const void*))
{
    size_t j;
    size_t i;
    data_t key;
    
    i = 0;
    j = 0;

    for(j = 2; j <= N; ++j)
    {
        //insertion_at_sorting_position(a, j, cmp_int);
        data_t key = a[j-1];

        for(i = j-2; (i >=0) && ((cmp ? cmp((void*)(a+i), (void*)(&key)) : (a[i] - key)) > 0); --i)
        {
            a[i+1] = a[i];
        }
        a[i+1] = key;
    }
}

void regrous_testing()
{
    data_t* a = NULL;
    size_t N = 0;
    
    printf("Enter size of array: ");
    scanf("%lu", &N);
    
    if(N <= 0)
    {
        puts("Bad size for array");
        exit(EXIT_FAILURE);
    }

    a = (data_t*)malloc(sizeof(data_t)*N);
    if(a == NULL)
    {
        puts("Out of memory");
        exit(EXIT_FAILURE);
    }

    input(a, N);
    time_t t_start = time(0);
    insertion_sort(a, N, cmp_int);
    //insertion_sort(a, N, NULL);
    time_t t_end = time(0);

    printf("Integral time for Sort: %lu\n", t_end - t_start);
    output(a, N, "Sorted Array");
    free(a);
    a = NULL;
}

void input(data_t* a, size_t N)
{
    data_t cap = N * 10;
    size_t i;
    srand(time(0));

    i = 0;
    while(i < N)
    {
        a[i] = rand() % cap;
        i = i + 1;
    }
}

void output(data_t* a, size_t N, const char* msg)
{
    size_t i;

    if(NULL != msg)
        puts(msg);

    i = 0;
    while(i < N)
    {
        printf("a[%lu]:%d\n", i, a[i]);
        i = i + 1;
    }
}
