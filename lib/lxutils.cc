/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2021  Luis Claudio Gamboa Lopes

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


#include"../include/lxutils.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include <minizip/zip.h>
#include <minizip/unzip.h>

#include<pthread.h>

//-------------------------------------------------------------------------

lxTextFile::lxTextFile()
{
 f = NULL;
}

int
lxTextFile::Open(lxString fname)
{
 fn = fname;
 f = fopen (fname.c_str (), "rw");
 if (f)
  return 1;
 else
  return 0;
}

int
lxTextFile::Create(lxString fname)
{
 fn = fname;
 f = fopen (fname.c_str (), "rw");
 if (f)
  return 1;
 else
  return 0;
}

bool
lxTextFile::IsOpened(void)
{
 if (f)
  return 1;
 else
  return 0;
}

void
lxTextFile::Close(void)
{
 fclose (f);
 f = NULL;
}

void
lxTextFile::GoToLine(int l)
{
 //FIXME	
 fseek (f, l, SEEK_SET);
}

FILE *
lxTextFile::GetFd(void)
{
 return f;
}

lxTextFile::operator FILE*() const
{
 return f;
}

void
lxTextFile::Clear(void)
{
 if (f) fclose (f);
 f = fopen (fn.c_str (), "w");
 if (f) fclose (f);
 f = fopen (fn.c_str (), "rw");
}

void
lxTextFile::AddLine(lxString line)
{
 fprintf (f, "%s\n", line.c_str ());
}

//-------------------------------------------------------------------------

lxImage::lxImage(CWindow * window)
{
 Image = 0;
}

lxImage::lxImage(Imlib_Image img)
{
 Image = img;
}

lxImage::~lxImage()
{
 if (Image)
  {
   Image = 0;
  }
}

bool
lxImage::LoadFile(lxString fname, int orientation, float scalex, float scaley, int useAlpha, double * ret_sx, double * ret_sy)
{
  Destroy ();
  return 1;
}
bool 
lxImage::CreateBlank(const unsigned int width, const unsigned int height, int orientation, double scalex, double  scaley ){
  Destroy ();
  return 1;
}

void
lxImage::Destroy(void)
{
 if (Image)
  {
   Image = 0;
  }
}

lxImage::operator
Imlib_Image() const
{
 return Image;
}
//-------------------------------------------------------------------------

lxBitmap::~lxBitmap()
{

}

lxBitmap::lxBitmap(lxImage * img, CWindow *win, int orient)
{
}

lxBitmap::lxBitmap(int width, int height)
{
}

lxBitmap::operator
Pixmap() const
{
 return CPixmap;
}

Pixmap
lxBitmap::GetPixmap(void)
{
 return CPixmap;
}

lxSize
lxBitmap::GetSize(void)
{
 lxSize s;
 s.SetHeight (0);
 s.SetWidth (0);
 return s;
}

unsigned int
lxBitmap::GetWidth(void)
{
 return 0;
}

unsigned int
lxBitmap::GetHeight(void)
{
 return 0;
}

//-------------------------------------------------------------------------

bool
lxSound::Create(lxString fname)
{
 //FIXME	
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
 return false;
}

void
lxSound::Stop(void)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

void
lxSound::Play(int flags)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}
//-------------------------------------------------------------------------

void
lxFileName::Assign(lxString fname)
{
 FName = fname;
}

void
lxFileName::MakeAbsolute(void)
{
 char resolved_path[PATH_MAX];
 realpath (FName, resolved_path);
 FName = resolved_path;
}

lxString
lxFileName::GetFullPath(void)
{
 return FName;
}

//-------------------------------------------------------------------------

lxColor::lxColor() { }

lxColor::lxColor(XColor color)
{
 Color = color;
}

lxColor::lxColor(const char * name)
{
 if (name[0] == '#')
  {
   unsigned int r, g, b;
   char tmp[3];
   tmp[2] = 0;
   tmp[0] = name[1];
   tmp[1] = name[2];
   sscanf (tmp, "%02X", &r);
   tmp[0] = name[3];
   tmp[1] = name[4];
   sscanf (tmp, "%02X", &g);
   tmp[0] = name[5];
   tmp[1] = name[6];
   sscanf (tmp, "%02X", &b);

   Color = ColorByRGB (r, g, b);
  }
 else
  {
   Color = ColorByName (name);
  }
}

lxColor::lxColor(unsigned char r, unsigned char g, unsigned char b)
{
 Color = ColorByRGB (r, g, b);
}

lxString
lxColor::GetAsString(int flags)
{
 char cname[20];


   cname[0] = 0;

 return cname;
}

lxColor::operator
XColor() const
{
 return Color;
}

void 
lxColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
  Color = ColorByRGB (r, g, b);
}

lxColor SystemColor(int id)
{
   return lxColor(0, 0, 0);
}

//-------------------------------------------------------------------------

lxCursor::lxCursor()
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

lxCursor::lxCursor(int type)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

//-------------------------------------------------------------------------

lxFont::lxFont()
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

lxFont::lxFont(int size, int family, int style, int weight)
{
#ifdef _DEBUG 
 //printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
#endif
}

void 
lxFont::SetPointSize(int size)
{
#ifdef _DEBUG 
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
#endif
}
//-------------------------------------------------------------------------

void
lxMilliSleep(unsigned int time)
{
 usleep (time * 1000);
}

void
lxSetCursor(lxCursor cursor)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

bool
lxFileExists(lxString fname)
{
 struct stat sb;

 sb.st_mode = 0;

 stat (fname.c_str (), &sb);

 if (S_ISREG (sb.st_mode))
  return true;
 else
  return false;
}

int
lxExecute(lxString cmd, unsigned int flags, void * arg)
{
 if (flags != lxEXEC_SYNC)
  cmd += lxT (" &");
 return system (cmd.c_str ()) + 1;
}

lxString
lxGetCwd(void)
{
 char cwd[1024];
 if (getcwd (cwd, sizeof (cwd)) != NULL)
  return cwd;
 else
  return "";
}

int
lxSetWorkingDirectory(lxString dir)
{
 return chdir (dir.c_str ());
}

bool
lxLaunchDefaultBrowser(lxString url)
{
 lxString cmd = lxT ("xdg-open ") + url + lxT ("  &");
 return system (cmd.c_str ());
}

bool
lxLaunchDefaultApplication(lxString cmd)
{
 lxString cmd_ = lxT ("xdg-open ") + cmd + lxT ("  &");
 return system (cmd_.c_str ());
}

//-------------------------------------------------------------------------

bool
lxUnzipDir(const lxString &in_filename, const lxString &out_dirname)
{

 char fname[1024];
 unzFile uzf = unzOpen (in_filename.c_str ());

 if (uzf != NULL)
  {
   if (unzGoToFirstFile (uzf) == UNZ_OK)
    {
     do
      {
       unz_file_info finfo;
       unzGetCurrentFileInfo (uzf, &finfo, fname, 1024, NULL, 0, NULL, 0);

       char *buff = (char *) malloc (finfo.uncompressed_size);
       unzOpenCurrentFile (uzf);
       unzReadCurrentFile (uzf, buff, finfo.uncompressed_size);
       unzCloseCurrentFile (uzf);

       lxString dname = out_dirname;
       dname += dirname (fname);

       if (dname.length () > 0)
        {
         lxCreateDir (dname);
        }

       lxString name = out_dirname;
       name += fname;

       FILE * fout = fopen (name.c_str (), "w");
       if (fout)
        {
         fwrite (buff, finfo.uncompressed_size, 1, fout);
         fclose (fout);
        }
       free (buff);
      }
     while (unzGoToNextFile (uzf) == UNZ_OK);
    }

   unzClose (uzf);
  }

 return 0;
}

bool
lxZipDir(const lxString &in_dirname, const lxString &out_filename)
{
 lxStringList paths = lxListDirRec (in_dirname);

 lxString dname = basename (in_dirname.substr (0, in_dirname.length () - 1));

 if (paths.GetLinesCount () == 0)
  {
   return 1;
  }


 zipFile zf = zipOpen (out_filename.c_str (), APPEND_STATUS_CREATE);
 if (zf == NULL)
  {
   return 1;
  }

 bool _return = true;


 for (size_t i = 0; i < paths.GetLinesCount (); i++)
  {
   FILE * file = fopen (paths.GetLine (i).c_str (), "r");
   if (file)
    {
     fseek (file, 0, SEEK_END);
     long size = ftell (file);
     fseek (file, 0, SEEK_SET);

     char * buffer = (char*) malloc (size);
     if (size == 0 || fread (buffer, size, 1, file))
      {
       zip_fileinfo zfi = {0};
       lxString fileName = dname + paths.GetLine (i).substr (in_dirname.length (), paths.GetLine (i).length () - in_dirname.length ());

       if (0 == zipOpenNewFileInZip (zf, fileName.c_str (), &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
        {
         if (zipWriteInFileInZip (zf, size == 0 ? "" : buffer, size))
          _return = false;

         if (zipCloseFileInZip (zf))
          _return = false;

         fclose (file);
         free (buffer);
         continue;
        }
      }
     fclose (file);
    }
   _return = false;
  }

 if (zipClose (zf, NULL))
  return 3;

 if (!_return)
  return 4;
 return 0;

}

bool
lxRemoveFile(const char * fname)
{
 return remove (fname);
}

bool
lxRenameFile(lxString oldfname, lxString newfname)
{
 return rename (oldfname.c_str (), newfname.c_str ());
}

bool
lxRemoveDir(const char* dirname)
{
 DIR *dp;
 struct dirent *dent;
 struct stat sb;
 char fname[1024];

 dp = opendir (dirname);

 if (dp)
  {
   while ((dent = readdir (dp)) != NULL)
    {
     snprintf (fname, 1024, "%s/%s", dirname, dent->d_name);
     stat (fname, &sb);

     if (S_ISREG (sb.st_mode))
      {
       lxRemoveFile (fname);
      }
     else if (S_ISDIR (sb.st_mode))
      {
       if (!(!strcmp (dent->d_name, ".") || !strcmp (dent->d_name, "..")))
        {
         lxRemoveDir (fname);
        }
      }
    }
   closedir (dp);
   return rmdir (dirname);
  }
 return 0;
}

bool
lxCreateDir(const char * dirname)
{
 DIR *dp;
 dp = opendir (dirname);

 if (dp)
  {
   return closedir (dp);
  }
 else
  {
#ifndef _WIN_
   return mkdir (dirname, S_IWUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH);
#else     
   return mkdir (dirname);
#endif
  }
 return 0;
}

lxStringList
lxListDirRec(const lxString & dirname)
{
 DIR *dp;
 struct dirent *dent;
 struct stat sb;
 char fname[1024];

 lxStringList list;

 list.Clear ();

 dp = opendir (dirname);

 if (dp)
  {
   while ((dent = readdir (dp)) != NULL)
    {
     snprintf (fname, 1024, "%s/%s", dirname.c_str (), dent->d_name);
     stat (fname, &sb);

     if (S_ISREG (sb.st_mode))
      {
       list.AddLine (fname);
      }
     else if (S_ISDIR (sb.st_mode))
      {
       if (!(!strcmp (dent->d_name, ".") || !strcmp (dent->d_name, "..")))
        {
         lxStringList list2 = lxListDirRec (fname);
         for (unsigned int i = 0; i < list2.GetLinesCount (); i++)
          {
           list.AddLine (list2.GetLine (i));
          }
        }
      }
    }
   closedir (dp);
  }
 return list;

}

lxString
lxGetUserDataDir(lxString appname)
{
 return lxString ("/home/") + getlogin () + "/." + appname;
}

lxString
lxGetTempDir(lxString appname)
{
 return "/tmp/";
}

lxString
lxGetExecutablePath(lxString appname)
{
 char buff[1024];	
 int size = readlink("/proc/self/exe",buff,1023);
 if(size == -1)
 {
   return "";
 }
 buff[size]=0;
 return buff;
}



// Useful functions_______________________________________________________

void
mprint(lxString message)
{
 fprintf (stdout, "%s", message.c_str ());
};

void
eprint(lxString error)
{
 fprintf (stderr, "%s", error.c_str ());
};

XColor
ColorByRGB(unsigned short r, unsigned short g, unsigned short b)
{

 return 0;
};

XColor
ColorByName(lxString name)
{
 return 0;
};


lxBitmap *
lxGetBitmapRotated(lxImage *image, CWindow * win, int orientation)
{
 return new lxBitmap (image, win, orientation);
}



unsigned int 
lxGetDisplayWidth(int disp)
{
  return 640;
}

unsigned int 
lxGetDisplayHeight(int disp)
{
  return 480;
}



lxMutex::lxMutex()
{
 Mutex = (void *) new pthread_mutex_t;
 pthread_mutex_init ((pthread_mutex_t*) Mutex, NULL);
}

lxMutex::~lxMutex()
{
 delete (pthread_mutex_t*) Mutex;
}

void *
lxMutex::GetMutex(void)
{
 return Mutex;
}

int
lxMutex::Lock(void)
{
 return pthread_mutex_lock ((pthread_mutex_t*) Mutex);
}

int
lxMutex::Unlock(void)
{
 return pthread_mutex_unlock ((pthread_mutex_t*) Mutex);
}

lxCondition::lxCondition(lxMutex & mutex)
{
 Mutex = mutex.GetMutex ();
 Cond = (void *) new pthread_cond_t;
 pthread_cond_init ((pthread_cond_t *) Cond, NULL);
}

lxCondition::~lxCondition()
{
 delete (pthread_cond_t*) Cond;
}

void
lxCondition::Signal(void)
{
 pthread_cond_signal ((pthread_cond_t *) Cond);
}

void
lxCondition::Wait(void)
{
 pthread_cond_wait ((pthread_cond_t *) Cond, (pthread_mutex_t*) Mutex);
}


lxString
lxGetLocalFile(lxString file)
{

#ifndef __WXMSW__
 if (file.Contains ("http"))
  {
   lxString appname = lowercase (basename(Application->Aargv[0]));

   lxString name = file.substr (file.find (".com/") + 4, file.length ());

   lxString local;

   local.Printf ("%s/%s_local/%s", (const char *) lxGetTempDir(appname).c_str (),
                 (const char *) appname.c_str (),
                 (const char *) name.c_str ());

   if (lxFileExists (local))
    {
     return local;
    }

   lxCreateDir (dirname (local));

   lxString cmd = "cd \"" + dirname (local) + "\"; wget --inet4-only \"" + file + "\"";

   system ((const char *) cmd.c_str ());

   return local;
  }
#endif

 //local file
 return file;
}


