import java.util.Scanner;
import java.math.BigInteger;

public class E {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while(sc.hasNextInt()) {
			int n = sc.nextInt();
			BigInteger dp[] = new BigInteger[3];
			dp[1] = BigInteger.ONE;
			dp[2] = dp[1].add(BigInteger.ONE);
			for(int i=3; i<=n; i++) {
				dp[i%3] = dp[(i+1)%3].add(dp[(i+2)%3]);
				//System.out.println(dp[i%3]);
			}
			BigInteger ans = dp[n%3].add(dp[(n+1)%3]);
			System.out.println(ans);
		}
	}
}