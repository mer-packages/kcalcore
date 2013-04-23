/*
 * @file qtest_kde.h
 *
 * Simple kcal porting stuff for Maemo.
 *
  Contact: Alvaro Manera <alvaro.manera@nokia.com>

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
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
 */

#ifndef _MEEGO_PORT_H_
#define _MEEGO_PORT_H_

/** Definitions for kcalcore library **/

#include <QCoreApplication>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QUrl>

#include <kdatetime.h>
#include <ksystemtimezone.h>

#include <cstdlib>

#define kDebug(x) qDebug() << __FILE__":" << __LINE__ << "-"
#define kWarning(x) qWarning() << __FILE__":" << __LINE__ << "-"
#define kError(x) qCritical() << __FILE__":" << __LINE__ << "-"


class KStringHandler 
{
 public:

  static QStringList perlSplit(const QRegExp & sep, const QString & s, int max)
  {
    bool ignoreMax = 0 == max;

    QStringList l;

    int searchStart = 0;
    int tokenStart = sep.indexIn(s, searchStart);
    int len = sep.matchedLength();

    while (-1 != tokenStart && (ignoreMax || l.count() < max - 1)) {
      if (!s.mid(searchStart, tokenStart - searchStart).isEmpty())
	l << s.mid(searchStart, tokenStart - searchStart);

      searchStart = tokenStart + len;
      tokenStart = sep.indexIn(s, searchStart);
      len = sep.matchedLength();
    }

    if (!s.mid(searchStart, s.length() - searchStart).isEmpty())
      l << s.mid(searchStart, s.length() - searchStart);

    return l;
  }
};

class KConfig 
{
 public:
  KConfig(const QLatin1String&)
  {
  }

  void reparseConfiguration()
  {
  }
};

class KConfigGroup 
{
 public:
  KConfigGroup(const KConfig*, const char*)
  {
  }
  
  QString readEntry(const char*)
  {
    return 0;
  }
};

class KSaveFile : public QFile 
{
 public:
  // TODO unimplemented
  static bool backupFile(const QString& /*filename*/)
  {
    return true;
  }

 KSaveFile(const QString& filename)
   : QFile(filename)
  {
  }

  bool open()
  {
    return QFile::open(QIODevice::WriteOnly | QIODevice::Text);
  }

  bool finalize()
  {
    return QFile::flush();
  }
};

namespace KRandom 
{
  inline int random()
  {
    return rand();
  }
}


class KUrl : public QUrl
{
 public:
  KUrl(QString uri) 
    : QUrl(uri)
  {
  }
};

class KLocale
{
 public:
  KLocale();

  enum DateFormat {
    ShortDate,      /**< Short (numeric) date format, e.g. 08-04-2007 */
    LongDate,       /**< Long (text) date format, e.g. Sunday 08 April 2007 */
    FancyShortDate, /**< Same as ShortDate for dates a week or more ago. For more
		       recent dates, it is represented as Today, Yesterday, or
		       the weekday name. */
    FancyLongDate   /**< Same as LongDate for dates a week or more ago. For more
		       recent dates, it is represented as Today, Yesterday, or
		       the weekday name. */
  };

  enum ReadDateFlags {
    NormalFormat = 1,  ///< Only accept a date string in normal (long) format
    ShortFormat = 2    ///< Only accept a date string in short format
  };

  static QString formatTime(const QTime &pTime, bool includeSecs = false, bool isDuration = false);
  static QString fancyDate(const QDate &date, int days);
  static QString formatDate(const QDate &pDate, DateFormat format);
  static QString formatDateTime(const QDateTime &dateTime,DateFormat format, 
				bool includeSeconds = false, int daysTo = 0);
  static QString dateFormatShort();
  static QString dateFormat();
  static QString timeFormat();

  static QDate readDate(const QString& str, bool *ok);
  static QDate readDate(const QString& str, const QString& fmt, bool *ok);
  static QDate readDate(const QString& str, const ReadDateFlags& flags, bool *ok);
  static int weekStartDay();


  QString decimalSymbol();
  static QLatin1String language();

 private:
  QString ds;

};

class KGlobal
{
  public:
  static KLocale* locale();
  static KLocale* plocale;
};


class MaemoQString : public QString 
{
 public:
  MaemoQString(const QString str)
  {
    str_ = str;
  }

  QString& toString(const KLocale*)
  {
    return str_;
  }

 private:
  QString str_;
};

inline MaemoQString ki18n(const char* str)
{
  return MaemoQString(QObject::tr(str));
}

inline MaemoQString ki18nc(const char* str1, const char* str2)
{
  // TODO strip @item tags
  return MaemoQString(QCoreApplication::translate(str1, str2));
}

#include "kdecore_export.h"

#include "kde_static.h"


/** Definitions for module tests **/

#include <iostream>
#include <string>
#include <QString>
#include <QtTest/QtTest>

#include <kdatetime.h>

using namespace std;

#define _TESTINPUT "./data/test_pilot.ics"

class KTemporaryFile : public QTemporaryFile
{
 public:
  void setSuffix(const QString &suffix) {  Q_UNUSED(suffix) }

};



QT_BEGIN_NAMESPACE

inline QDebug operator<<(QDebug os, const KDateTime& dateTime)
{
  os << dateTime.toString();
  return os;
}

inline QDebug operator<<(QDebug os, QByteArray& array)
{
  os << array.constData();
  return os;
}

QT_END_NAMESPACE

//Test cases need this

class KAboutData
{
 public:
  KAboutData(const char*, int, QString, const char*)
  {
  }
};

class KComponentData {
 public:
  KComponentData(KAboutData*)
  {
  }
};

class KCmdLineOptions {
 public:
  void add(const string&, QString)
  {
  }
};

class KCALCORE_EXPORT KCmdLineArgs
{
 public:
  static void init(int argc, char** argv, KAboutData*);
  static void addCmdLineOptions(KCmdLineOptions&);
  static KCmdLineArgs* parsedArgs();
  int count();
  void usage(const char* usage);
  QString arg(int num);
  bool isSet(const string&);

 private:
  static int argc_;
  static char** argv_;
};

#endif
