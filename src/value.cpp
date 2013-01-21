/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This file holds the methods to the value object. It's only
   job is to act as a simple ADT to store student marks

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <qmessagebox.h>
#include "value.h"
using namespace std;
// Init
Value::Value() {
   index = 0;
}

// Deconstructor
Value::~Value() {
   // deconstructor
}

// Push value on to the stack
void Value::PushValue(const char nvalue) {
   value[index++] = nvalue;
}

// Pop Value from the stack
QChar Value::PeekValue() {
   return value[index];
}

// Deletes a value with the index given. also move the data down and index--
void Value::ReplaceValue(int nindex, char nvalue) {
   if(nindex < index)
      value[nindex] = nvalue;
   else {
      QMessageBox::critical(0,"Infobot",
      "Trying to accessing non-existing value\n"
      "The system will now save and close, sorry for any inconveniance\n"
      "contact your vendor emediatly quoting error code AFQW242\n");
      exit(AFQW242);
   }
}

// Removes the top value
void Value::PopValue() {
   if(index>0) {
      value[index] = NULL;
      index--;
   }
}

// Get the Value index.. pop does not remove the index--
int Value::PeekValueIndex() {
   return index;
}

// Get the value within the given index
QChar Value::PeekValue(int nindex) {
   if(index > nindex)
       return value[nindex];
   else {
      QMessageBox::critical(0,"Infobot",
      "Trying to access non-existing value\n"
      "The system will now save and close, sorry for any inconveniance\n"
      "contact your vendor emediatly quoting error code AFQW243\n");
      exit(AFQW243);
      return ' ';
   }
}

// Gets the full string value
QChar* Value::PeekAllValues() {
   if(index>0)
      return value;
   return NULL;
}

// Checks if the list is empty
bool Value::IsEmptyIndex() {
   return (index == 0);
}


