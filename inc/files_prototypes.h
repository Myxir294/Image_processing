#ifndef FILES_H
#define FILES_H
#define LINE_LENGTH 1024
#include "structures.h"

int save (FILE*, s_image*, int, int);
int read (FILE*, s_image*);
void display (char*);

#endif
