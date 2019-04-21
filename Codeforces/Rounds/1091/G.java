import java.math.BigInteger;
import java.util.Scanner;

public final class G {

/*	T pollard(T n) {
	int i = 0, k = 2, d;
	T x = 3, y = 3;
	while (true) {
		i++;
		x = (modMul(x, x, n) + n - 1) % n;
		d = gcd(abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (i == k) y = x, k *= 2;
	}
}*/

	public static boolean hastime() {
		return System.nanoTime() < 5900000000L;
	}

	public static BigInteger gcd(BigInteger x, BigInteger y) {
		if (y == BigInteger.ZERO) return x;
		return gcd(y, x.remainder(y));
	}

	public static BigInteger pollard(BigInteger n) {

		final long LIMIT = 90000000000000L;

		if (n.compareTo(BigInteger.valueOf(LIMIT)) <= 0) {
			for(long i = 2; i*i <= LIMIT; i++) {
				if (n.remainder(BigInteger.valueOf(i)) == BigInteger.ZERO) {
					return BigInteger.valueOf(i);
				}
			}
			return BigInteger.ZERO;
		}

		BigInteger i = BigInteger.ZERO;
		BigInteger k = BigInteger.valueOf(2);
		BigInteger d;
		BigInteger x = BigInteger.valueOf(3);
		BigInteger y = x;
		while(hastime()) {
			i = i.add(BigInteger.ONE);
			x = x.multiply(x).remainder(n).add(n).subtract(BigInteger.ONE).remainder(n);
			d = gcd(y.subtract(x), n);
			if (d.compareTo(BigInteger.ONE) != 0 && d.compareTo(n) != 0) return d;
			if (i.compareTo(k) == 0) {
				y = x;
				k = k.multiply(BigInteger.valueOf(2));
			}
		}
		return BigInteger.ZERO;
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		BigInteger n = sc.nextBigInteger();

		BigInteger ans[] = new BigInteger[10];
		int cnt = 0;
		while(true) {
			BigInteger p = pollard(n);
			if (p == BigInteger.ZERO) break;
			ans[cnt++] = p;
			n = n.divide(p);
		}

		System.out.print("! " + cnt);
		for(int i = 0; i < cnt; i++) {
			System.out.print(" " + ans[i]);
		}
		System.out.println("");
	}
}