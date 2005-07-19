/**************************************************************************
 *
 * rotate.cpp - Example program of rotate algorithm. 
 *
 * $Id: //stdlib/dev/examples/stdlib/manual/rotate.cpp#11 $
 *
 ***************************************************************************
 *
 * Copyright (c) 1994-2005 Quovadx,  Inc., acting through its  Rogue Wave
 * Software division. Licensed under the Apache License, Version 2.0 (the
 * "License");  you may  not use this file except  in compliance with the
 * License.    You    may   obtain   a   copy   of    the   License    at
 * http://www.apache.org/licenses/LICENSE-2.0.    Unless   required    by
 * applicable law  or agreed to  in writing,  software  distributed under
 * the License is distributed on an "AS IS" BASIS,  WITHOUT WARRANTIES OR
 * CONDITIONS OF  ANY KIND, either  express or implied.  See  the License
 * for the specific language governing permissions  and limitations under
 * the License.
 * 
 **************************************************************************/

#include <algorithm>   // for rotate
#include <iostream>    // for cout, endl
#include <iterator>    // for ostream_iterator
#include <vector>      // for vector

#include <examples.h>


int main ()
{
    typedef std::vector<int, std::allocator<int> > Vector;

    // Initialize a vector with an array of integers.
    const Vector::value_type arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector v (arr + 0, arr + sizeof arr / sizeof *arr);

    typedef std::ostream_iterator<int, char, std::char_traits<char> > Iter;

    // Print out elements in original (sorted) order.
    std::cout << "Elements before rotate: \n     ";
    std::copy (v.begin (), v.end (), Iter (std::cout, " "));

    // Rotate the elements.
    std::rotate (v.begin (), v.begin () + 4, v.end ());

    // Print out the rotated elements.
    std::cout << "\n\nElements after rotate: \n     ";
    std::copy (v.begin (), v.end (), Iter (std::cout, " "));
    std::cout << std::endl;

    return 0;
}
