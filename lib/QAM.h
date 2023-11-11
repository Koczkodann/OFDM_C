#ifndef LIB_QAM_H_
#define LIB_QAM_H_

#include <stdio.h>

void qamModulation(int nBits,int* input, float* output,int inputNum);

//BPSK (QAM2)
const int nBits2 = 1;
const float constellation2[2][2] = {
    {-1, 0}, {1, 0}
};

//QPSK (QAM4)
const int nBits4 = 2;
const float constellation4[4][2] = {
	    {1, 1}, {1, -1},
	    {-1, 1}, {-1, -1}
	};

//QAM 8
const int nBits8 = 3;
const float constellation8[8][2] = {
	    {1, 1}, {1, 3},
		{3, 1}, {3, 3},
		{1, -1}, {1, -3},
	    {3, -1}, {3, -3}
	};

//QAM16
int nBits16 = 4;
const float constellation16[16][2] = {
    {-3, 3}, {-1, 3}, {1, 3}, {3, 3},
    {-3, 1}, {-1, 1}, {1, 1}, {3, 1},
    {-3, -1}, {-1, -1}, {1, -1}, {3, -1},
    {-3, -3}, {-1, -3}, {1, -3}, {3, -3}
};

#endif
