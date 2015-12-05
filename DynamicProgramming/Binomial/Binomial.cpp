#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 50;

// 1. memoization
static unsigned long long cache1[MAXN + 1][MAXN + 1];

void init_cache1()
{
	memset(cache1, 0, sizeof(cache1));
}

unsigned long long binomial1(int n, int r)
{
	if (cache1[n][r])
		return cache1[n][r];
	if (r == 0 || r == n)
		return cache1[n][r] = 1;
	return cache1[n][r] = binomial1(n - 1, r - 1) + binomial1(n - 1, r);
}

// 2. 반복적 DP - memoization의 초기화 생략 가능. 실제로 필요없는 case도 계산. 여러 번 호출한다면??
static unsigned long long cache2[MAXN + 1][MAXN + 1];
static int initialized = 0;

unsigned long long binomial2(int n, int r)
{
	if (n > initialized) {
		for (int i = initialized + 1; i <= n; ++i) {
			cache2[i][0] = 1;
			for (int j = 1; j < i; ++j) {
				cache2[i][j] = cache2[i - 1][j - 1] + cache2[i - 1][j];
			}
			cache2[i][i] = 1;
		}
		initialized = n;
	}
	return cache2[n][r];
}

int main(int argc, char* argv[])
{
	init_cache1();
	int testset[] = { 5, 3, 10, 7, 2, 2, 50, 25 };
	for (int i = 0; i < sizeof(testset) / sizeof(int); i += 2) {
		int n = testset[i];
		int r = testset[i + 1];
		printf("%d/%d: %llu %llu\n", n, r, binomial1(n, r), binomial2(n, r));
	}
	return 0;
}
