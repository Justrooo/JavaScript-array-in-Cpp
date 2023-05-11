#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <string>
#include <stdexcept>
#define COUT_OPERATOR true // true if you want << operator, false if not

template <typename T>
class Array // Array that is a vector but with Javascript functions like sort() or splice()
{
	std::vector<T> array;
	
	void quicksort(int left, int right) noexcept; // Quicksort algorithm to help sort() function
public:
	class iterator  // For range loop
	{
	public:
		iterator(T* ptr) : ptr(ptr) {}
		iterator operator++() { ++ptr; return *this; }
		bool operator!=(const iterator& other) const { return ptr != other.ptr; }
		const T& operator*() const { return *ptr; }
	private:
		T* ptr;
	};
	auto /* Thank God for the auto keyword */ begin() const { return array.begin(); } 
	auto /* Thank God for the auto keyword */ end() const { return array.end(); }

	Array(std::initializer_list<T> values); // Construct Array of initializer_list eg. Array<char> array {'a', 'b', 'c', 'd'} (vector-like behavior)
	Array(const int value_count, const T& value); // Construct Array of value_count elements, all of them are value eg. Array<char> array(4, 'X') ---> vector of {'X', 'X', 'X', 'X'}
	Array(const std::vector<T>& values); // Construct Array based of a vector
	Array() noexcept = default; // Default constructor

	// Overloaded operators
#if (COUT_OPERATOR == true)
	template <typename T>
	friend std::ostream& operator<<(std::ostream& cout, const Array<T>& array) noexcept;
	template <typename T>
	friend std::ostream& operator<<(std::ostream& cout, const Array<T>&& array) noexcept;
#endif

	Array<T> operator+(const Array& array) const; // same as concat()
	Array<T> operator+(const Array&& array) const;

	T& operator[](const unsigned int index);
	T operator[](const unsigned int index) const;

	// Public functions
	std::size_t length() const noexcept { return array.size(); }; // Returns length
	Array<T> concat(const Array<T>& model) const; // Concatenate (add) two Arrays of the same type
	std::string toString() const; // Convert Array to string (if it makes sense)
	std::string join(std::string sufix = ",") const; // Convert Array to string and add spacing
	Array<T> slice(std::size_t starting_pos = 0, std::size_t ending_pos = std::string::npos) const; // Make a sub-array
	Array<T> splice(std::size_t starting_pos = 0, std::size_t delete_count = std::string::npos) const; // Remove / replace elements in Array
	Array<T> splice(std::size_t starting_pos, std::size_t delete_count, const T& value); // Remove / replace elements in Array
	Array<T> splice(std::size_t starting_pos, std::size_t delete_count, std::initializer_list<T> values); // Remove / replace elements in Array
	std::size_t push(const T& value); // Push a new value at the back of the Array
	std::size_t push(std::initializer_list<T> values); // Push new values at the back of the Array using std::initializer_list
	std::size_t unshift(const T& value); // Push a new value at the beginning of the Array
	std::size_t unshift(std::initializer_list<T> values); // Push new values at the back of the Array using std::initializer_list
	T pop(); // Remove a value at the end of the Array
	T shift(); // Remove a value at the beginning of the Arrays
	Array<T> reverse(); // Reverse an Array
	Array<T> sort(); // (Quicksort algorithm) sort an Array

	template <typename T1>
	int indexOf(const T1& value) const noexcept; // Return first index of a value in Array if exists, if not returns -1
	template <typename T1>
	int lastIndexOf(const T1& value) const noexcept; // Return last index of a value in Array if exists, if not returns -1
	template <typename T1>
	bool includes(const T1& value) const noexcept; // Check if Array contains value
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Overloaded << operator for Array
#if (COUT_OPERATOR == true)
template <typename T>
std::ostream& operator<<(std::ostream& cout, const Array<T>& array) noexcept
{
	if (array.array.empty()) return cout << "[]";
	cout << "[ ";
	for (int i = 0; i < array.array.size() - 1; i++)
	{
		cout << array.array[i] << ", ";
	}
	cout << array.array[array.array.size() - 1] << " ]";
	return cout;
}
/***********************************************************************************************************************/
template <typename T>
std::ostream& operator<<(std::ostream& cout, const Array<T>&& array) noexcept
{
	if (array.array.empty()) return cout << "[]";
	cout << "[ ";
	for (int i = 0; i < array.array.size() - 1; i++)
	{
		cout << array.array[i] << ", ";
	}
	cout << array.array[array.array.size() - 1] << " ]";
	return cout;
}
/***********************************************************************************************************************/
#endif
template<typename T>
void Array<T>::quicksort(int left, int right) noexcept
{
	T v = array[(left + right) / 2];
	int i, j;
	T x;
	i = left;
	j = right;
	// Partitioning
	do {
		while (array[i] < v) i++;
		while (array[j] > v) j--;
		if (i <= j) {
			x = array[i];
			array[i] = array[j];
			array[j] = x;
			i++; j--;
		}
	} while (i <= j);
	// Recursion
	if (j > left) quicksort(left, j);
	if (i < right) quicksort(i, right);
}
/***********************************************************************************************************************/
template<typename T>
Array<T>::Array(std::initializer_list<T> values)
{
	for (const auto& value : values)
	{
		array.push_back(value);
	}
}
/***********************************************************************************************************************/
template<typename T>
Array<T>::Array(const int value_count, const T& value)
{
	for (int i = 0; i < value_count; i++)
	{
		array.push_back(value);
	}
}
/***********************************************************************************************************************/
template<typename T>
Array<T>::Array(const std::vector<T>& values)
{
	for (int i = 0; i < values.size(); i++)
	{
		array.push_back(values[i]);
	}
}
/***********************************************************************************************************************/
template<typename T>
inline Array<T> Array<T>::operator+(const Array& array) const
{
	return this->concat(array);
}
/***********************************************************************************************************************/
template<typename T>
inline Array<T> Array<T>::operator+(const Array&& array) const
{
	return this->concat(array);
}
/***********************************************************************************************************************/
template<typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index < array.size())
		return array[index];
	else
		throw std::out_of_range{"Index out of range."};
}
/***********************************************************************************************************************/
template<typename T>
inline T Array<T>::operator[](unsigned int index) const
{
	if (index < array.size())
		return array[index];
	else
		throw std::out_of_range{ "Index out of range." };
}
/***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::concat(const Array& model) const
{
	Array<T> result = array;
	for (int i = 0; i < model.array.size(); i++)
	{
		result.array.push_back(model.array[i]);
	}
	return result;
}
/***********************************************************************************************************************/
template<typename T>
std::string Array<T>::toString() const
{
	std::string result = "";
	for (int i = 0; i < array.size(); i++)
	{
		result += std::to_string(array[i]) + ",";
	}
	return result.substr(0, result.size()-1);
}
/***********************************************************************************************************************/
template<typename T>
inline std::string Array<T>::join(std::string sufix) const
{
	std::string result = "";
	for (int i = 0; i < array.size() - 1; i++)
	{
		result += std::to_string(array[i]) + sufix;
	}
	result += std::to_string(array[array.size() - 1]);
	return result;
}
/***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::slice(std::size_t starting_pos, std::size_t ending_pos) const
{
	if (ending_pos == std::string::npos) ending_pos = array.size();
	if (starting_pos < ending_pos && starting_pos < array.size() && ending_pos <= array.size())
	{
		Array<T> result;
		for (int i = starting_pos; i < ending_pos; i++)
		{
			result.array.push_back(array[i]);
		}
		return result;
	}
	else
		throw std::out_of_range{ "Index out of range." };
}
/***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::splice(std::size_t starting_pos, std::size_t delete_count) const
{
	if (delete_count == std::string::npos) delete_count = array.size();
	if (starting_pos < delete_count && starting_pos < array.size() && delete_count <= array.size())
	{
		Array<T> result = *this;
		for (int i = starting_pos; i < delete_count; i++)
		{
			if(array.size() != 0) result.shift();
		}
		return result;
	}
	else
		throw std::out_of_range{ "Index out of range." };
}
/***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::splice(std::size_t starting_pos, std::size_t delete_count, const T& value)
{
	if (delete_count == std::string::npos) delete_count = array.size();
	if (starting_pos <= delete_count && starting_pos < array.size() && delete_count <= array.size() && starting_pos + delete_count <= array.size())
	{
		Array<T> result;
		Array<T> result2;
		for (int i = 0; i < array.size(); i++)
		{
			if (i < starting_pos || i >= starting_pos + delete_count) result.array.push_back(array[i]);
		}
		for (int i = 0; i < result.array.size() + 1; i++)
		{
			if (i == starting_pos) result2.array.push_back(value);
			if (i < result.array.size()) result2.array.push_back(result.array[i]);
		}
		array = result2.array;
		return *this;
	}
	else if (array.empty())
		throw std::out_of_range{ "Cannot do operations on an empty Array." };
	else
		throw std::out_of_range{ "Index out of range." };
}
/***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::splice(std::size_t starting_pos, std::size_t delete_count, std::initializer_list<T> values)
{
	if (delete_count == std::string::npos) delete_count = array.size();
	if (starting_pos <= delete_count && starting_pos < array.size() && delete_count <= array.size() && starting_pos + delete_count <= array.size())
	{
		Array<T> result;
		Array<T> result2;
		for (int i = 0; i < array.size(); i++)
		{
			if (i < starting_pos || i >= starting_pos + delete_count) result.array.push_back(array[i]);
		}
		int i = 0;
		for (auto& value : values)
		{
			if (i == starting_pos)
			{
				for (auto& value : values)
				{
					result2.array.push_back(value);
				}
			}
			if (i < result.array.size()) result2.array.push_back(result.array[i]);
			i++;
		}
		array = result2.array;
		return *this;
	}
	else if (array.empty())
		throw std::out_of_range{ "Cannot do operations on an empty Array." };
	else
		throw std::out_of_range{ "Index out of range." };
}
/***********************************************************************************************************************/
template<typename T>
inline std::size_t Array<T>::push(const T& value)
{
	array.push_back(value);
	return array.size();
}
/***********************************************************************************************************************/
template<typename T>
std::size_t Array<T>::push(std::initializer_list<T> values)
{
	for (const auto& value : values)
	{
		array.push_back(value);
	}
	return array.size();
}
/***********************************************************************************************************************/
template<typename T>
std::size_t Array<T>::unshift(const T& value)
{
	Array result;
	result.array.push_back(value);
	for (int i = 0; i < array.size(); i++)
	{
		result.array.push_back(array[i]);
	}
	array = result.array;
	return array.size();
}
/***********************************************************************************************************************/
template<typename T>
std::size_t Array<T>::unshift(std::initializer_list<T> values)
{
	Array result;
	for (const auto& value : values)
	{
		result.array.push_back(value);
	}
	for (int i = 0; i < array.size(); i++)
	{
		result.array.push_back(array[i]);
	}
	array = result.array;
	return array.size();
}
/***********************************************************************************************************************//***********************************************************************************************************************/
template<typename T>
T Array<T>::pop()
{
	if (array.empty()) throw std::out_of_range{"Cannot do operations on an empty Array."};
	T last = array[array.size() - 1];
	array.pop_back();
	return last;
}
/***********************************************************************************************************************//***********************************************************************************************************************/
template<typename T>
T Array<T>::shift()
{
	if (array.empty()) throw std::out_of_range{ "Cannot do operations on an empty Array." };
	T first = array[0];
	Array result;
	for (int i = 0; i < array.size() - 1; i++)
	{
		result.array.push_back(array[i + 1]);
	}
	array = result.array;
	return first;
}
/***********************************************************************************************************************//***********************************************************************************************************************/
template<typename T>
inline Array<T> Array<T>::reverse()
{
	Array<T> result;
	for (int i = array.size() - 1; i >= 0; i--)
	{
		result.array.push_back(array[i]);
	}
	array = result.array;
	return *this;
}
/***********************************************************************************************************************//***********************************************************************************************************************/
template<typename T>
Array<T> Array<T>::sort()
{
	if (array.empty()) throw std::out_of_range{ "Cannot do operations on an empty Array." };
	quicksort(0, array.size() - 1);
	return *this;
}
/***********************************************************************************************************************//***********************************************************************************************************************/
template<typename T>
template<typename T1>
int Array<T>::indexOf(const T1& value) const noexcept
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i] == value) return i;
	}
	return -1;
}
/***********************************************************************************************************************/
template<typename T>
template<typename T1>
int Array<T>::lastIndexOf(const T1& value) const noexcept
{
	for (int i = array.size() - 1; i >= 0; i--)
	{
		if (array[i] == value) return i;
	}
	return -1;
}
/***********************************************************************************************************************/
template<typename T>
template<typename T1>
inline bool Array<T>::includes(const T1& value) const noexcept
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i] == value) return true;
	}
	return false;
}
/***********************************************************************************************************************/