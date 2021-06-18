#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "StackImplementation.h"

#include <string.h>

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

#include "Stack.inl"

#endif // STACK_H_INCLUDED
