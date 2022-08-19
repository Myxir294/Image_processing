#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "stdio.h"
#include "stdlib.h"

/*structure to contain images*/
typedef struct {
  int x_dimension, y_dimension, shades_number; /*images parameters*/
  void *pixels_GreyRed; /*tables for pixels - void, as the length (type) is unknown yet (dynamic)*/
  void *pixels_Green;
  void *pixels_Blue;
  int type; /*image type*/
  } s_image;

/* structure to process executution arguments */
typedef struct {
  FILE *input_file, *output_file; 
  int negative, tresholding, outlining, display, colour;/* args */
  float treshold_value; /* treshold value for tresholding function */
  int colour_value; /* chosen colour*/
  char *name; /* to display function*/
} execution_options;

#endif
