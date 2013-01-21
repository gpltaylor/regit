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
#include <qmessagebox.h>
#include "timetable.h"
#include "codes.h"
using namespace std;
TimeTable::TimeTable() {
   checker = false;
   numStudents = 0;
}

TimeTable::~TimeTable() {
}

bool TimeTable::IndexChecker(TimeTable *CurrentTable) {
   if(CurrentTable->PeekDateIndex() == CurrentTable->CurrentStudent[0].PeekValueIndex()){
      if(CurrentTable->CurrentStudent[0].PeekBehaviourIndex() == CurrentTable->CurrentStudent[0].PeekValueIndex()){
         checker = true;
         return checker;
      }
   }
   return false;
}
// Sets the timetables name
void TimeTable::setName(const char* name) {
   if( strlen( name ) < CLASSNAME ) {
      strcpy( className, name );
   } else {
      QMessageBox::critical( 0,"Infobot",
      "Could not set the Class Name\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW248\n" );
      exit(AFQW248);
   }
}

const char* TimeTable::getName() {
   return className;
}

// Sets the temp date.
void TimeTable::setDate(const QDate datetime) {
   classDateTime = datetime;
   if( classDateTime != datetime ) {
      QMessageBox::critical( 0,"Infobot",
      "Could not set the Class date or time\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW249\n" );
      exit(AFQW249);
      }
}

QDate TimeTable::getDate() {
   return classDateTime;
}

// Sets the Lecturers name
void TimeTable::setLFName(const char* name) {
   if( strlen( name ) < LFSIZE ) {
      strcpy( Lecturer, name );
   } else {
      QMessageBox::critical( 0,"Infobot",
      "Could not set the Class date or time\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW250\n" );
      exit(AFQW250);
   }
}

const char* TimeTable::getLFName() {
   return Lecturer;
}
// End of source
