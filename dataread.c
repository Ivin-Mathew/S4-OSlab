
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
void main()
{
   int shmid=shmget((key_t) 2222,1024,0666);
   printf("Identifier for shared memory is: %d\n",shmid);
   void *shared_memory=shmat(shmid,NULL,0);
   printf("Process attached at %p\n",shared_memory);
   printf("Data read from shared memory is:%s\n",(char *)shared_memory);
   shmdt(shared_memory);
   shmctl(shmid,IPC_RMID,NULL);
}

