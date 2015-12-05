#include <cstdio>
#include <cstdlib>

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
	// pre: first <= pivot <= last
	// pre: a[first, last] has no equal element
	// pre: a[first, pivot) is sorted in ascending order
	// pre: a[pivot, last] is sorted in ascending order
	// pre: a[first] > a[last] if first < pivot
	// pre: a[pivot-1] > a[pivot] if first < pivot
	int pivot = findrotationpivot(a, first, last);
	int p = key < a[first] ? lowerbound(a, pivot, last + 1, key) : lowerbound(a, first, pivot, key);
	return (p == last + 1 || a[p] != key) ? -1 : p;
}

int findkthvalfromtwo(const int a[], int lena, int b[], int lenb, int k)
{
	return 0;
}

int main(int argc, char* argv[])
{
	return 0;
}
