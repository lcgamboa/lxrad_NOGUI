/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gamb�a Lopes

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


#include"../include/cdialog.h"
#include"../include/capplication.h"


// CDialog__________________________________________________________


CDialog::CDialog (void)
{
  Return = false;
  SetClass ("CDialog");
  SetX (320);
  SetY (240);
  SetWidth (285);
  SetHeight (115);
  SetName ("Dialog");
  //button1
  button1.SetText ("OK");
  button1.SetX (80);
  button1.SetY (75);
  button1.SetTag (1);
  button1.SetFOwner (this);
  button1.EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CDialog::ButtonRelease1;
  CreateChild (&button1);
  //button1
  button2.SetText ("Cancel");
  button2.SetX (150);
  button2.SetY (75);
  button2.SetTag (0);
  button2.SetFOwner (this);
  button2.EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CDialog::ButtonRelease1;
  CreateChild (&button2);
  //string1
  string1.SetText ("");
  string1.SetX (0);
  string1.SetY (0);
  string1.SetWidth (285);
  string1.SetHeight (75);
  CreateChild (&string1);
};

void
CDialog::ButtonRelease1 (CControl * control, uint button, uint x, uint y,
			 uint state)
{
  Return = control->GetTag ();
  HideExclusive ();
};

bool
Dialog (lxString label)
{
  bool ret;
  CDialog *winput;
  winput = new CDialog;
  winput->string1.SetText (label);
  winput->WCreate ();
  winput->Draw ();
  winput->ShowExclusive ();
  winput->SetCanDestroy (true);
  ret = winput->Return;
  winput->WDestroy ();
  delete winput;
  return ret;
}


bool
Dialog_sz (lxString label, int Width, int Height)
{
  bool ret;
  CDialog *winput;
  winput = new CDialog;

  int width=10, height=10;  
	  
  winput->SetWidth (Width);
  winput->SetHeight (Height);
  winput->button1.SetX ((Width- 3*winput->button1.GetWidth())/2);
  winput->button1.SetY (Height-65);
  winput->button2.SetX (((Width- 3*winput->button1.GetWidth())/2)+(2*winput->button1.GetWidth()));
  winput->button2.SetY (Height-65);
  winput->string1.SetWidth (Width-5);
  winput->string1.SetHeight (Height-90);

  //wxDisplaySize (&width,&height);  
  
  winput->SetX ((width  - winput->GetWidth  ())/2);
  winput->SetY ((height - winput->GetHeight ())/2);

  winput->string1.SetText (label);
  winput->WCreate ();
  winput->Return=0;
  winput->SetCanDestroy (false);
  winput->Draw ();
  winput->ShowExclusive ();
  winput->SetCanDestroy (true);
  ret = winput->Return;
  winput->WDestroy ();
  return ret;
}

