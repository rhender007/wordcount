/*
 * Author: Robert Henderson
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"

int main (int argc, char **argv)
{
  SearchTree T;
  Position P;
  int i;
  int j = 0;

  T = MakeEmpty(NULL);

  char *name = (char *) malloc (strlen (argv[1]));
  name = argv[1];
  char *buffer = (char *) malloc (100 * sizeof (char));
  strcpy (buffer, "");
  char ch;
  int length = 0;
  char *temp = malloc (1 * sizeof (char));

  char *ourDelimiters = "$., !(+><-)/*^&[]{}~=%#-_\\";

  int delimiters[256] = { };
  delimiters[(int) '\n'] = 1;	/*new line always delim */
  delimiters[(int) '\t'] = 1;	/*tab always delim */
  delimiters[(int) '\0'] = 1;	/*null terminator always delim */

  int index;
  for (i = 0; i < strlen (ourDelimiters); i++)
    {
      index = (int) (ourDelimiters[i]);
      delimiters[index] = 1;
    }

  FILE *fp;
  if ((fp = fopen (name, "rb")) == NULL)
    printf ("file cannot be open");


  while ((ch = getc (fp)) != EOF)
    {
      if (!delimiters[(int) ch])
	{
	  temp[0] = tolower (ch);
	  strcat (buffer, temp);
	}
      else
	{
	  temp[0] = '\0';
	  strcat (buffer, temp);
	  if (strlen (buffer) > 0)
	    {
	      T = Insert (buffer, T);
	    }
	  strcpy (buffer, "");
	}
    }

  InorderTraversal (T);
  return 0;
}
