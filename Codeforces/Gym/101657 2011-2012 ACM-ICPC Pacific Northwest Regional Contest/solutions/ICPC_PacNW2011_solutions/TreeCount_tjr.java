/* Dynamic programming solution via memoization:  transform the
 * recurrence into a two-dimensional array filled from the top
 * left corner down and to the right.
 *
 * All arithmetic is done modulo one billion for retain the
 * rightmost nine digits.
 *
 * Recurrence from Tom Rokicki <rokicki@gmail.com>
 *
 *  $c[$n][$d] => number of avl trees of depth d with n nodes
 *
 *  c[n][d] = sum(0<=i<n) c[i][d-1]*c[n-1-i][d-1] +
 *                        c[i][d-2]*c[n-1-i][d-1] +
 *                        c[i][d-1]*c[n-1-i][d-2] ;
 *
 * Filled based on root at level 1 and leaf nodes at height 1.
 *
 * Author:  Tim Rolfe
 *
 * Revision to match contest specifications.  5 October 2011
 */
import java.util.*;     // Scanner
import java.io.*;

@SuppressWarnings("unchecked")
public class TreeCount_tjr
{
   static Integer [] minNumb = {0};    // Size of sparsest AVL tree:  minNumb[height]
   static long[][] c;                  // Table described by above recurrence.
   static final boolean TABLE = false; // Show table of c rather than row sums.
   // Compute module one billion for nine digits --- particularly
   // important for products.
   static final long BILLION = 1000000000L;

/* Recurrence for sparsest AVL trees:
   AVLn(0) = 0
   AVLn(1) = 1
   AVLn(h>1) = 1 + AVLn(h-1) + AVLn(h-2)
*/
   static void fillMinNumb(int maxNodes)
   {  ArrayList<Integer> sizeList = new ArrayList<Integer>();
      int ht = 2, nNodes;

      sizeList.add(0);  sizeList.add(1);
      while(true)  // break out when nNodes > maxNodes
      {  nNodes = 1 + sizeList.get(ht-1) + sizeList.get(ht-2);
         sizeList.add(nNodes);
         if (nNodes >= maxNodes)
            break;
         ht++;
      }
      minNumb = sizeList.toArray(minNumb);
   }

   static void fillCtable(int maxNodes)     // c[][] is global
   {  int row, col, k;

      c[0][0] = 1; // One empty tree  (height zero)
      c[1][1] = 1; // One single-node tree of height 1

/*    c[n][d] = sum(0<=i<n) c[i][d-1]*c[n-1-i][d-1] +
 *                          c[i][d-2]*c[n-1-i][d-1] +
 *                          c[i][d-1]*c[n-1-i][d-2] ;
 */
      for (row = 2; row <= maxNodes; row++)
      {  int lim = Arrays.binarySearch(minNumb, row);

         if (lim < 0)
            lim = Math.abs(lim) - 1;
         for (col = 1; col <= lim; col++)
         {  long sum = 0;

            for (k = 0; k < row; k++)
            {  long component = c[k][col-1]*c[row-1-k][col-1] % BILLION;

               sum += component;
               if (col > 1)
               {  component = c[k][col-2]*c[row-1-k][col-1] % BILLION;
                  sum += component;
                  component = c[k][col-1]*c[row-1-k][col-2] % BILLION;
                  sum += component;
               }
            }
            // For nine digits, compute modulo 10^9
            c[row][col] = sum % BILLION;
         }
      }
   }

   public static void main(String[] args) throws Exception
   {  Scanner console;
      int maxNodes = 1428;

      if (args.length == 0)
         console= new Scanner(System.in);
      else
         console = new Scanner(new File(args[0]));
      fillMinNumb(maxNodes);
      c = new long[maxNodes+1][minNumb.length+1];
      fillCtable(maxNodes);

      while (console.hasNextInt())
      {  int  size = console.nextInt(),
              col, lim = Math.abs(Arrays.binarySearch(minNumb, size));
         long sum = 0;
         String trailing;
         StringBuilder outString = new StringBuilder();

         console.nextLine(); // Discard \n
         for (col = 0; col <= lim; col++)
            sum += c[size][col];
         // One last modulo operation
         System.out.printf("%09d\n", sum%BILLION);
      }
   }
}
