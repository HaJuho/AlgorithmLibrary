#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define NEARQUICKSORT 10

void quicksort(int a[], int begin, int end)
{
	if (begin + NEARQUICKSORT >= end)
		return;

	int pivot = a[begin + (end - begin) / 2];
	int first = begin;
	int last = end - 1;
	while (first <= last) {
		while (a[first] < pivot)
			++first;
		while (pivot < a[last])
			--last;
		if (first <= last) {
			swap(a[first++], a[last--]);
		}
	}
	quicksort(a, begin, last + 1);
	quicksort(a, first, end);
}

void insertionsort(int a[], int len)
{
	for (int i = 1; i < len; ++i) {
		int j = i;
		while (j > 0 && a[j - 1] > a[j]) {
			swap(a[j - 1], a[j]);
			--j;
		}
	}
}

void quicksort(int a[], int len)
{
	quicksort(a, 0, len);
#if NEARQUICKSORT > 1
	insertionsort(a, len);
#endif
}

void mergesort(int a[], int begin, int end, int buf[])
{
	if (begin + 1 >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergesort(a, begin, mid, buf);
	mergesort(a, mid, end, buf);

	for (int i = 0, f = begin, s = mid, l = begin - end; i < l; ++i) {
		if (f == mid || (s < end && a[f] > a[s]))
			buf[i] = a[s++];
		else
			buf[i] = a[f++];
	}
	memcpy(&a[begin], buf, sizeof(int) * (end - begin));
}

void mergesort(int a[], int begin, int end)
{
	int* buf = (int*)malloc(sizeof(int) * (end - begin));
	if (buf) {
		mergesort(a, begin, end, buf);
		free(buf);
	}
}

int main(int argc, char* argv[])
{
	return 0;
}
