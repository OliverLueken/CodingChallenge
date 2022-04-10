/*
Test cases to test the functionality of myList
*/

#include <ranges>
#include <algorithm>

#include "catch.hpp"
#include "myList.hpp"



TEST_CASE("List creation"){

    SECTION("Create list with one element"){
        auto head = myList::make_list(1);
        REQUIRE(head->value == 1 );
        REQUIRE(head->next  == nullptr );
        myList::delete_list(head);
        REQUIRE(head == nullptr );
    }

    SECTION("Create list with two elements"){
        auto head = myList::make_list(1, 2);

        auto currentNodePtr = head;
        REQUIRE(currentNodePtr->value == 1 );
        REQUIRE(currentNodePtr->next  != nullptr );

        currentNodePtr = currentNodePtr->next;
        REQUIRE(currentNodePtr->value == 2 );
        REQUIRE(currentNodePtr->next  == nullptr );

        myList::delete_list(head);
        REQUIRE(head == nullptr );
    }

    SECTION("Create list with a lot of elements"){
        auto head = myList::make_list(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

        auto currentNodePtr = head;
        int expectedValue = 1;
        while(currentNodePtr != nullptr){
            REQUIRE(currentNodePtr->value == expectedValue );
            currentNodePtr = currentNodePtr->next;
            ++expectedValue;
        }

        myList::delete_list(head);
        REQUIRE(head == nullptr );
    }
}


TEST_CASE("advance"){
    auto head = myList::make_list(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    SECTION("Advance zero steps"){
        auto sameAsHeadPtr = advance(head, 0);
        REQUIRE(sameAsHeadPtr == head);
    }

    SECTION("Advance one steps"){
        auto nextNodePtr = advance(head, 1);
        REQUIRE(nextNodePtr == head->next);
    }

    SECTION("Advance more steps"){
        auto steps   = GENERATE(range(1,15));
        auto nodePtr = advance(head, steps);
        REQUIRE(nodePtr->value == steps+1);
    }

    SECTION("Advance multiple times"){
        auto firstStep  = GENERATE(range(1,5));
        auto secondStep = GENERATE(range(1,5));
        auto nodePtr       = advance(head,    firstStep );
        auto secondNodePtr = advance(nodePtr, secondStep);
        REQUIRE(secondNodePtr->value == firstStep+secondStep+1);
    }

    SECTION("Advance beyond list"){
        auto nodePtr = advance(head, 16);
        REQUIRE(nodePtr == nullptr);

        auto anotherNodePtr = advance(head, 17);
        REQUIRE(anotherNodePtr == nullptr);
    }

    myList::delete_list(head);
}


TEST_CASE("reverse list"){
    SECTION("Reverse list with one element"){
        auto head = myList::make_list(1);
        auto newHead = myList::reverse_list(head);

        REQUIRE(newHead == head );

        REQUIRE(newHead->value == 1 );
        REQUIRE(newHead->next  == nullptr );

        myList::delete_list(newHead);
        REQUIRE(newHead == nullptr );
    }

    SECTION("Reverse list with two elements"){
        auto head = myList::make_list(1, 2);
        auto newHead = myList::reverse_list(head);

        REQUIRE(head->value == 1 );
        REQUIRE(head->next  == nullptr );

        auto currentNodePtr = newHead;
        REQUIRE(currentNodePtr->value == 2 );
        REQUIRE(currentNodePtr->next  != nullptr );

        currentNodePtr = currentNodePtr->next;
        REQUIRE(currentNodePtr->value == 1 );
        REQUIRE(currentNodePtr->next  == nullptr );

        myList::delete_list(newHead);
        REQUIRE(newHead == nullptr );
    }

    SECTION("Reverse list with a lot of elements"){
        auto head = myList::make_list(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        auto newHead = myList::reverse_list(head);

        REQUIRE(head->value == 1 );
        REQUIRE(head->next  == nullptr );

        auto currentNodePtr = newHead;
        int expectedValue = 16;
        while(currentNodePtr != nullptr){
            REQUIRE(currentNodePtr->value == expectedValue);
            currentNodePtr = currentNodePtr->next;
            --expectedValue;
        }

        myList::delete_list(newHead);
        REQUIRE(newHead == nullptr );
    }
}

auto valuesAreReversedAsExpected(myList::Node<int>* head, const int size, int k){
    if( k==0 ){
        k=1;
    }
    const auto numberOfGroups = size/k;
    auto currentNodePtr = head;

    auto groupIsReversed = [&currentNodePtr, k](const auto group){
        auto hasExpectedValue = [&currentNodePtr, k, group](const auto nodeInGroup){
            const auto expectedValue = (group+1)*k-nodeInGroup;
            const auto currentValue  = currentNodePtr->value;
            currentNodePtr = currentNodePtr->next;
            return expectedValue == currentValue;
        };
        auto nodesInGroup = std::views::iota(0, k);
        return std::ranges::all_of(nodesInGroup, hasExpectedValue);
    };
    auto groups = std::views::iota(0, numberOfGroups);
    auto groupsReversed = std::ranges::all_of(groups, groupIsReversed);


    auto hasExpectedValue = [&currentNodePtr](const auto expectedValue){
        const auto currentValue = currentNodePtr->value;
        currentNodePtr = currentNodePtr->next;
        return expectedValue == currentValue;
    };
    auto lastElements = std::views::iota( std::min(numberOfGroups*k+1, size), size );
    auto lastElementsUnreversed = std::ranges::all_of(lastElements, hasExpectedValue);

    return groupsReversed && lastElementsUnreversed;
}

template<typename... ListValues>
auto test_reverse_group(unsigned int k, ListValues&&... values){
    auto head = myList::make_list(std::forward<ListValues>(values)...);

    std::cout << "Reversing groups with k = " << k << '\n';
    std::cout << "Before ";
    myList::print(head);

    head = myList::reverse_groups(head, k);
    std::cout << "After  ";
    myList::print(head);
    std::cout << '\n';

    const auto size = sizeof...(ListValues);
    const auto reverse_group_successful = valuesAreReversedAsExpected(head, size, k);

    myList::delete_list(head);
    return reverse_group_successful;
}

TEST_CASE("Reverse_group"){
    auto k = GENERATE(range(0,17));
    REQUIRE( test_reverse_group(k, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) );
}