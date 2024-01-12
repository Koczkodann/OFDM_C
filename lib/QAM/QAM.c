#include "QAM.h"
void bpskModulation(int nBits, float *input, float *output,int inputNum)
{
	int numBit;
	if(nBits == 1){
		for(numBit = 0; numBit < inputNum; numBit++){
			output[numBit] = round(((float)input[numBit] * 2) - 1);

		}
	}
}

void bpskDemodulation(int nBits, kiss_fft_cpx* input, kiss_fft_cpx* output,int inputNum)
{
	int numBit;
	if(nBits == 1){
		for(numBit = 0; numBit < inputNum; numBit++){
			output[numBit].r = round(((float)input[numBit].r + 1)/2);
		}
	}
}

//MODULACJA QAM
//TODO
/*void qamModulation(int QAM_num,int* input, float* outputSignal, int inputNum) {
    int i;
    float I, Q;
    float constellation[16][2];

    	if(QAM_num == 2){
    		printf("BPSK");
    		memcpy (constellation, constellation2, sizeof(constellation2));
    	}
    	else if(QAM_num == 4){
    		printf("QPSK");
    		memcpy (constellation, constellation4, sizeof(constellation4));
    	}
    	else if(QAM_num == 8){
    		printf("QAM8");
    		memcpy (constellation, constellation8, sizeof(constellation8));
    	}
    	else{
    		printf("QAM16");
    		memcpy (constellation, constellation16, sizeof(constellation16));
    	}
    
    for (i = 0; i < inputNum; i++) {
        I = constellation[input[i]][0];
        Q = constellation[input[i]][1];

        printf("I:\n");
        printf("%f ", I);
        printf("Q:\n");
        printf("%f ", Q);

        outputSignal[i] = I * cos(2 * M_PI * i / inputNum) - Q * sin(2 * M_PI * i / inputNum);
    }
}*/
