/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   this is a ADT to store dates, used for the timetable

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

#ifndef DATER_H
#define DATER_H

#ifndef CODES_H
#include "codes.h"
#endif

#ifndef DATE_H
#include "date.h"
#endif

#include <qdatetime.h>
#include <qstringlist.h> 

// This will be canged to handle QDate objects ADT's
class Dater {
   private:
      int index;
      QDate qvalue[MAXCLASSES];		//Dates of classes type QDate
   public:
      Dater();				// Constructor
      ~Dater();				// De-constructor

      void PushDateValue( QDate value);  // Adds a value
      QDate PeekDateValue( int nindex );  // Returns a date object of the given index element
      QDate PeekDateValue();  // Returns a date object of the last element in the list
      void ReplaceDateValue( int nindex, QDate nvalue );  // Replace a value using a given index
      void PopDateValue();                                // Removes the top indexed value
      int PeekDateIndex();                                // Views the index number
      bool IsEmptyDateIndex();                            // Checks if the list is empty
      
/*
 * This function will convert a string I.e. 25.06.1978 into a QDate and pass the new
 * object back.
 * This will be used to read strings from XML files and enter the QDate into the students DOB.
 * Also this will be used to help Creator save and store dates.
 */
QDate converter(QString ndate);
};

#endif
/* __VALUE_H__ */
// End of source
