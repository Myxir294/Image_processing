#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../inc/files_prototypes.h"
#include"../inc/structures.h"

/************************************************************************************
 * Function loads the image from the file or stdin to the structure
 *										    
 * PRE: none									    
 * POST: image correctly saved in the structure					    
 * \param[in] input_file pointer to the file containing PGM image			    
 * \param[in] image pointer to the structure 	    
 * \param[out] s_image structure filled with the image file data              
 * \return number of loaded	pixels					    
 ************************************************************************************/

int read(FILE *input_file, s_image *image) 
{
  char buf[LINE_LENGTH];    /* buffor to read the header and comments*/
  int character;                /* variable to read the comments */
  int end=0;            /* is EOF ? */
  int i,j;

  /*File pointer checking */
  if (input_file==NULL) 
  {
    fprintf(stderr,"Error: No file pointer provided\n");
    return(0);
  }

  /* Checking "the magic number" - should be P2 or P3 */
  if (fgets(buf,LINE_LENGTH,input_file)==NULL)   /* Reading the first line */
    end=1;                              /* Failure? EOF */
  if ( (buf[0]!='P') || ((buf[1]!='2') && (buf[1]!='3')) || end) 
  {  /* Neither "P2" nor "P3" ? */
    fprintf(stderr,"Error: Incorrect file format (Neither PPM nor PGM)\n");
    return(0);
  }
  else
  {
    switch (buf[1])
    { /*saving the image format*/
      case '2':
      {
        (image->type) = 2; /*PGM*/
        break;
      }  
      case '3':
      {
        (image->type) = 3; /*PPM*/
        break;
      }
    }   
  }   
  /* Skipping the comments */
  do {
    if ((character=fgetc(input_file))=='#') 
    {         /* Does the line begin with '#'? */
      if (fgets(buf,LINE_LENGTH,input_file)==NULL)  /* Read into buffor */
	      end=1;                   /* Check for possible EOF */
    }  
    else 
    {
      ungetc(character,input_file); /* When the first character in line */
    }                                         /* is not '#' - return it */
  } while (character=='#' && !end);   /* Repeat until EOF or end of comments */

  /* Loading the image dimensions and the max grayscale value */
   
  fscanf(input_file, "%d %d %d", &(image->x_dimension), &(image->y_dimension), &(image->shades_number));

  /* PGM image format*/
  if(image->type == 2)
  {
    printf("PGM image\n"); 

    // DYNAMIC 2D ARRAY IN C //
    image->pixels_GreyRed = malloc(image->x_dimension * image->y_dimension * sizeof(int)); /*Arranging table with memory for pixels*/  
    int (*pixels)[image->x_dimension];  /* Making a variable allowing to browse the pixels table - pointer to array*/
    pixels = (int(*)[image->x_dimension]) image->pixels_GreyRed; //tricky yet working conversion


    /*Reading pixels from the file*/
    for (i=0; i<image->y_dimension; i++) 
    {
      for (j=0; j<image->x_dimension; j++) 
      {
        if (fscanf(input_file,"%d",&(pixels[i][j]))!=1) 
        {
          fprintf(stderr,"Error: Incorrect dimensions\n");
          return(0);
        }
      }
    }
  }
  
  /*PPM image format*/  
  if(image->type == 3)
  {
   printf("image in PPM format\n"); 
   image->pixels_GreyRed = malloc(image->x_dimension * image->y_dimension * sizeof(int)); /*arranging memory for the red pixels*/  
   int (*pixels_r)[image->x_dimension];  /* Making a variable allowing to browse the pixels table - pointer to array*/
   pixels_r = (int (*)[image->x_dimension]) image->pixels_GreyRed;

   image->pixels_Green = malloc(image->x_dimension * image->y_dimension * sizeof(int)); /*green*/  
   int (*pixels_g)[image->x_dimension];  
   pixels_g = (int (*)[image->x_dimension]) image->pixels_Green;

   image->pixels_Blue = malloc(image->x_dimension * image->y_dimension * sizeof(int)); /*blue*/  
   int (*pixels_b)[image->x_dimension];  
   pixels_b = (int (*)[image->x_dimension]) image->pixels_Blue;

   int k = 1; /* additional variable to help locate pixels errors*/
   
    /*Reading pixels from the file*/
    for (i=0; i<image->y_dimension; i++) 
    {
      for (j=0;j< image->x_dimension; j++) 
      {
        if (  fscanf(input_file,"%d", &(pixels_r[i][j]))  !=1) 
        { /*red pixels*/
	        fprintf(stderr,"Error: Incorrect red dimensions %d\n", k);
    	    return(0);
        }  
        if (  fscanf(input_file,"%d", &(pixels_g[i][j]))  !=1) 
        { /*green*/
	        fprintf(stderr,"Error: Incorrect green dimensions %d\n", k);
    	    return(0);
        } 
        if (  fscanf(input_file,"%d", &(pixels_b[i][j]))  !=1) 
        { /*blue*/
	        fprintf(stderr,"Error: Incorrect blue dimensions %d\n", k);
    	    return(0);
        }
        k++;
      }
    }   
  }  
  return image->x_dimension * image->y_dimension;   /* Success */
  /* Return the number of loaded pixels */
}

/************************************************************************************
 * Funkcja zapisuje image ze struktury do pliku lub na standardowe wyjscie          *
 * Function saves the image from structure to file or to standard output            * 
 *										    
 * PRE: Image correctly saved in the structure 					                            *
 * POST:Image correctly passed to the output                             
 * \param[out] output_file pointer to the output file or stdout	 	    
 * \param[in] image pointer to the structure with image
 * \param[in] dim_change information of the dimensions being cut due to the procession
 * \param[in] conversion variable indicating conversion to PGM 
 * \return number of read pixels
 ************************************************************************************/
int save(FILE *output_file, s_image *image, int dim_change, int conversion) 
{
  int i,j;

 /*Checking the input variable*/
  if (output_file==NULL)
  {
    fprintf(stderr,"Error: No filename \n");
    return(0);
  }  

 /*Case of PGM image*/

 /* Writing P2, dimensions and number of shades to the new file */
  if(image->type == 2)
  {
    fprintf(output_file,"P2\n");
    fprintf(output_file,"%d %d\n%d\n",image->x_dimension,image->y_dimension,image->shades_number);
   
    if(dim_change == 0)
    { /*Original dimensions*/

      /* Writing the contents of pixels table to the new file*/ 
      int (*pixels)[image->x_dimension];  
      pixels = (int (*)[image->x_dimension]) image->pixels_GreyRed;
   
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          fprintf(output_file,"%d ",(pixels[i][j]));
        }
        fprintf(output_file,"\n");
      }
    }
    else
    { /*decreased dimensions*/    
    int (*pixels)[image->x_dimension+1];  
                                     /* x_dimension+1 because the dimensions were decreased, but to save the image properly
                                      the array has to have the same size as if they were not */
    pixels = (int (*)[image->x_dimension+1]) image->pixels_GreyRed;  
    /* Writing the contents of pixels table out */ 
      for (i=0;i<image->y_dimension;i++) 
      {
        for (j=0;j<image->x_dimension;j++) 
        {
          fprintf(output_file,"%d ",(pixels[i][j]));
        }
        fprintf(output_file,"\n");
      }    
    }
  }


  /*Case of PPM file extension*/

  
 /* Writing P3 or P2, then the dimensions and max grayscale*/
 
  if(image->type == 3)
  {
    if(conversion != 3)
    { 
      fprintf(output_file,"P3\n");
    }
    else
    { /*PGM conversion*/
      fprintf(output_file,"P2\n");
    } 
    fprintf(output_file,"%d %d\n%d\n",image->x_dimension,image->y_dimension,image->shades_number);
  
    if(dim_change == 0)
    {/* Original dimensions*/
   
      int (*pixels_r)[image->x_dimension];  
      pixels_r = (int (*)[image->x_dimension]) image->pixels_GreyRed;
   
       int (*pixels_g)[image->x_dimension]; 
      pixels_g = (int (*)[image->x_dimension]) image->pixels_Green;
 
      int (*pixels_b)[image->x_dimension];  
      pixels_b = (int (*)[image->x_dimension]) image->pixels_Blue;

      if(conversion != 3)
      {/*Save with PPM extension*/
       
        for (i=0;i<image->y_dimension;i++) 
        {
          for (j=0;j<image->x_dimension;j++) 
          {
            fprintf(output_file,"%d  %d  %d  ",(pixels_r[i][j]),(pixels_g[i][j]),(pixels_b[i][j]));
          }
        fprintf(output_file,"\n");
        }
      }
      else
      {/*Case of PGM saving format*/
      /*Meaning the values*/ 
        for (i=0;i<image->y_dimension;i++) 
        {
          for (j=0;j<image->x_dimension;j++) 
          {
            fprintf(output_file,"%d ",((pixels_r[i][j] + pixels_g[i][j] + pixels_b[i][j])/3));
          }
        fprintf(output_file,"\n");
        }     
      }         
    }
    else
    {/*Decreased dimensions*/
      int (*pixels_r)[image->x_dimension+1];  
      pixels_r = (int (*)[image->x_dimension+1]) image->pixels_GreyRed;
   
      int (*pixels_g)[image->x_dimension+1]; 
      pixels_g = (int (*)[image->x_dimension+1]) image->pixels_Green;
 
      int (*pixels_b)[image->x_dimension+1];  
      pixels_b = (int (*)[image->x_dimension+1]) image->pixels_Blue;
     
      if(conversion != 3)
      {/*Case of PPM saving format*/
       
        for (i=0;i<image->y_dimension;i++) 
        {
          for (j=0;j<image->x_dimension;j++) 
          {
            fprintf(output_file,"%d  %d  %d  ",(pixels_r[i][j]),(pixels_g[i][j]),(pixels_b[i][j]));
          }
        fprintf(output_file,"\n");
        }
      }
      else
      {/*PGM*/
      /*Meaning*/
        for (i=0;i<image->y_dimension;i++) 
        {
          for (j=0;j<image->x_dimension;j++)
          {
            fprintf(output_file,"%d ",((pixels_r[i][j] + pixels_g[i][j] + pixels_b[i][j])/3));
          }
        fprintf(output_file,"\n");
        }     
      }     
    } 
  }
  return image->x_dimension*image->y_dimension; /* Number of read pixels */  
}


/************************************************************************************
 * Function displays the image of given name using built-in display command (linux)
 *										    
 * PRE: Correct pointer to the file					    
 * POST: Displaying                           	 	                    
 * \param[in] filename pointer to the image file 	            
 *                                                                                  
 ************************************************************************************/

void display(char *filename) 
{
  char command[LINE_LENGTH];   /* temporary buffor */
  strcpy(command,"display ");  /* merging the commands */
  strcat(command,filename);    
  strcat(command," &");
  printf("%s\n",command);      
  system(command);             /* 'display "filename" &' command */
}
