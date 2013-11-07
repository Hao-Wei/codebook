// Binary indexed tree supporting binary search. Brian Bi
struct BIT {
	int n;
	vector<int> bit;
	// n is the size of the BIT.
	BIT(int n):n(n), bit(n+1) {}
	// returns f[1] + ... + f[idx-1]
	int read(int idx) {
		idx--;
		int res = 0;
		while (idx > 0) {
			res += bit[idx];
			idx -= idx & -idx;
		}
		return res;
	}
	// returns f[idx1] + ... + f[idx2-1]
	int read2(int idx1, int idx2) {
		return read(idx2) - read(idx1);
	}
	// indices are 1-based. adds val to f[idx]
	int update(int idx, int val) {
		while (idx <= n) {
			bit[idx] += val;
			idx += idx & -idx;
		}
	}
	// returns smallest positive idx such that read(idx) >= target
	int lower_bound(int target) {
		if (target <= 0) return 1;
		int pwr = 1; while (2*pwr <= n) pwr*=2;
		int idx = 0; int tot = 0;
		for (; pwr; pwr >>= 1) {
			if (idx+pwr > n) continue;
			if (tot + bit[idx+pwr] < target) {
				tot += bit[idx+=pwr];
			}
		}
		return idx+2;
	}
	// returns smallest positive idx such that read(idx) > target
	int upper_bound(int target) {
		if (target < 0) return 1;
		int pwr = 1; while (2*pwr <= n) pwr*=2;
		int idx = 0; int tot = 0;
		for (; pwr; pwr >>= 1) {
			if (idx+pwr > n) continue;
			if (tot + bit[idx+pwr] <= target) {
				tot += bit[idx+=pwr];
			}
		}
		return idx+2;
	}
};
