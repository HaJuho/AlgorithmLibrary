#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <string>

using namespace std;

#define SELECT_AT_LEAST_ONE

static const int MAXN = 10000;

/*
방법1. O(N) 시간. O(N) 공간.
M(k) : 수열 s[0], s[1], ... s[k]의 연속부분수열의 합 중 최대
c(k) : s[0], ... s[k]만 포함하고 s[k]는 꼭 포함하는 연속부분수열의 합 중 최대
c(0)=s[0]
k>1이면, c(k)=max(c(k-1)+s[k],s[k])
M(0)=s[0]
k>1이면, M(k)=max(c(k),M(k-1))=max(c(k),c(k-1),M(k-2))=..=max(c(k),c(k-1),..,c(0))
*/
static int cache[MAXN];

int find_max_consecutive_sum1(int s[], int n)
{
	// caching
#ifdef SELECT_AT_LEAST_ONE
	cache[0] = s[0];
#else
	cache[0] = max(s[0], 0);
#endif
	for (int i = 1; i < n; ++i)
#ifdef SELECT_AT_LEAST_ONE
		cache[i] = max(s[i] + cache[i - 1], s[i]);
#else
		cache[i] = max(s[i] + cache[i - 1], 0);
#endif

	return *max_element(cache, cache + n);
}

/*
방법2. O(N) 시간. O(1) 공간.
방법1과 다르지 않음. cache에 저장하지 않고 바로 M(k)를 계산하는 방식임.
최소 하나의 원소를 고르는 방식일 때 조금 개념이 헷갈림.
*/
int find_max_consecutive_sum2(int s[], int n)
{
#ifdef SELECT_AT_LEAST_ONE
	int max_so_far = 0x80000000;
#else
	int max_so_far = 0;
#endif
	int sum_ending_here = 0;
	for (int i = 0; i < n; ++i) {
		sum_ending_here += s[i];
#ifdef SELECT_AT_LEAST_ONE
		sum_ending_here = max(sum_ending_here, s[i]);
#else
		sum_ending_here = max(sum_ending_here, 0);
#endif
		max_so_far = max(max_so_far, sum_ending_here);
	}
	return max_so_far;
}

int main()
{
	//int testset[] = {33, 36, -73, 15, 43, -17, 36, -28, -1, 21};
	//int testset[] = {20, 30, -70, 15, 40};
	//int testset[] = {-5, -4, -3, -2, -1, -2, -3, -4, -5};
	//int testset[] = {-1, -4, -3, -2, -1, -2, -3, -4, -5};
	//int testset[] = { -1 };
	int testset[] = { -1, 2 };

	int mval1 = find_max_consecutive_sum1(testset, sizeof(testset) / sizeof(int));
	int mval2 = find_max_consecutive_sum2(testset, sizeof(testset)/sizeof(int));
	printf("%d %d\n", mval1, mval2);

	return 0;
}
