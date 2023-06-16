//
//  Sequence.hpp
//  Project2
//
//  Created by Esmail Mozaffari on 4/20/23.
//
// Author : Eideen Mozaffari
// UID : 105988436

#ifndef Sequence_INCLUDED
#define Sequence_INCLUDED

#include <stdio.h>
#include <string>

using ItemType = std::string;

class Sequence
{
    private:
        struct Node
        {
            ItemType value;
            Node* next;
            Node* prev;
        };
        Node* dummyNode;
        Node* m_head;
        int m_size;
        
    Node* getNode(int position) const;
    
    public:
        Sequence();
    
        Sequence(const Sequence& other);    // Copy constructor
        ~Sequence();        // Destructor
        Sequence& operator=(const Sequence& rhs);       // Assignment Operator
    
        bool empty() const;
        int size() const;
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& other);
    
        void dump() const;

};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);
int inSequence(const Sequence& seq1, ItemType value, int pos);

#endif /* Sequence_hpp */
