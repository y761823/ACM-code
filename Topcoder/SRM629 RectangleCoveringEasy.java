// BEGIN CUT HERE

// END CUT HERE
import java.util.*;
import java.io.*;
import java.math.*;

public class RectangleCoveringEasy {
	public int solve(int holeH, int holeW, int boardH, int boardW) {
		if(holeH > holeW) {
			int t = holeH; holeH = holeW; holeW = t;
		}
		if(boardH > boardW) {
			int t = boardH; boardH = boardW; boardW = t;
		}
		if(holeH == boardH && holeW == boardW) return -1;
		if(holeH <= boardH && holeW <= boardW) return 1;
		else return -1;
	}
	public static void main(String[] args) {
		RectangleCoveringEasy temp = new RectangleCoveringEasy();
		Scanner in = new Scanner(System.in);
		int holeH = in.nextInt(), holeW = in.nextInt(), boardH = in.nextInt(), boardW = in.nextInt();
		System.out.println(temp.solve(holeH, holeW, boardH, boardW));
		in.close();
	}
}
