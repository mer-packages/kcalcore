#ifndef _KPIMUTILS_EMAIL_H_
#define _KPIMUTILS_EMAIL_H_

namespace KPIMUtils {
  bool extractEmailAddressAndName( const QString &aStr,
                                   QString &mail, QString &name )
  {
    name.clear();
    mail.clear();

    const int len = aStr.length();
    const char cQuotes = '"';

    bool bInComment = false;
    bool bInQuotesOutsideOfEmail = false;
    int i=0, iAd=0, iMailStart=0, iMailEnd=0;
    QChar c;
    unsigned int commentstack = 0;

    // Find the '@' of the email address
    // skipping all '@' inside "(...)" comments:
    while ( i < len ) {
      c = aStr[i];
      if ( '(' == c ) {
        commentstack++;
      }
      if ( ')' == c ) {
        commentstack--;
      }
      bInComment = commentstack != 0;
      if ( '"' == c && !bInComment ) {
        bInQuotesOutsideOfEmail = !bInQuotesOutsideOfEmail;
      }

      if( !bInComment && !bInQuotesOutsideOfEmail ) {
        if ( '@' == c ) {
          iAd = i;
          break; // found it
        }
      }
      ++i;
    }

    if ( !iAd ) {
      // We suppose the user is typing the string manually and just
      // has not finished typing the mail address part.
      // So we take everything that's left of the '<' as name and the rest as mail
      for ( i = 0; len > i; ++i ) {
        c = aStr[i];
        if ( '<' != c ) {
          name.append( c );
        } else {
          break;
        }
      }
      mail = aStr.mid( i + 1 );
      if ( mail.endsWith( '>' ) ) {
        mail.truncate( mail.length() - 1 );
      }

    } else {
      // Loop backwards until we find the start of the string
      // or a ',' that is outside of a comment
      //          and outside of quoted text before the leading '<'.
      bInComment = false;
      bInQuotesOutsideOfEmail = false;
      for ( i = iAd-1; 0 <= i; --i ) {
        c = aStr[i];
        if ( bInComment ) {
          if ( '(' == c ) {
            if ( !name.isEmpty() ) {
              name.prepend( ' ' );
            }
            bInComment = false;
          } else {
            name.prepend( c ); // all comment stuff is part of the name
          }
        } else if ( bInQuotesOutsideOfEmail ) {
          if ( cQuotes == c ) {
            bInQuotesOutsideOfEmail = false;
          } else {
            name.prepend( c );
          }
        } else {
          // found the start of this addressee ?
          if ( ',' == c ) {
            break;
          }
          // stuff is before the leading '<' ?
          if ( iMailStart ) {
            if ( cQuotes == c ) {
              bInQuotesOutsideOfEmail = true; // end of quoted text found
            } else {
              name.prepend( c );
            }
          } else {
            switch ( c.toLatin1() ) {
            case '<':
              iMailStart = i;
              break;
            case ')':
              if ( !name.isEmpty() ) {
                name.prepend( ' ' );
              }
              bInComment = true;
              break;
            default:
              if ( ' ' != c ) {
                mail.prepend( c );
              }
            }
          }
        }
      }

      name = name.simplified();
      mail = mail.simplified();

      if ( mail.isEmpty() ) {
        return false;
      }

      mail.append( '@' );

      // Loop forward until we find the end of the string
      // or a ',' that is outside of a comment
      //          and outside of quoted text behind the trailing '>'.
      bInComment = false;
      bInQuotesOutsideOfEmail = false;
      int parenthesesNesting = 0;
      for ( i = iAd+1; len > i; ++i ) {
        c = aStr[i];
        if ( bInComment ) {
          if ( ')' == c ) {
            if ( --parenthesesNesting == 0 ) {
              bInComment = false;
              if ( !name.isEmpty() ) {
                name.append( ' ' );
              }
            } else {
              // nested ")", add it
              name.append( ')' ); // name can't be empty here
            }
          } else {
            if ( '(' == c ) {
              // nested "("
              ++parenthesesNesting;
            }
            name.append( c ); // all comment stuff is part of the name
          }
        } else if ( bInQuotesOutsideOfEmail ) {
          if ( cQuotes == c ) {
            bInQuotesOutsideOfEmail = false;
          } else {
            name.append( c );
          }
        } else {
          // found the end of this addressee ?
          if ( ',' == c ) {
            break;
          }
          // stuff is behind the trailing '>' ?
          if ( iMailEnd ){
            if ( cQuotes == c ) {
              bInQuotesOutsideOfEmail = true; // start of quoted text found
            } else {
              name.append( c );
            }
          } else {
            switch ( c.toLatin1() ) {
            case '>':
              iMailEnd = i;
              break;
            case '(':
              if ( !name.isEmpty() ) {
                name.append( ' ' );
              }
              if ( ++parenthesesNesting > 0 ) {
                bInComment = true;
              }
              break;
            default:
              if ( ' ' != c ) {
                mail.append( c );
              }
            }
          }
        }
      }
    }

    name = name.simplified();
    mail = mail.simplified();

    return ! ( name.isEmpty() || mail.isEmpty() );
  }
}

#endif
