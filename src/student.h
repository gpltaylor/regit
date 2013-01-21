/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This file creates an object Student. This object hold all the
   methods needed to store the data set in the design.
   Age, name, DOB, address, behaviour in every class, mark for every
   class is stored within this object.

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
#ifndef STUDENT_H
#define STUDENT_H

#ifndef BEHAVIOUR_H
#include "behaviour.h"
#endif

#ifndef VALUE_H
#include "value.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <qdatetime.h>

#include <qstring.h>

class Student : public Behaviour, public Value {
   private:
      int index;
      unsigned int age;
      QDate qage;
      QString studentid;
      QString address;
      QString name;
   public:
      Student();
      ~Student();
      void  SetStudentID(const QString nvalue);		// Set the students ID number
      const QString GetStudentID();			// Returns the students ID number
      void  SetStudentAddress(const QString nvalue);	// Set the students address
      const QString GetStudentAddress();		// Returns the students address
/*
 * Code added to support direct qdate access for student age
 */
      void  SetStudentAge(const unsigned int nage);	// Sets the students age
      void  SetStudentAge( const QDate nvalue );	// Sets the students age
      int   GetStudentAge();				// Returns the students age
      QDate QGetStudentAge();				// Returns the students
      void  SetStudentName(const QString value);	// Puts a name into the name field
      const QString GetStudentName();			// Returns student name
      void  ReplaceStudent(const QString nvalue);	// Replaces students name
      void  PopStudent();				// Removes student name set to null
      int   PeekStudentIndex();				// Views the index
};

#endif
// End of source
