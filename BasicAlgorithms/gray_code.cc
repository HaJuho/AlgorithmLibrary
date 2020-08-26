#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int bin_to_gray(int v, int len)
{
	int g = 0;
	int v1 = 0;
	for (int i = len - 1; i >= 0; --i) {
		int v2 = (v >> i) & 1;
		g |= (v1 ^ v2) << i;
		v1 = v2;
	}
	return g;
}

int gray_to_bin(int v, int len)
{
	int b = 0;
	int v1 = 0;
	for (int i = len - 1; i >= 0; --i) {
		int v2 = ((v >> i) & 1) ^ v1;
		b |= v2 << i;
		v1 = v2;
	}
	return b;
}

void print_gray(string& code, int pos)
{
	if (pos == code.size()) {
		cout << code << endl;
		return;
	}

	print_gray(code, pos + 1);
	code[pos] = '1' + '0' - code[pos];
	print_gray(code, pos + 1);
}

int main()
{
	string code("00000");
	print_gray(code, 0);

	for (int i = 0; i < 32; ++i) {
		int g = bin_to_gray(i, 5);
		int b = gray_to_bin(g, 5);
		cout << i << " " << bitset<8>(g) << " " << bitset<8>(b) << " " << b << endl;
	}

	return 0;
}
