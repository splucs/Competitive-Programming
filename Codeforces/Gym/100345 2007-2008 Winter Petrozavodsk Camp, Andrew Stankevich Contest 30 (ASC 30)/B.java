import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public class B {

    public static final int MAXN = 201;
    
    public static BigInteger der[];
    public static BigInteger pow2[];
    public static BigInteger pascal[][];
    
    public static void main(String[] args) throws Exception{
        der = new BigInteger[MAXN];
        der[0] = BigInteger.ONE;
        der[1] = BigInteger.ZERO;
        for(int i=2; i<MAXN; i++) {
            der[i] = BigInteger.valueOf(i-1).multiply(der[i-1].add(der[i-2]));
        }
        pow2 = new BigInteger[MAXN];
        pow2[0] = BigInteger.ONE;
        for(int i=1; i<MAXN; i++) {
            pow2[i] = BigInteger.valueOf(2).multiply(pow2[i-1]);
        }
        pascal = new BigInteger[MAXN][MAXN];
        for(int n=0; n<MAXN; n++) {
            for(int k=0; k<MAXN; k++) {
                if (k > n) pascal[n][k] = BigInteger.ZERO;
                else if (k == n ||  k == 0) pascal[n][k] = BigInteger.ONE;
                else pascal[n][k] = pascal[n-1][k].add(pascal[n-1][k-1]);
            }
        }
        
        Scanner sc = new Scanner(new File("derangements.in"));
        
        int n = sc.nextInt();
        BigInteger ans = BigInteger.ZERO;
        for(int i=0; i<=n; i++) {
            int j = n-i;
            ans = ans.add(pascal[n][i].multiply(der[j]).multiply(pow2[j]));
        }
        
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("derangements.out")));
        out.println(ans);
        out.close();
    }
    
}