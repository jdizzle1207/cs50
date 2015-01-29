/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a bitmap by a factor of 'n', an integer <= 100.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bmp.h"

void error(void);

int main(int argc, char* argv[])
{
  // ensure proper usage
  if (argc != 4) error();
  for (int i = 0; i < strlen(argv[1]); i++)
    {
      if (!isdigit(argv[1][i])) error();
    }
  int n = atoi(argv[1]);
  if (n > 100) error();

  // remember filenames
  char* infile = argv[2];
  char* outfile = argv[3];

  // open input file 
  FILE* inptr = fopen(infile, "r");
  if (inptr == NULL)
    {
      printf("Could not open %s.\n", infile);
      return 2;
    }

  // open output file
  FILE* outptr = fopen(outfile, "w");
  if (outptr == NULL)
    {
      fclose(inptr);
      fprintf(stderr, "Could not create %s.\n", outfile);
      return 3;
    }

  // read infile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

  // read infile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

  // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
      bi.biBitCount != 24 || bi.biCompression != 0)
    {
      fclose(outptr);
      fclose(inptr);
      fprintf(stderr, "Unsupported file format.\n");
      return 4;
    }


  // manipulate infoheader--saving original val to calculate padding below
  LONG origbiWidth = bi.biWidth;
  bi.biWidth *= n;
  bi.biHeight *= n;

  // write outfile's BITMAPFILEHEADER
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // write outfile's BITMAPINFOHEADER
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  // determine padding for scanlines
  int padding =  (4 - (origbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // determine padding for resized scanlines
  int newpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // define variable to track whether we keep repeating line or go on
  int linerepeated = 0;

  // also remember this location so we can rewind and repeat this line
  fpos_t* linebegin = malloc(sizeof(fpos_t));
  fgetpos(inptr, linebegin);

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
      // iterate over pixels in scanline
      for (int j = 0; j < origbiWidth; j++)
        {
	  // temporary storage
	  RGBTRIPLE triple;

	  // read RGB triple from infile
	  fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

	  // write RGB triple to outfile n times for horizontal resize
	  for (int i = 0; i < n; i++)
	    {
	      fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
	    }
        }

      // skip over padding, if any
      fseek(inptr, padding, SEEK_CUR);

      // then add it back (to demonstrate how)
      for (int k = 0; k < newpadding; k++)
        {
	  fputc(0x00, outptr);
        }

      // reached end of this scanline after padding so update
      linerepeated++;

      // if we've not repeated n times, rewind infile to last line
      if (linerepeated < n)
	{
	  fsetpos(inptr, linebegin);
	}

      // otherwise set this as the new position and reset linerepeated counter
      else
	{
	  fgetpos(inptr, linebegin);
	  linerepeated = 0;
	}
    }

  /**
   * after some headaches trying to figure what filesize would be after
   * resize, I decided to get the size after the fact and rewrite the
   * header then
   */

  // now that the image is ready, get filesize--seek to end and get position
  fseek(outptr, 0, SEEK_END);
  bf.bfSize = ftell(outptr);
  // seek back to beginning and rewrite header with correct filesize
  fseek(outptr, 0, SEEK_SET);
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // find size of image by getting difference of file size and current
  // position plus length of BITMAPINFOHEADER we haven't traversed yet
  bi.biSizeImage = bf.bfSize - (ftell(outptr)+sizeof(BITMAPINFOHEADER));

  // also write info header after correcting biSizeImage above
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
  
  // close infile
  fclose(inptr);

  // close outfile
  fclose(outptr);

  // free memory
  free (linebegin);

  // that's all folks
  return 0;
}

void error(void)
{
  printf("Usage: ./resize n infile outfile ** where n is integer <= 100\n");
  exit(1);
}
