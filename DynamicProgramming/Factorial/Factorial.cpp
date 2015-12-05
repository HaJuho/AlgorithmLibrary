#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static const int MAXN = 20;

// 1. memoization
static long long cache1[MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		cache1[i] = 0;
}

long long factorial1(int n)
{
	if (cache1[n] > 0)
		return cache1[n];
	if (n == 0 || n == 1)
		return cache1[n] = 1;
	return cache1[n] = n * factorial1(n - 1);
}

// 2. 반복적 DP -> 공간 절약. 또는 직접 계산??.
long long factorial2(int n)
{
	long long f = 1;
	for (int i = 1; i <= n; ++i)
		f *= i;
	return f;
}

int main(int argc, char* argv[])
{
	init_cache1();
	int ns[] = { 4, 0, 10, 1, 2, 12, 14, 16, 18, 20 };
	for (int n : ns) {
		printf("%d : %lld %lld\n", n, factorial1(n), factorial2(n));
	}
	return 0;
}
