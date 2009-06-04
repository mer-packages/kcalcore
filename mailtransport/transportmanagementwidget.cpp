/*
    Copyright (c) 2006 - 2007 Volker Krause <vkrause@kde.org>

    Based on KMail code by:
    Copyright (C) 2001-2003 Marc Mutz <mutz@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "transportmanagementwidget.h"
#include "addtransportassistant.h"
#include "ui_transportmanagementwidget.h"
#include "transportmanager.h"
#include "transport.h"
#include "transportconfigdialog.h"

#include <QPointer>

using namespace MailTransport;

class TransportManagementWidget::Private
{
  public:
    Ui::TransportManagementWidget ui;
};

TransportManagementWidget::TransportManagementWidget( QWidget *parent )
  : QWidget( parent ), d( new Private )
{
  KGlobal::locale()->insertCatalog( QString::fromLatin1( "libmailtransport" ) );
  d->ui.setupUi( this );
  updateButtonState();

  connect( d->ui.transportList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
           SLOT(updateButtonState()) );
  connect( d->ui.transportList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
           SLOT(editClicked()) );
  connect( d->ui.addButton, SIGNAL(clicked()), SLOT(addClicked()) );
  connect( d->ui.editButton, SIGNAL(clicked()), SLOT(editClicked()) );
  connect( d->ui.renameButton, SIGNAL(clicked()), SLOT(renameClicked()) );
  connect( d->ui.removeButton, SIGNAL(clicked()), SLOT(removeClicked()) );
  connect( d->ui.defaultButton, SIGNAL(clicked()), SLOT(defaultClicked()) );
}

TransportManagementWidget::~TransportManagementWidget()
{
  delete d;
}

void TransportManagementWidget::updateButtonState()
{
  // TODO figure out current item vs. selected item -> using both ATM
  if ( !d->ui.transportList->currentItem() ) {
    d->ui.editButton->setEnabled( false );
    d->ui.renameButton->setEnabled( false );
    d->ui.removeButton->setEnabled( false );
    d->ui.defaultButton->setEnabled( false );
  } else {
    d->ui.editButton->setEnabled( true );
    d->ui.renameButton->setEnabled( true );
    d->ui.removeButton->setEnabled( true );
    if ( d->ui.transportList->currentItem()->data( 0, Qt::UserRole ) ==
         TransportManager::self()->defaultTransportId() ) {
      d->ui.defaultButton->setEnabled( false );
    } else {
      d->ui.defaultButton->setEnabled( true );
    }
  }
}

void TransportManagementWidget::addClicked()
{
  QPointer<AddTransportAssistant> ass = new AddTransportAssistant( this );
  ass->exec();
  delete ass;
}

void TransportManagementWidget::editClicked()
{
  Q_ASSERT( d->ui.transportList->currentItem() );

  int currentId = d->ui.transportList->currentItem()->data( 0, Qt::UserRole ).toInt();
  Transport *transport = TransportManager::self()->transportById( currentId );
  Q_ASSERT( transport );
  transport = transport->clone();
  QPointer<TransportConfigDialog> dlg = new TransportConfigDialog( transport, this );
  dlg->setCaption( i18nc( "@title:window", "Modify Transport" ) );
  dlg->exec();
  delete dlg;
  delete transport;
}

void TransportManagementWidget::renameClicked()
{
  // TODO test all of these for cases when the transport is removed from outside
  Q_ASSERT( d->ui.transportList->currentItem() );

  d->ui.transportList->editItem( d->ui.transportList->currentItem(), 0 );
}

void TransportManagementWidget::removeClicked()
{
  Q_ASSERT( d->ui.transportList->currentItem() );

  TransportManager::self()->removeTransport(
        d->ui.transportList->currentItem()->data( 0, Qt::UserRole ).toInt() );
}

void TransportManagementWidget::defaultClicked()
{
  Q_ASSERT( d->ui.transportList->currentItem() );

  TransportManager::self()->setDefaultTransport(
        d->ui.transportList->currentItem()->data( 0, Qt::UserRole ).toInt() );
}

#include "transportmanagementwidget.moc"
