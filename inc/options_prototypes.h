#ifndef OPTIONS_H
#define OPTIONS_H
#define V_OK 0                   /* value indicating no errors */

#define E_OPTION -1    /* error codes for options checking*/
#define E_NAME   -2
#define E_VALUE  -3
#define E_FILE   -4
#define E_COLOUR -5
#define MENU 1
#include "structures.h"

void initialize_options(execution_options*);
int process_options(int,char**,execution_options*);

#endif
