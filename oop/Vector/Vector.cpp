#include "Vector.h"

template<class T>
Vector<T>::Vector() :m_nSize(0), m_nCapacity(1){
	m_pElements = new T[0];
}

template <class T>
Vector<T>::Vector(int size) : m_nSize(0), m_nCapacity(size) {
	m_pElements = new T[size];
}

template<class T>
Vector<T>::Vector(const Vector& r) {
	m_nSize = r.m_nSize;
	m_nCapacity = r.m_nCapacity;
	m_pElements = new T[m_nSize+m_nCapacity];
	for (int i = 0; i < m_nSize; i++) m_pElements[i] = r[i];
}

template <class T>
Vector<T>::~Vector() {
	delete[] m_pElements;
}

template <class T>
T& Vector<T>::operator[](int index) {
	T& temp = this->m_pElements[index];
	return temp;
}

template <class T>
T& Vector<T>::at(int index) {
	if (index < 0 || index >= m_nSize){
		throw "Index Out of the Bounds";
	}
	T& temp = m_pElements[index];
	return temp;
}

template <class T>
int Vector<T>::size() const{
	return m_nSize;
}

template <class T>
void Vector<T>::push_back(const T& x) {
	if (m_nCapacity == m_nSize)
		inflate();
	m_pElements[m_nSize] = x;
	m_nSize++;
}

template <class T>
void Vector<T>::clear() {
	delete[] m_pElements;
	m_nSize = 0;
	m_nCapacity = 0;
	m_pElements = new T[0];
}

template <class T>
bool Vector<T>::empty() const{
	if (m_nCapacity == 0)return true;
	else return false;
}

template <class T>
void Vector<T>::inflate() {
	m_nCapacity= 2 * (m_nCapacity+1);
	T* ptr = new T[m_nSize];
	for (int i = 0; i < m_nSize; i++) ptr[i] = m_pElements[i];
	delete[]m_pElements;
	m_pElements = ptr;
}