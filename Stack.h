#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "StackImplementation.h"
#include "Vector/VectorStack.h"
#include "List/ListStack.h"

#include <string.h>
#include <stdexcept>
#include <algorithm>

enum class StackContainer {
    Vector = 0,
    List,
    None,
};

template <typename T>
class Stack {
public:
    Stack(StackContainer container = StackContainer::Vector);
    Stack(const T* valueArray, const size_t arraySize,
          StackContainer container = StackContainer::Vector);

    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);

    Stack(Stack&& moveStack) noexcept;
    Stack& operator=(Stack&& moveStack) noexcept;

    ~Stack();

    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;

    bool isEmpty() const;
    size_t size() const;
private:
    StackImplementation<T>* _pimpl = nullptr;
    StackContainer _containerType = StackContainer::None;
};

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
            _pimpl = new VectorStack<T>(*dynamic_cast<VectorStack<T>*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            _pimpl = new ListStack<T>(*dynamic_cast<ListStack<T>*>(copyStack._pimpl));
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

#endif // STACK_H_INCLUDED
