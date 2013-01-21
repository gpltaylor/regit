/* This file is part of the Regit Project regit.sourceforge.net
   created by Garry Taylor taylorg@southport-college.ac.uk
   This is the main slot handler for all signals from the
   creator object.

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

// Sets the address column to a bigger size
void Creator::init() { 
    StudentDetails->setColumnWidth ( 4, 300 ); // Sets the width of the address column
     StudentDetails->setColumnWidth ( 3, 85 );; // Sets the width of the DOB column
     creatorTT = new TimeTable();
     open = false;
     disableActions();
}

void Creator::destroy() {
    delete creatorTT;
}

void Creator::fileNew() {
    // closeTT Checks weather to save the current data creates a new timetable object
    // and clears the gui
    closeTT();
    enableActions();
}

void Creator::fileOpen() {
    // Check weather to save changes
    saveChanges();
    StudentDetails->setNumRows( 0 );
    StudentDetails->setNumRows( 1 );        
    
    QString temp, temp1, temp2;
    QStringList list, templist;
    
    QString s = QFileDialog::getOpenFileName(
                    appDir +"/timetables/",
                    "Regit Timetable (*.xml)",
                    this,
                    "open file dialog"
                    "Choose a file" );
    // If the user cancels the open
    if( s.isNull() ) {
		  closeTT();
		  return;
	 }
    creatorTT = classcreatorLoad(s);
    enableActions();
    this->setCaption( s );
    
// Load all the data onto the interface and clears the current data
   
    // Set the class name
    temp = creatorTT->getName();
    ClassName->setText( temp );
    
    // Set the date and time no longer used. Moved to LecturerTT
    //temp = creatorTT->getDate();
    //DateTime->setText( temp );
    
    // Set the Lecturers name
    temp = creatorTT->getLFName(); 
    LFName->setText( temp );
    
    // Set up the StudentList table. Can loop using !null for Student ID
    StudentDetails->setNumRows( creatorTT->numStudents );    
    for (unsigned int x = 0; x < creatorTT->numStudents && x < MAXSTUDENTS; x++ ) {
 temp = creatorTT->CurrentStudent[x].GetStudentID();
 if( temp.isEmpty() ) {
     break;
 }
 StudentDetails->setText( x, 0, creatorTT->CurrentStudent[x].GetStudentID() );
 
 // Sets the names
 {
     list = creatorTT->CurrentStudent[x].GetStudentName();
     templist = list.split( " ", creatorTT->CurrentStudent[x].GetStudentName(),  false );
     QStringList::Iterator it = templist.begin();
     temp1 = *it;
     it++;
     temp2 = *it;
     
     StudentDetails->setText( x, 1, temp1 );
     StudentDetails->setText( x, 2, temp2 );
 }
  
  StudentDetails->setText( x, 3,  creatorTT->CurrentStudent[x].QGetStudentAge().toString( "dd.MM.yyyy" ) );
  StudentDetails->setText( x, 4, creatorTT->CurrentStudent[x].GetStudentAddress() );
    }
    open = true;
    filePrint();
}

void Creator::fileSave() {
    create();
}

void Creator::fileSaveAs() {
    QString s;
    QStringList nList;
    s = QFileDialog::getSaveFileName(
     QString::null,
                    "Regit Timetable (*.xml)",
                    this,
                    "Save As file dialog"
                    "Create a new file" );
    if( s.isNull() ) {
 QMessageBox::information(this, "infobot", "Save canceled");
 return;
    }
    
    // Cutting up the string to get the file name only. excluting the .xml if present
    nList = QStringList::split("/", s, true);
    QStringList::Iterator it = nList.end();
    it--;
    s = *it;
    s.remove( ".xml" );
    ClassName->setText( s );
    create();
}

void Creator::filePrint() {
}

void Creator::fileExit() {
    if(open == true) {
 saveChanges();
 Creator::close();
    }
    else {
 Creator::close();
    }
}

void Creator::editUndo()
{
    
}

void Creator::editRedo()
{
    
}

void Creator::editCut()
{
    
}

void Creator::editCopy()
{
    
}

void Creator::editPaste()
{
   
}

void Creator::editFind()
{
    
}

void Creator::helpIndex() {

}

void Creator::helpContents()
{
    
}

void Creator::helpAbout() {
    QMessageBox::information(this, "Infobot",
    "Class Creator allows a administrator to setup a class.\n"
    "This data can then be used as the basic setup for the \n"
    "Regit application. The class information is saved in XML\n"
    "and can be used to populate a website."
    "\n\nThis program is Open Source under the GPL License \n"
    "please read the copy of The GPL License agreement..\n\n"
    "Program developed by Garry Taylor");
}

void Creator::newStudent() {
    if( StudentDetails->numRows() <  MAXSTUDENTS ) {
 StudentDetails->insertRows( StudentDetails->numRows() );
    }
    else {
 QMessageBox::information( this, "Infobot", "Sorry but you have exceded the maximum\n"
     "number of students allowed" );
    }
}


void Creator::removeStudent() {
    if(StudentDetails->numRows() == 1) {
 QMessageBox::information( this, "Infobot", "That would be silly" );
    }
    else {
 StudentDetails->removeRow( StudentDetails->currentRow() );
    }
}

// Use this slot to call the built in function checker(); coded bellow.
// This is because we need a boolean to show info..
// This will be updated in future editions
void Creator::validate() {
    if( Creator::checker() )
 QMessageBox::information( this, "Infobot", "This data is fine" );
}

void Creator::create() {
    int row, col;
    row = col = 0;
    QString studentname, qage;
    Dater dater;
    studentname = "";    
    /* Create calls validate to check the data then populates the timetable object.
     * This data is then sent on to classcreator to be saved.
     */ 
	 if( checker() ) {
		  // Populate the timetable.
		  for(; row <= StudentDetails->numRows()-1; row++) {
				if(StudentDetails->text(row, col ) != NULL ) {
					 qage = StudentDetails->text(row, col+3);
					 studentname = StudentDetails->text( row, col+1 ).ascii();
					 studentname += " ";
					 studentname += StudentDetails->text( row, col+2 ).ascii();
					 creatorTT->CurrentStudent[row].SetStudentID( StudentDetails->text( row, col ).ascii() );
					 creatorTT->CurrentStudent[row].SetStudentName( studentname );
					 creatorTT->CurrentStudent[row].SetStudentAge( dater.converter( qage ) );
					 creatorTT->CurrentStudent[row].SetStudentAddress( StudentDetails->text( row, col+4 ).ascii() );
				}
		  }
		  // Gets the text box data for Class name, date and Lecturer name
		  QString tempname;  // making the default dir timetables
		  // tempname = "timetables/" + ClassName->text();
		  // creatorTT->setName( tempname.ascii() );
		  //creatorTT->setDate( DateTime->text().ascii() );  no longer used
		  // creatorTT->setLFName( LFName->text().ascii() );
		  
		  if ( !classcreatorSave( creatorTT, StudentDetails->numRows(), open ) ) {
				QMessageBox::information( this, "infobot", "File Saved" );
				open = true;
		  } else {
				QMessageBox::information( this, "infobot", "Sorry but this file already exists\n"
												  "please open the file first to make changes or save the file\n"
												  "with a diffrent name.");
		  }
	 }
}

void Creator::canel() {
    if( open ) {
 switch(QMessageBox::information(this,"Infobot",
     "Canceling will loose all changes\n"
     "Are you sure?",
     "Yes please cancel",
     "No do not Cancel") )  {
     case 0: Creator::close(); break;
      case 1: break;
   }
    }
    else {
 Creator::close();
    }
}

// This function will test all the data against common rules
// I may create a rule.h with defined values like I have done in codes.h
// but this will take some time.
int Creator::checker() {
    if( ClassName->text().isEmpty() ||
 LFName->text().isEmpty() ) {
 QMessageBox::information(this, "Infobot", "Validation rule not enforced..\n"
     "Sorry the timetable can not be created\n"
     "Please check that all the data is corect\n");
 return false;
    }
    else {       
 return true;
    }
}

void Creator::saveChanges() {
    if( !ClassName->text().isEmpty() )  {
    switch(QMessageBox::warning(this,"Infobot",
 "Do you wish to save the changes", 
 "Yes please",
 "No thank you") )  {
       case 0: create(); break;
       case 1: disableActions(); break;
    }
   }
}

// Used to disable and enable the main buttons
void Creator::disableActions() {
    fileSaveAction->setEnabled( false );
    fileSaveAsAction->setEnabled( false );
    filePrintAction->setEnabled( false );
    closeTimeTableAction->setEnabled( false );
    newStudentAction->setEnabled( false );
    removeNewStudentAction->setEnabled( false );
    validatorAction->setEnabled( false );
}

void Creator::enableActions() {
    fileSaveAction->setEnabled( true );
    fileSaveAsAction->setEnabled( true );
    filePrintAction->setEnabled( true );
    closeTimeTableAction->setEnabled( true );
    newStudentAction->setEnabled( true );
    removeNewStudentAction->setEnabled( true );
    validatorAction->setEnabled( true );
}

void Creator::closeTT() {
    if (open == true )
 saveChanges();
    delete creatorTT;
    creatorTT = new TimeTable();
    // Set the class name
    ClassName->setText( QString::null );
    
    // Set the Lecturers name
    LFName->setText( QString::null );
    
    StudentDetails->setNumRows( 0 );
    StudentDetails->setNumRows( 1 );
    
    disableActions();
    this->setCaption( "Creator" );
    open = false;
}


void Creator::setAppDir( QString app )
{
    appDir = app;
}
