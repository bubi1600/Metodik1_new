#pragma once
#include <cstddef>  //size_t

class int_buffer
{
public:
    explicit int_buffer(size_t size);   //konstruktor
    int_buffer(const int* source, size_t size);    //copy konstruktor, till specifik size 
    int_buffer(const int_buffer& rhs); //copy konstruktor
    int_buffer(int_buffer&& rhs); //move konstruktor
    int_buffer& operator=(const int_buffer& rhs); //copy assignment
    int_buffer& operator=(int_buffer&& rhs);   //move assignment
    int& operator [](size_t index);
    const int& operator [](size_t index) const;
    size_t size() const;    //Returnerar antal element
    int* begin();   //Returnerar adressen till första elementet
    int* end();     //Returnerar adressen till sista elementet
    const int* begin() const;   //Samma som föregående, men för konstanta object
    const int* end() const;
    ~int_buffer();
private:
    int* _ptr = nullptr;
    size_t _size = 0;

    void swap(int_buffer& swap_with);   //Swaps two buffers
};