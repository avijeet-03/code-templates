class SlidingMedian {
	multiset<int> low, high;
	int firstHalfSum, secondHalfSum;

	void balance() {
		// adjust the sizes
		// while left half is greater than right half
		while (low.size() > high.size() + 1) {
			// take max of left and insert it in right half
			int leftMax = *low.rbegin();
			low.erase(low.find(leftMax));
			firstHalfSum -= leftMax;

			high.insert(leftMax);
			secondHalfSum += leftMax;
		}
		// while right half is greater than left half
		while (low.size() < high.size()) {
			// take right min and insert it in left half
			int rightMin = *high.begin();
			high.erase(high.begin());
			secondHalfSum -= rightMin;

			low.insert(rightMin);
			firstHalfSum += rightMin;
		}
	}

public:
	SlidingMedian() {
		low.clear();
		high.clear();
		firstHalfSum = secondHalfSum = 0;
	}

	void insert(int x) {
		if (low.empty() || x <= *low.rbegin()) {
			low.insert(x);
			firstHalfSum += x;
		}
		else {
			high.insert(x);
			secondHalfSum += x;
		}
		balance();
	}

	void remove(int x) {
		if (low.find(x) != low.end()) {
			low.erase(low.find(x));
			firstHalfSum -= x;
		}
		else if (high.find(x) != high.end()) {
			high.erase(high.find(x));
			secondHalfSum -= x;
		}
		balance();
	}

	int getMedian() {
		if (low.empty())
			return -1;
		return *low.rbegin();
	}

	int getCost() {
		int mid = getMedian();
		int l = low.size();
		int r = high.size();

		return (l * mid - firstHalfSum) + (secondHalfSum - r * mid);
	}
};

// Task: https://cses.fi/problemset/task/1077