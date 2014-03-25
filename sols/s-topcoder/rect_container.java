/*
In S-Topcoder Contest,

You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

import java.io.FileInputStream;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.util.TreeSet;
import java.util.Vector;

/*
   As the name of the class should be Algorithm , using Algorithm.java as the filename is recommended.
   In any case, you can execute your program by running 'java Algorithm' command.
 */

class Rect {
	int x, y;
	int width, height;
};

class BottomLeftComp implements Comparator<Rect>{
    @Override
    public int compare(Rect r1, Rect r2) {
        if (r1.x == r2.x)
        	return r1.y - r2.y;
        else
        	return r1.x - r2.x;
    }
}

class Algorithm {
	static boolean DBG = false;
	static final int maxn = 1005;		
	static final int MAXITER = 100;
	static final int INF = 1000000;		
	
	static void Logd(String str) {
		if (!DBG) return;
		System.err.println(str);
	}
	
	static void prln(String str) {
		System.out.println(str);
	}
	
	int N;
	TreeSet<Rect> cells = new TreeSet<Rect>(new BottomLeftComp());
	Vector<Rect> rects = new Vector<Rect>();
	int boundX, boundY;
	
	int bestArea, bestW, bestH;
	Vector<Rect> bestRects = new Vector<Rect>();
	
	Rect newRect(int w, int h) {
		Rect res = new Rect();
		res.width = w; res.height = h;
		res.x = res.y = 0;
		return res;
	}
	
	void initCells(int maxHeight, int maxWidth) {		
		cells.clear();
		Rect r = newRect(maxWidth, maxHeight);
		cells.add(r);
	}
	
	void insertCell(Rect r) {
		cells.add(r);
	}
	
	class SpaceInCell {
		Rect rect;
		int x, y;
		SpaceInCell(Rect r, int _x, int _y) {
			rect = r; x = _x; y = _y;
		}
	}
	
	SpaceInCell findSpaceInCells(int size) {
		if (cells.size() == 0)
			return null;
		
		// find first column and first row
		for (Rect r : cells) {
			if (r.height >= size && r.width >= size) {
				return new SpaceInCell(r, r.x, r.y);
			}
		}
		return null;
	}
	
	void allocFromCell(Rect cell, Rect rect) {
		// tricky
		int leftCol = rect.x - cell.x;
		int bottomRow = rect.y - cell.y;
		int topRow = cell.y + cell.height - (rect.y + rect.height);
		int rightRow = cell.x + cell.width - (rect.x + rect.width);

		Rect r;
		int oldCellHeight = cell.height;
		int oldCellX = cell.x;
		int oldCellY = cell.y;

		// cell is removed
		if (leftCol == 0 && bottomRow == 0) {
			cells.remove(cell);
		} else {
			if (leftCol > 0)
				cell.width = leftCol;
			if (bottomRow > 0) {
				// below rect
				if (leftCol > 0) {
					// add
					r = newRect(rect.x, bottomRow);
					r.x = cell.x + leftCol;
					r.y = cell.y;
					insertCell(r);
				} else {
					// modify current
					cell.height = bottomRow;
					cell.width = rect.width;
				}
			}
		}

		if (topRow > 0) {
			// above rect
			r = newRect(rect.width, topRow);
			r.x = oldCellX + leftCol;
			r.y = rect.y + rect.height;
			insertCell(r);
		}
		if (rightRow > 0) {
			// right of rect
			r = newRect(rightRow, oldCellHeight);
			r.x = rect.x + rect.width;
			r.y = oldCellY;
			insertCell(r);
		}
	}
	
	void clearRects() {
		boundX = boundY = 0;
		rects.clear();
	}
	
	void addRect(Rect r) {
		boundX = Math.max(boundX, r.x + r.width);
		boundY = Math.max(boundY, r.y + r.height);
		rects.add(r);
	}
	
	class Point {
		int x, y;
		Point (int _x, int _y) {
			x = _x; y = _y;
		}
	}
	
	// updates boundX and boundY as new bounding rect
	boolean basicGreedy(Integer side[]) {
		int i;
		int h, w;
		
		// init
		h = side[0];
		w = 0;

		for (i=0; i<N; i++) {
			// greedy alloc
			SpaceInCell sc = findSpaceInCells(side[i]);

			if (sc != null) {
				// place the rect in cell
				Rect newR = newRect(side[i], side[i]);
				newR.x = sc.x;
				newR.y = sc.y;
				allocFromCell(sc.rect, newR);
				addRect(newR);
			} else
				return false;
		}

		return true;
	}
	
	boolean tryPack(Integer side[], int w, int h) {
		initCells(h, w);
		clearRects();
		return basicGreedy(side);
	}
	
	void saveSol(int w, int h) {
		bestArea = w * h;
		bestW = w;
		bestH = h;
		bestRects.clear();
		bestRects.addAll(rects);
	}
	
	void solve(int N, Integer side[]) {
		int i,j,d;
		this.N = N;
		Arrays.sort(side, Collections.reverseOrder());
		initCells(side[0], INF);
		clearRects();

		// find upperbound with greedy
		int wu, hu;
		basicGreedy(side);
		wu = boundX; hu = boundY;
		
		saveSol(wu, hu); // baseline solution

		int iters = 0;
		int tryw = wu - 1, tryh = hu + 1;

		// Search with at most MAXITER iterations
		while (iters++ < MAXITER) {
			Logd("ITER#" + iters + " area=" + tryw * tryh + "(" + tryw + "x" + tryh + ")\n");
			boolean possible = tryPack(side, tryw, tryh);

			if (possible) {
				// Save solution
				if (tryw * tryh < bestArea)
					saveSol(tryw, tryh);
				tryw -= Math.max(1, tryw / (1 + MAXITER - iters));
			} else
				tryh += Math.max(1, tryh / (1 + MAXITER - iters));

			Logd(possible + "\n");
		}
		
		prln(bestW + " " + bestH);
		
		for (Rect r : bestRects)
			prln(r.width + " " + r.x + " " + r.y);
	}
	
	public static void main(String args[]) throws Exception	{
		/*
		   The method below means that the program will read from input.txt, instead of standard(keyboard) input.
		   To test your program, you may save input data in input.txt file,
		   and call below method to read from the file when using nextInt() method.
		   You may remove the comment symbols(//) in the below statement and use it.
		   But before submission, you must remove the freopen function or rewrite comment symbols(//).
		 */		

		/*
		   Make new scanner from standard input System.in, and read data.
		 */
		Scanner sc = new Scanner(System.in);
//		Scanner sc = new Scanner(new FileInputStream("rect_container.txt"));

		int N;
		
		Integer side[];
		
		int T = sc.nextInt();
		for (int test_case = 0; test_case < T; test_case++) {
			
			N = sc.nextInt();
			side = new Integer[N];
			
			for (int i = 0; i < N; i++)
				side[i] = sc.nextInt();
			
			// Print the answer to standard output(screen).
			System.out.println("Case #"+(test_case+1));
			
			Algorithm algo = new Algorithm();
			algo.solve(N, side);
		}
	}
}
