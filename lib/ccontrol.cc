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

#include"../include/ccontrol.h"
#include"../include/cwindow.h"
#include"../include/cmenu.h"
#include"../include/cpmenu.h"
#include"../include/capplication.h"

extern CApplication *Application;

#include<stdio.h>

// CControl______________________________________________________________

CControl::CControl (void)
{
  //Dynamic = false;
  Owner = NULL;
  Win = NULL;
  Paint = NULL;
  ChildCount = -1;
  Child = NULL;
  SetX(0);
  SetY(0);
  Border = 1;
  Width = 10;
  Height = 10;
  Visible = true;
  GChanges=true;
  Tag = 0;
  //OnFocus=false;
  CanExecuteEvent = 1;
  CanExecuteEventOld = 1;
  CanFocus = 1;
  Enable = 1;
  Pen = 0;
  FOwner = NULL;
  PointerOn = false;
  FontName = "-misc-fixed-medium-r-normal--13-100-100-100-c-70-iso8859-1";
  SetClass ("CControl");
  PopupMenu = NULL;
  CanVisible = true;
  DragAcceptFiles = false;
  SetHint(""); 
  
  EvMouseMove = NULL;
  EvMouseButtonPress = NULL;
  EvMouseButtonRelease = NULL;
  EvMouseButtonClick = NULL;
  EvMouseButtonDoubleClick = NULL;
  EvKeyboardPress = NULL;
  EvKeyboardRelease = NULL;
  EvKeyboardKey = NULL;
  PointerIn = NULL;
  PointerOut = NULL;
  EvOnDraw = NULL;
  EvOnFocusIn = NULL;
  EvOnFocusOut = NULL;
  EvOnDropFile = NULL;

  CFont = NULL;
  ColorName = "";
  ColorSet = false;
}

CControl::~CControl ()
{
//  eprint("~"+GetClass()+"\n");
  if (Child)
    {
      for (int c = 0; c <= ChildCount; c++)
	{
	  if (Child[c]->GetDynamic ())
	    delete Child[c];
	  Child[c] = NULL;
	}
      ChildCount = -1;
      delete[]Child;
      Child = NULL;
    }
}


int
CControl::Create (CControl * control)
{
#ifdef _DEBUG	
//  printf("Created :(%s)\t%s - %s\n",control->GetName().c_str(),Class.c_str(),Name.c_str());	
#endif
  SetOwner (control);
  Win = control->Win;
  Paint = control->Paint;

  if (ColorSet)
    {
      if (ColorName.size () > 0)
	Color = ColorByName (ColorName);
      else
	Color = 0;
    }
  else
    Color = ColorByName ("light gray");

  if (ChildCount > -1)
    {
    for (int i = 0; i <= ChildCount; i++)
      {
	Child[i]->Create (this);
      }
    } 
    DisableColor = ColorByName ("dark gray");


    if(!Enable)
    {
      Enable=true;
      SetEnable(false);
    }

    if(CanExecuteEvent && DragAcceptFiles)
    {
      SetDragAcceptFiles(DragAcceptFiles);
    }


    return 1;
}


void
CControl::Destroy (void)
{
#ifdef _DEBUG 
//  if(Owner)
//    printf("Destroy :(%s)\t%s - %s\n",Owner->GetName().c_str(),Class.c_str(),Name.c_str());	
#endif
  DestroyChilds ();
  Erase ();
  if (Win != NULL)
    {
      if (CFont)
	{
	  CFont = NULL;
	}
      if (Win->GetLastControl () == this)
	Win->SetLastControl (NULL);
    }
}

CWindow *
CControl::GetWin (void)
{
  return Win;
}

void
CControl::SetWin (CWindow * win)
{
  Win = win;
}

void
CControl::Draw (void)
{
  if ((!Visible) || (Paint == NULL)) return;
  on_draw ();
  if (ChildCount != -1)
    {
    for (int i = 0; i <= ChildCount; i++)
      {
	Child[i]->Draw ();
      }
    }
    Update ();
}

void
CControl::Update (void)
{
  if ((!Visible) || (Paint == NULL) || (Win->GetWWindow () == 0))
    return;

  if ((Win == Owner) && (Win != this))
    {
      if (Win->GetControlOnFocus () == this)
	{
	   Paint->InitDraw (this);
	   Paint->Pen.SetColor (ColorByName ("black"));
	   Paint->Frame (  - 1,  - 1, Width + 1, Height + 1);
	}
      else
	{
	   Paint->InitDraw (this);
	   Paint->Pen.SetColor (Win->GetColor ());
	   Paint->Frame ( - 1, - 1, Width + 1, Height + 1);
	}
    }
  
    Paint->DrawControl (this);

}

void
CControl::Erase (void)
{
  if ((Paint == NULL) || (!Visible)) return;

  if ((this != Win)&&(Owner == Win))
    {
	Paint->InitDraw (this);
        Paint->Pen.SetColor (Owner->GetColor ());
	Paint->Rectangle (0,0, Width, Height);
        if (Win->GetControlOnFocus () == this)
	{
	  Paint->Pen.SetColor (Win->GetColor ());
	  Paint->Frame (- 1, - 1, Width + 1, Height + 1);
	}
        Paint->DrawControl (this);
    }

}


void
CControl::Event (vEvent event)
{
  CControl *control = 0;


  if (Win == NULL)
    return;
  
  //mouse position
  if ((event.type == MotionNotify) && (Win != NULL))
  {
      if(Owner==this)
      {
      Win->SetXMouse (event.motion.x);
      Win->SetYMouse (event.motion.y);
      control=NULL;
      for (int j = 0; j <= ChildCount; j++)
      {
        if (Child[j]->OwnerEvent (Win->GetXMouse (), Win->GetYMouse ())
	  && (Child[j]->GetVisible ()))
	 control = Child[j];
       }

      if(control)
         Application->SetHintControl(control,event.motion.x,event.motion.y);
      else
         Application->SetHintControl(NULL,0,0);
      }
  }
  
   if ((event.type == ButtonPress) && (Win != NULL))
    {
      Win->SetXMouse (event.button.x);
      Win->SetYMouse (event.button.y);
    }
  //verify Owner of event  
  for (int j = 0; j <= ChildCount; j++)
    {
      if (Child[j]->OwnerEvent (Win->GetXMouse (), Win->GetYMouse ())
	  && (Child[j]->GetVisible ()))
	control = Child[j];
    }

  if (control == NULL)
    {
      control = this;
    }
  else
    {
      if (control->GetCanExecuteEvent ())
	{
	  control->Event (event);
	  return;
	}
      else
	{
	  control = control->GetOwner ();
	}
    }
  //verify control focus 
  if (control != Win->GetLastControl ())
    {
      control->pointer_in ();
      if (Win->GetLastControl () != NULL)
	Win->GetLastControl ()->pointer_out ();
    }
  Win->SetLastControl (control);
  if (control->Win != NULL)
    {
      if ((event.type == ButtonPress)
	  && (control != control->Win->GetControlOnFocus ())
	  && (event.button.button == 1))
	{
	  control->SetFocus (true);
	}
    }


  if (control == NULL)
    return;
//activate event in control
  switch (event.type)
    {
//  case ClientMessage:         
//  return 1;break;
//  case DestroyNotify:           
//  return 1;break;
//  case CirculateNotify:         
//  return 1;break;
//  case ConfigureNotify:         
//  return 1;break;
//  case GravityNotify:         
//  return 1;break;
//  case MapNotify:             
//  return 1;break;
//  case ReparentNotify:                
//  return 1;break;
//  case UnmapNotify:           
//  return 1;break;
    case MotionNotify:
      control->mouse_move (event);
      return;
      break;
    case KeyPress:
      if (event.key.key == 12) //tab
	{
//look status        
	  Win->CirculateFocus (true);
	  return;
	}

      if (Win->GetControlOnFocus ())
	Win->GetControlOnFocus ()->key_press (event);
      else
	control->key_press (event);
      return;
      break;
    case KeyRelease:
      if (Win->GetControlOnFocus ())
	Win->GetControlOnFocus ()->key_release (event);
      else
	control->key_release (event);
      return;
      break;
    case ButtonPress:
      control->button_press (event);
      return;
      break;
    case ButtonRelease:
      control->button_release (event);
      return;
      break;
//  case EnterNotify:           
//  return 1;break;
//  case LeaveNotify:           
//  return 1;break;
//  case ColormapNotify:                
//  return 1;break;
//  case GraphicsExpose:                
//  return 1;break;
//  case NoExpose:              
//  return 1;break;
//  case FocusIn:                       
//  return 1;break;
//  case FocusOut:              
//  return 1;break;
//  case KeymapNotify:          
//  return 1;break;
//  case PropertyNotify:                
//  return 1;break;
//  case ResizeRequest:         
//  return 1;break;
//  case MappingNotify:         
//  return 1;break;
//  case SelectionClear:                
//  return 1;break;
//  case SelectionNotify:               
//  return 1;break;
//  case SelectionRequest:      
//  return 1;break;
//  case VisibilityNotify:      
//  return 1;break;
//  case LASTEvent:             
//  return 1;break;
//  case Expose:  
//  return 1;break;
/*
        case lxEVT_DROP_FILES:
          on_drop_files ((wxDropFilesEvent*) & event);
          break;
*/
    default:
      //printf("default !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      return;
    }

}

void
CControl::DestroyChilds (void)
{
  for (int c = 0; c <= ChildCount; c++)
    {
      Child[c]->SetVisible (false);
      Child[c]->Destroy ();
      if (Child[c]->GetDynamic ())
	delete Child[c];
      Child[c] = NULL;
    }
  ChildCount = -1;
  delete[]Child;
  Child = NULL;
  if (Win)
    if (Win->GetLastControl () == this)
      Win->SetLastControl (NULL);
}

void
CControl::CreateChild (CControl * control)
{
  ChildCount++;
  CControl **Child1;
  Child1 = new CControl *[ChildCount + 1];
  for (int c = 0; c < ChildCount; c++)
    Child1[c] = Child[c];
  Child1[ChildCount] = control;
  if (Child)
    delete[]Child;
  Child = Child1;

  if (Win != NULL)
    control->Create (this);
}

void
CControl::DestroyChild (CControl * control)
{
  int childn = -1;
  if (Win)
    if (Win->GetLastControl () == control)
      Win->SetLastControl (NULL);
  for (int f = 0; f <= ChildCount; f++)
    if (Child[f] == control)
      {
	childn = f;
	break;
      }
  if (childn != -1)
    {
      Child[childn]->Erase ();
      Child[childn]->Destroy ();
      if (Child[childn]->GetDynamic ())
	delete Child[childn];
      for (int c = childn; c < ChildCount; c++)
	Child[c] = Child[c + 1];

      Child[ChildCount] = NULL;
      ChildCount--;
    }
}

bool
CControl::OwnerEvent (int x, int y)
{
  CalcRXY();

  if ((x > RX) && (x < (int) (Width + RX)))
    {
      if ((y > RY) && (y < (int) (Height + RY)))
	return true;
      else
	return false;
    }
  else
    return false;
}

lxStringList CControl::GetContext (void)
{
  CObject::GetContext ();

 //propierties
  Context.AddLine (xml_out (lxT("X"), lxT("int"), itoa (GetX ())));
  Context.AddLine (xml_out (lxT("Y"), lxT("int"), itoa (GetY ())));
  Context.AddLine (xml_out (lxT("Width"), lxT("uint"), itoa (GetWidth ())));
  Context.AddLine (xml_out (lxT("Height"), lxT("uint"), itoa (GetHeight ())));
  Context.AddLine (xml_out (lxT("Hint"), lxT("String"), GetHint ()));
  Context.AddLine (xml_out (lxT("Enable"), lxT("bool"), itoa (GetEnable ())));
  Context.AddLine (xml_out (lxT("Visible"), lxT("bool"), itoa (GetVisible ())));
  Context.AddLine (xml_out (lxT("Color"), lxT("String"), GetColor ().GetAsString (lxC2S_HTML_SYNTAX) ));

  if (PopupMenu)
    Context.AddLine (xml_out (lxT("PopupMenu"), lxT("PopupMenu"), PopupMenu->GetName ()));
  else
    Context.AddLine (xml_out (lxT("PopupMenu"), lxT("PopupMenu"), lxT("NULL")));

//events  
  Context.AddLine (xml_out (lxT("EvMouseMove"), lxT("Event"), btoa (GetEv (true))));
  Context.AddLine (xml_out (lxT("EvMouseButtonPress"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvMouseButtonRelease"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvMouseButtonClick"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvMouseButtonDoubleClick"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvKeyboardPress"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvKeyboardRelease"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvKeyboardKey"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvOnDraw"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvOnFocusIn"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvOnFocusOut"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT("EvMouseWheel"), lxT("Event"), btoa (GetEv ())));
  Context.AddLine (xml_out (lxT ("EvOnDropFile"), lxT ("Event"), btoa (GetEv ())));

  return Context;
}

void
CControl::SetContext (lxStringList context)
{
  lxString name, type, value;

  CObject::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      xml_in (Context.GetLine (i), name, type, value);
     
      //printf("Set%ls\n",name.c_str()); 
 
      if (name.compare (lxT("X")) == 0)
	SetX (atoi (value));
      if (name.compare (lxT("Y")) == 0)
	SetY (atoi (value));
      if (name.compare (lxT("Width")) == 0)
	SetWidth (atoi (value));
      if (name.compare (lxT("Height")) == 0)
	SetHeight (atoi (value));
      if (name.compare (lxT("Hint")) == 0)
	SetHint (value);
      if (name.compare (lxT("Enable")) == 0)
	SetEnable (atoi (value));
      if (name.compare (lxT("Visible")) == 0)
      {
	SetVisible (!(atoi (value)),false);
	SetVisible (atoi (value));
      }
      if (name.compare (lxT("Color")) == 0)
	if(value.compare(lxT("#000001")) != 0 )//color not defined      
	   SetColor (lxColor(value));
      if (name.compare ("PopupMenu") == 0)
	if (value.compare ("NULL") != 0)
	  SetPopupMenu (dynamic_cast < CPMenu * >(Win->GetChildByName (value)));
      if (name.compare (lxT("EvMouseMove")) == 0)
	SetEv (atob (value), true);
      if (name.compare (lxT("EvMouseButtonPress")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvMouseButtonRelease")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvMouseButtonClick")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvMouseButtonDoubleClick")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvKeyboardPress")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvKeyboardRelease")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvKeyboardKey")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvOnDraw")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvOnFocusIn")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvOnFocusOut")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT("EvMouseWheel")) == 0)
	SetEv (atob (value));
      if (name.compare (lxT ("EvOnDropFile")) == 0)
        SetEv (atob (value));
    }
}



void
CControl::WriteXMLContext (lxString filename, bool first)
{
  lxStringList list;
  list = GetContext ();
  list.InsertLine (lxT("<") + Name + lxT(">"), 0);
  if (first)
    list.SaveToFile (filename);
  else
    list.AppendToFile (filename);

  for (int i = 0; i <= ChildCount; i++)
    {
      Child[i]->WriteXMLContext (filename, false);
      /*    
         list=Child[i]->GetContext();
         list.InsertLine("<"+Child[i]->GetName()+">",0);
         list.AddLine("<\\"+Child[i]->GetName()+">");
         list.AppendToFile(filename);    
       */
    }
  list.Clear ();
  list.AddLine (lxT("</") + Name + lxT(">"));
  list.AppendToFile (filename);
}

void
CControl::LoadXMLContext (lxString filename)
{
  lxTextFile fin;
  lxStringList list;
  lxString line, name;

  fin.Open(filename);
  fin.GoToLine(0);
  
  //printf("<XML_%ls>\n",Name.c_str());
 
  if (fin.IsOpened())
    {
      list.Clear ();
      while (fgetline (fin, line))
	{
#ifdef _DEBUG_
#ifdef __UNICODE__
          printf("%ls == %ls ???\n",(const wchar_t*)line.c_str(),(const wchar_t*) (lxT("<") + Name + lxT(">")).c_str());
#else
          printf("%s == %s ???\n",(const char*)line.c_str(), (const char *)(lxT("<") + Name + lxT(">")).c_str());
#endif
#endif

	  if (line.compare (lxT("<") + Name + lxT(">")) == 0)
	    {
	      fgetline (fin, line);
	      do
		{
		  list.AddLine (line);
		  fgetline (fin, line);
		}
	      while (line[0] == ' ');
	      SetContext (list);

	      while (line.compare (lxT("</") + Name + lxT(">")) != 0)
		{
		  name = line.substr (1, line.size () - 2);
		  CControl *ch = GetChildByName (name);
		  if (ch != NULL)
		    ch->LoadXMLContext (filename);
		  else
		    printf ("Child Not Found! %s \n", (char *)name.char_str ());
		  do
		    {
		      fgetline (fin, line);
		    }
		  while ((line.compare (lxT("</") + name + lxT(">")) != 0));
		  fgetline (fin, line);
		}

	    }

	}

      fin.Close();
      //printf("<\\XML_%s>\n",Name.c_str());
    }
  else
    printf ("File not found!\n");


}

/*
XRectangle
CControl::GetRectangle (void)
{
  XRectangle rec;
  rec.x = X;
  rec.y = Y;
  rec.width = Width;
  rec.height = Height;
  return rec;
}
*/

//properties


void
CControl::SetFont (const lxString font)
{
  FontName = font;

}



lxString CControl::GetFontName (void)
{
  return FontName;
}

void
CControl::SetFontSize (uint size)
{
  FontSize = size;
}

uint
CControl::GetFontSize (void)
{
  return FontSize;
}

void
CControl::SetFontFamily (int family)
{
}

void
CControl::SetHint(lxString hint)
{
  Hint=hint;
}

lxString
CControl::GetHint(void)
{
 return Hint;
}

void 
CControl::CalcRXY(void)
{
  CWindow *o,*t; 
  o = dynamic_cast < CWindow * >(Owner);
  t = dynamic_cast < CWindow * >(this);
  
  if(o) //owner == CWindow
  {
    if(t) //this == CWindow 
    {
      RX=0;	  
      RY=0;
    }
    else //this != CWindow
    {
      CMenu  *m = dynamic_cast < CMenu * >(this);
      if((o->HasMenu)&&(!m))
        RY=Y+25;
      else
        RY=Y;
      
      RX=X;	  
    }
  }
  else //owner != CWindow
  {
    if(Owner != NULL)
    {
      RX=Owner->GetRX()+X;  
      RY=Owner->GetRY()+Y;  
    }
  }
}

void
CControl::SetX (int x)
{
  Erase ();
  X = x;
  Update ();
}

int
CControl::GetX (void)
{
  return X;
}

void
CControl::SetY (int y)
{
  Erase ();
  Y = y;
  Update ();
}

int
CControl::GetY (void)
{
  return Y;
}

int
CControl::GetRX (void)
{
  return RX;
}

int
CControl::GetRY (void)
{
  return RY;
}

void
CControl::SetWidth (uint w)
{
  Erase ();
  Width = w;
  GChanges=true;
  Draw ();
}

uint
CControl::GetWidth (void)
{
  return Width;
}

void
CControl::SetHeight (uint h)
{
  Erase ();
  Height = h;
  GChanges=true;
  Draw ();
}

uint
CControl::GetHeight (void)
{
  return Height;
}

void
CControl::SetBorder (uint b)
{
  Border = b;
}

uint
CControl::GetBorder (void)
{
  return Border;
}

void
CControl::SetColor (XColor c)
{
  Color = c;
  Update();
}

void
CControl::SetColor (const lxString name)
{
  ColorName = name;

  if(name.compare("#000001") == 0)return;

  if (Win != NULL)
    Color = ColorByName (name);
  else
    ColorSet = true;
 
  Update();
}

void
CControl::SetColor (uint r, uint g, uint b)
{
  if (Win != NULL)
    {
      Color = ColorByRGB (r, g, b);
    }
  else
    {
      ColorSet = true;
      ColorName = "";
    }
  Update();
}

lxColor CControl::GetColor (void)
{
  return Color;
}


bool
CControl::GetCanExecuteEvent (void)
{
  return CanExecuteEvent;
}

void
CControl::SetCanExecuteEvent (bool cee)
{
  CanExecuteEvent = cee;
  CanExecuteEventOld = cee;
}

void
CControl::SetEnable (bool enable)
{
  XColor temp;
  
  if (Enable != enable)
    {
    temp=Color;  
    Color=DisableColor;
    DisableColor=temp;
    
    Enable = enable;
    SetCanExecuteEvent (Enable);
    SetCanFocus (Enable);
   
    Draw();
    }
  
}

bool CControl::GetEnable (void)
{
  return Enable;
}

void
CControl::SetPen (int pen)
{
  Pen = pen;
  Draw ();
}

int
CControl::GetPen (void)
{
  return Pen;
}

CControl *
CControl::GetOwner (void)
{
  return Owner;
}

void
CControl::SetOwner (CControl * control)
{
  Owner = control;

}

void
CControl::SetVisible (bool visible, bool update)
{
  if (update)
    if (visible)
      {
	CanExecuteEvent = CanExecuteEventOld;
	Visible = visible;
	Update ();
      }
    else
      {
	CanExecuteEventOld = CanExecuteEvent;
	Erase ();
	Visible = visible;
      }
  else
    Visible = visible;
}

bool
CControl::GetVisible (void)
{
  return Visible;
}

void
CControl::SetPopupMenu (CPMenu * poupmenu)
{
  PopupMenu = poupmenu;
}

void
CControl::SetFocus (bool focus)
{
  if (CanFocus)
    {
      if (focus)
	{
	  Win->SetControlOnFocus (this);
	  focus_in ();
	}
      else
	{
	  Win->SetControlOnFocus (NULL);
	  focus_out ();
	}
    }
}

bool
CControl::GetFocus (void)
{
  if (Win->GetControlOnFocus () == this)
    return true;
  else
    return false;
}

void
CControl::SetCanFocus (bool canfocus)
{
  CanFocus = canfocus;
}

bool
CControl::GetCanFocus (void)
{
  return CanFocus;
}

bool
CControl::GetDynamic (void)
{
  return Dynamic;
}

int
CControl::GetChildCount (void)
{
  return ChildCount;
}


CControl *
CControl::GetChild (uint child)
{
  return Child[child];
}

CControl *
CControl::GetChildByName (const lxString child)
{
  for (int a = 0; a <= ChildCount; a++)
    if (Child[a]->GetName ().compare (child) == 0)
      return Child[a];
  return NULL;
}


void
CControl::SetFOwner (CControl * control)
{
  FOwner = control;
}

CControl *
CControl::GetFOwner (void)
{
  return FOwner;
}

void
CControl::SetDragAcceptFiles(bool accept)
{
 DragAcceptFiles = accept;
}

//operators

void *
CControl::operator new (size_t sz)
{
/*The use of calloc instead malloc preserve Dynamic=false in controls owned */
  CControl *m = (CControl *) calloc (sz, 1);
  if (!m)
    puts ("out of memory");
  m->Dynamic = true;
  return (void *) m;
}

void *
CControl::operator new[] (size_t sz)
{
  printf ("operator new[]: %ld Bytes\n", sz);
  return::new char[sz];
}
  
void 
CControl::operator delete(void *p)
{
  free(p);
}

//events

void
CControl::mouse_move (vEvent event)
{
  if ((FOwner) && (EvMouseMove))
    (FOwner->*EvMouseMove) (this, 0, event.motion.x-RX, event.motion.y-RY, event.motion.state);
}

void
CControl::button_press (vEvent event)
{
  BTimePress = event.button.time;

  if ((FOwner) && (EvMouseButtonPress))
    (FOwner->*EvMouseButtonPress) (this, event.button.button, event.button.x-RX,
				 event.button.y-RY, event.button.state);

  if ((event.button.button == 3) && (PopupMenu != NULL)&&((PopupMenu->GetChildCount ()) != -1))
    {
      //int x, y;
      //int child;
      if (!PopupMenu->GetWWindow () != 0)
	{
	  //Application.ACreateWindow (SubMenu,Win);
	  Application->ACreateWindow (PopupMenu);
	}
      /*
      PopupMenu->SetX (0);
      PopupMenu->SetY (0);
      */
   
      PopupMenu->SetX (event.button.x);
      PopupMenu->SetY (event.button.y);
     
      PopupMenu->Show ();
      PopupMenu->Draw ();
      while (PopupMenu->GetVisible ())
	{
	  Application->ProcessEvents (PopupMenu);
	}
    
    }
}

void
CControl::button_release (vEvent event)
{
  BTimeRelease = event.button.time;

  if ((FOwner) && (EvMouseButtonRelease))
    (FOwner->*EvMouseButtonRelease) (this, event.button.button,
				   event.button.x-RX, event.button.y-RY,
				   event.button.state);


  if ((BTimeRelease - BTimeClick) < DOUBLECLICKTIME)
    {
      if ((FOwner) && (EvMouseButtonDoubleClick))
	{
	  (FOwner->*EvMouseButtonDoubleClick) (this, event.button.button,
					     event.button.x, event.button.y,
					     event.button.state);
	}
    }
  else
    {
      if ((FOwner) && (EvMouseButtonClick))
	{
	  (FOwner->*EvMouseButtonClick) (this, event.button.button,
				       event.button.x, event.button.y,
				       event.button.state);
	}
      BTimeClick = BTimePress;
    }

  if ((event.button.button == 3) && (PopupMenu != NULL))
    {
      PopupMenu->SetVisible (false);
      Win->Draw ();
    }
}

void
CControl::key_press (vEvent event)
{
  if ((FOwner) && (EvKeyboardPress))
  {
    (FOwner->*EvKeyboardPress) (this, event.key.key, event.key.key , event.key.state);
  }
}

void
CControl::key_release (vEvent event)
{
  if ((FOwner) && (EvKeyboardRelease))
  {
    (FOwner->*EvKeyboardRelease) (this, event.key.key, event.key.key , event.key.state);
  }
}


void
CControl::focus_in (void)
{
  Update ();
  if ((FOwner) && (EvOnFocusIn))
    (FOwner->*EvOnFocusIn) (this);
}

void
CControl::focus_out (void)
{
  Update ();
  if ((FOwner) && (EvOnFocusOut))
    (FOwner->*EvOnFocusOut) (this);
}

void
CControl::pointer_in (void)
{
  PointerOn = true;
  if ((FOwner) && (PointerIn))
    (FOwner->*PointerIn) (this);
}

void
CControl::pointer_out (void)
{
  PointerOn = false;
  if ((FOwner) && (PointerOut))
    (FOwner->*PointerOut) (this);
}

void
CControl::on_draw (void)
{
  if ((FOwner) && (EvOnDraw))
    (FOwner->*EvOnDraw) (this);
}


bool 
CControl::GetCanVisible (void)
{
  return CanVisible;
}

void
CControl::on_drop_files(vEvent event)
{
 if ((FOwner) && (EvOnDropFile))
  {
/*
   wxString name;
   wxString* dropped = event->GetFiles ();
   wxArrayString files;

   for (int i = 0; i < event->GetNumberOfFiles (); i++)
    {
     name = dropped[i];
     if (wxFileExists (name))
      files.push_back (name);
     else if (wxDirExists (name))
      wxDir::GetAllFiles (name, &files);
    }
 
   for (size_t i = 0; i < files.size (); i++)
    {
     (FOwner->*EvOnDropFile) (this, (const char *) files[i].c_str ());
    }
*/
  }
}

