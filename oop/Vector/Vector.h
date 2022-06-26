#ifndef VECTOR_H
#define VECTOR_H

#include<exception>

template <class T>
class Vector {
public:
    Vector();                      // creates an empty vector
    Vector(int size);              // creates a vector for holding 'size' elements
    Vector(const Vector& r);       // the copy ctor
    ~Vector();                     // destructs the vector 
    T& operator[](int index);      // accesses the specified element without bounds checking
    T& at(int index);              // accesses the specified element, throws an exception of
                                   // type 'std::out_of_range' when index <0 or >=m_nSize
    int size() const;              // return the size of the container
	int capa() const;			   // return the capability of the container
    void push_back(const T& x);    // adds an element to the end 
    void clear();                  // clears the contents
    bool empty() const;            // checks whether the container is empty 
private:
    void inflate();                // expand the storage of the container to a new capacity,
                                   // e.g. 2*m_nCapacity
    T* m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the number of elements that can be held in currently
                                   // allocated storage
};

template<class T>
Vector<T>::Vector() :m_nSize(0), m_nCapacity(5) {
	m_pElements = new T[5];//initialize the vector with capability of 5
}

template <class T>
Vector<T>::Vector(int size) : m_nSize(0), m_nCapacity(size) {
	m_pElements = new T[size];//initialize the vector with capability of size
}

template <class T>
T& Vector<T>::operator[](int index) {
	T& temp = this->m_pElements[index];//override the operator "[]" with no bound check
	return temp;
}

template<class T>
Vector<T>::Vector(const Vector& r) {//create the vector from another vector
	m_nSize = r.m_nSize;
	m_nCapacity = r.m_nCapacity;
	m_pElements = new T[m_nCapacity];
	for (int i = 0; i < m_nSize; i++) this->at(i) = r.m_pElements[i];//copy the element
}

template <class T>
Vector<T>::~Vector() {
	delete[] m_pElements;//destruct the vector
}

template <class T>
T& Vector<T>::at(int index) {
	try {
		if (index < 0 || index >= m_nSize) {
			throw "std::out_of_range";//throw exception
		}
	}
	catch (const char* msg) {
		std::cout << "exception: " << msg;
	}
	return m_pElements[index];
}

template <class T>
int Vector<T>::size() const {
	return m_nSize;//return current size of the vector
}

template<class T>
int Vector<T>::capa() const {
	return m_nCapacity;//return current capability of the vector
}

template <class T>
void Vector<T>::push_back(const T& x) {
	if (m_nCapacity == m_nSize)//if the vector is full ,inflate it 
		inflate();
	m_pElements[m_nSize] = x;//push this element into the vector
	m_nSize++;
}

template <class T>
void Vector<T>::clear() {
	delete[] m_pElements;//create another vector
	m_nSize = 0;
	m_pElements = new T[m_nCapacity];
}

template <class T>
bool Vector<T>::empty() const {
	if (m_nSize == 0)return true;//check the size to decide whether it is empty
	else return false;
}

template <class T>
void Vector<T>::inflate() {
	m_nCapacity = 2 * m_nCapacity;//make the capability double
	T* ptr = new T[m_nCapacity];//create a array with double capability
	for (int i = 0; i < m_nSize; i++) ptr[i] = m_pElements[i];//copy the element from origin array
	delete[] m_pElements;//delete origin element
	m_pElements = ptr;
}
#endif
