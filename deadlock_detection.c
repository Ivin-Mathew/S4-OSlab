#include <stdio.h>

struct process_info{
	
	int allocated[10];
	int request[10];
};
int no_of_process, no_of_resources;

//Take the input
void input(struct process_info process[no_of_process], int available[no_of_resources]){
	for(int i=0;i<no_of_process;i++){
		printf("Enter process[%d] info\n",i);
		
		printf("Enter No. of Allocated Resources: ");
		for(int j=0;j<no_of_resources;j++){
			scanf("%d",&process[i].allocated[j]);

		}
		printf("Enter No. of Requested Resources: ");
		for(int j=0;j<no_of_resources;j++){
			scanf("%d",&process[i].request[j]);
		}
	}
	printf("Enter Available Resources: ");
	for(int i=0;i< no_of_resources;i++){
		scanf("%d",&available[i]);
	}
}

//Print the Info in Tabular form
void showTheInfo(struct process_info process[no_of_process]){
	printf("PID\tAllocated\tRequest\n");
	for(int i=0;i<no_of_process;i++){
		printf("P[%d]\t",i);
		
		for(int j=0;j<no_of_resources;j++){
			printf("%d ",process[i].allocated[j]);
		}
		printf("\t\t");
		for(int j=0;j<no_of_resources;j++){
			printf("%d ",process[i].request[j]);
		}
		printf("\n");
	}
}
int isSafeState(struct process_info process[no_of_process],int available[no_of_resources],int safeSequence[no_of_process]){
	int finish[no_of_process];
	int work[no_of_resources];
	for(int i=0;i<no_of_resources;i++){
		work[i]=available[i];
	}
	for(int i=0;i<no_of_process;i++){
		finish[i]=0;
	}
	int proceed=1;
	int k=0;
	while(proceed){
		proceed=0;
		for(int  i=0;i<no_of_process;i++){
			int flag=1;
			if(finish[i]==0){
				for(int j=0;j<no_of_resources;j++){
					if(process[i].request[j]<=work[j]){
						continue;
					}
					else{
						flag=0;
						break;
					}
				}
				if(flag==0){
					continue;
				}
				for(int j=0;j<no_of_resources;j++){
					work[j]=work[j]+process[i].allocated[j];
				}
				finish[i]=1;
				safeSequence[k++]=i;
				proceed=1;
			}
		}
	}
	int i;
	for(i=0;i<no_of_process&&finish[i]==1;i++){
		continue;
	}
	if(i==no_of_process){
		return 1;
	}
	else{
		return 0;
	}
}




int main()
{
	printf("Enter No of Process\n");
	scanf("%d",&no_of_process);
	printf("Enter No of Resource Instances in system\n");
	scanf("%d",&no_of_resources);
	int available[no_of_resources];
	int safeSequence[no_of_process];
	//Create Array of Structure to store Processes's Informations
	struct process_info process[no_of_process];
	
	printf("****************Enter details of processes*****************\n");
	input(process, available);

	showTheInfo(process);
	if(isSafeState(process, available, safeSequence)){
		printf("System is in safe state\n");
		printf("Safe sequence is: ");
		for(int i=0;i<no_of_process;i++){
			printf("P[%d] ",safeSequence[i]);
		}
	}
	else{
		printf("System is not in Safe State\n");
	}
	return 0;
}

