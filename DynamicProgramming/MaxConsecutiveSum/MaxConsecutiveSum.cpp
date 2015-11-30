#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>

/*
M(n) : 수열 s[0], s[1], ... s[n-1]의 연속부분수열의 합 중 최대
c(n) : s[n-1]을 포함하는 연속부분수열의 합 중 최대
c(1)=s[0]
n>1이면, c(n)=max(c(n-1)+s[n-1],s[n-1])
M(1)=s[0]
n>1이면, M(n)=max(c(n),M(n-1))=max(c(n),c(n-1),M(n-2))=..=max(c(n),c(n-1),..,c(1))
*/

#define MAXN 10000

int find_max_consecutive_sum(int s[], int n)
{
	int c[MAXN];
	c[0] = s[0];
	for (int i = 1; i < n; ++i) {
		if (c[i - 1] > 0) {
			c[i] = s[i] + c [i - 1];
		}
		else {
			c[i] = s[i];
		}
	}

	int max_sum = 0;
	for (int i = 0; i < n; ++i) {
		if (c[i] > max_sum) {
			max_sum = c[i];
		}
	}
	return max_sum;
}

// TODO - verify this algorithm
int find_max_consecutive_sum2(int s[], int n)
{
	int acc = s[0];
	int cur_min = s[0];
	int max_sum = 0;
	for (int i = 1; i < n; ++i) {
		acc += s[i];
		if (acc < cur_min) {
			cur_min = acc;
		}
		int cur_sum = acc - cur_min;
		if (cur_sum > max_sum) {
			max_sum = cur_sum;
		}
	}
	return max_sum;
}

int main()
{
	int testset[] = {33, 36, -73, 15, 43, -17, 36, -28, -1, 21};
	//int testset[] = {20, 30, -70, 15, 40};
	//int testset[] = {-5, -4, -3, -2, -1, -2, -3, -4, -5};

	int mval = find_max_consecutive_sum2(testset, sizeof(testset)/sizeof(int));
	printf("%d\n", mval);

	return 0;
}
