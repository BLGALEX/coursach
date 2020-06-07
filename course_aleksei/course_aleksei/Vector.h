#pragma once


template <typename T>
class Vector {
public:
    Vector() noexcept : _size(0),
                        _capacity(0),
                        _ptr(nullptr) {};

    explicit Vector(size_t size) noexcept : _size(size),
                                            _capacity(size),
                                            _ptr(size == 0 ? nullptr : new int[size]) {};

    ~Vector() noexcept {
        delete[] _ptr;
    }

    Vector(const Vector<T>& v) noexcept : _size(v._size),
                                          _capacity(v._capacity),
                                          _ptr(new T[_capacity]) {
        T* in = v._ptr;
        T* out = _ptr;
        for (int i = 0; i < v._size; ++i) {
            *(out++) = *(in++);
        }
    }

    Vector& operator = (const Vector<T>& v) noexcept {
        if (*this == &v) return *this;
        ~Vector();
        *this = std::move(Vector(v));

        return *this;
    }

    Vector(Vector<T>&& v) noexcept : _size(v._size),
                                     _capacity(v._capacity) {
        _ptr = v._ptr;
        v._size = 0;
        v._capacity = 0;
        v._ptr = nullptr;
    }

    Vector& operator = (Vector<T>&& v) noexcept {
        if (*this == &v) return *this;
        ~Vector();
        _size = v._size;
        _capacity = v._capacity;
        _ptr = v._ptr;
        v._size = 0;
        v._capacity = 0;
        v._ptr = 0;

        return *this;
    }

    void PushBack(T t) {
        if (_size == _capacity) {
            _capacity = (_capacity == 0 ? 1 : _capacity * 2);
            T* new_ptr = new T[_capacity];
            new_ptr[_size] = std::move(t);

            for (int i = 0; i < _size; ++i) {
                new_ptr[i] = std::move(_ptr[i]);
            }

            _size++;
            delete[] _ptr;
            _ptr = new_ptr;
        } else {
            _ptr[_size++] = std::move(t);
        }
    }

    void PopBack() noexcept {
        _ptr[_size--].~T();
    }

    T& operator[](size_t index) noexcept {
        return _ptr[index];
    }

    const T& operator[](size_t index) const noexcept {
        return _ptr[index];
    }

    T* Data() noexcept {
        return _ptr;
    }

    const T* Data() const noexcept {
        return _ptr;
    }

    size_t Size() const noexcept {
        return _size;
    }

    size_t Capacity() const noexcept {
        return _capacity;
    }
private:
    size_t _size;
    size_t _capacity;
    T* _ptr;
};