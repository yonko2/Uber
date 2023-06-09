#pragma once
#include <fstream>

/**
 * @source https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2012/Templates/Pair/Pair.hpp
 */

template<typename T, typename D>
class Pair
{
	T first;
	D second;
public:
	Pair() = default;
	Pair(const T& first, const D& second);
	const T& getFirst() const;
	const D& getSecond() const;

	void setFirst(const T& newValue);
	void setSecond(const D& newValue);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

template<typename T, typename D>
Pair<T, D>::Pair(const T& first, const D& second) : first(first), second(second)
{}

template<typename T, typename D>
const T& Pair<T, D>::getFirst() const
{
	return first;
}
template<typename T, typename D>
const D& Pair<T, D>::getSecond() const
{
	return second;
}

template<typename T, typename D>
void Pair<T, D>::setFirst(const T& newValue)
{
	first = newValue;
}

template<typename T, typename D>
void Pair<T, D>::setSecond(const D& newValue)
{
	second = newValue;
}

template <typename T, typename D>
void Pair<T, D>::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->first, sizeof T);
	ofs.write((const char*)&this->second, sizeof D);
}

template <typename T, typename D>
void Pair<T, D>::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&this->first, sizeof T);
	ifs.read((char*)&this->second, sizeof D);
}
