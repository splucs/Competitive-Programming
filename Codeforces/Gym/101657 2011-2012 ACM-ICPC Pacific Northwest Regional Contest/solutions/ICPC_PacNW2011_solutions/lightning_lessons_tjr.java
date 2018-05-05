/*  Sample input
4
2 1 1
5 1 3 6 10 15
5 1 2 4 8 16
2 1 0

Output from lightning-lessons.cc:
zap!
zzzap!
*fizzle*
*bunny*

Author:  Tim Rolfe
*/
import java.io.File;
import java.util.Scanner;
@SuppressWarnings("unchecked")
public class lightning_lessons_tjr
{  // Logic taken from lightning-lessons.cc
   static boolean nonz(int[] x, int lim)
   {  while (lim-- > 0)
         if (x[lim] != 0) return true;
      return false;
   }

   public static void main(String[] args) throws Exception
   {//Scanner console = new Scanner(new File("ex.in"));
      Scanner console = new Scanner(System.in);
      int prob, nProb = console.nextInt();

      console.nextLine();    // discard '\n
      for (prob = 0; prob < nProb; prob++)
      {  int size = console.nextInt(), lim = size;
         int[] bolt = new int[size];
         int idx, echo = 0;

         for (idx = 0; idx < size; idx++)
            bolt[idx] = console.nextInt();
         for ( ; nonz(bolt, lim) && lim > 1; lim--, echo++ )
            for (idx = 1; idx < lim; idx++)
               bolt[idx-1] = bolt[idx] - bolt[idx-1];
         if (bolt[0] > 0)
            System.out.printf("*fizzle*\n");
         else if (bolt[0] < 0)
            System.out.printf("*bunny*\n");
         else
         {  while (echo-- > 0)
               System.out.print('z');
            System.out.print("ap!\n");
         }
      }
   }
}
