/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem J. Juggle with Criteria                                */
/*                                                                */
/* Original idea        Mikhail Dvorkin                           */
/* Problem statement    Mikhail Dvorkin                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Mikhail Dvorkin                           */
/******************************************************************/

import java.io.*;
import java.util.*;

public class juggle_md {
	private static String fileName = juggle_md.class.getSimpleName().replaceFirst("_.*", "").toLowerCase();
	private static String inputFileName = fileName + ".in";
	private static String outputFileName = fileName + ".out";
	private static Scanner in;
	private static PrintWriter out;

	public static int[][] allPermutations(int n) {
		if (n == 0) {
			return new int[][]{new int[]{}};
		}
		int[][] prev = allPermutations(n - 1);
		int[][] result = new int[prev.length * n][];
		for (int first = 0, count = 0; first < n; first++) {
			for (int[] p : prev) {
				int[] r = new int[n];
				r[0] = first;
				for (int i = 0; i < n - 1; i++) {
					r[i + 1] = p[i];
					if (r[i + 1] >= first) {
						r[i + 1]++;
					}
				}
				result[count++] = r;
			}
		}
		return result;
	}

	public static int[] criteria(int[] p, boolean cont) {
		int n = p.length;
		int inversions = 0;
		int localInversions = 0;
		int giSubsequence = 0;
		int giSubstring = 0;
		int fixedPoints = 0;
		int curSubstring = 0;
		int[] subsequence = new int[n];
		for (int i = 0; i < n; i++) {
			if (p[i] == i) {
				fixedPoints++;
			}
			if (i > 0 && p[i - 1] > p[i]) {
				localInversions++;
			}
			if (i == 0 || p[i - 1] > p[i]) {
				curSubstring = 1;
			} else {
				curSubstring++;
			}
			giSubstring = Math.max(giSubstring, curSubstring);
			subsequence[i] = 1;
			for (int j = 0; j < i; j++) {
				if (p[j] > p[i]) {
					inversions++;
				} else {
					subsequence[i] = Math.max(subsequence[i], subsequence[j] + 1);
				}
			}
			giSubsequence = Math.max(giSubsequence, subsequence[i]);
		}
		if (cont) {
			giSubstring = Math.max(giSubstring, curSubstring + 1);
		}
		return new int[]{
				inversions,
				localInversions,
				giSubsequence,
				giSubstring,
				fixedPoints,
		};
	}

	public void run() {
		int m = in.nextInt();
		int len = in.nextInt();
		int n = Math.min(len, 7);
		int[][] allPermutations = allPermutations(n);
		int[][] a = new int[allPermutations.length][];
		for (int i = 0; i < allPermutations.length; i++) {
			a[i] = criteria(allPermutations[i], len > n);
		}
		int c = a[0].length;
		int masks = (int) Math.pow(3, c);
		int[][] found1 = new int[masks][];
		int[][] found2 = new int[masks][];
		for (int i = 0; i < allPermutations.length; i++) {
			int[] ai = a[i];
			for (int j = 0; j < allPermutations.length; j++) {
				int[] aj = a[j];
				int mask = 0;
				for (int k = 0; k < c; k++) {
					mask *= 3;
					mask += 1 + Integer.compare(ai[k], aj[k]);
				}
				found1[mask] = allPermutations[i];
				found2[mask] = allPermutations[j];
			}
		}
		while (m --> 0) {
			String s = in.next();
			int mask = 0;
			for (int k = 0; k < c; k++) {
				mask *= 3;
				mask += "<=>".indexOf(s.charAt(k));
			}
			if (found1[mask] == null) {
				out.println("Not exists");
			} else {
				out.println("Exists");
				for (int[] found : new int[][]{found1[mask], found2[mask]}) {
					for (int i = 0; i < n; i++) {
						out.print((found[i] + 1) + " ");
					}
					for (int i = len; i > n; i--) {
						out.print(i + " ");
					}
					out.println();
				}
			}
		}
	}

	public static void main(String[] args) throws IOException {
		Locale.setDefault(Locale.US);
		in = new Scanner(new FileReader(inputFileName));
		out = new PrintWriter(outputFileName);
		new juggle_md().run();
		in.close();
		out.close();
	}
}

