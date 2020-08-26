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

#include "enumerate_combination_repetition.h"

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
int main(int argc, char* argv[])
{
	vector<string> arr1 = { "1", "2", "3", "4", "5" };
	JustPrint1 just_print1;
	enumerate_rep_comb(arr1.begin(), arr1.end(), 3, just_print1);
	cout << just_print1.count << endl;

	string arr2[] = { "10", "9", "8", "7", "6" };
	JustPrint<string*> just_print2;
	enumerate_rep_comb(arr2, arr2 + 5, 2, just_print2);
	cout << just_print2.count << endl;

	return 0;
}
