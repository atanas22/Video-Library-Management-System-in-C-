# Video-Library-Management-System-in-C-
C++ console application

The system lets you to:
1. Add/delete members/cassettes
2. Search members/cassettes
3. Display all cassettes/members
4. Rent/return cassettes
5. Show out of date rented cassettes and the members who rente them

Every member has the following data:
1. Unique ID
2. Name
3. Phone number
4. Address
5. Card validity
6. And a list with the names of the cassettes the member has rented 
   and also the period of allowed usage of a cassette (rent and end dates) with their charges

*if a member doesn't return a cassette within the period of 7 days- then he will be charged with 0.50lv a day

Every cassette has the following data:
1. Name
2. info
3. total number
4. left number cassettes of this cassette in the library
5. the people who rent this cassette and also the period of allowed usage of a cassette (rent and end dates) with their charges

* After closing the system (correctly) - it saves the data
* The system also checks for wrong entered user values 
* There is already entered some data into the system
