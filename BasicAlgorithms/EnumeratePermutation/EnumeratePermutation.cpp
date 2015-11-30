/*****************************************************************************
*****************************************************************************/
//#include <cstdio>
//#include <cstdlib>
//#include <cstdint>
//#include <cstring>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "EnumeratePermutation.hpp"

using namespace std;

/*****************************************************************************
*****************************************************************************/
template<typename RandomIterator>
struct JustPrint {
	int count;
	JustPrint() : count(0) {}
	bool operator()(RandomIterator& begin, const int* index_begin, const int* index_end) {
		for_each(index_begin, index_end, [begin](int idx) { cout << begin[idx] << " "; });
		cout << endl;
		count++;
		return false;
	}
};

struct JustPrint1 {
	int count;
	JustPrint1() : count(0) {}
	bool operator()(vector<string>::iterator& begin, const int* index_begin, const int* index_end) {
		for_each(index_begin, index_end, [begin](int idx) { cout << begin[idx] << " "; });
		cout << endl;
		count++;
		return false;
	}
};

/*****************************************************************************
*****************************************************************************/
void test_next_perm(vector<string> arr1) // copy
{
	vector<string> arr2(arr1);

	for_each(arr1.begin(), arr1.end(), [](string& s) { cout << s << " "; });
	cout << ": ";
	for_each(arr2.begin(), arr2.end(), [](string& s) { cout << s << " "; });
	cout << endl;

	while (next_perm(arr1.begin(), arr1.end())) {
		next_permutation(arr2.begin(), arr2.end());
		for_each(arr1.begin(), arr1.end(), [](string& s) { cout << s << " "; });
		cout << ": ";
		for_each(arr2.begin(), arr2.end(), [](string& s) { cout << s << " "; });
		cout << endl;
	}

	next_permutation(arr2.begin(), arr2.end());
	for_each(arr1.begin(), arr1.end(), [](string& s) { cout << s << " "; });
	cout << ": ";
	for_each(arr2.begin(), arr2.end(), [](string& s) { cout << s << " "; });
	cout << endl;
}

int main(int argc, char* argv[])
{
	vector<string> arr1 = { "1", "2", "3", "4", "5" };
	JustPrint1 just_print1;
	enumerate_perm(arr1.begin(), arr1.end(), 3, just_print1);
	cout << just_print1.count << endl;

	string arr2[] = { "10", "9", "8", "7", "6" };
	JustPrint<string*> just_print2;
	enumerate_perm(arr2, arr2 + 5, 7, just_print2);
	cout << just_print2.count << endl;

	test_next_perm(arr1);

	return 0;
}
