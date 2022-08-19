#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../inc/filters_prototypes.h"
#include"../inc/structures.h"

/************************************************************************************
 * Functions saves the outline of the image to the structure                        
 * PRE:Correctly saved image and correct value of colour variable
 * POST:Correctly saved processed image in the structure
 * \param[in] image pointer to the data structure
 * \param[in] colour informs about the chosen colour
 * \return number of read pixels						   
 ************************************************************************************/

int outline(s_image *image, int colour) {
  int i,j,a,b; 
  switch(colour)
  {
    case 0:
    {/*Red/gray*/  
      int (*pixels)[image->x_dimension]; /*Variable allowing to move through the pixels array*/
      pixels = (int (*)[image->x_dimension]) image->pixels_GreyRed;
  
    /*Saving the outline in the structure*/
      for (i=0;i<(image->y_dimension);i++) 
      { /*Comparisons for all the columns and rows except the last ones*/
        for (j=0;j<(image->x_dimension);j++)
        {
	        a = pixels[i][j] - pixels[i][j+1];  /*horizontal comparison*/
	        if (a<0)
          {  
	          a = -1 * a; /* absolute value*/
	        }
	        b = pixels[i][j] - pixels[i+1][j]; /*vertical comparison*/
	        if (b<0)
          {
	          b = -1 * a; /* absolute value*/
	        }
	        pixels[i][j] = a + b; /*saving to the pixels array*/
	        if (pixels[i][j] > (image->shades_number))
          { 
	          pixels[i][j] = (image->shades_number); /* out of bounds prevention*/
	        }	    
        }
      }
      break;
    }
    case 1:
    {/*Green pixels - just like for the red ones (way too much code repetition, to be fixed)*/
      int (*pixels)[image->x_dimension]; 
      pixels = (int (*)[image->x_dimension]) image->pixels_Green;
  

      for (i=0;i<(image->y_dimension);i++) 
      { 
        for (j=0;j<(image->x_dimension);j++)
        {
	        a = pixels[i][j] - pixels[i][j+1];  
	        if (a<0)
          {  
	          a = -1 * a; 
	        }
	        b = pixels[i][j] - pixels[i+1][j]; 
	        if (b<0)
          {
	          b = -1 * a; 
	        }
	        pixels[i][j] = a + b; 
	        if (pixels[i][j] > (image->shades_number))
          { 
	          pixels[i][j] = (image->shades_number); 
	        }	    
        }
      }
      break;
    }
    case 2:
    {/*Blue pixels - as above*/
      int (*pixels)[image->x_dimension]; 
      pixels = (int (*)[image->x_dimension]) image->pixels_Blue;
  
      for (i=0;i<(image->y_dimension);i++)
      { 
        for (j=0;j<(image->x_dimension);j++)
        {
	        a = pixels[i][j] - pixels[i][j+1];  
	        if (a<0)
          {  
	          a = -1 * a; 
	        }
	        b = pixels[i][j] - pixels[i+1][j];
	        if (b<0)
          {
	          b = -1 * a; 
	        }
	        pixels[i][j] = a + b; 
	        if (pixels[i][j] > (image->shades_number))
          { 
	          pixels[i][j] = (image->shades_number); 
	        }	    
        }
      }
      break;
    }    
    case 3:{/*Grayscale conversion*/
      int (*pixels_n)[image->x_dimension]; /*Variables for each colour*/
      pixels_n = (int (*)[image->x_dimension]) image->pixels_Blue;
      int (*pixels_z)[image->x_dimension]; 
      pixels_z = (int (*)[image->x_dimension]) image->pixels_Green;
      int (*pixels_c)[image->x_dimension]; 
      pixels_c = (int (*)[image->x_dimension]) image->pixels_GreyRed;

    /*Saving 3 outlines in the structure*/
      for (i=0;i<(image->y_dimension);i++)
      { 
        for (j=0;j<(image->x_dimension);j++)
        {
	        a = pixels_n[i][j] - pixels_n[i][j+1];  
	        if (a<0)
          {  
	          a = -1 * a; 
	        }
	        b = pixels_n[i][j] - pixels_n[i+1][j];
	        if (b<0)
          {
	          b = -1 * a; 
	        }
	        pixels_n[i][j] = a + b; /*saving to the blue pixels array*/
	        if (pixels_n[i][j] > (image->shades_number))
          { 
	          pixels_n[i][j] = (image->shades_number); 
	        }	    
        }
      }
      for (i=0;i<(image->y_dimension);i++)
      { 
        for (j=0;j<(image->x_dimension);j++)
        {
	        a = pixels_z[i][j] - pixels_z[i][j+1];  
	        if (a<0)
          {  
	          a = -1 * a;
	        }
	        b = pixels_z[i][j] - pixels_z[i+1][j]; 
	        if (b<0)
          {
	          b = -1 * a; 
	        }
	        pixels_z[i][j] = a + b; /*saving to the green pixels array*/
	        if (pixels_z[i][j] > (image->shades_number))
          { 
	          pixels_z[i][j] = (image->shades_number); 
	        }	    
        }
      }    
      for (i=0;i<(image->y_dimension);i++) 
      { 
        for (j=0;j<(image->x_dimension);j++) 
        {
	        a = pixels_c[i][j] - pixels_c[i][j+1];  
	        if (a<0)
          {  
	          a = -1 * a;
	        }
	        b = pixels_c[i][j] - pixels_c[i+1][j]; 
	        if (b<0)
          {
	          b = -1 * a; 
	        }
	        pixels_c[i][j] = a + b; /*saving to the red pixels array*/
	        if (pixels_c[i][j] > (image->shades_number))
          { 
	          pixels_c[i][j] = (image->shades_number); 
	        }	    
        }
      }
      break;
    }
  }   
  image->x_dimension = (image->x_dimension) - 1; /*saving decremented dimensions*/
  image->y_dimension = (image->y_dimension) - 1;
  /*Decremention is necessary as the last rows and columns could not be compared with anything and did not change*/
  return (image->x_dimension * image->y_dimension) ; /* return the number of read pixels */
}

/************************************************************************************
 * Function makes the negative of the image and saves it in the structure
 * PRE:Correctly saved image and correct value of colour variable
 * POST:Correctly saved processed image in the structure
 * \param[in] image pointer to the data structure
 * \param[in] colour informs about the chosen colour
 * \return number of read pixels						   
 ************************************************************************************/

int negative(s_image *image, int colour) {
  int i,j;
  switch(colour)
  {
    case 0:
    {/*Red/gray pixels*/
      int (*pixels)[image->x_dimension]; 
      pixels = (int(*)[image->x_dimension]) image->pixels_GreyRed;
      /* Saving the negative*/
      for (i=0;i<image->y_dimension;i++)
      {
        for (j=0;j<image->x_dimension;j++)
        {
        pixels[i][j] = (image->shades_number) - pixels[i][j]; /*Reversing the colour and saving*/    
        }   
      }
      break;
    }     
    case 1:
    {/*Green pixels - as above (unnecessary repetition, again - to be fixed)*/   
      int (*pixels)[image->x_dimension]; 
      pixels = (int(*)[image->x_dimension]) image->pixels_Green;
      for (i=0;i<image->y_dimension;i++)
      {
        for (j=0;j<image->x_dimension;j++)
        {
          pixels[i][j] = (image->shades_number) - pixels[i][j]; 
        }   
      }
      break;
    }
    case 2:
    {/*Blue - as above*/   
      int (*pixels)[image->x_dimension]; 
      pixels = (int(*)[image->x_dimension]) image->pixels_Blue;
      for (i=0;i<image->y_dimension;i++)
      {
        for (j=0;j<image->x_dimension;j++)
        {
          pixels[i][j] = (image->shades_number) - pixels[i][j];   
        }   
      }
      break;
    }
    case 3:
    {/*Grayscale conversion*/   
      int (*pixels_c)[image->x_dimension]; /*Variable for each colour array */
      pixels_c = (int(*)[image->x_dimension]) image->pixels_GreyRed;
    
      int (*pixels_z)[image->x_dimension]; 
      pixels_z = (int(*)[image->x_dimension]) image->pixels_Green;
    
      int (*pixels_n)[image->x_dimension]; 
      pixels_n = (int(*)[image->x_dimension]) image->pixels_Blue;

      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++)
        {       
          pixels_c[i][j] = (image->shades_number)  - pixels_c[i][j]; 
          pixels_z[i][j] = (image->shades_number)  - pixels_z[i][j]; 
          pixels_n[i][j] = (image->shades_number)  - pixels_n[i][j]; 
        }   
      }
      break;
    }
  }   
  return image->x_dimension*image->y_dimension; /*number of read pixels*/
}


/************************************************************************************
 * Function makes the tresholding operation     	       	                                                    
 * PRE:Correctly saved image, correct values of colour and treshold_value
 * POST:Correctly processed image
 * \param[in] colour informs about the chosen colour
 * \param[in] treshold_percent_value        
 * \param[in] image pointer to the image structure                               
 * \return number of read pixels					    
 ************************************************************************************/

int treshold(s_image *image, float treshold_percent_value, int colour) {
  int i,j;

 /*Calculating the treshold grayscale value */
  int trsh = (int) (((treshold_percent_value)/100) * (image->shades_number));

  switch(colour)
  {
    case 0:
    {/*Red/gray pixels*/
      int (*pixels)[image->x_dimension]; 
      pixels = (int(*)[image->x_dimension]) image->pixels_GreyRed; 
      /* Saving while taking the treshold value into account */
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          if (pixels[i][j] <= trsh)
          { /* Comparing with treshold*/
            pixels[i][j] = 0; /*Assigning to the minimum grayscale*/
          }
          else
          {
            pixels[i][j] = (image->shades_number); /*To the maximum*/
          }
        }
      }
      break;
    }
    case 1:
    {/*Green pixels*/
      int (*pixels)[image->x_dimension];
      pixels = (int(*)[image->x_dimension]) image->pixels_Green; 
      
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          if (pixels[i][j] <= trsh)
          { 
            pixels[i][j] = 0; 
          }
          else
          {
            pixels[i][j] = (image->shades_number); 
          }
        }
      }
    break;
    }
    case 2:
    {/* I'm blue daba Da ba dee da ba di Da ba dee da ba di */
      int (*pixels)[image->x_dimension]; 
      pixels = (int(*)[image->x_dimension]) image->pixels_Blue; 
      
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          if (pixels[i][j] <= trsh)
          { 
            pixels[i][j] = 0; 
          }
          else
          {
            pixels[i][j] = (image->shades_number); 
          }
        }
      }
    break;
    }
    case 3:
    {/*Grayscale conversion*/
      int (*pixels_n)[image->x_dimension]; 
      pixels_n = (int(*)[image->x_dimension]) image->pixels_Blue;
      int (*pixels_c)[image->x_dimension]; 
      pixels_c = (int(*)[image->x_dimension]) image->pixels_GreyRed;
      int (*pixels_z)[image->x_dimension]; 
      pixels_z = (int(*)[image->x_dimension]) image->pixels_Green;
   
    /*Comparisons for each colour */
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          if (pixels_n[i][j] <= trsh)
          { 
            pixels_n[i][j] = 0; 
          }
          else
          {
            pixels_n[i][j] = (image->shades_number); 
          }
      
          if (pixels_z[i][j] <= trsh)
          { 
            pixels_z[i][j] = 0; 
          }
          else
          {
            pixels_z[i][j] = (image->shades_number); 
          }
      
          if (pixels_c[i][j] <= trsh)
          { 
            pixels_c[i][j] = 0; 
          }
          else
          {
            pixels_c[i][j] = (image->shades_number); 
          }
      
        }
      }
      break;
    }    
  }
  return image->x_dimension*image->y_dimension; /* Return the number of read pixels */
}
