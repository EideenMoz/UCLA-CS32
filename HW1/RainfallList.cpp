//
//  RainfallList.cpp
//  RainfallList
//
//  Created by Esmail Mozaffari on 4/15/23.
//

#include <iostream>
#include "RainfallList.h"
#include "Sequence.h"

RainfallList::RainfallList() : m_RainfallList()
{
}

bool RainfallList::add(unsigned long rainfall)
{
    if (rainfall >= 0 && rainfall <= 400 && m_RainfallList.insert(rainfall) != -1)
        return true;
    else
        return false;
}

bool RainfallList::remove(unsigned long rainfall)
{
    int index_of_rainfall = m_RainfallList.find(rainfall);
    // find returns -1 if no value in sequence
    if (index_of_rainfall != -1) {
        m_RainfallList.erase(index_of_rainfall);
        return true;
    }
    else
        return false;
}

int RainfallList::size() const
{
    return m_RainfallList.size();
}

unsigned long RainfallList::minimum() const
{
    unsigned long min = 0;
    
    if (m_RainfallList.empty())
        return NO_RAINFALLS;
    
    else {
        m_RainfallList.get(0, min);
        return min;
    }
}


unsigned long RainfallList::maximum() const
{
    unsigned long max = 0;
    
    if (m_RainfallList.empty())
        return NO_RAINFALLS;
    
    else {
        m_RainfallList.get(size()-1, max);
        return max;
    }
}




