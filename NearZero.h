/* NearZero 29/10/2015

 $$$$$$$$$$$$$$$$$$
 $   NearZero.h   $
 $$$$$$$$$$$$$$$$$$

 by W.B. Yates

 Copyright (C) 2015  W.B. Yates
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/
 
 
 History:

*/


#ifndef __NEARZERO_H__
#define __NEARZERO_H__



const double NEAR_ZERO =  1E-10;

inline bool nearZero(double p, double threshold = NEAR_ZERO) { return ((p > -threshold) && (p < threshold)); }


#endif


