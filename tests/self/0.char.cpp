/************************************************************************
 *
 * 0.char.cpp - test exercising the UserTraits helper class template
 *              and the rw_widen() set of overloaded functions
 *
 * $Id$
 *
 ************************************************************************
 *
 * Copyright 2006 The Apache Software Foundation or its licensors,
 * as applicable.
 *
 * Copyright 2006 Rogue Wave Software.
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

#include <rw_char.h>
#include <driver.h>

#include <string.h>    // for memset, size_t

/***********************************************************************/

static void
test_user_traits_char ()
{
    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "template class UserTraits<char>");

    rw_warn (0, 0, 0, "UserTraits<char> not exercised");
}

/***********************************************************************/

static void
test_user_traits_wchar_t ()
{
    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "template class UserTraits<wchar_t>");

    rw_warn (0, 0, 0, "UserTraits<wchar_t> not exercised");
}

/***********************************************************************/

static void
test_user_traits_user_char ()
{
    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "template class UserTraits<UserChar>");

    const UserChar src [] = {
        { 1, 2 }, { 0, 0 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 0, 0 }
    };

    const size_t nsrc = sizeof src / sizeof *src;

    UserChar dst [nsrc];

    typedef UserTraits<UserChar>         Traits;
    typedef UserTraits<UserChar>::MemFun MemFun;

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::assign] = 0;

    Traits::assign (dst [0], src [0]);
    rw_assert (dst [0].f == src [0].f && dst [0].c == src [0].c, 0, __LINE__,
               "UserTraits::assign(char_type&, const char_type&)");

    rw_assert (1 == Traits::n_calls_ [MemFun::assign], 0, __LINE__,
               "UserTraits::assign(char_type&, const char_type&)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::eq] = 0;

    bool eq = Traits::eq (dst [0], src [0]);
    rw_assert (eq, 0, __LINE__,
               "UserTraits::eq(const char_type&, const char_type&)");

    rw_assert (1 == Traits::n_calls_ [MemFun::eq], 0, __LINE__,
               "UserTraits::eq(const char_type&, const char_type&)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::lt] = 0;

    bool lt = Traits::lt (dst [0], src [0]);
    rw_assert (!lt, 0, __LINE__,
               "UserTraits::lt(const char_type&, const char_type&)");

    rw_assert (1 == Traits::n_calls_ [MemFun::lt], 0, __LINE__,
               "UserTraits::lt(const char_type&, const char_type&)");

    lt = Traits::lt (src [0], src [1]);
    rw_assert (eq, 0, __LINE__,
               "UserTraits::lt(const char_type&, const char_type&)");

    rw_assert (2 == Traits::n_calls_ [MemFun::lt], 0, __LINE__,
               "UserTraits::lt(const char_type&, const char_type&)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::compare] = 0;

    int compare = Traits::compare (src, src, nsrc);
    rw_assert (0 == compare, 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*) "
               "== 0, got %d", compare);

    rw_assert (1 == Traits::n_calls_ [MemFun::compare], 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*)");

    compare = Traits::compare (src, src + 1, nsrc - 1);
    rw_assert (+1 == compare, 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*) "
               "== +1, got %d", compare);

    rw_assert (2 == Traits::n_calls_ [MemFun::compare], 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*)");

    compare = Traits::compare (src + 1, src, nsrc - 1);
    rw_assert (-1 == compare, 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*) "
               "== -1, got %d", compare);

    rw_assert (3 == Traits::n_calls_ [MemFun::compare], 0, __LINE__,
               "UserTraits::compare(const char_type*, const char_type*)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::length] = 0;

    size_t length = Traits::length (src);
    rw_assert (1 == length, 0, __LINE__,
               "UserTraits::length(const char_type*)");

    rw_assert (1 == Traits::n_calls_ [MemFun::length], 0, __LINE__,
               "UserTraits::length(const char_type*)");

    length = Traits::length (src + 1);
    rw_assert (0 == length, 0, __LINE__,
               "UserTraits::length(const char_type*)");

    rw_assert (2 == Traits::n_calls_ [MemFun::length], 0, __LINE__,
               "UserTraits::length(const char_type*)");

    length = Traits::length (src + 2);
    rw_assert (nsrc - 3 == length, 0, __LINE__,
               "UserTraits::length(const char_type*) == %zu, got %zu",
               nsrc - 3, length);

    rw_assert (3 == Traits::n_calls_ [MemFun::length], 0, __LINE__,
               "UserTraits::length(const char_type*)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::find] = 0;

    const UserChar *find = Traits::find (src, nsrc, src [0]);
    rw_assert (src == find, 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    rw_assert (1 == Traits::n_calls_ [MemFun::find], 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    find = Traits::find (src, nsrc, src [1]);
    rw_assert (src + 1 == find, 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    rw_assert (2 == Traits::n_calls_ [MemFun::find], 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    find = Traits::find (src, nsrc, src [2]);
    rw_assert (src + 2 == find, 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    rw_assert (3 == Traits::n_calls_ [MemFun::find], 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    find = Traits::find (src + 1, nsrc - 1, src [0]);
    rw_assert (0 == find, 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    rw_assert (4 == Traits::n_calls_ [MemFun::find], 0, __LINE__,
               "UserTraits::find(const char_type*, size_t, const char_type&)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::copy] = 0;

    const UserChar uc = { -1, 1 };

    memset (dst, 0, sizeof dst);
    dst [0] = uc;

    const UserChar *copy = Traits::copy (dst, src, 0);
    rw_assert (dst == copy, 0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    rw_assert (Traits::eq (dst [0], uc), 0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    rw_assert (1 == Traits::n_calls_ [MemFun::copy], 0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    memset (dst, 0, sizeof dst);
    dst [1] = uc;

    copy = Traits::copy (dst, src, 1);

    rw_assert (dst == copy, 0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    rw_assert (Traits::eq (dst [0], src [0]) && Traits::eq (dst [1], uc),
               0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    rw_assert (2 == Traits::n_calls_ [MemFun::copy], 0, __LINE__,
               "UserTraits::copy(char_type*, const char_type*, size_t)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::move] = 0;

    memset (dst, 0, sizeof dst);
    dst [0] = uc;

    const UserChar *move = Traits::move (dst, src, 0);
    rw_assert (dst == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (Traits::eq (dst [0], uc), 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (1 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    memset (dst, 0, sizeof dst);
    dst [1] = uc;

    move = Traits::move (dst, src, 1);

    rw_assert (dst == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (Traits::eq (dst [0], src [0]) && Traits::eq (dst [1], uc),
               0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (2 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    
    memcpy (dst, src, sizeof dst);
    move = Traits::move (dst, dst + 1, 1);

    rw_assert (dst == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (   Traits::eq (dst [0], src [1])
               && Traits::eq (dst [1], src [1]),
               0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (3 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    memcpy (dst, src, sizeof dst);
    move = Traits::move (dst, dst + 1, 2);

    rw_assert (dst == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (   Traits::eq (dst [0], src [1])
               && Traits::eq (dst [1], src [2])
               && Traits::eq (dst [2], src [2]),
               0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (4 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    memcpy (dst, src, sizeof dst);
    move = Traits::move (dst + 1, dst, 1);

    rw_assert (dst + 1 == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (   Traits::eq (dst [0], src [0])
               && Traits::eq (dst [1], src [0])
               && Traits::eq (dst [2], src [2]),
               0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (5 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    memcpy (dst, src, sizeof dst);
    move = Traits::move (dst + 1, dst, 2);

    rw_assert (dst + 1 == move, 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (   Traits::eq (dst [0], src [0])
               && Traits::eq (dst [1], src [0])
               && Traits::eq (dst [2], src [1])
               && Traits::eq (dst [3], src [3]),
               0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    rw_assert (6 == Traits::n_calls_ [MemFun::move], 0, __LINE__,
               "UserTraits::move(char_type*, const char_type*, size_t)");

    //////////////////////////////////////////////////////////////////
    Traits::n_calls_ [MemFun::assign] = 0;

    memset (dst, 0, sizeof dst);
    dst [0] = uc;

    const UserChar *assign = Traits::assign (dst, 0, src [0]);

    rw_assert (dst == assign, 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (Traits::eq (dst [0], uc), 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (1 == Traits::n_calls_ [MemFun::assign2], 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    memset (dst, 0, sizeof dst);
    dst [1] = uc;

    assign = Traits::assign (dst, 1, src [0]);
    rw_assert (dst == assign, 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (Traits::eq (dst [0], src [0]) && Traits::eq (dst [1], uc),
               0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (2 == Traits::n_calls_ [MemFun::assign2], 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    memset (dst, 0, sizeof dst);
    dst [2] = uc;

    assign = Traits::assign (dst, 2, src [0]);
    rw_assert (dst == assign, 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (   Traits::eq (dst [0], src [0])
               && Traits::eq (dst [1], src [0])
               && Traits::eq (dst [2], uc),
               0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    rw_assert (3 == Traits::n_calls_ [MemFun::assign2], 0, __LINE__,
               "UserTraits::assign(char_type*, size_t, const char_type&)");

    //////////////////////////////////////////////////////////////////
    rw_warn (0, 0, 0, "UserTraits<UserChar>::not_eof() not exercised");
    rw_warn (0, 0, 0, "UserTraits<UserChar>::eof() not exercised");
    rw_warn (0, 0, 0, "UserTraits<UserChar>::to_char_type() not exercised");
    rw_warn (0, 0, 0, "UserTraits<UserChar>::to_int_type() not exercised");
    rw_warn (0, 0, 0, "UserTraits<UserChar>::eq_int_type() not exercised");
}

/***********************************************************************/

static void
test_widen ()
{
    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "rw_widen(char*, const char*, size_t)");

    static const char   src []  = "abcdefgh";
    static const size_t nsrc = sizeof src;
    char                cdst [nsrc + 1];

    for (size_t i = 0; i != nsrc + 1; ++i) {

        memset (cdst, 0, sizeof cdst);

        const char* const ret = i < nsrc ?
            rw_widen (cdst, src, i) : rw_widen (cdst, src);

        rw_assert (cdst == ret, 0, __LINE__,
                   "rw_widen(char*, %{#s}%{?}, %zu%{;})",
                   src, i < nsrc);

        rw_assert (0 == memcmp (cdst, src, i) && '\0' == cdst [i],
                   0, __LINE__,
                   "rw_widen(char*, %{#s}%{?}, %zu%{;}) == %{#*s}, got %{#*s}",
                   src, i < nsrc, i, int (i), src, int (i + 1), cdst);
    }

#ifndef _RWSTD_NO_WCHAR_T

    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "rw_widen(wchar_t*, const char*, size_t)");

    static const wchar_t wsrc [] = L"abcdefgh";
    wchar_t              wdst [nsrc + 1];

    for (size_t i = 0; i != nsrc + 1; ++i) {

        memset (wdst, 0, sizeof wdst);

        const wchar_t* const ret = i < nsrc ?
            rw_widen (wdst, src, i) : rw_widen (wdst, src);

        rw_assert (wdst == ret, 0, __LINE__,
                   "rw_widen(wchar_t*, %{#s}%{?}, %zu%{;})",
                   src, i < nsrc, i);

        rw_assert (   0 == memcmp (wdst, wsrc, i * sizeof *wdst)
                   && '\0' == wdst [i],
                   0, __LINE__,
                   "rw_widen(wchar_t*, %{#s}%{?}, %zu%{;}) == L%{#*ls}, "
                   "got L%{#*ls}",
                   src, i < nsrc, i, int (i), wsrc, int (i + 1), wdst);
    }

#endif   // _RWSTD_NO_WCHAR_T

    //////////////////////////////////////////////////////////////////
    rw_info (0, 0, 0, "rw_widen(UserChar*, const char*, size_t)");

    static const UserChar usrc [] = {
        { 0, 'a' }, { 0, 'b' }, { 0, 'c' }, { 0, 'd' },
        { 0, 'e' }, { 0, 'f' }, { 0, 'g' }, { 0, 'h' },
        { 0, '\0' }
    };
    UserChar udst [nsrc + 1];

    for (size_t i = 0; i != nsrc + 1; ++i) {

        memset (udst, 0, sizeof udst);

        const UserChar* const ret = i < nsrc ?
            rw_widen (udst, src, i) : rw_widen (udst, src);

        rw_assert (udst == ret, 0, __LINE__,
                   "rw_widen(wchar_t*, %{#s}%{?}, %zu%{;})",
                   src, i < nsrc, i);

        rw_assert (   0 == memcmp (udst, usrc, i * sizeof *udst)
                   && 0 == udst [i].f && 0 == udst [i].c,
                   0, __LINE__,
                   "rw_widen(UserChar*, %{#s}%{?}, %zu%{;})",
                   src, i < nsrc, i);
    }
}

/***********************************************************************/

static int no_user_traits;
static int no_user_traits_char;
static int no_user_traits_wchar_t;
static int no_user_traits_user_char;
static int no_rw_widen;


static int
run_test (int, char*[])
{
    if (no_user_traits) {
        rw_note (0, 0, 0, "UserTraits tests disabled");
    }
    else {
        if (no_user_traits_char) {
            rw_note (0, 0, 0, "UserTraits<char> tests disabled");
        }
        else {
            test_user_traits_char ();
        }

        if (no_user_traits_wchar_t) {
            rw_note (0, 0, 0, "UserTraits<wchar_t> tests disabled");
        }
        else {
            test_user_traits_wchar_t ();
        }

        if (no_user_traits_user_char) {
            rw_note (0, 0, 0, "UserTraits<UserChar> tests disabled");
        }
        else {
            test_user_traits_user_char ();
        }
    }

    if (no_rw_widen) {
        rw_note (0, 0, 0, "rw_widen() tests disabled");
    }
    else {
        test_widen ();
    }

    return 0;
}

/***********************************************************************/

int main (int argc, char *argv[])
{
    return rw_test (argc, argv, __FILE__,
                    "",
                    0,
                    run_test,
                    "|-no-UserTraits# "
                    "|-no-UserTraits<char># "
                    "|-no-UserTraits<wchar_t># "
                    "|-no-UserTraits<UserChar># "
                    "|-no-rw_widen#",
                    &no_user_traits,
                    &no_user_traits_char,
                    &no_user_traits_wchar_t,
                    &no_user_traits_user_char,
                    &no_rw_widen);
}