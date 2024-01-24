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

	/// LOADING TEXT FILE
    char *filename = "dataOut.txt";
    char *outname = "2dataOut.txt";
    int inputLen = checkFileLenghtLine(filename);
    kiss_fft_cpx *input =(kiss_fft_cpx *)malloc((inputLen) * sizeof(kiss_fft_cpx));
    loadFileCpx(input,filename);



    /// Parametry dla OFDM
    	float bOFDMch = floor((float)bandWidth/(float)noSubcarriers);
    	float nOFDMch = floor((float)sampFreq/(float)bOFDMch);

    	float guardSamples = ceil(nOFDMch/(float)cpIndex);
    	int nZeros = (nOFDMch - noSubcarriers)/2;
    	int cp = guardSamples;
    	int packetsNum = ceil((float)inputLen/(((float)noSubcarriers) + 2*nZeros + cp))-1;
    /// Koniec parametrow

    	printf("packetsNum: %d ", packetsNum);

    	kiss_fft_cpx **OFDMbaseband = (kiss_fft_cpx **)malloc(packetsNum*sizeof(kiss_fft_cpx*));
    	    for (int i = 0; i < packetsNum; i++){
    	    	OFDMbaseband[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2*nZeros + cp) * sizeof(kiss_fft_cpx));
    	    }

    	    for(int i = 0; i < packetsNum; i++){
    	    	for(int j = 0; j < noSubcarriers +2*nZeros + cp; j++){
    	    		if(j+i*noSubcarriers<inputLen){
    	    			OFDMbaseband[i][j].r=input[(i*noSubcarriers+i*2*nZeros+i*cp)+j].r;
    	    			OFDMbaseband[i][j].i=input[(i*noSubcarriers+i*2*nZeros+i*cp)+j].i;
    	    		}
    	    		else
    	    			break;
    	    	}
    	    }

    	    kiss_fft_cpx **deguarded = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx*));
    	    for (int i = 0; i < packetsNum; i++) {
    	        deguarded[i] = (kiss_fft_cpx *)malloc((noSubcarriers + 2 * nZeros) * sizeof(kiss_fft_cpx));
    	    }

    	    // Removing CyclePrefix
    	       for (int i = 0; i < packetsNum; i++){
    	       	for (int j = 0; j <noSubcarriers + 2 * nZeros; j++){
    	       		deguarded[i][j].r = OFDMbaseband[i][cp + j].r;
    	       		deguarded[i][j].i = OFDMbaseband[i][cp + j].i;
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
    	               fftInput[i][j].r = deguarded[i][j].r;
    	               fftInput[i][j].i = deguarded[i][j].i;
    	           }
    	           kiss_fft(cfg_inv, fftInput[i], fftOutput[i]);
    	       }

    	       kiss_fft_cpx **trainBuffer = (kiss_fft_cpx **)malloc(packetsNum * sizeof(kiss_fft_cpx *));
    	       for (int i = 0; i < packetsNum; i++) {
    	           	           trainBuffer[i] = (kiss_fft_cpx *)malloc((noSubcarriers) * sizeof(kiss_fft_cpx));
    	           	       }


    	       fftShift(fftOutput, packetsNum, noSubcarriers + 2*nZeros);
    	       rmZeros(fftOutput, trainBuffer, packetsNum, noSubcarriers, nZeros);


    	       float *trainSequence = (float *)malloc(packetsNum*noSubcarriers*sizeof(float *));

    	       for(int i = 0; i < packetsNum; i++){
    	       	for(int j = 0; j < noSubcarriers; j++){
    	       			trainSequence[j+i*noSubcarriers] = trainBuffer[i][j].r;
    	       	}
    	       }

    	       float *output = (float *)malloc(packetsNum*noSubcarriers*sizeof(float *));
    	       bpskDemodulation(1, trainSequence, output, noSubcarriers*packetsNum);

    	       ///DEBUG
    	       for(int i = 0; i < packetsNum; i++)
    	       {
    	          	for(int j = 0; j < noSubcarriers; j++)
    	          	{
    	          		printf("|%d - %d: ", i, j);
    	          		printf("%f ", output[i*noSubcarriers + j]);
    	          	}
    	       }

    	       saveFileBin(output, outname, packetsNum, noSubcarriers);

    	       /// FREE ALOCATED MEMORY
    	       free(input);
    	       for (int i = 0; i < packetsNum; i++) {
    	           free(OFDMbaseband[i]);
    	       }
    	       free(OFDMbaseband);
    	       for (int i = 0; i < packetsNum; i++) {
    	           free(deguarded[i]);
    	       }
    	       free(deguarded);
    	       for (int i = 0; i < packetsNum; i++) {
    	           free(fftInput[i]);
    	           free(fftOutput[i]);
    	       }
    	       free(fftInput);
    	       free(fftOutput);
    	       kiss_fft_free(cfg_inv);
    	       for (int i = 0; i < packetsNum; i++) {
    	           free(trainBuffer[i]);
    	       }
    	       free(trainBuffer);
    	       free(trainSequence);
    	       free(output);


	return 0;
}

