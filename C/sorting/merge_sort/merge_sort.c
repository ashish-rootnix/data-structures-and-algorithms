/**
 * @brief Merge sort
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>

typedef int data_t;
void merge_sort(data_t* a, size_t p, size_t q, int(*cmp)(void* p, void* q));
void regrous_sorting_test();
void sort_test();

int cmp(void* p, void* q) // Greater than
{
    return *(int*)p - *(int*)q;
}

int main()
{
    //sort_test();
    regrous_sorting_test();
}
void merge(data_t* a, size_t p, size_t q, size_t r, int(*cmp)(void* p, void* q))
{
    size_t nl = q - p + 1; // length of left array
    size_t nr = r - q;  // Length of rignt array
    size_t i, j,  k;

    data_t* temp_data = (data_t*)malloc(sizeof(data_t)* (nl+nr));
    memset(temp_data, 0, (nl+nr));
    i = 0;
    j = 0;
    k = 0;

    while ((i < nl) && (j < nr))
    {
        if((cmp ? cmp((void*)(a+p+i), (void*)(a+q+1+j)) : (a[p+i] <= a[q+1+j])) > 0)
        {
            temp_data[k] = a[p+i];
            i = i + 1;
        }
        else
        {
            temp_data[k] = a[q+1+j];
            j = j + 1;
        }
        k = k + 1;
    }
    while(i < nl)
    {
        temp_data[k] = a[p+i];
        i = i + 1;
        k = k + 1;                    
    }
    while(j < nr)
    {
        temp_data[k] = a[q+1+j];
        j = j + 1;
        k = k + 1;                    
    }
    for(i = 0; i < (nl+nr); ++i)
    {
        a[p+i] = temp_data[i];
    }
}
void merge_sort(data_t* a, size_t p, size_t r, int(*cmp)(void* p, void* q))
{
    if(p >= r)
        return;
    size_t q = (p + r) / 2;

    merge_sort(a, p, q, cmp);
    merge_sort(a, q+1, r, cmp);

    merge(a, p, q, r, cmp);
}

void regrous_sorting_test()
{
    data_t* data = NULL;
    size_t N;

    printf("Enter size :");
    scanf("%lu", &N);

    data = (data_t*)malloc(sizeof(data_t)*N);
    if(NULL == data)
    {
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    srand(time(0));
    for(size_t i = 0; i < N; ++i)
    {
        data[i] = rand() % N * 10;
    }

    time_t t_start = time(0);
    merge_sort(data, 0, N-1, NULL);
    time_t t_end = time(0);

    printf("Merge sort time for %lu elements is %lu \n", N, t_end- t_start);
}

void sort_test()
{
    int a[] = {2, 4, 6, 7, 1, 2, 3, 5};

    puts("Before sorting array: ");
    for(size_t i = 0; i < 8; ++i)
    {
        printf("data[%lu]:%d\n", i, a[i]);
    }
    printf("\n");
    merge_sort(a, 0, 7, cmp);
    puts("Sorted array: ");
    for(size_t i = 0; i < 8; ++i)
    {
        printf("data[%lu]:%d\n", i, a[i]);
    }
}
