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
    char *filename = "dataOut.txt";
    char *outname = "2dataOut.txt";
    kiss_fft_cpx *input =(kiss_fft_cpx *)malloc((checkFileLenght(filename)) * sizeof(kiss_fft_cpx));
    loadFileCpx(input,filename);

    int inputLen = sizeof(input) / sizeof(input[0]);

    /// Parametry dla OFDM
    	float bOFDMch = floor((float)bandWidth/(float)noSubcarriers);
    	float nOFDMch = floor((float)sampFreq/(float)bOFDMch);

    	float guardSamples = ceil(nOFDMch/(float)cpIndex);
    	int nZeros = (nOFDMch - noSubcarriers)/2;
    	int cp = guardSamples;
    	float packetsNum = ceil((float)inputLen/((float)noSubcarriers)+2*nZeros+cp);
    /// Koniec parametrow

    	kiss_fft_cpx **OFDMbaseband = (kiss_fft_cpx **)malloc(packetsNum*sizeof(kiss_fft_cpx*));
    	    for (int i = 0; i < packetsNum; i++){
    	    	OFDMbaseband[i] = (float *)malloc((noSubcarriers + 2*nZeros) * sizeof(kiss_fft_cpx));
    	    }

    	    for(int i = 0; i < packetsNum; i++){
    	    	for(int j = 0; j < noSubcarriers; j++){
    	    		if(j+i*noSubcarriers<inputLen){
    	    			OFDMbaseband[i][j]=input[j+i*noSubcarriers];
    	    		}
    	    		else
    	    			break;
    	    	}
    	    }

    	    kiss_fft_cpx **guarded = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx*));
    	    for (int i = 0; i < packetsNum; i++) {
    	        guarded[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
    	    }

    	    // Removing CyclePrefix //TODO
    	       for (int i = 0; i < packetsNum; i++){
    	       	for (int j = 0; j <noSubcarriers + 2 * nZeros + cp; j++){
    	       		if(j <= cp){
    	       		guarded[i][j].r = OFDMbaseband[i][noSubcarriers + 2 * nZeros - cp + j].r;
    	       		guarded[i][j].i = OFDMbaseband[i][noSubcarriers + 2 * nZeros - cp + j].i;
    	       		}
    	       		if(j > cp){
    	       		guarded[i][j].r = OFDMbaseband[i][j - cp].r;
    	       		guarded[i][j].i = OFDMbaseband[i][j - cp].i;
    	       		}
    	       	}
    	       }

    	       // Konfiguracja Kissfft
    	       kiss_fft_cfg cfg_inv = kiss_fft_alloc(noSubcarriers + 2 * nZeros, 0, NULL, NULL);

    	       // Alokacja pamiêci
    	       kiss_fft_cpx **fftInput = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx *));
    	       kiss_fft_cpx **fftOutput = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx *));
    	       for (int i = 0; i < packetsNum; i++) {
    	           fftInput[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
    	           fftOutput[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
    	       }

    	       // FFT
    	       for (int i = 0; i < packetsNum; i++) {
    	           for (int j = 0; j < noSubcarriers + 2 * nZeros; j++) {
    	               fftInput[i][j].r = OFDMbaseband[i][j].r;
    	               fftInput[i][j].i = OFDMbaseband[i][j].i;
    	           }
    	           kiss_fft(cfg_inv, fftInput[i], fftOutput[i]);
    	       }

    	       fftShift(fftOutput, packetsNum, noSubcarriers + 2*nZeros);
    	       rmZeros(fftOutput, packetsNum, noSubcarriers, nZeros);

    	       printf("Nzeros: %d  ", nZeros);

    	       for(int i = 0; i < packetsNum; i++)
    	       {
    	          	for(int j = 0; j < noSubcarriers + 2*nZeros + cp; j++)
    	          	{
    	          		printf("|%d - %d: ", i, j);
    	          		printf("%f ", fftOutput[i][j].r);
    	          	}
    	       }

    	       //bpskdemodulation(1, fftOutput, outData, )


	return 0;
}

