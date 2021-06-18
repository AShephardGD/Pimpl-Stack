#include "Stack.h"
#include "Vector/VectorStack.h"
#include "List/ListStack.h"

#include <stdexcept>
#include <algorithm>

template <typename T>
Stack<T>::Stack(StackContainer container) {
    _containerType = container;
    switch(container) {
        case StackContainer::Vector:
            _pimpl = new VectorStack<T>();
            break;
        case StackContainer::List:
            _pimpl = new ListStack<T>();
            break;
        default:
            throw std::invalid_argument("Wrong stack type.");
            break;
    }
}

template <typename T>
Stack<T>::Stack(const T* valueArray, const size_t arraySize,
                StackContainer container) {
    _containerType = container;
    switch(container) {
        case StackContainer::Vector:
            _pimpl = new VectorStack<T>();
            break;
        case StackContainer::List:
            _pimpl = new ListStack<T>();
            break;
        default:
            throw std::invalid_argument("Wrong stack type.");
            break;
    }
    for (size_t i = 0; i < arraySize; ++i) {
        _pimpl->push(valueArray[i]);
    }
}

template <typename T>
Stack<T>::Stack(const Stack& copyStack) {
    _containerType = copyStack._containerType;
    switch (_containerType) {
        case StackContainer::Vector:
            _pimpl = new VectorStack<T>(copyStack._pimpl);
            break;
        case StackContainer::List:
            _pimpl = new ListStack<T>(copyStack._pimpl);
            break;
        default:
            throw std::invalid_argument("Wrong stack type.");
            break;
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& copyStack) {
    _containerType = copyStack._containerType;
    delete _pimpl;
    switch (_containerType) {
        case StackContainer::Vector:
            _pimpl = new VectorStack<T>(copyStack._pimpl);
            break;
        case StackContainer::List:
            _pimpl = new ListStack<T>(copyStack._pimpl);
            break;
        default:
            throw std::invalid_argument("Wrong stack type.");
            break;
    }
    return *this;
}

template <typename T>
Stack<T>::Stack(Stack&& moveStack) noexcept {
    std::swap(_pimpl, moveStack._pimpl);
    std::swap(_containerType, moveStack._containerType);
    moveStack._pimpl = nullptr;
    moveStack._containerType = StackContainer::None;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& moveStack) noexcept {
    std::swap(_pimpl, moveStack._pimpl);
    std::swap(_containerType, moveStack._containerType);
    delete moveStack._pimpl;
    moveStack._pimpl = nullptr;
    moveStack._containerType = StackContainer::None;
    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    delete _pimpl;
}

template <typename T>
void Stack<T>::push(const T& value) {
    _pimpl->push(value);
}

template <typename T>
void Stack<T>::pop() {
    _pimpl->pop();
}

template <typename T>
T& Stack<T>::top() {
    return _pimpl->top();
}

template <typename T>
const T& Stack<T>::top() const {
    return _pimpl->top();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return _pimpl->isEmpty();
}

template <typename T>
size_t Stack<T>::size() const {
    return _pimpl->size();
}
