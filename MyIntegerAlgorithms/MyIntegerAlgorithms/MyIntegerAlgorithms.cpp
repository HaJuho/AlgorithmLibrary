#include <cassert>

// O(1)
inline void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

// O(1)
inline int& min(int& a, int& b)
{
	return !(b < a) ? a : b;
}

// O(1)
inline const int& min(const int& a, const int& b)
{
	return !(b < a) ? a : b;
}

// O(1)
inline int& max(int& a, int& b)
{
	return a < b ? b : a;
}

// O(1)
inline const int& max(const int& a, const int& b)
{
	return a < b ? b : a;
}

// O(N)
int* min_element(int* begin, int* end)
{
	if (begin == end)
		return end;
#if 0
	int* smallest = begin;
	int m = *smallest;
	while (++begin != end) {
		int v = *begin;
		if (v < m) {
			smallest = begin;
			m = v;
		}
	}
	return smallest;
#else
	int* sentinal = end - 1;
	int sentval = *sentinal;
	int* smallest = begin;
	int m = 0x7fffffff;
	while (begin != sentinal) {
		int v = *begin;
		if (v < m) {
			smallest = begin;
			m = v;
			*sentinal = v;
		}
		++begin;
		while (*begin < m)
			++begin;
	}
	*sentinal = sentval;
	if (sentval < m)
		smallest = sentinal;
	return smallest;
#endif
}

// O(N)
const int* min_element(const int* begin, const int* end)
{
	if (begin == end)
		return end;
#if 0
	const int* smallest = begin;
	int m = *smallest;
	while (++begin != end) {
		int v = *begin;
		if (v < m) {
			smallest = begin;
			m = v;
		}
	}
	return smallest;
#else
	int* sentinal = const_cast<int*>(end - 1);
	int sentval = *sentinal;
	const int* smallest = begin;
	int m = 0x7fffffff;
	while (begin != sentinal) {
		int v = *begin;
		if (v < m) {
			smallest = begin;
			m = v;
			*sentinal = v;
		}
		++begin;
		while (*begin < m)
			++begin;
	}
	*sentinal = sentval;
	if (sentval < m)
		smallest = sentinal;
	return smallest;
#endif
}

// O(N)
int* max_element(int* begin, int* end)
{
	if (begin == end)
		return end;
#if 0
	int* largest = begin;
	int m = *largest;
	while (++begin != end) {
		int v = *begin;
		if (v > m) {
			largest = begin;
			m = v;
		}
	}
	return largest;
#else
	int* sentinal = end - 1;
	int sentval = *sentinal;
	int* largest = begin;
	int m = 0x80000000;
	while (begin != sentinal) {
		int v = *begin;
		if (v > m) {
			largest = begin;
			m = v;
			*sentinal = v;
		}
		++begin;
		while (*begin > m)
			++begin;
	}
	*sentinal = sentval;
	if (sentval < m)
		largest = sentinal;
	return largest;
#endif
}

// O(N)
const int* max_element(const int* begin, const int* end)
{
	if (begin == end)
		return end;
#if 0
	const int* largest = begin;
	int m = *largest;
	while (++begin != end) {
		int v = *begin;
		if (v > m) {
			largest = begin;
			m = v;
		}
	}
	return largest;
#else
	int* sentinal = const_cast<int*>(end - 1);
	int sentval = *sentinal;
	const int* largest = begin;
	int m = 0x80000000;
	while (begin != sentinal) {
		int v = *begin;
		if (v > m) {
			largest = begin;
			m = v;
			*sentinal = v;
		}
		++begin;
		while (*begin > m)
			++begin;
	}
	*sentinal = sentval;
	if (sentval < m)
		largest = sentinal;
	return largest;
#endif
}

// O(N)
int* copy(const int* begin, const int* end, int* res)
{
	while (begin != end) {
		*res++ = *begin++;
	}
	return res;
}

// O(N)
void reverse(int* begin, int* end)
{
	while (begin < --end) {
		swap(*begin, *end);
		++begin;
	}
}

// O(N)
void rotate(int* begin, int* mid, int* end)
{
	int* next = mid;
	while (begin != next) {
		swap(*begin++, *next++);
		if (next == end)
			next = mid;
		else if (begin == mid)
			mid = next;
	}
}

// O(N)
int* find(int* begin, int* end, int key)
{
	if (begin == end)
		return end;
	int* sentinal = end - 1;
	int sentval = *sentinal;
	*sentinal = key;
	while (*begin != key)
		++begin;
	*sentinal = sentval;
	//return *begin == key ? begin : end; // not sure it's optimized ?
	return (begin == sentinal && key != sentval) ? end : begin;
}

// O(N)
const int* find(const int* begin, const int* end, int key)
{
	if (begin == end)
		return end;
	int* sentinal = const_cast<int*>(end - 1);
	int sentval = *sentinal;
	*sentinal = key;
	while (*begin != key)
		++begin;
	*sentinal = sentval;
	//return *begin == key ? begin : end; // not sure it's optimized ?
	return (begin == sentinal && key != sentval) ? end : begin;
}

// O(log N)
int* lower_bound(int* begin, int* end, int key)
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

// O(log N)
const int* lower_bound(const int* begin, const int* end, int key)
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

// O(log N)
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

// O(log N)
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

// O(N)
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

// O(N)
bool prev_permutation(int* begin, int* end)
{
	if (begin == end)
		return false;
	// TODO : not implemented
	return false;
}

// O(N log N)
#define QUICK_SORT_NEAR_LEV 4
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

// O(N^2)
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

// O(N log N). worst O(N^2)
void sort(int* begin, int* end)
{
	quick_near_sort(begin, end);
#if QUICK_SORT_NEAR_LEV > 1
	insertion_sort(begin, end);
#endif
}

// O(N log N)
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

	copy(buf, bufw, begin);
}

// O(N log N)
void stable_sort(int* begin, int* end)
{
	int* buf = new int[end - begin];
	if (buf) {
		merge_sort(begin, end, buf);
		delete buf;
	}
}

// O(N)
// void make_heap(int* begin, int* end)

// O(log N)
// void pop_heap(int* begin, int* end)

// O(log N)
// void push_heap(int* begin, int* end)

// O(N log N)
// void sort_heap(int* begin, int* end)

// O(N)
// bool is_heap(const int* begin, const int* end)

// O(N log M)
// void partial_sort(int* begin, int* mid, int* end)

// O(N). worst O(N^2)
// void nth_element(int* begin, int* end, int n)

// O(N)
// int* partition(int* begin, int* end, int pivot)

// O(N + M)
// int* merge(const int* begin1, const int* end1, const int* begin2, const int* end2, int* res)

// O(N log N) without buffer ?? how ??
// int* inplace_merge(int* begin, int* mid, int* end)

// O(N + M)
// bool includes(const int* begin1, const int* end1, const int* begin2, const int* end2)

// O(N + M)
// bool set_intersection(const int* begin1, const int* end1, const int* begin2, const int* end2, int* res)

// O(N + M)
// bool set_union(const int* begin1, const int* end1, const int* begin2, const int* end2, int* res)

// O(N + M)
// bool set_difference(const int* begin1, const int* end1, const int* begin2, const int* end2, int* res)

// O(N + M)
// bool set_symmetric_difference(const int* begin1, const int* end1, const int* begin2, const int* end2, int* res)

// O(N)
// int* remove(int* begin, int* end, int key)

// O(N)
// int* unique(int* begin, int* end)


#include <cstdio>

int main(int argc, char* argv[])
{
	int a[] = { 1, 2, 3, 4 };
	stable_sort(a, a + 4);
	printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
	return 0;
}
