
struct runningMedian {

	priority_queue<int> a;
	priority_queue<int, vector<int>, greater<int>> b;

	runningMedian() {
		while (!a.empty())
			a.pop();
		while (!b.empty())
			b.pop();
	}

	void insert(int x) {
		if ((int)a.size() == (int)b.size()) {
			// add to the first heap
			if (b.empty() or b.top() >= x)
				a.push(x);
			else {
				a.push(b.top());
				b.pop();
				b.push(x);
			}
		} else {
			// add into the second heap
			if (x < a.top()) {
				b.push(a.top());
				a.pop();
				a.push(x);
			} else {
				b.push(x);
			}
		}
	}

	double median() {
		if (a.empty()) return 0.0;
		if ((int)a.size() == (int)b.size())
			return (a.top() + b.top()) / 2.0;
		return a.top() / 1.0;
	}

};