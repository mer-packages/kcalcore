/*
    This file is part of the kcal library.

     Copyright (C) 2004 Dirk Mueller <mueller@kde.org>

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
#ifndef KCAL_EXPORT_H
#define KCAL_EXPORT_H

#include <QObject>

#ifndef KCALCORE_EXPORT
#define KCALCORE_EXPORT __attribute__ ((visibility("default")))
#define KDECORE_EXPORT KCALCORE_EXPORT
#endif

#define KDE_DEPRECATED

#define KDE_CONSTRUCTOR_DEPRECATED

#ifdef COMPILING_TESTS
#ifndef KCAL_TEST_EXPORT
# if defined(MAKE_KCAL_TEST_LIB)
   /* We are building this library */
#  define KCAL_TEST_EXPORT KDE_EXPORT
# else
   /* We are using this library */
#  define KCAL_TEST_EXPORT KDE_IMPORT
# endif
#endif
#endif /* COMPILING_TESTS */

/**
  @namespace KCal

  @brief
  Contains all the KCal library global classes, objects, and functions.
*/

#if 0
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

#endif

#if 0
  enum ReadDateFlags {
      NormalFormat = 1,  ///< Only accept a date string in normal (long) format
      ShortFormat = 2    ///< Only accept a date string in short format
  };
#endif
#endif
