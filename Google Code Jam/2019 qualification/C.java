import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public final class C {

	public static BigInteger gcd(BigInteger a, BigInteger b) {
		if (b.compareTo(BigInteger.ZERO) == 0) return a;
		else return gcd(b, a.remainder(b));
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		for(int caseNo = 1; caseNo <= T; caseNo++) {
			BigInteger n = sc.nextBigInteger();
			int L = sc.nextInt();
			BigInteger arr[] = new BigInteger[L];
			BigInteger ans[] = new BigInteger[L+1];
			int j = -1;
			for(int i = 0; i < L; i++) {
				arr[i] = sc.nextBigInteger();
				if (j == -1 && i > 0 && arr[i].compareTo(arr[i-1]) != 0) {
					j = i;
					ans[j] = gcd(arr[i-1], arr[i]);
				}
			}
			for(int i = j-1; i >= 0; i--) {
				ans[i] = arr[i].divide(ans[i+1]);
			}
			for(int i = j+1; i <= L; i++) {
				ans[i] = arr[i-1].divide(ans[i-1]);
			}
			HashSet<BigInteger> used = new HashSet<>();
			BigInteger primes[] = new BigInteger[26];
			int cnt = 0;
			for(int i = 0; i <= L; i++) {
				if (used.contains(ans[i])) continue;
				used.add(ans[i]);
				primes[cnt++] = ans[i];
			}
			Arrays.sort(primes);
			HashMap<BigInteger, Character> reduce = new HashMap<>();
			for(int i = 0; i < 26; i++) {
				reduce.put(primes[i], (char)('A' + i));
			}
			System.out.print("Case #" + caseNo + ": ");
			for(int i = 0; i <= L; i++) {
				System.out.print(reduce.get(ans[i]));
			}
			System.out.println();
		}
	}
}