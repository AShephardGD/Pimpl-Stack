#include "VectorStack.h"
#include "MyVector.h"

#include "stdexcept"
#include "algorithm"

template <typename T>
VectorStack<T>::VectorStack() {
    _vector = new MyVector<T>();
}

template <typename T>
VectorStack<T>::VectorStack(const VectorStack& copy) {
    _vector = new MyVector<T>(copy);
}

template <typename T>
VectorStack<T>& VectorStack<T>::operator=(const VectorStack& copy) {
    delete _vector;
    _vector = new MyVector<T>(copy);
    return *this;
}

template <typename T>
VectorStack<T>::VectorStack(VectorStack&& other) noexcept {
    std::swap(_vector, other._vector);
    other._vector = nullptr;
}

template <typename T>
VectorStack<T>& VectorStack<T>::operator=(VectorStack&& other) noexcept {
    std::swap(_vector, other._vector);
    delete other._vector;
    other._vector = nullptr;
    return *this;
}

template <typename T>
void VectorStack<T>::push(const T& value) {
    _vector->pushBack(value);
}

template <typename T>
void VectorStack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Called pop() - Stack is empty.");
    }
    _vector->popBack();
}

template <typename T>
T& VectorStack<T>::top() {
    if (isEmpty()) {
        throw std::out_of_range("Called top() - Stack is empty.");
    }
    return (*_vector)[_vector->size() - 1];
}

template <typename T>
const T& VectorStack<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Called top() - Stack is empty.");
    }
    return (*_vector)[_vector->size() - 1];
}

template <typename T>
bool VectorStack<T>::isEmpty() const {
    return !_vector->size();
}

template <typename T>
size_t VectorStack<T>::size() const {
    return _vector->size();
}

template <typename T>
VectorStack<T>::~VectorStack() {
    delete _vector;
}
