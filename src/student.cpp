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
#include "student.h"
using namespace std;

// Init
Student::Student() {
   index = 0; // Note that this is the number of students/ not to be caculated like value/date/behaviour
}

// Deconstructor
Student::~Student() {
   // deconstructor
}

// Sets the students ID number
void Student::SetStudentID( const QString nvalue ) {
   if( nvalue.length() < IDSIZE ) {
      studentid = nvalue;
   } else {
      QMessageBox::critical(0,"Infobot",
      "Error - New Student ID is out of bounds\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW245\n");
   }
}

// Sets the students ID Number
const QString Student::GetStudentID() {
   return studentid;
}

// Sets the students address
void Student::SetStudentAddress( const  QString nvalue ) {
   if( nvalue.length() <STUDENTADDRESS ) {
      address = nvalue;
   } else {
      QMessageBox::critical(0,"Infobot",
      "Error - New Student Address is outof bounds\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW246\n");
   }
}

// Returns the students address
const QString Student::GetStudentAddress() {
   return address;
}

// Sets the students age
void Student::SetStudentAge(const unsigned int nage) {
    /*
      * Need to be modified to set the exact date of birth.
      */
    {
	QDate temp;
	age = ( qage.year() - temp.year() );
    }
       
   if (age == nage )
      return;
   if( nage > 150 ) {
      QMessageBox::critical(0,"Infobot",
      "Error - Could not set the age to the give value\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW247\n");
      exit(AFQW247);
   }
   else {
      age = nage;
      qage.setYMD( 2003-age, 1,1 );
   }
}

// Sets the students age
void Student::SetStudentAge( const QDate nvalue ) {
    qage = nvalue;	
}

// Returns the students age
int Student::GetStudentAge() {
   return age;
}

// Returns the students   age is object type QDate
QDate Student::QGetStudentAge() {
    return qage;
}

// Push value on to the stack
void Student::SetStudentName(const QString nvalue) {
   if( nvalue.length() < NAMESIZE ) {
      name = nvalue;
      index++;
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Error - Student name is too long\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW238\n");
   }
}

// Deletes a value with the index given. also move the data down and index--
void Student::ReplaceStudent(const QString nvalue) {
   if( nvalue.length() < NAMESIZE  ) {
      name = nvalue;
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Error - Could not replace the student, maybe one does not exist\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW239\n");
   }
}

// Removes the top value
void Student::PopStudent() {
   if( index!=0 ) {
      index--;
   }
}

// Get the value within the given index
const QString Student::GetStudentName() {
   if( name.length() != 0 ) {
      return name;
   }
   else {
      QMessageBox::critical(0,"Infobot",
      "Error - No students in list\n"
      "sorry for any inconveniance\n"
      "contact your vendor quoting error code AFQW240\n");
       return "EMPTY";
   }
}

// Get the studentdata index.. pop does not remove the index--
int Student::PeekStudentIndex() {
   return index;
}

// End of Source
