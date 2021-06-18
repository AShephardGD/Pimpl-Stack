#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <iostream>

// ��������� ��������� capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

template <typename T>
class MyVector
{
public:
    // ����������� ���������
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

    // ��������� ������ ���������� ValueType()
    MyVector(size_t size = 0,
             ResizeStrategy strategy = ResizeStrategy::Multiplicative,
             float coef = 1.5f);
    // ��������� ������ ���������� value
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

    // ������ � ��������,
    // ������ �������� �� O(1)
    T& operator[](const size_t i);
    const T& operator[](const size_t i) const;

    // �������� � �����,
    // ������ �������� �� amort(O(1))
    void pushBack(const T& value);
    // ��������,
    // ������ �������� �� O(n)
    void insert(size_t i, const T& value);     // ������ ��� ������ ��������
    void insert(size_t i, const MyVector& value);      // ������ ��� �������
    void insert(VectorIterator it, const T& value);  // ������ ��� ������ ��������
    void insert(VectorIterator it, const MyVector& value);   // ������ ��� �������

    // ������� � �����,
    // ������ �������� �� amort(O(1))
    void popBack();
    // �������
    // ������ �������� �� O(n)
    void erase(const size_t i);
    void erase(const size_t i, size_t len);            // ������� len ��������� ������� � i

    // ����� �������,
    // ������ �������� �� O(n)
    // ���� isBegin == true, ����� ������ ������� ��������, ������� value, ����� ����������
    // ���� �������� �������� ���, ������� end
    VectorIterator find(const T& value, bool isBegin = true);
    ConstVectorIterator find(const T& value, bool isBegin = true) const;

    // ��������������� ������ (������������� ������ capacity)
    void reserve(const size_t capacity);

    // �������� ������
    // ���� ����� ������ ������ ��������, �� ����� �������� ���������� value
    // ���� ������ - �������� ������
    void resize(const size_t size, const T& value = T());

    // ������� �������, ��� ��������� capacity
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

#include "MyVector.inl"

#endif // MYVECTOR_H_INCLUDED
