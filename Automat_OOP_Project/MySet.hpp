#pragma once
template<typename T>
class Set {

private:
	T* elements;
	size_t size;
	size_t capacity;

	void CopySet(const Set<T>& other);
	void Clear();
	void Resize();

public:
	Set();
	Set(const Set<T>& other);
	Set<T>& operator=(const Set<T>& other);

	~Set();

	size_t getSize() const;

	T getElement(const int pos) const;

	T& operator[](const int);

	const T& operator[](const int)const;


	int getElementIndex(const T&);
	bool Add(T elem);
	bool Remove(T elem);
	bool RemoveAt(int index);
	bool Contains(T elem) const;
	bool isEmpty()const;
	void Print();
	void DeleteSet();

	bool ContainsAny(Set<T>);


	bool Equals(const Set<T>& other);

	template<typename T>
	friend bool operator==(const Set<T>& lhs, const Set<T>& rhs);


	bool operator==(const Set<T>& other)const;
	bool operator==(Set<T>& other)const;
	template<typename T>
	friend Set<T> Union(const Set<T>& set1, const Set<T>& set2);
	template<typename T>
	friend Set<T> Intersection(const Set<T>& set1, const Set<T>& set2);
	template<typename T>
	friend Set<T> SetDifference(const Set<T>& set1, const Set<T>& set2);

};


template<typename T>
Set<T>::Set() {

	capacity = 1;
	size = 0;
	elements = new(std::nothrow) T[capacity];
}

template<typename T>
Set<T>::~Set() {
	Clear();
}

template<typename T>
Set<T>::Set(const Set<T>& other) {
	CopySet(other);
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T>& other) {

	if (this != &other) {

		Clear();
		CopySet(other);
	}
	return *this;
}

template<typename T>
void Set<T>::CopySet(const Set<T>& other) {

	elements = new(std::nothrow) T[other.capacity];

	size = other.size;
	capacity = other.capacity;
	for (int i = 0; i < other.size; i++)
		elements[i] = other.elements[i];

}

template<typename T>
void Set<T>::Clear() {
	if (elements != nullptr) {
		delete[] elements;
	}

	elements = nullptr;
	size = 0;
	capacity = 2;
}

template<typename T>
void Set<T>::Resize() {

	T* temp = elements;
	elements = new(std::nothrow) T[capacity * 2];
	for (int i = 0; i < size; i++)
		elements[i] = temp[i];

	capacity = capacity * 2;
	delete[] temp;
}

template<typename T>
size_t Set<T>::getSize() const {
	return size;
}

template<typename T>
T Set<T>::getElement(int index) const {
	if (index >= 0 && index < size) {
		return this->elements[index];
	}
	else {
		std::cerr << "Invalid index exeption.";

	}
}

template<typename T>
T& Set<T>::operator[](const int index)
{
	if (index >= 0 && index < size) {
		return this->elements[index];
	}
	else {
		std::cerr << "Invalid index exeption.";

	}
}

template<typename T>
const T& Set<T>::operator[](const int index)const
{
	if (index >= 0 && index < size) {
		return this->elements[index];
	}
	else {
		std::cerr << "Invalid index exeption.";

	}
}


template<typename T>
int Set<T>::getElementIndex(const T& item)
{
	for (size_t i = 0; i < size; i++)
	{
		if (elements[i] == item)return i;
	}
	return -1;
}

template<typename T>
bool Set<T>::Add(T elem) {

	if (!Contains(elem)) {
		if (size >= capacity) {
			Resize();
		}

		elements[size++] = elem;
		return true;
	}
	return false;
}

template<typename T>
bool Set<T>::Remove(T elem)
{
	int index = getElementIndex(elem);
	if (index != -1) {
		RemoveAt(index);

		size--;
		return true;
	}
	else return false;
}

template<typename T>
bool Set<T>::RemoveAt(int index)
{
	if (index >= 0 && index < size) {

		for (size_t i = index; i < size - 1; i++)
		{
			elements[i] = elements[i + 1];
		}

		size--;
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
bool Set<T>::Contains(T elem) const {

	for (int i = 0; i < size; i++) {
		if (elements[i] == elem)
			return true;
	}
	return false;
}

template<typename T>
bool Set<T>::isEmpty() const
{
	return (size == 0);
}

template<typename T>
void Set<T>::Print() {

	for (int i = 0; i < getSize(); i++)
		std::cout << elements[i] << " ";
	std::cout << std::endl;
}

template<typename T>
void Set<T>::DeleteSet()
{
	size = 0;
}

template<typename T>
bool Set<T>::ContainsAny(Set<T> other)
{
	for (size_t i = 0; i < other.size(); i++)
	{
		if ((*this).Contains(other[i])) {
			return true;
		}
	}
	return false;
}



template<typename T>
bool operator==(const Set<T>& lhs, const Set<T>& rhs)
{
	return lhs.Equals(rhs);
}

template<typename T>
Set<T> Union(const Set<T>& set1, const Set<T>& set2) {

	Set<T> new_set;

	for (int i = 0; i < set1.getSize(); i++)
		new_set.Add(set1.getElement(i));

	for (int i = 0; i < set2.getSize(); i++)
		new_set.Add(set2.getElement(i));

	return new_set;
}

template<typename T>
Set<T> Union(Set<T>& set1, Set<T>& set2) {

	Set<T> new_set;

	for (int i = 0; i < set1.getSize(); i++)
		new_set.Add(set1.getElement(i));

	for (int i = 0; i < set2.getSize(); i++)
		new_set.Add(set2.getElement(i));

	return new_set;
}

template<typename T>
Set<T> Intersection(const Set<T>& set1, const Set<T>& set2) {

	Set<T> new_set;

	for (int i = 0; i < set1.getSize(); i++) {
		for (int j = 0; j < set2.getSize(); j++) {
			if (set1.getElement(i) == set2.getElement(j))
				new_set.Add(set1.getElement(i));
		}
	}
	return new_set;
}

template<typename T>
Set<T> SetDifference(const Set<T>& set1, const Set<T>& set2) {

	Set<T> new_set;
	bool isIn = false;

	for (int i = 0; i < set1.getSize(); i++) {
		for (int j = 0; j < set2.getSize(); j++) {
			if (set1.getElement(i) == set2.getElement(j))
				isIn = true;
		}

		if (!isIn)
			new_set.Add(set1.getElement(i));

		isIn = false;
	}
	return new_set;
}

template<typename T>
bool Set<T>::Equals(const Set<T>& other) {

	if (getSize() != other.getSize())
		return  false;
	for (int i = 0; i < other.getSize(); ++i)
	{
		if (!Contains(other.getElement(i)))
			return false;
	}
	return true;
}

template<typename T>
bool Set<T>::operator==(const Set<T>& other) const
{
	if (getSize() != other.getSize())
		return  false;
	for (int i = 0; i < other.getSize(); ++i)
	{
		if (!Contains(other.getElement(i)))
			return false;
	}
	return true;
}

template<typename T>
bool Set<T>::operator==(Set<T>& other) const
{
	if (getSize() != other.getSize())
		return  false;
	for (int i = 0; i < other.getSize(); ++i)
	{
		if (!Contains(other.getElement(i)))
			return false;
	}
	return true;
}


