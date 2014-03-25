import java.io.FileInputStream;
import java.util.Scanner;

class Algorithm {
	static boolean DBG = false;
	static final int maxn = 505;
	
	static void Logd(String str) {
		if (!DBG) return;
		System.err.println(str);
	}
	
	static void prln(String str) {
		System.out.println(str);
	}
	
	static int N;
	static Integer rank[];
	
	// returns min,cost,cases
	int[] solve(int left, int right) {
		int i;
		int imin = left, cost = 0;
		int cases = 1, pairings = 0;		
		
		// base (single number)
		if (left == right)
			return new int[]{rank[left], 0, 1};
		
		for (i = left; i <= right; i++)
			if (rank[i] < rank[imin])
				imin = i;
		
		if (imin > left) {
			int[] res = solve(left, imin - 1);
			cost += res[1] + res[0] - rank[imin];
			cases *= res[2];
			pairings++;
		}
		
		if (imin < right) {
			int[] res = solve(imin + 1, right);
			cost += res[1] + res[0] - rank[imin];
			cases *= res[2];
			pairings++;
		}

		cases *= pairings;
		
		return new int[]{rank[imin], cost, cases};
	}
	
	public static void main(String args[]) throws Exception	{
		Scanner sc = new Scanner(System.in);
//		Scanner sc = new Scanner(new FileInputStream("company_track_meet.txt"));
		
		int T = sc.nextInt();
		for (int test_case = 0; test_case < T; test_case++) {
			
			N = sc.nextInt();
			rank = new Integer[N];
			
			for (int i = 0; i < N; i++)
				rank[i] = sc.nextInt();

			Algorithm algo = new Algorithm();
			int[] res = algo.solve(0, N - 1);
			prln(res[1] + "\n" + res[2] + "\n");
		}
	}
}
