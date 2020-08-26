#ifndef __ENUMERATE_COMBINATION_H__
#define __ENUMERATE_COMBINATION_H__

template<typename RandomIterator, typename Predicate>
class EnumerateCombination {
	int _index_begin[64];
	RandomIterator _begin;
	Predicate& _p;
	int* const _index_end;
	int _n;

	bool enumerate_comb(int* to_select, int cand)
	{
		int r = _index_end - to_select;
		if (r == 0)
			return _p(_begin, _index_begin, _index_end);
		else if (r > _n - cand)
			return false;

		*to_select = cand;
		if (enumerate_comb(to_select + 1, cand + 1))
			return true;
		return enumerate_comb(to_select, cand + 1);
	}

public:
	EnumerateCombination(RandomIterator& begin, RandomIterator& end, int r, Predicate& p) :
		_begin(begin), _p(p),
		_index_end(r > (end - begin) ? _index_begin + (end - begin) : _index_begin + r),
		_n(end - begin)
	{
	}

	bool enumerate_comb()
	{
		return enumerate_comb(_index_begin, 0);
	}
};

template<typename RandomIterator, typename Predicate>
bool enumerate_comb(RandomIterator begin, RandomIterator end, int r, Predicate& p)
{
	EnumerateCombination<RandomIterator, Predicate> ec(begin, end, r, p);
	return ec.enumerate_comb();
}

#endif  // __ENUMERATE_COMBINATION_H__
