#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>

static const int DEN = 1000000007;

static const int MAXN = 10000;

/*
n/m partition: n을 m 이하의 자연수의 합으로 나타내는 방법.
방법 1
1) n<m이면 p(n,m)=p(n,n)
2) p(0,m)=1
3) n>=m, n>0이면, p(n,m)=p(n-1,1)+p(n-2,2)+...+p(n-m,m)
*/
static int cache1[MAXN + 1][MAXN + 1];

void init_cache1()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXN; ++j)
			cache1[i][j] = -1;
}

int number_partition1(int n, int m)
{
	if (n < m)
		m = n;
	if (cache1[n][m] >= 0)
		return cache1[n][m];
	if (n == 0)
		return cache1[n][m] = 1;

	unsigned long long count = 0;
	for (int i = 1; i <= m; ++i)
		count += number_partition1(n - i, i);
	return cache1[n][m] = static_cast<int>(count % DEN);
}

/*
n/m partition: n을 m 이하의 자연수의 합으로 나타내는 방법.
방법 2
1) n<m이면 p(n,m)=p(n,n)
2) p(0,m)=1
3) p(n,0)=0
4) n>=m이면, p(n,m)=p(n-m,m)+p(n,m-1)
*/
static int cache2[MAXN + 1][MAXN + 1];

void init_cache2()
{
	for (int i = 0; i <= MAXN; ++i)
		for (int j = 0; j <= MAXN; ++j)
			cache2[i][j] = -1;
}

int number_partition2(int n, int m)
{
	if (n < m)
		m = n;
	if (cache2[n][m] >= 0)
		return cache2[n][m];
	if (n == 0)
		return cache2[n][m] = 1;
	if (m == 0)
		return cache2[n][m] = 0;
	int v = number_partition2(n - m, m) + number_partition2(n, m - 1);
	return cache2[n][m] = v > DEN ? v - DEN : v;
}

int main()
{
	init_cache1();
	init_cache2();
	int testset[] = { 5, 3, 10, 7, 2, 5, 50, 30, 1000, 1000 };
	for (int i = 0; i < sizeof(testset) / sizeof(int); i += 2) {
		int n = testset[i];
		int m = testset[i + 1];
		printf("%d/%d: %d %d\n", n, m, number_partition1(n, m), number_partition2(n, m));
	}
	return 0;
}
