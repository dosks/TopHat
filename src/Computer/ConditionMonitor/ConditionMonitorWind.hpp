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

#ifndef XCSOAR_CONDITION_MONITOR_WIND_HPP
#define XCSOAR_CONDITION_MONITOR_WIND_HPP

#include "ConditionMonitor.hpp"
#include "Geo/SpeedVector.hpp"

/** #ConditionMonitor to track/warn on significant changes in wind speed */
class ConditionMonitorWind final : public ConditionMonitor {
  SpeedVector wind;
  SpeedVector last_wind;

public:
  constexpr ConditionMonitorWind()
    :ConditionMonitor(60 * 5, 10),
     wind(SpeedVector::Zero()), last_wind(SpeedVector::Zero()) {}

protected:
  bool CheckCondition(const NMEAInfo &basic,
                      const DerivedInfo &calculated,
                      const ComputerSettings &settings) override;
  void Notify() override;
  void SaveLast() override;
};

#endif