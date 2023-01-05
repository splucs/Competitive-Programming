/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem E. Electricity                                         */
/*                                                                */
/* Original idea        Vitaly Aksenov                            */
/* Problem statement    Sergey Poromov                            */
/* Test set             Sergey Poromov                            */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Sergey Poromov                            */
/******************************************************************/

import java.util.*;
import java.io.*;

public class Tests {
	Random random = new Random(2556630);
	
	static final int MAXN = 100000;
	static final int MAX = 1000;
	
	void genRand(int n, int m, int MAXA, int MAXB) {
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = random.nextInt(MAXA) + 1;
		}
		int[] b = new int[m];
		for (int i = 0; i < m; i++) {
			b[i] = random.nextInt(MAXB) + 1;
		}
		printTest(a, b);
	}
	
	void genMax(int n, int m) {
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = MAX;
		}
		int[] b = new int[m];
		for (int i = 0; i < m; i++) {
			b[i] = MAX;
		}
		printTest(a, b);
	}
	
	void sample1() {
		printTest(new int[]{3, 2, 1}, new int[]{2, 3});
	}
	
	void sample2() {
		printTest(new int[]{2, 2}, new int[]{2, 3, 1});
	}
	
	void run() {
		sample1();
		sample2();
		
		genRand(10, 10, 100, 100);
		genRand(10, 10, 10, 100);
		genRand(10, 10, 100, 10);
		genRand(10, 100, 10, 100);
		genRand(100, 10, 100, 10);
		genRand(MAXN, MAXN, MAX, MAX);
		genRand(MAXN, MAXN, MAX, MAX);
		genMax(MAXN, MAXN);
		genMax(1, MAXN);
		genMax(MAXN, 1);
		genRand(1, MAXN, 1, MAX);
		genRand(MAXN, 1, MAX, 1);
	}
	
	int testsCount = 0;
	
	void printTest(int[] a, int[] b) {
		new File("tests").mkdir();
		PrintWriter out = null;
		try {
			out = new PrintWriter("tests/" + String.format("%02d", ++testsCount));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		out.println(a.length + " " + b.length);
		for (int i = 0; i < a.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(a[i]);
		}
		out.println();
		for (int i = 0; i < b.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(b[i]);
		}
		out.println();
		out.close();
	}
	
	public static void main(String[] args) {
		new Tests().run();
	}
}

