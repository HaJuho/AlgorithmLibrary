#include <cstdio>
#include <cstdlib>

using namespace std;

int lowerbound(int a[], int begin, int end, int key)
{
	// pre: begin <= end
	// pre: a is valid in [begin, end)
	// pre: a is sorted in ascending order
	if (begin == end)
		return begin;
	// assert: begin < end
	// imagine: a[begin-1] = -inf, a[end] = inf
	// assert: a[begin-1] = -inf < a[begin] <= a[begin+1] <= ... <= a[end-1] < a[end] = inf

	int first = begin - 1, last = end;
	// loop invariant: first < last
	// loop invariant: a[first] < key <= a[last]
	while (first + 1 < last) {
		int mid = first + (last - first) / 2;
		// assert: first < mid < last
		if (a[mid] < key)
			first = mid;
		else
			last = mid;
	}
	// assert: first + 1 >= last && first < last && first + 1 == last
	// assert: a[first] < key <= a[last]
	return last;
}

int upperbound(int a[], int begin, int end, int key)
{
	// pre: begin <= end
	// pre: a is valid in [begin, end)
	// pre: a is sorted in ascending order
	if (begin == end)
		return begin;
	// assert: begin < end
	// imagine: a[begin-1] = -inf, a[end] = inf
	// assert: a[begin-1] = -inf < a[begin] <= a[begin+1] <= ... <= a[end-1] < a[end] = inf

	int first = begin - 1, last = end;
	// loop invariant: first < last
	// loop invariant: a[first] <= key < a[last]
	while (first + 1 < last) {
		int mid = first + (last - first) / 2;
		// assert: first < mid < last
		if (key < a[mid])
			last = mid;
		else
			first = mid;
	}
	// assert: first + 1 >= last && first < last && first + 1 == last
	// assert: a[first] <= key < a[last]
	return last;
}

int findtop(int a[], int begin, int end)
{
	return 0;
}

int findrotationpivot(int a[], int begin, int end)
{
	return 0;
}

int searchinrotated(int a[], int begin, int end, int key)
{
	return 0;
}

int findkthvalfromtwo(int a[], int lena, int b[], int lenb, int k)
{
	return 0;
}

int main(int argc, char* argv[])
{
	return 0;
}
