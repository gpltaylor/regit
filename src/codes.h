/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This hold the globle values used. This also hold basic error
   trapping codes, to assit in debugging.

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


#ifndef CODES_H
#define CODES_H
// Globle variables
#define MAXCLASSES 32
#define NAMESIZE 32
#define CLASSNAME 132
#define CLASSDATE 32
#define LFSIZE 32
#define NOTESIZE 255
#define MAXSTUDENTS 25
#define IDSIZE 10
#define STUDENTADDRESS 60

///Globle Error Codes
#define AFQW233 1  // "Tring to replace a date using a out-of-bound index"
#define AFQW234 2  // "Tring to view a date using out-of-bound index"
#define AFQW235 3  // "Replace Behaviour using out-of-bound index"
#define AFQW236 4  // "Tring to view out-of-bound behaviour"
#define AFQW237 5  // "Tring to view out-of-bound behaviour using bad index"
#define AFQW238 6  // "Out-of-bound student index, soon to be replaced" TODO: replace this
#define AFQW239 7  // "Tring to replace a non-existant student"
#define AFQW240 8  // "Tring to view non existent student"
#define AFQW242 10 // "Tring to replace a value with out-of-bound index"
#define AFQW243 11 // "Tring to view value with out-of-bound index"
#define AFQW244 12 // "Tring to insert value with out-of-bound index"
#define AFQW245 13 // "Tring to enter a student ID that is out of bounds"
#define AFQW246 14 // "Tring to enter a address that is out of bounds"
#define AFQW247 15 // "Tring to set the age to a bad value"
#define AFQW248 16 // "Trying to set the Class Name to bad value"
#define AFQW249 17 // "Trying to set the Class date or time to bad value"
#define AFQW250 18 // "Trying to set the Lecturer name to a bad value"
#define AFQW251 19 // "Trying to convert a bad string using Dater::converter"

#endif

