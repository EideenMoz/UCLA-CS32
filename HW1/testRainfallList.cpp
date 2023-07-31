//
//  main.cpp
//  RainfallList
//
//  Created by Esmail Mozaffari on 4/15/23.
//

#include <iostream>
#include "RainfallList.h"
#include <cassert>

int main(){
    RainfallList r;
    r.add(1);
    r.add(2);
    r.add(-1);
    r.add(400);
    for (int i = 0; i < 161; i++)
        r.add(10);
    assert (r.maximum() == 400);
    assert (r.minimum() == 1);
    assert (r.size() == 160);
    assert (r.remove(2) == true);
    assert (r.size() == 159);
    
    RainfallList r2;
    assert (r2.add(-1) == false);
    assert (r2.add(401) == false);
    assert (r2.size() == 0);
    assert (r2.remove(10) == false);
    assert (r2.maximum() == std::numeric_limits<unsigned long>::max());
    assert (r2.minimum() == std::numeric_limits<unsigned long>::max());
    
    RainfallList r3;
    assert (r3.add(10) == true);
    assert (r3.maximum() == 10);
    assert (r3.minimum() == 10);
    assert (r3.remove(10) == true);
    assert (r3.size() == 0);
    assert (r3.remove(10) == false);
    
    
    std::cerr << "All test cases passed" << std::endl;
    
}
