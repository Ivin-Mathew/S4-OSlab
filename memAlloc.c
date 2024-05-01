#include<stdio.h>



int bl,pr;
int blocks[20][2];
int page[20][2];

void firstfit();
void bestfit();
void worstfit();

void main(){
	printf("Enter no of blocks:");
	scanf("%d",&bl);
	printf("Enter block sizes:\n");
	for(int i=0;i<bl;i++){
		printf("block %d size= ",i);
		scanf("%d",&blocks[i][0]);
		blocks[i][1]=0;
	}



	printf("Enter no of processes:");
	scanf("%d",&pr);
	printf("Enter process sizes\n");
	for(int i=0;i<pr;i++){
		printf("process %d size= ",i);
		scanf("%d",&page[i][0]);
		page[i][1]=-1;
	}

	printf("1:First Fit\n2:Best fit\n3:Worst fit\n4:Exit");
	int opt=0;
	while (opt!=4){
		printf("Enter option:");
		scanf("%d",&opt);

		if(opt==1){
			firstfit();
		}
		else if(opt==2){
			bestfit();
		}
		else if(opt==3){
			worstfit();
		}
	}
}


void firstfit(){

	for(int i=0;i<pr;i++)
		page[i][1]=-1;
	for(int i=0;i<bl;i++)
		blocks[i][1]=0;

	for(int i=0;i<pr;i++){
		int alloc=0;
		while(alloc==0){
			for(int j=0;j<bl;j++){
				if(blocks[j][1]==0 && blocks[j][0]>=page[i][0]){
					alloc=1;
					blocks[j][1]=1;
					page[i][1]=j;
					break;
				}
			}
			break;
		}
	}

	printf("Allocated blocks:\n");
	for(int i=0;i<pr;i++){
		printf("Process %d : Block %d\n",i,page[i][1]);
	}

}

void bestfit(){
	
	for(int i=0;i<pr;i++)
		page[i][1]=-1;
	for(int i=0;i<bl;i++)
		blocks[i][1]=0;

	for(int i=0;i<pr;i++){
		int cur=-1;
		int temp=-1;
		for(int j=0;j<bl;j++){
			int diff=-1;
			if(blocks[j][1]==0 && blocks[j][0]>=page[i][0]){
				diff=blocks[j][0]-page[i][0];
				if(temp==-1){
					temp=diff;
					cur=j;
				}
				else if(diff<temp){
					temp=diff;
					cur=j;
				}
			}
		}
		page[i][1]=cur;
		blocks[cur][1]=1;
	}

	printf("Allocated blocks:\n");
	for(int i=0;i<pr;i++){
		printf("Process %d : Block %d\n",i,page[i][1]);
	}
	
}

void worstfit(){

	for(int i=0;i<pr;i++)
		page[i][1]=-1;
	for(int i=0;i<bl;i++)
		blocks[i][1]=0;

	for(int i=0;i<pr;i++){
		int cur=0;
		int diff=-1;
		for(int j=0;j<bl;j++){
			int temp=0;
			if(blocks[j][1]==0 && blocks[j][0]>page[i][0]){
				temp=blocks[j][0]-page[i][0];
				if(temp>diff){
					diff=temp;
					cur=j;
				}
			}
		}
		if(diff!=-1){
			page[i][1]=cur;
			blocks[cur][1]=1;
		}
	}

	printf("Allocated blocks:\n");
	for(int i=0;i<pr;i++){
		printf("Process %d : Block %d\n",i,page[i][1]);
	}
}