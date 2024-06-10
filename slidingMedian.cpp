
struct slidingMedian {
	multiset<int> a, b;

	slidingMedian() {
		a.clear();
		b.clear();
	}

	void relax() {
		if (b.size() > a.size()) {
			a.insert(*b.begin());
			b.erase(b.begin());
		}
		if ((int)b.size() + 2 == (int)a.size()) {
			int x = *a.rbegin();
			b.insert(x);
			a.erase(a.find(x));
		}
		if (a.empty() or b.empty())
			return;
		if (*b.begin() >= *a.rbegin())
			return;


		int x = *a.rbegin();
		a.erase(a.find(x));
		int y = *b.begin();
		b.erase(b.find(y));

		a.insert(y);
		b.insert(x);
	}

	void insert(int x) {
		if (a.size() == b.size())
			a.insert(x);
		else
			b.insert(x);

		relax();
	}

	void remove(int x) {
		auto it = a.find(x);
		if (it != a.end())
			a.erase(it);
		else {
			it = b.find(x);
			if (it != b.end())
				b.erase(it);
		}
		relax();
	}

	int median() {
		if (a.empty())
			return -1;
		return *a.rbegin();
	}
};