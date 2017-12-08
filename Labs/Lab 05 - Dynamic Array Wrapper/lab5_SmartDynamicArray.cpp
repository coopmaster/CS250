#include "lab5_SmartDynamicArray.hpp"

#include "cuTEST/Menu.hpp"

SmartDynamicArray::SmartDynamicArray()
{
	m_arraySize = 0;
	m_itemCount = 0;
	m_data = nullptr;
}

SmartDynamicArray::~SmartDynamicArray()
{
	DeallocateMemory();
}

void SmartDynamicArray::AllocateMemory()
{
	AllocateMemory(10);
}

void SmartDynamicArray::AllocateMemory( int newSize )
{
	try{
		m_arraySize = newSize;
		m_itemCount = 0;
		m_data = new string[newSize];
	}catch( const logic_error& e ){
		cout << "ERROR: unable to allocate memory <" << e.what() << ">";
	}
}

void SmartDynamicArray::DeallocateMemory()
{
	if (m_data != nullptr){
		delete[] m_data;
		m_data = nullptr;
	}
}


bool SmartDynamicArray::IsInvalidIndex( int index ) const
{
	if (index < 0)
		return true;
	else
		return false;
}


bool SmartDynamicArray::IsNonContiguousIndex( int index ) const
{
	if (index > m_itemCount)
		return true;
	else
		return false;
}


void SmartDynamicArray::Push( const string& newItem )
{
}


void SmartDynamicArray::Pop()
{
}


bool SmartDynamicArray::IsEmpty() const
{
    return false; // placeholder
}


void SmartDynamicArray::ShiftRight( int index )
{
}


void SmartDynamicArray::ShiftLeft( int index )
{
}


void SmartDynamicArray::Resize()
{
	Resize(m_arraySize+10);
}


void SmartDynamicArray::Resize( int newSize )
{

}


bool SmartDynamicArray::IsFull() const
{
    return false; // placeholder
}


int SmartDynamicArray::Size() const
{
    return -1; // placeholder
}


void SmartDynamicArray::Remove( int index )
{
}


string SmartDynamicArray::Get( int index ) const
{
    return "placeholder"; // placeholder
}


void SmartDynamicArray::Insert( int index, const string& newItem )
{
}


void SmartDynamicArray::Extend( const SmartDynamicArray& other )
{
}


string SmartDynamicArray::operator[]( int index )
{
    return Get( index );
}


SmartDynamicArray& SmartDynamicArray::operator=( const SmartDynamicArray& other )
{
    for ( int i = 0; i < other.m_itemCount; i++ )
    {
        m_data[i] = other.m_data[i];
        m_itemCount++;
    }

    return *this;
}

bool SmartDynamicArray::operator==( const SmartDynamicArray& other )
{
    if ( m_itemCount != other.m_itemCount )
    {
        return false;
    }

    for ( int i = 0; i < m_itemCount; i++ )
    {
        if ( m_data[i] != other.m_data[i] )
        {
            return false;
        }
    }

    return true;
}


bool SmartDynamicArray::operator!=( const SmartDynamicArray& other )
{
    return !( *this == other );
}
