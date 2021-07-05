/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    current.cxx
 * Author:       Hao-Kai SUN
 * Created:      2020-06-28 Sun 14:28:54 CST
 * <<=====================================>>
 * Last Updated: 2020-06-28 Sun 14:29:51 CST
 *           By: Hao-Kai SUN
 *     Update #: 2
 * <<======== COPYRIGHT && LICENSE =======>>
 *
 * Copyright © 2020 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ============================== CODES ==============================>>> */
#include "StoeeLAlg/util/current.h"

std::string currentDT()
{
    char buf[100];
    time_t now        = time(0);
    struct tm tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

/* ===================================================================<<< */
/* ======================= current.cxx ends here ======================== */
