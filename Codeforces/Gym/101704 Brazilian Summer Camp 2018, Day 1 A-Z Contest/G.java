import java.util.*;
import java.math.BigInteger;

public final class G {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		BigInteger fat[] = new BigInteger[n];
		fat[0] = BigInteger.ONE;
		for(int i = 1; i < n; i++) {
			fat[i] = BigInteger.valueOf(i).multiply(fat[i-1]);
		}
		BigInteger k = sc.nextBigInteger();
		k = k.subtract(BigInteger.ONE);
		int arr[] = new int[n];
		for(int i = 0; i < n; i++) arr[i] = i+1;
		for(int i = 0; i < n; i++) {
			//System.out.println("k = " + k);
			
			int pos = k.divide(fat[n-i-1]).intValue();
			int tmp = arr[i];
			arr[i] = arr[i+pos];
			arr[i+pos] = tmp;
			Arrays.sort(arr, i+1, n);
			//System.out.println("pos = " + pos + " change " + i + " " + (i+pos));
			k = k.remainder(fat[n-i-1]);
			System.out.print(arr[i] + " ");
		}
		System.out.print("\n");
	}
}