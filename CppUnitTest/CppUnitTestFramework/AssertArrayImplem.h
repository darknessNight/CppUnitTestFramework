#include "AssertArray.h"
#pragma once

template<typename T>
inline bool AssertArray::checkAreEqual(T expIter, T expEnd, T resIter, T resEnd)
{
	if (isDiffLenght(expIter, expEnd, resIter, resEnd))
		return false;

	return std::equal(expIter, expEnd, resIter, resEnd);
}
template<typename T>
inline bool AssertArray::isDiffLenght(T & expIter, T & expEnd, T & resIter, T & resEnd) {
	return expEnd - expIter != resEnd - resIter;
}


template<typename T>
inline bool AssertArray::checkAreEquivalent(T expIter, T expEnd, T resIter, T resEnd)
{
	if (isDiffLenght(expIter, expEnd, resIter, resEnd))
		return false;

	auto el = *expIter;
	auto resEls = getCopyOfArray<decltype(el)>(resIter, resEnd);
	auto expEls = getCopyOfArray<decltype(el)>(expIter, expEnd);
	sortArrays(resEls, expEls);
	return checkAreEqual(resEls.begin(), resEls.end(), expEls.begin(), expEls.end());
}
template<typename T>
inline void AssertArray::sortArrays(std::vector<T>& resEls, std::vector<T>& expEls)
{
	std::sort(resEls.begin(), resEls.end());
	std::sort(expEls.begin(), expEls.end());
}
template<typename T, typename U>
inline std::vector<T> AssertArray::getCopyOfArray(U & arrIter, U & arrEnd) {
	std::vector<T> arrEls(arrEnd - arrIter);
	std::copy(arrIter, arrEnd, arrEls.begin());
	return arrEls;
}
template<typename T>
inline bool AssertArray::checkContains(T expIter, T expEnd, T resIter, T resEnd)
{
	if (resEnd - resIter < expEnd - expIter)
		return false;

	auto el = *expIter;
	auto resEls = getCopyOfArray<decltype(el)>(resIter, resEnd);
	auto expEls = getCopyOfArray<decltype(el)>(expIter, expEnd);
	std::sort(resEls.begin(), resEls.end());
	std::sort(expEls.begin(), expEls.end());

	return findAllElements(expEls, resEls);
}
template<typename T>
inline bool AssertArray::findAllElements(std::vector<T>& expEls, std::vector<T>& resEls)
{
	auto res = resEls.begin();
	for (auto exp : expEls) {
		if (!hasPassElementInResult(res, resEls, exp))
			return false;
	}
	return true;
}
template<typename T, typename U, typename W>
inline bool AssertArray::hasPassElementInResult(W &res, std::vector<T> & resEls, U &exp) {
	if (res == resEls.end())
		return false;
	while (*res != exp) {
		res++;
		if (res == resEls.end())
			return false;
	}
	res++;
	return true;
}
template<typename T>
inline bool AssertArray::checkIsSubsequence(T expIter, T expEnd, T resIter, T resEnd)
{
	if (resEnd - resIter < expEnd - expIter || expEnd - expIter <= 0)
		return false;

	return findSubsequence(resIter, resEnd, expIter, expEnd);
}
template<typename T>
inline bool AssertArray::findSubsequence(T & resIter, T & resEnd, T & expIter, T & expEnd)
{
	for (; resIter != resEnd; resIter++) {
		if (*resIter == *expIter) {
			if (isSubsequence(resIter, expIter, resEnd, expEnd))
				return true;
		}
	}
	return false;
}
template<typename T>
inline bool AssertArray::isSubsequence(T & resIter, T & expIter, T & resEnd, T & expEnd)
{
	auto resI = resIter;
	auto expI = expIter;
	moveIteratorToEndEqualSequences(resI, expI, resEnd, expEnd);
	return foundedSubsequence(expI, expEnd, resI, resEnd);
}
template<typename T>
inline void AssertArray::moveIteratorToEndEqualSequences(T & resI, T & expI, T & resEnd, T & expEnd)
{
	while (*resI == *expI) {
		resI++; expI++;
		if (resI == resEnd || expI == expEnd)
			break;
	}
}
template<typename T>
inline bool AssertArray::foundedSubsequence(T & expI, T & expEnd, T & resI, T & resEnd)
{
	if (expI == expEnd)
		return true;
	if (resI == resEnd)
		return false;
	return false;
}
template<typename T>
inline bool AssertArray::checkIsOrdered(T resIter, T resEnd)
{
	if (resIter != resEnd) {
		auto oldVal = resIter;
		resIter++;
		return checkOrderedAllItems(resIter, resEnd, oldVal);
	}
	return true;
}
template<typename T>
inline bool AssertArray::checkOrderedAllItems(T & resIter, T & resEnd, T & oldVal)
{
	for (; resIter != resEnd; resIter++) {
		if (*oldVal > *resIter)
			return false;
		oldVal = resIter;
	}
	return true;
}
template<typename T, typename U>
inline bool AssertArray::checkAllItemsAre(T resIter, T resEnd, bool(*predicate)(const U item))
{
	for (; resIter != resEnd; resIter++)
		if (!predicate(resIter))
			return false;
	return true;
}
template<typename T>
inline bool AssertArray::checkAllItemsAreUnique(T resIter, T resEnd)
{
	if (resIter == resEnd)
		return true;
	auto el = *resIter;
	auto els = countOccurrences<decltype(el)>(resIter, resEnd);

	return checkAllItemsOccurrOnlyOnce(els);
}
template<typename T>
inline bool AssertArray::checkAllItemsOccurrOnlyOnce(std::map<T, int>& els)
{
	for (auto i : els) {
		if (i.second > 1)
			return false;
	}
	return true;
}
template<typename U, typename T>
inline std::map<U, int> AssertArray::countOccurrences(T & resIter, T & resEnd)
{
	std::map<U, int> els;
	for (; resIter != resEnd; resIter++)
		els[*resIter]++;
	return els;
}