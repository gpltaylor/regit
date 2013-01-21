/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk

   This file handles the GUI signal from the Student Comments dialog box.

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
void StudentDayStat::init( ) {
}

void StudentDayStat::cancel() {
    this->close();
}


// Use to populate the timetable untill Regit can use it.
void StudentDayStat::populater( QString sid, QString sname, QDate dob, QDate doc, QString comment ) {
    /*
      * Next step is to create some temp data and try out the data with static row,col values
      */
    StudentID->setText( sid );
    StudentName->setText( sname );
    DateOfBirth->setText( dob.toString() );
    DateOfComment->setText( doc.toString() );
    commenttextEdit->setText( comment );
}




