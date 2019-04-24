#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num = -1;

void *thread(void *vargp)
{
	int arg = *((int*)vargp);
	int label = num+1;
	num +=1;
	if(arg == 1 | arg == 0)
	{
		printf("[%d]\n",label);
		return NULL;
	}
	
	printf("(%d\n",label);
	pthread_t ltid; 
	pthread_t rtid;
	arg--;
	pthread_create(&ltid, NULL, thread, &(arg));
	pthread_join(ltid,NULL);
	arg--;
	pthread_create(&rtid, NULL, thread, &(arg));	
	pthread_join(rtid,NULL);
	arg+=2;
	printf("%d)\n", label);

	return NULL;
		 
} 

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	thread(&n);
	return 0;
}
