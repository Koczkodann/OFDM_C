#include "FileControl.h"

int checkFileLenght(char *filename)
{
	FILE *in = fopen(filename, "r");
	int numChar = 0;

	if(in == NULL)
	{
		printf("Error: could not open file: %s", filename);
	}
	else
	{
		while(fgetc(in) != EOF){
			numChar = numChar + 1;
		}
	}

	fclose(in);
	return numChar;
}

int checkFileLenghtLine(char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1; // or handle the error as needed
    }

    int count = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    fclose(file);
    return count;
}

void loadFileBin(float *output, char *filename)
{
	char ch;
	int numChar = 0;
	FILE *in = fopen(filename, "r");

	if(in == NULL)
		{
			printf("Error: could not open file: %s", filename);
		}
		else
		{
			while((ch = fgetc(in)) != EOF)
			{
				output[numChar]=ch - '0';
				numChar = numChar + 1;
			}
		}
	fclose(in);
}

void loadFileCpx(kiss_fft_cpx *input, char *filename)
{
	char ch[100];
	int numChar = 0;
	FILE *in = fopen(filename, "r");

	if(in == NULL)
	{
		printf("Error: could not open file: %s", filename);
	}
	else
	{
		while(fgets(ch, sizeof(ch),in) != NULL){
			double real, imag;
			if (sscanf(ch, "%lf +i%lf", &real, &imag) == 2) {
				input[numChar].r = real;
				input[numChar].i = imag;
				numChar++;
		}else {
		    fprintf(stderr, "Error parsing line: %s\n", ch);
		}
	}

}
}

void saveFile(kiss_fft_cpx **input, char *filename,int packetsNum, int lenght){
	FILE *in = fopen(filename, "w");

	if(in == NULL)
	{
		printf("Error: could not open file: %s", filename);
	}
	else
	{
		for(int i = 0; i < packetsNum; i++)
		{
			for(int j = 0; j < lenght; j++)
			{
				fprintf(in, "%f +i%f\n", input[i][j].r, input[i][j].i);
			}
		}
	}
	fclose(in);
}

void saveFileBin(float *input, char *filename, int packetsNum, int lenght){
	FILE *in = fopen(filename, "w");

	if(in == NULL)
	{
		printf("Error: could not open file: %s", filename);
	}
	else
	{
		for(int i = 0; i < packetsNum*lenght; i++)
		{
			fprintf(in, "%d", (int)input[i]);
		}
	}
	fclose(in);
}
