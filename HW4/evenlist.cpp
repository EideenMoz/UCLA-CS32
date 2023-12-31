//
//  main.cpp
//  evenlist
//
//  Created by Esmail Mozaffari on 5/12/23.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

  // Remove the even integers from li.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original list.
void removeEven(list<int>& li)
{
    if (li.empty())
        return;
    
    for (list<int>::iterator i = li.begin(); i != li.end();)
    {
        if (*i % 2 == 0)
        {
            i = li.erase(i);
        }
        else
        {
            cerr << *i << endl;
            i++;
        }
    }
}




void test()
{
    int a[8] = { 1, 7, 6, 5, 8, 4, 3, 2 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 1 && x.back() == 2);
    removeEven(x);
    assert(x.size() == 4);
    for (list<int>::iterator i = x.begin(); i != x.end(); i++)
        cerr << *i << ", ";
    cerr << endl;
    
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 1, 3, 5, 7 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
