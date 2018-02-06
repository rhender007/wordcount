/*
 * Author: Robert Henderson
 */
#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct TreeNode
{
  ElementType Element;
  SearchTree Left;
  SearchTree Right;
  int count;
};

SearchTree
MakeEmpty (SearchTree T)
{
  if (T != NULL)
    {
      MakeEmpty (T->Left);
      MakeEmpty (T->Right);
      free (T);
    }
  return NULL;
}

Position
Find (ElementType X, SearchTree T)
{
  if (T == NULL)
    return NULL;
  if ((strcmp (X, T->Element) < 0))	/*greater than 0   str1 is greater than str2 */
    return Find (X, T->Left);
  else if ((strcmp (X, T->Element) > 0))
    return Find (X, T->Right);
  else
    return T;
}


Position
FindMin (SearchTree T)
{
  if (T == NULL)
    return NULL;
  else if (T->Left == NULL)
    return T;
  else
    return FindMin (T->Left);
}

Position
FindMax (SearchTree T)
{
  if (T != NULL)
    while (T->Right != NULL)
      T = T->Right;

  return T;
}

SearchTree
Insert (ElementType X, SearchTree T)
{
  if (T == NULL)
    {
      /*1 node */
      T = malloc (sizeof (struct TreeNode));
      if (T == NULL){
	      fprintf( stderr, "%s\n", "Out of space!!!" );
         exit( 1 );
   }
      else
	{
	  T->Element = (char *) malloc ((strlen (X) * sizeof (char)) + 1);
	  strcpy (T->Element, X);
	  T->Element[strlen (X)] = '\0';
	  T->count = 1;
	  T->Left = T->Right = NULL;
	}
    }
  else if ((strcmp (X, T->Element) < 0))
    T->Left = Insert (X, T->Left);
  else if ((strcmp (X, T->Element) > 0))
    T->Right = Insert (X, T->Right);
  else
    T->count++;
  /* increment count if found */

  return T;

}

SearchTree
Delete (ElementType X, SearchTree T)
{
  Position TmpCell;

  if (T == NULL)
    fprintf( stderr, "%s\n", "Element not found" );
  else if ((strcmp (X, T->Element) < 0))	/* Go left */
    T->Left = Delete (X, T->Left);
  else if ((strcmp (X, T->Element) > 0))	/* Go right */
    T->Right = Delete (X, T->Right);
  else if (T->Left && T->Right)	/* Two children */
    {
      /* Rep w smallest */
      TmpCell = FindMin (T->Right);
      T->Element = TmpCell->Element;
      T->Right = Delete (T->Element, T->Right);
    }
  else				/* 1 || 0 children */
    {
      TmpCell = T;
      if (T->Left == NULL)	/* 0 children */
	T = T->Right;
      else if (T->Right == NULL)
	T = T->Left;
      free (TmpCell);
    }

  return T;
}


ElementType
Retrieve (Position P)
{
  return P->Element;
}

void
InorderTraversal (SearchTree T)
{
  if (T != NULL)
    {
      InorderTraversal (T->Left);
      printf ("%s\t", T->Element);
      printf ("%d\n", T->count);
      InorderTraversal (T->Right);
    }
}
