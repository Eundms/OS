#include<stdio.h>
#include<unistd.h>
int main(){
	printf("Enqueue 3\n");
	syscall(326,3);
	printf("Enqueue 2\n");
	syscall(326,2);
	printf("Enqueue 1\n");
	syscall(326,1);

	int deq=syscall(327);
	printf("Dequeue %d\n",deq);

}

