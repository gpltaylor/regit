/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This file creates the value object, this will story the marks
   that a given student will get. I.e. absent, present.

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
 
#ifndef VALUE_H
#define VALUE_H

#ifndef CODES_H
#include "codes.h"
#endif

#include <qstring.h>

class Value {
   private:
      int index;
      QChar value[MAXCLASSES];          // Time table marks I.e. absent present Field trip
   public:
      Value();                          // Constructor
      ~Value();                         // De-constructor
      void PushValue(const char value); // Adds a value
      QChar PeekValue(int nindex);      // Views the value giving index;
      QChar PeekValue();		// Returns the current index value I.e. last value added
      QChar* PeekAllValues();           // Returns all the values
      void ReplaceValue(int nindex, char nvalue);     // Replace a value using a given index
      void PopValue();                                // Removes the top indexed value
      int PeekValueIndex();                           // Views the index number
      bool IsEmptyIndex();                            // Checks if the list is empty
};

#endif
/* __VALUE_H__ */
// End of source
