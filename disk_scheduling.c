#include<stdio.h>
#include<stdlib.h>
void display_out(int TotalHeadMovement,int order[], int n );
void fcfs_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[]);
void scan_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[]);
void c_scan_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[]);
int size;
void main(){
	int rq[100],rq_temp[100],i,j,n,initial_pos;
	int choice;
	int TotalHeadMovement=0;
	int order[100];
	printf("Enter total disk size: ");
	scanf("%d",&size);
	printf("Enter the number of Requests: ");
	scanf("%d",&n);
	printf("Enter Request sequence: \n");
	for(i=0;i<n;i++){
		scanf("%d",&rq_temp[i]);
	}
	printf("Enter initial head position: ");
	scanf("%d",&initial_pos);

	printf("\n---------------------------------------------------------");
	printf("\nMenu\n1.FCFS\n2.SCAN\n3.C SCAN\n0.Exit\n");
	do{
		for(i=0;i<n;i++){
			rq[i]=rq_temp[i];
		}
		
		printf("Enter choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1: fcfs_sch(rq,n,initial_pos,TotalHeadMovement,order);
					break;
			case 2:scan_sch(rq,n,initial_pos,TotalHeadMovement,order);
					break;
			case 3:c_scan_sch(rq,n,initial_pos,TotalHeadMovement,order);
					break;
					
			case 0: 
					break;
		}
	}while(choice!=0);

}

void fcfs_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[]){
	for(int i=0;i<n;i++){
		TotalHeadMovement+=abs(rq[i]-initial_pos);
		order[i]=rq[i];
		initial_pos=rq[i];
	}
	display_out(TotalHeadMovement,order,n);
}

void display_out(int TotalHeadMovement,int order[], int n){
	printf("Seek sequence : ");
	for(int i=0;i<n;i++){
		printf("%d ",order[i]);
	}
	printf("\nTotalHeadMovement = %d ",TotalHeadMovement);
}


void scan_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[])
{
	int move,i,j,k=0;
	int index;
	printf("Enter direction to move(1= high and 0= low):  ");
	scanf("%d",&move);
	rq[n]=size;
	n++;
	//sorting rq
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(rq[j]>rq[j+1]){
				int temp=rq[j];
				rq[j]=rq[j+1];
				rq[j+1]=temp;
			}
		}
	}
	printf("Sorted requests; ");
	for(i=0;i<n;i++){
		if(rq[i]!=size)
			printf("%d ",rq[i]);
	}
	printf("\n");
	for(i=0;i<n;i++){
		if(initial_pos<rq[i]){
			index=i;
			break;
		}
	}
	if (move == 1){
		for(i=index;i<n;i++){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}

		TotalHeadMovement+=abs(size-rq[i-1]-1);
		
		initial_pos=size-1;
		for(i=index-1;i>=0;i--){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}
	}
	else{
		for(i=index-1;i>=0;i--){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];

		}
		TotalHeadMovement+=abs(rq[i+1]);
		initial_pos=0;
		for(i=index;i<n;i++){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}
	}
	display_out(TotalHeadMovement,order,k);
}
void c_scan_sch(int rq[],int n,int initial_pos,int TotalHeadMovement,int order[])
{
	int move,i,j,k=0;
	int index;
	printf("Enter direction to move(1=high and 0=low):  ");
	scanf("%d",&move);
	rq[n]=size;
	n++;
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(rq[j]>rq[j+1]){
				int temp=rq[j];
				rq[j]=rq[j+1];
				rq[j+1]=temp;
			}
		}
	}
	printf("Sorted requests:");
	for(i=0;i<n;i++){
		printf("%d ",rq[i]);

	}
	printf("\n");
	for(i=0;i<n;i++){
		if(initial_pos<rq[i]){
			index=i;
			break;
		}
	}
	if (move == 1){
		for(i=index;i<n;i++){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}

		TotalHeadMovement+=abs(size-rq[i-1]-1);
		TotalHeadMovement+=abs(size-1-0);

		initial_pos=0;
		for(i=0;i<=index-1;i++){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}
	}
	else{
		for(i=index-1;i>=0;i--){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];
		}
		TotalHeadMovement+=abs(rq[i+1]);
		TotalHeadMovement+=abs(size-1-0);
		initial_pos=size-1;
		for(i=n-1;i>=index;i--){
			TotalHeadMovement+=abs(rq[i] - initial_pos);
			initial_pos=rq[i];
			order[k++]=rq[i];

		}
	}
	display_out(TotalHeadMovement,order,k);

}
