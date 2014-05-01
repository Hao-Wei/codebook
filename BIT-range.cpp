// Note: The array is 0-based.
struct BIT_range {
    int len;
    vector<int> dataAdd;
    vector<int> dataMul;
    // Initializes array to all zeroes
    BIT_range(int len): len(len), dataAdd(len, 0), dataMul(len, 0) {}
    void internalUpdate(int at, int mul, int add) {
        while (at < len) {
            dataMul[at] += mul;
            dataAdd[at] += add;
            at |= (at + 1);
        }
    }
    // Adds x to all elements in range [left, right]
    void update(int left, int right, int x) {
        internalUpdate(left, x, -x * (left - 1));
        internalUpdate(right, -x, x * right);
    }
    // Returns sum of elements in range [0, at]
    int query(int at) {
        int mul = 0;
        int add = 0;
        int start = at;
        while (at >= 0) {
            mul += dataMul[at];
            add += dataAdd[at];
            at = (at & (at + 1)) - 1;
        }
        return mul * start + add;
    }
};
