/*
  This file is part of the kcal library.

  Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
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

#include "meego_port.h"
#include "global.h"


KLocale* KGlobal::plocale = 0;

KLocale* KGlobal::locale()
{
  return plocale;
}

static inline void put_it_in( QChar *buffer, int& index, const QString &s )
{
  for ( int l = 0; l < s.length(); l++ )
    buffer[index++] = s.at( l );
}

static inline void put_it_in( QChar *buffer, int& index, int number )
{ 
  buffer[index++] = number / 10 + '0';
  buffer[index++] = number % 10 + '0';
}


QString KLocale::formatTime(const QTime &pTime, bool includeSecs, bool isDuration)
{

    const QString rst = timeFormat();
    //const QString rst = "%H:%M:%S";

    // only "pm/am" here can grow, the rest shrinks, but
    // I'm rather safe than sorry
    QChar *buffer = new QChar[rst.length() * 3 / 2 + 30];

    int index = 0;
    bool escape = false;
    int number = 0;

    for ( int format_index = 0; format_index < rst.length(); format_index++ ) {
      if ( !escape ) {
	if ( rst.at( format_index ).unicode() == '%' )
	  escape = true;
	else
	  buffer[index++] = rst.at( format_index );
      }
      else {
	switch ( rst.at( format_index ).unicode() ) {
	case '%':
	  buffer[index++] = '%';
	  break;
	case 'H':
	  put_it_in( buffer, index, pTime.hour() );
	  break;
	case 'I':
	  if ( isDuration )
	    put_it_in( buffer, index, pTime.hour() );
	  else
	    put_it_in( buffer, index, ( pTime.hour() + 11) % 12 + 1 );
	  break;
	case 'M':
	  put_it_in( buffer, index, pTime.minute() );
	  break;
	case 'S':
	  
	  if (includeSecs)
	    put_it_in( buffer, index, pTime.second() );
	  else if (index > 0) {
	    // remove spaces (#164813)
	    while(index > 0 && buffer[index-1].isSpace())
	      --index;
	    // we remove the separator sign before the seconds and
	    // assume that works everywhere
	    --index;
	    // remove spaces (#164813)
	    while(index > 0 && buffer[index-1].isSpace())
	      --index;
	    break;
	  }
	  break;
	case 'k':
	  number = pTime.hour();
	case 'l':
	  // to share the code
	  if ( rst.at( format_index ).unicode() == 'l' )
	    number = isDuration ? pTime.hour() : (pTime.hour() + 11) % 12 + 1;
	  if ( number / 10 )
	    buffer[index++] = number / 10 + '0';
	  buffer[index++] = number % 10 + '0';
	  break;
	case 'p':
	  if ( !isDuration ) {
	    QString s;
	    if ( pTime.hour() >= 12 )
	      put_it_in( buffer, index, QObject::tr("pm") );
	    else
	      put_it_in( buffer, index, QObject::tr("am") );
	  }
	  break;
	default:
	  buffer[index++] = rst.at( format_index );
	  break;
	}
	escape = false;
      }
    }

    QString ret( buffer, index );
    delete [] buffer;
    if ( isDuration ) // eliminate trailing-space due to " %p"
      return ret.trimmed();
    else
      return ret;
}

QString KLocale::fancyDate(const QDate &date, int days)
{
    switch (days)
    {
        case 0:
            return QObject::tr("Today");
        case 1:
            return QObject::tr("Yesterday");
        default:
            return calendarsystem->weekDayName(date);
    }
}

QString KLocale::formatDate(const QDate &pDate, DateFormat format)
{
    if (format == FancyShortDate || format == FancyLongDate)
    {
        int days = pDate.daysTo(QDate::currentDate());
        if (days >= 0 && days < 7)
            return fancyDate(pDate, days);
        format = (format == FancyShortDate) ? ShortDate : LongDate;
    }
    const QString rst = (format == ShortDate) ? dateFormatShort() : dateFormat();
    //const QString rst = (format == ShortDate) ? "%Y-%m-%d" : "%A %d %B %Y";

    QString buffer;

    if ( ! pDate.isValid() || !calendarsystem) return buffer;

    bool escape = false;

    int year = calendarsystem->year(pDate);
    int month = calendarsystem->month(pDate);

    for ( int format_index = 0; format_index < rst.length(); ++format_index ) {
      if ( !escape ) {
	if ( rst.at( format_index ).unicode() == '%' )
	  escape = true;
	else
	  buffer.append(rst.at(format_index));
      }
      else {
	switch ( rst.at( format_index ).unicode() ) {
	case '%':
	  buffer.append(QLatin1Char('%'));
	  break;
	case 'Y':  //Long year numeric
	  buffer.append(calendarsystem->yearString(pDate, KCalendarSystem::LongFormat));
	  break;
	case 'y':  //Short year numeric
	  buffer.append(calendarsystem->yearString(pDate, KCalendarSystem::ShortFormat));
	  break;
	case 'n':  //Short month numeric
	  buffer.append(calendarsystem->monthString(pDate, KCalendarSystem::ShortFormat));
	  break;
	case 'e':  //Short day numeric
	  buffer.append(calendarsystem->dayString(pDate, KCalendarSystem::ShortFormat));
	  break;
	case 'm':  //Long month numeric
	  buffer.append(calendarsystem->monthString(pDate, KCalendarSystem::LongFormat));
	  break;
	case 'b':  //Short month name
	  // FIXME: Give the proper dateMonthNamePossessive
	  /*	      if (d->dateMonthNamePossessive)
		      buffer.append(calendarsystem->monthName(month, year, KCalendarSystem::ShortNamePossessive));
		      else*/
	  buffer.append(calendarsystem->monthName(month, year, KCalendarSystem::ShortName));
	  break;
	case 'B':  //Long month name
	  // FIXME: Give the proper dateMonthNamePossessive
	  /*              if (d->dateMonthNamePossessive)
			  buffer.append(calendarsystem->monthName(month, year, KCalendarSystem::LongNamePossessive));
			  else*/
	  buffer.append(calendarsystem->monthName(month, year, KCalendarSystem::LongName));
	  break;
	case 'd':  //Long day numeric
	  buffer.append(calendarsystem->dayString(pDate, KCalendarSystem::LongFormat));
	  break;
	case 'a':  //Short weekday name
	  buffer.append(calendarsystem->weekDayName(pDate, KCalendarSystem::ShortDayName));
	  break;
	case 'A':  //Long weekday name
	  buffer.append(calendarsystem->weekDayName(pDate, KCalendarSystem::LongDayName));
	  break;
	default:
	  buffer.append(rst.at(format_index));
	  break;
	}
	escape = false;
      }
    }
    return buffer;
}


QString KLocale::formatDateTime(const QDateTime &dateTime,
				DateFormat format, bool includeSeconds, int daysTo)
{
  QString dateStr = (format == FancyShortDate || format == FancyLongDate)
    ? fancyDate(dateTime.date(), daysTo)
    : formatDate(dateTime.date(), format);
  return QCoreApplication::translate("concatenation of dates and time", "%1 %2").arg(dateStr).arg(formatTime(dateTime.time(), includeSeconds));
}


int KLocale::weekStartDay()
{
  return 1;
}

QString KLocale::dateFormatShort()
{
  return "%Y-%m-%d";
}

QString KLocale::dateFormat()
{
  return "%A %d %B %Y";
}

QString KLocale::timeFormat()
{
  return "%H:%M:%S";
}


QDate KLocale::readDate(const QString& intstr, bool *ok)
{
  QDate date;
  date = readDate(intstr, ShortFormat, ok);
  if (date.isValid()) return date;
  return readDate(intstr, NormalFormat, ok);
}

QDate KLocale::readDate(const QString& intstr, const ReadDateFlags& flags, bool *ok)
{
  QString fmt = ((flags & ShortFormat) ? dateFormatShort() : dateFormat()).simplified();
  return readDate( intstr, fmt, ok );
}

QDate KLocale::readDate(const QString& intstr, const QString& fmt, bool *ok)
{

  QString str = intstr.simplified().toLower();
  int day = -1, month = -1;
  // allow the year to be omitted if not in the format
  int year = calendarsystem->year(QDate::currentDate());
  int strpos = 0;
  int fmtpos = 0;
  
  int iLength; // Temporary variable used when reading input
  
  bool error = false;
  
  while (fmt.length() > fmtpos && str.length() > strpos && !error) {
      
    QChar c = fmt.at(fmtpos++);
    
    if (c != '%') {
      if (c.isSpace() && str.at(strpos).isSpace())
	strpos++;
      else if (c != str.at(strpos++))
	error = true;
    }
    else {
      int j;
      // remove space at the beginning
      if (str.length() > strpos && str.at(strpos).isSpace())
	strpos++;
      
      c = fmt.at(fmtpos++);
      switch (c.unicode()) {
      case 'a':
      case 'A':
	
	error = true;
	j = 1;
	while (error && (j < 8)) {
	  QString s;
	  if ( c == 'a') {
	    s = calendarsystem->weekDayName(j, KCalendarSystem::ShortDayName).toLower();
	  } else {
	    s = calendarsystem->weekDayName(j, KCalendarSystem::LongDayName).toLower();
	  }
	  int len = s.length();
	  if (str.mid(strpos, len) == s) {
	    strpos += len;
	    error = false;
	  }
	  j++;
	}
	break;
	
      case 'b':
      case 'B':
	
	error = true;
	//TODO
	/*
	if (d->dateMonthNamePossessive) {
	  j = 1;
	  while (error && (j < 13)) {
	    QString s;
	    if ( c == 'b' ) {
	      //s = calendar()->monthName(j, year, KCalendarSystem::ShortNamePossessive).toLower();
	      s = calendarsystem->monthName(j, year, KCalendarSystem::ShortNamePossessive).toLower();
	    } else {
	      //s = calendar()->monthName(j, year, KCalendarSystem::LongNamePossessive).toLower();
	      s = calendarsystem->monthName(j, year, KCalendarSystem::LongNamePossessive).toLower();
	    }
	    int len = s.length();
	    if (str.mid(strpos, len) == s) {
	      month = j;
	      strpos += len;
	      error = false;
	    }
	    j++;
	  }
	} 
	*/
	j = 1;
	while (error && (j < 13)) {
	  QString s;
	  if ( c == 'b' ) {
	    s = calendarsystem->monthName(j, year, KCalendarSystem::ShortName).toLower();
	  } else {
	    s = calendarsystem->monthName(j, year, KCalendarSystem::LongName).toLower();
	  }
	  int len = s.length();
	  if (str.mid(strpos, len) == s) {
	    month = j;
	    strpos += len;
	    error = false;
	  }
	  j++;
	}
	break;
      case 'd':
      case 'e':
	day = calendarsystem->dayStringToInteger(str.mid(strpos), iLength);
	strpos += iLength;
	    
	error = iLength <= 0;
	break;
	
      case 'n':
      case 'm':
	month = calendarsystem->monthStringToInteger(str.mid(strpos), iLength);
	strpos += iLength;
	
	error = iLength <= 0;
	break;
	      
      case 'Y':
      case 'y':
	year = calendarsystem->yearStringToInteger(str.mid(strpos), iLength);
	strpos += iLength;
 
	error = iLength <= 0;
	break;
      }
    }
  }
 
  /* for a match, we should reach the end of both strings, not just one of
     them */
  if ( fmt.length() > fmtpos || str.length() > strpos ) {
    error = true;
  }
  
  
  if ( year != -1 && month != -1 && day != -1 && !error) {
    if (ok) *ok = true;
    
    QDate result;
    calendarsystem->setYMD(result, year, month, day);
 
    return result;
  }
  
  if (ok) *ok = false;
  return QDate(); // invalid date
}


KLocale::KLocale() : ds(QLocale::c().decimalPoint())
{
}

QString KLocale::decimalSymbol()
{
  return ds;
}

QLatin1String KLocale::language()
{
  QLocale::Language ln = QLocale::c().language();

  if (ln == QLocale::Hebrew)
    return QLatin1String("he");

  return QLatin1String("C");
}

int KCmdLineArgs::argc_ = 0;
char** KCmdLineArgs::argv_ = 0;

void KCmdLineArgs::init(int argc, char** argv, KAboutData*)
{
  argc_ = argc;
  argv_ = argv;
}

void KCmdLineArgs::addCmdLineOptions(KCmdLineOptions&)
{
}

KCmdLineArgs* KCmdLineArgs::parsedArgs()
{
  return new KCmdLineArgs();
}

int KCmdLineArgs::count()
{
  return argc_ - 1;
}

void KCmdLineArgs::usage(const char* usage)
{
  cerr << "usage: " << usage << endl;
}

QString KCmdLineArgs::arg(int num)
{
  return QString(argv_[num+1]);
}

bool KCmdLineArgs::isSet(const string&)
{
  return false;
}
