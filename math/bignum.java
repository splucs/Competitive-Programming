import java.util.Scanner;
import java.math.BigInteger;

class Main { /* UVa 10925 - Krakovia */
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int caseNo = 1;
		while (true) {
			int N = sc.nextInt(), F = sc.nextInt();
			if (N == 0 && F == 0) break;
			BigInteger sum = BigInteger.ZERO;
			for (int i = 0; i < N; i++) {
				BigInteger V = sc.nextBigInteger();
				sum = sum.add(V);
			}
			System.out.println("Bill #" +
				(caseNo++) + " costs " + sum +
			": each friend should pay " +
			sum.divide(BigInteger.valueOf(F)));
			System.out.println();
		}
	}
}