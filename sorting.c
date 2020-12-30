/**
 * Carter Mooring
 * Date: Nov. 4th, 2020
 * Project 4
 * CPSC 346 OS
 * 
 * How to Run: 'gcc -pthread sorting.c -o a.out'
 * 				'./a.out'
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE				10
#define NUMBER_OF_THREADS	3

void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
	int from_index;
	int to_index;
} parameters;

int main (int argc, const char * argv[]) 
{
	int i;
    
	pthread_t workers[NUMBER_OF_THREADS];
	
	/* establish the first sorting thread */
	//1. call malloc to allocate a “parameters”
	//2. use “parameters” to specify the first half of the array
      //3. create the first thread
    parameters *data = (parameters*)malloc(SIZE/2 * sizeof(parameters));
    data -> from_index = 0;
    data -> to_index = (SIZE/2) - 1;
    pthread_create(&workers[0], 0, sorter, data);
	

	/* establish the second sorting thread */
	//1. call malloc to allocate a “parameters”
	//2. use “parameters” to specify the first half of the array
      //3. create the second thread
    data = (parameters*)malloc(SIZE/2 * sizeof(parameters));
    data -> from_index = (SIZE/2);
    data -> to_index = SIZE - 1;
    pthread_create(&workers[1], 0, sorter, data);
	
	/* now wait for the 2 sorting threads to finish */
	// use ptheread_join; wait for 2 sorting threads to finish 
	for(i = 0; i < NUMBER_OF_THREADS - 1; i++){
		pthread_join(workers[i], NULL);
	}

	/* establish the merge thread */
	//reuse “parameters” to hold the beginning index in each half
	//create the third thread: merge 
	
	/* wait for the merge thread to finish */
	 data = (parameters*)malloc(SIZE * sizeof(parameters));
	 data -> from_index = 0;
	 data -> to_index = SIZE;
	 pthread_create(&workers[2], 0, merger, data);


	/* output the sorted array */
	 pthread_join(workers[2], NULL);
	
    return 0;
}

/**
 * Sorting thread.
 *
 * This thread can essentially use any algorithm for sorting
 */

void *sorter(void *params)
{
	parameters* p = (parameters *)params;
	
	// Sorting algorithm here. It can be any sorting algorithm.
	int start = p -> from_index;
	int end = p -> to_index+1;

	int i, j, k, l;
	
	printf("\n");
	
	printf("The array inputed is:");
	for(i = start; i < end; i++){
		printf("%d", list[i]);
	}
	
	printf("\n");
	printf("\n");
	
	
	int temp = 0;
	for(i = start; i < end; i++){
		for(j = start; j < end - 1; j++){
			if(list[j] > list[j + 1]){
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	
	printf("The sorted array is:");
	
	for(k = start; k < end; k++){
		printf("%d", list[k]);
	}
	
	for(l = start; l < end; l++){
		result[l] = list[l];
	}
	printf("\n");
	
	pthread_exit(0);
}

/**
 * Merge thread
 *
 * Uses simple merge sort for merging two sublists
 */

void *merger(void *params)
{
	parameters* p = (parameters *)params;
	
	//reuse “parameters” to hold the first index in each half
	//merge two sorted sublist to the arry result
	int start = p -> from_index;
	int end = p -> to_index+1;

	int i, j, k, l;
	int temp;
	
	for(i = start; i < end; i++){
		for(j = start; j < end - 1; j++){
			if(result[j] > result[j + 1]){
				temp = result[j];
				result[j] = result[j + 1];
				result[j + 1] = temp;
			}
		}
	}
	printf("\n");
	printf("FINAL RESULT\n");
	
	printf("The final sorted array is:");
	
	for(l = start + 1; l < end; l++)
    {
        printf("%d", result[l]);
    }
	printf("\n");
	
	pthread_exit(0);
}


