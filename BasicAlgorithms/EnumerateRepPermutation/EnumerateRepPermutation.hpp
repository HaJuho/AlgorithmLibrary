#ifndef __ENUMERATE_REP_PERMUTATION_HPP__
#define __ENUMERATE_REP_PERMUTATION_HPP__

template<typename RandomIterator, typename Predicate>
class EnumerateRepPermutation {
	int _index_begin[64];
	RandomIterator _begin;
	Predicate& _p;
	int* const _index_end;
	int _n;

	bool enumerate_rep_perm(int* to_select)
	{
		if (to_select == _index_end)
			return _p(_begin, _index_begin, _index_end);

		for (int i = 0; i < _n; ++i) {
			*to_select = i;
			if (enumerate_rep_perm(to_select + 1))
				return true;
		}
		return false;
	}

public:
	EnumerateRepPermutation(RandomIterator& begin, RandomIterator& end, int r, Predicate& p) :
		_begin(begin), _p(p),
		_index_end(_index_begin + r),
		_n(end - begin)
	{
	}

	bool enumerate_rep_perm()
	{
		return enumerate_rep_perm(_index_begin);
	}
};

template<typename RandomIterator, typename Predicate>
bool enumerate_rep_perm(RandomIterator begin, RandomIterator end, int r, Predicate& p)
{
	EnumerateRepPermutation<RandomIterator, Predicate> erp(begin, end, r, p);
	return erp.enumerate_rep_perm();
}

#endif /* __ENUMERATE_REP_PERMUTATION_HPP__ */
