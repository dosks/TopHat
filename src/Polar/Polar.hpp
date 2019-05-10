/*
Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_POLAR_INFO_HPP
#define XCSOAR_POLAR_INFO_HPP

#include "Shape.hpp"
#include "Math/fixed.hpp"

struct PolarCoefficients;

/**
 * Struct for internally stored WinPilot-like polars
 */
struct PolarInfo
{
  // Using doubles here to simplify the code in PolarStore.cpp
  //
  fixed reference_mass; /**< Reference Mass (kg) */
  fixed max_ballast;  /**< Max water ballast (l) */

  PolarShape shape;

  fixed wing_area;    /**< Reference wing area (m^2) */
  fixed v_no;         /**< Maximum speed for normal operations (m/s) */

  gcc_pure
  PolarCoefficients CalculateCoefficients() const;

  bool IsValid() const {
    return shape.IsValid();
  }
};

#endif
