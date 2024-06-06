/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2020  Luis Claudio Gamboa Lopes

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
#include"../include/cpaint.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"

// CPaint________________________________________________________________


CPaint::CPaint (void)
{
  SetClass ("CPaint");
  RX=0;
  RY=0;
  DoCalcRXY=true;
  Scalex=1.0;
  Scaley=1.0;
  Agc=0;
  orientation=0;
}
  
void 
CPaint::SetDoCalcRXY(bool docalcrxy)
{
  DoCalcRXY=docalcrxy;
};


CPaint::~CPaint (void)
{
};

void
CPaint::Create (CControl * control)
{
  Owner = control;
  Pen.Create (control, &Agc);
};
  
void 
CPaint::Create (CControl * control, lxBitmap *bitmap)
{
  Owner = NULL;
  Pen.Create (NULL, &Agc);
  Width = bitmap->GetWidth();
  Height = bitmap->GetHeight();	  
}

void
CPaint::Destroy (void)
{
};

void
CPaint::SetFont (CControl * control)
{

};

void
CPaint::InitDraw (CControl * control)
{
  if(DoCalcRXY)
  {	
    control->CalcRXY();
    RX=control->GetRX();
    RY=control->GetRY();
  }
  else
  {
  RX=0;
  RY=0;
  };
  SetFont(control);
};

void
CPaint::DrawControl (CControl * control)
{

};




void
CPaint::Point (int x, int y)
{
}


void
CPaint::Line (int x1, int y1, int x2, int y2)
{

}



void
CPaint::Rectangle (int x, int y, int w, int h)
{

}

void
CPaint::Frame (int x, int y, int w, int h, uint wb)
{

};

void
CPaint::LowerFrame (int x, int y, int w, int h, uint wb)
{
  XColor OldPen;
  for (uint c = 0; c < wb; c++)
    {
      OldPen = Pen.GetFgColor ();
      Pen.SetColor (ColorByName ("gray35"));
      Line ( x + c, y + c, x + c, h - 2 - c);
      Line ( x + c, y + c, w - c - 1, y + c);
      Pen.SetColor (ColorByName ("gray59"));
      Line ( x + 1 + c, y + 1 + c, x + 1 + c, h - 2 - c);
      Line ( x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
      Pen.SetColor (ColorByName ("gray96"));
      Line ( x + c, h - c - 1, w - c - 1, h - 1 - c);
      Line ( w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
      Pen.SetColor (ColorByName ("gray82"));
      Line ( x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
      Line ( w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
      Pen.SetColor (OldPen);
    };
};


void
CPaint::RaiserFrame (int x, int y, int w, int h, uint wb)
{
  XColor OldPen;
  for (uint c = 0; c < wb; c++)
    {
      OldPen = Pen.GetFgColor ();
      Pen.SetColor (ColorByName ("gray96"));
      Line ( x + c, y + c, x + c, h - 2 - c);
      Line ( x + c, y + c, w - c - 1, y + c);
      Pen.SetColor (ColorByName ("gray86"));
      Line ( x + 1 + c, y + 1 + c, x + 1 + c, h - 3 - c);
      Line ( x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
      Pen.SetColor (ColorByName ("gray35"));
      Line ( x + c, h - 1 - c, w - c - 1, h - 1 - c);
      Line ( w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
      Pen.SetColor (ColorByName ("gray59"));
      Line ( x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
      Line ( w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
      Pen.SetColor (OldPen);
    };
};

void
CPaint::Text (lxString text,  int x1, int y1)
{

}
  
void 
CPaint::TextOnRect (lxString text,lxRect rect,CAlign align)
{

}


void
CPaint::ImgText ( int x1, int y1, lxString text)
{

}
  
void 
CPaint::PutPixmap (int x,int y, int w, int h,Pixmap pixmap)
{
}
  
void 
CPaint::SetLineWidth(int w)
{
  Pen.SetWidth (w);
}

void 
CPaint::Init(void)
{
  Scalex=1.0;
  Scaley=1.0;  
  orientation=0;
}
  

void 
CPaint::Init(float sx, float sy, int _orientation)
{
  Scalex=sx;
  Scaley=sy;  
  
  orientation = _orientation;
}

void 
CPaint::End(void)
{
  if(Owner)  
    Owner->Draw();	
}

void 
CPaint::SetFgColor(unsigned char r,unsigned char g, unsigned char b)
{
   Pen.SetColor (ColorByRGB(r,g,b));
}

void 
CPaint::SetFgColor(lxString cname)
{
   Pen.SetColor (ColorByName(cname));
}


void 
CPaint::SetBgColor(unsigned char r,unsigned char g, unsigned char b)
{
   Pen.SetBgColor (ColorByRGB(r,g,b));
}

	
void 
CPaint::SetBgColor(lxString cname)
{
   Pen.SetBgColor (ColorByName(cname));
}
  
unsigned char 
CPaint::GetFgColor(void)
{
  return Pen.GetFgColor();
}

unsigned char 
CPaint::GetBgColor(void)
{
  return Pen.GetBgColor();
}

void 
CPaint::Rectangle (bool filled, int x, int y, int w, int h)
{
  if(filled)
    Rectangle ( x, y,  w, h);
  else
    Frame ( x, y, w, h,1);

}

//FIXME
void 
CPaint::RotatedText (lxString str, int x, int y, int _angle)
{

}

void 
CPaint::PutBitmap (lxBitmap* bitmap,int x,int y)
{
    
}

void 
CPaint::SetBitmap(lxBitmap * bitmap,double xs, double ys)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void 
CPaint::SetFont (lxFont font)
{
#ifdef _DEBUG	
//  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
#endif
}

void 
CPaint::SetFontSize (const int pointsize)
{
#ifdef _DEBUG	
//  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
#endif
}

void 
CPaint::SetFontWeight (const int weight)
{
#ifdef _DEBUG	
//  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
#endif
}



void 
CPaint::ChangeScale(float sx, float sy)
{
  Scalex=sx;
  Scaley=sy;	  
}

void 
CPaint::Circle (bool filled, int x, int y, int radius)
{
}
  
void 
CPaint::Arc (bool filled, int x1, int y1, int x2, int y2, int xc, int yc)
{
}

void 
CPaint::EllipticArc(bool filled, int x, int y, int width, int height, double start, double end)
{
}
  
void 
CPaint::SetColor(unsigned char r,unsigned char g, unsigned char b)
{
  Pen.SetColor (ColorByRGB(r,g,b));
  Pen.SetBgColor (ColorByRGB(r,g,b));
}

void 
CPaint::SetColor(lxColor c)
{
  Pen.SetColor (c);
  Pen.SetBgColor (c);
}

void CPaint::SetFgColor(lxColor c)
{
  Pen.SetColor (c);
}

void CPaint::SetBgColor(lxColor c)
{
  Pen.SetBgColor (c);
}

void 
CPaint::Rotate(int *x, int *y)
{
  int ox=*x;
  int oy=*y;

  switch(orientation)
  {
    case 1:
    *x= Width -oy;
    *y= ox;
    break;
    case 2:
    *x= Width -ox;
    *y= Height -oy;
    break;
    case 3:
    *x= oy;
    *y= Height - ox;
    break;
    default:
    break;
  } 

}

void 
CPaint::Polygon(bool filed, lxPoint * points, int npoints)
{
}
