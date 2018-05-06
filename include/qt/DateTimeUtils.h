/*
     File:       DateTimeUtils.h
 
     Contains:   International Date and Time Interfaces (previously in TextUtils)
 
     Version:    QuickTime 7.3
 
     Copyright:  (c) 2007 (c) 1994-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DATETIMEUTILS__
#define __DATETIMEUTILS__

#ifndef __CONDITIONALMACROS__
#include "ConditionalMacros.h"
#endif

#ifndef __MACTYPES__
#include "MacTypes.h"
#endif

#ifndef __UTCUTILS__
#include "UTCUtils.h"
#endif

#ifndef __CFDATE__
#include "CFDate.h"
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*

    Here are the current routine names and the translations to the older forms.
    Please use the newer forms in all new code and migrate the older names out of existing
    code as maintainance permits.
    
    New Name                    Old Name(s)
    
    DateString                  IUDatePString IUDateString 
    InitDateCache
    LongDateString              IULDateString
    LongTimeString              IULTimeString
    StringToDate                String2Date
    StringToTime                                
    TimeString                  IUTimeString IUTimePString
    LongDateToSeconds           LongDate2Secs
    LongSecondsToDate           LongSecs2Date
    DateToSeconds               Date2Secs
    SecondsToDate               Secs2Date


    Carbon only supports the new names.  The old names are undefined for Carbon targets.
    This is true for C, Assembly and Pascal.
    
    InterfaceLib always has exported the old names.  For C macros have been defined to allow
    the use of the new names.  For Pascal and Assembly using the new names will result
    in link errors. 
    
*/

typedef SInt16 ToggleResults;
enum {
                                        /* Toggle results */
  toggleUndefined               = 0,
  toggleOK                      = 1,
  toggleBadField                = 2,
  toggleBadDelta                = 3,
  toggleBadChar                 = 4,
  toggleUnknown                 = 5,
  toggleBadNum                  = 6,
  toggleOutOfRange              = 7,    /*synonym for toggleErr3*/
  toggleErr3                    = 7,
  toggleErr4                    = 8,
  toggleErr5                    = 9
};

enum {
                                        /* Date equates */
  smallDateBit                  = 31,   /*Restrict valid date/time to range of Time global*/
  togChar12HourBit              = 30,   /*If toggling hour by char, accept hours 1..12 only*/
  togCharZCycleBit              = 29,   /*Modifier for togChar12HourBit: accept hours 0..11 only*/
  togDelta12HourBit             = 28,   /*If toggling hour up/down, restrict to 12-hour range (am/pm)*/
  genCdevRangeBit               = 27,   /*Restrict date/time to range used by genl CDEV*/
  validDateFields               = -1,
  maxDateField                  = 10
};

enum {
  eraMask                       = 0x0001,
  yearMask                      = 0x0002,
  monthMask                     = 0x0004,
  dayMask                       = 0x0008,
  hourMask                      = 0x0010,
  minuteMask                    = 0x0020,
  secondMask                    = 0x0040,
  dayOfWeekMask                 = 0x0080,
  dayOfYearMask                 = 0x0100,
  weekOfYearMask                = 0x0200,
  pmMask                        = 0x0400,
  dateStdMask                   = 0x007F /*default for ValidDate flags and ToggleDate TogglePB.togFlags*/
};

typedef SInt8 LongDateField;
enum {
  eraField                      = 0,
  yearField                     = 1,
  monthField                    = 2,
  dayField                      = 3,
  hourField                     = 4,
  minuteField                   = 5,
  secondField                   = 6,
  dayOfWeekField                = 7,
  dayOfYearField                = 8,
  weekOfYearField               = 9,
  pmField                       = 10,
  res1Field                     = 11,
  res2Field                     = 12,
  res3Field                     = 13
};

typedef SInt8 DateForm;
enum {
  shortDate                     = 0,
  longDate                      = 1,
  abbrevDate                    = 2
};

enum {
                                        /* StringToDate status values */
  fatalDateTime                 = 0x8000, /* StringToDate and String2Time mask to a fatal error */
  longDateFound                 = 1,    /* StringToDate mask to long date found */
  leftOverChars                 = 2,    /* StringToDate & Time mask to warn of left over characters */
  sepNotIntlSep                 = 4,    /* StringToDate & Time mask to warn of non-standard separators */
  fieldOrderNotIntl             = 8,    /* StringToDate & Time mask to warn of non-standard field order */
  extraneousStrings             = 16,   /* StringToDate & Time mask to warn of unparsable strings in text */
  tooManySeps                   = 32,   /* StringToDate & Time mask to warn of too many separators */
  sepNotConsistent              = 64,   /* StringToDate & Time mask to warn of inconsistent separators */
  tokenErr                      = 0x8100, /* StringToDate & Time mask for 'tokenizer err encountered' */
  cantReadUtilities             = 0x8200,
  dateTimeNotFound              = 0x8400,
  dateTimeInvalid               = 0x8800
};

typedef short                           StringToDateStatus;
typedef StringToDateStatus              String2DateStatus;
struct DateCacheRecord {
  short               hidden[256];            /* only for temporary use */
};
typedef struct DateCacheRecord          DateCacheRecord;
typedef DateCacheRecord *               DateCachePtr;
struct DateTimeRec {
  short               year;
  short               month;
  short               day;
  short               hour;
  short               minute;
  short               second;
  short               dayOfWeek;
};
typedef struct DateTimeRec              DateTimeRec;

typedef SInt64                          LongDateTime;
#if TARGET_RT_BIG_ENDIAN
union LongDateCvt {
  SInt64              c;
  struct {
    UInt32              lHigh;
    UInt32              lLow;
  }                       hl;
};
typedef union LongDateCvt               LongDateCvt;
#else
union LongDateCvt {
  SInt64              c;
  struct {
    UInt32              lLow;
    UInt32              lHigh;
  }                       hl;
};
typedef union LongDateCvt               LongDateCvt;
#endif  /* TARGET_RT_BIG_ENDIAN */

union LongDateRec {
  struct {
    short               era;
    short               year;
    short               month;
    short               day;
    short               hour;
    short               minute;
    short               second;
    short               dayOfWeek;
    short               dayOfYear;
    short               weekOfYear;
    short               pm;
    short               res1;
    short               res2;
    short               res3;
  }                       ld;
  short               list[14];               /*Index by LongDateField!*/
  struct {
    short               eraAlt;
    DateTimeRec         oldDate;
  }                       od;
};
typedef union LongDateRec               LongDateRec;

typedef SInt8                           DateDelta;
struct TogglePB {
  long                togFlags;               /*caller normally sets low word to dateStdMask=$7F*/
  ResType             amChars;                /*from 'itl0', but uppercased*/
  ResType             pmChars;                /*from 'itl0', but uppercased*/
  long                reserved[4];
};
typedef struct TogglePB                 TogglePB;
/*
    Conversion utilities between CF and Carbon time types. 
*/
/*
 *  UCConvertUTCDateTimeToCFAbsoluteTime()
 *  
 *  Discussion:
 *    Use UCConvertUTCDateTimeToCFAbsoluteTime to convert from a
 *    UTCDDateTime to a CFAbsoluteTime. Remember that the epoch for
 *    UTCDateTime is January 1, 1904 while the epoch for CFAbsoluteTime
 *    is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iUTCDate:
 *      A pointer to a UTCDateTime struct that represents the time you
 *      wish to convert from.
 *    
 *    oCFTime:
 *      A pointer to a CFAbsoluteTime. On successful return, this will
 *      contain the converted time from the input time type.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertUTCDateTimeToCFAbsoluteTime(
  const UTCDateTime *  iUTCDate,
  CFAbsoluteTime *     oCFTime);


/*
 *  UCConvertSecondsToCFAbsoluteTime()
 *  
 *  Discussion:
 *    Use UCConvertSecondsToCFAbsoluteTime to convert from the normal
 *    seconds representation of time to a CFAbsoluteTime. Remember that
 *    the epoch for seconds is January 1, 1904 while the epoch for
 *    CFAbsoluteTime is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iSeconds:
 *      A UInt32 value that represents the time you wish to convert
 *      from.
 *    
 *    oCFTime:
 *      A pointer to a CFAbsoluteTime. On successful return, this will
 *      contain the converted time from the input time type.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertSecondsToCFAbsoluteTime(
  UInt32            iSeconds,
  CFAbsoluteTime *  oCFTime);


/*
 *  UCConvertLongDateTimeToCFAbsoluteTime()
 *  
 *  Discussion:
 *    Use UCConvertLongDateTimeToCFAbsoluteTime to convert from a
 *    LongDateTime to a CFAbsoluteTime. Remember that the epoch for
 *    LongDateTime is January 1, 1904 while the epoch for
 *    CFAbsoluteTime is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iLongTime:
 *      A LongDateTime value that represents the time you wish to
 *      convert from.
 *    
 *    oCFTime:
 *      A pointer to a CFAbsoluteTime. On successful return, this will
 *      contain the converted time from the input time type.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertLongDateTimeToCFAbsoluteTime(
  LongDateTime      iLongTime,
  CFAbsoluteTime *  oCFTime);


/*
 *  UCConvertCFAbsoluteTimeToUTCDateTime()
 *  
 *  Discussion:
 *    Use UCConvertCFAbsoluteTimeToUTCDateTime to convert from a
 *    CFAbsoluteTime to a UTCDateTime. Remember that the epoch for
 *    UTCDateTime is January 1, 1904 while the epoch for CFAbsoluteTime
 *    is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iCFTime:
 *      A CFAbsoluteTime value that represents the time you wish to
 *      convert from.
 *    
 *    oUTCDate:
 *      A pointer to a UTCDateTime. On successful return, this will
 *      contain the converted time from the CFAbsoluteTime input.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertCFAbsoluteTimeToUTCDateTime(
  CFAbsoluteTime   iCFTime,
  UTCDateTime *    oUTCDate);


/*
 *  UCConvertCFAbsoluteTimeToSeconds()
 *  
 *  Discussion:
 *    Use UCConvertCFAbsoluteTimeToSeconds to convert from a
 *    CFAbsoluteTime to a UInt32 representation of seconds. Remember
 *    that the epoch for seconds is January 1, 1904 while the epoch for
 *    CFAbsoluteTime is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iCFTime:
 *      A CFAbsoluteTime value that represents the time you wish to
 *      convert from.
 *    
 *    oSeconds:
 *      A pointer to a UInt32. On successful return, this will contain
 *      the converted time from the CFAbsoluteTime input.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertCFAbsoluteTimeToSeconds(
  CFAbsoluteTime   iCFTime,
  UInt32 *         oSeconds);


/*
 *  UCConvertCFAbsoluteTimeToLongDateTime()
 *  
 *  Discussion:
 *    Use UCConvertCFAbsoluteTimeToLongDateTime to convert from a
 *    CFAbsoluteTime to a LongDateTime. Remember that the epoch for
 *    LongDateTime is January 1, 1904 while the epoch for
 *    CFAbsoluteTime is January 1, 2001.
 *  
 *  Parameters:
 *    
 *    iCFTime:
 *      A CFAbsoluteTime value that represents the time you wish to
 *      convert from.
 *    
 *    oLongDate:
 *      A pointer to a LongDateTime. On successful return, this will
 *      contain the converted time from the CFAbsoluteTime input.
 *  
 *  Result:
 *    A result code indicating whether or not conversion was successful.
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Mac OS X:         in version 10.2 and later
 */
EXTERN_API_C( OSStatus )
UCConvertCFAbsoluteTimeToLongDateTime(
  CFAbsoluteTime   iCFTime,
  LongDateTime *   oLongDate);



/*
    These routine are available in Carbon with their new name
*/
/*
 *  DateString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
DateString(
  long       dateTime,
  DateForm   longFlag,
  Str255     result,
  Handle     intlHandle)                                      THREEWORDINLINE(0x3F3C, 0x000E, 0xA9ED);


/*
 *  TimeString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
TimeString(
  long      dateTime,
  Boolean   wantSeconds,
  Str255    result,
  Handle    intlHandle)                                       THREEWORDINLINE(0x3F3C, 0x0010, 0xA9ED);


/*
 *  LongDateString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
LongDateString(
  const LongDateTime *  dateTime,
  DateForm              longFlag,
  Str255                result,
  Handle                intlHandle)                           THREEWORDINLINE(0x3F3C, 0x0014, 0xA9ED);


/*
 *  LongTimeString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
LongTimeString(
  const LongDateTime *  dateTime,
  Boolean               wantSeconds,
  Str255                result,
  Handle                intlHandle)                           THREEWORDINLINE(0x3F3C, 0x0016, 0xA9ED);



/*
    These routine are available in Carbon and InterfaceLib with their new name
*/
/*
 *  InitDateCache()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( OSErr )
InitDateCache(DateCachePtr theCache)                          FOURWORDINLINE(0x2F3C, 0x8204, 0xFFF8, 0xA8B5);


/*
 *  StringToDate()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( StringToDateStatus )
StringToDate(
  Ptr            textPtr,
  long           textLen,
  DateCachePtr   theCache,
  long *         lengthUsed,
  LongDateRec *  dateTime)                                    FOURWORDINLINE(0x2F3C, 0x8214, 0xFFF6, 0xA8B5);


/*
 *  StringToTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( StringToDateStatus )
StringToTime(
  Ptr            textPtr,
  long           textLen,
  DateCachePtr   theCache,
  long *         lengthUsed,
  LongDateRec *  dateTime)                                    FOURWORDINLINE(0x2F3C, 0x8214, 0xFFF4, 0xA8B5);


/*
 *  LongDateToSeconds()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
LongDateToSeconds(
  const LongDateRec *  lDate,
  LongDateTime *       lSecs)                                 FOURWORDINLINE(0x2F3C, 0x8008, 0xFFF2, 0xA8B5);


/*
 *  LongSecondsToDate()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
LongSecondsToDate(
  const LongDateTime *  lSecs,
  LongDateRec *         lDate)                                FOURWORDINLINE(0x2F3C, 0x8008, 0xFFF0, 0xA8B5);


/*
 *  ToggleDate()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( ToggleResults )
ToggleDate(
  LongDateTime *    lSecs,
  LongDateField     field,
  DateDelta         delta,
  short             ch,
  const TogglePB *  params)                                   FOURWORDINLINE(0x2F3C, 0x820E, 0xFFEE, 0xA8B5);


/*
 *  ValidDate()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( short )
ValidDate(
  const LongDateRec *  vDate,
  long                 flags,
  LongDateTime *       newSecs)                               FOURWORDINLINE(0x2F3C, 0x820C, 0xFFE4, 0xA8B5);


/*
 *  ReadDateTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter __D0 ReadDateTime(__A0)
#endif
EXTERN_API( OSErr )
ReadDateTime(unsigned long * time)                            ONEWORDINLINE(0xA039);


/*
 *  GetDateTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter GetDateTime(__A0)
#endif
EXTERN_API( void )
GetDateTime(unsigned long * secs)                             TWOWORDINLINE(0x20B8, 0x020C);


/*
 *  SetDateTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter __D0 SetDateTime(__D0)
#endif
EXTERN_API( OSErr )
SetDateTime(unsigned long time)                               ONEWORDINLINE(0xA03A);


/*
 *  SetTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter SetTime(__A0)
#endif
EXTERN_API( void )
SetTime(const DateTimeRec * d)                                TWOWORDINLINE(0xA9C7, 0xA03A);


/*
 *  GetTime()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter GetTime(__A0)
#endif
EXTERN_API( void )
GetTime(DateTimeRec * d)                                      THREEWORDINLINE(0x2038, 0x020C, 0xA9C6);


/*
 *  DateToSeconds()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
EXTERN_API( void )
DateToSeconds(
  const DateTimeRec *  d,
  unsigned long *      secs);


/*
 *  SecondsToDate()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Mac OS X:         in version 10.0 and later
 */
#if TARGET_OS_MAC && TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#pragma parameter SecondsToDate(__D0, __A0)
#endif
EXTERN_API( void )
SecondsToDate(
  unsigned long   secs,
  DateTimeRec *   d)                                          ONEWORDINLINE(0xA9C6);



/*
    These routine are available in InterfaceLib using their old name.
    Macros allow using the new names in all source code.
*/
#if CALL_NOT_IN_CARBON
/*
 *  IUDateString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IUDateString(
  long       dateTime,
  DateForm   longFlag,
  Str255     result)                                          TWOWORDINLINE(0x4267, 0xA9ED);


/*
 *  IUTimeString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IUTimeString(
  long      dateTime,
  Boolean   wantSeconds,
  Str255    result)                                           THREEWORDINLINE(0x3F3C, 0x0002, 0xA9ED);


/*
 *  IUDatePString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IUDatePString(
  long       dateTime,
  DateForm   longFlag,
  Str255     result,
  Handle     intlHandle)                                      THREEWORDINLINE(0x3F3C, 0x000E, 0xA9ED);


/*
 *  IUTimePString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IUTimePString(
  long      dateTime,
  Boolean   wantSeconds,
  Str255    result,
  Handle    intlHandle)                                       THREEWORDINLINE(0x3F3C, 0x0010, 0xA9ED);


/*
 *  IULDateString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IULDateString(
  LongDateTime *  dateTime,
  DateForm        longFlag,
  Str255          result,
  Handle          intlHandle)                                 THREEWORDINLINE(0x3F3C, 0x0014, 0xA9ED);


/*
 *  IULTimeString()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API( void )
IULTimeString(
  LongDateTime *  dateTime,
  Boolean         wantSeconds,
  Str255          result,
  Handle          intlHandle)                                 THREEWORDINLINE(0x3F3C, 0x0016, 0xA9ED);



#endif  /* CALL_NOT_IN_CARBON */

#if CALL_NOT_IN_CARBON
#define DateString(dateTime, longFlag, result, intlHandle) \
         IUDatePString( dateTime, longFlag, result, intlHandle)
#define TimeString(dateTime, wantSeconds, result, intlHandle) \
         IUTimePString(dateTime, wantSeconds, result, intlHandle)
#define LongDateString(dateTime, longFlag, result, intlHandle) \
         IULDateString(dateTime, longFlag, result, intlHandle)
#define LongTimeString(dateTime, wantSeconds, result, intlHandle) \
         IULTimeString(dateTime, wantSeconds, result, intlHandle)
#endif /* CALL_NOT_IN_CARBON */
#if OLDROUTINENAMES
#define String2Date(textPtr, textLen, theCache, lengthUsed, dateTime)  \
         StringToDate(textPtr, textLen, theCache, lengthUsed, dateTime)
#define String2Time(textPtr, textLen, theCache, lengthUsed, dateTime)  \
         StringToTime(textPtr, textLen, theCache, lengthUsed, dateTime)
#define LongDate2Secs(lDate, lSecs) LongDateToSeconds(lDate, lSecs)
#define LongSecs2Date(lSecs, lDate) LongSecondsToDate(lSecs, lDate)
#define Date2Secs(d, secs) DateToSeconds(d, secs)
#define Secs2Date(secs, d) SecondsToDate(secs, d)
#endif  /* OLDROUTINENAMES */

#if CALL_NOT_IN_CARBON
/*
 *  iudatestring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iudatestring(
  long       dateTime,
  DateForm   longFlag,
  char *     result);


/*
 *  iudatepstring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iudatepstring(
  long       dateTime,
  DateForm   longFlag,
  char *     result,
  Handle     intlHandle);


/*
 *  iutimestring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iutimestring(
  long      dateTime,
  Boolean   wantSeconds,
  char *    result);


/*
 *  iutimepstring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iutimepstring(
  long      dateTime,
  Boolean   wantSeconds,
  char *    result,
  Handle    intlHandle);


/*
 *  iuldatestring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iuldatestring(
  LongDateTime *  dateTime,
  DateForm        longFlag,
  char *          result,
  Handle          intlHandle);


/*
 *  iultimestring()
 *  
 *  Availability:
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    CarbonLib:        not available
 *    Mac OS X:         not available
 */
EXTERN_API_C( void )
iultimestring(
  LongDateTime *  dateTime,
  Boolean         wantSeconds,
  char *          result,
  Handle          intlHandle);


#endif  /* CALL_NOT_IN_CARBON */





#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DATETIMEUTILS__ */

