#ifndef STACKIMPLEMENTATION_H_INCLUDED
#define STACKIMPLEMENTATION_H_INCLUDED

#include <string.h>

template <typename T>
class StackImplementation {
public:
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
    virtual T& top() = 0;
    virtual const T& top() const = 0;

    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;

    virtual ~StackImplementation() {};
};

#endif // STACKIMPLEMENTATION_H_INCLUDED
