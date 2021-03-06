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

#include "ConditionMonitorWind.hpp"
#include "NMEA/Derived.hpp"
#include "Language/Language.hpp"
#include "Message.hpp"
#include "Input/InputQueue.hpp"

bool
ConditionMonitorWind::CheckCondition(const NMEAInfo &basic,
                                     const DerivedInfo &calculated,
                                     const ComputerSettings &settings)
{
  wind = calculated.GetWindOrZero();

  if (!calculated.flight.flying) {
    last_wind = wind;
    return false;
  }

  fixed mag_change = fabs(wind.norm - last_wind.norm);
  fixed dir_change = (wind.bearing - last_wind.bearing).AsDelta().AbsoluteDegrees();

  if (mag_change > fixed(2.5))
    return true;

  return wind.norm > fixed(5) &&
         dir_change > fixed(45);
}

void
ConditionMonitorWind::Notify()
{
  InputEvents::processGlideComputer(GCE_WIND_CHANGE);
  Message::AddMessage(_("Significant wind change"));
}

void
ConditionMonitorWind::SaveLast()
{
  last_wind = wind;
}
