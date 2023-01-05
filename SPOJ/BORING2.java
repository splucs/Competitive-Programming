import java.util.*;
import java.math.BigInteger;

public final class BORING2 {

	public static void testcase(Scanner sc) {
		BigInteger N, P;
		N = sc.nextBigInteger();
		P = sc.nextBigInteger();
		int comp = N.compareTo(P);
		BigInteger ans;
		BigInteger base = P.subtract(BigInteger.ONE);
		if (comp < 0) {
			int d = P.subtract(N).intValue()-1;
			BigInteger cur = N, inv = BigInteger.ONE;
			for(int it = 0; it < d; it++) {
				cur = cur.add(BigInteger.ONE);
				inv = inv.multiply(cur).remainder(P);
			}
			inv = inv.modInverse(P);
			ans = base.multiply(inv).remainder(P);
		}
		else {
			int d = N.subtract(P).intValue()+1;
			BigInteger cur = P, acum = BigInteger.ONE;
			for(int it = 0; it < d; it++) {
				acum = acum.multiply(cur).remainder(P);
				cur = cur.add(BigInteger.ONE);
			}
			ans = base.multiply(acum).remainder(P);
		}
		System.out.println(ans);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		for(int t  = 0; t < T; t++) {
			testcase(sc);
		}
	}
}