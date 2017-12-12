# cuTEST

By Rachel Morris!

## About

This is a testing framework I've written to use in my C++ programming classes...
*CS 200: Concepts of Programming Algorithms using C++* and
*CS 250: Data Structures using C++*.

## Usage

Note: This requires building with c++11 flags (or later... using function pointers).
Make sure to build with ```-std=c++11``` or similar.

Build the program, with **test.cpp** as the file that contains main().
When it is run, a file called **test_result.txt** will be generated with
the output of all the tests.

I will usually clone this repository into my project directory,
so that cuTEST is a subdirectory, one level up from my project's source files.

### Creating the Tester file

Copy the **TestTemplate.hpp** file into the directory where you have
the classes you want to test, and rename it **Tester.hpp**.

### Setting up the Tester

This Tester file should ```#include``` the .h/.hpp file of the class you're
going to be testing out.

Within the constructor, you will add a test like this:

```c++
AddTest(TestListItem("TEST_LABEL",             bind(&Tester::TestFunction, this)));
```

Where your ```TestFunction``` is a member function of the Tester.
You will also need to declare your function(s) within the Tester class.

You can define the functions at the bottom of the file if you want.

### Test anatomy

The ```TesterBase``` has some functions you can use to make it easier on yourself.
For example:

```c++
int Tester::ExampleTest()
{
    InitTest( "ExampleTest", { "Prerequisite1", "Prerequisite2" } );

    StartTest( "This_is_test_1" );
    if ( 0 == 1 )
    {
        TestFail();
        ReportFailure( "ExampleTest_Test1", "0_equal_to_1" );
    }
    else if ( 0 == 2 )
    {
        TestFail();
        ReportFailure( "ExampleTest_Test1", "0_equal_to_2" );
    }
    else
    {
        TestPass();
    }

    DisplayScore();
    return TestResult();
}
```

<table>
<tr>
<th> InitTest </th>
<td>
Parameters:

1. Label for test (shows up in output)
2. List of prerequisite functions (i.e., functions that need to be implemented for the test to work) - also shows up in the output.
</td>
</tr>

<tr>
<th> StartTest </th>
<td>
For each test that you have in this function, you can start it with this header.
This is also just outputted to the text file, and a more useful way than just separating
out your sub-tests with comments.

This also adds to the *m_subtest_totalTests* variable in TesterBase.
</td>
</tr>

<tr>
<th> TestFail() </th>
<td>
Doesn't actually do anything right now!
</td>
</tr>

<tr>
<th> TestPass() </th>
<td>
Incremenets the internal *m_subtest_totalPasses* variable in TesterBase.

You should only have one **TestPass** per **StartTest**, so your
pass should be in the *else* statement in a block of checks for
failure cases.
</td>
</tr>

<tr>
<th> ReportFailure() </th>
<td>
There are several versions of this function, which you can use to let the user
know what went wrong in the test.

```c++
void ReportFailure( const string& test, const string& message, const string& expected, const string& actual );
void ReportFailure( const string& test, const string& message, int expected, int actual );
void ReportFailure( const string& test, const string& message, float expected, float actual );
void ReportFailure( const string& test, const string& message );
void ReportFailure( const string& message );
```
</td>
</tr>

<tr>
<th> DisplayScore() </th>
<td>
This writes out the total tests passed / total tests statistic.
</td>
</tr>

<tr>
<th> TestResult() </th>
<td>
Returns 

```c++
( m_subtest_totalPasses == m_subtest_totalTests )
```

In other words: 1 if all tests pass, 0 if not.
</td>
</tr>

</table>

