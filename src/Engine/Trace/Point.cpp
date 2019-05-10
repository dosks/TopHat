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

#include "Point.hpp"
#include "NMEA/MoreData.hpp"
#include "Navigation/Aircraft.hpp"

TracePoint::TracePoint(const MoreData &basic)
  :SearchPoint(basic.location),
   time((unsigned)basic.time),
   altitude(basic.nav_altitude),
   vario(basic.netto_vario),
   engine_noise_level(basic.engine_noise_level_available
                      ? basic.engine_noise_level
                      : 0u),
   drift_factor(sigmoid(basic.nav_altitude / 100) * 256)
{
}

TracePoint::TracePoint(const AircraftState &state):
  SearchPoint(state.location),
  time((unsigned)state.time),
  altitude(state.altitude),
  vario(state.netto_vario),
  engine_noise_level(0),
  drift_factor(sigmoid(state.altitude_agl / 100) * 256)
{
}