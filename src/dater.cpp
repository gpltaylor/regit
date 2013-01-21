#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "dater.h"
#include "codes.h"
#include <qmessagebox.h>
using namespace std;
// Init
Dater::Dater() {
   index = 0;
}

// Deconstructor
Dater::~Dater() {
   // deconstructor
}

// Push value on to the stack Type QDate
void Dater::PushDateValue(QDate nvalue) {
   if(index < MAXCLASSES) {
      qvalue[index++] = nvalue;
   }
   else {
      cout << "Error - Value out of bound error code. AFQW244\n";
      QMessageBox::critical(0, "infobot", "The new date has overflown your memmory\n"
      "contact your vendor emediatly quoting error code AFQW244\n"
      "The system will now save and close, sorry for any inconveniance");
      exit(AFQW244);
  }
}

// Pop Value from the stack
QDate Dater::PeekDateValue() {
   return qvalue[index];
}

// Deletes a value with the index given. also move the data down and index-- (type QDate)
void Dater::ReplaceDateValue(int nindex, QDate nvalue) {
   if( index > nindex && index < MAXCLASSES ) {
      qvalue[nindex] = nvalue;
   }
   else {
      QMessageBox::critical(0, "infobot", "Replacing date has overflown your memmory\n"
      "contact your vendor emediatly quoting error code AFQW233\n"
      "The system will now save and close, sorry for any inconveniance");
      exit(AFQW233);
   }
}

// Removes the top value
void Dater::PopDateValue() {
   if( index>0 && index < MAXCLASSES ) {
      index--;
   }
}

// Get the Value index.. pop does not remove the index--
// This will be used to check that all values and behaviour
// have the same ammount of entries
int Dater::PeekDateIndex() {
   return index;
}


// Get the value within the given index
QDate Dater::PeekDateValue(int nindex) {
   if( index > nindex && index < MAXCLASSES )
       return qvalue[nindex];
   else {
       QDate tmp;
       
       QMessageBox::critical(0, "infobot", "Reading date has overflown your memmory\n"
       "contact your vendor emediatly quoting error code AFQW234\n"
       "The system will now save and close, sorry for any inconveniance");
       exit(AFQW234);
       
       return tmp;
   }
}

// Checks if the list is empty
bool Dater::IsEmptyDateIndex() {
   return (index == 0);
}

/*
 * This function will convert a string I.e. 25.06.1978 into a QDate and pass the new
 * object back.
 * This will be used to read strings from XML files and enter the QDate into the students DOB.
 * Also this will be used to help Creator save and store dates.
 */
QDate Dater::converter(QString ndate) {
    QStringList ldob;
    QDate dob;
    int year, month, day;
    year = month = day = 1;

// some people will separate the date and time using . or / or - this trys to solve this problem
    if ( ndate.contains( "." ) )
 ldob = QStringList::split( ".", ndate );
    if ( ndate.contains( "/" ) )
 ldob = QStringList::split( "/", ndate );
    if ( ndate.contains( "-" ) )
 ldob = QStringList::split( "-", ndate ); 
    
    
    QStringList::Iterator it = ldob.begin();
    day = atoi(*it);   it++;
    month = atoi(*it); it++;
    year = atoi(*it);
    
    if ( month <1 || day <1 || month > 12 || day > 31 ) {
 QMessageBox::critical(0, "infobot", "Error inserting date\n"
 "contact your vendor quoting error code AFQW251\n"
 "The system will now save and close, sorry for any inconveniance");
 exit( AFQW251 );
    }
    dob.setYMD( year, month, day );
    return dob;
}


