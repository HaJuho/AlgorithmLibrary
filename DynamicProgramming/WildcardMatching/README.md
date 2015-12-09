# Wildcard Matching

와일드 카드 매칭 문제

텍스트 A[0...n-1]과 패턴 P[0...m-1]이 주어질 때 A에서 패턴 P를 찾을 수 있는가?

패턴 P에 와일드 카드 '*'와 '?'이 포함될 수 있다.

C(i,j)를 A[0...i]와 P[0...j]가 매칭되는 지 여부라고 하자.

C(-1,-1) = true

C(i,-1) = false if i >= 0

C(-1,j) = C(-1,j-1) && P[j-1]=='*' if j >= 0

C(i,j) = C(i-1,j-1) if i >= 0 && j >= 0 && (A[i]==P[j] || P[j]=='?')

C(i,j) = C(i-1,j) || C(i,j-1) if i >= 0 && j >= 0 && (P[j]=='*')

C(i,j) = false if others

시간 복잡도 O(N^2)

공간 복잡도 O(N^2). O(N)으로 최적화 가능