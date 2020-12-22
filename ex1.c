#include <stdio.h>
#include <stdlib.h>

char LMA[3][2]={{'a','b'},{'e','f'},{'c','d'}};
char LMB[3][2]={{'r','x'},{'y','y'},{'z','z'}};
int PTA[3];
int PTB[3];

int FFL[16];
int mark[16]={0};
char FM[16][2];

int main(){
	//FFL
	int r=0;
	for(int i=0;i<16;++i){
		r=(rand()%16);
		while(mark[r]){
			r=(rand()%16);
		}
		mark[r]=1;
		FFL[i]=r;
		//printf("%d\n",r);
	}
	
	for(int i=0;i<3;++i){
		PTA[i]=FFL[i];
		PTB[i]=FFL[3+i];
	}

	printf("PTA\n");
	printf("page   fram\n");	
	for(int i=0;i<3;++i){
		printf("%d      %d\n",i,PTA[i]);
	}
	printf("LMA\n");
	for(int i=0;i<3;++i){
		printf("%d      %c%c\n",i,LMA[i][0],LMA[i][1]);
	}

	printf("PTB\n");
	printf("page   fram\n");	
	for(int i=0;i<3;++i){
		printf("%d      %d\n",i,PTB[i]);
	}
	printf("LMB\n");
	for(int i=0;i<3;++i){
		printf("%d      %c%c\n",i,LMB[i][0],LMB[i][1]);
	}
	
	for(int i=0;i<3;++i){
		FM[PTA[i]][0]=LMA[i][0];
		FM[PTA[i]][1]=LMA[i][1];
		FM[PTB[i]][0]=LMB[i][0];
		FM[PTB[i]][1]=LMB[i][1];
	}

	printf("FM\n");
	for(int i=0;i<16;++i){
		printf("%d    %d   %c\n",i,0,FM[i][0]); 
		printf("%d    %d   %c\n",i,1,FM[i][1]);
	}	
	
	for(int i=6;i<16;++i) printf("%d ",FFL[i]);	
	return 0;
}
