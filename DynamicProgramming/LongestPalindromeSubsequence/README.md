# Longest Palindrome Subsequence

���� ȸ�� �κ� ����

Palindrome�� ���ʿ��� ���� ���� �����ʿ��� ���� �� ���� ���ڿ�(����)

���� A[0...n-1]�� ���� ��, ���� ȸ�� �κ� ������ ���̴� ?

Subsequence�� �������� ������ �ʿ�� ����.

B(i,j) = A[i...j]������ ���� ȸ�� �κ� ����

```
B(i,j) = 0, if i > j
B(i,i) = 1
B(i,j) = B(i+1,j-1) + 2, if A[i] == A[j], i < j
B(i,j) = max(B(i,j-1), B(i+1,j)), if A[i] != A[j], i < j
```

�ð� ���⵵ O(N^2)

���� ���⵵ O(N^2). �ݺ��� DP�� O(N) ���������� �����ϴ�. (triple buffer?)
