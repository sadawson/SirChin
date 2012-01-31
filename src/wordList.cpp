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
   This is the implementaion file for a linked list of words. With some 
   methods that correspond to the task.
   
   File: WordList.cpp
   Other files:
      - ./wordList.h > The corr. header file
      - ./main.cpp > The front end on the engine that will take the text file
                     input then create and use obects its created
      - ../docs/assignment3.pdf > Problem Statement/Design Brief
      - ../bin/sirChin.exe > Win32 binary last compiled 23/01/07 16:35
      - ../bin/sirChin.bin > Linux compatible binary compiled 22/01/07 22:42
      - ../bin/data.txt > The file that is going to have it inputed
\*                                                                            */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "wordList.h"


void wordList::add(string item)
//inserts item into alphabetical order
{
   createNode(item);
   //creates an sNode2 that temp is now pointing to
   
   if (head!=NULL)
   //the list is not empty
   {
      if (temp->data<head->data)
      //if the new node is smaller than head,
      //    its got to be the new head
      {
         prepend(item);
      }//end if head
      else if (temp->data>tail->data)
      //if the new node is bigger than tail,
      //    its got to be the new tail
      {  
         append(item);
      }//end if new tail
      else
      //the general case got to work out where it has to go
      {
         sNode2* i;
         //pointer used to traverse the list
         
         bool added=false;
         //a flag to stop the loop once its beed added         

         i=head;
         //point at the head to start with

         while (i!=NULL && !added)
         //step through the list while you havnt found a place to put the 
         //the new node
         {
            if (temp->data < i->data)
            //if item < *i it goes on the left of *i
            {
               added=true;
               i->previous->next=temp;
               temp->next=i;
               temp->previous=i->previous;
               i->previous=temp;
            }//end if
            i=i->next;
            //iterative step
         }//end loop
      }//end general case
   }//end if not empty
   else
   //the list is empty
   {
      head=temp;
      tail=temp;
   }//end else
}//end orderedInsert

string wordList::query (string inString)
//returns the word lexigraphically in the word list that satisfies the
//query if there is none that satifies it the word none is displayed on
//the screen.
{
   vector <srtQuery> vQueries;
   //this will store all the queries

   srtQuery vTempQuery;
   //a temp struct that will be used to push the queries into vQueries
   
   for (int i=0;i<inString.size();i++)
   //step though in string
   {
      if (inString.at(i)=='+')
      {
         vTempQuery.mustHave.push_back(inString.at(i+1));
         //add the letter
         i++;
         //skip it so it dont get checked and you end up double dipping
      }//end else if
      else if (inString.at(i)=='-')
      {
         vTempQuery.cantHave.push_back(inString.at(i+1));
         //add the letter
         i++;
         //skip it so it dont get checked and you end up double dipping
      }//end else if
      else if (inString.at(i)=='|')
      //you have gotten to the end of that query add it to the vector of
      //queries and clear the temps incase there is more to be added
      {
         vQueries.push_back(vTempQuery);
         vTempQuery.atLeast.clear();
         vTempQuery.cantHave.clear();
         vTempQuery.mustHave.clear();
      }//end else if
      else
      //only leaves the letters that form the at least part of the query
      {
         vTempQuery.atLeast.push_back(inString.at(i));
      }//end else
   }//end for

   vQueries.push_back(vTempQuery);
   //push on the last one.

   init_tList();
   //gets the tList ready to be traveresed

   return queryWL(vQueries);
   //The vasade has served its purpose everything is now in a vector that is
   //easily traverseable now to query the wordlist

}//end query

string wordList::queryWL (vector <srtQuery> &inQueries)
//returns the word lexigraphically in the word list that satisfies the
//query if there is none that satifies it the word NONE is displayed on
//the screen.
{
   string returnString;
   returnString="NONE";
   //this is a flag it will remain unchanged until a query has a solution found

   sNode2* solution;
   solution=NULL;
   //this pointer poitns to the lexigraphically smallest word int he lsit
   //that can solve the query
   
   for (int iQ=0;iQ<inQueries.size();iQ++)
   //step though each query
   {
      for (int iMH=0;iMH<inQueries[iQ].mustHave.size();iMH++)
      //step through all the mustHave characters 
         removeManyWords('+',inQueries[iQ].mustHave[iMH]);

      for (int iCH=0;iCH<inQueries[iQ].cantHave.size();iCH++)
      //step through all the cantHave characters
         removeManyWords('-',inQueries[iQ].cantHave[iCH]);   

      for (int iAL=0;iAL<inQueries[iQ].atLeast.size();iAL++)
      //step through all the atLeast characters
         removeManyWords(inQueries[iQ].atLeast);

      if (tHead!=NULL) 
      //if it is pointing to something that something satisfies the query
      {
         if (solution!=NULL) 
         //if there has been of others
         {
            if (solution->data>tHead->data) 
            //if the new solution is lexigraphicalled smaller
            {
               solution=tHead;
            }//end if
         }
         else 
         {
            solution=tHead;
         }//end else
      }//end if
 
      if (iQ!=inQueries.size()-1)
      //if there are more queries need to set them up
         if (solution==NULL)
         //no solution have ever been found
            init_tList();
         else if (head==solution)
         //if the head solves the query then there is nothing else in the list
         //that could possibly solve it and be lexigraphically before it
            return head->data;
         else
            init_tList(solution->previous);
   }//end loop queries
   
   if (solution!=NULL)
   //providing there are some solutions
   {
      returnString=solution->data;
      //set the flag
   }//end if

   return returnString;
}//end Query Word List

void wordList::clear()
//removes all nodes from the list
{
   if (tail!=NULL)
   {
      if (head==tail)
      //last item
      {
         //free (head);
         // was an attempt at fixing a memory leak but failed
         delete head;
         head=NULL;
         tail=NULL;
      }//end last term
      else
      //there is more than one
      {
         temp=tail->previous;
         //free (tail);
         // see above
         delete tail;
         tail=temp;
         clear();
      }//end delete general
   }//end there is something in the list
}//end clear

void wordList::createNode(string item)
//creates a node that temp will point to
{
   temp=new sNode2;
   temp->data=item;
   temp->next=NULL;
   temp->previous=NULL;
   temp->tNext=NULL;
   temp->tPrevious=NULL;
}//end createNode

void wordList::displayAll()
//displays the contents of the linked list on the screen
//a debuging function
{
   for (temp=head; temp!=NULL; temp=temp->next)
      cout<<temp->data<<" ";
   cout<<endl;
}//end displayAll

void wordList::append(string item)
//adds item to the end of the list
{
   //temp is pointing ot the node that needs to be added
   tail->next=temp;
   temp->previous=tail;
   tail=temp;
}//end append

void wordList::prepend(string item)
//adds an item to the begining of the list
{
   //temp is pointing to the node that needs adding
   head->previous=temp;
   temp->next=head;
   head=temp;
}//end prepend

void wordList::init_tList()
//sets up the pointers that will be used by the query algorthm for traversing the
//the data structure.
{
   tHead=head;
   tTail=tail;
   tHead->tPrevious=NULL;
   tTail->tNext=NULL;
   for (temp=head; temp!=NULL;temp=temp->next)
   {
      temp->tNext=temp->next;
      temp->tPrevious=temp->previous;
   }//end for
}//end init_tList

void wordList::init_tList(sNode2* lastNode)
//sets up the pointers that will be used by the query algorthm for traversing the
//the data structure.
//Parameter denotes the last item that could possible solve the query.
{
   for (temp=head; temp!=NULL && temp!=lastNode ;temp=temp->next)
   //step though list until either the end or the lastNode
   {
      temp->tNext=temp->next;
      temp->tPrevious=temp->previous;
   }//end for
   tHead=head;
   tTail=lastNode;
   tHead->tPrevious=NULL;
   tTail->tNext=NULL;
}//end init_tList

bool wordList::containsLetter(string inString, char ch)
//returns true iff the string inString has a character that is equivalent to
//the character ch
{
   bool found=false;
   //a flag that will store wether or not an item has been found

   for (int i=0; i<inString.size() && !found; i++)
   //step through string until the end or if you find the char your looking for
      if (inString.at(i)==ch)
         found=true;

   return found;
   // return true iff ch is in inString
   //     reason it is false by defaul will only become true when ch is found inside inString
}//end containsLetter

void wordList::removeManyWords (char operation, char ch)
//'removes' from the list any words that either have, don't have a
//specifed char
//   operation "+" : only words that have the char will remain
//   operation "-" : only words that don't have the char will remain
{
   sNode2* tI;
   for (tI=tHead;tI!=NULL;tI=tI->tNext)
   {  
      if (operation=='+'&&!containsLetter(tI->data,ch)
         //the word has to have ch and it doesnt
         || //or
         operation=='-'&&containsLetter(tI->data,ch))
         //the word cant have ch and it doesnt  
      {
         temp=tI;
         removeWord();
      }//end if
   }//end for
}//end removeManyWords

void wordList::removeManyWords (vector <char> inChars)
//remvoes from the tList any words that don't contain atLeast one
// of the chars in the inChars Vector
{
   bool foundLetter=false;
   //a flag
   sNode2* tI;
   for (tI=tHead;tI!=NULL;tI=tI->tNext)
   //step through words
   {
      for (int i=0;i<inChars.size()&&!foundLetter;i++)
      //step through chars      
      {
         if (containsLetter(tI->data,inChars[i]))
         //if the word contains one of the required letters its found
         {
            foundLetter=true;
         }//end if
      }//end for
      if (!foundLetter)
      //The word that tI points to doesnt contain at least one
      {
         temp=tI;
         removeWord();
      }
      foundLetter=false;
   }//end for
}//end removeManyWords

void wordList::removeWord()
//removes the word in tList that temp is poitning to
{ 
   if (tHead == tTail && tHead!=NULL && temp==tHead )
   //there is only one item left
   {
      tHead=NULL;
      tTail=NULL;
   }
   else if (temp == tHead)
   //need to get rid of the head
   {
      tHead=tHead->tNext;
      tHead->tPrevious=NULL;
   }
   else if (temp == tTail)
   //need to get rid of the tail
   {
      tTail=temp->tPrevious;
      tTail->tNext=NULL;
   }
   else
   //general case
   {
      temp->tNext->tPrevious=temp->tPrevious;
      temp->tPrevious->tNext=temp->tNext;
   }
}//end remove word

wordList::wordList()
//default constructor for the list
{
   head=NULL;
   tail=NULL;
   tHead=NULL;
   tTail=NULL;
   temp=NULL;
}//end cnostrcutor

wordList::~wordList()
//destuctor for the list
//could be made more effient
{
  clear();
}//end destructor
 
