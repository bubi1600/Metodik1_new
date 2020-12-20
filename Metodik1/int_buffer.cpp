#include "int_buffer.h"
#include <utility>  //move
#include <algorithm>
#include <iostream>

int_buffer::int_buffer(size_t size)     //konstruktor
    : _size(size), _ptr(new int[size])
{}; //array container skapas i heap minnet, new returnerar en pekare till minnet där array har allokerats.

int_buffer::int_buffer(const int* source, size_t size) //copy konstruktor, till specifik size 
    :int_buffer(size) //återanvänder kod int buffer
{
    std::copy(source, source + size, _ptr);
}; 

int_buffer::int_buffer(const int_buffer& rhs)   //Copy konstruktor
    :int_buffer(rhs.begin(), rhs.size())
{}; //deep copy

int_buffer::int_buffer(int_buffer&& rhs)    //Move konstruktor
    :_ptr(rhs._ptr), _size(rhs._size)
{
    rhs._ptr = nullptr; //Förhindra att destruktorn frigör samma minne flera gånger
    rhs._size = 0;
};

int_buffer& int_buffer::operator=(const int_buffer& rhs)   //Copy assign
{
    int_buffer tmp(rhs);

    swap(tmp); //deep copy

    return *this;
};

int_buffer& int_buffer::operator=(int_buffer&& rhs) //Move assign
{
    swap(rhs);

    return *this;
};

int& int_buffer::operator [](size_t index)
{
    return (_ptr[index]);
}

const int& int_buffer::operator [](size_t index) const
{
    return (_ptr[index]);
}

size_t int_buffer::size() const
{
    return _size;
};

int_buffer::~int_buffer()//destructor
{
    delete[] _ptr;
}; //deallokerar array från heap minnet.

int* int_buffer::begin()
{
    return _ptr;
};

int* int_buffer::end()
{
    return _ptr + _size;
};

const int* int_buffer::begin() const
{
    return _ptr;
};

const int* int_buffer::end() const
{
    return _ptr + _size;
};

void int_buffer::swap(int_buffer& swap_with)
{
    std::swap(_size, swap_with._size);
    std::swap(_ptr, swap_with._ptr);
};