import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;

public class CodeJam16Q3 {
    static int N, K;
    static Random rand = new Random();

    static int maxFactor = 10000;
    static boolean[] primeTable; // false means prime, true non-prime
    static long[] factors = new long[11]; 

    static void makePrimeTable() {
        primeTable = new boolean[maxFactor + 1];
        int i;
        for (i = 2; i <= maxFactor; i++) {
            if (primeTable[i])
                continue;
            for (int j = i * 2; j <= maxFactor; j += i) {
                primeTable[j] = true; // non-prime
            }
        }

        // Show primetable
        if (false) {
            for (i = 2; i <= maxFactor; i++)
                if (!primeTable[i])
                    System.out.print(i + " ");
        }
    }

    // return -1 if a factor cannot be found (don't care if it is prime or not)
    static long findFactor(long num) {
        long nonTrialMax = Math.min(num - 1, maxFactor);
        for (int i = 2; i <= nonTrialMax; i++) {
            if (primeTable[i])
                continue;
            if (num % i == 0)
                return i;
        }
        return -1;
    }

    static void solve(PrintStream out) {
        boolean[] largeNum = new boolean[N];
        HashSet<String> usedNumbers = new HashSet<String>();

        int goodCount = 0;
        while (goodCount < K) {
            // Generate the number
            largeNum[0] = largeNum[N - 1] = true;
            StringBuilder sb = new StringBuilder();
            sb.append("1");
            for (int i = N - 2; i >= 1; i--) {
                largeNum[i] = rand.nextBoolean();
                sb.append(largeNum[i] ? "1" : "0");
            }
            sb.append("1");
            String numString = sb.toString();

            if (usedNumbers.contains(numString))
                continue; // try next

            boolean goodNum = true;
            for (int base = 2; base <= 10; base++) {
                // Convert to bases
                long value = 0L;
                long mult = 1L;
                for (int i = 0; i < N; i++) {
                    if (largeNum[i])
                        value += mult;
                    mult *= base;
                }

                // System.err.println(base + ":" + value);

                // Verify non-primeness
                factors[base] = findFactor(value);
                if (factors[base] < 0) {
                    goodNum = false;
                    break;
                }
            }

            if (goodNum) {
                // print
                out.print(numString);
                for (int base = 2; base <= 10; base++)
                    out.print(" " + factors[base]);
                
                out.println();
                goodCount++;
                usedNumbers.add(numString);
            }
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        String filename = "C-small";
        String inFilename = filename + ".in";
        String outFilename = filename + ".out";
        Scanner in = null;

        makePrimeTable();

        boolean outputToFile = true;
        PrintStream ps = !outputToFile
                ? System.out
                : new PrintStream(new File(outFilename));
        try {
            in = new Scanner(new File(inFilename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        int testCases = in.nextInt();
        for (int tc = 1; tc <= testCases; tc++) {
            N = in.nextInt();
            K = in.nextInt();
            ps.println("Case #" + tc + ":");
            solve(ps);
        }
    }
}