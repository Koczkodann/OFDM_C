#ifndef LIB_FILECONTROL_H_
#define LIB_FILECONTROL_H_
#include <stddef.h>
#include <stdio.h>
#include "../kissfft/kiss_fft.h"

int checkFileLenght(char *filename);
void loadFileBin(float *output, char *filename);
void loadFileCpx(kiss_fft_cpx **input, char *filename);
void saveFile(kiss_fft_cpx **input, char *filename, int packetsNum, int lenght);


#endif /* LIB_FILECONTROL_H_ */
