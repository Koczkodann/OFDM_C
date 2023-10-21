#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415

//BPSK (QAM2)
const int qamNumber = 2;
const int nBits = 1;
const float constellation[2][2] = {
    {-1, 0}, {1, 0}
};

//QAM16
/*
int qamNumber = 16;
int nBits = 4;
const float constellation[16][2] = {
    {-3, 3}, {-1, 3}, {1, 3}, {3, 3},
    {-3, 1}, {-1, 1}, {1, 1}, {3, 1},
    {-3, -1}, {-1, -1}, {1, -1}, {3, -1},
    {-3, -3}, {-1, -3}, {1, -3}, {3, -3}
};*/

//MODULACJA QAM
void qamModulation(int* input, float* outputSignal, int inputNum) {
    int i, j;
    float I, Q;
    
    for (i = 0; i < inputNum; i++) {
        I = constellation[input[i]][0];
        Q = constellation[input[i]][1];
        outputSignal[i] = I * cos(2 * PI * i / inputNum) + Q * sin(2 * PI * i / inputNum);
    }
}

int main() {
    //int input[] = {7, 12, 2, 4, 9, 15, 6, 1}; //QAM 16
    int input[] = {0, 1, 0, 1, 1, 1, 0, 1};    //QAM2
    int inputNum = sizeof(input) / sizeof(input[0]);

    float outputSignal[inputNum];
    qamModulation(input, outputSignal, inputNum);

    // Print the modulated signal
    printf("QAM modulation:\n");
    for (int i = 0; i < inputNum; i++) {
        printf("%f ", outputSignal[i]);
    }

    return 0;
}