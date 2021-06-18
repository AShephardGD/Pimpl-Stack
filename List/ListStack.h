#ifndef LISTSTACK_H_INCLUDED
#define LISTSTACK_H_INCLUDED

#include "../StackImplementation.h"
#include "SingleLinkedList.h"

template <typename T>
class ListStack : public StackImplementation<T> {
public:
    ListStack();
    ListStack(const ListStack& copy);
    ListStack& operator=(const ListStack& copy);

    ListStack(ListStack&& other) noexcept;
    ListStack& operator=(ListStack&& other) noexcept;

    void push(const T& value) override;
    void pop() override;
    T& top() override;
    const T& top() const override;

    bool isEmpty() const;
    size_t size() const;

    ~ListStack();
private:
    SingleLinkedList<T>* _list = nullptr;
};

#include "ListStack.inl"

#endif // LISTSTACK_H_INCLUDED
