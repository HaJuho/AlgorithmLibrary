#ifndef __ENUMERATE_PERMUTATION_HPP__
#define __ENUMERATE_PERMUTATION_HPP__

#include <algorithm>

template<typename RandomIterator, typename Predicate>
class EnumeratePermutation {
	int _index_begin[64];
	RandomIterator _begin;
	Predicate& _p;
	int* const _index_end;
	int* const _cand_index_end;

	bool enumerate_perm(int* to_select)
	{
		if (to_select == _index_end)
			return _p(_begin, _index_begin, _index_end);

		for (int* it = to_select; it != _cand_index_end; ++it) {
			std::swap(*to_select, *it);
			if (enumerate_perm(to_select + 1))
				return true;
			std::swap(*to_select, *it);
		}
		return false;
	}

public:
	EnumeratePermutation(RandomIterator& begin, RandomIterator& end, int r, Predicate& p) :
		_begin(begin), _p(p),
		_index_end(r > (end - begin) ? _index_begin + (end - begin) : _index_begin + r),
		_cand_index_end(_index_begin + (end - begin))
	{
		for (int i = 0, n = end - begin; i < n; ++i)
			_index_begin[i] = i;
	}

	bool enumerate_perm()
	{
		return enumerate_perm(_index_begin);
	}
};

template<typename RandomIterator, typename Predicate>
bool enumerate_perm(RandomIterator begin, RandomIterator end, int r, Predicate& p)
{
	EnumeratePermutation<RandomIterator, Predicate> ep(begin, end, r, p);
	return ep.enumerate_perm();
}

template<typename RandomIterator>
bool next_perm(RandomIterator begin, RandomIterator end)
{
	if (begin == end)
		return false;

	RandomIterator it = end - 1;
	while (it != begin && *(it - 1) >= *it)
		--it;
	reverse(it, end);
	
	if (it == begin)
		return false;
	else {
		auto it1 = it - 1;
		RandomIterator it2 = upper_bound(it, end, *it1);
		swap(*it1, *it2);
		return true;
	}
}

#endif /* __ENUMERATE_PERMUTATION_HPP__ */
