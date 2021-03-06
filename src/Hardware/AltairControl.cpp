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

#include "Hardware/AltairControl.hpp"

#include <tchar.h>

static constexpr DWORD IOCTL_TRA_BACKLIGHTSETVALUE = 5000;
static constexpr DWORD IOCTL_TRA_BACKLIGHTGETVALUE = 5001;
static constexpr DWORD IOCTL_TRA_GETINFO = 5030;
static constexpr DWORD IOCTL_TRA_SHORTBEEP = 5060;

AltairControl::AltairControl()
 :handle(::CreateFile(_T("TRA1:"), GENERIC_READ|GENERIC_WRITE, 0,
                      nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr))
{
}

AltairControl::~AltairControl()
{
  if (handle != INVALID_HANDLE_VALUE)
    ::CloseHandle(handle);
}

bool
AltairControl::ShortBeep()
{
  if (handle == INVALID_HANDLE_VALUE)
    return false;

  return ::DeviceIoControl(handle, IOCTL_TRA_SHORTBEEP,
                           nullptr, 0, nullptr, 0, nullptr, nullptr);
}

bool
AltairControl::GetBacklight(int &value_r)
{
  if (handle == INVALID_HANDLE_VALUE)
    return false;

  return ::DeviceIoControl(handle, IOCTL_TRA_BACKLIGHTGETVALUE,
                           &value_r, sizeof(value_r),
                           nullptr, 0, nullptr, nullptr);
}

bool
AltairControl::SetBacklight(int value)
{
  if (handle == INVALID_HANDLE_VALUE)
    return false;

  return ::DeviceIoControl(handle, IOCTL_TRA_BACKLIGHTSETVALUE,
                           &value, sizeof(value), nullptr, 0, nullptr, nullptr);
}
