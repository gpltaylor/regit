/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

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
#include "behaviour.h"
using namespace std;
// Init
Behaviour::Behaviour() {
   index = 0;
}

// Deconstructor
Behaviour::~Behaviour() {
   // deconstructor
}

// Push value on to the stack
void Behaviour::PushBehaviour( const QString nvalue ) {
   if( strlen(nvalue) > NOTESIZE ) {
      QMessageBox::critical(0, "Infobot",
      "Your comment is to big\n"
      "This comment will not be added\n"
      "Please reduce comment size");
      return;
   }
   note[index++] = nvalue;
}

// Deletes a value with the index given. also move the data down and index--
void Behaviour::ReplaceBehaviour( int nindex, const QString nvalue ) {
   if( strlen(nvalue) > NOTESIZE ) {
      QMessageBox::critical(0, "Infobot",
      "Your comment is to big\n"
      "This comment will not be added\n"
      "Please reduce comment size");
      return;
   }

   if( nvalue.isNull() )
      return;
   if( index > nindex ) {
      note[nindex] = nvalue;
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Replacing behaviour has overflown your memmory\n"
      "The system will now save and close, sorry for any inconveniance\n"
      "contact your vendor emediatly quoting error code AFQW235\n");
      exit(AFQW235);
   }
}

// Removes the top value
void Behaviour::PopBehaviour(int nindex) {
   if(index>0) {
      note[nindex] = "No Comment";
   }
}

// Removes the top index
void Behaviour::PopBehaviour() {
    index= index-1;
}


// Pop Value from the stack
const QString Behaviour::PeekBehaviour() {
   if(index > index) {
       return note[index];
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Viewing behaviour has overflown your memmory\n"
      "The system will now save and close, sorry for any inconveniance\n"
      "contact your vendor emediatly quoting error code AFQW236\n");
      exit(AFQW236);
      return "EMPTY";
   }
}

// Get the value within the given index
const QString Behaviour::PeekBehaviour(int nindex) {
   if(index > nindex) {
       return note[nindex];
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Viewing given index behaviour has overflown your memmory\n"
      "The system will now save and close, sorry for any inconveniance\n"
      "contact your vendor emediatly quoting error code AFQW237\n");
      exit(AFQW237);
      return "EMPTY";
   }
}

// Get the studentdata index.. pop does not remove the index--
int Behaviour::PeekBehaviourIndex() {
   return index;
}

// Checks if the list is empty
bool Behaviour::IsEmptyBehaviourIndex() {
   return (index == 0);
}

// End of Source
