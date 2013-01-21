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
#include <stdio.h>
#include <time.h>
#include "date.h"
using namespace std;
char date::format;
char date::out_string[25];
int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

date::date(void)
{
   time_t time_date;
   struct tm *current_date;
   time_date = time(NULL);
   current_date = localtime(&time_date);
   month = current_date->tm_mon + 1;
   day = current_date->tm_mday;
   year = current_date->tm_year + 1900;
   format = 1;
}

int date::Set_Date(int in_day, int in_month, int in_year) {
   int temp = 0;
   int max_days;
                      // The limits on the year are purely arbitrary
   if (in_year < 1500) {           // Check that the year is between
      year = 1500;                 //  1500 and 2200
      temp = 1;
   } else {
      if (in_year > 2200) {
         year = 2200;
         temp = 1;
      } else
         year = in_year;
   }

   if(in_month < 1) {              // Check that the month is between
      month = temp = 1;            //  1 and 12
   } else {
      if (in_month > 12) {
         month = 12;
         temp = 1;
      } else
         month = in_month;
   }

   max_days = Days_This_Month();
   if (in_day < 1) {               // Check that the day is between
      day = temp = 1;              //  1 and max_days
   } else {
      if (in_day > max_days) {
         day = max_days;
         temp = 1;
      } else
         day = in_day;
   }

   return temp;
}

static char *month_string[13] = {
     " ", "Jan", "Feb", "Mar", "Apr",
     "May", "Jun", "Jul", "Aug",
     "Sep", "Oct", "Nov", "Dec"
};


// Returns the month
char *date::Get_Month_String()
{
   return month_string[month];
}

// REturns the date in a full string
// CAn set up the system to show diffrent date formats
// This is for future development
char *date::Get_Date_String()
{
   switch (format) {
      case 2  : sprintf(out_string, "%02d/%02d/%02d", day, month, year - 1900);
                break;

      case 3  : sprintf(out_string, "%02d/%02d/%04d", day, month, year);
                break;

      case 4  : sprintf(out_string, "%d %s %04d", day, month_string[month], year);
                break;

      case 1  : // Fall through to the default case
      default : sprintf(out_string, "%d %s, %04d", day, month_string[month], year);
                break;
   }
   return out_string;
}

// returns the month is a int
int date::Days_This_Month()
{
   if (month != 2)
      return days[month];

   if (year % 4)       // Not leap year
      return 28;
   if (year % 100)     // It is leap year
      return 29;
   if (year % 400)     // Not leap year
      return 28;
   return 29;          // It is leap year
}

// End of source
