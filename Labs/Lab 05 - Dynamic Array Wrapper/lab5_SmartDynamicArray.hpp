#ifndef _SMART_DYNAMIC_ARRAY_HPP
#define _SMART_DYNAMIC_ARRAY_HPP

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class SmartDynamicArray
{
    public:
    SmartDynamicArray();
    ~SmartDynamicArray();

    void Push( const string& newItem );
    void Insert( int index, const string& newItem );
    void Extend( const SmartDynamicArray& other );
    void Pop();
    void Remove( int index );
    string Get( int index ) const;
    void Resize();
    void Resize( int newSize );

    int Size() const;
    bool IsFull() const;
    bool IsEmpty() const;

    string operator[]( int index );
    SmartDynamicArray& operator=( const SmartDynamicArray& other );
    bool operator==( const SmartDynamicArray& other );
    bool operator!=( const SmartDynamicArray& other );

    private:
    void ShiftRight( int index );
    void ShiftLeft( int index );
    bool IsInvalidIndex( int index ) const;
    bool IsNonContiguousIndex( int index ) const;
    void AllocateMemory();
    void AllocateMemory( int newSize );
    void DeallocateMemory();

    string* m_data;
    int m_itemCount;
    int m_arraySize;

    friend class Tester;
};

#endif
