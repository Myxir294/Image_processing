#include"../inc/filters_prototypes.h"
#include"../inc/options_prototypes.h"
#include"../inc/files_prototypes.h"
#include"../inc/structures.h"

int main(int argc, char ** argv)
{
  s_image image; /*structure with the image*/
  char chosen_colour; 
  int decreased_dimensions = 0; /*informative*/
  int saving = 0; /*Default values for the function processing options*/
  int tresholding = 0;
  int negating = 0;
  int reading = 0;
  int outlining = 0;
  int treshold_value; /*treshold value in case of using the menu*/
  char name_menu[100]; /*filename array*/
  execution_options options; /* structure for execution options/arguments */
  execution_options *chosen_options; 
  chosen_options = &options;
  int tab[2] = {0}; /* table for switch if no menu*/
  char menu[2] = "9"; /* table for switch in menu*/
  printf("Value returned by options processing function:");
  printf("%d\n", process_options(argc,argv,chosen_options));
  tab[0] = process_options(argc,argv,chosen_options); 
  switch (tab[0])
  { /*execution arguments are present*/
    case 0:
    {
      reading = read(chosen_options->input_file,&image); /* file reading*/
      fclose(chosen_options->input_file);
      if (reading != 0)
      { /* reading succesful*/
        if (image.type == 2)
        { /*Monochromatic PGM image*/
	        chosen_options->colour_value = 0; /* preventing colours processing*/
        }
        if (chosen_options->tresholding == 1)
        { /*tresholding*/
	        tresholding = treshold(&image,chosen_options->treshold_value,chosen_options->colour_value);
	        if(tresholding != 0)
          {
	          printf("Tresholding successful\n");
	        }   
        }
        if (chosen_options->negative == 1)
        { /*making a negative*/
	        negating = negative(&image,chosen_options->colour_value);
	        if(negating != 0)
          {
	          printf("Negating successful\n");
	        }
        } 
        if (chosen_options->outlining == 1)
        { /*making an outline*/
	        outlining = outline(&image,chosen_options->colour_value);
	        if(outlining != 0)
          {
	          decreased_dimensions = 1; 
	          printf("Outlining successful\n");
	        }  
        } 
        saving = save(chosen_options->output_file,&image, decreased_dimensions, chosen_options->colour_value); /*saving image*/
        if(saving == 0)
        {
          printf("Saving failed\n");
        }
        else
        {
	        printf("Saving successful\n");
        }
        if (chosen_options->display == 1)
        {
	        display(chosen_options->name); /*display image*/
        }
        free(image.pixels_GreyRed); /*freeing the memory*/
        if (image.type == 3)
        {
	        free(image.pixels_Blue); 
          free(image.pixels_Green);
        }      
      } 
      else
      { /*reading file failed*/
        printf("Error while reading file\n");
      }      
      break;
    }
    case 1 :
    { /*No execution args - menu*/
      printf("User menu\n");
      while (menu[0] != '8')
      {
        printf ("What do you want to do?:\n");
        printf ("1 - Read image\n");
        printf ("2 - Save the processed image\n");
        printf ("3 - Choose colour to be processed\n");
        printf ("4 - Make a negative of the image\n");
        printf ("5 - Make an outline of the image\n");
        printf ("6 - Make tresholding of the image\n");
        printf ("7 - Display read/saved file\n");
        printf ("8 - Leave the program\n");     
        printf ("Your pick:");
        scanf ("%s", menu); 
        switch (menu[0])
        {
          case '1':
          { /*load file*/
            printf("Enter the filename:\n");
            scanf("%s",name_menu);
            chosen_options->input_file = fopen(name_menu,"r"); /*read file*/
	          if (chosen_options->input_file==NULL) 
            {
	            printf("There is no such file\n");
	            break;
	          } 
            reading = read(chosen_options->input_file, &image);
            fclose(chosen_options->input_file);
	          if(reading != 0)
            {
	            printf("Reading succesful\n");
	          }
	          else
            {
	            printf("No correct input file provided\n");
	          }
	          break;
          }
          case '2':
          { /*saving file*/
	          if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
	          }
            printf("Enter filename:\n");
            scanf("%s",name_menu);
            chosen_options->output_file=fopen(name_menu,"w");
            saving = save(chosen_options->output_file,&image, decreased_dimensions, chosen_options->colour_value);
	          fclose(chosen_options->output_file);
            if(saving == 0)
            {
              printf("Saving Error\n");
            }
	          else
            {
	            printf("Saving successful\n");
	          }
	          break;
          }
          case '3':
          {/*colour processing*/
            if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
            }	
            if (image.type == 2)
            { /*Extension error preventing*/
	            printf("Error: Chosen file is a PGM\n");
            }
            else
            {
	            printf("Choose a colour: r,g,b,s (monochromatic)\n");
	            scanf("%s",&chosen_colour); 
	            switch (chosen_colour)
              {
                case 'r':
                {
                  printf("Red colour chosen\n"); 
                  break;
                }
                case 'g':
                {
                  chosen_options->colour_value = 1;
                  printf("Green colour chosen\n");
                  break;
                }
                case 'b':
                {
                  chosen_options->colour_value = 2;
                  printf("Blue colour chosen\n");		
                  break;
                }
                case 's':
                {
                  chosen_options->colour_value = 3;
                  printf("Conversion to monochromatic chosen\n");		
                  break;
                }	     
                default:
                {
                  printf("Incorrect option!\n");
                  break;
                }	   
              }
            } 
            break;
          }
          case '4':
          { /*Negative*/
            if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
            }
            negating = negative(&image,chosen_options->colour_value);
            if(negating != 0)
            {
	            printf("Negating successful\n");
            }
            break;
          } 
          case '5':
          {/*Outlining*/
            if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
            }
            outlining = outline(&image,chosen_options->colour_value);
	          if(outlining != 0)
            {
	            decreased_dimensions = 1;
	            printf("Outlining successful\n");
	          }  
            break;
          }
          case '6':
          {/*Tresholding*/
            if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
            }
            printf("Enter a treshold value (0-100)\n");
            scanf("%d",&treshold_value);
            if(treshold_value >=0 && treshold_value <= 100)
            {
	            chosen_options->treshold_value = treshold_value;
	            tresholding = treshold(&image,chosen_options->treshold_value,chosen_options->colour_value);
	            if(tresholding != 0)
              {
	              printf("Tresholding successful\n");
	            }
            } 
            else
            {
	            printf("Invalid treshold value!");
            }
            break;
          }
          case '7':
          {/*display image*/
            if(chosen_options->input_file == NULL)
            {
	            printf("Read a file first\n");
	            break;
            }
            display(name_menu);
            break;
          }
          case '8':
          {/*Leave menu*/
	          break;
          }
          default:
          {
	          printf("Invalid\n");
	          break;
          }
        }
      }
      if(reading != 0)
      {  
        free(image.pixels_GreyRed); /*Memory dellocation*/
        if (image.type == 3)
        {
          free(image.pixels_Green);
          free(image.pixels_Blue);
        }
      } 
      break;
    }/*end of user menu case */
    /*Error reports*/ 
    case -1 :
    {
      printf ("Invalid option\n");
      break;
    }
    case -2 :
    {
      printf ("No input file name\n");
      break;
    }
    case -3 :
    {
      printf ("Invalid treshold value\n");
      break;
    }
    case -4 :
    {
      printf("No input file\n");
      break;
    }
    case -5 :
    {
      printf("Invalid colour\n");
      break;
    }
    default:
    {
      printf("Options processing error\n");
      break;   
    } 
  }
  return 0;
}
