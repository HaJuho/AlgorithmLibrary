#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 100;

// 1. memoization
static long long cache1[MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		cache1[i] = -1;
}

long long fibonacci1(int n)
{
	if (cache1[n] >= 0)
		return cache1[n];
	if (n == 0)
		return cache1[0] = 0;
	if (n == 1)
		return cache1[1] = 1;
	return cache1[n] = fibonacci1(n - 1) + fibonacci1(n - 2);
}

// 2. 반복적 DP -> 공간 절약. 또는 직접 계산??.
long long fibonacci2(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	long long fn1 = 1;
	long long fn2 = 0;
	for (int i = 2; i < n; ++i) {
		long long fn = fn1 + fn2;
		fn2 = fn1;
		fn1 = fn;
	}
	return fn1 + fn2;
}

int main(int argc, char* argv[])
{
	init_cache1();

	int ns[] = { 4, 0, 10, 1, 2, 20, 40, 60, 80, 100 };
	for (int n : ns) {
		printf("%d : %lld %lld\n", n, fibonacci1(n), fibonacci2(n));
	}
	return 0;
}
