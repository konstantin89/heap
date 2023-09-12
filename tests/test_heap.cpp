#include <catch2/catch_test_macros.hpp>
#include "Heap.h"

#include <functional>
#include <algorithm>

class TestClass
{
public:
    TestClass(std::string s, int i): s(s), i(i) 
    {

    }

    ~TestClass() = default;

    bool operator>(const TestClass& other) const {
        return i > other.i;
    }

    std::string s;
    int i;
};

template <typename DataType>
static void CommonTestCase(typename heap::Heap<DataType>::ContainerType dataSet, 
                           typename heap::Heap<DataType>::ContainerType expectedPopOrder)
{
    heap::Heap<int> heapStructure;

    for(auto element: dataSet)
    {
        heapStructure.Push(element);
    }

    for(auto popElement: expectedPopOrder)
    {
        REQUIRE_FALSE(heapStructure.IsEmpty());
        REQUIRE(heapStructure.Top() == popElement);

        heapStructure.Pop();
    } 
}

TEST_CASE( "Sanity", "[heap]" ) 
{
    heap::Heap<int>::ContainerType testCase = {4,2,6,8,1};
    heap::Heap<int>::ContainerType expectedResult = {8,6,4,2,1};

    CommonTestCase<int>(testCase, expectedResult);
}

TEST_CASE( "Duplicate elements", "[heap]" ) 
{
    heap::Heap<int>::ContainerType testCase = {4,2,6,8,1,4};
    heap::Heap<int>::ContainerType expectedResult = {8,6,4,4,2,1};
    
    CommonTestCase<int>(testCase, expectedResult);
}

TEST_CASE( "Complex int set", "[heap]" ) 
{
    heap::Heap<int>::ContainerType testCase = {2,0,34,1,5,6,7,8,23,12,34,45,56,4,2,6,8,1,45,23,12,7,4,12,34,56,34,23,12,45,56,67};

    heap::Heap<int>::ContainerType expectedResult = testCase;
    std::sort(expectedResult.begin(), expectedResult.end(), std::greater<int>());
    
    CommonTestCase<int>(testCase, expectedResult);
}

TEST_CASE( "Emplace", "[heap]" ) 
{
    heap::Heap<TestClass> heapStructure;
    heapStructure.Emplace("Hello", 5);
    heapStructure.Emplace("World", 6);

    REQUIRE(heapStructure.Top().i == 6);
    heapStructure.Pop();

    REQUIRE(heapStructure.Top().i == 5);
    heapStructure.Pop();

    REQUIRE(heapStructure.IsEmpty());
}
