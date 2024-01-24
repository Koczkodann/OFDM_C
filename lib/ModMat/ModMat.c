#include "ModMat.h"
void fftShift(kiss_fft_cpx **input, int size1, int size2) {
    kiss_fft_cpx temp[size2];

    int shift = size2/2;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2 - shift; j++) {
            temp[j].r = input[i][j + shift].r;
            temp[j].i = input[i][j + shift].i;
        }

        for (int j = size2 - shift, k = 0; j < size2; j++, k++) {
            temp[j].r = input[i][k].r;
            temp[j].i = input[i][k].i;
        }

        for (int j = 0; j < size2; j++) {
            input[i][j].r = temp[j].r;
            input[i][j].i = temp[j].i;
        }
    }
}

void zeros(kiss_fft_cpx **input, kiss_fft_cpx **output, int size1, int size2, int nZeros) {


    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < nZeros; j++) {
            output[i][j].r = 0;
            output[i][j].i = 0;
        }
    }


    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            output[i][j+nZeros].r = input[i][j].r;
            output[i][j+nZeros].i = input[i][j].i;
        }
    }


    for (int i = size1; i < size1; i++) {
        for (int j = 0; j < nZeros; j++) {
            output[i][j+nZeros+size2].r = 0;
            output[i][j+nZeros+size2].i = 0;
        }
    }
}

void rmZeros(kiss_fft_cpx **input, kiss_fft_cpx **output, int size1, int size2, int nZeros){

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            output[i][j].r = input[i][j+nZeros].r;
            output[i][j].i = input[i][j+nZeros].i;
        }
    }
}

