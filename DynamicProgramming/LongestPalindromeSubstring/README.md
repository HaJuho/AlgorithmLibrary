# Longest Palindrome Substring

���� ȸ�� �κ� ���� ����

Palindrome�� ���ʿ��� ���� ���� �����ʿ��� ���� �� ���� ���ڿ�(����)

���� A[0...n-1]�� ���� ��, ���� ȸ�� �κ� ���� ������ ���̴�?

B(i,j) = A[i...j]�� ȸ���̸� true, �ƴϸ� false

```
B(i,j) = true, if i > j
B(i,i) = true
B(i,j) = B(i+1,j-1), if A[i] == A[j], i < j
B(i,j) = false, if A[i] != A[j], i < j
```

�ð� ���⵵ O(N^2)

���� ���⵵ O(N^2). �ݺ��� DP�� O(N) ���������� �����ϴ�. (triple buffer?)
