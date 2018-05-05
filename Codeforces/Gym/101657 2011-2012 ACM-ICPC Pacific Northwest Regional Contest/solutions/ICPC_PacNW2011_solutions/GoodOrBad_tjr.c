/* ICPC PacNW 2011 Contest
   Gimme problem -- designed for all teams to solve

   Author:  Tim Rolfe
*/

#include <stdio.h>      // the usual suspects
#include <ctype.h>      // toupper
#include <string.h>     // strlen

int main(void)
{  char input[255];     // data from stdin
   int  prob, nProb;    // loop parameters

   scanf("%d", &nProb);
   while (getchar() != '\n')
      ;                 // get to the next line

   for (prob = 1; prob <= nProb; prob++)
   {  int ng = 0, nb = 0, idx, lim;

      fgets(input, 255, stdin);
      lim = strlen(input)-1;      // Last char in string
      input[lim] = '\0';          // wipe out the trailing \n
      if (input[lim-1] == '\r')   // Check for "\r\n"
         input[--lim] = '\0';
      for (idx = 0; idx < lim; idx++)  // Counting loop
      {  int ck = toupper(input[idx]); // Allow single check
         if      (ck == 'G') ng++;
         else if (ck == 'B') nb++;
      }
      printf("%s is ", input);
      if      (ng > nb) printf("GOOD\n");
      else if (ng < nb) printf("A BADDY\n");
      else              printf("NEUTRAL\n");
   }
   return 0;            // Keep the compiler happy:  ! ! Success ! !
}
