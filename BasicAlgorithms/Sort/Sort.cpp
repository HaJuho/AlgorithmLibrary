#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define QUICK_SORT_NEAR_LEV 10

void quick_near_sort(int a[], int begin, int end)
{
	if (begin + QUICK_SORT_NEAR_LEV >= end)
		return;

	int pivot = a[begin + ((end - begin) >> 1)];
	int first = begin;
	int last = end - 1;
	while (first <= last) {
		while (a[first] < pivot)
			++first;
		while (pivot < a[last])
			--last;
		if (first <= last)
			swap(a[first++], a[last--]);
	}

	quick_near_sort(a, begin, last + 1);
	quick_near_sort(a, first, end);
}

void insertion_sort(int a[], int len)
{
	for (int i = 1; i < len; ++i) {
		int j = i;
		while (j > 0 && a[j - 1] > a[j]) {
			swap(a[j - 1], a[j]);
			--j;
		}
	}
}

void quick_sort(int a[], int len)
{
	quick_near_sort(a, 0, len);
#if QUICK_SORT_NEAR_LEV > 1
	insertion_sort(a, len);
#endif
}

void merge_sort(int a[], int begin, int end, int buf[])
{
	if (begin + 1 >= end)
		return;

	int mid = begin + ((end - begin) >> 1);
	merge_sort(a, begin, mid, buf);
	merge_sort(a, mid, end, buf);

#if 0
	for (int i = 0, f = begin, s = mid, l = begin - end; i < l; ++i) {
		if (f == mid || (s < end && a[f] > a[s]))
			buf[i] = a[s++];
		else
			buf[i] = a[f++];
	}
#else
	int f = begin, s = mid;
	int i = 0;
	while (f != mid && s != end) {
		if (a[f] > a[s])
			buf[i++] = a[s++];
		else
			buf[i++] = a[f++];
	}
	while (f != mid)
		buf[i++] = a[f++];
	while (s != end)
		buf[i++] = a[s++];
#endif

	memcpy(&a[begin], buf, sizeof(int) * (end - begin));
}

void merge_sort(int a[], int len)
{
	int* buf = new int[len];
	if (buf) {
		merge_sort(a, 0, len, buf);
		delete buf;
	}
}

int main(int argc, char* argv[])
{
	return 0;
}
