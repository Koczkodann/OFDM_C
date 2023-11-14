/*
 * FileControl.h
 *
 *  Created on: 14 Nov 2023
 *      Author: Pandrako
 */

#ifndef LIB_FILECONTROL_H_
#define LIB_FILECONTROL_H_
#include <stddef.h>
#include <stdio.h>

int checkFileLenght(char *filename);
void loadFile(int *output, char *filename);
void saveFile(float *input, char *filename);


#endif /* LIB_FILECONTROL_H_ */
