#ifndef DISTRIBUTIONLISTEDITORWIDGET_H
#define DISTRIBUTIONLISTEDITORWIDGET_H

/*                                                                      
    This file is part of KAddressBook.                                  
    Copyright (c) 2002 Mike Pilone <mpilone@slac.com>                   
                                                                        
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or   
    (at your option) any later version.                                 
                                                                        
    This program is distributed in the hope that it will be useful,     
    but WITHOUT ANY WARRANTY; without even the implied warranty of      
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        
    GNU General Public License for more details.                        
                                                                        
    You should have received a copy of the GNU General Public License   
    along with this program; if not, write to the Free Software         
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.           
                                                                        
    As a special exception, permission is given to link this program    
    with any edition of Qt, and distribute the resulting executable,    
    without including the source code for Qt in the source distribution.
*/                                                                      

#include <qwidget.h>

#include "distributionlist.h"

class QListViewItem;
class QString;
class KListView;

namespace KABC {

class AddressBook;
class AddresseeListViewItem;
class DistributionListEditorWidgetPrivate;
class DistributionListEditorWidget : public QWidget
{
  Q_OBJECT
  
  public:
    DistributionListEditorWidget(AddressBook *book, QWidget *parent, 
                                 const char *name = 0);
    ~DistributionListEditorWidget();
    
    void clear();
    
    void setDistributionList(DistributionList *list);
    DistributionList *distributionList();
    
  signals:
    void modified();
    
  protected slots:
    void add();
    void remove();
    void availableSelectionChanged();
    void selectedSelectionChanged();
    
  private:
    void initGUI();
    bool selectEntry(DistributionList::Entry &e);
    AddresseeListViewItem *findItem(KListView *view, const QString &uid);
    void moveItem(KListView *source, KListView *target);
    
    DistributionListEditorWidgetPrivate *d;
};

}
#endif
