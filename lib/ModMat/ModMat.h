#ifndef LIB_MODMAT_H_
#define LIB_MODMAT_H_
#include <stddef.h>
#include <stdio.h>
#include "../kissfft/kiss_fft.h"

void fftShift(kiss_fft_cpx **input, int size1, int size2);
void zeros(kiss_fft_cpx **input, kiss_fft_cpx **output, int size1, int size2, int nZeros);
void rmZeros(kiss_fft_cpx **input, kiss_fft_cpx **output, int size1, int size2, int nZeros);

#endif /* LIB_FILECONTROL_H_ */
