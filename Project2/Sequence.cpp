//
//  Sequence.cpp
//  Project2
//
//  Created by Esmail Mozaffari on 4/20/23.
// Author : Eideen Mozaffari
// UID : 105988436

#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
{
    // Construct circular doubly linked list with dummy node and head
    // Dynamically allocate space for dummy node, initialize the head pointer to dummy node
    // Initialize dummy node pointers to itself, set intial size of list to 0 (dummy node does not count as element of list)
    dummyNode = new Node;
    m_head = dummyNode;
    dummyNode->next = dummyNode;
    dummyNode->prev = dummyNode;
    m_size = 0;
    
}

Sequence::Sequence(const Sequence& other)
{
    // Copy Constructor
    // Create new sequence
    dummyNode = new Node;
    m_head = dummyNode;
    dummyNode->next = dummyNode;
    dummyNode->prev =  dummyNode;
    m_size = 0;
    
    // Copy elements from other to new sequence
    int i = 0;
    for (Node* p = other.m_head->next; p != other.m_head; p = p->next ) {
        insert(i, p->value);
        i++;
    }
   
}



Sequence::~Sequence()
{
    
    // Pointer keeping track of position in list
    Node* current = m_head;
    // Update current to next node each iteration, and then delete current's previous node
    // Keep doing this until current's -
    while (current->next != m_head) {
        current = current->next;
        delete current->prev;
    }
    // Last node in list
    delete current;
}



Sequence& Sequence::operator=(const Sequence &rhs)
{
    // Copy and swap method
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    
    return *this;
}

bool Sequence::empty() const
{
    return (m_size == 0);
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType &value)
{
    if (pos < 0 || pos > m_size) {
        return -1;
    }
    else {
        // Create pointer to node at insertion spot in Sequence
        Node* p = getNode(pos);
        // Create and initialize new node
        Node* new_Node = new Node;
        new_Node->value = value;
        // Hook up new node
        new_Node->next = p;
        new_Node->prev = p->prev;
        p->prev->next = new_Node;
        p->prev = new_Node;
        
        m_size++;
    }
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    int pos = 0;
    // Start at position 0
    // Find insertion position
    Node* p = m_head->next;
    while ( p != m_head && value > p->value) {
        p = p->next;
        pos++;
    }
    insert(pos, value);
    
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    else {
        // Create pointer to node at deletion position
        Node* p = getNode(pos);
        // Update elements on either side to disconnect node from list
        p->prev->next = p->next;
        p->next->prev = p->prev;
        // Remove node
        delete p;
        m_size--;
    }
    
    return true;
}


int Sequence::remove(const ItemType &value)
{
    int items_removed = 0;
    int i = 0;
    // Start at position 0,
    // If we find the value, our traversing pointer moves back one position in the list, delete the node at the position,
    // Then the next element takes the index position of the one just deleted
    for (Node* p = m_head->next; p != m_head; p = p->next, i++) {
        if (p->value == value) {
            p = p->prev;
            erase(i);
            i--;
            items_removed++;
        }
    }
    
    return items_removed;
}


bool Sequence::get(int pos, ItemType &value) const
{
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    else {
        Node* p = getNode(pos);
        value = p->value;
        return true;
    }
}

bool Sequence::set(int pos, const ItemType &value)
{
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    else {
        Node* p = getNode(pos);
        p->value = value;
        return true;
    }
}


int Sequence::find(const ItemType &value) const
{
    int index = 0;
    
    for (Node* p = m_head->next; p != m_head; p = p->next) {
        if (p->value == value) {
            return index;
        }
        index++;
    }
    
    return -1;
}

void Sequence::swap(Sequence &other)
{
    // Swap heads
    Node* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;
    
    // Swap sizes
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

Sequence::Node* Sequence::getNode(int position) const
{
    // Return a pointer to node corresponding's position in list,
    // Given a position, return a pointer to the node in that positon,
    // The functions calling this function are responsible for checking a valid position is passed.
    int index = 0;
    Node* p = m_head->next;
    while ( index < position && index < m_size ) {
        p = p->next;
        index++;
    }
    return p;
}

void Sequence::dump() const
{
    for (Node* p = m_head->next; p != m_head; p = p->next)
        std::cerr << p->value << std::endl;
    
    std::cerr << "The sequence size is " << m_size << std::endl;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // If either sequence is empty, there are no such elementss in either sequence that exist to potentially have the same value in another sequence
    if (seq1.empty() || seq2.empty())
        return -1;
    // Sequence 2 cannot be a subsequence of a smaller set
    if (seq2.size() > seq1.size())
        return -1;
    // Both sequences are the same object
    if (&seq1 == &seq2)
        return 0;
    // Store the value of the first element in seq2
    ItemType seq2_head = 0;
    seq2.get(0, seq2_head);
    int pos = seq1.find(seq2_head);
    // If we seq2 first value is not found in seq1, seq2 cannot be a subsequence
    if (pos == -1) {
        return -1;
    }
    // There is at least one element in seq1 that shares the value of the first element in seq2
    else {
        ItemType temp_seq1;
        ItemType temp_seq2;
        // Iterate through both sequences, checking if the consecutive values are equal
        for (int i = pos, k = 0; k < seq2.size() && i < seq1.size();) {
            seq1.get(i, temp_seq1);
            seq2.get(k, temp_seq2);
            // If values are not equal, check if there is another occurence of seq2's head in seq1
            // inSequence returns -1 if no value is found, otherwise it returns the value's position in seq1
            if (temp_seq1 != temp_seq2) {
                if ( (i = inSequence(seq1, seq2_head, pos+1)) == -1) {
                    return -1;
                }
                k = 0;
                pos = i;
            }
            // If the values in each sequence are the same, keep looping through the sequences
            else {
                i++;
                k++;
            }
        // If we have reached the end of seq1, but have not reached the end of seq2,
        // Then seq2 is not a subsequence
        if (i == seq1.size() && k != seq2.size())
            return -1;
        }
        
        return pos;
    }
}

// Helper function used in subsequence to check for an occurence of a value
// Basically, a find function that takes in a sequence, value, and a position to start checking at
// Return index of position where value is found, otherwise return -1
int inSequence(const Sequence& seq1, ItemType value, int pos)
{
    ItemType temp_seq1;
    // Check if value is anywhere else in seq1
    for (int i = pos; i < seq1.size(); i++) {
        seq1.get(i, temp_seq1);
        // If we find seq2's head in seq1, return the index in seq1
        if (value == temp_seq1) {
            return i;
        }
    }
    //Otherwise value is not in sequence
    return -1;
}


void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // Account for aliasing, where result could be either seq1 or seq2
    if (&result == &seq1 || &result == & seq2) {
        // Case 1: seq1 and result are aliases, seq2 is unique
        if (&result == &seq1 && &result != &seq2) {
            // Create copy of seq1
            Sequence seq1_cpy(seq1);
            // Remove all items in result
            while (result.size() > 0) {
                result.erase(result.size()-1);
            }
            // Insert all nodes in seq1's copy into result, in reverse
            int i = 0;
            int k = seq1_cpy.size() - 1;
            while (result.size() < seq1_cpy.size()) {
                ItemType temp;
                seq1_cpy.get(k, temp);
                result.insert( i, temp);
                i++;
                k--;
            }
            // Insert all the nodes in seq2 into result, in reverse
            int j = seq2.size()-1;
            while (result.size() < seq1_cpy.size() + seq2.size()) {
                ItemType temp;
                seq2.get(j, temp);
                result.insert(i, temp);
                i++;
                j--;
            }
        }
        // Case 2: seq2 and result are aliases, seq1 is unique
        else if (&result == &seq2 && &result != &seq1) {
            // Create copy of seq2
            Sequence seq2_cpy(seq2);
            // Remove all items in result
            while (result.size() > 0) {
                result.erase(result.size()-1);
            }
            // Insert all nodes in seq1 into result, in reverse
            int i = 0;
            int k = seq1.size() - 1;
            while (result.size() < seq1.size()) {
                ItemType temp;
                seq1.get(k, temp);
                result.insert(i, temp);
                i++;
                k--;
            }
            // Insert all nodes in seq2's into result, in reverse
            int j = seq2_cpy.size()-1;
            while (result.size() < seq1.size() + seq2_cpy.size()) {
                ItemType temp;
                seq2_cpy.get(j, temp);
                result.insert(i, temp);
                i++;
                j--;
            }
        }
        // Case 3: seq1, seq2, and result are all aliases of each other
        else {
            // Create copies for seq1,seq2
            Sequence seq1_cpy(seq1);
            Sequence seq2_cpy(seq2);
            // Remove all items in result
            while (result.size() > 0) {
                result.erase(result.size()-1);
            }
            // Insert all nodes in seq1's copy into result, in reverse
            int i = 0;
            int k = seq1_cpy.size() - 1;
            while (result.size() < seq1_cpy.size()) {
                ItemType temp;
                seq1_cpy.get(k, temp);
                result.insert(i, temp);
                i++;
                k--;
            }
            // Insert all nodes in seq2's copy into result, in reverse
            int j = seq2_cpy.size()-1;
            while (result.size() < seq1_cpy.size() + seq2_cpy.size()) {
                ItemType temp;
                seq2_cpy.get(j, temp);
                result.insert(i, temp);
                i++;
                j--;
            }
            
        }
    }
    // Otherwise, no aliasing with result is occuring
    else {
            // Remove all items in result
            while (result.size() > 0) {
                result.erase(result.size()-1);
            }
            // Add seq 1 first, then seq2
        
            // Insert all nodes in seq1 into result, in reverse
            int i = 0;
            int k = seq1.size() - 1;
            while (result.size() < seq1.size()) {
                ItemType temp;
                seq1.get(k, temp);
                result.insert( i, temp);
                i++;
                k--;
            }
            // Insert all nodes in seq2 into result, in reverse
            int j = seq2.size()-1;
            while (result.size() < seq1.size() + seq2.size()) {
                ItemType temp;
                seq2.get(j, temp);
                result.insert(i, temp);
                i++;
                j--;
            }
    }
}
