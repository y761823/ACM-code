// BEGIN CUT HERE

// END CUT HERE
import java.util.*;
import java.math.*;
public class CandyMaking {
	static final double EPS = 1e-16;
	
	int c[], d[];
	int n;
	
	int sgn(double x) {
		if(x > EPS) return 1;
		if(x < -EPS) return -1;
		return 0;
	}
	
	double sum(double x) {
		double res = 0;
		for(int i = 0; i < n; ++i) {
			res += Math.abs(x * c[i] - d[i]);
		}
		return res;
	}

	public double findSuitableDensity(int[] containerVolume, int[] desiredWeight) {
		c = containerVolume; d = desiredWeight;
		n = c.length;
		double res = 1e100;
		for(int i = 0; i < n; ++i) {
			double x = (double)d[i] / c[i];
			res = Math.min(res, sum(x));
		}
		return res;
	}
}
