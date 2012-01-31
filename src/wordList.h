/*                                                                            *\
   (c)2007 Simon Anthony Dawson
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2, or (at your option) any later
   version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   This notice must stay intact for legal use
\*                                                                            */

/*                                                                            *\
  Name: Finding the Chinese Knight
  Version: 1.0 release candidate 1
  Author: Simon Dawson
  Date: 17/01/07 16:24
  Description:
      For the purpose of this assignment, a query is a sequence of one or more
terms. Queries are separated by single vertical bars (\|"). A search term is
one or more letters followed by zero or more signed letters. A signed letter
is either +s (`positive" s) or -s (\negative" s), where s is a single letter. 
All letters in the query are lowercase, and no letter will appear more than once
within a term. A query will not contain spaces.

A term matches a word if the word contains at least one of the unsigned
letters, all of the positive letters, and none of the negative letters; a query
matches a word if at least one of its terms matches the word.

   This is the header file for a linked list of words. With some methods
   That correspond to the task.
   
   File: WordList.h
   Other files:
      - /wordList.cpp > Implementaion file for this header
      - ../docs/assignment3.pdf > Problem Statement/Design Brief
      - /main.cpp > The front end on the engine that will take the text file
               input then create and use obects its created
      - ../src/sirChin.exe > Win32 binary last compiled 23/01/07 16:35
      - ../src/sirChin > Linux compatible binary compiled 22/01/07 22:42
      - ../bin/data.txt > The file that is going to have it inputed
\*                                                                            */

#ifndef _WORDLIST_H
#define _WORDLIST_H

#include <string>
#include <vector>
using namespace std;

struct sNode2
// This is the building block of the project these little ones will join
// together and be replcated and used to display the results of the queries
{
   string data;
   //the word

   sNode2* next;
   //the next node in the list

   sNode2* previous;
   //the previous node in the list

   sNode2* tNext;
   //the next node in the list of possible solutions to a query
   //This is a pointer that will be used to TRAVERSE the list for the purpose
   //of solving the queries problem

   sNode2* tPrevious;
   //the previous node in the list of possible solutions to a query
   //This is a pointer that will be used to TRAVERSE the list for the purpose
   //of solving the queries problem

};//end struct sNode2

struct srtQuery
// This is a way of bundeling up all the components in a query together
{
   vector <char> atLeast;
   //a vector storing all the unsigned characters
   vector <char> mustHave;
   //a vector storing all the characters signed with a +
   vector <char> cantHave;
   //a vector storing all the characters signed with a -
};//end struct srtQuery

class wordList
{
   public:
      wordList();
      //default constructor for the list
      
      void add(string item);
      //inserts item into alphabetical order

      string query (string inString);
      //returns the word lexigraphically in the word list that satisfies the
      //query if there is none that satifies it the word NONE is displayed on
      //the screen.
      // This function is a vasade that will take the string input and make it
      // more managable

      void clear();
      //removes all nodes from the list recursivly

      ~wordList();
      // destuctor calls the clear function
      

   private:
      sNode2* head;
      //the first entry in the list
      
      sNode2* tail;
      //the last entry it points to

      sNode2* tHead;
      //the first entity in the list that possibly can solve the query
      
      sNode2* tTail;
      //the last entity in the list that possibly can solve the query

      sNode2* temp;
      //your "bitch", the work horse of this thing

      string queryWL (vector <srtQuery> &inQueries);
      //returns the word lexigraphically in the word list that satisfies the
      //query if there is none that satifies it the word NONE is displayed on
      //the screen.

      void append(string item);
      //adds item to the end of the list
      
      void prepend(string item);
      //adds an item to the begining of the list
   
      void init_tList();
      //sets up the pointers that will be used by the query algorthm for traversing the
      //the data structure

      void init_tList(sNode2* lastNode);
      //sets up the pointers that will be used by the query algorthm for traversing the
      //the data structure
      //The list of traversable nodes ends at lastNode

      void createNode(string item);
      //creates a node that temp will point to

      bool containsLetter(string inString, char ch);
      //returns true iff the string inString has a character that is equivalent to
      //the character ch

      void removeManyWords (char operation, char ch);
      //'removes' from the list any words that either have, don't have a
      //specifed char
      //   operation "+" : only words that have the char will remain
      //   operation "-" : only words that don't have the char will remain

      void removeManyWords (vector <char> inChars);
      //remvoes from the tList any words that don't contain atLeast one
      // of the chars in the inChars Vector      

      void removeWord();
      //removes the word in tList that temp is poitning to

       void displayAll();
      //displays the contensts of the list iff there is anything to show

};// end WordList class

#endif


