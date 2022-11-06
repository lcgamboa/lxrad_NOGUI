/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gamboa Lopes

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

#include<stdio.h>

#include"../include/cwindow.h"
#include"../include/capplication.h"
#include"../include/newcontrolbycname.h"



//CWindow _______________________________________________________________

CWindow::CWindow (void)
{
  WWindow = 0;
  SetClass ("CWindow");
  Win = NULL;
  PixmapBuffer=true;
  HasMenu=0;
  //  PixmapBuffer=false;
  XMouse = 0;
  YMouse = 0;
  SetX (0);
  SetY (0);
  SetWidth (300);
  SetHeight (200);
  PWidth=0;
  PHeight=0;
  SetBorder (1);
  Visible = 1;
  show = 0;
  Title = "LXRAD Window";
  WParent=NULL;
  WPixmap = 0;

  ControlOnFocus = NULL;
  LastControl = NULL;
//events
  EvOnCreate = NULL;
  EvOnDestroy = NULL;
  EvOnShow = NULL;
  EvOnHide = NULL;
  EvOnEnter = NULL;
  EvOnLeave = NULL;
  
}

CWindow::~CWindow (void)
{

}

void
CWindow::WCreate (CWindow* window)
{
  WWindow = Application->GetAWindowCount ()+2;
 
  ADepth = Application->GetADepth ();
  //ADefaultRootWindow = Application->GetADefaultRootWindow ();
  ABlackColor = Application->GetABlackColor ();
  AWhiteColor = Application->GetAWhiteColor ();
  
  Win = this;
  CreatePixmap(); 
  WPaint.Create (this);
  Paint = &WPaint;
  
  Create (this);
  Draw();
  
  on_create ();
  
  printf("Window [%s] create\n",Title.c_str()); 
  
  if(Visible) Show ();
 
}

void
CWindow::Destroy (void)
{
  CControl::Destroy ();
  DestroyPixmap();
}


void
CWindow::Draw(void)
{
  if(Paint == NULL)return;
  Paint->InitDraw(this);
  Paint->Pen.SetColor(Color);
  Paint->Rectangle ( 0, 0, Width, Height);
  CControl::Draw ();
}

void
CWindow::SetPixmapBuffer(bool pbuffer)
{
  PixmapBuffer=pbuffer;
}

bool
CWindow::GetPixmapBuffer(void)
{
  return PixmapBuffer;
}

Pixmap 
CWindow::GetPixmap(void)
{
  return WPixmap;
}

void
CWindow::DestroyPixmap (void)
{
  if ((WPixmap != 0)&&(WPixmap != WWindow))
    {
      WPixmap=0;
    }
}

void
CWindow::CreatePixmap(bool draw)
{
  if(PixmapBuffer)
  {
  if((Width > PWidth) || ( Height > PHeight))
  {
  DestroyPixmap();	
  if(Width > PWidth)PWidth=Width;
  if(Height > PHeight)PHeight=Height;
  if(draw) Draw();
  }
  }
  else
   WPixmap=WWindow;
}



void
CWindow::DestroyChild (CControl * control)
{
  if (control == ControlOnFocus)
    ControlOnFocus = NULL;
  CControl::DestroyChild (control);
}

void
CWindow::DestroyChilds (void)
{
  ControlOnFocus = NULL;
  CControl::DestroyChilds ();
}


void
CWindow::WDestroy (void)
{
  Hide ();
  on_destroy ();
  if ((CanDestroy) || (this == Application->GetAWindow ((uint) 0)))
    {
      Destroy ();
      WPaint.Destroy ();

      Win = NULL;
      Application->ADestroyWindow (this);
      WWindow = 0;
    }
}

void
CWindow::Show (void)
{
  if(Win != NULL)
    {
      if(!show)
      {
	on_show ();
        show=1;
        printf("Window [%s] show\n",Title.c_str()); 
      }
      SetVisible (true);
      Draw();
      Update ();
    }
}

void
CWindow::ShowExclusive (void)
{
  Show ();
  CanExitExclusive = true;
  while (CanExitExclusive)
    Application->ProcessEvents (this);
}

void
CWindow::Hide (void)
{
   if(show)
   {
     on_hide ();
     show=0;
     SetVisible (false);
     printf("Window [%s] hide\n",Title.c_str()); 
   }
}

void
CWindow::HideExclusive (void)
{
  CanExitExclusive = false;
  Hide ();
}

void
CWindow::Update (void)
{
  /*	
  for (int i = 0; i <= ChildCount; i++)
    {
      if (Child[i]->GetVisible ())
	{
	  if(PixmapBuffer)	
	    Child[i]->Update ();
	  else
	    Child[i]->Draw ();
	}
    }
  */
  CControl::Update();
}

void
CWindow::SetOverrideRedirect (bool redirect)
{
}

void
CWindow::SetSaveUnder (bool saveunder)
{
}




bool
CWindow::WEvents (vEvent WEvent)
{
  int ret=0;

  switch (WEvent.type)
    {
    case ClientMessage:
      ret=1;
      break;
    case DestroyNotify:
      on_destroy ();
      ret=1;
      break;
    case CirculateNotify:
      eprint( "CirculateNotify\n");
      ret=1;
      break;
    case ConfigureNotify:
      //look in the end of function for the last
      ret=1;
      break;
//    case GravityNotify:
//      ret=1;
//      break;
    case MapNotify:
      on_show ();
      ret=1;
      break;
//  case ReparentNotify:                
//  ret= 1;break;
    case UnmapNotify:
      on_hide ();
      ret=1;
      break;
//  ret=1 1;break;
//  case MotionNotify:          
//  ret=1 1;break;
//  case KeyPress:              
//  ret= 1;break;
//  case KeyRelease:            
//  ret= 1;break;
//  case ButtonPress:           
//  ret= 1;break;
//  case ButtonRelease:
//  ret= 1;break;
    case EnterNotify:
      on_enter ();
      ret= 1;
      break;
    case LeaveNotify:
      on_leave ();
      ret=1;
      break;
//  case ColormapNotify:                
//  ret=1 1;break;
//  case GraphicsExpose:                
//  ret=1 1;break;
//  case NoExpose:              
//  ret=1 1;break;
    case FocusIn:
      ret= 1;
      break;
    case FocusOut:
      ret= 1;
      break;
//  case KeymapNotify:          
//  ret=1 1;break;
//  case PropertyNotify:                
//  ret=1 1;break;
//  case ResizeRequest:         
//  ret= 1;
//  break;
    case MappingNotify:
      ret= 1;
      break;
//  case SelectionClear:                
//  ret= 1;break;
//  case SelectionNotify:               
//  ret= 1;break;
//  case SelectionRequest:      
//  ret= 1;break;
//  case VisibilityNotify:      
//      eprint("visibilityNotify\n");
//                      ret= 1;
//                      break;
//  case LASTEvent:             
//  ret= 1;break;
    default:
      CControl::Event (WEvent);
      ret= 1;
    case Expose:
      ret= 1;
      break;
    }


  if ((LEvent.type != WEvent.type)&&(LEvent.type == ConfigureNotify))
  {

  }


  LEvent=WEvent;

  return ret;
}


lxStringList CWindow::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("Title=" + GetTitle () + ";String");
  //events 
  Context.AddLine ("OnCreate=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnDestroy=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnShow=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnHide=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnEnter=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnLeave=" + btoa (GetEv (false)) + ";event");
  return Context;
}

void
CWindow::SetContext (lxStringList context)
{
  Erase ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      lxString line = Context.GetLine (i);
      lxString arg;
      eqparse (line, arg);
      if (line.compare ("Title") == 0)
	SetTitle (arg);
      if (line.compare ("OnCreate") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnDestroy") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnShow") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnHide") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnEnter") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnLeave") == 0)
	SetEv (atob (arg), false);
    }
  Draw ();
}

void
CWindow::CirculateFocus (bool asc)
{
  if (asc)
    {
      for (int c = 0; c < ChildCount; c++)
	{
	  if (Child[c] == ControlOnFocus)
	    {
	      if (Child[c + 1]->GetCanFocus ())
		{
		  Child[c + 1]->SetFocus (true);
		  return;
		}
	      else
		{
		  SetControlOnFocus (NULL);
		  ControlOnFocus = Child[c + 1];
		  CirculateFocus (asc);
		  return;
		}
	    }
	}
      if (Child[0]->GetCanFocus ())
	{
	  Child[0]->SetFocus (true);
	  return;
	}
      else
	{
	  SetControlOnFocus (NULL);
	  ControlOnFocus = Child[0];
	  CirculateFocus (asc);
	  return;
	}
    }
  else
    {
      for (int c = ChildCount - 1; c >= 0; c++)
	if (Child[c] == ControlOnFocus)
	  {
	    if (Child[c - 1]->GetCanExecuteEvent ())
	      {
		Child[c - 1]->SetFocus (true);
		return;
	      }
	    else
	      ControlOnFocus = Child[c - 1];
	  }
    }
}

void
CWindow::SetFocus (void)
{
}




//propiedades
int 
CWindow::GetWWindow (void)
{
  return WWindow;
}

int *
CWindow::GetADepth (void)
{
  return ADepth;
}

void
CWindow::SetCanDestroy (bool candestroy)
{
  CanDestroy = candestroy;
}

bool
CWindow::GetCanDestroy (void)
{
  return CanDestroy;
}

void
CWindow::SetXMouse (uint x)
{
  XMouse = x;
}

uint
CWindow::GetXMouse (void)
{
  return XMouse;
}

void
CWindow::SetYMouse (uint y)
{
  YMouse = y;
}

uint
CWindow::GetYMouse (void)
{
  return YMouse;
}

void
CWindow::SetTitle (const lxString & title)
{
  Title = title;
}

lxString CWindow::GetTitle (void)
{
  return Title;
}

CControl *
CWindow::GetControlOnFocus (void)
{
  if (ControlOnFocus)
    return ControlOnFocus;
  else
    return NULL;
}


void
CWindow::SetControlOnFocus (CControl * controlonfocus)
{
  if ((ControlOnFocus != NULL) && (ControlOnFocus->GetCanFocus ()))
    {
      CControl *last = ControlOnFocus;
      ControlOnFocus = NULL;
      last->focus_out ();
    }
  ControlOnFocus = controlonfocus;
}

CControl *
CWindow::GetLastControl (void)
{
  if (LastControl)
    return LastControl;
  else
    return NULL;
}

void
CWindow::SetLastControl (CControl * lastcontrol)
{
  LastControl = lastcontrol;
}

void
CWindow::SetX (int x)
{
  CControl::SetX (x);
}

void
CWindow::SetY (int y)
{
  CControl::SetY (y);
}

void
CWindow::SetWidth (uint width)
{
  CControl::SetWidth (width);
}

void
CWindow::SetHeight (uint height)
{
  CControl::SetHeight (height);
}

int
CWindow::GetClientWidth(void)
{
 return Width;
}


int
CWindow::GetClientHeight(void)
{
 return Height;
}

//operators

void *
  CWindow::operator
new (size_t sz)
{
  CWindow *m = (CWindow *) calloc (sz, 1);
  if (!m)
    puts ("out of memory");
  m->Dynamic = true;
  m->CanDestroy = true;
  return (void *) m;
}

//eventos

void
CWindow::on_create (void)
{
  if ((FOwner) && (EvOnCreate))
    (FOwner->*EvOnCreate) (this);
}

void
CWindow::on_destroy (void)
{
  if ((FOwner) && (EvOnDestroy))
    (FOwner->*EvOnDestroy) (this);
}

void
CWindow::on_show (void)
{
  if ((FOwner) && (EvOnShow))
    (FOwner->*EvOnShow) (this);
}

void
CWindow::on_hide (void)
{
  if ((FOwner) && (EvOnHide))
    (FOwner->*EvOnHide) (this);
}

void
CWindow::on_enter (void)
{
  if ((FOwner) && (EvOnEnter))
    (FOwner->*EvOnEnter) (this);
}

void
CWindow::on_leave (void)
{
  if ((FOwner) && (EvOnLeave))
    (FOwner->*EvOnLeave) (this);
}


bool 
CWindow::LoadXMLContextAndCreateChilds(lxString filename, CControl* ctrl)
{
  FILE* file2;
  lxStringList list;
  lxString line;

  file2 = fopen (filename.c_str(),"r");
  rewind(file2);
  

  if (file2)
    {

      if(ctrl == NULL)//for owner window
      {
        if(fgetline (file2, line))
        {
          ctrl = this;
          ctrl->SetName(line.substr (1, line.size () - 2));//Get Window name
          ctrl->SetFOwner (this);
          rewind(file2);
        }
      }

      list.Clear ();
      while (fgetline (file2, line))
        {
          if (line.compare (lxT ("<") + ctrl->GetName () + lxT (">")) == 0)
            {
              fgetline (file2, line);
              do
                {
                  list.AddLine (line);
                  fgetline (file2, line);
                }
              while (line.c_str()[0] == ' ');
              ctrl->SetContext (list);

              while (line.compare (lxT ("</") + ctrl->GetName () + lxT (">")) != 0)
                {
                  lxString controlclass, ctype, name, cname;

                  cname = line.substr (1, line.size () - 2);
                  fgetline (file2, line);
                  xml_in (line, name, ctype, controlclass);

                  CControl *ch = newcontrolbycname (controlclass);
                  ch->SetName (cname);
                  ch->SetFOwner (ctrl);
                 
		  /* 
		  if (ch->GetClass ().compare (lxT ("CItemMenu")) == 0)
                    {
                      ch->SetVisible (false, false);
                    }
                  */
                  ctrl->CreateChild (ch);

                  if (ch != NULL)
                    LoadXMLContextAndCreateChilds (filename, ch);
                  else
                    printf ("Child Not Found! %s \n", (char*) name.char_str ());

                  do
                    {
                      fgetline (file2, line);
                    }
                  while ((line.compare (lxT ("</") + cname + lxT (">")) != 0));
                  fgetline (file2, line);
                }

            }

        }

      fclose(file2);
      return 1;
    }
  else
    printf ("File (%s) not found!\n",(char *)filename.char_str());

  return 0;
}

bool 
CWindow::GetCanExitExclusive(void)
{
  return CanExitExclusive;
}
  
CWindow* 
CWindow::GetWWidget (void)
{
  return this; 
}
