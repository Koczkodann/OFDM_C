#include "../lib/QAM/QAM.h"
#include "../lib/FileControl/FileControl.h"
#include "../lib/kissfft/kiss_fft.h"

//funkcje dodatkowe
void fftShift(float *array,int lenght, int shift);
float** zeros(float **input, int size1, int size2, int nZeros);

/// Parametry modulacji
int bandWidth = 5000;  //szerokosc pasma
int sampFreq = 96000;  //czestotliwosc probkowania
int noSubcarriers = 64; //liczba podnosnych dla OFDM
int cpIndex = 5; //wspolczynnik dlugosci cyklicznego prefiksu


int main() {

    char *filename = "data.txt";
    float input[checkFileLenght(filename)];
    loadFile(input,filename);


    int inputLen = sizeof(input) / sizeof(input[0]);

	/// Parametry dla OFDM
	float bOFDMch = floor((float)bandWidth/(float)noSubcarriers);
	float nOFDMch = floor((float)sampFreq/(float)bOFDMch);

	float guardSamples = ceil(nOFDMch/(float)cpIndex);
	float packetsNum = (float)inputLen/(float)noSubcarriers;
	float nZeros = (nOFDMch - noSubcarriers)/2;
	float cp = guardSamples;
	/// Koniec parametrow

	//Modulacja QAM
    float trainSequence[inputLen];
    bpskModulation(1, input, trainSequence, inputLen);
    //Kooniec modulacji QAM


    int buffNumber = ceil((float)inputLen/(float)noSubcarriers);

    float **trainBuffer = (float **)malloc(buffNumber*sizeof(float*));
    for (int i = 0; i < buffNumber; i++){
    	trainBuffer[i] = (float *)malloc(noSubcarriers * sizeof(float));
    }

    for(int i = 0; i < buffNumber; i++){
    	for(int j = 0; j < noSubcarriers; j++){
    		if(j+i*noSubcarriers<inputLen){
    			trainBuffer[i][j]=trainSequence[j+i*noSubcarriers];
    			//printf("%f ", trainBuffer[i][j]);
    			//printf("%d ", i*64+j);
    		}
    		else
    			break;
    	}
    }
    float **trainBuffer2 = zeros(trainBuffer, buffNumber, noSubcarriers, nZeros);



    return 0;
}

void fftShift(float *array, int lenght, int shift) {
    int temp[lenght];

    shift = (shift % lenght + lenght) % lenght;

    for (int i = 0; i < lenght - shift; i++) {
        temp[i] = array[i + shift];
    }

    for (int i = lenght - shift, j = 0; i < lenght; i++, j++) {
        temp[i] = array[j];
    }

    for (int i = 0; i < lenght; i++) {
        array[i] = temp[i];
    }
}

float** zeros(float **input, int size1, int size2, int nZeros) {
    // Calculate the new size of the matrix
    int newSize1 = size1 + nZeros + nZeros;

    // Create a new 2D array with the calculated size
    int **output = (int **)malloc(newSize1 * sizeof(int*));
    for (int i = 0; i < newSize1; i++) {
        output[i] = (int *)malloc(size2 * sizeof(int));
    }

    // Add zeros at the beginning
    for (int i = 0; i < nZeros; i++) {
        for (int j = 0; j < size2; j++) {
            output[i][j] = 0;
        }
    }

    // Copy the original matrix elements
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            output[i + nZeros][j] = input[i][j];
        }
    }

    // Add zeros at the end
    for (int i = size1 + nZeros; i < newSize1; i++) {
        for (int j = 0; j < size2; j++) {
            output[i][j] = 0;
        }
    }

    return output;
}
