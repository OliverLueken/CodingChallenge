/*
Test cases to test the functionality of myList
*/

#include "catch.hpp"
#include "myList.hpp"



TEST_CASE("List creation", "[generators]"){

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



