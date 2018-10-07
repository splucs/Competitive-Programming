import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.math.*;

public final class E {

	public static int n;
	public static BigInteger k;
	public static Set<BigInteger> used = new TreeSet<>();

	public static class Truple {
		public BigInteger a, b, c;
		public Truple(BigInteger _a, BigInteger _b, BigInteger _c) {
			a = _a; b = _b; c = _c;
		}
		public Truple adj1() {
			BigInteger kb = k.multiply(b);
			BigInteger kc = k.multiply(c);
			BigInteger d = kb.add(kc).subtract(a);
			return new Truple(d, b, c);
		}
		public Truple adj3() {
			BigInteger ka = k.multiply(a);
			BigInteger kc = k.multiply(c);
			BigInteger d = kc.add(ka).subtract(b);
			return new Truple(a, d, c);
		}
		public Truple adj2() {
			BigInteger ka = k.multiply(a);
			BigInteger kb = k.multiply(b);
			BigInteger d = ka.add(kb).subtract(c);
			return new Truple(a, b, d);
		}
	}

	public static final Queue<Truple> q = new ArrayBlockingQueue<>(10000000);

	public static void insert(Truple u) {
		if (n == 0) return;
		if (BigInteger.ZERO.compareTo(u.a) >= 0
		 || BigInteger.ZERO.compareTo(u.b) >= 0
		 || BigInteger.ZERO.compareTo(u.c) >= 0) {
			return;
		}
		q.add(u);
		if (used.contains(u.a)
		 || used.contains(u.b)
		 || used.contains(u.c)) {
			return;
		}
		used.add(u.a);
		used.add(u.b);
		used.add(u.c);
		n--;
		System.out.println(u.a + " " + u.b + " " + u.c);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		k = sc.nextBigInteger();
		n = sc.nextInt();
		q.add(new Truple(BigInteger.ZERO, BigInteger.ONE, k));
		while(n > 0) {
			Truple u = q.remove();
			insert(u.adj1());
			insert(u.adj2());
			insert(u.adj3());
		}
		sc.close();
	}
}