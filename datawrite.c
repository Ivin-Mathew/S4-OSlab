#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
void main()
{
   int shmid=shmget((key_t) 2222,1024,0666|IPC_CREAT);
   printf("Identifier for shared memory is %d\n",shmid);

   void* shared_memory=shmat(shmid,NULL,0);
   printf("Process attached at %p\n",shared_memory);
   
   printf("Enter data to write to shared memory:");
   char buff[100];
   scanf("%[^\n]",buff);
   strcpy(shared_memory,buff); //data written to shared memory
   printf("Data written to shared memory is:%s\n",(char *)shared_memory);
   shmdt(shared_memory); //detach from shared memory
}
