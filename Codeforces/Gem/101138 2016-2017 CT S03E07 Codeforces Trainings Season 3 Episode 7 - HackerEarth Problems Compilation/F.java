import java.util.Scanner;
import java.math.BigInteger;

public class F {
	public static final int MAXN = 100009;
	public static final int INF = 2000000009;
	
	public static long A[], sum[], h;
	public static int n;

	public static long simulate(int i) {
		long lo = -1;
		long hi = INF;
		long j;
		BigInteger cur, d, dh, goal;
		while(hi > lo+1) {
			j = (hi + lo) / 2;
			d = BigInteger.valueOf(n*j+i);
			dh = d.multiply(d.add(BigInteger.ONE)).divide(BigInteger.valueOf(2));
			cur = BigInteger.valueOf(j*sum[n] + sum[i]);
                        goal = BigInteger.valueOf(h).subtract(dh);
			if (cur.compareTo(goal) >= 0) hi = j;
			else lo = j;
		}
		return hi;
	}

	public static void main(String[] args) {
		A = new long[MAXN];
		sum = new long[MAXN];
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		h = sc.nextLong();
		sum[0] = 0;
		for(int i=1; i<=n; i++) {
			A[i] = sc.nextLong();
			sum[i] = A[i] + sum[i-1];
		}
		long ans = INF*(long)INF;
		for(int i=1; i<=n; i++) {
			long cur = simulate(i);
			if (ans > cur*n + i) ans = cur*n + i;
		}
		System.out.println(ans);
	}
}