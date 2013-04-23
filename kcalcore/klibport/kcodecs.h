/*
   Copyright (C) 2000-2001 Dawit Alemayehu <adawit@kde.org>
   Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License (LGPL)
   version 2 as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

   RFC 1321 "MD5 Message-Digest Algorithm" Copyright (C) 1991-1992.             // krazy:exclude=copyright
   RSA Data Security, Inc. Created 1991. All rights reserved.

   The KMD5 class is based on a C++ implementation of
   "RSA Data Security, Inc. MD5 Message-Digest Algorithm" by
   Mordechai T. Abzug,	Copyright (c) 1995.  This implementation                // krazy:exclude=copyright
   passes the test-suite as defined in RFC 1321.

   The encoding and decoding utilities in KCodecs with the exception of
   quoted-printable are based on the java implementation in HTTPClient
   package by Ronald Tschalär Copyright (C) 1996-1999.                          // krazy:exclude=copyright

   The quoted-printable codec as described in RFC 2045, section 6.7. is by
   Rik Hemsley (C) 2001.
*/

#ifndef KCODECS_H
#define KCODECS_H

#define KBase64 KCodecs

#include "kcalcore_export.h"

#include <QString>

class QByteArray;
class QIODevice;

/**
 * A wrapper class for the most commonly used encoding and
 * decoding algorithms.  Currently there is support for encoding
 * and decoding input using base64, uu and the quoted-printable
 * specifications.
 *
 * \b Usage:
 *
 * \code
 * QByteArray input = "Aladdin:open sesame";
 * QByteArray result = KCodecs::base64Encode(input);
 * cout << "Result: " << result.data() << endl;
 * \endcode
 *
 * <pre>
 * Output should be
 * Result: QWxhZGRpbjpvcGVuIHNlc2FtZQ==
 * </pre>
 *
 * The above example makes use of the convenience functions
 * (ones that accept/return null-terminated strings) to encode/decode
 * a string.  If what you need is to encode or decode binary data, then
 * it is highly recommended that you use the functions that take an input
 * and output QByteArray as arguments.  These functions are specifically
 * tailored for encoding and decoding binary data.
 *
 * @short A collection of commonly used encoding and decoding algorithms.
 * @author Dawit Alemayehu <adawit@kde.org>
 * @author Rik Hemsley <rik@kde.org>
 */
namespace KCodecs
{

  /**
   * Decodes the given data that was encoded using the
   * base64 algorithm.
   *
   * @param in   data to be decoded.
   * @return     decoded string.
   */
  KCALCORE_EXPORT QByteArray base64Decode( const QByteArray& in );

  /**
   * Decodes the given data that was encoded with the base64
   * algorithm.
   *
   * Use this function if you want the result of the decoding
   * to be placed in another array which cuts down the number
   * of copy operation that have to be performed in the process.
   * This is also the preferred method for decoding an encoded
   * binary data.
   *
   * NOTE: the output array is first reset and then resized
   * appropriately before use, hence, all data stored in the
   * output array will be lost.
   *
   * @param in   data to be decoded.
   * @param out  decoded data.
   */
  KCALCORE_EXPORT void base64Decode( const QByteArray& in, QByteArray& out );


  /**
   * Decodes string @p text according to RFC2047,
   * i.e., the construct =?charset?[qb]?encoded?=
   *
   * Note: a more rubust version of this function is included in kdepimlibs/libkmime
   *
   * @param text source string
   * @returns the decoded string
   */
  KCALCORE_EXPORT QString decodeRFC2047String(const QString &text);

  /**
   * Encodes the given data using the quoted-printable algorithm.
   *
   * @param in data to be encoded
   * @param out encoded data
   * @param useCRLF if true the input data is expected to have CRLF line breaks
   *        and the output will have CRLF line breaks, too
   */
  KCALCORE_EXPORT void quotedPrintableEncode(const QByteArray& in, QByteArray& out, bool useCRLF);

}

#endif // KCODECS_H
