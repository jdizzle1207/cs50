/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int detectedjpeg(char* buffer, char* magic);
void recoverfile(FILE* card, char* magic, char* buffer, char* filename, int* filenum);

// define BYTE as unsigned 8 bits for use with sizeof()
// outside main so as to be accessible from every fn
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{

  // declare 'magic bytes' that may denote start of jpeg
  char* magic = malloc(sizeof(BYTE)*3);
  magic[0] = 0xff;
  magic[1] = 0xd8;
  magic[2] = 0xff;

  // define starting jpeg number
  int* filenum = malloc(sizeof(int));
  *filenum = 0;

  // define filename
  char* filename = malloc(sizeof(BYTE)*8);
  snprintf(filename, 8, "%03i.jpg", *filenum);

  char* buffer = malloc(sizeof(BYTE)*512);

  // open image file for reading
  FILE* card = fopen("card.raw", "r");

  // while I can still read buffer
  while(fread(buffer, sizeof(BYTE)*512, 1, card))
    {
      if (detectedjpeg(buffer, magic)) recoverfile(card, magic, buffer, filename, filenum);
    }

  // close file
  fclose(card);

  // free our memory
  free(buffer);
  free(filename);
  free(magic);

}

int detectedjpeg(char* buffer, char* magic)
{
  int match = 1;
  for (int i = 0; i < 3; i++)
    {
      if (!(buffer[i] == magic[i])) match = 0;
    }
  return match;
}

void recoverfile(FILE* card, char* magic, char* buffer, char* filename, int* filenum)
{
  // open jpg file for writing
  FILE* jpg = fopen(filename, "a");
  if (jpg == NULL) exit(1);
		   
  // until I find another match (or EOF/error) I'll continue to write to jpg
  do
    {
      fwrite(buffer, sizeof(BYTE)*512, 1, jpg);
      // exit at EOF/error
      if(!fread(buffer, sizeof(BYTE)*512, 1, card)) exit(0);
    }
  while (!detectedjpeg(buffer, magic));

  fseek(card, sizeof(BYTE)*(-512), SEEK_CUR);
		   
  // close file
  fclose(jpg);
		   
  // increment jpg number and reset filename
  *filenum = *filenum + 1;
  snprintf(filename, 8, "%03i.jpg", *filenum);

}
