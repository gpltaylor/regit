/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This file creates the timetable object. It hold the data needed
   for a timetable I.e. the date of a given class.
   It inherits Dater, Dater holds dates in an ADT
   similar to how value and behaviour works.
   This is because every timetable will have its own set of date.


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
#ifndef TIMETABLE_H
#define TIMETABLE_H

#ifndef STUDENT_H
#include "student.h"
#endif

#ifndef DATER_H
#include "dater.h"
#endif

class TimeTable : public Dater {
   private:
      bool checker;
      char className[CLASSNAME];
      QDate classDateTime;
      char Lecturer[LFSIZE];
   public :
      Student CurrentStudent[MAXSTUDENTS];        // These are the student that are part of the given time table
      unsigned int numStudents;   

      unsigned short int stats[2];
      TimeTable();                                // Constructor
      ~TimeTable();                               // De-Constructor

      void setName(const char* name);             // Sets the class name
      const char* getName();                      // Returns the class name

/*
 * These are temp variables used only as a point of ref. This information will be
 * accessed from the Staff TimeTables.
 */
      void setDate(const QDate datetime);   // Sets the class time and date for the classes
      QDate getDate();                // Returns the date and time for classes

      void setLFName(const char* name);           // Sets the lecturers name for the class
      const char* getLFName();                    // Returns the lecturers name
      bool IndexChecker(TimeTable *CurrentTable); // This will check to see that the index values are the same
};
#endif
// End of source
