//
//  testSequence.c
//  HW1Tests
//
//  Created by Esmail Mozaffari on 4/17/23.
//


//#define TESTNUM 7

#ifndef TESTNUM
#define TESTNUM 0
#endif

#if TESTNUM == 1

#include <iostream>
#include <cassert>
#include "Sequence.h"

int main() {
    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "e");
    s.insert(3, "b");
    s.insert(4, "c");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    std::string x;
    assert(s.get(0, x)  &&  x == "a");
    assert(s.get(1, x)  &&  x == "e");
    assert(s.get(2, x)  &&  x == "c");
    
    s.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#elif TESTNUM == 2

#include <iostream>
#include <cassert>
#include "Sequence.h"

int main() {
    
    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    
    s1.dump();
    s2.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#elif TESTNUM == 3

#include <iostream>
#include <cassert>
#include "Sequence.h"

int main() {
    Sequence s;
    s.insert(0, "dosa");
    s.insert(1, "pita");
    s.insert(2, "");
    s.insert(3, "matzo");
    assert(s.find("") == 2);
    s.remove("dosa");
    assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
           s.find("matzo") == 2);
    
    s.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#elif TESTNUM == 4

#include "Sequence.h"
#include <iostream>
#include <cassert>

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find("42") == -1);
    assert(s.insert("42") == 0);
    assert(s.size() == 1  &&  s.find("42") == 0);
    
    s.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#elif TESTNUM == 5

#include "Sequence.h"
#include <iostream>
#include <cassert>

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find("laobing") == -1);
    assert(s.insert("laobing") == 0);
    assert(s.size() == 1  &&  s.find("laobing") == 0);
    
    s.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#elif TESTNUM == 6

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    
    s.dump();
    cerr << "Passed all tests" << endl;
}

#elif TESTNUM == 7

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s1;
    Sequence s2;
    assert(s1.empty() == true);
    assert(s1.insert(1, 5) == -1);
    assert(s1.insert(s1.size(), 1) == 0);
    assert(s1.insert(s1.size(), 2) == 1);
    assert(s1.insert(s1.size(), 3) == 2);
    assert(s1.insert(3) == 2);
    assert(s1.insert(0) == 0);
    assert(s1.insert(4) == 5);
    assert(s1.erase(0) == true);
    assert(s1.erase(4) == true);
    assert(s1.erase(2) == true);
    assert(s1.remove(3) == 1);
    assert(s1.remove(1) == 1);
    assert(s1.remove(2) == 1);
    
    for (int i = 0; i < 5; i++)
        assert(s1.insert(i) == i);
    
    for (int i = 0; i < 6; i++)
        assert(s2.insert(i, i+5) == i);
    
    assert(s1.remove(5) == false);
    assert(s2.remove(4) == false);

    s1.swap(s2);
    assert(s1.size() == 6  &&  s1.find(5) == 0  &&  s2.size() == 5  &&
                    s2.find(0) == 0  &&  s2.find(1) == 1);
    s2.swap(s1);
    assert(s1.size() == 5  &&  s1.find(0) == 0  &&  s2.size() == 6  &&
                    s2.find(5) == 0  &&  s2.find(6) == 1);
    
    
    
    
    
    s1.dump();
    s2.dump();
    cerr << "Passed all tests" << endl;
    
}

#elif TESTNUM == 8

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}



#else

#include "Sequence.h"
#include <iostream>
#include <cassert>

int main()
{
        Sequence s;
        s.insert(0, 1);
        s.insert(1, 2);
        s.insert(2, 3);
        s.insert(3, 4);
        s.insert(4, 5);
        assert( (s.insert(6) ) == 5);
        assert( (s.insert(7) ) == 6);
        assert( (s.insert(7) ) == 6);
        assert( (s.insert(0) ) == 0);
    
    s.dump();
    std::cerr << "All Tests Passed" << std::endl;
}

#endif
