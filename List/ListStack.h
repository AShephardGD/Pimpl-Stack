#ifndef LISTSTACK_H_INCLUDED
#define LISTSTACK_H_INCLUDED

#include "../StackImplementation.h"
#include "SingleLinkedList.h"

#include <stdexcept>
#include <algorithm>

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

template <typename T>
ListStack<T>::ListStack() {
    _list = new SingleLinkedList<T>();
}

template <typename T>
ListStack<T>::ListStack(const ListStack& copy) {
    _list = new SingleLinkedList<T>(*(copy._list));
}

template <typename T>
ListStack<T>& ListStack<T>::operator=(const ListStack& copy) {
    delete _list;
    _list = new SingleLinkedList<T>(*(copy._list));
    return *this;
}

template <typename T>
ListStack<T>::ListStack(ListStack&& other) noexcept {
    std::swap(_list, other._list);
    other._list = nullptr;
}

template <typename T>
ListStack<T>& ListStack<T>::operator=(ListStack&& other) noexcept {
    std::swap(_list, other._list);
    delete other._list;
    other._list = nullptr;
    return *this;
}

template <typename T>
void ListStack<T>::push(const T& value) {
    _list->pushBack(value);
}

template <typename T>
void ListStack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Called pop() - Stack is empty.");
    }
    _list->popBack();
}

template <typename T>
T& ListStack<T>::top() {
    if (isEmpty()) {
        throw std::out_of_range("Called top() - Stack is empty.");
    }
    return (*_list)[_list->size() - 1];
}

template <typename T>
const T& ListStack<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Called top() - Stack is empty.");
    }
    return (*_list)[_list->size() - 1];
}

template <typename T>
bool ListStack<T>::isEmpty() const {
    return !_list->size();
}

template <typename T>
size_t ListStack<T>::size() const {
    return _list->size();
}

template <typename T>
ListStack<T>::~ListStack() {
    delete _list;
}


#endif // LISTSTACK_H_INCLUDED
