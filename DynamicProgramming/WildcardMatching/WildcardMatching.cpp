/*****************************************************************************
*****************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <iostream>
#include <string>
#include <algorithm>

#include "buffalgo.hpp"

using namespace std;
using namespace juho;

bool wildcard_matching(char* A, char* P)
{
	int n = strlen(A);
	int m = strlen(P);
	buffalgo2<bool> b = buffalgo2<bool>::rectangle(n + 1, m + 1, -1, -1);
	bool** c = b.get();
	c[-1][-1] = true;
	for (int i = 0; i < n; ++i)
		c[i][-1] = false;
	for (int j = 0; j < m; ++j)
		c[-1][j] = c[-1][j - 1] & (P[j] == '*');
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (A[i] == P[j] || P[j] == '?')
				c[i][j] = c[i - 1][j - 1];
			else if (P[j] == '*')
				c[i][j] = c[i - 1][j] | c[i][j - 1];
			else
				c[i][j] = false;
		}
	}
	
	return c[n - 1][m - 1];
}

int main(int argc, char* argv[])
{
	char* testA = "hello";
	char* testB = "*o";

	printf("%s %s %d\n", testA, testB, wildcard_matching(testA, testB));

	return 0;
}
