#ifndef __ENUMERATE_SUBSETS_HPP__
#define __ENUMERATE_SUBSETS_HPP__

template<typename RandomIterator, typename Predicate>
class EnumerateSubsets {
	int _index_begin[64];
	RandomIterator _begin;
	Predicate& _p;
	int _n;

	bool enumerate_subsets(int* to_select, int cand)
	{
		if (cand == _n)
			return _p(_begin, _index_begin, to_select);

		*to_select = cand;
		if (enumerate_subsets(to_select + 1, cand + 1))
			return true;
		return enumerate_subsets(to_select, cand + 1);
	}

public:
	EnumerateSubsets(RandomIterator& begin, RandomIterator& end, int r, Predicate& p) :
		_begin(begin), _p(p), _n(end - begin)
	{
	}

	bool enumerate_subsets()
	{
		return enumerate_subsets(_index_begin, 0);
	}
};

template<typename RandomIterator, typename Predicate>
bool enumerate_subsets(RandomIterator begin, RandomIterator end, int r, Predicate& p)
{
	EnumerateSubsets<RandomIterator, Predicate> ec(begin, end, r, p);
	return ec.enumerate_subsets();
}

#endif /* __ENUMERATE_SUBSETS_HPP__ */
