#ifndef _KTERM_API_H_
#define _KTERM_API_H_


#ifdef KTERM_STATIC_DEFINE /* Define if compiling as a static library (-DKTERM_STATIC_DEFINE) */
#	define KTERM_API
#	define KTERM_NO_EXPORT
#else
#	ifndef KTERM_API
#		ifdef KTERM_EXPORTS /* We are building this library */
#			if defined _WIN32 || defined _WIN64 || defined __CYGWIN__ || defined __MINGW64__
#				if defined __GNUC__ || defined __clang__
#					define KTERM_API __attribute__ ((dllexport))
#				else
#					define KTERM_API __declspec(dllexport)
#				endif
#			else 
#				if (defined __GNUC__ && __GNUC__ >= 4) || defined __clang__
#					define KTERM_API __attribute__ ((visibility ("default")))
#				endif
#			endif
#    	else /* We are using this library */
#			if defined _WIN32 || defined _WIN64 || defined __CYGWIN__ || defined __MINGW64__
#				if defined __GNUC__ || defined __clang__
#					define KTERM_API __attribute__ ((dllimport))
#				else
#					define KTERM_API __declspec(dllimport)
#				endif
#			else 
#				if defined __GNUC__ && __GNUC__ >= 4
#					define KTERM_API
#				endif
#			endif
#       endif
#	else /* Should Only reach here for non-*nix, un-supported platforms */
#       warning "Platform Unsupported - Either Not a derivative of Unix // Not Windows"
#		define KTERM_API
#   endif
#	ifndef KTERM_NO_EXPORT
#       if defined __GNUC__ && __GNUC__ >= 4 /* Symbols exported by default on *nix systems */
#           define KTERM_NO_EXPORT __attribute__((visibility ("hidden")))
#       else /* (DLL) Symbols on platforms like windows must be exported manually [__declspec(dllexport)] */
#		    define KTERM_NO_EXPORT 
#       endif
#	endif
#endif


#ifndef KTERM_DEPRECATED
#   if defined(__cplusplus)
#       if __cplusplus >= 201402L /* [[deprecated]] Supported since C++14 */
#           define KTERM_DEPRECATED [[deprecated]]
#           define KTERM_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]
#       endif
#   else
#       if defined _WIN32 || defined _WIN64
#           if defined __GNUC__ || defined __clang__ /* Cygwin, MinGW32/64 */
#               define KTERM_DEPRECATED          __attribute__((deprecated))
#               define KTERM_DEPRECATED_MSG(MSG) __attribute__((deprecated(MSG)))
#           else
#               define KTERM_DEPRECATED          __declspec(deprecated)
#               define KTERM_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
#           endif
#       elif defined __GNUC__ || defined __clang__
#           define KTERM_DEPRECATED __attribute__((deprecated))
#           define KTERM_DEPRECATED_MSG(MSG) __attribute__((deprecated(MSG)))
#       else /* Should Only reach here for non-*nix, un-supported platforms */
#           define KTERM_DEPRECATED
#           define KTERM_DEPRECATED_MSG(MSG)
#       endif
#   endif
#endif


#ifndef KTERM_DEPRECATED_EXPORT
#  define KTERM_DEPRECATED_EXPORT KTERM_API KTERM_DEPRECATED
#endif


#ifndef KTERM_DEPRECATED_NO_EXPORT
#  define KTERM_DEPRECATED_NO_EXPORT KTERM_NO_EXPORT KTERM_DEPRECATED
#endif


/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KTERM_NO_DEPRECATED
#    define KTERM_NO_DEPRECATED
#  endif
#endif

#endif /* _KTERM_API_H_ */