
//  main.cpp
//  Project2
//
//  Created by Esmail Mozaffari on 4/20/23.


//#include "Sequence.h"
//#include <iostream>
//#include <cassert>
//
//using namespace std;
//
//void test()
//{
//      cerr << "test A" << endl;
//    Sequence s;
//      cerr << "test B" << endl;
//    s.insert(0, IntWrapper(10));
//      cerr << "test C" << endl;
//    s.insert(0, IntWrapper(20));
//      cerr << "test D" << endl;
//    Sequence s2;
//      cerr << "test E" << endl;
//    s2.insert(0, IntWrapper(30));
//      cerr << "test F" << endl;
//    s2 = s;
//      cerr << "test G" << endl;
//    s2.insert(0, IntWrapper(40));
//      cerr << "test H" << endl;
//}
//
//int main()
//{
//    test();
//    cerr << "DONE" << endl;
//}


#define TESTNUM 17

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

#elif TESTNUM == 17

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
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
    // default constructor
    Sequence s;
    // For an empty sequence:
    assert(s.size() == 0);             // test size
    assert(s.empty());                 // test empty
    assert(s.find(10) == -1);
    assert(s.remove(0) == 0);  // nothing to remove

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

#elif TESTNUM == 9

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s5;
    s5.insert(0, 10);
    s5.insert(0, 20);
    assert(s5.size() == 2);
    ItemType x = 999;
    assert(s5.get(0, x) && x == 20);
    assert(s5.get(1, x) && x == 10);
    assert(s5.set(0, 30) && s5.find(30) == 0);
    assert(s5.set(1, 40) && s5.find(40) == 1);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 10

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main() {
    Sequence s8;
    s8.insert(0,30);
    s8.insert(1,21);
    s8.insert(2,63);
    s8.insert(3,42);
    s8.insert(4,17);
    s8.insert(5, 63);
    s8.insert(6, 17);
    s8.insert(7, 29);
    s8.insert(8, 8);
    s8.insert(9, 32);
    Sequence s9;
    s9.insert(0, 63);
    s9.insert(1, 17);
    s9.insert(2, 29);

    assert(subsequence(s8, s9) == 5);

    Sequence s10, s11, s12;
    assert(subsequence(s10, s11) == -1);

    s10.insert(0, 63);
    s10.insert(1, 17);
    s10.insert(2, 29);
    assert(subsequence(s10, s11) == -1);
    assert(subsequence(s12, s10) == -1);

    s11.insert(0, 63);
    s11.insert(1, 17);
    s11.insert(2, 29);
    assert(subsequence(s10, s11) == 0);

    s11.insert(3, 30);
    assert(subsequence(s10, s11) == -1);











    std::cerr << "All Test Cases passed" << std::endl;
    return 0;


}

#elif TESTNUM == 11

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main()
{
    Sequence s1;
    assert(s1.insert(0, 1) == 0);
    assert( s1.insert(1, 3) == 1);
    assert( s1.insert(1, 2) == 1);
    assert( s1.insert(4) == 3);


    // Copy Constructor
    Sequence s3 = s1;
    for (int i = 0, k = 1; i < 4; i++, k++) {       // test copy constructor
        assert(s3.find(k) == i);
    }
    for (int i = 0; i < 4; i++) {                   // test erase
        assert(s3.erase(0) == true);
    }
    assert(s1.size() == 4);                         // s1 is not affected
    assert(s3.empty() == true);                     // s3 is empty now


    // Assignment Operator
    Sequence s2 = s1;           // Copy Constructor
    s3 = s2;                    // Assignment operator

    for (int i = 0, k = 1; i < 4; i++, k++) {       // test copy constructor
        assert(s3.find(k) == i);
    }
    for (int i = 0; i < 4; i++) {                   // test erase
        assert(s3.erase(0) == true);
    }
    assert(s1.size() == 4);                    // s1 is not affected
    assert(s2.size() == 4);                    // s2 is not affected
    assert(s3.empty() == true);                // s3 is empty now



    Sequence s4;
    for (int i = 0; i < 5; i++) {
        s4.insert(7);
    }
    assert(s4.remove(7) == 5);          // Test remove
    assert(s4.empty() == true);



//
//    s1.dump();
//    s2.dump();
//    s3.dump();

    std::cerr << "All Test Cases passed" << std::endl;
    return 0;

}

#elif TESTNUM == 12

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main()
{
    Sequence s1;
    s1.insert(0, 1);
    s1.insert(1, 2);
    s1.insert(2, 3);
    s1.insert(3, 4);

    Sequence s2;
    s2.insert(0, 5);
    s2.insert(1, 6);
    s2.insert(2, 7);
    s2.insert(3, 8);

    s2 = s1;

    s1.dump();
    s2.dump();

    std::cerr << "All Test Cases passed" << std::endl;
    return 0;

}

#elif TESTNUM == 13

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main() {
    // Default Constructor, insert single parameter, insert double parameter

        Sequence s1;
        assert(s1.insert(0, 1) == 0);        // test insert on empty list
        assert(s1.insert(1, 3) == 1);            // end of list, one element list
        assert(s1.insert(1, 2) == 1);        // middle of list
        assert(s1.insert(4) == 3);        // test insert with 1 parameter
        assert(s1.insert(10,5) == -1);        // out of bounds insert
        assert(s1.insert(-1,5) == -1);        // out of bounds insert




    // Copy Constructor, insert, find, size

        Sequence s3 = s1;
        for (int i = 0, k = 1; i < 4; i++, k++) {       // test copy constructor
            assert(s3.find(k) == i);
        }
        for (int i = 0; i < 4; i++) {                   // test erase
            assert(s3.erase(0) == true);
        }
        assert(s1.size() == 4);                         // s1 is not affected
        assert(s3.empty() == true);                     // s3 is empty now


    // Assignment Operator/Copy Constructor

        Sequence s2 = s1;           // Copy Constructor
        s3 = s2;                    // Assignment operator

        for (int i = 0, k = 1; i < 4; i++, k++) {       // test assignment op
            assert(s3.find(k) == i);
        }
        for (int i = 0; i < 4; i++) {                   // test erase
            assert(s3.erase(0) == true);
        }
        assert(s1.size() == 4);                    // s1 is not affected
        assert(s2.size() == 4);                    // s2 is not affected
        assert(s3.empty() == true);                // s3 is empty now




    // Remove

        Sequence s4;
        for (int i = 0; i < 5; i++)
            s4.insert(7);
        assert(s4.remove(7) == 5);          // Test remove
        assert(s4.remove(10) == 0);          // Test element not in list
        assert(s4.empty() == true);    // All 5 elements removed


    // Get and Set

        Sequence s5;
        s5.insert(0, 10);
        s5.insert(0, 20);
        assert(s5.size() == 2);
        ItemType x = 999;
        assert(s5.get(0, x) && x == 20);            // x is 20
        assert(s5.get(1, x) && x == 10);            // x is 10
        assert(s5.get(2, x) == false);            // out of bounds get
        assert(s5.get(-1, x) == false);            // out of bounds get
        assert(s5.set(0, 30) && s5.find(30) == 0);    // Element 1 has val 30
        assert(s5.set(1, 40) && s5.find(40) == 1);    // Element 2 has val 40
        assert(s5.set(2, 50) == false);            // out of bounds set
        assert(s5.set(-1, 60) == false);            // out of bounds set





    // Swap, insert, erase, remove

        Sequence s6;
        Sequence s7;
        assert(s6.empty() == true);
        assert(s6.insert(1, 5) == -1);            // out of bounds insert
        assert(s6.insert(0, 1) == 0);
        assert(s6.insert(1, 2) == 1);
        assert(s6.insert(2, 3) == 2);
        assert(s6.insert(3) == 2);
        assert(s6.insert(0) == 0);
        assert(s6.insert(4) == 5);
        assert(s6.erase(0) == true);        // erase first element
        assert(s6.erase(4) == true);        // erase last element
        assert(s6.erase(2) == true);
        assert(s6.remove(3) == 1);
        assert(s6.remove(1) == 1);
        assert(s6.remove(2) == 1);            // s6 is empty now

        for (int i = 0; i < 5; i++)        // s6 is {0,1,2,3,4}
            assert(s6.insert(i) == i);

        for (int i = 0; i < 6; i++)
            assert(s7.insert(i, i+5) == i);    // s7 is {5,6,7,8,9,10}

        assert(s6.remove(5) == 0);        // no element exists
        assert(s7.remove(4) == 0);        // no element exists

    // Swap lists
        s6.swap(s7);
        assert(s6.size() == 6  &&  s6.find(5) == 0  &&  s7.size() == 5  &&
                        s7.find(0) == 0  &&  s7.find(1) == 1);
    // Swap lists back
        s6.swap(s7);
        assert(s6.size() == 5  &&  s6.find(0) == 0  &&  s7.size() == 6  &&
                        s7.find(5) == 0  &&  s7.find(6) == 1);

    // s6 is {0,1,2,3,4} and s7 is {5,6,7,8,9,10} after double swap, both back to original sequences


    // Subsequence

        Sequence s8;
        s8.insert(0,30);
        s8.insert(1,21);
        s8.insert(2,63);
        s8.insert(3,42);
        s8.insert(4,17);
        s8.insert(5, 63);
        s8.insert(6, 17);
        s8.insert(7, 29);
        s8.insert(8, 8);
        s8.insert(9, 32);
        Sequence s9;
        s9.insert(0, 63);
        s9.insert(1, 17);
        s9.insert(2, 29);

        assert(subsequence(s8, s9) == 5);        // Example from spec, tests for
                            // multiple occurrences of s9’s
                            // first element. We need to keep iterating through s8 to produce the right behavior

        Sequence s10, s11, s12;
        assert(subsequence(s10, s11) == -1);    // two empty sequences

        s10.insert(0, 63);
        s10.insert(1, 17);
        s10.insert(2, 29);
        assert(subsequence(s10, s11) == -1);    // tests empty sequence, which is !subsequence of another sequence

        assert(subsequence(s12, s10) == -1);    // tests two empty sequences

        assert(subsequence(s10, s10) == 0);    // tests same sequence

        s11.insert(0, 63);
        s11.insert(1, 17);
        s11.insert(2, 29);
        s11.insert(3, 30);
        assert(subsequence(s10, s11) == -1);    // tests when the “subsequence” still has more characters but the other sequence has no more left, even if they are identical up until the end of the first sequence



    // concatReverse

    Sequence s13;
        s13.insert(0, 3);
        s13.insert(1, 5);
        s13.insert(2, 7);
        s13.insert(1, 4);
        s13.insert(10);
        s13.erase(4);        // s13 is going to get changed with concatReverse

        Sequence a;
        a.insert(1);
        a.insert(2);
        a.insert(3);
        Sequence b;
        b.insert(4);
        b.insert(5);
        b.insert(6);

        concatReverse(a, b, s13);        // s13 is {3,2,1,6,5,4}

        assert(s13.find(3) == 0 && s13.find(2) == 1 && s13.find(1) == 2 && s13.find(6) == 3 && s13.find(5) == 4 && s13.find(4) == 5);


    // concatReverse and Assignment operator

        Sequence c = a;
        Sequence d = a;
        concatReverse(c, d, a);
        assert(a.find(3) == 0 && a.find(2) == 1 && a.find(1) == 2);
        assert(a.size() == 6);
        assert(c.find(1) == 0 && c.find(2) == 1 && c.find(3) == 2);
        assert(c.size() == 3);
        assert(d.find(1) == 0 && d.find(2) == 1 && d.find(3) == 2);
        assert(d.size() == 3);


    // concatReverse and Aliasing

        Sequence e;
        e.insert(1);
        e.insert(2);
        e.insert(3);
        Sequence f;
        f.insert(4);
        f.insert(5);
        f.insert(6);
        Sequence g = f;

        // seq1 and result are aliases
        concatReverse(e, f, e);
        assert(e.find(3) == 0 && e.find(2) == 1 && e.find(1) == 2 && e.find(6) == 3 && e.find(5) == 4 && e.find(4) == 5);
        assert(e.size() == 6);
        // seq 2 and result are aliases
        concatReverse(e, f, f);
        assert(f.find(4) == 0 && f.find(5) == 1 && f.find(6) == 2 && f.find(1) == 3 && f.find(2) == 4 && f.find(3) == 5);
        assert(f.size() == 9);

        // seq1, seq2, and result are all aliases
        concatReverse(g, g, g);
        assert(g.find(6) == 0 && g.find(5) == 1 && g.find(4) == 2);
        assert(g.size() == 6);

    std::cerr << "All Test Cases passed" << std::endl;
    return 0;


}


#elif TESTNUM == 14

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main()
{
    Sequence e;
    e.insert(1);
    e.insert(2);
    e.insert(3);
    Sequence f;
    f.insert(4);
    f.insert(5);
    f.insert(6);
    Sequence g = f;

    concatReverse(e, f, e);
    assert(e.find(3) == 0 && e.find(2) == 1 && e.find(1) == 2 && e.find(6) == 3 && e.find(5) == 4 && e.find(4) == 5);
    assert(e.size() == 6);

    concatReverse(e, f, f);
    assert(f.find(4) == 0 && f.find(5) == 1 && f.find(6) == 2 && f.find(1) == 3 && f.find(2) == 4 && f.find(3) == 5);
    assert(f.size() == 9);

    concatReverse(g, g, g);
    assert(g.find(6) == 0 && g.find(5) == 1 && g.find(4) == 2);
    assert(g.size() == 6);
    g.dump();



    std::cerr << "All Test Cases passed" << std::endl;
    return 0;



}



#else

#include <iostream>
#include "Sequence.h"
#include <cassert>

int main() {

//    Sequence s13;
//    s13.insert(0, 3);
//    s13.insert(1, 5);
//    s13.insert(2, 7);
//    s13.insert(1, 4);
//    s13.insert(10);
//    s13.erase(4);

    Sequence a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    Sequence b;
    b.insert(4);
    b.insert(5);
    b.insert(6);

//    concatReverse(a, b, s13);
//    assert(s13.find(3) == 0 && s13.find(2) == 1 && s13.find(1) == 2 && s13.find(6) == 3 && s13.find(5) == 4 && s13.find(4) == 5);
//    s1.dump();

    Sequence c = a;
    Sequence d = a;
    concatReverse(c, d, a);
    assert(a.find(3) == 0 && a.find(2) == 1 && a.find(1) == 2);
    assert(a.size() == 6);
    assert(c.find(1) == 0 && c.find(2) == 1 && c.find(3) == 2);
    assert(c.size() == 3);
    assert(d.find(1) == 0 && d.find(2) == 1 && d.find(3) == 2);
    assert(d.size() == 3);

//    c.dump();
//    d.dump();
//    a.dump();

    concatReverse(c, b, a);
//    c.dump();
//    b.dump();
//    a.dump();


    concatReverse(b, c, a);
//    b.dump();
//    c.dump();
//    a.dump();

    Sequence e, f;
    concatReverse(e, b, a);
//        e.dump();
//        b.dump();
//        a.dump();

    concatReverse(a, a, a);
    a.dump();



    std::cerr << "All Test Cases passed" << std::endl;
    return 0;
}



#endif


//#include "Sequence.h"
//#include <type_traits>
//
//#define CHECKTYPE(c, f, r, a)  \
//{  \
// static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
//     "You did not declare " #c "::" #f " as the Project 2 spec does");  \
// auto p = static_cast<r (c::*)a>(&c::f);  \
// (void) p;  \
//}
//#define CHECKTYPENONMEMBER(f, r, a)  \
//{  \
// static_assert(std::is_same<decltype(&f), r (*)a>::value, \
//     "You did not declare " #f " as the Project 2 spec does");  \
// auto p = static_cast<r (*)a>(f);  \
// (void) p;  \
//}
//
//static_assert(std::is_default_constructible<Sequence>::value,
//        "Sequence must be default-constructible.");
//static_assert(std::is_copy_constructible<Sequence>::value,
//        "Sequence must be copy-constructible.");
//static_assert(std::is_copy_assignable<Sequence>::value,
//        "Sequence must be assignable.");
//
//void thisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(Sequence, empty,  bool, () const);
//    CHECKTYPE(Sequence, size,   int,  () const);
//    CHECKTYPE(Sequence, erase,  bool, (int));
//    CHECKTYPE(Sequence, remove, int,  (const ItemType&));
//    CHECKTYPE(Sequence, get,    bool, (int, ItemType&) const);
//    CHECKTYPE(Sequence, set,    bool, (int, const ItemType&));
//    CHECKTYPE(Sequence, find,   int,  (const ItemType&) const);
//    CHECKTYPE(Sequence, swap,   void, (Sequence&));
//    CHECKTYPENONMEMBER(subsequence,   int,  (const Sequence&, const Sequence&));
//    CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
//    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void) p; }
//    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void) p; }
//}
//
//#include <iostream>
//int main()
//{
//    std::cerr << "nice " << std::endl;
//
//}
//
//
