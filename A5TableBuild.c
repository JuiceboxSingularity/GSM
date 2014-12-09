#include "A5Chain.h"

void tableCreate(int chains, int end){
	int i,z;
	A5State state;	
	srand (5);
	byte a[15];
	unsigned long long start,input,output;
	for (i = 0; i < chains; i++){
		//state=chainReduce(a);
		start = rand();
		start <<= 32;
		start |= rand();
		state = convertToState(start);
		chain(state,a,end);
		input = compressStateStruct(state);
		printf("%016llX,",input);
		output = compressState(a);
		printf("%016llX\n",output);		
	}
}

int main(int argc, char *argv[]){
	int i,z,chains,dp;
	
	if (argc < 3) {
       fprintf(stderr,"usage %s chains distinguishedPointStart\n", argv[0]);
       exit(0);
    }
	chains = atoi(argv[2]);
	dp = atoi(argv[2]);
	/*
	byte key[8] = {0x12, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	reg frame = 0x134;
	byte a[15];byte b[15];
	A5State state;
	
	A5Setup(key,frame);
	A5Run(a,b);
	A5GetState(&state);
	printf("HEYHEYHEY\n");
	*/
	tableCreate(chains,dp);
	//tableSearch();
	//A5Setup(key,frame);
	
}