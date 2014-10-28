import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class poj1737_ConnectedGraph {
	Scanner scan;

	BigInteger C[][] = new BigInteger[55][55];
	BigInteger p[] = new BigInteger[1300];
	BigInteger ans[] = new BigInteger[55];

	BigInteger ONE = BigInteger.valueOf(1);

	int n;

	public poj1737_ConnectedGraph(Scanner sc) {
		scan = sc;
	}

	void run() {
		init();
		do {
			n = scan.nextInt();
			if (n == 0) break;
			System.out.println(solve());
		} while(true);
	}

	void init() {
		int i, j;
		for (i = 1; i <= 50; i++)
			C[i][0] = C[i][i] = ONE;
		
		for (i = 2; i <= 50; i++)
			for (j = 1; j < i; j++)
				C[i][j] = C[i - 1][j].add(C[i - 1][j - 1]);
		
		p[0] = ONE;
		for (i = 1; i < 1300; i++)
			p[i] = p[i-1].multiply(BigInteger.valueOf(2));
		
		ans[1] = ans[2] = ONE;
		ans[3] = BigInteger.valueOf(4);
		
		for (i = 4; i <= 50; i++) {
			ans[i] = p[(i - 1) * i / 2];
			for (j = 1; j < i; j++)
				ans[i] = ans[i].subtract(
							ans[j].multiply(
									C[i-1][j-1].multiply(p[(i-j) * (i-j-1) / 2])));
		}
	}
	
	BigInteger solve() {
		return ans[n];
	}

	public static void main(String args[]) throws FileNotFoundException {
		InputStream is = System.in;
		File file = new File(System.getProperty("user.dir")+"/" + 
				"poj1737_ConnectedGraph.txt");

		Scanner scan = new Scanner(file);
		
		poj1737_ConnectedGraph poj = new poj1737_ConnectedGraph(scan);
		poj.run();
	}
}
