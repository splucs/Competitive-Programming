import java.math.BigInteger;
import java.util.Scanner;

public final class F {
	public static BigInteger x, y;
	
	static BigInteger extGcd(BigInteger a, BigInteger b) {
		if (b.compareTo(BigInteger.ZERO) == 0) {
			x = BigInteger.ONE; y = BigInteger.ZERO;
			return a;
		}
		else {
			BigInteger g = extGcd(b, a.remainder(b));
			BigInteger tmp = x;
			x = y;
			y = tmp;
			y = y.subtract(a.divide(b).multiply(x));
			return g;
		}
	}
	
	static BigInteger crt(BigInteger rem[], BigInteger mod[], int n) {
		if (n == 0) return BigInteger.ZERO;
		BigInteger ans = rem[0], m = mod[0];
		for(int i = 1; i < n; i++) {
			BigInteger g = extGcd(mod[i], m);
			if (ans.subtract(rem[i]).remainder(g).compareTo(BigInteger.ZERO) != 0) {
				return null;
			}
			ans = ans.add(rem[i].subtract(ans).multiply(m.divide(g)).multiply(y));
			m = (mod[i].divide(g)).multiply(m.divide(g)).multiply(g);
			ans = (ans.remainder(m).add(m)).remainder(m);
		}
		return ans;
	}
	
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int B, Z;
		B = sc.nextInt();
		Z = sc.nextInt();
		int P[][] = new int[B][Z+1];
		int fst[][] = new int[B][Z+1];
		int scd[][] = new int[B][Z+1];
		
		for(int b = 0; b < B; b++) {
			for(int z = 0; z <= Z; z++) {
				P[b][z] = sc.nextInt();
				fst[b][z] = -1;
				scd[b][z] = -1;
			}
		}
		
		
		
		for (int b = 0; b < B; b++) {
			int k = P[b][0];
			int tempo = 0;
			while (true) {
				if (fst[b][k] == -1) {
					fst[b][k] = tempo;
				} else if (scd[b][k] == -1) {
					scd[b][k] = tempo;
				} else {
					break;
				}
				k = P[b][k];
				tempo++;
			}
		}
		int bstNum = -1;
		BigInteger bestTempo = BigInteger.ZERO;
		for (int z = 1; z <= Z; z++) {
			BigInteger rem[] = new BigInteger[B];
			BigInteger mod[] = new BigInteger[B];
			
			boolean ok = true;
			int rep = -1;
			for (int b = 0; b < B; b++) {
				if (fst[b][z] == -1) {
					ok = false;
				} else if (scd[b][z] == -1) {
					if (rep == -1) rep = fst[b][z];
					else if (rep != fst[b][z]) ok = false;
				}

				rem[b] = BigInteger.valueOf(fst[b][z]);
				mod[b] = BigInteger.valueOf(scd[b][z] - fst[b][z]);
			}
			if (!ok) continue;
			if (rep != -1) {
				// Check remainder = rep
				for (int b = 0; b < B; b++) {
					int xxx = mod[b].intValue();
					int yyy = rem[b].intValue();
					if (rep%xxx != yyy) ok = false;
				}
				if (ok) {
					BigInteger xxx = BigInteger.valueOf(rep);
					if (bstNum == -1 || xxx.compareTo(bestTempo) < 0) {
						bestTempo = xxx;
						bstNum = z;
					}
				}
			} else {
				BigInteger xxx = crt(rem, mod, B);
				if (xxx != null) {
					if (bstNum == -1 || xxx.compareTo(bestTempo) < 0) {
						bestTempo = xxx;
						bstNum = z;
					}
				}
			}
		}
		
		if (bstNum == -1) {
			System.out.println("*");
		} else {
			System.out.println(bstNum + " " + bestTempo);
		}
	}
}