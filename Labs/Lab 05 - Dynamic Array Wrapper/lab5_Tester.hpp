#ifndef _TESTER_HPP
#define _TESTER_HPP

#include <iostream>
#include <string>
#include <ostream>
using namespace std;

#include "cuTEST/TesterBase.hpp"
#include "cuTEST/Menu.hpp"
#include "cuTEST/StringUtil.hpp"

#include "lab5_SmartDynamicArray.hpp"

class Tester : public TesterBase
{
public:
	Tester()
	{
		AddTest(TestListItem("Test Initialize",             bind(&Tester::Test_Initialize, this)));
		AddTest(TestListItem("Test AllocateMemory",         bind(&Tester::Test_AllocateMemory, this)));
		AddTest(TestListItem("Test DeallocateMemory",       bind(&Tester::Test_DeallocateMemory, this)));
		AddTest(TestListItem("Test IsInvalidIndex",         bind(&Tester::Test_IsInvalidIndex, this)));
		AddTest(TestListItem("Test IsNoncontiguousIndex",   bind(&Tester::Test_IsNoncontiguousIndex, this)));
		AddTest(TestListItem("Test Push",                   bind(&Tester::Test_Push, this)));
		AddTest(TestListItem("Test Pop",                    bind(&Tester::Test_Pop, this)));
		AddTest(TestListItem("Test IsEmpty",                bind(&Tester::Test_IsEmpty, this)));
		AddTest(TestListItem("Test ShiftRight",             bind(&Tester::Test_ShiftRight, this)));
		AddTest(TestListItem("Test ShiftLeft",              bind(&Tester::Test_ShiftLeft, this)));
		AddTest(TestListItem("Test Remove",                 bind(&Tester::Test_Remove, this)));
		AddTest(TestListItem("Test Resize",                 bind(&Tester::Test_Resize, this)));
		AddTest(TestListItem("Test IsFull",                 bind(&Tester::Test_IsFull, this)));
		AddTest(TestListItem("Test Size",                   bind(&Tester::Test_Size, this)));
		AddTest(TestListItem("Test Get",                    bind(&Tester::Test_Get, this)));
		AddTest(TestListItem("Test Extend",                 bind(&Tester::Test_Extend, this)));
		AddTest(TestListItem("Test Insert",                 bind(&Tester::Test_Insert, this)));
	}

	virtual ~Tester() { }

private:
	int Test_Initialize();
	int Test_AllocateMemory();
	int Test_DeallocateMemory();
	int Test_IsFull();
	int Test_IsEmpty();
	int Test_Push();
	int Test_Pop();
	int Test_Size();
	int Test_ShiftRight();
	int Test_ShiftLeft();
	int Test_Get();
	int Test_Insert();
	int Test_Remove();
	int Test_Extend();
	int Test_Resize();
	int Test_IsInvalidIndex();
	int Test_IsNoncontiguousIndex();
};


int Tester::Test_Initialize()
{
    StartTestSet( "Test_Initialize", { "SmartDynamicArray constructor" } );

    ostringstream oss;

    string* expectedOutput1;
    string* actualOutput1;

    int expectedOutput2, actualOutput2;
    int expectedOutput3, actualOutput3;

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check to make sure new SmartDynamicArrays initialize its m_data pointer to nullptr" ); {
        Set_Comments( "Created new empty SmartDynamicArray" );

        SmartDynamicArray sd1;

        expectedOutput1 = nullptr;
        actualOutput1   = sd1.m_data;

        oss << expectedOutput1;
        Set_ExpectedOutput  ( "m_data", oss.str() );
        oss << actualOutput1;
        Set_ActualOutput    ( "m_data", oss.str() );

        if ( expectedOutput1 != actualOutput1 )   { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check to make sure new SmartDynamicArrays initialize its m_itemCount value to 0" ); {
        Set_Comments( "Created new empty SmartDynamicArray" );

        SmartDynamicArray sd2;

        expectedOutput2 = 0;
        actualOutput2   = sd2.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput2 );
        Set_ActualOutput    ( "m_itemCount", actualOutput2 );

        if ( expectedOutput2 != actualOutput2 )   { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check to make sure new SmartDynamicArrays initialize its m_arraySize value to 0" ); {
        Set_Comments( "Created new empty SmartDynamicArray" );

        SmartDynamicArray sd3;

        expectedOutput3 = 0;
        actualOutput3   = sd3.m_arraySize;

        Set_ExpectedOutput  ( "m_arraySize", expectedOutput3 );
        Set_ActualOutput    ( "m_arraySize", actualOutput3 );

        if ( expectedOutput3 != actualOutput3 )   { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_AllocateMemory()
{
    StartTestSet( "Test_AllocateMemory", { "AllocateMemory" } );

    string* expectedOutput1;
    string* actualOutput1;

    ostringstream oss;
    bool threwException;

    string* temp = new string[ 100 ]; // this should be deallocated by the destructor of SmartDynamicArray
    threwException = false;

    SmartDynamicArray sd1;
    sd1.m_data = temp;
    try
    {
        sd1.AllocateMemory();
    }
    catch( exception& ex )
    {
        threwException = true;
    }

    expectedOutput1 = temp;
    actualOutput1   = sd1.m_data;

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When m_data is already pointing to an address, make sure an exception is thrown" ); {
        Set_Comments( "Created new SmartDynamicArray, set its m_data to some address, called AllocateMemory. Should throw exception and not change m_data." );

        Set_ExpectedOutput  ( "Should throw an exception" );
        if ( threwException )   Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( threwException == false )          { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When m_data is already pointing to an address, make the address doesn't change" ); {
        Set_Comments( "Created new SmartDynamicArray, set its m_data to some address, called AllocateMemory. m_data should still point to original address and not a new address." );

        oss << expectedOutput1;
        Set_ExpectedOutput  ( "m_data", oss.str() );
        oss << actualOutput1;
        Set_ActualOutput    ( "m_data", oss.str() );

        if ( expectedOutput1 != actualOutput1 )   { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_DeallocateMemory()
{
    StartTestSet( "Test_DeallocateMemory", { "DeallocateMemory" } );

    string* expectedOutput1;
    string* actualOutput1;

    ostringstream oss;
    bool threwException;

    string* temp = new string[ 100 ]; // this should be deallocated by the destructor of SmartDynamicArray
    threwException = false;

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When m_data is not pointing to an address, calling DeallocateMemory shouldn't cause a problem" ); {
        Set_Comments( "Created new SmartDynamicArray, set its m_data to nullptr, called DeallocateMemory." );

        SmartDynamicArray sd1;
        sd1.m_data = nullptr;
        try
        {
            sd1.DeallocateMemory();
        }
        catch( exception& ex )
        {
            threwException = true;
        }

        Set_ExpectedOutput  ( "Shouldn't have an error" );
        if ( threwException )   Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( threwException == true )           { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When m_data is already pointing to an address, make the address doesn't change" ); {
        Set_Comments( "Created new SmartDynamicArray, set its m_data to some address, called DeallocateMemory. Memory should be freed (can't test this) & m_data set to nullptr." );

        SmartDynamicArray sd2;
        sd2.m_data = temp;
        sd2.DeallocateMemory();

        expectedOutput1 = nullptr;
        actualOutput1 = sd2.m_data;

        oss << expectedOutput1;
        Set_ExpectedOutput  ( "m_data", oss.str() );
        oss << actualOutput1;
        Set_ActualOutput    ( "m_data", oss.str() );

        if ( expectedOutput1 != actualOutput1 )   { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Push()
{
    StartTestSet( "Test_Push", { "Push" } );

    ostringstream oss;

    SmartDynamicArray sd1;
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Push an item to empty SmartDynamicArray, make sure memory is allocated." ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed one item in" );
        string* actualOutput1;

        sd1.m_data = nullptr;

        sd1.Push( "Hello" );

        actualOutput1 = sd1.m_data;

        Set_ExpectedOutput  ( "m_data shouldn't be pointing at nullptr" );
        oss << actualOutput1;
        Set_ActualOutput    ( "m_data", oss.str() );

        if ( nullptr == actualOutput1 )      { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    if ( sd1.m_data == nullptr )
    {
        // Can't do any more tests; exit!
        FinishTestSet();
        return TestResult();
    }

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Push an item to empty SmartDynamicArray, make sure it is accessible." ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed one item in" );
        string expectedOutput2, actualOutput2;

        SmartDynamicArray sd2;
        sd2.m_data = nullptr;

        sd2.Push( "Hello" );

        expectedOutput2 = "Hello";
        actualOutput2 = sd2.m_data[0];

        Set_ExpectedOutput  ( "First item", expectedOutput2 );
        Set_ActualOutput    ( "First item", actualOutput2 );

        if ( expectedOutput2 != actualOutput2 )     { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Push several items to a SmartDynamicArray, make sure they're accessible" ); {
        Set_Comments( "Created new empty SmartDynamicArray, push several items in" );
        string expectedOutputs[] = { "Hello", "there", "how", "are", "you" };

        SmartDynamicArray sd2;
        sd2.m_data = nullptr;

        for ( int i = 0; i < 5; i++ )
        {
            sd2.Push( expectedOutputs[i] );
        }

        Set_ExpectedOutput  ( "Item 0", expectedOutputs[0] );
        Set_ActualOutput    ( "Item 0", sd2.m_data[0] );

        Set_ExpectedOutput  ( "Item 1", expectedOutputs[1] );
        Set_ActualOutput    ( "Item 1", sd2.m_data[1] );

        Set_ExpectedOutput  ( "Item 2", expectedOutputs[2] );
        Set_ActualOutput    ( "Item 2", sd2.m_data[2] );

        Set_ExpectedOutput  ( "Item 3", expectedOutputs[3] );
        Set_ActualOutput    ( "Item 3", sd2.m_data[3] );

        Set_ExpectedOutput  ( "Item 4", expectedOutputs[4] );
        Set_ActualOutput    ( "Item 4", sd2.m_data[4] );

        if      ( expectedOutputs[0] != sd2.m_data[0] )     { TestFail(); }
        else if ( expectedOutputs[1] != sd2.m_data[1] )     { TestFail(); }
        else if ( expectedOutputs[2] != sd2.m_data[2] )     { TestFail(); }
        else if ( expectedOutputs[3] != sd2.m_data[3] )     { TestFail(); }
        else if ( expectedOutputs[4] != sd2.m_data[4] )     { TestFail(); }
        else                                                { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Pop()
{
    StartTestSet( "Test_Pop", { "Pop", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should not become negative if pop is called on an empty SmartDynamicArray" ); {
        Set_Comments( "Created empty SmartDynamicArray, called Pop" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Pop();

        expectedOutput = 0;
        actualOutput = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should be 0 after calling push then pop" ); {
        Set_Comments( "Created empty SmartDynamicArray, called Push, then called Pop" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "Moo" );
        sd.Pop();

        expectedOutput = 0;
        actualOutput = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should be -1 after popping one item" ); {
        Set_Comments( "Created empty SmartDynamicArray, called Push 5 times, then Pop 3 times" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "Moo1" );
        sd.Push( "Moo2" );
        sd.Push( "Moo3" );
        sd.Push( "Moo4" );
        sd.Push( "Moo5" );
        sd.Pop();
        sd.Pop();
        sd.Pop();

        expectedOutput = 2;
        actualOutput = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_IsEmpty()
{
    StartTestSet( "Test_IsEmpty", { "Push", "Pop" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsEmpty is true for new SmartDynamicArray" ); {
        Set_Comments( "Created empty SmartDynamicArray" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = true;
        actualOutput = sd.IsEmpty();

        Set_ExpectedOutput  ( "IsEmpty()", expectedOutput );
        Set_ActualOutput    ( "IsEmpty()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsEmpty is false for SmartDynamicArray after push" ); {
        Set_Comments( "Created empty SmartDynamicArray, Pushed 1 item" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "I'm hungry" );

        expectedOutput = false;
        actualOutput = sd.IsEmpty();

        Set_ExpectedOutput  ( "IsEmpty()", expectedOutput );
        Set_ActualOutput    ( "IsEmpty()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsEmpty is false for SmartDynamicArray after push" ); {
        Set_Comments( "Created empty SmartDynamicArray, Pushed 2 item" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "I'm hungry" );
        sd.Push( "I'm still hungry" );

        expectedOutput = false;
        actualOutput = sd.IsEmpty();

        Set_ExpectedOutput  ( "IsEmpty()", expectedOutput );
        Set_ActualOutput    ( "IsEmpty()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsEmpty is true for SmartDynamicArray after push and pop" ); {
        Set_Comments( "Created empty SmartDynamicArray, Pushed 2 items, Popped 2 items" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "I'm hungry" );
        sd.Push( "I'm still hungry" );
        sd.Pop();
        sd.Pop();

        expectedOutput = true;
        actualOutput = sd.IsEmpty();

        Set_ExpectedOutput  ( "IsEmpty()", expectedOutput );
        Set_ActualOutput    ( "IsEmpty()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_IsInvalidIndex()
{
    StartTestSet( "Test_IsInvalidIndex", { "IsInvalidIndex" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure negative indexes are marked as invalid" ); {
        Set_Comments( "Index is -1" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = true;
        actualOutput = sd.IsInvalidIndex( -1 );

        Set_ExpectedOutput  ( "IsInvalidIndex()", expectedOutput );
        Set_ActualOutput    ( "IsInvalidIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure negative indexes are marked as invalid" ); {
        Set_Comments( "Index is -10" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = true;
        actualOutput = sd.IsInvalidIndex( -10 );

        Set_ExpectedOutput  ( "IsInvalidIndex()", expectedOutput );
        Set_ActualOutput    ( "IsInvalidIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure 0 index is marked as valid" ); {
        Set_Comments( "Index is 0" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = false;
        actualOutput = sd.IsInvalidIndex( 0 );

        Set_ExpectedOutput  ( "IsInvalidIndex()", expectedOutput );
        Set_ActualOutput    ( "IsInvalidIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure positive index is marked as valid" ); {
        Set_Comments( "Index is 5" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = false;
        actualOutput = sd.IsInvalidIndex( 5 );

        Set_ExpectedOutput  ( "IsInvalidIndex()", expectedOutput );
        Set_ActualOutput    ( "IsInvalidIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_IsNoncontiguousIndex()
{
    StartTestSet( "Test_IsNonContiguousIndex", { "IsNonContiguousIndex" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When the item count is 0, make sure anything after 1 is non-contiguous" ); {
        Set_Comments( "Index is 5" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.m_itemCount = 0;

        expectedOutput = true;
        actualOutput = sd.IsNonContiguousIndex( 5 );

        Set_ExpectedOutput  ( "IsNonContiguousIndex()", expectedOutput );
        Set_ActualOutput    ( "IsNonContiguousIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When the item count is 0, make sure 0 is contiguous" ); {
        Set_Comments( "Index is 0" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.m_itemCount = 0;

        expectedOutput = false;
        actualOutput = sd.IsNonContiguousIndex( 0 );

        Set_ExpectedOutput  ( "IsNonContiguousIndex()", expectedOutput );
        Set_ActualOutput    ( "IsNonContiguousIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When the item count is 5, make sure 2 is contiguous" ); {
        Set_Comments( "Index is 2" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.m_itemCount = 5;

        expectedOutput = false;
        actualOutput = sd.IsNonContiguousIndex( 2 );

        Set_ExpectedOutput  ( "IsNonContiguousIndex()", expectedOutput );
        Set_ActualOutput    ( "IsNonContiguousIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When the item count is 5, make sure 5 is contiguous" ); {
        Set_Comments( "Index is 5" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.m_itemCount = 5;

        expectedOutput = false;
        actualOutput = sd.IsNonContiguousIndex( 5 );

        Set_ExpectedOutput  ( "IsNonContiguousIndex()", expectedOutput );
        Set_ActualOutput    ( "IsNonContiguousIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "When the item count is 5, make sure 6 is non-contiguous" ); {
        Set_Comments( "Index is 5" );
        bool expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.m_itemCount = 5;

        expectedOutput = true;
        actualOutput = sd.IsNonContiguousIndex( 6 );

        Set_ExpectedOutput  ( "IsNonContiguousIndex()", expectedOutput );
        Set_ActualOutput    ( "IsNonContiguousIndex()", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();
    
    FinishTestSet();
    return TestResult();
}

int Tester::Test_ShiftRight()
{
    StartTestSet( "Test_ShiftRight", { "ShiftRight", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted right correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftRight at 0" );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "a", "a", "b", "c" }; // don't care about item 0
        string actualOutput[4];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftRight( 0 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            if ( i == 0 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted right correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftRight at 1" );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "a", "b", "b", "c" }; // don't care about item 1
        string actualOutput[4];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftRight( 1 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            if ( i == 1 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted right correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftRight at 2" );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "a", "b", "c", "c" }; // don't care about item 2
        string actualOutput[4];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftRight( 2 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            if ( i == 2 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure ShiftRight doesn't affect array if index is outside of contiguous elements" ); {
        Set_Comments( "Push 3 items, then use ShiftRight at 3" );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[3] = { "a", "b", "c" };
        string actualOutput[3];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftRight( 3 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_ShiftLeft()
{
    StartTestSet( "Test_ShiftLeft", { "ShiftLeft", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted left correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftLeft at 0 shouldn't affect the list" );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "b", "c", "c" };
        string actualOutput[3];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftLeft( 0 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            if ( 2 == 0 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted left correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftLeft at 1, should shift everything." );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "a", "c", "c" };
        string actualOutput[3];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftLeft( 1 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            if ( 2 == 0 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure everything is shifted left correctly" ); {
        Set_Comments( "Push 3 items, then use ShiftLeft at 5, nothing should change." );

        string initialArray[] = { "a", "b", "c" };
        string expectedOutput[] = { "a", "b", "c" };
        string actualOutput[3];

        SmartDynamicArray sd;

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( initialArray[i] );
        }

        sd.ShiftLeft( 5 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 3; i++ )
        {
            if ( 2 == 0 ) { continue; }
            actualOutput[i] = sd.m_data[i];
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput[i] );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput[i] );
            
            if ( expectedOutput[i] != actualOutput[i] )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )        { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();
    
    FinishTestSet();
    return TestResult();
}

int Tester::Test_Get()
{
    StartTestSet( "Test_Get", { "Push", "Get" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure an exception is thrown for an invalid index" ); {
        Set_Comments( "Empty SmartDynamicArray, try to get item 5" );
        SmartDynamicArray sd;

        string expectedOutput, actualOutput;

        bool threwException = false;
        try
        {
            expectedOutput = sd.Get( 5 );
        }
        catch( exception& ex )
        {
            threwException = true;
        }

        Set_ExpectedOutput  ( "Exception should throw" );
        if ( threwException )   Set_ActualOutput    ( "Exception was thrown" );
        else                    Set_ActualOutput    ( "Exception was not thrown" );

        if ( threwException == false )  { TestFail(); }
        else                            { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Use Get to access every item Pushed in" ); {
        Set_Comments( "Empty SmartDynamicArray, Push some items, try to Get each one." );
        SmartDynamicArray sd;

        string items[] = { "a", "b", "c", "d" };
        string expectedOutput, actualOutput;

        for ( int i = 0; i < 4; i++ )
        {
            sd.Push( items[i] );
        }

        bool allMatched = true;
        for ( int i = 0; i < 4; i++ )
        {
            expectedOutput = items[i];
            actualOutput = sd.Get( i );

            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatched = false;
            }
        }

        if ( allMatched == false )          { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Insert()
{
    StartTestSet( "Test_Insert", { "Insert" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Insert first item into SmartDynamicArray" ); {
        Set_Comments( "Created empty SmartDynamicArray, used Insert to add first item at 0. Size should be incremented." );
        SmartDynamicArray sd;
        sd.Insert( 0, "HI" );

        string expectedOutput = "HI";
        string actualOutput = sd.m_data[0];
        int expectedSize = 1;
        int actualSize = sd.m_itemCount;

        Set_ExpectedOutput  ( "Item 0", expectedOutput );
        Set_ActualOutput    ( "Item 0", actualOutput );

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( expectedOutput != actualOutput )       { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Insert several items at the end of the array and verify" ); {
        Set_Comments( "Created empty SmartDynamicArray, used Insert to add first item at 0. Size should be incremented." );
        SmartDynamicArray sd;

        string values[] = { "SoM", "SoM2", "LoM", "DoM", "CoM" };

        for ( int i = 0; i < 5; i++ )
        {
            sd.Insert( i, values[i] );
        }

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 5; i++ )
        {
            string expectedOutput = values[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }

        int expectedSize = 5;
        int actualSize = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Insert several items at the begnning of the array and verify" ); {
        Set_Comments( "Created empty SmartDynamicArray, insert each item at 0, everything should shift" );
        SmartDynamicArray sd;

        string values[] = { "TLJ", "MI", "DoTT", "TWD" };
        string expectedOutputs[] = { "TWD", "DoTT", "MI", "TLJ" };

        for ( int i = 0; i < 4; i++ )
        {
            sd.Insert( 0, values[i] );
        }

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )                    { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Insert several items, with a few at midpoints" ); {
        Set_Comments( "Created empty SmartDynamicArray, insert each item at different positions" );
        SmartDynamicArray sd;

        string values[] = { "KQ", "SQ", "QFG", "LSL", "TP" };
        string expectedOutputs[] = { "TP", "KQ", "LSL", "SQ", "QFG" };

        sd.Insert( 0, values[0] );  // KQ
        sd.Insert( 1, values[1] );  // SQ
        sd.Insert( 2, values[2] );  // QFG
        sd.Insert( 1, values[3] );  // LSL
        sd.Insert( 0, values[4] );  // TP

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )                    { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check for exception - invalid index" ); {
        Set_Comments( "Try to insert at negative position" );
        SmartDynamicArray sd;

        bool exceptionThrown = false;

        try
        {
            sd.Insert( -1, "HI" );
        }
        catch( exception& ex )
        {
            exceptionThrown = true;
        }
        
        Set_ExpectedOutput  ( "Should throw an exception" );
        if ( exceptionThrown )  Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( exceptionThrown == false )     { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check for exception - non-contiguous index" ); {
        Set_Comments( "Insert A, B, C, then try to insert D at index 5." );
        SmartDynamicArray sd;

        bool exceptionThrown = false;

        sd.Insert( 0, "A" );
        sd.Insert( 1, "B" );
        sd.Insert( 2, "C" );

        try
        {
            sd.Insert( 5, "D" );
        }
        catch( exception& ex )
        {
            exceptionThrown = true;
        }
        
        Set_ExpectedOutput  ( "Should throw an exception" );
        if ( exceptionThrown )  Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( exceptionThrown == false )     { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Remove()
{
    StartTestSet( "Test_Remove", { "Remove", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Remove items, check array and m_itemCount" ); {
        Set_Comments( "Push several items, remove item at index 0" );
        SmartDynamicArray sd;

        string values[] = { "HL", "TF", "P" };
        string expectedOutputs[] = { "TF", "P" };

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( values[i] );
        }

        sd.Remove( 0 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 2; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }
        
        int expectedSize = 2;
        int actualSize = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Remove items, check array and m_itemCount" ); {
        Set_Comments( "Push several items, remove item at index 1" );
        SmartDynamicArray sd;

        string values[] = { "HL", "TF", "P" };
        string expectedOutputs[] = { "HL", "P" };

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( values[i] );
        }

        sd.Remove( 1 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 2; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }
        
        int expectedSize = 2;
        int actualSize = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Remove items, check array and m_itemCount" ); {
        Set_Comments( "Push several items, remove item at index 2" );
        SmartDynamicArray sd;

        string values[] = { "HL", "TF", "P" };
        string expectedOutputs[] = { "HL", "TF" };

        for ( int i = 0; i < 3; i++ )
        {
            sd.Push( values[i] );
        }

        sd.Remove( 2 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 2; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }
        
        int expectedSize = 2;
        int actualSize = sd.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check for exception - invalid index" ); {
        Set_Comments( "Try to remove at negative position" );
        SmartDynamicArray sd;

        bool exceptionThrown = false;

        try
        {
            sd.Remove( -1 );
        }
        catch( exception& ex )
        {
            exceptionThrown = true;
        }
        
        Set_ExpectedOutput  ( "Should throw an exception" );
        if ( exceptionThrown )  Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( exceptionThrown == false )     { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Check for exception - non-contiguous index" ); {
        Set_Comments( "Insert A, B, C, then try to remove D at index 5." );
        SmartDynamicArray sd;

        bool exceptionThrown = false;

        sd.Push( "A" );
        sd.Push( "B" );
        sd.Push( "C" );

        try
        {
            sd.Remove( 5 );
        }
        catch( exception& ex )
        {
            exceptionThrown = true;
        }
        
        Set_ExpectedOutput  ( "Should throw an exception" );
        if ( exceptionThrown )  Set_ActualOutput    ( "Threw exception" );
        else                    Set_ActualOutput    ( "Didn't throw exception" );

        if ( exceptionThrown == false )     { TestFail(); }
        else                                { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Extend()
{
    StartTestSet( "Test_Extend", { "Extend", "Resize", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Extend without resize" ); {
        Set_Comments( "Try to extend a small array by another small array" );
        SmartDynamicArray sd1, sd2;

        sd1.Push( "a" );
        sd1.Push( "b" );
        sd2.Push( "c" );
        sd2.Push( "d" );

        sd1.Extend( sd2 );

        string expectedOutputs[] = { "a", "b", "c", "d" };

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 4; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd1.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }
        
        int expectedSize = 4;
        int actualSize = sd1.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Extend with resize" ); {
        Set_Comments( "Try to extend an array with another array that will push it past the m_arraySize" );
        SmartDynamicArray sd1, sd2;

        sd1.Push( "A-1" );
        sd1.Push( "A-2" );
        sd1.Push( "A-3" );
        sd1.Push( "A-4" );
        sd1.Push( "A-5" );
        sd1.Push( "A-6" );

        sd2.Push( "B-1" );
        sd2.Push( "B-2" );
        sd2.Push( "B-3" );
        sd2.Push( "B-4" );
        sd2.Push( "B-5" );
        sd2.Push( "B-6" );

        sd1.Extend( sd2 );

        string expectedOutputs[] = { "A-1", "A-2", "A-3", "A-4", "A-5", "A-6", "B-1", "B-2", "B-3", "B-4", "B-5", "B-6" };

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 12; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd1.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }
        
        int expectedSize = 12;
        int actualSize = sd1.m_itemCount;

        Set_ExpectedOutput  ( "m_itemCount", expectedSize );
        Set_ActualOutput    ( "m_itemCount", actualSize );

        if ( allMatch == false )                    { TestFail(); }
        else if ( expectedSize != actualSize )      { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Resize()
{
    StartTestSet( "Test_Resize", { "Resize", "AllocateMemory", "Push" } );

    ostringstream oss;
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure Resize will change the address of m_data" ); {
        Set_Comments( "" );
        SmartDynamicArray sd;
        sd.AllocateMemory( 5 );

        string* oldOutput = sd.m_data;

        sd.Resize( 10 );
        
        string* actualOutput   = sd.m_data;

        oss << oldOutput;
        Set_ExpectedOutput  ( "m_data something besides", oss.str() );
        oss << actualOutput;
        Set_ActualOutput    ( "m_data", oss.str() );

        if ( oldOutput == actualOutput )        { TestFail(); } // don't want same address
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure Resize will change the size of m_arraySize" ); {
        Set_Comments( "" );
        SmartDynamicArray sd;
        sd.AllocateMemory( 5 );

        sd.Resize( 10 );

        int expectedOutput = 10;
        int actualOutput = sd.m_arraySize;

        Set_ExpectedOutput  ( "m_arraySize", expectedOutput );
        Set_ActualOutput    ( "m_arraySize", actualOutput );

        if ( actualOutput != actualOutput )     { TestFail(); } 
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure data is copied over to resized array" ); {
        Set_Comments( "" );
        SmartDynamicArray sd;
        sd.AllocateMemory( 5 );

        string expectedOutputs[] = { "A0", "A1", "A2", "A3", "A4" };

        for ( int i = 0; i < 5; i++ )
        {
            sd.Push( expectedOutputs[i] );
        }

        sd.Resize( 10 );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 5; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )                    { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure we can add more data after resize" ); {
        Set_Comments( "" );
        SmartDynamicArray sd;
        sd.AllocateMemory( 5 );

        string expectedOutputs[] = { "A0", "A1", "A2", "A3", "A4", "B0", "B1" };

        for ( int i = 0; i < 5; i++ )
        {
            sd.Push( expectedOutputs[i] );
        }

        sd.Resize( 10 );

        sd.Push( "B0" );
        sd.Push( "B1" );

        // Verify
        bool allMatch = true;
        for ( int i = 0; i < 7; i++ )
        {
            string expectedOutput = expectedOutputs[i];
            string actualOutput = sd.m_data[i];
            
            Set_ExpectedOutput  ( "Item " + StringUtil::ToString( i ), expectedOutput );
            Set_ActualOutput    ( "Item " + StringUtil::ToString( i ), actualOutput );

            if ( expectedOutput != actualOutput )
            {
                allMatch = false;
            }
        }

        if ( allMatch == false )                    { TestFail(); }
        else                                        { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_IsFull()
{
    StartTestSet( "Test_IsFull", { "IsFull", "Resize", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsFull returns false for new array with AllocateMemory already called" ); {
        Set_Comments( "Created new empty SmartDynamicArray, called AllocateMemory" );
        bool expectedOutput, actualOutput;
        
        SmartDynamicArray sd1;
        sd1.AllocateMemory();

        expectedOutput = false;
        actualOutput = sd1.IsFull();

        Set_ExpectedOutput  ( "Is full:", expectedOutput );
        Set_ActualOutput    ( "Is full:", actualOutput );

        if ( expectedOutput != actualOutput )   { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsFull returns false for an array with a few items" ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed a few items" );
        bool expectedOutput, actualOutput;
        
        SmartDynamicArray sd1;
        sd1.Push( "HI" );
        sd1.Push( "..." );
        sd1.Push( "SUP?" );

        expectedOutput = false;
        actualOutput = sd1.IsFull();

        Set_ExpectedOutput  ( "Is full:", expectedOutput );
        Set_ActualOutput    ( "Is full:", actualOutput );

        if ( expectedOutput != actualOutput )   { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsFull returns true once it hits 10 items (before any resize)" ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed 10 items" );
        bool expectedOutput, actualOutput;
        
        SmartDynamicArray sd1;
        for ( int i = 0; i < 10; i++ )
        {
            sd1.Push( "YO" );
        }
        expectedOutput = true;
        actualOutput = sd1.IsFull();

        Set_ExpectedOutput  ( "Is full:", expectedOutput );
        Set_ActualOutput    ( "Is full:", actualOutput );

        if ( expectedOutput != actualOutput )   { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsFull returns false once it hits 11 items (after resize)" ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed 11 items" );
        bool expectedOutput, actualOutput;
        
        SmartDynamicArray sd1;
        for ( int i = 0; i < 11; i++ )
        {
            sd1.Push( "YO" );
        }
        expectedOutput = false;
        actualOutput = sd1.IsFull();

        Set_ExpectedOutput  ( "Is full:", expectedOutput );
        Set_ActualOutput    ( "Is full:", actualOutput );

        if ( expectedOutput != actualOutput )   { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure IsFull returns false once it hits 20 items (after resize)" ); {
        Set_Comments( "Created new empty SmartDynamicArray, pushed 20 items" );
        bool expectedOutput, actualOutput;
        
        SmartDynamicArray sd1;
        for ( int i = 0; i < 20; i++ )
        {
            sd1.Push( "YO" );
        }
        expectedOutput = true;
        actualOutput = sd1.IsFull();

        Set_ExpectedOutput  ( "Is full:", expectedOutput );
        Set_ActualOutput    ( "Is full:", actualOutput );

        if ( expectedOutput != actualOutput )   { TestFail(); }
        else                                    { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

int Tester::Test_Size()
{
    StartTestSet( "Test_Size", { "Size", "Resize", "Push" } );

    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Make sure Size is 0 for new SmartDynamicArray" ); {
        Set_Comments( "Created empty SmartDynamicArray" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;

        expectedOutput = 0;
        actualOutput = sd.Size();

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should be 1 after one Push" ); {
        Set_Comments( "Created empty SmartDynamicArray, Pushed 1" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "NO" );

        expectedOutput = 1;
        actualOutput = sd.Size();

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should be 2 after two Push" ); {
        Set_Comments( "Created empty SmartDynamicArray, Pushed 2" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Push( "NO" );
        sd.Push( "NO" );

        expectedOutput = 2;
        actualOutput = sd.Size();

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    StartTest( "Size should be the same after resize (the m_itemCount)" ); {
        Set_Comments( "Created empty SmartDynamicArray, called Resize" );
        int expectedOutput, actualOutput;

        SmartDynamicArray sd;
        sd.Resize( 15 );

        expectedOutput = 0;
        actualOutput = sd.Size();

        Set_ExpectedOutput  ( "m_itemCount", expectedOutput );
        Set_ActualOutput    ( "m_itemCount", actualOutput );

        if ( expectedOutput != actualOutput )     { TestFail(); }
        else                                      { TestPass(); }
    } FinishTest();

    FinishTestSet();
    return TestResult();
}

#endif
