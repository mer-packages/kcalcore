/*
    Copyright (c) 2007 Tobias Koenig <tokoe@kde.org>

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

#ifndef AKONADI_ITEMDETAILSVIEW_H
#define AKONADI_ITEMDETAILSVIEW_H

#include "akonadi_export.h"

class QStringList;

namespace Akonadi {

class Item;

/**
 * This class can be used to implement item views.
 *
 * Item views are widgets that show information about one item
 * in the Akonadi storage. The presentation of the information
 * is up to the user of this class.
 *
 * @see ItemBrowser
 */
//FIXME_API: rename class to ItemMonitor
class AKONADI_EXPORT ItemDetailsView
{
  public:
    /**
     * Creates a new item details view.
     */
    ItemDetailsView();

    /**
     * Destroys the item details view.
     */
    virtual ~ItemDetailsView();

    /**
     * Sets the item that shall be watched.
     */
    void setItem( const Item &id );

    /**
     * Returns the currently watched item.
     */
     Item item() const;

  protected:
    /**
     * This method is called whenever the watched item has changed.
     *
     * @param item The data of the changed item.
     */
    virtual void itemChanged( const Item &item );

    /**
     * This method is called whenever the watched item has been removed.
     */
    virtual void itemRemoved();

    /**
     * This method returns the identifiers of the parts that shall be fetched
     * for the item.
     */
    virtual QStringList fetchPartIdentifiers() const;

  private:
    class Private;
    Private* const d;

    Q_DISABLE_COPY( ItemDetailsView )
};

}

#endif
