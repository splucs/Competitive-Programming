import java.util.Scanner;
import java.math.BigInteger;

public final class Y {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		BigInteger F[] = new BigInteger[n+1];
		F[0] = BigInteger.ZERO;
		if (n > 0) F[1] = BigInteger.ONE;
		if (n > 1) F[2] = BigInteger.ONE;
		for(int i = 3; i <= n; i++) {
			F[i] = F[i-1].add(F[i-3]);
		}
		System.out.println(F[n]);
	}
}