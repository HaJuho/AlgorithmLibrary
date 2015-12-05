/*****************************************************************************
*****************************************************************************/
#include <cassert>

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int& min(int& a, int& b)
{
	return !(b < a) ? a : b;
}

const int& min(const int& a, const int& b)
{
	return !(b < a) ? a : b;
}

int& max(int& a, int& b)
{
	return a < b ? b : a;
}

const int& max(const int& a, const int& b)
{
	return a < b ? b : a;
}

int* min_element(int* begin, int* end)
{
	if (begin == end)
		return end;
	int* smallest = begin;
	while (++begin != end) {
		if (*begin < *smallest)
			smallest = begin;
	}
	return smallest;
}

const int* min_element(const int* begin, const int* end)
{
	if (begin == end)
		return end;
	const int* smallest = begin;
	while (++begin != end) {
		if (*begin < *smallest)
			smallest = begin;
	}
	return smallest;
}

int* max_element(int* begin, int* end)
{
	if (begin == end)
		return end;
	int* largest = begin;
	while (++begin != end) {
		if (*largest < *begin)
			largest = begin;
	}
	return largest;
}

const int* max_element(const int* begin, const int* end)
{
	if (begin == end)
		return end;
	const int* largest = begin;
	while (++begin != end) {
		if (*largest < *begin)
			largest = begin;
	}
	return largest;
}

int* copy(const int* begin, const int* end, int* res)
{
	while (begin != end) {
		*res++ = *begin++;
	}
	return res;
}

void reverse(int* begin, int* end)
{
	while (begin < --end) {
		swap(*begin, *end);
		++begin;
	}
}

int* lower_bound(int* begin, int* end, const int key)
{
	int* first = begin - 1;
	int* last = end;
	while (first + 1 < last) {
		int* mid = first + ((last - first) >> 1);
		if (*mid < key)
			first = mid;
		else
			last = mid;
	}
	return last;
}

const int* lower_bound(const int* begin, const int* end, const int key)
{
	const int* first = begin - 1;
	const int* last = end;
	while (first + 1 < last) {
		const int* mid = first + ((last - first) >> 1);
		if (*mid < key)
			first = mid;
		else
			last = mid;
	}
	return last;
}

int* upper_bound(int* begin, int* end, int key)
{
	int* first = begin - 1;
	int* last = end;
	while (first + 1 < last) {
		int* mid = first + ((last - first) >> 1);
		if (key < *mid)
			last = mid;
		else
			first = mid;
	}
	return last;
}

const int* upper_bound(const int* begin, const int* end, int key)
{
	const int* first = begin - 1;
	const int* last = end;
	while (first + 1 < last) {
		const int* mid = first + ((last - first) >> 1);
		if (key < *mid)
			last = mid;
		else
			first = mid;
	}
	return last;
}

bool next_permutation(int* begin, int* end)
{
	if (begin == end)
		return false;

	int* it = end - 1;
	while (it != begin && *(it - 1) >= *it)
		--it;
	reverse(it, end);

	if (it == begin)
		return false;
	else {
		int* it1 = it - 1;
		int* it2 = upper_bound(it, end, *it1);
		swap(*it1, *it2);
		return true;
	}
}

bool prev_permutation(int* begin, int* end)
{
	if (begin == end)
		return false;
	// TODO : not implemented
	return false;
}

#define QUICK_SORT_NEAR_LEV 10

void quick_near_sort(int* begin, int* end)
{
	if (begin + QUICK_SORT_NEAR_LEV >= end)
		return;

	int pivot = *(begin + ((end - begin) >> 1));
	int* first = begin;
	int* last = end - 1;
	while (first <= last) {
		while (*first < pivot)
			++first;
		while (pivot < *last)
			--last;
		if (first <= last)
			swap(*first++, *last--);
	}

	quick_near_sort(begin, last + 1);
	quick_near_sort(first, end);
}

void insertion_sort(int* begin, int* end)
{
	for (int* pos = begin + 1; pos != end; ++pos) {
		int* tmp = pos;
		while (tmp != begin && *(tmp - 1) > *tmp) {
			swap(*(tmp - 1), *tmp);
			--tmp;
		}
	}
}

void sort(int* begin, int* end)
{
	quick_near_sort(begin, end);
#if QUICK_SORT_NEAR_LEV > 1
	insertion_sort(begin, end);
#endif
}

void merge_sort(int* begin, int* end, int* buf)
{
	if (begin + 1 >= end)
		return;

	int* mid = begin + ((end - begin) >> 1);
	merge_sort(begin, mid, buf);
	merge_sort(mid, end, buf);

	int* f = begin;
	int* s = mid;
	int* bufw = buf;
	while (f != mid && s != end) {
		if (*f > *s)
			*bufw++ = *s++;
		else
			*bufw++ = *f++;
	}
	while (f != mid)
		*bufw++ = *f++;
	while (s != end)
		*bufw++ = *s++;

	copy(buf, bufw, begin);
}

void stable_sort(int* begin, int* end)
{
	int* buf = new int[end - begin];
	if (buf) {
		merge_sort(begin, end, buf);
		delete buf;
	}
}

#include <cstdio>

int main(int argc, char* argv[])
{
	int a[] = { 4, 1, 3, 2 };
	stable_sort(a, a + 4);
	printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
	return 0;
}
