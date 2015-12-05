#include <cstdio>
#include <cstdlib>

#include <algorithm>

using namespace std;

int lowerbound(const int a[], int begin, int end, int key)
{
	// pre: begin <= end
	// pre: a[begin, end) is sorted in ascending order

	// virtual: a[begin-1] = -inf, a[end] = inf
	// assert: a[begin-1] = -inf < a[begin] <= a[begin+1] <= ... <= a[end-1] < a[end] = inf

	int first = begin - 1, last = end;
	// loop invariant: first < last
	// loop invariant: a[first] < key <= a[last]
	while (first + 1 < last) {
		int mid = first + ((last - first) >> 1);
		// assert: first < mid < last
		if (a[mid] < key)
			first = mid;
		else
			last = mid;
	}
	// assert: first+1 >= last && first < last... first+1 == last
	// assert: a[first] < key <= a[last]
	return last;
}

int upperbound(const int a[], int begin, int end, int key)
{
	// pre: begin <= end
	// pre: a[begin, end) is sorted in ascending order

	// virtual: a[begin-1] = -inf, a[end] = inf
	// assert: a[begin-1] = -inf < a[begin] <= a[begin+1] <= ... <= a[end-1] < a[end] = inf

	int first = begin - 1, last = end;
	// loop invariant: first < last
	// loop invariant: a[first] <= key < a[last]
	while (first + 1 < last) {
		int mid = first + ((last - first) >> 1);
		// assert: first < mid < last
		if (key < a[mid])
			last = mid;
		else
			first = mid;
	}
	// assert: first+1 >= last && first < last... first+1 == last
	// assert: a[first] <= key < a[last]
	return last;
}

int findtop(const int a[], int first, int last)
{
	// pre: first <= top <= last
	// pre: a[i] < a[i+1] for first <= i < top (sorted in ascending order)
	// pre: a[i-1] > a[i] for top < i <= last (sorted in descending order)

	// loop invariant: first <= top <= last
	while (first + 1 < last) {
		int mid = first + ((last - first) >> 1);
		// assert: first < mid < last
		if (a[mid] < a[mid + 1]) // mid < top
			first = mid + 1;
		else if (a[mid - 1] > a[mid]) // top < mid
			last = mid - 1;
		else // a[mid-1] < a[mid] > a[mid+1]
			return mid;
	}
	// assert: first <= top <= last && first+1 >= last... first == last || first+1 == last
	return a[first] > a[last] ? first : last;
}

int findrotationpivot(const int a[], int first, int last)
{
	// pre: first <= pivot <= last
	// pre: a[first, pivot) is sorted in ascending order
	// pre: a[pivot, last] is sorted in ascending order
	// pre: a[first] >= a[last] if first < pivot
	// pre: a[pivot-1] > a[pivot] if first < pivot
	if (first == last)
		return first;
	if (a[first] < a[last])
		return first;
	if (a[first] > a[last]) {
		// loop invariant: first < pivot <= last
		// loop invariant: a[first] > a[last] >= a[pivot]
		while (first + 1 < last) {
			int mid = first + ((last - first) >> 1);
			// assert: first < mid < last
			if (a[first] <= a[mid]) // a[mid] >= a[first] > a[last] >= a[pivot]
				first = mid;
			else // a[first] > a[mid] >= a[pivot]
				last = mid;
		}
		// assert: first+1 >= last && first < last... first+1 == last
		// assert: first < pivot <= last
		return last;
	}
	// case: a[first] == a[last]
	int mid = first + ((last - first) >> 1);
	// assert: first <= mid < last;
	if (a[first] < a[mid]) // case: a[first] < a[mid] > a[last]
		return findrotationpivot(a, mid + 1, last);
	if (a[mid] < a[last]) // case: a[first] > a[mid] < a[last]
		return findrotationpivot(a, first, mid);
	// case: a[first] == a[mid] == a[last]
	int right = findrotationpivot(a, mid + 1, last);
	if (right > mid + 1 || a[mid] > a[right])
		return right;
	return findrotationpivot(a, first, mid);
}

int searchinrotated(const int a[], int first, int last, int key)
{
	// pre: ...
	int pivot = findrotationpivot(a, first, last);
	int p = key < a[first] ? lowerbound(a, pivot, last + 1, key): lowerbound(a, first, pivot, key);
	return (p == last + 1 || a[p] != key) ? -1 : p;
}

int searchinrotated2(const int a[], int first, int last, int key)
{
	// pre: first > last OR all other pre conditions
	// pre: a[first, last] has no duplicate elements
	// pre: first <= pivot <= last
	// pre: a[first, pivot) is sorted in ascending order
	// pre: a[pivot, last] is sorted in ascending order
	// pre: a[first] > a[last] if first < pivot
	// pre: a[pivot-1] > a[pivot] if first < pivot
	if (first > last)
		return -1;
	int mid = first + ((last - first) >> 1);
	if (a[mid] == key)
		return mid;
	if (a[first] <= a[mid]) {
		if (a[first] <= key && key < a[mid])
			return searchinrotated2(a, first, mid - 1, key);
		else
			return searchinrotated2(a, mid + 1, last, key);
	}
	else { // a[mid] < a[first]
		if (a[mid] < key && key <= a[last])
			return searchinrotated2(a, mid + 1, last, key);
		else
			return searchinrotated2(a, first, mid - 1, key);
	}
}

int findkthvalfromtwo(const int a[], int lena, int b[], int lenb, int k)
{
	// pre: a[0, lena) is sorted in ascending order
	// pre: b[0, lenb) is sorted in ascending order
	if (k >= lena + lenb)
		return -987654321;
	// assert: k < lena + lenb
	if (k < lena && a[k] <= b[0])
		return a[k];
	if (k < lenb && b[k] <= a[0])
		return b[k];

	int first = max(0, k - lenb);
	int last = min(k, lena);
	// virtual: a[lena] = inf
	// virtual: b[lenb] = inf
	// loop invariant: first < last
	// loop invariant: a[first] < b[k-first]
	// loop invariant: b[k-last] <= a[last]
	while (first + 1 < last) {
		int mid = first + ((last - first) >> 1);
		// assert: first < mid < last
		if (a[mid] < b[k - mid])
			first = mid;
		else // b[k-mid] <= a[mid]
			last = mid;
	}
	// assert: first+1 >= last && first < last... first+1 == last
	// assert: a[first] < b[k-first]
	// assert: b[k-last] <= a[last]
	// assert: a[first] <= a[last]
	// assert: b[k-last] <= b[k-first]
	return max(a[first], b[k - last]);
}

int main(int argc, char* argv[])
{
	return 0;
}
