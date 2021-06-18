#ifndef VECTORSTACK_H_INCLUDED
#define VECTORSTACK_H_INCLUDED

#include "MyVector.h"
#include "../StackImplementation.h"

template <typename T>
class VectorStack : public StackImplementation<T> {
public:
    VectorStack();
    VectorStack(const VectorStack& copy);
    VectorStack& operator=(const VectorStack& copy);

    VectorStack(VectorStack&& other) noexcept;
    VectorStack& operator=(VectorStack&& other) noexcept;

    void push(const T& value) override;
    void pop() override;
    T& top() override;
    const T& top() const override;

    bool isEmpty() const;
    size_t size() const;

    ~VectorStack();
private:
    MyVector<T>* _vector = nullptr;
};

#include "VectorStack.inl"

#endif // VECTORSTACK_H_INCLUDED
