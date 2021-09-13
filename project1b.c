#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int SharedVariable = 0;
pthread_mutex_t lock; //prevent error when accessing SharedVarible 
                 //and ensure synchronization while the program is running
pthread_barrier_t barr; //causes a certain number of threads to rendezvous at the barrier before starting the next part of the program

void *threadFunc(void *arg){
   int which = *((int*)arg);
   int i;
   
   for(i=0;i<20; i++){
      #ifdef PTHREAD_SYNC
      	 pthread_mutex_lock(&lock); 
      #endif
      
      printf("*** thread %d sees value %d\n", which, SharedVariable);
      SharedVariable++;
      
      #ifdef PTHREAD_SYNC
      	 pthread_mutex_unlock(&lock); 
      #endif
   }
    
   pthread_barrier_wait(&barr);
   printf("Thread %d sees final value %d\n", which, SharedVariable);
   return NULL;
}

int main(int argc, char** argv) { 
   int i, err;
   int n = atoi(argv[1]); //n is number of threads- to put the number in the command parameter
      
   pthread_t threads[n];
   int threadIds[n];
   
   pthread_mutex_init(&lock, NULL); //initialize mutex
   pthread_barrier_init(&barr, NULL, n); //initialize barrier
   
 for(i=0; i<n; i++) {//create threads
   threadIds[i] = i;
   err = pthread_create(&threads[i], NULL, threadFunc,(void*)&threadIds[i]);
      if(err) {
        printf("Error! %d\n", err);
        exit(-1);
      } 
 }
  
 for(i=0; i<n; i++)
    pthread_join(threads[i], NULL); // join thread
 
 return 0;
}     
    
    
    
    
