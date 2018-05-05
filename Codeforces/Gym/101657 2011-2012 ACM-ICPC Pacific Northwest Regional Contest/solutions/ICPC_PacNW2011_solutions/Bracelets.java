import java.io.File;
import java.util.Arrays;
import java.util.Scanner;


public class Bracelets {
  static int[][] dp = new int[2048][4096];
  static char[] s, t;
  static int m, n;
  
  static int lcs(int start, int left, int right, int[] lbound, int[] rbound) {
    if (right - left <= 1) return 0;
    int answer = 0;
    
    int[] nlbound = new int[2048];
    int[] nrbound = new int[2048];
    
    dp[start][0] = 0;
    for (int i = 0; i <= m; i++) {
      for (int j = Math.max(start, lbound[i]); j <= rbound[i]; j++) {
        if (i == 0 && j == start) continue;
        if (i == 0) {
          dp[i][j] = dp[i][j-1];
        } else if (j == start) {
          dp[i][j] = dp[i-1][j];
        } else {
          dp[i][j] = 0;
          if (j <= rbound[i-1]) {
            dp[i][j] = dp[i-1][j];
          }
          if (j-1 <= rbound[i-1] && j > lbound[i-1] && s[i-1] == t[j-1] && dp[i-1][j-1] + 1 > dp[i][j]) {
            dp[i][j] = dp[i-1][j-1] + 1;
          }
          if (j > lbound[i] && dp[i][j-1] > dp[i][j]) {
            dp[i][j] = dp[i][j-1];
          }
        }
      }
    }
    
    answer = dp[m][start + n];
    
    int j = start + n;
    int i = m;
    while (i >= 0 && j >= start) {
      nlbound[i] = j;
      if (i > 0 && j <= rbound[i-1] && dp[i][j] == dp[i-1][j]) {
        i--;
      } else if (i > 0 && j > start && lbound[i-1] < j && j-1 <= rbound[i-1] && s[i-1] == t[j-1] && dp[i][j] == dp[i-1][j-1]+1) {
        i--; j--;
      } else {
        j--;
      }
    }
    j = start + n;
    for (i = m; i >= 0; i--) {
      nrbound[i] = j;
      while (lbound[i] < j && dp[i][j] == dp[i][j-1]) {j--;}
      if (i > 0 && j > start && lbound[i-1] < j && j-1 <= rbound[i-1] && s[i-1] == t[j-1] && dp[i][j] == dp[i-1][j-1]+1) j--;
    }
    
    if (start == 0) {
      for (i = 0; i <= m; i++) nrbound[i] += n;
      answer = Math.max(answer, lcs(n / 2, 0, n, nlbound, nrbound));
    } else {
      answer = Math.max(answer, lcs((start + left) / 2, left, start, lbound, nrbound));
      answer = Math.max(answer, lcs((start + right) / 2, start, right, nlbound, rbound));
    }
    
    return answer;
  }
  
  public static void main(String[] args) throws Exception {
    Scanner in = new Scanner(new File("bracelets.in"));
    int[] lbound = new int[2048];
    int[] rbound = new int[2048];
    
    while (in.hasNext()) {
      String S = in.next(), T = in.next();
      if (S.length() < T.length()) {String swap = S; S = T; T = swap;}
      
      m = S.length();
      n = T.length();
      
      if (n == 1) {
        System.out.println(S.contains(T) ? 2 : 0);
        continue;
      }
      
      Arrays.fill(lbound, 0);
      Arrays.fill(rbound, n);
      
      s = S.toCharArray();
      t = new char[T.length() * 2];
      for (int i = 0; i < T.length(); i++) {
        t[i] = T.charAt(i);
        t[i+n] = T.charAt(i);
      }
      
      int answer = lcs(0, 0, n, lbound, rbound);
      s = new StringBuffer(S).reverse().toString().toCharArray();
      answer = Math.max(answer, lcs(0, 0, n, lbound, rbound));
      
      System.out.println(2 * answer);
    }
  }
}
