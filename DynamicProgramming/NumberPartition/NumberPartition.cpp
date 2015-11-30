#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>

/*
m/n partition: n�� m ������ �ڿ����θ� ��Ÿ���� ���.
* ���� ��ȭ�� �̿�.
1) p(0,m)=1
2) n<m�̸� p(n,m)=p(n,n)
3) n>=m, n>0�̸�, p(n,m)=p(n-1,1)+p(n-2,2)+...+p(n-m,m)
�Ǵ� n>=m�̸�, p(n,m)=p(n-m,m)+p(n,m-1) ������� �̿��� ���� �ִ�.
*/

#define MAXN 200

static int cache[MAXN][MAXN];

int partition(int n, int m)
{
	if (n < m) {
		m = n;
	}
	if (cache[n][m] > 0) {
		return cache[n][m];
	}
	if (n == 0) {
		return cache[n][m] = 1;
	}
	int count = 0;
	for (int i = 1; i <= m; ++i) {
		count += partition(n - i, i);
	}
	return cache[n][m] = count;
}

int main()
{
	memset(cache, 0, MAXN * MAXN * sizeof(int));
	printf("%d\n", partition(5, 3));
	return 0;
}
