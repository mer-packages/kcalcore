/*
    This file is part of libkabc.
    Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include <kapplication.h>
#include <kstandarddirs.h>
#include <ksimpleconfig.h>
#include <kdebug.h>

#include "stdaddressbook.h"

#include "binaryformat.h"
#include "resourcefile.h"
#include "resourcesql.h"
#include "vcardformat.h"

using namespace KABC;

AddressBook *StdAddressBook::mSelf = 0;

QString StdAddressBook::fileName()
{
  return locateLocal( "data", "kabc/std.vcf" );
}

AddressBook *StdAddressBook::self()
{
  kdDebug(5700) << "StdAddressBook::self()" << endl;

  if ( !mSelf ) {
    mSelf = new StdAddressBook;
  }
  return mSelf;
}

bool StdAddressBook::save()
{
  kdDebug(5700) << "StdAddressBook::save()" << endl;
  Ticket *ticket = self()->requestSaveTicket();
  if ( !ticket ) {
    kdError() << "Can't save to standard addressbook. It's locked." << endl;
    return false;
  }
  return self()->save( ticket );
}


StdAddressBook::StdAddressBook()
{
    KSimpleConfig config( "kabcrc", true );
    config.setGroup( "General" );

    QStringList keys = config.readListEntry( "ResourceKeys" );
    bool firstResource = true;
    for ( QStringList::Iterator it = keys.begin(); it != keys.end(); ++it ) {
	config.setGroup( "Resource_" + (*it) );
	uint type = config.readNumEntry( "Type" );

	Resource *resource = 0;

	QString ident;
	switch ( type ) {
	    case RES_SQL:
		resource = new ResourceSql( this, &config );
		ident = ((ResourceSql*)resource)->identifier();
		break;
	    case RES_BINARY:
		resource = new ResourceFile( this, &config, new BinaryFormat );
		ident = ((ResourceFile*)resource)->identifier();
		break;
	    case RES_VCARD:
	    default:
		resource = new ResourceFile( this, &config, new VCardFormat );
		ident = ((ResourceFile*)resource)->identifier();
		break;
	}

	if ( addResource( resource ) ) {
	    mIdentifier += ident + ( firstResource ? "" : ":" );

	    if ( firstResource ) {
		firstResource = false;
		mName = config.readEntry( "Name" );
	    }
	}
    }

    if ( keys.count() == 0 ) {
	/* there is an empty config file, so we create a default resource */
	addResource( new ResourceFile( this, &config, new VCardFormat ) );
	mName = config.readEntry( "VCard-Default" );
    }

    load();
}

StdAddressBook::~StdAddressBook()
{
  save();
}

QString StdAddressBook::identifier()
{
    return mIdentifier;
}
