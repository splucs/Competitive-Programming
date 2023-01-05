/*   Each input line has a, b, c, d, m, and t

     liters/hour = a v^4 + b v^3 + c v^2 + d v = P(v) = t liters / time in hours
     t liters / P(v) = time in hours

     distance = velocity * time:  m = v * time in hours
     time in hours = m / v

     t liters / P(v) = m / v
     m * P(v) / v = t
     m * P(v) / v - t = 0
     m * (((a * v + b) * v + c) * v + d) - t = 0

     Author:  Tim Rolfe

     Modified to output using the format ###.# per Tom Rokicki's e-mail of
     10 Oct 2011 1:23 PM.
     27 Oct 2011:  format ##.##; truncation formally done as integer truncation
*/
import java.util.*;
import java.io.File;

@SuppressWarnings("unchecked")
public class SpeedRacer_tjr
{
   static double compute(double[] coeff, double v)
   {  double poly = ( ( ( coeff[0] * v + coeff[1]) *  // a and b
                      v + coeff[2] ) *                // c
                      v + coeff[3] ) *                // d
                      coeff[4] -                      // m
                      coeff[5];                       // t
      return poly;
   }

   // Granted, iterative version calls only one compute per iteration,
   // but the recursive method is more quickly written.
   static double bisect(double[] coeff, double lo, double hi)
   {  double valLo = compute(coeff, lo),
             valHi = compute(coeff, hi),
             mid = (lo + hi) / 2,
             valMid = compute(coeff, mid);

      if (Math.abs(valMid) < 1E-10) return mid;
      if (valLo*valMid > 0)  // I.e., same sign, root on right
         return bisect(coeff, mid, hi);
      else                   // root on left
         return bisect(coeff, lo, mid);
   }

   static public void main(String[] args) throws Exception
   {  int idx, iv, prob = 0;
      double poly, v;
      double[] data = new double[6];
      String fname = args.length > 0 ? args[0] : "SpeedRacer.in";
      Scanner input;
      boolean DEBUG = false; // Show search for cross-over
      boolean SYSIN = false; // Contest spec.s:  input from System.in

      if (SYSIN)
         input = new Scanner(System.in);
      else
         input = new Scanner(new File(fname));

      while ( input.hasNextDouble() )
      {  for (idx = 0; idx < data.length; idx++)
            data[idx] = input.nextDouble();
         v = 0;
         poly = compute(data, 0E+0);
         // Find cross-over point, successively double iv
         for (iv = 1; iv < 1000; iv += iv)
         {  double polyOld = poly;
            v = iv;
            poly = compute(data, v);
            if (DEBUG)
               System.out.printf("At %d, %15.8g goes to %15.8g\n", iv, polyOld, poly);
            if (polyOld * poly < 0 || poly == 0)
               break;
         }
         if (poly != 0)
            if (iv == 1)
               v = bisect(data, 0, 1);
            else
               v = bisect(data, v/2, v);
//       System.out.println(String.format("%15.8g", v).trim()); // max.prec.
//       System.out.printf("%3.2f\n", v-0.005); // per e-mail of Oct 10, 2011
         v = 0.01 * (int)(v*100.);
         System.out.printf("%3.2f\n", v);
      }
   }
}
