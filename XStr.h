#pragma once
#include <iostream>

inline unsigned __int64 strLen(const char* str) {
    unsigned __int64 length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}

inline char* strCpy(char* buffer, const char* srcStr) {
    unsigned __int64 i = 0;
    for (; srcStr[i] != '\0'; ++i) {
        buffer[i] = srcStr[i];
    }
    buffer[i] = '\0';
    return buffer;
}

template<typename T>
class XStr {
private:
    char* _data;
    T _length;
public:
    XStr() : _data(nullptr), _length(0) {}
    XStr(const char *pStr) : _length(static_cast<T>(strLen(pStr))) {
        _data = new char[_length + 1];
        strCpy(_data, pStr);
    }
    XStr(const XStr &other) : _length(other._length) {
        _data = new char[_length + 1];
        strCpy(_data, other._data);
    }
    XStr(XStr &&other) noexcept : _data(other._data), _length(other._length) {
        other._data = nullptr;
        other._length = 0;
    }
    ~XStr() {
        for (T i = 0; i < _length; ++i) { _data[i] = 0x90; }
        delete[] _data;
        _data = nullptr;
    }

    // Operator overloads
    char operator[](T index) {
        return (index < _length) ? _data[index] : '\0';
    }

    friend std::ostream& operator<<(std::ostream& os, const XStr& other) {
        os << other._data;
        return os;
    }

    // Properties
    T length() const { return _length; }
    const char* c_str() const { return _data; }

    // Methods
    void fragment() {
        for (T i = 0; i < _length; ++i) {
            T idx = rand() % _length;
            _data[idx] = 'A' + rand() % 26;
        }
    }

    void charSwap(char chr) {
        for (T i = 0; i < _length; ++i) {
            _data[i] = chr;
        }
    }
};
