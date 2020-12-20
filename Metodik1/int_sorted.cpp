#include"int_sorted.h"
#include <iostream>
#include <utility>
#include <stdio.h>
#include <algorithm>

int_sorted::int_sorted(const int* source, size_t size)
    :_buffer(source, size)
{
    if (size <= 1)   return; //Om storleken �r 0 eller 1 beh�ver den inte sorteras

    //Sortera source och l�gg �ver den sorterade int_sorted i en tempor�r instans
    int_sorted temp = sort(source, source + size);

    _buffer = std::move(temp._buffer);  //Flytta den tempor�ra till denna
}

size_t int_sorted::size() const
{
    return _buffer.size();  //Ta storleken f�r buffern
}

int* int_sorted::insert(int value)
{
    int_buffer temp_buffer(_buffer.size() + 1);   //Skapa en tempor�r buffer att bygga upp den nya buffern i

    int* insertpoint = temp_buffer.begin(); //S�tter insertpunkten till den f�rsta adressen

    for (const int* i = _buffer.begin(); i != _buffer.end(); i++)    //G�r igenom hela buffern
    {
        if (value < *i) break;   //N�r den hittar platsen f�r det nya v�rdet, avbryt loopningen

        insertpoint++;  //Flytta insertpunkten fram�t i listan
    }

    *insertpoint = value;   //S�tt in det nya v�rdet d�r det ska vara

    const int* prev_iter = _buffer.begin();
    int* new_iter = temp_buffer.begin();


    //Loopa igenom b�da buffrarna och kopiera �ver alla element fr�n den gamla buffern till temp_buffer
    for (; prev_iter != _buffer.end(); ++prev_iter, ++new_iter)
    {
        if (new_iter == insertpoint) ++new_iter; //N�r den n�r det insertade elementet, hoppa �ver detta

        *new_iter = *prev_iter; //L�gg �ver v�rdet
    }

    _buffer = std::move(temp_buffer);   //Byt ut buffern till den nyskapade 

    return insertpoint; //Returnera insertpunkten
}

const int* int_sorted::begin() const
{
    return _buffer.begin();
}

const int* int_sorted::end() const
{
    return _buffer.end();
}

int_sorted int_sorted::merge(const int_sorted& merge_with) const
{
    int_buffer merged(size() + merge_with.size());

    const int* iter1 = begin();
    const int* iter2 = merge_with.begin();
    int* merged_iter = merged.begin();

    for (; iter1 != end() && iter2 != merge_with.end(); merged_iter++)
    {
        if (*iter1 < *iter2)
        {
            *merged_iter = *iter1;
            iter1++;
        }
        else
        {
            *merged_iter = *iter2;
            iter2++;
        }
    }

    //Om det finns n�tt kvar i n�gon av buffrarna, skriv dessa till den nya
    for (; iter1 != end(); iter1++, merged_iter++)
        *merged_iter = *iter1;

    for (; iter2 != merge_with.end(); iter2++, merged_iter++)
        *merged_iter = *iter2;

    int_sorted ret(nullptr, 0);

    ret._buffer = std::move(merged);

    return ret;
}

int_sorted int_sorted::sort(const int* begin, const int* end)
{
    if (begin == end)   return int_sorted(nullptr, 0);

    if (begin == end - 1)   return int_sorted(begin, 1); //martin pratar om den

    ptrdiff_t half = (end - begin) / 2; // pointer diff type

    const int* mid = begin + half;

    return sort(begin, mid).merge(sort(mid, end));
}