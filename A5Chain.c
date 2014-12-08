#include "A5.h"



A5State chainReduce(byte *outA){
	unsigned long long stateB = 0;
	A5State state;
	int i;
	for (i=0; i<7; i++){
		stateB |= *(outA+i);
		stateB = stateB << 8;
	}
	stateB |= outA[7];
	state.R1 = stateB>>45;
	state.R2 = stateB>>23;
	state.R2&=SIZE2;
	state.R3 = stateB;
	state.R3&=SIZE3;
	return state;
}

int done(byte outA[15]){
	int done = 0,i;
	for (i=5;i<=7;i++){
			done |= outA[i];
	}
	if (done == 0) return 1;
	return 0;
}

void chain(A5State intialState, byte outA[15]){
	long long count = 0;
	int z;
	A5State state = intialState;
	A5SetState(&state);
	A5QRun(outA);
	while (!done(outA)){
			count++;
			if (count == 10000){
				printf("\nKEYSTREAM:");
				for (z=0; z<15; z++) printf("%02X", outA[z]);
				printf("\n");
			}
			/*
			if ((count&1048575)==1048575){
				printf(" %d \n",count);
			}
			for (z=0; z<15; z++) printf("%02X", a[z]);
			printf(" %0d",a[7]);
			printf("\n");
			*/
			state=chainReduce(outA);
			A5SetState(&state);
			A5100Clock();
			A5QRun(outA);
	}
	printf("\n%d \n",count);
}

void tableCreate(){
	int i,z;
	A5State state;
	byte a[15];byte b[15];
	byte key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	for (i = 0; i < 10; i++){
		key[0]=i;
		state=chainReduce(key);
		chain(state,a);
		printf("%u %u %u \n",state.R1,state.R2,state.R3);
		for (z=0; z<8; z++) printf("%02X", a[z]);
		printf("\n");
	}
}

void tableSearch(){
	

}

int main(){
	byte key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15];byte b[15];
	A5State state;
	int i,z;
	A5Setup(key,frame);
	A5Run(a,b);
	A5GetState(&state);
		
	table();
	
	//A5Setup(key,frame);
		
	printf("\n\n");
	
	for (i=0; i<15; i++)
		printf("%02X", a[i]);
	printf("\n");
	char t[4];
	long tt[4];
	
}