#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <algorithm>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

template <typename T>
class MyVector
{
public:
    // реализовать итераторы
    class VectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        VectorIterator(T* ptr, size_t index);

        T& operator*();
        T* operator->();
        VectorIterator& operator++();
        VectorIterator operator++(int notUsed);
        bool operator!=(const VectorIterator& other);
        bool operator==(const VectorIterator& other);
        std::ptrdiff_t operator-(const VectorIterator& other);

        size_t getIndex() const;
    private:
        T* _ptr;
        size_t _index;
    };
    class ConstVectorIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T;
        using pointer           = const T*;
        using reference         = const T&;

        ConstVectorIterator(const T* ptr);

        const T& operator*();
        const T* operator->();
        ConstVectorIterator& operator++();
        ConstVectorIterator operator++(int notUsed);
        bool operator!=(const ConstVectorIterator& other);
        bool operator==(const ConstVectorIterator& other);
        std::ptrdiff_t operator-(const ConstVectorIterator& other);
    private:
        const T* _ptr;
    };

    // заполнить вектор значениями ValueType()
    MyVector(size_t size = 0,
             ResizeStrategy strategy = ResizeStrategy::Multiplicative,
             float coef = 1.5f);
    // заполнить вектор значениями value
    MyVector(size_t size,
             const T& value,
             ResizeStrategy strategy = ResizeStrategy::Multiplicative,
             float coef = 1.5f);

    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);

    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    size_t capacity() const;
    size_t size() const;
    float loadFactor() const;

    VectorIterator begin();
    ConstVectorIterator begin() const;
    VectorIterator end();
    ConstVectorIterator end() const;

    // доступ к элементу,
    // должен работать за O(1)
    T& operator[](const size_t i);
    const T& operator[](const size_t i) const;

    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const T& value);
    // вставить,
    // должен работать за O(n)
    void insert(size_t i, const T& value);     // версия для одного значения
    void insert(size_t i, const MyVector& value);      // версия для вектора
    void insert(VectorIterator it, const T& value);  // версия для одного значения
    void insert(VectorIterator it, const MyVector& value);   // версия для вектора

    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack();
    // удалить
    // должен работать за O(n)
    void erase(const size_t i);
    void erase(const size_t i, size_t len);            // удалить len элементов начиная с i

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    VectorIterator find(const T& value, bool isBegin = true);
    ConstVectorIterator find(const T& value, bool isBegin = true) const;

    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);

    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются value
    // если меньше - обрезаем вектор
    void resize(const size_t size, const T& value = T());

    // очистка вектора, без изменения capacity
    void clear();

    void print(std::ostream& stream = std::cout) const;
    template <typename Type>
    friend std::ostream& operator<<(std::ostream& stream, const MyVector<Type>& myVector);
private:
    void resizeVector(size_t size);
    T* _data;
    size_t _size;
    size_t _capacity;
    float _resizeCoef;
    ResizeStrategy _strategy;
};

template<typename T>
MyVector<T>::VectorIterator::VectorIterator(T* ptr, size_t index) : _ptr(ptr), _index(index) {}

template <typename T>
T& MyVector<T>::VectorIterator::operator*() {
    return *(_ptr);
}

template <typename T>
T* MyVector<T>::VectorIterator::operator->() {
    return _ptr;
}

template <typename T>
typename MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator++() {
    ++_ptr;
    ++_index;
    return *(this);
}

template <typename T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator++(int notUsed) {
    VectorIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool MyVector<T>::VectorIterator::operator!=(const MyVector<T>::VectorIterator& other) {
    return _ptr != other._ptr;
}

template <typename T>
bool MyVector<T>::VectorIterator::operator==(const MyVector<T>::VectorIterator& other) {
    return _ptr == other._ptr;
}

template <typename T>
std::ptrdiff_t MyVector<T>::VectorIterator::operator-(const MyVector<T>::VectorIterator& other) {
    return _ptr - other._ptr;
}

template <typename T>
size_t MyVector<T>::VectorIterator::getIndex() const {
    return _index;
}



template <typename T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(const T* ptr) : _ptr(ptr) {}

template <typename T>
const T& MyVector<T>::ConstVectorIterator::operator*() {
    return *(_ptr);
}

template <typename T>
const T* MyVector<T>::ConstVectorIterator::operator->() {
    return _ptr;
}

template <typename T>
typename MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator++() {
    ++_ptr;
    return *(this);
}

template <typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator++(int notUsed) {
    ConstVectorIterator temp = *(this);
    ++(*this);
    return temp;
}

template <typename T>
bool MyVector<T>::ConstVectorIterator::operator!=(const MyVector<T>::ConstVectorIterator& other) {
    return _ptr != other._ptr;
}

template <typename T>
bool MyVector<T>::ConstVectorIterator::operator==(const MyVector<T>::ConstVectorIterator& other) {
    return _ptr == other._ptr;
}

template <typename T>
std::ptrdiff_t MyVector<T>::ConstVectorIterator::operator-(const MyVector<T>::ConstVectorIterator& other) {
    return _ptr - other._ptr;
}



template <typename T>
MyVector<T>::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    if (_size) {
        _data = new T[size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = T();
        }
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = coef;
    _strategy = strategy;
}

template <typename T>
MyVector<T>::MyVector(size_t size, const T& value, ResizeStrategy strategy, float coef) {
    _size = size;
    _capacity = size;
    if (_size) {
        _data = new T[size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = value;
        }
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = coef;
    _strategy = strategy;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& copy) {
    _size = copy.size();
    _capacity = copy.size();
    if (size()) {
        _data = new T[size()];
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = copy[i];
        }
    }
    else {
        _data = nullptr;
    }
    _resizeCoef = copy._resizeCoef;
    _strategy = copy._strategy;
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept {
    _data = nullptr;
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    std::swap(_capacity, other._capacity);
    std::swap(_resizeCoef, other._resizeCoef);
    std::swap(_strategy, other._strategy);
}



template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    _size = other.size();
    delete[] _data;
    resizeVector(size());
    if (size()) {
        for (size_t i = 0; i < size(); ++i) {
            _data[i] = other[i];
        }
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    std::swap(_capacity, other._capacity);
    std::swap(_resizeCoef, other._resizeCoef);
    std::swap(_strategy, other._strategy);
    delete[] other._data;
    other._size = 0;
    other._capacity = 0;
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}



template <typename T>
size_t MyVector<T>::capacity() const {
    return _capacity;
}

template <typename T>
size_t MyVector<T>::size() const{
    return _size;
}

template <typename T>
float MyVector<T>::loadFactor() const {
    if (capacity()) {
        return ((float) size()) / ((float) capacity());
    }
    else {
        return 1;
    }
}



template <typename T>
typename MyVector<T>::VectorIterator MyVector<T>::begin() {
    if (size()) {
        return MyVector::VectorIterator(_data, 0);
    }
    else {
        return MyVector::VectorIterator(nullptr, 0);
    }
}

template <typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::begin() const {
    if (size()) {
        return MyVector::ConstVectorIterator(_data);
    }
    else {
        return MyVector::ConstVectorIterator(nullptr);
    }
}

template <typename T>
typename MyVector<T>::VectorIterator MyVector<T>::end() {
    if (size()) {
        return MyVector::VectorIterator(_data + size(), size());
    }
    else {
        return MyVector::VectorIterator(nullptr, 0);
    }
}

template <typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::end() const {
    if (size()) {
        return MyVector::ConstVectorIterator(_data + size());
    }
    else {
        return MyVector::ConstVectorIterator(nullptr);
    }
}



template <typename T>
T& MyVector<T>::operator[](const size_t i) {
    if (i >= size()) {
        throw std::out_of_range("Called [] - Out of MyVector's range");
    }
    return _data[i];
}

template <typename T>
const T& MyVector<T>::operator[](const size_t i) const {
    if (i >= size()) {
        throw std::out_of_range("Called [] - Out of MyVector's range");
    }
    return _data[i];
}



template <typename T>
void MyVector<T>::pushBack(const T& value) {
    insert(size(), value);
}

template <typename T>
void MyVector<T>::insert(size_t i, const T& value) {
    if (i > size()) {
        i = size();
    }
    size_t newSize = size() + 1;
    resizeVector(newSize);
    for (size_t idx = size(); idx > i; --idx) {
        _data[idx] = _data[idx - 1];
    }
    _data[i] = value;
    _size = newSize;
}

template <typename T>
void MyVector<T>::insert(size_t i, const MyVector& value) {
    if (i > size()) {
        i = size();
    }
    size_t newSize = size() + value.size(), forEnd = i + value.size() - 1;
    resizeVector(newSize);
    for (size_t idx = newSize - 1; idx > forEnd; --idx) {
        _data[idx] = _data[idx - value.size()];
    }
    for (size_t idx = i; idx <= forEnd; ++idx) {
        _data[idx] = value[idx - i];
    }
    _size = newSize;
}

template <typename T>
void MyVector<T>::insert(MyVector::VectorIterator it, const T& value) {
    insert(it.getIndex(), value);
}

template <typename T>
void MyVector<T>::insert(MyVector::VectorIterator it, const MyVector& value) {
    insert(it.getIndex(), value);
}



template <typename T>
void MyVector<T>::popBack() {
    --_size;
}

template <typename T>
void MyVector<T>::erase(const size_t i) {
    erase(i, 1);
}

template <typename T>
void MyVector<T>::erase(const size_t i,  size_t len) {
    if (i >= size()) {
        throw std::out_of_range("Called erase() - Out of MyString's range");
    }
    if (i + len > size()) {
        len = size() - i;
    }
    _size = size() - len;
    for (size_t index = i; index < _size; ++index) {
        _data[index] = _data[index + len];
    }
}



template <typename T>
typename MyVector<T>::VectorIterator MyVector<T>::find(const T& value, bool isBegin) {
    VectorIterator it(_data, 0);
    if (isBegin) {
        for (; it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return it;
    }
    else {
        VectorIterator res(_data, 0);
        for (; it != end(); ++it) {
            if (*it == value) {
                res = it;
            }
        }
        if ((it == end()) && (*res != value)) {
            return it;
        }
        return res;
    }
}

template <typename T>
typename MyVector<T>::ConstVectorIterator MyVector<T>::find(const T& value, bool isBegin) const {
    ConstVectorIterator it(_data);
    if (isBegin) {
        for (; it != end(); ++it) {
            if (*it == value) {
                return it;
            }
        }
        return it;
    }
    else {
        ConstVectorIterator res(_data);
        for (; it != end(); ++it) {
            if (*it == value) {
                res = it;
            }
        }
        if ((it == end()) && (*res != value)) {
            return it;
        }
        return res;
    }
}



template <typename T>
void MyVector<T>::reserve(const size_t capacity) {
    if (!capacity) {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = capacity;
        return;
    }
    T* newData = new T[capacity];
    _capacity = capacity;
    if (capacity < size()) {
        for (size_t i = 0; i < capacity; ++i) {
            newData[i] = _data[i];
        }
        _size = capacity;
    }
    else {
        for (size_t i = 0; i < size(); ++i) {
            newData[i] = _data[i];
        }
    }
    delete[] _data;
    _data = newData;
}

template <typename T>
void MyVector<T>::resize(const size_t size, const T& value) {
    if (size > _size) {
        resizeVector(size);
        for (size_t i = _size; i < size; ++i) {
            _data[i] = value;
        }
    }
    _size = size;
}

template <typename T>
void MyVector<T>::clear() {
    _size = 0;
}



template <typename T>
void MyVector<T>::print(std::ostream& stream) const {
    ConstVectorIterator it(_data);
    stream << "[";
    if (size()) {
        stream << *it;
        ++it;
        for (; it != end(); ++it) {
            stream << ", " << *it;
        }
    }
    stream << "]";
}



template <typename T>
std::ostream& operator<<(std::ostream& stream, const MyVector<T>& myVector) {
    myVector.print(stream);
    return stream;
}



template <typename T>
void MyVector<T>::resizeVector(size_t size) {
    if (size >= capacity()) {
        switch (_strategy) {
            case ResizeStrategy::Additive:
                _capacity += _resizeCoef;
                break;
            case ResizeStrategy::Multiplicative:
                if (_capacity <= 1) {
                    _capacity += 5 * _resizeCoef;
                    break;
                }
                _capacity *= _resizeCoef;
                break;
        }
        T* newData = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
        resizeVector(size);
    }
}


#endif // MYVECTOR_H_INCLUDED
