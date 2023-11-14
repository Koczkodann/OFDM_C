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
			numChar++;
		}
	}

	fclose(in);
	return numChar+1;
}

void loadFile(int *output, char *filename)
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
			while(ch = fgetc(in) != EOF)
			{
				output[numChar]=ch;
				numChar++;
			}
		}
	fclose(in);
}

void saveFile(float *input, char *filename){


}
