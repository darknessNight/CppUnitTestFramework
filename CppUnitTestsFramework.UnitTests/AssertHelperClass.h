#pragma once

class AssertHelperClass {
private:
	int val;
public:
	AssertHelperClass(int v) {
		val = v;
	}
	bool operator==(const AssertHelperClass& rhs) const {
		return val == rhs.val;
	}
	bool operator<(const AssertHelperClass& rhs) const {
		return val < rhs.val;
	}
	bool operator>(const AssertHelperClass& rhs) const {
		return val > rhs.val;
	}
};