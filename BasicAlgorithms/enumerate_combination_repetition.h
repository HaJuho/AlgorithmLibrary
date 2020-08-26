#ifndef __ENUMERATE_COMBINATION_REPETITION_H__
#define __ENUMERATE_COMBINATION_REPETITION_H__

template<typename RandomIterator, typename Predicate>
class EnumerateRepCombination {
	int _index_begin[64];
	RandomIterator _begin;
	Predicate& _p;
	int* const _index_end;
	int _n;

	bool enumerate_rep_comb(int* to_select, int cand)
	{
		if (to_select == _index_end)
			return _p(_begin, _index_begin, _index_end);
		else if (cand == _n)
			return false;

		*to_select = cand;
		if (enumerate_rep_comb(to_select + 1, cand))
			return true;
		return enumerate_rep_comb(to_select, cand + 1);
	}

public:
	EnumerateRepCombination(RandomIterator& begin, RandomIterator& end, int r, Predicate& p) :
		_begin(begin), _p(p),
		_index_end(_index_begin + r),
		_n(end - begin)
	{
	}

	bool enumerate_rep_comb()
	{
		return enumerate_rep_comb(_index_begin, 0);
	}
};

template<typename RandomIterator, typename Predicate>
bool enumerate_rep_comb(RandomIterator begin, RandomIterator end, int r, Predicate& p)
{
	EnumerateRepCombination<RandomIterator, Predicate> ec(begin, end, r, p);
	return ec.enumerate_rep_comb();
}

#endif  // __ENUMERATE_COMBINATION_REPETITION_H__
