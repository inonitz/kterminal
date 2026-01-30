#ifndef __KTERM_API_EXTERN_C_DEFINITION_MACRO
#define __KTERM_API_EXTERN_C_DEFINITION_MACRO
#ifdef __cplusplus
#   define KTERM_EXTERNC extern "C"
#   define KTERM_EXTERNC_DECL_BEGIN KTERM_EXTERNC {
#   define KTERM_EXTERNC_DECL_END   }
#else
#   define KTERM_EXTERNC
#   define KTERM_EXTERNC_DECL_BEGIN
#   define KTERM_EXTERNC_DECL_END
#endif
#endif