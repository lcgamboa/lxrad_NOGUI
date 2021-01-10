/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2018  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

/**
 * \file cstatusbar.h
 * \author Luis Claudio Gamboa Lopes
 * \date 06-25-2010
 */

#ifndef CSTATUSBAR
#define CSTATUSBAR

#include"ccontrol.h"
#include"cwindow.h"

/** \brief Statusbar Control.
 *
 * Generic Statusbar Control Class.
 */

class CStatusbar:public CControl
{
protected:
  lxStringList Fields;
public:
  CStatusbar (void);
  void SetX(int x);
  void SetY(int y);
  void Draw (void);
  void Update (void);
   ~CStatusbar (void);
  int Create (CControl * control);
  lxStringList GetContext (void);
  void SetContext (lxStringList context);
  //propiedades
  void SetFields (lxString litens);
  lxString GetFields (void);
  lxString GetField (int item);
  void SetField (int item, lxString sitem);
  int GetFieldsCount (void);
  void AddField (lxString text);
};

#endif
