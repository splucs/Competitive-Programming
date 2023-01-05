/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem C. Chemistry                                           */
/*                                                                */
/* Original idea        Maxim Buzdalov                            */
/* Problem statement    Anton Akhi                                */
/* Test set             Maxim Buzdalov                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Anton Akhi                                */
/******************************************************************/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class chemistry_aa {
	public static void main(String[] args) {
		new chemistry_aa().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;

	private void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new FileReader(FNAME + ".in"));
			out = new PrintWriter(FNAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(566);
		}
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	String FNAME = "chemistry";

	private void solve() throws IOException {
		int n = nextInt();
		long[][] a = new long[n + 1][n + 1];
		a[1][1] = 1;
		for (int i = 2; i < a.length; i++) {
			for (int j = 1; j < a[i].length; j++) {
				if (i == 2 && j == 4) {
					i += 0;
				}
				// 1
				a[i][j] = a[i - 1][j - 1];

				// 2
				// two different
				for (int l = 1; l < i - 1; l++) {
					for (int k = 1; k < j; k++) {
						a[i][j] += a[l][k] * a[i - 1][j - 1 - k];
					}
				}
				// same length different size
				for (int k = 1; k < j - 1 - k; k++) {
					a[i][j] += a[i - 1][k] * a[i - 1][j - 1 - k];
				}
				// same
				if (j % 2 == 1 && j > 1) {
					a[i][j] += a[i - 1][(j - 1) / 2]
							* (a[i - 1][(j - 1) / 2] + 1) / 2;
				}

				// 3
				// three different
				for (int l1 = 1; l1 < i - 1; l1++) {
					for (int k1 = 1; k1 < j; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int l2 = l1 + 1; l2 < i - 1; l2++) {
							for (int k2 = 1; k1 + k2 < j - 1; k2++) {
								sum += a[l2][k2] * a[i - 1][j - 1 - k1 - k2];
							}
						}
						a[i][j] += a[l1][k1] * sum;
					}
				}

				// same length i - 1
				for (int l1 = 1; l1 < i - 1; l1++) {
					for (int k1 = 1; k1 < j; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int k2 = 1; k2 < j - 1 - k1 - k2; k2++) {
							sum += a[i - 1][k2] * a[i - 1][j - 1 - k1 - k2];
						}
						if ((j - 1 - k1) % 2 == 0 && j - 1 - k1 > 0) {
							sum += a[i - 1][(j - 1 - k1) / 2]
									* (a[i - 1][(j - 1 - k1) / 2] + 1) / 2;
						}
						a[i][j] += a[l1][k1] * sum;
					}
				}

				// same length l1
				for (int l1 = 1; l1 < i - 1; l1++) {
					for (int k1 = 1; k1 < j; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int k2 = k1 + 1; 0 <= j - 1 - k1 - k2; k2++) {
							sum += a[l1][k2] * a[i - 1][j - 1 - k1 - k2];
						}
						a[i][j] += a[l1][k1] * sum;
						if (j - 1 - 2 * k1 > 0) {
							a[i][j] += a[l1][k1] * (a[l1][k1] + 1) / 2
									* a[i - 1][j - 1 - 2 * k1];
						}
					}
				}

				// same length different size
				for (int k1 = 1; k1 < j; k1++) {
					if (a[i - 1][k1] == 0) {
						continue;
					}
					long sum = 0;
					for (int k2 = k1 + 1; k2 < j - 1 - k1 - k2; k2++) {
						sum += a[i - 1][k2] * a[i - 1][j - 1 - k1 - k2];
					}
					a[i][j] += a[i - 1][k1] * sum;
				}

				// same length two + one
				for (int k1 = 1; 0 < j - 1 - 2 * k1; k1++) {
					if (j - 1 - 2 * k1 != k1) {
						a[i][j] += a[i - 1][k1] * (a[i - 1][k1] + 1) / 2
								* a[i - 1][j - 1 - 2 * k1];
					}
				}

				// all same
				if ((j - 1) % 3 == 0 && j > 1) {
					int k = (j - 1) / 3;
					a[i][j] += a[i - 1][k] * (a[i - 1][k] + 1)
							* (a[i - 1][k] + 2) / 6;
				}
			}
		}
		long ans = 0;
		for (int l = 2; l <= n; l++) {
			if (l % 2 == 0) {
				for (int k = 1; k < n - k; k++) {
					ans += a[l / 2][k] * a[l / 2][n - k];
				}
				if (n % 2 == 0) {
					ans += a[l / 2][n / 2] * (a[l / 2][n / 2] + 1) / 2;
				}
			} else {
				// 2
				// two different
				for (int k = 1; k < n - 1 - k; k++) {
					ans += a[l / 2][k] * a[l / 2][n - 1 - k];
				}
				// two same
				if (n % 2 == 1 && n - 1 > 0) {
					ans += a[l / 2][n / 2] * (a[l / 2][n / 2] + 1) / 2;
				}

				// 3
				// three different
				for (int l1 = 1; l1 < l / 2; l1++) {
					for (int k1 = 1; k1 < n; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int k2 = 1; k2 < n - 1 - k1 - k2; k2++) {
							sum += a[l / 2][k2] * a[l / 2][n - 1 - k1 - k2];
						}
						if ((n - 1 - k1) % 2 == 0 && (n - 1 - k1) > 0) {
							sum += a[l / 2][(n - 1 - k1) / 2]
									* (a[l / 2][(n - 1 - k1) / 2] + 1) / 2;
						}
						ans += a[l1][k1] * sum;
					}
				}

				// same length different size
				for (int k1 = 1; k1 < n; k1++) {
					if (a[l / 2][k1] == 0) {
						continue;
					}
					long sum = 0;
					for (int k2 = k1 + 1; k2 < n - 1 - k1 - k2; k2++) {
						sum += a[l / 2][k2] * a[l / 2][n - 1 - k1 - k2];
					}
					ans += a[l / 2][k1] * sum;
				}

				// same length two sizes
				for (int k1 = 1; k1 < n && n - 1 - 2 * k1 > 0; k1++) {
					if (n - 1 - 2 * k1 != k1) {
						ans += a[l / 2][k1] * (a[l / 2][k1] + 1) / 2
								* a[l / 2][n - 1 - 2 * k1];
					}
				}

				// all same
				if ((n - 1) % 3 == 0 && n - 1 > 0) {
					ans += a[l / 2][(n - 1) / 3] * (a[l / 2][(n - 1) / 3] + 1)
							* (a[l / 2][(n - 1) / 3] + 2) / 6;
				}

				// 4
				// different
				for (int l1 = 1; l1 < l / 2; l1++) {
					for (int k1 = 1; k1 < n; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int l2 = l1 + 1; l2 < l / 2; l2++) {
							for (int k2 = 1; k1 + k2 < n; k2++) {
								if (a[l2][k2] == 0) {
									continue;
								}
								// TODO: lol!
								long s2 = 0;
								for (int k = 1; k < n - 1 - k1 - k2 - k; k++) {
									s2 += a[l / 2][k]
											* a[l / 2][n - 1 - k1 - k2 - k];
								}
								if ((n - 1 - k1 - k2) % 2 == 0
										&& (n - 1 - k1 - k2) > 0) {
									s2 += a[l / 2][(n - 1 - k1 - k2) / 2]
											* (a[l / 2][(n - 1 - k1 - k2) / 2] + 1)
											/ 2;
								}
								sum += a[l2][k2] * s2;
							}
						}
						ans += a[l1][k1] * sum;
					}
				}

				// two + two
				for (int l1 = 1; l1 < l / 2; l1++) {
					for (int k1 = 1; k1 < n; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						long sum = 0;
						for (int k2 = k1 + 1; k1 + k2 < n; k2++) {
							if (a[l1][k2] == 0) {
								continue;
							}
							long s2 = 0;
							for (int k = 1; k < n - 1 - k1 - k2 - k; k++) {
								s2 += a[l / 2][k]
										* a[l / 2][n - 1 - k1 - k2 - k];
							}
							if ((n - 1 - k1 - k2) % 2 == 0
									&& (n - 1 - k1 - k2) > 0) {
								s2 += a[l / 2][(n - 1 - k1 - k2) / 2]
										* (a[l / 2][(n - 1 - k1 - k2) / 2] + 1)
										/ 2;
							}
							sum += a[l1][k2] * s2;
						}
						ans += a[l1][k1] * sum;
						for (int k = 1; k < n - 1 - 2 * k1 - k; k++) {
							ans += a[l1][k1] * (a[l1][k1] + 1) / 2
									* a[l / 2][k]
									* a[l / 2][n - 1 - 2 * k1 - k];
						}
						if ((n - 1 - 2 * k1) % 2 == 0 && (n - 1 - 2 * k1) > 0) {
							ans += a[l1][k1] * (a[l1][k1] + 1) / 2
									* a[l / 2][(n - 1 - 2 * k1) / 2]
									* (a[l / 2][(n - 1 - 2 * k1) / 2] + 1) / 2;
						}
					}
				}

				// one + three
				for (int l1 = 1; l1 < l / 2; l1++) {
					for (int k1 = 1; k1 < n; k1++) {
						if (a[l1][k1] == 0) {
							continue;
						}
						for (int k2 = 1; k2 < n - k1; k2++) {
							if (a[l / 2][k2] == 0) {
								continue;
							}
							for (int k3 = k2 + 1; k3 < n - 1 - k1 - k2 - k3; k3++) {
								ans += a[l1][k1] * a[l / 2][k2] * a[l / 2][k3]
										* a[l / 2][n - 1 - k1 - k2 - k3];
							}
						}
						for (int k2 = 1; k2 < n - k1; k2++) {
							if (n - 1 - k1 - 2 * k2 > 0
									&& k2 != n - 1 - k1 - 2 * k2) {
								ans += a[l1][k1] * a[l / 2][k2]
										* (a[l / 2][k2] + 1) / 2
										* a[l / 2][n - 1 - k1 - 2 * k2];
							}
						}
						if ((n - 1 - k1) % 3 == 0 && (n - 1 - k1) > 0) {
							ans += a[l1][k1] * a[l / 2][(n - 1 - k1) / 3]
									* (a[l / 2][(n - 1 - k1) / 3] + 1)
									* (a[l / 2][(n - 1 - k1) / 3] + 2) / 6;
						}
					}
				}

				// all four
				// all different
				for (int k1 = 1; k1 < n; k1++) {
					if (a[l / 2][k1] == 0) {
						continue;
					}
					for (int k2 = k1 + 1; k1 + k2 < n; k2++) {
						if (a[l / 2][k2] == 0) {
							continue;
						}
						for (int k3 = k2 + 1; k3 < n - 1 - k1 - k2 - k3; k3++) {
							ans += a[l / 2][k1] * a[l / 2][k2] * a[l / 2][k3]
									* a[l / 2][n - 1 - k1 - k2 - k3];
						}
					}
				}

				// two + one + one
				for (int k1 = 1; k1 < n; k1++) {
					if (a[l / 2][k1] == 0) {
						continue;
					}
					for (int k2 = 1; k2 < n - 1 - 2 * k1 - k2; k2++) {
						if (k2 == k1 || k1 == (n - 1 - k2 - 2 * k1)
								|| a[l / 2][k2] == 0) {
							continue;
						}
						ans += a[l / 2][k1] * (a[l / 2][k1] + 1) / 2
								* a[l / 2][k2] * a[l / 2][n - 1 - 2 * k1 - k2];
					}
					if ((n - 1 - 2 * k1) % 2 == 0 && (n - 1 - 2 * k1) > 0
							&& (n - 1 - 2 * k1) > 2 * k1) {
						ans += a[l / 2][k1] * (a[l / 2][k1] + 1) / 2
								* a[l / 2][(n - 1 - 2 * k1) / 2]
								* (a[l / 2][(n - 1 - 2 * k1) / 2] + 1) / 2;
					}
				}

				// one + three
				for (int k1 = 1; k1 < n; k1++) {
					if (n - 1 - 3 * k1 < 0 || n - 1 - 3 * k1 == k1) {
						continue;
					}
					ans += a[l / 2][k1] * (a[l / 2][k1] + 1)
							* (a[l / 2][k1] + 2) / 6 * a[l / 2][n - 1 - 3 * k1];
				}

				// all four
				if ((n - 1) % 4 == 0 && n - 1 > 0) {
					ans += a[l / 2][(n - 1) / 4] * (a[l / 2][(n - 1) / 4] + 1)
							* (a[l / 2][(n - 1) / 4] + 2)
							* (a[l / 2][(n - 1) / 4] + 3) / 24;
				}

			}
		}
		out.println(Math.max(ans, 1));
	}
}

