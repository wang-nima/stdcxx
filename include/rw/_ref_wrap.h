// -*- C++ -*-
/***************************************************************************
 *
 * This is an internal header file used to implement the C++ Standard
 * Library. It should never be #included directly by a program.
 *
 * $Id$
 *
 ***************************************************************************
 *
 * Licensed to the Apache Software  Foundation (ASF) under one or more
 * contributor  license agreements.  See  the NOTICE  file distributed
 * with  this  work  for  additional information  regarding  copyright
 * ownership.   The ASF  licenses this  file to  you under  the Apache
 * License, Version  2.0 (the  "License"); you may  not use  this file
 * except in  compliance with the License.   You may obtain  a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the  License is distributed on an  "AS IS" BASIS,
 * WITHOUT  WARRANTIES OR CONDITIONS  OF ANY  KIND, either  express or
 * implied.   See  the License  for  the  specific language  governing
 * permissions and limitations under the License.
 *
 * Copyright 2008 Rogue Wave Software.
 * 
 **************************************************************************/

#ifndef _RWSTD_RW_REF_WRAP_INCLUDED
#  define _RWSTD_RW_REF_WRAP_INCLUDED

#  include <rw/_defs.h>

#  if !defined _RWSTD_NO_EXT_CXX_0X


_RWSTD_NAMESPACE (__rw) {


/**
 * @class std::reference_wrapper
 *
 * Encapsulates a reference as an object.  This class template allows
 * references to be manipulated and behave as an ordinary object.
 *
 * @tparam Type A non-reference type.
 */

template <class _Type>
class __rw_ref_wrap
{

};


}   // namespace __rw


#  endif   // !defined _RWSTD_NO_EXT_CXX_0X

#endif   // _RWSTD_RW_REF_WRAP_INCLUDED
