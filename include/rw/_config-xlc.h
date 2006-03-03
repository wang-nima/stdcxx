/***************************************************************************
 *
 * _config-xlc.h - IBM VisualAge/XLC++ configuration definitions
 *
 * This is an internal header file used to implement the C++ Standard
 * Library. It should never be #included directly by a program.
 *
 * $Id$
 *
 ***************************************************************************
 * 
 * Copyright 2005-2006 The Apache Software Foundation or its licensors,
 * as applicable.
 *
 * Copyright 1994-2006 Rogue Wave Software.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 **************************************************************************/

// _THREAD_SAFE defined by the xlC_r compiler driver

#ifndef _RWSTD_NO_PURE_C_HEADERS
#  define _RWSTD_NO_PURE_C_HEADERS
#endif   // _RWSTD_NO_PURE_C_HEADERS

#if defined _RWSTD_NO_NEW_HEADER
#  undef _RWSTD_NO_NEW_HEADER
#endif   // _RWSTD_NO_NEW_HEADER

// our <cxxx> libc headers put the libc functions in namespace std
#ifdef _RWSTD_NO_LIBC_IN_STD
#  undef _RWSTD_NO_LIBC_IN_STD
#endif   // _RWSTD_NO_LIBC_IN_STD

#ifndef _RWSTD_NO_DEPRECATED_C_HEADERS
#  define _RWSTD_NO_DEPRECATED_C_HEADERS
#endif

// static data members of cass templates aren't properly collapsed
// (compiler emits one copy per each translation unit that contains
// the definition of the template member)
#define _RWSTD_NO_COLLAPSE_TEMPLATE_STATICS

// the above prevents correct static mutex initialization
// (but the alternative approach is also unreliable)
#define _RWSTD_NO_STATIC_MUTEX_INIT

// VisualAge for C++ version >= 5.0.2.0, when the tempinc model
// (which makes use of implicit inclusion) is in effect (i.e.,
 // when neither of -qtemplateregistry or -qnotempinc is specified
// on the command line) the compiler defines the macro __TEMPINC__
#if __IBMCPP__ < 502 || !defined (__TEMPINC__)
   // override the autodetected setting of the macro
#  undef  _RWSTD_NO_IMPLICIT_INCLUSION
#  define _RWSTD_NO_IMPLICIT_INCLUSION
#endif

#if __IBMCPP__ >=  502 && defined (__TEMPINC__)
   // override the autodetected setting of the macro
#  undef _RWSTD_NO_IMPLICIT_INCLUSION
#endif   // VAC++ >= 5.0.2 && __TEMPINC__

#if !defined (_RWSTD_WCTRANS_T)
#  undef _RWSTD_NO_WCTRANS_T
#  define _RWSTD_WCTRANS_T  win_t(*wctrans_t)(wint_t)
#endif // _RWSTD_WCTRANS_T

#ifdef _RWSTD_OS_AIX
   // operator new and delete is not reliably replaceable across
   // shared library boundaries, which includes the shared library
   // version of the language support library
#  define _RWSTD_NO_REPLACEABLE_NEW_DELETE

#  if (8 == _RWSTD_LONG_SIZE)
     // avoid using strtof() in LP64 due to bug #379 (PMR 02164)
#    ifndef _RWSTD_NO_STRTOF
#      define _RWSTD_NO_STRTOF
#    endif   // _RWSTD_NO_STRTOF
#    ifndef _RWSTD_NO_STRTOF_IN_LIBC
#      define _RWSTD_NO_STRTOF_IN_LIBC
#    endif   // _RWSTD_NO_STRTOF_IN_LIBC
#  endif   // REENTRANT && LP64
#endif   // AIX

#ifndef __TEMPINC__
   // avoid VAC++ 7.0 diagnostic 1540-2910 (I) The template uses
   // a file organization for tempinc, but tempinc is not being
   // used. See bug #450

   // prevent warnings about VAC++ being unable to find
   // source for (intentionally undefined) member functions
   // of class templates
#  define _RWSTD_NO_UNDEFINED_TEMPLATES
#endif   // __TEMPINC__


#ifdef _RWSTD_USE_CONFIG
   // avoid using autodetected libc headers
#  undef _RWSTD_ANSI_C_ASSERT_H
#  undef _RWSTD_ANSI_C_CTYPE_H
#  undef _RWSTD_ANSI_C_ERRNO_H
#  undef _RWSTD_ANSI_C_FLOAT_H
#  undef _RWSTD_ANSI_C_ISO646_H
#  undef _RWSTD_ANSI_C_LIMITS_H
#  undef _RWSTD_ANSI_C_LOCALE_H
#  undef _RWSTD_ANSI_C_MATH_H
#  undef _RWSTD_ANSI_C_SETJMP_H
#  undef _RWSTD_ANSI_C_SIGNAL_H
#  undef _RWSTD_ANSI_C_STDARG_H
#  undef _RWSTD_ANSI_C_STDDEF_H
#  undef _RWSTD_ANSI_C_STDIO_H
#  undef _RWSTD_ANSI_C_STDLIB_H
#  undef _RWSTD_ANSI_C_STRING_H
#  undef _RWSTD_ANSI_C_TIME_H
#  undef _RWSTD_ANSI_C_WCHAR_H
#  undef _RWSTD_ANSI_C_WCTYPE_H
#else
   // RCB is too dumb to autodetect these

#  ifndef _RWSTD_NO_COLLAPSE_STATIC_LOCALS
#    define _RWSTD_NO_COLLAPSE_STATIC_LOCALS
#  endif

#  ifndef _RWSTD_NO_COLLAPSE_TEMPLATE_LOCALS
#    define _RWSTD_NO_COLLAPSE_TEMPLATE_LOCALS
#  endif

#  ifndef _RWSTD_NO_EXTERN_FUNCTION_TEMPLATE
#    define _RWSTD_NO_EXTERN_FUNCTION_TEMPLATE
#  endif

#  ifndef _RWSTD_NO_EXTERN_TEMPLATE_BEFORE_DEFINITION
#    define _RWSTD_NO_EXTERN_TEMPLATE_BEFORE_DEFINITION
#  endif

#endif   // _RWSTD_USE_CONFIG