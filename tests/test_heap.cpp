#include <catch2/catch_test_macros.hpp>

#include "Heap.h"

TEST_CASE( "Sanity", "[heap]" ) 
{
    heap::Heap<int> h;

    heap::Heap<int>::ContainerType testCase = {4,2,6,8,1};
    heap::Heap<int>::ContainerType expectedResult = {8,6,4,2,1};
    
    for(auto element: testCase)
    {
        h.Push(element);
    }

    for(auto element: expectedResult)
    {
        REQUIRE_FALSE(h.IsEmpty());
        REQUIRE(h.Top() == element);

        h.Pop();
    } 
}
