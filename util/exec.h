/************************************************************************
 *
 * exec.h - Interface declaration for the child process subsystem
 *
 * $Id$
 *
 ************************************************************************
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
 **************************************************************************/

#ifndef RW_EXEC_H
#define RW_EXEC_H

struct exec_attrs {
#if !defined (_WIN32) && !defined (_WIN64)
    int status;
    int killed;
#else
    /* AKA DWORD */
    unsigned long status;
    unsigned long error;
#endif  /* _WIN{32,64} */
};

int get_signo (const char* signame);

const char* get_signame (int signo);

struct exec_attrs exec_file (struct target_status* result);

#endif   // RW_EXEC_H