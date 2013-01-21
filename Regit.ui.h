/*****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
		  **
		  ** If you wish to add, delete or rename functions or slots use
		  ** Qt Designer which will update this file, preserving your code. Create an
		  ** init() function in place of a constructor, and a destroy() function in
		  ** place of a destructor.
 *****************************************************************************/
void Regit::init() {
	 Table->setNumCols( 1 );
	 Table->setNumRows( 1 );
	 timetable = new TimeTable();
	 open = false;
	 this->setIcon( QPixmap::QPixmap( "images/absent.xpm" ) );
	 // Disable the actions
	 disableActions(); 
}

void Regit::fileNew() {
	 /*  insert and populate the headers and colounms
		*/
	 if( Table->numCols() < MAXCLASSES ) {
		  QDate currentdate;
		  date todaysdate;
		  currentdate.setYMD( todaysdate.Get_Year(), todaysdate.Get_Month(), todaysdate.Get_Day() );
		  
		  Table->insertColumns( Table->numCols() );
		  Table->horizontalHeader ()->setLabel( Table->numCols()-1, tr( currentdate.toString( "dd.MM.yyyy" ) ) );
		  // creates an empty behviour, value to update index
		  // This populates all student new comment and add a new date to the timetable
		  timetable->PushDateValue( currentdate );
		  for(int row=0; row<= Table->numRows(); row++) {
				timetable->CurrentStudent[row].PushBehaviour( "No Comment" );
				timetable->CurrentStudent[row].PushValue(' ');
		  }
		  Table->setCurrentCell( 0, Table->numCols()-1 );
	 }
	 else {
		  QMessageBox::information(this, "Infobot",
											"You have exceeded your available number of allowed classes");
		  Table->setCurrentCell( 0, 0 );
	 }
}

void Regit::fileOpen() {
	 if ( open )
		  saveChanges();
	 
	 QString s = QFileDialog::getOpenFileName(
				appDir + "/timetables/",
				"Regit Timetable (*.xml)",
				this,
				"open file dialog"
				"Choose a file" );
	 
	 // Set that the file is open
	 if( s.isNull() ) {
		  closeTimeTable();
		  return;
	 }
	 Regit::Populator( s );
	 appDir = s;
}


/* Create and populate the table. Used to a table with Operner
	Because of this the ClassCreate will be moved to the Opener module which is a 
	better idea
	*/
void Regit::Populator( QString s)  {
	 Table->setNumRows( 0 );
	 Table->setNumRows( 1 );     
	 QString temp, temp1, temp2;
	 QStringList list, templist;
	 bool behaviour; behaviour = true;
	 
	 timetable = classcreatorLoad(s);
	 open = true;
	 this->setCaption( s );
	 // Create the file witch the full path
	 timetable->setName ( s.ascii() );
	 // Enables the actions 
	 enableActions();
	 
	 // Set up the StudentList table. Can loop using !null for Student ID    
	 Table->setNumRows( timetable->numStudents );
	 for (unsigned int x = 0; x < timetable->numStudents && x < MAXSTUDENTS; x++ ) {
		  temp = timetable->CurrentStudent[x].GetStudentID();
		  if( temp.isEmpty() ) {
				return;
		  }
		  // This is the main part of the program
		  Table->verticalHeader()->setLabel( x, timetable->CurrentStudent[x].GetStudentName() );
		  // Sets up the Students Mark and Behaviour
		  // Need to loop of Mark index and Behaviour index
		  Table->setNumCols( timetable->CurrentStudent[x].PeekValueIndex() );
		  // Sets up the tables headers(dates) and Sides(names)
		  for( int dates=0; dates < timetable->CurrentStudent[x].PeekValueIndex(); dates++ ) {
				Table->horizontalHeader()->setLabel( dates, timetable->PeekDateValue( dates ).toString( "dd.MM.yyyy" ) );
		  }
		  
		  for( int mark = 0; mark < timetable->CurrentStudent[x].PeekValueIndex(); mark++ ) {
				behaviour = ( timetable->CurrentStudent[x].PeekBehaviour( mark) != "No Comment" );
				if ( timetable->CurrentStudent[x].PeekBehaviour( mark) == "" ) {
					 behaviour = false;
				} 
				
				switch( timetable->CurrentStudent[x].PeekValue( mark ) ) {
				case 'P':
				case 'p':
					 if( behaviour )
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/presentwb.xpm" ) );
					 else
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/present.xpm" ) );
					 break;
				case 'A':
				case 'a':
					 if( behaviour )
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/absentwb.xpm" ) );
					 else
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/absent.xpm" ) );
					 break;
				case 'F':
				case 'f':
					 if( behaviour )
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/FieldTripwb.xpm" ) );
					 else
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/FieldTrip.xpm" ) );
					 break;
				case 'L':
				case 'l':
					 if( behaviour )
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/latewb.xpm" ) );
					 else
						  Table->setPixmap( x , mark , QPixmap::QPixmap( "images/late.xpm" ) );
					 break;
				}     
		  }
	 }
}

void Regit::fileSave() {
	 //QString comment = Table->text(0,0);
	 if ( !open )
		  return;
	 else {
		  for(int row=0; row <= Table->numRows()-1; row++) {
				for(int col=0; col <= Table->numCols()-1; col++) {
					 if( Table->text(row, col ) != NULL )
						  timetable->CurrentStudent[row].ReplaceBehaviour( col, Table->text(row, col ).ascii() );
				}
		  }
	 }
	 // Test the file handlers
	 classcreatorSave(timetable, Table->numRows(), open);
	 QMessageBox::information(this, "Infobot", "your data has been saved");
}

void Regit::fileSaveAs() {
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
	 } else {
		  // Cutting up the string to get the file name only. excluting the .xml if present
		  nList = QStringList::split("/", s, true);
		  QStringList::Iterator it = nList.end();
		  it--;
		  s = *it;
		  QString path = appDir + s;
		  path.remove( ".xml" );
		  
		  // Test the file handlers
		  timetable->setName( path );
		  classcreatorSave(timetable, Table->numRows(), open);
		  QMessageBox::information(this, "Infobot", "your data has been saved");  
		  
		  // Set the title to the new filename
		  this->setCaption( path );
	 }
}

void Regit::filePrint() {
}

void Regit::fileExit() {
	 Regit::close();
}

void Regit::editUndo()
{
	 
}

void Regit::editRedo()
{
	 
}

void Regit::editCut()
{
	 
}

void Regit::editCopy()
{
	 
}

void Regit::editPaste()
{
	 
}

void Regit::editFind()
{
	 
}

void Regit::helpIndex()
{
	 
}

void Regit::helpContents()
{
	 
}

void Regit::helpAbout()
{
	 
}

void Regit::presentMark() {
	 int row = Table->currentRow();
	 int col = Table->currentColumn();
	 
	 timetable->CurrentStudent[row].ReplaceValue(col , 'P');
	 
	 // Set the right image if there is a comment 
	 if( findBehaviour() )
		  Table->setPixmap(row ,col , QPixmap::QPixmap( "images/presentwb.xpm" ) );
	 else
		  Table->setPixmap(row ,col , QPixmap::QPixmap( "images/present.xpm" ) );
	 
	 moveDown();
}

void Regit::feildTripMark() {
	 int row = Table->currentRow();
	 int col = Table->currentColumn();
	 
	 timetable->CurrentStudent[row].ReplaceValue(col , 'F');
	 
	 // Set the right image if there is a comment 
	 if( findBehaviour() )
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/FieldTripwb.xpm" ) );
	 else
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/FieldTrip.xpm" ) );
	 
	 moveDown();
}

void Regit::lateMark() {
	 int row = Table->currentRow();
	 int col = Table->currentColumn();
	 
	 timetable->CurrentStudent[row].ReplaceValue(col , 'L');
	 
	 // Set the right image if there is a comment 
	 if( findBehaviour() )
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/latewb.xpm" ) );
	 else
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/late.xpm" ) );
	 
	 moveDown();
}

void Regit::absentMark() {
	 int row = Table->currentRow();
	 int col = Table->currentColumn();
	 
	 timetable->CurrentStudent[row].ReplaceValue(col , 'A');
	 
	 // Set the right image if there is a comment 
	 if( findBehaviour() )
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/absentwb.xpm" ) );
	 else
		  Table->setPixmap(row , col , QPixmap::QPixmap( "images/absent.xpm" ) );
	 
	 moveDown();
}

void Regit::delCol() {
	 QString date;
	 date = Table->horizontalHeader ()->label( Table->numCols()-1 );
	 
	 switch(QMessageBox::warning(this,"Infobot - Warning",
										  "Do you wish to delete the records for: " + date , 
										  "Yes please",
										  "No thank you") )  { 
	 case 0: {
				/*
		* Removing the comumn from the table. Also removing the record from the ADT
		* With writing stupid code I can not delete a record from the middle of a timetable. this 
		* is because of a bad design with the ADT. No Pop<typename>(index);
		* Note: update the ADT to use Vector<type> instead of arrays.
		*/
				timetable->PopDateValue(  );
				for(int row=0; row<= Table->numRows(); row++) {
					 timetable->CurrentStudent[row].PopBehaviour( );
					 timetable->CurrentStudent[row].PopValue();
				}
				Table->setNumCols( Table->numCols()-1 );     
				break;
		  }
	 case 1: break;
	 }
}

void Regit::classCreator() {
	 Creator* nCreator;
	 nCreator = new Creator();
	 nCreator->setAppDir( appDir );
	 nCreator->show();
}

void Regit::saveChanges() {
	 switch(QMessageBox::warning(this,"Infobot",
										  "Do you wish to save the changes", 
										  "Yes please",
										  "No thank you") )  {
	 case 0: fileSave(); break;
	 case 1: break;
	 }
}

// Allows the user to close the open timetable but keep the app running
void Regit::closeTimeTable() {
	 if( open )
		  saveChanges();
	 
	 delete timetable;
	 timetable = new TimeTable();
	 Table->setNumRows( 0 );
	 Table->setNumCols( 0 );
	 Table->setNumRows( 1 );
	 Table->setNumCols( 1 );    
	 // Reset the title to Regit and disabled the actions
	 this->setCaption( "Regit" );
	 open = false;
	 disableActions();
}

void Regit::disableActions() {
	 fileSaveAction->setEnabled( false );
	 fileSaveAsAction->setEnabled( false );
	 closeAction->setEnabled( false );
	 filePrintAction->setEnabled( false );
	 fileNewAction->setEnabled( false );
	 PresentAction->setEnabled( false );
	 AbsentAction->setEnabled( false );
	 LateAction->setEnabled( false );
	 FieldTripAction->setEnabled( false );
	 viewBehaviourAction->setEnabled( false );
	 deleteColAction->setEnabled( false );
	 // only admin task can be performed when the timetables are closed.
	 ClassCreatorAction->setEnabled( true );
}

void Regit::enableActions() {
	 fileSaveAction->setEnabled( true );
	 fileSaveAsAction->setEnabled( true );
	 closeAction->setEnabled( true );
	 filePrintAction->setEnabled( true );
	 fileNewAction->setEnabled( true );
	 PresentAction->setEnabled( true );
	 AbsentAction->setEnabled( true );
	 LateAction->setEnabled( true );
	 FieldTripAction->setEnabled( true );
	 viewBehaviourAction->setEnabled( true );
	 deleteColAction->setEnabled( true );
	 ClassCreatorAction->setEnabled( false );
}


void Regit::dayReport() {
	 QString comment, id, name;
	 QDate dob, doc;
	 int student = Table->currentRow();
	 int date = Table->currentColumn();
	 
	 if ( Table->currentSelection ()==-1) {
		  QMessageBox::information( this, "infobot", "No cell is selected"  );
		  return;
	 }
	 
	 // populate temp vars to pass to StudentDayStat
	 id = timetable->CurrentStudent[student].GetStudentID( );
	 name = timetable->CurrentStudent[student].GetStudentName( );
	 dob = timetable->CurrentStudent[student].QGetStudentAge( );
	 doc = timetable->PeekDateValue( date );
	 comment = timetable->CurrentStudent[student].PeekBehaviour( date );    
	 
	 if( !timetable->CurrentStudent[student].PeekBehaviour( date ).isNull() ) { 
		  StudentDayStat* sds;
		  sds = new StudentDayStat( );
		  sds->populater( id, name, dob, doc, comment );
		  sds->show();
	 }
}


bool Regit::findBehaviour() {
	 int row = Table->currentRow();
	 int col = Table->currentColumn();    
	 bool behaviour; behaviour = false;
	 behaviour = ( timetable->CurrentStudent[row].PeekBehaviour( col ) != "No Comment" );
	 if( !Table->text(row, col ).isNull() )
		  behaviour = true;
	 return behaviour;
}


void Regit::setPath( QString npath )
{
	 appDir = npath;
}

void Regit::moveDown() {
	 Table->setCurrentCell( Table->currentRow()+1, Table->currentColumn() );
}


QString Regit::getPath()
{
	 return appDir;
}
