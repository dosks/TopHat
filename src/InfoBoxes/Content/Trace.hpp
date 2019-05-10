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

#ifndef XCSOAR_INFOBOX_CONTENT_TRACE_HPP
#define XCSOAR_INFOBOX_CONTENT_TRACE_HPP

#include "InfoBoxes/Content/Base.hpp"
#include "InfoBoxes/Content/Altitude.hpp"

class TraceVariableHistory;

class InfoBoxContentSpark: public InfoBoxContent
{
protected:
  void Paint(Canvas &canvas, const PixelRect &rc,
                const TraceVariableHistory& var,
                const bool center = true);
  void SetVSpeedComment(InfoBoxData &data,
                    const TraceVariableHistory& var);

};

class InfoBoxContentVarioSpark : public InfoBoxContentSpark
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
};

class InfoBoxContentNettoVarioSpark : public InfoBoxContentSpark
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
};

class InfoBoxContentCirclingAverageSpark : public InfoBoxContentSpark
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
};

class InfoBoxContentBarogram : public InfoBoxContent
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
  virtual const InfoBoxPanel *GetDialogContent() override;
};

class InfoBoxContentThermalBand : public InfoBoxContent
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
};

class InfoBoxContentTaskProgress : public InfoBoxContent
{
public:
  virtual void Update(InfoBoxData &data) override;
  virtual void OnCustomPaint(Canvas &canvas, const PixelRect &rc) override;
};

#endif