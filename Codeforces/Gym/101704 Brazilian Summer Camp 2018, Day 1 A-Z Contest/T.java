import java.util.*;
import java.math.*;

public final class T {

	public static final int MAXN = 109;
	public static BigInteger pascal[][];
	public static int ans[];
	public static int n;
	public static int k;

	public static void solve(int i, int cur, BigInteger pos) {
		if (cur > k || i > n) return;
		//System.out.println("solve i=" + i + " cur=" + cur + " pos=" + pos);
		int comp = pascal[n-i][k-cur].compareTo(pos);
		if (comp == -1) {
			solve(i+1, cur, pos.subtract(pascal[n-i][k-cur]));
		}
		else {
			ans[cur] = i;
			solve(i+1, cur+1, pos);
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		pascal = new BigInteger[MAXN][MAXN];
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				if (j > i) pascal[i][j] = BigInteger.ZERO;
				else if (j == 0 || i == j) pascal[i][j] = BigInteger.ONE;
				else pascal[i][j] = pascal[i-1][j-1].add(pascal[i-1][j]);
			}		
		}
		ans = new int[MAXN];
		k = sc.nextInt();
		BigInteger pos = sc.nextBigInteger();
		solve(1, 1, pos);
		for(int i = 1; i <= k; i++) {
			System.out.print(ans[i] + " ");
		}
		System.out.print("\n");
	}
}