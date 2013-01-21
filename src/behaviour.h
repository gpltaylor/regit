/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This is a simple obect that acts as a ADT for the students behaviour
   for every class timetabled. (Even if absent).

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
#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#ifndef CODES_H
#include "codes.h"
#endif

#include <qstring.h>

class Behaviour {
   private:
      int index;
      QString note[MAXCLASSES];
   public:
      Behaviour();
      ~Behaviour();
      void PushBehaviour(const QString value);  // Puts a name onto the stack
      const QString PeekBehaviour(int nindex);  // Views a given value by its index
      const QString PeekBehaviour();   // Views the top value on the stack

      void ReplaceBehaviour(int nindex, const QString nvalue); // Replaces a given value
      void PopBehaviour(int nindex);    // Removes value by index
      void PopBehaviour();     // Removed last element
      int PeekBehaviourIndex();     // Views the top index
      bool IsEmptyBehaviourIndex();    // Shows if the stack is empty
};
#endif
// End of source
