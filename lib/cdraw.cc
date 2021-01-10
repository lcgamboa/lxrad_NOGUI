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

#include"../config.h"
#include"../include/cdraw.h"
#include"../include/cmessage.h"
#include"../include/capplication.h"

#include"xevents.cc"



// CDraw_____________________________________________________________

CDraw::CDraw (void)
{
  FileName = "";
  Data = NULL;
  SetX (10);
  SetY (10);
  SetWidth (100);
  SetHeight (100);
  SetClass ("CDraw");
  SetTransparent (false);
  CMask = 0;
  CPixmap = 0;
};

CDraw::~CDraw (void)
{
};

int
CDraw::Create (CControl * control)
{
  if (!ColorSet)
    SetColor ("white");
  int ret =CControl::Create (control);
  Canvas.Create(this);
  Canvas.SetDoCalcRXY(false);
  Visible=false;	    
  SetPixmapFileName (FileName);
  SetPixmapData (Data);
  Visible=true;	    
  if(!CPixmap)
  {
    //CPixmap =XCreatePixmap (Win->GetADisplay (), Win->GetWWindow (), Width, Height, *(Win->GetADepth()));
    //Canvas.SetDrawIn(CPixmap);
    Canvas.Pen.SetColor (Color);
    Canvas.Rectangle ( 0, 0, Width, Height);
  };
 
  return ret;
}

void
CDraw::Destroy (void)
{
  Canvas.Destroy();
  CControl::Destroy ();
};

void 
CDraw::SetWidth (uint width)
{
  CControl::SetWidth(width);
}

void 
CDraw::SetHeight (uint height)
{
  CControl::SetHeight(height);
}
      
void
CDraw::Draw ()
{

}

lxString
CDraw::GetPixmapFileName (void)
{
  return FileName;
}


bool
CDraw::SetPixmapFileName (lxString filename)
{
  FileName = filename;
  return true;
}


bool
CDraw::SetPixmapData (char **data)
{
  Data = data;
  return true;
}

void
CDraw::WritePixmapToFile (lxString filename)
{

}


bool 
CDraw::SetImgFileName(lxString iname)
{
  return SetPixmapFileName (iname);
}
  
bool 
CDraw::SetImgFileName(lxString filename, float sx, float sy)
{
  FileName = filename;
 
  return true;
}

void 
CDraw::WriteImgToFile (lxString filename)
{
}

lxStringList CDraw::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("PixmapFileName=" + GetPixmapFileName () + ";File");
  return Context;
}

void
CDraw::SetContext (lxStringList context)
{
  Erase ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      lxString line = Context.GetLine (i);
      lxString arg;
      eqparse (line, arg);
      if (line.compare ("PixmapFileName") == 0)
      {
	if(arg.size() >  0)
	  SetPixmapFileName (arg);
	else
	  SetPixmapFileName ("");
      };
    };
  Draw ();
}

void 
CDraw::SetTransparent (bool)
{
}
  
