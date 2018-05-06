#ifndef MPC_HC_CONFIG_H
#define MPC_HC_CONFIG_H

#ifndef _T
#if !defined(ISPP_INVOKED) && (defined(UNICODE) || defined(_UNICODE))
#define _T(text) L##text
#else
#define _T(text) text
#endif
#endif

#define USE_STATIC_UNRAR 1

#ifndef MPCHC_LITE
#define USE_STATIC_MEDIAINFO 1
#endif

#define SHADERS_DIR _T("PlayerShaders")
#define SHADERS_EXT _T(".hlsl")

// If this is enabled, the registered LAV Filters can be loaded as internal filters
#define ENABLE_LOAD_EXTERNAL_LAVF_AS_INTERNAL 0

#endif // MPC_HC_CONFIG_H
