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

#ifndef CAPPLICATION
#define CAPPLICATION

#include"clxrad.h"
#include"cwindow.h"
#include"ctimer.h"
#include"cthread.h"
#include"chint.h"
#include<locale.h>

class CWindow;

class CApplication
{
private:
  vEvent AEvent, LAEvent;
  CWindow **AWindowList;
  int AWindowCount;
  CTimer **TimerList;
  int TimerCount;
  CThread **ThreadList;
  int ThreadCount;
  timeval LastDrawTime;
  int PixelsCount;
  TXColor *ColorTable;
  bool Exit;
  CControl* HintControl;
  int HintTime;
  int HintX,HintY;
  int ADepth;
  unsigned int AWhiteColor;
  unsigned int ABlackColor;
  int Tag;
  lxString Title;
public:
    CApplication (void);
   ~CApplication (void);
  //Display *GetADisplay (void);
  //Screen *GetAScreen (void);
  //XIM GetIM (void);
  void Start (void);
  void ACreateWindow (CWindow * AWindow,CWindow* window=NULL);
  void ADestroyWindow (CWindow * AWindow);
  bool ProcessEvents (CWindow * AWindow);
  bool ProcessEvents (void);
  void AddTimer(CTimer *tm);	
  void RemoveTimer(CTimer *tm);	
  void AddThread(CThread *td);	
  void RemoveThread(CThread *td);	
  void Draw (void);
  void Update (void);
  void Load (void);
  int Aargc;
  char **Aargv;
  bool GetExit (void);
  //propiedades
  int GetAWindowCount (void);
  CWindow *GetAWindow (uint window);
  void SetTag (int x);
  int GetTag ();
  lxString GetTitle ();
  //Window *GetADefaultRootWindow (void);
  int *GetADepth (void);
  unsigned int *GetAWhiteColor (void);
  unsigned int *GetABlackColor (void);
  void SetHintControl(CControl* hcontrol,int x,int y);
  void AddToColorTable (lxString colorname, XColor color, XColor displaycolor);
  bool XSearchInColorTable (lxString name, XColor * color);
  bool XSearchInColorTable (XColor * color);
};


#endif
