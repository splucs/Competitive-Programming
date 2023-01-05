import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public final class I {
	static class Participant {
		BigInteger val;
		String name;
		boolean ok;
		public Participant(String _name, BigInteger _val) {
			name = _name;
			val = _val;
			ok = false;
		}
	}

	static class ValComparator implements Comparator<Participant> {
		@Override
		public int compare(Participant a, Participant b) {
			return a.val.compareTo(b.val);
		}
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);

		ArrayList<Participant> arr = new ArrayList<>();

		int n = sc.nextInt();
		BigInteger s = sc.nextBigInteger();

		for(int i = 0; i < n; i++) {
			String name = sc.next();
			BigInteger val = sc.nextBigInteger();
			arr.add(new Participant(name, val));
		}

		Collections.sort(arr, new ValComparator());
		
		//for (Participant p : arr) {
		//	System.out.println(p.name + " " + p.val);
		//}

		for(int i = 0; i < n; i++) {
			BigInteger cur = s;
			ArrayList<Participant> in = new ArrayList<>();
			for(int j = i; j >= 0; j--) {
				Participant p = arr.get(j);
				if (p.val.compareTo(cur) <= 0) {
					in.add(p);
					cur = cur.subtract(p.val);
				}
				if (cur.compareTo(BigInteger.ZERO) == 0)break;
			}
			if (cur.compareTo(BigInteger.ZERO) != 0) continue;
			for (Participant p : in) {
				p.ok = true;
			}
		}

		ArrayList<Participant> ans = new ArrayList<>();
		for (Participant p : arr) {
			if (p.ok) ans.add(p);
		}

		System.out.println(ans.size());
		for (Participant p : ans) {
			System.out.println(p.name);
		}
	}
}