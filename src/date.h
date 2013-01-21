/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This is a simple object used to get the current time.

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
#ifndef DATE_H
#define DATE_H

class date {
protected:
   int month;                  // 1 through 12
   int day;                    // 1 through max_days
   int year;                   // 1500 through 2200
   static char out_string[25]; // Format output area
   static char format;         // Format to use for output
   int Days_This_Month();
public:
   date();
   ~date() {};
   int Set_Date(int in_day, int in_month, int in_year);       // Sets the date
   int Get_Month() { return month; };                         // Returns the month
   int Get_Day()   { return day;   };                         // Returns the day
   int Get_Year()  { return year;  };                         // Returns the year
   char *Get_Date_String();                                   // Returns the date in a string
   char *Get_Month_String();                                  // Returns the month in a string
};

#endif
// End of source
