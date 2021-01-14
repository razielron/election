#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	template<class T>
	class DynamicArr {

	protected:
		T* _array;
		const int GROTH_FACTOR = 2;
		int _logSize;
		int _phySize;

	public:
		DynamicArr(int size = 1);
		DynamicArr(T);
		DynamicArr(istream& in);
		~DynamicArr();

	public:
		// returns size of array
		int size() const { return _logSize; }
		//returns array
		T* getArr() { return _array; }
		//returns the first element in the array
		const T& front() const { return _array[0]; }
		// return true if the array is empty
		bool empty() const { return _logSize == 0; }
		// returns the physical size
		int capacity() const { return _phySize; }
		//clears the array
		void clear() { _logSize = 0; }

	public:
		T operator[](int idx) { return _array[idx]; }
		T operator[](int idx) const { return _array[idx]; }
		bool operator!() const { return this == nullptr; }
		friend ostream& operator<<(ostream& os, const DynamicArr<T>& element) {
			if (!os || !element) {
				throw invalid_argument("DynamicArr, operator<<, parameter issue");
			}

			for (int i = 0;i < element.size(); i++) {
				os << *(element[i]);
			}
			return os;
		}

	public:
		// append at the end
		void push_back(T element);
		//delete at given position
		void erase(int pos);
		//insert at given position, and increse the array accordingly
		void insertAt(T element, int pos);
		// doubles capacity if it has to and deletes reference to current array
		void resize();
		// copies original array into temp
		void copy(T* element);
		// returns element in a given position
		T at(int pos);
		//returns an element by given parameter
		T find(string id);
		//returns an element by given parameter
		T find(int id);
		//Swaps elements
		void swap(T al1, T el2);
		//deletes all values in the array
		void deleteValues();


		/*------------------------Iterator Class------------------------*/


		template <bool is_const>
		class base_iterator
		{
		public:
			using ds_type = std::conditional_t<is_const, const DynamicArr, DynamicArr>;

			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = std::conditional_t<is_const, const T, T>;
			using pointer = value_type*;
			using reference = value_type&;

			base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

			//default constructor
			base_iterator(const base_iterator&) = default;

			constexpr base_iterator& operator=(const base_iterator&) = default;

			friend class base_iterator<true>;
			template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
			base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}

			bool operator==(const base_iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const base_iterator& other) const {
				return !(*this == other);
			}


			reference operator*() {
				return _da->_arr[_i];
			}
			pointer operator->() {
				return &_da->_arr[_i];
			}

			// increment-decrement iterator methods
			virtual base_iterator& operator++() {
				++_i;
				return *this;
			}
			virtual base_iterator operator++(int) {
				base_iterator temp(*this);
				++_i;
				return temp;
			}
			virtual base_iterator& operator--() {
				--_i;
				return *this;
			}
			virtual base_iterator operator--(int) {
				base_iterator temp(*this);
				--_i;
				return temp;
			}

		protected:
			ds_type* _da;
			int	_i;

		};

		/*------------------------End of Iterator Class------------------------*/

		using iterator = base_iterator<false>;
		using const_iterator = base_iterator<true>;

	public:
		//inserts a value in a given position
		void insert(const iterator& pos, const T& val) {
			if (!pos || !val) {
				throw invalid_argument("DynamicArr, insert, parameters issue");
			}

			if (_logSize == _phySize)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}

			iterator p = pos;
			*p = val;
			++_logSize;
		}
		//earases the values in a given pos
		const iterator& erase(const iterator& pos) {
			if (pos._i > _logSize) {
				throw invalid_argument("DynamicArr, erase, parameters issue");
			}

			delete* pos;
			_logSize--;
			iterator itrCurrent = pos, itrEndCurrent = pos++;


			while (itrEndCurrent != end()) {
				*itrCurrent = *itrEndCurrent;
				delete* itrEndCurrent;
				itrCurrent++;
				itrEndCurrent++;
			}

			return pos--;
		}
		//earases the values in a given range and returns iterator the one step before
		const iterator& erase(const iterator& first, const iterator& last) {
			if (first._i > _logSize || last._i > _logSize) {
				throw invalid_argument("DynamicArr, erase, parameters issue");
			}

			iterator itrCurrent = first, itrEndCurrent = last;
			while (itrCurrent != last)
			{
				delete* itrCurrent;
				itrCurrent++;
			}

			itrCurrent = first;
			while (itrEndCurrent != end()) {
				*itrCurrent = *itrEndCurrent;
				delete* itrEndCurrent;
				itrCurrent++;
				itrEndCurrent++;
			}

			_logSize -= last._i - first._i;
			return first--;
		}
		//returns iterator at the beginning of the array
		iterator begin() { return iterator(*this, 0); }
		//returns iterator at the end of the array
		iterator end() { return iterator(*this, _logSize); }
		
		//Swaps elements
		template<class T>
		void swap(iterator& i, iterator& j) {
			if (!i || !j) {
				throw invalid_argument("DynamicArr, swap, parameters issue");
			}

			T temp = *i;
			*i = *j;
			*j = temp;
		}

		//Sorts the array according to given function
		template<class T, class Func>
		void sort(iterator& first, iterator& last, const Func& func) {
			if (!first || !last) {
				throw invalid_argument("DynamicArr, sort, parameters issue");
			}

			iterator temp = first;
			for (iterator i = first; i != last; ++i)
				for (iterator j = first; j._i < last._i - i._da + 1; ++j)
					if (func(i, j))
						swap(*i, *j);
		}
		
	};
		
	/*------------------------DynamicArr Functions Implementation------------------------*/
	template<class T>
	DynamicArr<T>::DynamicArr(int size) : _logSize(0), _phySize(size) {
		if (size < 0) {
			throw invalid_argument("DyncamicArr, constructor(size), size cannot be negative");
		}
		try {
			_array = _phySize ? new T[_phySize] : nullptr;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	};
	
	template<class T>
	DynamicArr<T>::DynamicArr(T element) : _logSize(1), _phySize(2) {
		if (!element) {
			throw invalid_argument("DyncamicArr, constructor(element), paramerter issue");
		}

		try {
			_array = new T[_phySize];
			_array[0] = element;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	}

	template<class T>
	DynamicArr<T>::DynamicArr(istream& in) : _logSize(0) {
		if (!in) {
			throw invalid_argument("DyncamicArr, constructor(size), size cannot be negative");
		}

		in.read(rcastc(&_phySize), sizeof(int));
		if (!in.good()) {
			throw iostream::failure("PartyCandidates, load(in, districts, citizens)");
		}

		try {
			_array = new T[_phySize];
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	};

	template<class T>
	DynamicArr<T>::~DynamicArr() {
		delete[] _array;
	}

	//deletes all values in the array
	template<class T>
	void DynamicArr<T>::deleteValues() {
		for (int i = 0; i < _logSize; i++) {
			delete _array[i];
		}
	}

	template<class T>
	void DynamicArr<T>::push_back(T element) {
		if (!element) {
			throw invalid_argument("DyncamicArr, pushBack, paramerter issue");
		}

		if (_logSize == _phySize) {
			resize();
		}
		_array[_logSize] = element;
		_logSize++;
	}

	template<class T>
	void DynamicArr<T>::erase(int pos) {
		if (pos > _logSize || pos < 0) {
			throw invalid_argument("DyncamicArr, erase, paramerter issue");
		}
		delete _array[pos];
		for (int i = pos;i < _logSize-1;i++)
			_array[i] = _array[i + 1];
		delete _array[_logSize-1];
		_logSize--;
	}

	template<class T>
	void DynamicArr<T>::insertAt(T element, int pos) {
		if (pos > _logSize || pos < 0) {
			throw out_of_range("DynamicArr, insertAt, out of range");
		}

		if (_logSize == _phySize) {
			resize();
		}
		_logSize++;

		for (int i = _logSize - 1;i >= pos;i--) {
			if (i == pos)
				_array[pos] = element;
			else {
				_array[i] = _array[i - 1];
			}
		}
	}

	template<class T>
	void DynamicArr<T>::resize() {
		try {
			_phySize *= GROTH_FACTOR;
			T* temp = new T[_phySize];
			copy(temp);
			delete[] _array;
			_array = temp;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	} 

	template<class T>
	void DynamicArr<T>::copy(T* element) {
		if (!element) {
			throw invalid_argument("DyncamicArr, copy, paramerter issue");
		}

		for (int i = 0;i < _logSize;i++) {
			element[i] = _array[i];
		}
	}

	template<class T>
	T DynamicArr<T>::at(int pos) {
		if (pos > _logSize || pos < 0) {
			throw out_of_range("DynamicArr, at, out of range");
		}
		return _array[pos];
	}

	template<class T>
	T DynamicArr<T>::find(string id) {
		for (int i = 0;i < _logSize;i++) {
			if (!(_array[i]->getId().compare(id)))
				return _array[i];
		}
		
		throw runtime_error("DynamicArr, find, cannot find element by given string id");
	}

	template<class T>
	T DynamicArr<T>::find(int id) {
		for (int i = 0;i < _logSize;i++) {
			if (_array[i]->getId() == id)
				return _array[i];
		}
		
		throw runtime_error("DynamicArr, find, cannot find element by given int id");
	}

	template<class T>
	void DynamicArr<T>::swap(T el1, T el2) {
		T temp = el1;
		el1 = el2;
		el2 = temp;
	}			
}




