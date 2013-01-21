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
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <stdlib.h>
#include "timetable.h"
#include "dater.h"
#include "codes.h"
#include "classcreator.h"
//#include "../xml/xmltraversal.h"

using namespace std;

/* This function will save all data in a pre-format. This will be
   updated to be XML for crapy .net compatability
*/
Dater ndate; // Used to convert strings to QDates for XML pases and saves

int classcreatorSave( TimeTable* timetable, int row, bool fileopen ) {
   QStringList* output;
   output = new QStringList();
   QString lineoutput, lineoutput1;
   
   cout << "Test location: " << timetable->getName() << endl;
   
   // XML Header
   *output += "<?xml version=\"1.0\"?>";
   *output += "<?xml-stylesheet type=\"text/css\" href=\"basicclass.css\"?> ";
   *output += "<TIMETABLE>";

   // Name of course or class
   lineoutput = "<CLASSNAME>";
   lineoutput.append( timetable->getName() );
   lineoutput.append( "</CLASSNAME>" );
   *output += lineoutput;

   /* Name of Lecturer
     * This needs to be removed as different lecturer could teach this class. This information
     * should be gained from a separate Staff timetable. call lectuerTT
     */
   lineoutput = "<LECTURER>";
   lineoutput.append( timetable->getLFName() );
   lineoutput.append( "</LECTURER>" );
   *output += lineoutput;

   // Date of classes no longer used moved to LecturerTT
   /*
   *output += "<DATE>";
   lineoutput = "<DAY>";
   lineoutput.append( timetable->getDate() );
   lineoutput.append( "</DAY>" );
   *output += lineoutput;
   *output += "</DATE>";
   */
   
   // Set the dates the classes was held on
   *output += "<CLASSDATES>"; 
   for (int x=0; x < timetable->PeekDateIndex(); x++) {
       lineoutput = "<CLASSDATE>";
       lineoutput.append( timetable->PeekDateValue(x).toString( "dd.MM.yyyy" ) );
       lineoutput.append( "</CLASSDATE>");
       *output += lineoutput;
   }
   *output += "</CLASSDATES>";   

   // Number fo student in the timetable loop
   for(int x=0; x<row; x++) {
      *output += "<STUDENT>";

      lineoutput = "<STUDENTID>";
      lineoutput.append( timetable->CurrentStudent[x].GetStudentID() ); 
      lineoutput.append( "</STUDENTID>" );
      *output += lineoutput;

      lineoutput = "<NAME>";
      lineoutput.append( timetable->CurrentStudent[x].GetStudentName() );
      lineoutput.append( "</NAME>" );
      *output += lineoutput;

      lineoutput = "<AGE>";
      lineoutput.append( timetable->CurrentStudent[x].QGetStudentAge().toString( "dd.MM.yyyy" ) );
      lineoutput.append( "</AGE>" );
      *output += lineoutput;

      lineoutput = "<ADDRESS>";
      lineoutput.append( timetable->CurrentStudent[x].GetStudentAddress() );
      lineoutput.append( "</ADDRESS>" );
      *output += lineoutput;

      /*  Create absent mark for any student/s just created to populate all classes marks missed
         *  Some students could be added to the class late. their mark here will be passed as absent
         *  this will have to change as it will make the stats incorect. Possably change the 'A' to a '-'
         */
      do {
   timetable->CurrentStudent[x].PushValue( 'A' );
      } while ( timetable->CurrentStudent[x].PeekValueIndex() < timetable->PeekDateIndex()  );
      
      // Now we can add the marks to the XML file
      *output +="<MARKS>";
      for (int index =0; index < timetable->PeekDateIndex(); index++) {
   lineoutput = "<MARK>";
   lineoutput.append( timetable->CurrentStudent[x].PeekValue( index ).upper() );
   lineoutput.append( "</MARK>"); 
   *output += lineoutput;
      }
      *output +="</MARKS>";      

      // Create No Comment mark for any student/s just created to populate all classes behaviour missed
      do {
   timetable->CurrentStudent[x].PushBehaviour( QString::QString("No Comment") );
      } while ( timetable->CurrentStudent[x].PeekBehaviourIndex() < timetable->PeekDateIndex() );
      
      *output +="<BEHAVIOURS>";
      for (int index =0; index < timetable->PeekDateIndex(); index++) {
   lineoutput = "<BEHAVIOUR>";
   lineoutput.append( timetable->CurrentStudent[x].PeekBehaviour( index ) );
   lineoutput.append( "</BEHAVIOUR>"); 
   *output += lineoutput;
      }
      
      // End of behaviours
      *output += "</BEHAVIOURS>";
      
      // End of students details
      *output += "</STUDENT>";
  }
         // End of XML document
      *output += "</TIMETABLE>";


   // write the data to a file
   QFile* outputfile;
   QString filename;
   filename.append( timetable->getName() );
//   filename.append(".xml");

	cout << "Filename: " << filename << " fileopen: " << fileopen << endl;
	if ( QFile::exists( filename ) && fileopen == false ) {
		 delete output;
		 return 0;
	} else {
		 outputfile = new QFile( filename );
		 if(outputfile->open( IO_ReadWrite | IO_WriteOnly ) ) {
			  QTextStream stream( outputfile );
			  for (QStringList::Iterator it = output->begin(); it != output->end(); ++it) {
					stream << *it << "\n";
			  }
			  outputfile->close();
			  delete output;
			  return 0;
		 }
	}

	delete output;
	return 1;
}

/* This function will load all data in a pre-format. This will be
   updated to be XML for crapy .net compatability
*/
TimeTable* classcreatorLoad(QString name) {
   QFile* input;
   TimeTable* newtable;
   newtable = new TimeTable();
   QStringList lines;
   QString line;
   

      // Check that the file exist and the string data has not been corupted
   // If not then populate the new TimeTable object
   if ( QFile::exists( name ) ) {
       input = new QFile(name);
             
      QFile file( name );
    
       if ( file.open( IO_ReadOnly ) ) {
          QTextStream stream( &file );
       
        int i; i=0;
        while ( !stream.eof() ) {
           line = stream.readLine(); // line of text excluding '\n'
           lines += line;
        }
 validate( newtable, &lines );
 file.close();       
      }
   }
   return newtable;
}

/*
  * This is the point at which the data will be read and validated.
  * This is a private function just to split the code into easier parts
  */
void validate( TimeTable* nTimetable, const QStringList *nList ) {
    int row; row =0;
    int x; x =0;
    int numStudents; // Stores the number of students
    int numElements; // Will store an int value for the number of behaviours, marks, dates
    QStringList temp;
    QString tempString;
    //XMLTraversal *xml = new XMLTraversal( nList->join( "" ) ) ;
       
    // Setting the class name
    //xml->cd("CLASSNAME");
    //cout << "XML output\n";
    //cout << xml->currentValue();
    temp = nList->grep("<CLASSNAME>", true);
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<CLASSNAME>");tempString.remove("</CLASSNAME>");
       nTimetable->setName( tempString.ascii() );
    }
     
    // Setting the Lecturers name
    temp = nList->grep("<LECTURER>", true);
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<LECTURER>");tempString.remove("</LECTURER>");
       nTimetable->setLFName( tempString.ascii() );
    }
    
    // Setting the Date and time no longer used moved to LecturerTT
    /*
        temp = nList->grep("<DAY>", true);
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<DAY>");tempString.remove("</DAY>");
       nTimetable->setDate( tempString.ascii() );
       cout << tempString << endl;
    } 
    */
    
    //  Need to retrive any date, value (marks) and behaviours
    // Setting up the Student CLASSDATE
    temp = nList->grep("<CLASSDATE>", true);
    x=0;
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) { 
       tempString = *it;
       tempString.remove("<CLASSDATE>"); tempString.remove("</CLASSDATE>");
       nTimetable->PushDateValue( ndate.converter( tempString.ascii() ) );
       x++;
    }
    
    // Setting up the Student ID
    temp = nList->grep("<STUDENTID>", true);
    x=0;
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<STUDENTID>"); tempString.remove("</STUDENTID>");
       nTimetable->CurrentStudent[x].SetStudentID( tempString.ascii() );
       x++;
    } numStudents = x; // Sets the number of students in the class
    nTimetable->numStudents = x; 
    
    // Setting up the Student Name
    temp = nList->grep("<NAME>", true);
    x=0;
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<NAME>"); tempString.remove("</NAME>");
       nTimetable->CurrentStudent[x].SetStudentName( tempString.ascii() );
       x++;
    }    
    
    // Setting up the Student Age using Dater::converter
    temp = nList->grep("<AGE>", true);
    x=0;
    QDate nage;
    Dater nqage;

    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<AGE>"); tempString.remove("</AGE>");
       nage = nqage.converter( tempString.ascii() );
       nTimetable->CurrentStudent[x].SetStudentAge( nage );
       x++;
    }
    
    // Setting up the Student Address
    temp = nList->grep("<ADDRESS>", true);
    x=0;
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
       tempString = *it;
       tempString.remove("<ADDRESS>"); tempString.remove("</ADDRESS>");
       nTimetable->CurrentStudent[x].SetStudentAddress( tempString.ascii() );
       x++;
    } 
    
    // Setting up the student marks
    temp = nList->grep("<MARK>", true);
    x=0;
    // Used to get the number of elements in the list and devide by the number of students
    // this will set the value for how many marks belong to a given student
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) { 
 x++;
    } numElements = x / numStudents;
    
    
    x=0; // reset the index counter
       /*
           * This section of code adds a value to a given student for MARKS. Each student needs to have a mark for
           * for every class day they have/have-not been in. Above we have calculated the number of students.
           * by deviding the number of students with the number of marks in the XML file we can calculate the number
           * of MARKS per student. These section of code therfore loops with the number of students but only increments
           * when the number of MARKS per student has been reached. If the xml file is not curupt this will not cause a 
           * problem. :)
           */    
    int markIndex;
    markIndex = 0;

    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
 tempString = *it;
 tempString.remove("<MARK>"); tempString.remove("</MARK>");
 nTimetable->CurrentStudent[x].PushValue( tempString[0].latin1 () ); 
 markIndex++;
 
 if( markIndex == numElements ) {
     x++;
     markIndex = 0;
 }
    }
    
    // Sets up behaviours
    temp = nList->grep("<BEHAVIOUR>", true);
    x=0;
    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) { 
 x++;
    } numElements = x / numStudents;
    
    x=0; // reset the index counter

    markIndex = 0;

    for ( QStringList::Iterator it = temp.begin(); it != temp.end(); ++it ) {
 tempString = *it;
 tempString.remove("<BEHAVIOUR>"); tempString.remove("</BEHAVIOUR>");
 nTimetable->CurrentStudent[x].PushBehaviour( tempString.ascii() ); 
 markIndex++;
 
 if( markIndex == numElements ) {
     x++;
     markIndex = 0;
 }
    }    
}

// EOF

