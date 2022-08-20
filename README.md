# Image_processing
Allows to make negatives, outlines and tresholiding operations on PPM and PGM images

By default, the program opens up a console user menu, allowing to choose beetween options displayed on the screen. In order to process the image, one has to open a file through menu (alternatively load it via passing stream to the program, not tested but technically should work), choose an operation and than display the image, with the posiblity of saving it in the new file. The program allows to do different operations on the same picture or to pick only a single colour to be processed (by default, in PPM files all are chosen). Choosing gray will convert the image to PGM (the user still has to manually add a .PGM extension to the new filename, otherwise it may not be recognized correclty by the system).   

The program can be run with execution arguments, for example:
  
  -i Winnie.ppm - loads a file (as no output stream is given, it will be displayed literally in the stdout)  
  -i Winnie.ppm -o Winnie2.ppm - basically just copies the file  
  -i Winnie.ppm -n -o Winnie2.ppm - makes a negative and saves it in new file  
  -i Winnie.ppm -n -d -o Winnie2.ppm - same as above but displays the outcome  
  -i Winnie.ppm -p 90 -d -o Winnie2.ppm - tresholding with zeroing 90% of grayscale  
  -i Winnie.ppm -m -s -o Winnie2.pgm - monochromatic conversion  
  -i Winnie.ppm -m -r -n Winnie2.ppm - makes a negative but processes only the red colour  
  -i Winnie.ppm -k -d - makes an outline, does not save the outcome  
  
This was my first ever relatively robust program and the code may be a little "sloppy" or hard to read, but it does the job and I made efforts to make it a bit more comprehensible. Although it is not under any further development at the moment, it could be nicely improved, for example by allowing to process different file formats and do more operations, like erasing the background of the image.

  
