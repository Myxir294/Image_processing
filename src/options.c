#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../inc/options_prototypes.h"
#include"../inc/structures.h"

/* The functions below are modified version of functions at the course website, 
 in the opcje.c file, COPYRIGHT (c) 2007-2013 ZPCiR */

/*******************************************************/
/* Function initializes structure pointed by argument  */
/* PRE:                                                */
/*      choose != NULL                                 */
/* POST:                                               */
/*      "zeroed" options structure                     */
/*******************************************************/

void initialize_options(execution_options* execution_options) 
{
  execution_options->input_file=NULL;
  execution_options->output_file=NULL;
  execution_options->negative=0;
  execution_options->outlining=0;
  execution_options->tresholding=0;
  execution_options->display=0;
  execution_options->colour=0;
  execution_options->colour_value=0;
}

/************************************************************************/
/* Function processes execution options saved in argv array and saves   */
/* them in the structure.                                               */
/* The options can be passed as follows:                                */
/*         program {[-i name] [-o name] [-p value] [-n] [-k] [-d]       */
/*                  [-m character] }                                    */
/* Function arguments:                                                  */
/*         argc  -  number of executiion arguments                      */
/*         argv  -  array of execution arguments                        */
/*         execution_options -  structure containing information on     */
/*                                the exe. options                      */
/* PRE:                                                                 */
/*      none                                                            */
/* POST:                                                                */
/*      function opens files, return file pointers in structure,        */
/*      then set the correct passed exe argument values to 1,           */
/*      not passed to 0. Returns V_OK, error code or MENU constant      */
/*      (if all args are 0)                                             */
/* NOTE:                                                                */
/*      function does not check if the pointed files exist and whether  */
/*      the user is allowed to modify them                              */
/************************************************************************/

int process_options(int argc, char **argv, execution_options* execution_options) {
  int i, treshold;
  char colour;
  char *input_filename, *output_filename;

  initialize_options(execution_options);
  execution_options->output_file=stdout;        /* if no "-o" argument */

  if(argc == 1)
  {
    return MENU;
  }
  else
  {
    for (i=1; i<argc; i++) 
    {
      if (argv[i][0] != '-')  /* error: no "-" character */
        return E_OPTION; 
      switch (argv[i][1]) 
      {
        case 'i': 
        {                 /* input filename argument */
          if (++i<argc) 
          {   /* processing argument as filename */
	          input_filename = argv[i];
	          if (strcmp(input_filename,"-")==0) /* if the name is just "-"*/
	            execution_options->input_file=stdin;/* input is stdin */
	          else /* opening the file   */
	            execution_options->input_file=fopen(input_filename,"r");
          } 
          else 
	          return E_NAME;                   /* error code: no filename */
          break;
        }
        case 'o': 
        {                 /* output filename argument */
          if (++i<argc) 
          {   /* processing argument as filename */
	          output_filename=argv[i];
	          if (strcmp(output_filename,"-")==0) /* if the name is just "-"*/
            {
	            execution_options->output_file=stdout;/* output is stdout */
	            execution_options->name=input_filename; /*setting filename as input filename*/ 
	          }      
	          else
            { /* opening the file   */
	            execution_options->output_file=fopen(output_filename,"w");
	            execution_options->name=output_filename; /*setting filename as output filename*/
	          }  
          } 
          else 
	          return E_NAME;                   /* error code: no filename */
          break;
        }
        case 'p': 
        {
          if (++i<argc) 
          { /* processing next argument as valid treshold value */
	          if (sscanf(argv[i],"%d", &treshold)==1 && treshold >= 0 && treshold <= 100)
            { 
	            execution_options->tresholding=1;
	            execution_options->treshold_value=treshold;
	          }
            else
	            return E_VALUE;     /* value error */
          } 
          else 
	          return E_VALUE;       /* value error */
          break;
        }
        case 'n': /* Values indicating what the user wants to do*/
        {                 
          execution_options->negative=1;
          break;
        }
        case 'k': 
        {                 
          execution_options->outlining=1;
          break;
        }
        case 'd': 
        {                 
          execution_options->display=1;
          break;
        }
        case 'm': 
        { /*colours processing*/
          if (++i<argc) 
          {/* loading the next argument as the colour*/
	          if (sscanf(argv[i],"%c", &colour)==1)
            {
	            switch (colour)
              {
	              case 'r':{break;} /* red by default */
	              case 'g':
                { /*green*/
	                execution_options->colour_value = 1;
	                break;
	              }
	              case 'b':
                { /*blue*/
	                execution_options->colour_value = 2;
	                break;
	              }
	              case 's':
                { /*conversion into gray scale*/
	                execution_options->colour_value = 3;
	                break;
	              }	     
	              default:
	                return E_COLOUR; /*error if something else than the above ones*/
	                break;
	            }	  
	          }
	          else
            {
	            return E_COLOUR;
	            break;
            }
          }
          else
          {
	          return E_COLOUR;
          }
          break;
        }  
        default:                    /* incorrect argument */
          return E_OPTION;
      } /*switch end */
    }/* for end */
    if (execution_options->output_file==stdout)
    { 
      execution_options->name=input_filename; /* setting filename in the structure */
    }
    if (execution_options->input_file!=NULL) 
      return V_OK;
    else 
      return E_FILE; /* error: no input file */
  }
}
