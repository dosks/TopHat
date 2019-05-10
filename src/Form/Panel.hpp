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

#ifndef XCSOAR_FORM_PANEL_HPP
#define XCSOAR_FORM_PANEL_HPP

#include "Screen/Features.hpp"

#ifdef HAVE_CLIPPING
#include "Screen/SolidContainerWindow.hpp"
#else
#include "Screen/ContainerWindow.hpp"
#endif

struct DialogLook;

/**
 * The PanelControl class implements the simplest form of a ContainerControl
 */
class PanelControl :
#ifdef HAVE_CLIPPING
  public SolidContainerWindow
#else
  /* don't need to erase the background when it has been done by the
     parent window already */
  public ContainerWindow
#endif
{
public:
  PanelControl() = default;

  /**
   * Constructor of the PanelControl class
   * @param owner Parent ContainerControl
   */
  PanelControl(ContainerWindow &parent, const DialogLook &look,
               const PixelRect &rc,
               const WindowStyle style=WindowStyle()) {
    Create(parent, look, rc, style);
  }

  void Create(ContainerWindow &parent, const DialogLook &look,
              const PixelRect &rc,
              const WindowStyle style=WindowStyle());
};

#endif
