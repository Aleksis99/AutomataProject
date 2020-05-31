#pragma once

template<typename T>
class Vector {
private:
	T* arr;
	int count;
	int capacity;

	void copyVec(const Vector& other);
	void deleteVec();

	void resize();

	void swap(T&, T&);
public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	T& operator[](const int);
	const T& operator[](const int)const;

	void pushBack(const T);
	bool deleteAt(const int);
	bool deleteItem(const T&);
	int findItem(const T&);
	void clear();
	int size()const;
	void sort();
	void print() const;
	T popBack();
	void reverse();

	T* getArray();

};

template<typename T>
Vector<T>::Vector() {
	capacity = 4;
	count = 0;
	arr = new(std::nothrow) T[capacity];
}
template<typename T>
void Vector<T>::copyVec(const Vector<T>& other) {
	capacity = other.capacity;
	count = other.count;
	arr = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		arr[i] = other.arr[i];
	}

}
template<typename T>
void Vector<T>::deleteVec() {
	if (arr != nullptr) {
		delete[]arr;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyVec(other);
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		deleteVec();
		copyVec(other);
	}

	return *this;
}
template<typename T>
Vector<T>::~Vector<T>() {
	deleteVec();
}
template<typename T>
T& Vector<T>::operator[](const int index) {
	if (index >= 0 && index < count) {
		return this->arr[index];
	}
	else {
		std::cerr << "Invalid index exeption";

	}
}
template<typename T>
const T& Vector<T>::operator[](const int index) const
{
	if (index >= 0 && index < count) {
		return this->arr[index];
	}
	else {
		std::cerr << "Invalid index exeption";

	}
}
template<typename T>
void Vector<T>::pushBack(const T element) {
	if (count < capacity) {
		arr[count] = element;
		count++;
	}
	else {
		resize();
		pushBack(element);
	}
}
template<typename T>
void Vector<T>::resize() {

	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < count; i++)
	{
		newArr[i] = arr[i];
	}
	deleteVec();
	arr = newArr;
}
template<typename T>
int Vector<T>::size()const {
	return this->count;
}
template<typename T>
bool Vector<T>::deleteAt(const int index) {
	if (index >= 0 && index < count) {

		for (size_t i = index; i < count - 1; i++)
		{
			arr[i] = arr[i + 1];
		}

		count--;
		return true;
	}
	else {
		return false;
	}
}
template<typename T>
bool Vector<T>::deleteItem(const T& item)
{
	int index = findItem(item);
	if (index != -1) {
		deleteAt(index);
		return true;
	}
	else return false;
}
template<typename T>
int Vector<T>::findItem(const T& item)
{
	for (size_t i = 0; i < count; i++)
	{
		if (arr[i] == item)return i;
	}
	return -1;
}
template<typename T>
inline void Vector<T>::clear()
{
	count = 0;
}
template<typename T>
void Vector<T>::sort() {
	for (size_t i = 0; i < count - 1; i++)
	{
		int min = arr[i];
		int index = i;
		for (size_t j = i + 1; j < count; j++)
		{
			if (arr[j] < min) {
				min = arr[j];
				index = j;
			}
		}
		arr[index] = arr[i];
		arr[i] = min;
	}
}
template<typename T>
void Vector<T>::print()const {
	for (size_t i = 0; i < count; i++)
	{
		std::cout << arr[i];
	}
}
template<typename T>
T Vector<T>::popBack() {
	if (count > 0) {
		T a = arr[count - 1];
		count--;
		return a;
	}
	else {
		return -1;
	}
}
template<typename T>
void Vector<T>::swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
template<typename T>
void Vector<T>::reverse() {
	for (size_t i = 0; i < count / 2; i++)
	{
		swap(arr[i], arr[count - i - 1]);
	}
}

template<typename T>
T* Vector<T>::getArray()
{
	return arr;
}

