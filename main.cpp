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
#include <qapplication.h>
#include "Regit.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );
    Regit myRegit;
    app.setMainWidget( &myRegit );
    myRegit.setPath( app.applicationDirPath() );
    myRegit.show();

    return app.exec();
}
