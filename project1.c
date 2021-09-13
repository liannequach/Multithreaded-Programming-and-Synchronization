#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> //header for usleep()
#include <string.h>

int SharedVariable= 0;
void *SimpleThread(void* which);

int main(int argc, char *argv[]) {
  int which;
  pthread_t *tid;
	
  if(argc != 2) { //check if the argument count is valid
     fprintf(stderr, "usage: a.out <integer value>\n");
     return 0;
  }
  else {
     for (which = 0; which < strlen(argv[1]); which++){
	if(argv[1][which] < '0' || argv[1][which] > '9'){
	   printf("\nnot valid\n");
	   break;
	 }
     }

     int n = atoi(argv[1]); //n is number of threads
     tid = (pthread_t *)malloc(sizeof(pthread_t) * atoi(argv[1]));
     int *j = (int *)malloc(sizeof(int)*n);
     for (which=0; which<n; which++){  			    		        j[which] = which;
		pthread_create(&tid[which], NULL,SimpleThread, &j[which]);
		pthread_join(tid[which],NULL);
     }
  }
  exit(0);
}

void *SimpleThread(void *which){
	int *addr;
	addr = which;
	int num, val =0;
	for (num=0; num<20; num++){
		if (random() > RAND_MAX /2)
			usleep(500); //0.0005s - time lapse
		val = SharedVariable;
		printf("***thread %d sees value %d\n", *addr, val);
		SharedVariable = val + 1;
	}
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *addr, val);
}











