/*
Exp.No:10
Aim:Memory Allocation Methods
Write a menu driven program for the implementation of the following Memory 
Allocation Methods for fixed partition :
 (a) First Fit (b) Best Fit (c) Worst Fit

 Name:Amal Raj R
 Roll No: 10
 Date: 29-04-2024
*/

#include<stdio.h>
void firstfit(int bsize[],int bno,int psize[],int pno);
void worstfit(int bsize[],int bno,int psize[],int pno);
void bestfit(int bsize[],int bno,int psize[],int pno);
void display_table(int psize[],int pno);
int allocation[10];

void main(){
	int bsize[10], psize[10], bno, pno,  i, j,bsize_temp[10];
	
	printf("Enter no. of blocks:");
	scanf("%d", &bno);
	printf("\nEnter size of each block:");
	for(i = 0; i < bno; i++){
		scanf("%d", &bsize_temp[i]);

	}
	printf("\nEnter no. of processes:");
	scanf("%d", &pno);
	printf("\nEnter size of each process: ");
	for(i = 0; i < pno; i++)
	{
		scanf("%d", &psize[i]);
	}
	int choice;
	do{
		for(i=0;i<10; i++)
		{
			allocation[i] =- 1;
		}

		for(i = 0; i < bno; i++){
			bsize[i]=bsize_temp[i];
		}
		printf("---------------------------------------------------------");
		printf("\nMenu\n1.First Fit\n2.Best Fit\n3.Worst Fit\n0.Exit\nEnter choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1: firstfit(bsize,bno,psize,pno);
					break;
			case 2: bestfit(bsize,bno,psize,pno);
					break;
			case 3: worstfit(bsize,bno,psize,pno);
					break;
					
			case 0: 
					break;
		}
	}while(choice!=0);




}


void firstfit(int bsize[],int bno,int psize[],int pno)
{
	printf("\nFirst Fit\n");

	

	for (int i = 0; i < pno; i++){
		for (int j=0; j<bno; j++){
			if (bsize[j]>= psize[i]){
				allocation[i] = j;
				bsize[j] -= psize[i];
				break;
			}
		}
	}
	display_table(psize,pno);

}

void bestfit(int bsize[],int bno,int psize[],int pno)
{
	//nb=bno
	//np=pno
	//b[20]=bsize[10]
	//p[20]=psize[01]

	int b[20],p[20],i,j,nb,np,temp,lowest,bestplace;
	
	printf("\nBest Fit\n");
	
	

	for(i=0;i<pno;i++){
		bestplace=-1;
		for(j=0;j<bno;j++){
			if(bsize[j]>psize[i]){
				if(bestplace == -1){
					bestplace = j;
					lowest = bsize[j]-psize[i];
				}
				else{
					temp=bsize[j]-psize[i];
					if(temp < lowest){
						bestplace = j;
						lowest = bsize[j] - psize[i];
					}

				}
				

			}
		}
		if(bestplace != -1){
			allocation[i] = bestplace;
			bsize[bestplace]-=psize[i];
		}
	}

	display_table(psize,pno);



	
	

}



void worstfit(int bsize[],int bno,int psize[],int pno){
	
	int i,j;
	printf("\nWorst Fit\n");

	
	for(i=0;i<pno;i++){
		int worstplace =- 1;
		for(j=0;j<bno;j++){
			if(bsize[j]>=psize[i]){
				if(worstplace ==- 1) 
					worstplace=j;
				else if (bsize[worstplace]<bsize[j])
					worstplace =j;


			}

		}
		if(worstplace !=- 1){
			allocation[i]=worstplace;
			bsize[worstplace] -= psize[i];
		}
	}
	display_table(psize,pno);
	
	



}
void display_table(int psize[],int pno){
	printf("\nProcess No.\tProcess Size\tBlock no.\n");
	for (int i = 0; i < pno; i++){
		printf(" %d\t\t%d\t\t",i+1,psize[i]);
		if (allocation[i] !=- 1)
			printf("%d\n",allocation[i]+1);
		else
			printf("Not Allocated\n");
	}
}