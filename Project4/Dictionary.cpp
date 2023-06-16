//
//  Dictionary.cpp
//  Anagrams
//
//  Created by Esmail Mozaffari on 5/31/23.
//

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).


// /Users/esmailmozaffari/Documents/CS32/Project4/Anagrams/Anagrams/words.txt


#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    vector<list<list<string>>> m_hashTable;     // vector of lists of lists containing strings
    int m_buckets;
    string Order(string s) const;
};


DictionaryImpl::DictionaryImpl(int maxBuckets)
{
    m_hashTable.resize(maxBuckets);
    m_buckets = maxBuckets;
}




void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if (word.empty())
        return;
    
//    string ordered = Order(word);
    string ordered = word;
    std::sort(ordered.begin(), ordered.end());
    
    
    size_t keyIndex = hash<string>()(ordered) % m_buckets;
    
    list<list<string>>::iterator iter;
    for (iter = m_hashTable[keyIndex].begin(); iter != m_hashTable[keyIndex].end(); iter++)
    {
        string temp = (*iter).front();
        std::sort(temp.begin(), temp.end());
        if ( temp == ordered)
        {
            (*iter).push_back(word);
            return;
        }
    }
    
    if (iter == m_hashTable[keyIndex].end())
    {
        m_hashTable[keyIndex].emplace_back();
        m_hashTable[keyIndex].back().push_back(ordered);
        m_hashTable[keyIndex].back().push_back(word);
    }
    

//    for (list<string>::iterator innerIter = m_hashTable[keyIndex].begin()->begin(); innerIter != m_hashTable[keyIndex].begin()->end(); innerIter++)
//    {
////        cerr << *innerIter << " " << keyIndex << endl;
//        cerr << keyIndex << endl;
//    }
//
//
}



void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
    
//    string ordered = Order(letters);
    string ordered = letters;
    std::sort(ordered.begin(), ordered.end());
    
    size_t keyIndex = hash<string>()(ordered) % m_buckets;
    
    list<list<string>>::const_iterator iter;
    for (iter = m_hashTable[keyIndex].begin(); iter != m_hashTable[keyIndex].end(); iter++)
    {
        if ( (*iter).front() == ordered )
        {
            list<string>::const_iterator innerIter = iter->begin();
            innerIter++;
            while (innerIter != iter->end())
            {
                callback(*innerIter);
                innerIter++;
            }
            return;
        }
            
    }
    
}

//string DictionaryImpl::Order(string s) const
//{
//    // We want to order(alphabetize/sort) the word as efficiently as possible
//    vector<int> count(26, 0);
//    string result = "";
//
//    for (int i = 0; i < s.size(); i++)
//    {
//        int pos = s[i] - 97;            // 'a' has ascii value 97, convert char to index position (a0, b1, c2, d3, ...., z25)
//        count[pos] += 1;
//    }
//
//    for (int i = 0; i < count.size(); i ++)
//    {
//        if (count[i] != 0)
//        {
//            char curr = i + 97;                // convert int back to char
//            result += string(count[i], curr);
//        }
//
//    }
//
//    return result;
//
//}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//  // Each successive call to this function generates the next permutation of the
//  // characters in the parameter.  For example,
//  //    string s = "eel";
//  //    generateNextPermutation(s);  // now s == "ele"
//  //    generateNextPermutation(s);  // now s == "lee"
//  //    generateNextPermutation(s);  // now s == "eel"
//  // You don't have to understand this function's implementation.
//void generateNextPermutation(string& permutation)
//{
//    string::iterator last = permutation.end() - 1;
//    string::iterator p;
//
//    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
//        ;
//    if (p != permutation.begin())
//    {
//        string::iterator q;
//        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
//            ;
//        swap(*(p-1), *(q-1));
//    }
//    for ( ; p < last; p++, last--)
//        swap(*p, *last);
//}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}


