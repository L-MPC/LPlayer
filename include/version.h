#ifndef MPC_VERSION_H
#define MPC_VERSION_H

#include "mpc-hc_config.h"

#ifndef _T
#if !defined(ISPP_INVOKED) && (defined(UNICODE) || defined(_UNICODE))
#define _T(text)    L##text
#else
#define _T(text)    text
#endif
#endif

//#ifndef NO_VERSION_REV_NEEDED
//#include "..\build\version_rev.h"
//#endif

//#define MPCHC_HASH _T("MPlayer 1.0")
//#define MPC_VERSION_REV 40
//#define MPC_VERSION_ADDITIONAL _T(" (MPlayer 1.0)")
//#define GCC32_VERSION _T("-")
//#define GCC64_VERSION _T("-")

#define DO_MAKE_STR(x)          _T(#x)
#define MAKE_STR(x)             DO_MAKE_STR(x)

#define MPC_VERSION_MAJOR       1
#define MPC_VERSION_MINOR       0
#define MPC_VERSION_PATCH       0

#define MPC_VERSION_REV 40

#ifdef MPCHC_LITE
	#define MPCHC_IS_LITE trie
#else
	#define MPCHC_IS_LITE false
#endif

#ifndef NO_VERSION_REV_NEEDED

#if MPC_VERSION_REV > 0
#define MPC_NIGHTLY_RELEASE     1
#else
#define MPC_NIGHTLY_RELEASE     0
#endif

#endif // NO_VERSION_REV_NEEDED

#define MPC_COMP_NAME_STR       _T("-")
#define MPC_COPYRIGHT_STR       _T("Copyright (C) 2017")
#define MPC_VERSION_COMMENTS    _T("-")

#ifndef ISPP_INVOKED

#ifdef NO_VERSION_REV_NEEDED

//#define MPC_VERSION_NUM         MPC_VERSION_MAJOR,MPC_VERSION_MINOR,MPC_VERSION_PATCH,0
#define MPC_VERSION_NUM         MPC_VERSION_MAJOR,MPC_VERSION_MINOR,MPC_VERSION_PATCH
#define MPC_VERSION_STR         MAKE_STR(MPC_VERSION_MAJOR) _T(".") \
                                MAKE_STR(MPC_VERSION_MINOR) _T(".") \
                                MAKE_STR(MPC_VERSION_PATCH)
#define MPC_VERSION_STR_FULL    MPC_VERSION_STR

#else // !NO_VERSION_REV_NEEDED

//#define MPC_VERSION_NUM         MPC_VERSION_MAJOR,MPC_VERSION_MINOR,MPC_VERSION_PATCH,MPC_VERSION_REV
#define MPC_VERSION_NUM         MPC_VERSION_MAJOR,MPC_VERSION_MINOR,MPC_VERSION_PATCH

#if MPC_NIGHTLY_RELEASE

#define MPC_VERSION_STR         MAKE_STR(MPC_VERSION_MAJOR) _T(".") \
                                MAKE_STR(MPC_VERSION_MINOR) _T(".") \
                                MAKE_STR(MPC_VERSION_PATCH)
                                //MAKE_STR(MPC_VERSION_REV)
#define MPC_VERSION_STR_FULL    MAKE_STR(MPC_VERSION_MAJOR) _T(".") \
                                MAKE_STR(MPC_VERSION_MINOR) _T(".") \
                                MAKE_STR(MPC_VERSION_PATCH)
                                //MAKE_STR(MPC_VERSION_REV) \
                                //MPC_VERSION_ADDITIONAL

#else // !MPC_NIGHTLY_RELEASE

#define MPC_VERSION_STR         MAKE_STR(MPC_VERSION_MAJOR) _T(".") \
                                MAKE_STR(MPC_VERSION_MINOR) _T(".") \
                                MAKE_STR(MPC_VERSION_PATCH)
#define MPC_VERSION_STR_FULL    MAKE_STR(MPC_VERSION_MAJOR) _T(".") \
                                MAKE_STR(MPC_VERSION_MINOR) _T(".") \
                                MAKE_STR(MPC_VERSION_PATCH)
                                //MPC_VERSION_ADDITIONAL

#endif // MPC_NIGHTLY_RELEASE

#endif // NO_VERSION_REV_NEEDED

#endif // ISPP_INVOKED


#if MPC_NIGHTLY_RELEASE
#define MPC_VERSION_NIGHTLY     _T("Nightly")
#endif

#ifdef _WIN64
#define MPC_VERSION_ARCH        _T("x64")
#else
#define MPC_VERSION_ARCH        _T("x86")
#endif

#define MPC_DX_SDK_MONTH        _T("Octomber")
#define MPC_DX_SDK_YEAR         2016
#define MPC_DX_SDK_NUMBER       40


#endif // MPC_VERSION_H
