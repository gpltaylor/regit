/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   A very powerful XML file creator and reader. All timetable data is stored
   in XML. This object is used to read and write all student timetables

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
#ifndef CLASSCREATOR_H
#define CLASSCREATOR_H

#include "timetable.h"
#include "dater.h"
#include <qstring.h>
#include <qstringlist.h>

// Save the data to the XML file
int classcreatorSave( TimeTable* timetable, int row, bool fileopen );
// Loads the data to the Creator interface
TimeTable* classcreatorLoad( QString name );
// Loads the data into the TimeTable object
void validate( TimeTable* nTimetable, const QStringList* nList );
#endif
// EOF

