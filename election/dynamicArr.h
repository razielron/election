#include "districtLoader.h"
#include "devidedDis.h"
#include "uniformDis.h"
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


namespace Elections
{
	class Election;
	class District;
	template<class T>
	class DynamicArr {
	private:
		T* _array;
		const int GROTH_FACTOR = 2;
		int _logSize;
		int _phySize;

	public:
		DynamicArr() :_logSize(0), _phySize(1), _array(new T[_phySize]) {};
		DynamicArr(T);
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
		friend ostream& operator<<(ostream& os, const DynamicArr<T>& element);

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


		/*------------------------Iterator Class------------------------*/


		template <bool is_const>
		class base_iterator
		{
		private:
			ds_type* _da;
			int	_i;

		public:
			using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;

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
			base_iterator& operator++() {
				++_i;
				return *this;
			}
			base_iterator operator++(int) {
				base_iterator temp(*this);
				++_i;
				return temp;
			}
			base_iterator& operator--() {
				--_i;
				return *this;
			}
			base_iterator operator--(int) {
				base_iterator temp(*this);
				--_i;
				return temp;
			}

		};

		/*------------------------End of Iterator Class------------------------*/

		using iterator = base_iterator<false>;
		using const_iterator = base_iterator<true>;

	public:
		//inserts a value in a given position
		void insert(const iterator& pos, const T& val);
		//earases the values in a given pos
		const iterator& erase(const iterator& pos);
		//earases the values in a given range and returns iterator the one step before
		const iterator& erase(const iterator& first, const iterator& last);
		//returns iterator at the beginning of the array
		iterator begin() { return iterator(*this, 0); }
		//returns iterator at the end of the array
		iterator end() { return iterator(*this, _logSize); }
		
		
		//Swaps elements
		template<class T>
		void swap(iterator& i, iterator& j) {
			T temp = *i;
			*i = *j;
			*j = temp;
		}
		//Sorts the array according to given function
		template<class T, class Func>
		void sort(iterator& first, iterator& last, const Func& func) {
			iteratr temp = first;
			for (iterator i = first; i != last; ++i)
				for (iterator j = first; j._i < last._i - i._da + 1; ++j)
					if (func(i, j) < 0)
						swap(*i, *j);
		}
		
	};
		
	/*------------------------DynamicArr Functions Implementation------------------------*/

	template<class T>
	DynamicArr<T>::DynamicArr(T element) : _logSize(1), _phySize(2) {
		_array = new T[_phySize];
		_array[0] = element;
	}

	template<class T>
	DynamicArr<T>::~DynamicArr() {
		for (int i = 0;i < _logSize;i++) {
			delete _array[i];
		}
		delete[] _array;
	}

	template<class T>
	void DynamicArr<T>::push_back(T element) {
		if (_logSize == _phySize) {
			resize();
		}
		_array[_logSize] = element;
		_logSize++;
	}

	template<class T>
	void DynamicArr<T>::erase(int pos) {
		if (pos > _logSize || pos < 0) {
			cout << "Invalid syntax" << endl;
			return;
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
			cout << "Invalid syntax" << endl;
			return;
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
		_phySize *= GROTH_FACTOR;
		T* temp = new T[_phySize];
		copy(temp);
		delete[] _array;
		_array = temp; //!!!!!!
	} 

	template<class T>
	void DynamicArr<T>::copy(T* element) {
		for (int i = 0;i < _logSize;i++) {
			element[i] = _array[i];
		}
	}

	template<class T>
	T DynamicArr<T>::at(int pos) {
		if (pos > _logSize || pos < 0) {
			cout << "Invalid syntax" << endl;
			return nullptr;
		}
		return _array[pos];
	}

	template<class T>
	ostream& operator<<(ostream& os, const DynamicArr<T>& element) {
		for (int i = 0;i < element.size(); i++) {
			os << element[i];
		}
		return os;
	}

	template<class T>
	T DynamicArr<T>::find(string id) {
		for (int i = 0;i < _logSize;i++) {
			if (!(_array[i]->getId().compare(id)))
				return _array[i];
		}
		return nullptr;	
	}

	template<class T>
	T DynamicArr<T>::find(int id) {
		for (int i = 0;i < _logSize;i++) {
			if (!(_array[i]->getId() == id))
				return _array[i];
		}
		return nullptr;
	}

	template<class T>
	void DynamicArr<T>::swap(T el1, T el2) {
		T temp = el1;
		el1 = el2;
		el2 = temp;
	}

	template<class T>
	void DynamicArr<T>::insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
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
		++_logicalSize;
	}

	template<class T>
	const DynamicArr<T>::iterator& DynamicArr<T>::erase(const iterator& pos) {
		if (pos._i > _logSize) {
			cout << "Error" << endl;
			return nullptr;
		}
		
		delete* pos;
		_logSize--;
		iterator itrCurrent = pos, itrEndCurrent = pos++;


		while (itrEndCurrent != end()) {
			*itrCurrent = *itrEndCurrent;
			delete *itrEndCurrent;
			itrCurrent++;
			itrEndCurrent++;
		}

		return pos--;
	}

	template<class T>
	const DynamicArr<T>::iterator& DynamicArr<T>::erase(const iterator& first, const iterator& last) {
		if (pos._i > _logSize) {
			cout << "Error" << endl;
			return nullptr;
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
				
}




