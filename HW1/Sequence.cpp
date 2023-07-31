
//  Sequence.cpp
//  Sequence
//
//  Created by Esmail Mozaffari on 4/14/23.
//
#include "Sequence.h"
#include <iostream>

Sequence::Sequence() : m_sequence {}
{
    m_size = 0;
}

bool Sequence::empty() const
{
    return (m_size == 0);
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    // Make sure size isnt 160
    if (pos < 0 || pos > m_size || m_size == DEFAULT_MAX_ITEMS)
        return -1;
    
    else {
        // Add element to end of array
        if (pos == m_size) {
            m_sequence[pos] = value;
            m_size++;
        }
        else {
            // Shift over last element array 1, then shift over second to last to last
            // Stop after the last item shifted was the item at the position
            int i = m_size;
            while ( i > pos) {
                m_sequence[i] = m_sequence[i-1];
                i--;
            }
            m_sequence[pos] = value;
            m_size++;
        }
    }
    
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    // position
    int p = 0;
    // array is already full
    if (m_size == DEFAULT_MAX_ITEMS) {
        return -1;
    }
    else {
        // Find p such that the value at p is <= m_sequence at p
        while (value > m_sequence[p] && p < m_size) {
            p++;
        }
        insert(p, value);
    }
    
    return p;
}

bool Sequence::erase(int pos)

{
    if (pos < 0 || pos >= m_size)
        return false;
    
    else {
        int i = pos;
        while (i < m_size-1) {
            m_sequence[i] = m_sequence[i+1];
            i++;
        }
        m_size--;
    }
    
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int items_removed = 0;
    
    for (int i = 0; i < m_size; i++) {
        if (m_sequence[i] == value) {
            erase(i);
            i--;
            items_removed++;
        }
        
    }
    return items_removed;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_size)
        return false;
    else {
        value = m_sequence[pos];
        return true;
    }
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_size)
        return false;
    else {
        m_sequence[pos] = value;
        return true;
    }
}

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    for (int i = 0; i < m_size; i++) {
        if (m_sequence[i] == value) {
            p = i;
            return p;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)
{
    int max_Size = 0;
    if (m_size > other.m_size)
        max_Size = m_size;
    else
        max_Size = other.m_size;

    for (int i = 0; i < max_Size; i++)
    {
        ItemType temp = m_sequence[i];
        m_sequence[i] = other.m_sequence[i];
        other.m_sequence[i] = temp;
    }

    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;

}

void Sequence::dump() const
{
    for (int i = 0; i < m_size; i++)
        std::cerr << m_sequence[i] << std::endl;
    
    std::cerr << "The sequence size is " << m_size << std::endl;
}

