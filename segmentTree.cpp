class Node {
public:

	Node() {

	}
};

class SegmentTree {
	vector<int> a;
	vector<Node> tree;
	int n;

	// tree nodes are 1 based indexing
	// array nodes are 0 based indexing
	// l and r are both inclusive and 0 indexed

	// +++++++++++++++ Change here +++++++++++++++++
	Node neutral() {
		return Node();
	}

	Node leafNode(int val) {
		return Node();
	}

	Node merge(Node &x, Node &y) {

	}
	// +++++++++++++++ Change here +++++++++++++++++

	void build(int node, int start, int end) {
		if (start == end) {
			tree[node] = leafNode(a[start]);
			return;
		}

		int mid = (start + end) / 2;
		// build the left subtree [start..mid]
		build(2 * node, start, mid);
		// build the right subtree [mid + 1.....end]
		build(2 * node + 1, mid + 1, end);

		tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
	}

	void update(int node, int start, int end, int ind, int val) {
		// if leaf node update the tree node
		if (start == end) {
			tree[node] = leafNode(val);
			return;
		}

		int mid = (start + end) / 2;
		if (ind <= mid)
			update(2 * node, start, mid, ind, val);
		else
			update(2 * node + 1, mid + 1, end, ind, val);

		tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
	}

	Node query(int node, int start, int end, int lq, int rq) {
		// if the nodes contains all the info
		if (start >= lq && end <= rq)
			return tree[node];
		// if node completely lie out of the range
		if (end < lq || start > rq)
			return neutral();

		int mid = (start + end) / 2;
		Node left_tree = query(2 * node, start, mid, lq, rq);
		Node right_tree = query(2 * node + 1, mid + 1, end, lq, rq);

		return merge(left_tree, right_tree);
	}

public:
	void build(vector<int> &a) {
		this->n = a.size();
		this->a = a;
		tree = vector<Node> (4 * n);
		build(1, 0, n - 1);
	}

	void update(int ind, int val) {
		update(1, 0, n - 1, ind, val);
	}

	int query(int l, int r) {
		// return the exact ans that is needed
	}
};