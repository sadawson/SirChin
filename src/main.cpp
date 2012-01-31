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
   This is the front-end on the engine. It will take the text file
   input then create, fill and use an wordList object used by
   
   File: WordList.cpp
   Other files:
      - /wordList.h > The corr. header file
      - /main.cpp > The front end on the engine that will take the text file
                     input then create and use obects its created
      - ../docs/assignment3.pdf > Problem Statement/Design Brief
      - ../bin/sirChin.exe > Win32 binary last compiled 30/01/07 16:12
      - ../bin/sirChin.bin > Linux compatible binary compiled 22/01/07 22:42
      - ../bin/data.txt > The file that is going to have it inputed
\*                                                                            */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "wordList.h"
#include <ctime>
using namespace std;

int main()
{
   //=========================== Declarations ==================================
      int startTime=time(NULL);
      //the time that the program start
   
      wordList wL;
      //This is an object that will store and compute queries on
   
      ifstream inData("data.txt");
       //Open the file specified at the path bellow
      if( !inData ) 
         cerr << "No file exists!" << endl;
      // if there is an error alert user

      string temp;
      //stores the current line you are working with
      
      bool addingWords=true;
      //a flag:
      //   true : adding words to the list
      //   false : querying words in the list
   //===========================================================================

   //Read the file into the the program to be processed

   while (inData>>temp)
   //step through input file a line at a time until eof
   {
      if (addingWords)
      // add words until either "*" indicateds time to start doing queries
      // or a "#" signals eof
      {
         if (temp=="*")
         //end of adding words to word list
         {
            addingWords=false;
         }//end if
         else if (temp!="#")
         //if not end of the file only thing it could be is another word for list
         {
            wL.add(temp);
         }//end if
      }
      else
      //perform queries on list 
      {
         if (temp=="**")
         //end of queries
         {
            addingWords=true;
            wL.clear();
            //clear the wordlist
            cout<<"$"<<endl;
         }//end if
         else if (temp!="#")
         //print the result of querieing with the current line of text
         //from the input file as the query
         {
            cout<<wL.query(temp)<<endl;
         }//end else if
         else
         //it has completed clear the last one
         {
            wL.clear();
         }//end else
      }//end else
   }//end loop

   cout<<"Execution time: "<<time(NULL)-startTime<<endl;
   //display execution time

   system("PAUSE");
   return EXIT_SUCCESS;
}//end main

