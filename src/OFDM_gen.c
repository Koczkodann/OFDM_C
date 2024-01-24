#include "../lib/QAM/QAM.h"
#include "../lib/FileControl/FileControl.h"
#include "../lib/kissfft/kiss_fft.h"
#include "../lib/ModMat/ModMat.h"

/// Parametry modulacji
int bandWidth = 5000;  //szerokosc pasma
int sampFreq = 96000;  //czestotliwosc probkowania
int noSubcarriers = 64; //liczba podnosnych dla OFDM
int cpIndex = 5; //wspolczynnik dlugosci cyklicznego prefiksu


int main() {

	/// LOADING BINARY FILE
    char *filename = "data.txt";
    char *outname = "dataOut.txt";
    float *input = malloc(checkFileLenght(filename) * sizeof(float));
    loadFileBin(input, filename);

    int inputLen = checkFileLenght(filename);

	/// Parametry dla OFDM
	float bOFDMch = floor((float)bandWidth/(float)noSubcarriers);
	float nOFDMch = floor((float)sampFreq/(float)bOFDMch);

	float guardSamples = ceil(nOFDMch/(float)cpIndex);
	int nZeros = (nOFDMch - noSubcarriers)/2;
	int cp = guardSamples+1;
	float packetsNum = ceil((float)inputLen/(float)noSubcarriers);
	/// Koniec parametrow


	// Modulacja QAM
    float *trainSequence = malloc(inputLen * sizeof(float));
    bpskModulation(1, input, trainSequence, inputLen);
    // Koniec modulacji QAM


    kiss_fft_cpx **trainBuffer = (kiss_fft_cpx **)malloc(packetsNum*sizeof(kiss_fft_cpx*));
    for (int i = 0; i < packetsNum; i++){
    	trainBuffer[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2*nZeros) * sizeof(kiss_fft_cpx));
    }

    for(int i = 0; i < packetsNum; i++){
    	for(int j = 0; j < noSubcarriers; j++){
    		if(j+i*noSubcarriers<inputLen){
    			trainBuffer[i][j].r = trainSequence[j+i*noSubcarriers];
    		}
    		else
    			break;
    	}
    }


	kiss_fft_cpx **spectrumTable = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx*));
    for (int i = 0; i < packetsNum; i++) {
        spectrumTable[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2*nZeros) * sizeof(kiss_fft_cpx));
    }

    zeros(trainBuffer, spectrumTable, packetsNum, noSubcarriers, nZeros);
    fftShift(spectrumTable, packetsNum, noSubcarriers + 2*nZeros);

    // Konfiguracja IFFT
    kiss_fft_cfg cfg_inv = kiss_fft_alloc(noSubcarriers + 2 * nZeros, 1, NULL, NULL);

    // Alokacja pamiêci
    kiss_fft_cpx **ifftInput = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx *));
    kiss_fft_cpx **ifftOutput = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx *));
    for (int i = 0; i < packetsNum; i++) {
        ifftInput[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
        ifftOutput[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
    }

    // IFFT
    for (int i = 0; i < packetsNum; i++) {
        for (int j = 0; j < noSubcarriers + 2 * nZeros; j++) {
            ifftInput[i][j].r = spectrumTable[i][j].r;
            ifftInput[i][j].i = spectrumTable[i][j].i;
        }
        kiss_fft(cfg_inv, ifftInput[i], ifftOutput[i]);
    }


    /// KONFIGURACJE PREFIKSU CYKILCZNEGO
    kiss_fft_cpx **guarded = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx*));
    for (int i = 0; i < packetsNum; i++) {
        guarded[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros + cp) * sizeof(kiss_fft_cpx));
    }

    /// DODANIE PREFIXU CYKLICZNEGO i wyskalowanie w stosunku do matlab
    for (int i = 0; i < packetsNum; i++){
    	for (int j = 0; j <noSubcarriers + 2 * nZeros + cp; j++){
    		if(j <= cp){
    		guarded[i][j].r = ifftOutput[i][noSubcarriers + 2 * nZeros - cp + j].r/1232;
    		guarded[i][j].i = ifftOutput[i][noSubcarriers + 2 * nZeros - cp + j].i/1232;
    		}
    		if(j > cp){
    		guarded[i][j].r = ifftOutput[i][j - cp].r/1232;
    		guarded[i][j].i = ifftOutput[i][j - cp].i/1232;
    		}
    	}
    }

    /// ZAPIS DO PLIKU WYJŒCIOWEGO
    saveFile(guarded, outname, packetsNum, noSubcarriers + 2 * nZeros + cp+1);


    //DEBUG
    /*
    printf("Nzeros: %d  ", nZeros);

    for(int i = 0; i < packetsNum; i++)
    {
       	for(int j = 0; j < noSubcarriers + 2*nZeros + cp; j++)
       	{
       		printf("|%d - %d: ", i, j);
       		printf("%f ", ifftOutput[i][j].r);
       	}
    }*/

    /// FREEING ALL ALOCATED MEMORY
    free(input);
    free(trainSequence);
    for (int i = 0; i < packetsNum; i++) {
        free(trainBuffer[i]);
    }
    free(trainBuffer);
    for (int i = 0; i < packetsNum; i++) {
        free(spectrumTable[i]);
    }
    free(spectrumTable);
    for (int i = 0; i < packetsNum; i++) {
        free(ifftInput[i]);
        free(ifftOutput[i]);
    }
    free(ifftInput);
    free(ifftOutput);
    for (int i = 0; i < packetsNum; i++) {
        free(guarded[i]);
    }
    free(guarded);
    kiss_fft_free(cfg_inv);

    return 0;
}

