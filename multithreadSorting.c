#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr;
int arrSize;
int half;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void *sortHalf(void *array)
{
    int arraySize = *(int *)array;

    if (arraySize > half)
    { //this is the upper half of the arry
        for (int i = half; i < arraySize; i++)

        { // Last i elements are already in place
            for (int j = half; j < arraySize - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                    swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    else
    { //this sorts the lower half of the array
        for (int i = 0; i < arraySize; i++)
        {
            // Last i elements are already in place
            for (int j = 0; j < arraySize - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                    swap(&arr[j], &arr[j + 1]);
            }
        }
    }

    return NULL;
}

void *mergeArray(void *arraySize)
{

    int arrayLength = *(int *)arraySize;
    for (int i = 0; i < arrayLength; i++)

    { // Last i elements are already in place
        for (int j = 0; j < arrayLength - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int i = 0;       //array index
    int fint = 0;    //reading integers from file
    int counter = 1; //counting the size of array
    FILE *fp = fopen(argv[1], "r");

    //getting the size of the array
    fscanf(fp, "%d", &fint);
    while (!feof(fp))
    {
        counter++;
        fscanf(fp, "%d", &fint);
    }

    //allocating space to array, getting ful size and half size of array
    arr = (int *)malloc(sizeof(int) * counter);

    arrSize = counter;
    half = counter / 2;

    printf("%d , %d  \n\n", half, counter);

    //rewind the pointer to the start of the file
    rewind(fp);

    //reading the file and allocating integers to indexes
    fscanf(fp, "%d", &fint);
    while (!feof(fp))
    {
        arr[i] = fint;
        fscanf(fp, "%d", &fint);
        i++;
    }
    arr[i + 1] = fint;
    fclose(fp);

    pthread_t thread1,
        thread2, mergeThread;

    /* Create independent threads each of which will execute function */
    /* distingusing the threads but the size of the array */
    pthread_create(&thread1, NULL, sortHalf, &half);
    pthread_create(&thread2, NULL, sortHalf, &counter);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    for (int i = 0; i < counter - 1; i++)
    {
        printf("%d , ", arr[i]);
    }
    printf("\tarray after first two threads completed\n");

    int result = pthread_create(&mergeThread, NULL, mergeArray, &counter);

    pthread_join(mergeThread, NULL);

    for (int i = 0; i < counter - 1; i++)
    {
        printf("%d , ", arr[i]);
    }
    exit(0);
}
