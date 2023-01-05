import java.util.*;
import java.math.*;

public final class Q {

	public static final int MAXN = 59;
	public static BigInteger fat[];
	public static int freq[], n;

	public static BigInteger compute() {
		int tot = 0;
		BigInteger den = BigInteger.ONE;
		for(int i = 0; i < MAXN; i++) {
			tot += freq[i];
			den = den.multiply(fat[freq[i]]);
		}
		return fat[tot].divide(den);
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String s = sc.nextLine();

		fat = new BigInteger[MAXN];
		fat[0] = BigInteger.ONE;
		for(int i = 1; i < MAXN; i++) {
			fat[i] = BigInteger.valueOf(i).multiply(fat[i-1]);
		}

		freq = new int[MAXN];
		for(int i = 0; i < MAXN; i++) freq[i] = 0;

		n = s.length();
		for(int i = 0; i < n; i++) {
			freq[s.charAt(i) - 'a']++;
		}

		BigInteger ans = BigInteger.ONE;
		for(int i = 0, j; i < n; i++) {
			for(j = 0; j != s.charAt(i)-'a'; j++) {
				if (freq[j] == 0) continue;
				freq[j]--;
				ans = ans.add(compute());
				freq[j]++;
			}
			freq[j]--;
		}

		System.out.println(ans);
	}
}