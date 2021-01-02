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
		DynamicArr(istream& in, Election* election);
		DynamicArr(istream& in, DynamicArr<T> citizens);
		~DynamicArr();

	public:
		// returns size of array
		int length() const { return _logSize; }
		T* getArr() { return _array; }

	public:
		T operator[](int idx) { return _array[idx]; }
		T operator[](int idx) const { return _array[idx]; }
		friend ostream& operator<<(ostream& os, const DynamicArr<T>& element);

	public:
		// append at the end
		void insert(T element);
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
		//returns the party with most electors
		T getElectionWinner();

	public:
		void save(ostream& out) const;
		void load(istream& in);
		void load(istream& in, Election* election);
		void saveId(ostream& out) const;
		void loadById(istream& in, DynamicArr<T> citizens);
		void saveVotes(ostream& out) const;
		void loadVotes(istream& in, DynamicArr<T> parties);
		
	};
		

	template<class T>
	DynamicArr<T>::DynamicArr(T element) : _logSize(1), _phySize(2) {
		_array = new T[_phySize];
		_array[0] = element;
	}

	template<class T>
	DynamicArr<T>::DynamicArr(istream& in, Election* election) {
		load(in, election);
	}

	template<>
	DynamicArr<Citizen*>::DynamicArr(istream& in, DynamicArr<Citizen*> citizens) {
		loadById(in, citizens);
	}

	template<class T>
	DynamicArr<T>::~DynamicArr() {
		for (int i = 0;i < _logSize;i++) {
			delete _array[i];
		}
		delete[] _array;
	}

	template<class T>
	void DynamicArr<T>::insert(T element) {
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
		for (int i = 0;i < element.length(); i++) {
			os << element[i];
		}
		return os;
	}

	
	template<>
	ostream& operator<<(ostream& os, const DynamicArr<District*>& disArr) {
		for (int i = 0; i < disArr.length() ; i++) {
			if (typeid(*(disArr[i])) == typeid(UniformDis))
				os << *(static_cast<UniformDis*>(disArr[i])) << endl;
			else
				os << *(static_cast<DevidedDis*>(disArr[i])) << endl;
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
	void DynamicArr<T>::save(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			_array[i]->save(out);
		}
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Save issue" << endl;
			exit(-1);
		}
	}

	template<>
	void DynamicArr<District*>::load(istream& in) {
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new District*[_phySize];

		for (int i = 0; i < _phySize; i++) {
			_array[i] = DistrictLoader::load(in);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictArr load issue" << endl;
			exit(-1);
		}
	}
	
	template<class T>
	void DynamicArr<T>::load(istream& in, Election* election) {
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new T[_phySize];
		for (int i = 0; i < _phySize; i++) {
			_array[i] = new T(in, election);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Load issue" << endl;
			exit(-1);
		}
	}

	template<class T>
	void DynamicArr<T>::saveId(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_array[i]->saveId(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	template<class T>
	void DynamicArr<T>::loadById(istream& in, DynamicArr<T> citizens) {
		int tempSize = 0;
		char* tempCitId;

		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new T [_phySize];

		for (int i = 0; i < _logSize; i++) {
			in.read(rcastc(&tempSize), sizeof(int));
			tempCitId = new char[tempSize + 1];
			in.read(rcastc(tempCitId), sizeof(char) * tempSize);
			tempCitId[tempSize] = '\0';
			_array[i] = citizens->getCit(tempCitId);
			delete[] tempCitId;

			//next ex we will implament try&catch
			if (!in.good()) {
				cout << "Load issue" << endl;
				exit(-1);
			}
		}
	}

	template<class T>
	void DynamicArr<T>::saveVotes(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->saveVote(out);
		}
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Save issue" << endl;
			exit(-1);
		}
	}

	template<class T>
	void DynamicArr<T>::loadVotes(istream& in, DynamicArr<T> parties) {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->loadVote(in, parties);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	template<class T>
	T DynamicArr<T>::getElectionWinner() {
		Party* winner = nullptr;
		int winnerElectors = 0;

		for (int i = 0;i < _logSize;i++) {
			if (_array[i]->getTotalElectors() > winnerElectors) {
				winnerElectors = _array[i]->getTotalElectors();
				winner = _array[i];
			}
		}
		return winner;
	}
}




