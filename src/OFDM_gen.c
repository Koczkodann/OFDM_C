#include "../lib/QAM.h"

/// Parametry modulacji
int bandWidth = 5000;  //szerokosc pasma
int sampFreq = 96000;  //czestotliwosc probkowania
int noSubcarriers = 64; //liczba podnosnych dla OFDM
int cpIndex = 5; //wspolczynnik dlugosci cyklicznego prefiksu


int main() {
	/// Dane wejsciowe
    int input[] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};    //QAM2
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
    qamModulation(1, input, trainSequence, inputLen);
    //Kooniec modulacji QAM


    int buffNumber = ceil((float)inputLen/(float)noSubcarriers);
    float trainBuffer[(int)buffNumber][noSubcarriers];

    for(int i = 0; i < buffNumber; i++){
    	for(int j = 0; j < noSubcarriers; j++){
    		if(j+i*noSubcarriers<inputLen){
    			trainBuffer[i][j]=trainSequence[j+i*noSubcarriers];
    			//printf("%f ", trainBuffer[i][j]);
    		}
    		else
    			break;
    	}
    }

    // Print the modulated signal
    printf("QAM modulation:\n");
    for (int i = 0; i < inputLen; i++) {
        printf("%f ", trainBuffer[0][i]);
    }

    return 0;
}
