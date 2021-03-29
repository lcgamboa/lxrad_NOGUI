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


#ifndef LXUTILS_H
#define	LXUTILS_H

#include"clxrad.h"
#include"mstring.h"
#include<math.h>

class CWindow;

//Compatibillity 
#define CPWindow CWindow
#define CImage CDraw
#define lxT
#define _T
#define CCanvas CPaint
#define XColor unsigned int


typedef struct
{
    int x;
    int y;
} lxPoint;

struct TXColor
{
  lxString name;
  XColor color;
  XColor displaycolor;
};

void mprint(lxString message);

void eprint(lxString error);

XColor ColorByRGB (unsigned short r, unsigned short g, unsigned short b);

XColor ColorByName (lxString name);


class lxTextFile
{
  private:	
  FILE * f;
  lxString fn;
  public:
  lxTextFile();
  int Open(lxString fname);
  int Create(lxString fname);
  bool IsOpened(void);
  void Close(void);
  void GoToLine(int l);
  FILE * GetFd(void);
  operator FILE*() const;
  void Clear(void);
  void Write(void){};
  void AddLine(lxString line);
};

#define Imlib_Image int
class lxImage
{
private:
Imlib_Image Image;
public:
lxImage(Imlib_Image img);
lxImage(CWindow * window);
~lxImage();
bool LoadFile(lxString fname, int orientation = 0 , float scalex = 1.0, float scaley = 1.0, int useAlpha = 0);
void Destroy();
operator Imlib_Image() const;
};

class lxSize
{
private:
  unsigned int w,h;
public:
  unsigned int GetWidth(void){return w;};
  unsigned int GetHeight(void){return h;};
  void SetWidth(unsigned int w_){w=w_;}
  void SetHeight(unsigned int h_){h=h_;};
};

#define Pixmap int

class lxBitmap
{
private:
Pixmap CPixmap;
public:
~lxBitmap();
lxBitmap (lxImage * img, CWindow * win ,int orient=0);
lxBitmap (int width, int height); 
Pixmap  GetPixmap(void);
operator Pixmap() const;
lxSize GetSize(void);
unsigned int GetWidth(void);
unsigned int GetHeight(void);
};

class lxSound
{
private:
public:
  bool Create(lxString fname);	
  void Stop(void);
  void Play(int flags);
};

class lxFileName
{
private:
lxString FName;
public:
  void Assign(lxString fname);
  void MakeAbsolute(void);
  lxString GetFullPath(void);
};

//#define lxPoint XPoint

typedef struct
{
int x,y,width,height;	
}lxRect;

class lxColor
{
private:	
  XColor Color;
public:
  lxColor();
  lxColor(XColor color);
  lxColor(const char * name);
  lxColor(unsigned char r, unsigned char g, unsigned char b);
  lxString GetAsString(int flags =0);
  operator XColor() const;
  unsigned char Red(void){return 0;};
  unsigned char Green(void){return 0;};
  unsigned char Blue(void){return 0;};
};

class lxCursor
{
public:
  lxCursor();
  lxCursor(int type);
};

class lxFont
{
private:
public:
  lxFont();
  lxFont(int size,int family,int style,int weight);
};


#define lxFONTFAMILY_DEFAULT  0x00
#define lxFONTFAMILY_TELETYPE 0x01
#define lxFONTSTYLE_NORMAL 0x01
#define lxFONTWEIGHT_BOLD 0x01
#define lxFONTWEIGHT_NORMAL 0x00


#define lxCURSOR_CROSS 0x01
#define lxCURSOR_ARROW 0x02
#define lxCURSOR_SIZENWSE 0x04
#define lxCURSOR_SIZING  0x08
#define lxCURSOR_SIZENS  0x10
#define lxCURSOR_SIZEWE  0x20

#define lxALIGN_LEFT   0x00
#define lxALIGN_RIGHT  0x01
#define lxALIGN_CENTER 0x02
#define lxALIGN_CENTER_VERTICAL 0x04


#define lxFD_OPEN 	0x1
#define lxFD_SAVE 	0x2
#define lxFD_CHANGE_DIR 0x4

#define lxSOUND_ASYNC  0x01
#define lxSOUND_LOOP   0x02

#define lxEXEC_MAKE_GROUP_LEADER 0x01

#define lxConvUTF8 2048

#define lxC2S_HTML_SYNTAX 0x01

#define lxEXEC_ASYNC 0x01
#define lxEXEC_SYNC  0x02      

#define lxMOUSE_BTN_RIGHT 0x01
#define lxMOUSE_BTN_LEFT  0x02      

#define LXK_SHIFT 1  
#define LXK_RIGHT 2
#define LXK_LEFT  3
#define LXK_DOWN  4
#define LXK_UP    5
#define LXK_CONTROL  6

lxBitmap * lxGetBitmapRotated(lxImage *image, CWindow * win, int orientation); 

void lxMilliSleep(unsigned int time);
void lxSetCursor(lxCursor cursor); 
bool lxFileExists(lxString fname);
int lxExecute(lxString cmd,unsigned int flags=0, void * arg = NULL);
lxString lxGetCwd(void);
int lxSetWorkingDirectory(lxString dir);
bool lxLaunchDefaultBrowser(lxString url);
bool lxLaunchDefaultApplication(lxString cmd);

lxString lxGetUserDataDir(lxString appname="");
lxString lxGetTempDir(lxString appname="");
lxString lxGetExecutablePath(lxString appname="");

lxStringList lxListDirRec(const lxString &dirname);
bool lxZipDir(const lxString &in_dirname, const lxString &out_filename);
bool lxUnzipDir(const lxString &in_filename, const lxString &out_dirname);

bool lxRemoveFile(const char* fname);
bool lxRemoveDir(const char* dirname);
bool lxCreateDir(const char * dirname);
bool lxRenameFile(lxString oldfname, lxString newfname);

unsigned int lxGetDisplayWidth(int disp);
unsigned int lxGetDisplayHeight(int disp);

#endif	/* LXUTILS_H */
