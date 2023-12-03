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
	return numChar+1;
}

void loadFile(float *output, char *filename)
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

void saveFile(float *input, char *filename){


}
