
struct Node {

};

struct SegmentTree {
	int len;
	vector<Node> values;

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Node single(int val) {
		// value at the base level while updating
		return {};
	}

	Node neutral = {}; // the value which will not affect our answer

	Node merge(Node a, Node b) {
		// the associative operation we are doing
		// a is left subsegment, b is right subsegment
		return {};
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	SegmentTree(int n) {
		len = 1;
		while (len < n) len *= 2;
		values = vector<Node> (2 * len);
	}

	void build(vector<int> &a, int x, int lx, int rx) {
		// leaf node
		if (rx - lx == 1) {
			// if lx is within the original array
			if (lx < (int)a.size())
				values[x] = single(a[lx]);
			return;
		}

		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);

		values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
	}

	void build(vector<int> &a) {
		build(a, 0, 0, len);
	}

	void update(int ind, int val, int x, int lx, int rx) {
		// x is current node, lx and rx are borders of curr node
		if (rx - lx == 1) { // leaf node
			// bottom level of the segtree
			values[x] = single(val);
			return;
		}

		int mid = (lx + rx) / 2;

		if (ind < mid) {
			// go to left subtree
			update(ind, val, 2 * x + 1, lx, mid);
		} else {
			// go to right subtree
			update(ind, val, 2 * x + 2, mid, rx);
		}
		values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
	}

	void update(int ind, int val) {
		update(ind, val, 0, 0, len);
	}

	Node calc(int l, int r, int x, int lx, int rx) {
		// current range do not intersect with required range
		if (r <= lx or l >= rx)
			return neutral;
		// whole segment lie in this range
		if (l <= lx and r >= rx)
			return values[x];

		int mid = (lx + rx) / 2;

		Node leftVal = calc(l, r, 2 * x + 1, lx, mid);
		Node rightVal = calc(l, r, 2 * x + 2, mid, rx);

		return merge(leftVal, rightVal);
	}

	Node calc(int l, int r) {
		return calc(l, r, 0, 0, len);
	}
};