#pragma	title("Java - PM Sample  --  Version 1.0  --  (Support.C)")
#pragma	subtitle("   Support Routines - Interface Definitions")

#define	INCL_DOS		   /* Include OS/2 PM DOS Interface	*/
#define	INCL_GPI		   /* Include OS/2 PM GPI Interface	*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>
#include <string.h>

#include "appdefs.h"
#include "java.h"

/* This	module contains	routine	used to	provide	various	support		*/
/* routines.								*/

/* Filename:   Support.C						*/

/*  Version:   1.0							*/
/*  Created:   1996-10-10						*/
/*  Revised:   1996-10-10						*/

/* Routines:   VOID InitApp(HWND hwndFrame, HWND hwndClient,		*/
/*			    PSZ	pszWindowListTitle);			*/
/*	       HWND CreateStdWindow(HWND hwndParent, ULONG flStyle,	*/
/*				    ULONG flCreateFlags,		*/
/*				    PSZ	pszClientClass,	PSZ pszTitle,	*/
/*				    ULONG styleClient, HMODULE hmod,	*/
/*				    ULONG idResources,			*/
/*				    PHWND phwndClient,			*/
/*				    LONG x, LONG y, LONG cx, LONG cy);	*/


/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DISCLAIMER OF WARRANTIES:						*/
/* -------------------------						*/
/* The following [enclosed] code is sample code	created	by IBM		*/
/* Corporation and Prominare Inc.  This	sample code is not part	of any	*/
/* standard IBM	product	and is provided	to you solely for the purpose	*/
/* of assisting	you in the development of your applications.  The code	*/
/* is provided "AS IS",	without	warranty of any	kind.  Neither IBM nor	*/
/* Prominare shall be liable for any damages arising out of your	*/
/* use of the sample code, even	if they	have been advised of the	*/
/* possibility of such damages.						*/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*		       D I S C L A I M E R				*/
/* This	code is	provided on an as is basis with	no implied support.	*/
/* It should be	considered freeware that cannot	be rebundled as		*/
/* part	of a larger "*ware" offering without our consent.		*/
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Copyright ¸ International Business Machines Corp., 1996.		*/
/* Copyright ¸ 1996  Prominare Inc.  All Rights	Reserved.		*/

/* --------------------------------------------------------------------	*/


#pragma	subtitle("   Program Initialization -   Program Initialization Function")
#pragma	page( )

/* --- InitApp ----------------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	perform	basic application		*/
/*     initialization to support the owner draw	list boxes and to set	*/
/*     the window list title if	provided.				*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND hwndFrame;	  = Application	Frame Window Handle		*/
/*     HWND hwndClient;	  = Application	Client Window Handle		*/
/*     PSZ  pszTaskTitle; = Window List	Title				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

VOID InitApp(HWND hwndFrame, HWND hwndClient, PSZ pszWindowListTitle)

{
HPS	hPS;			   /* Presentation Space Handle		*/
SWCNTRL	swCtl;			   /* Task Switch Control Structure	*/

		       /* Get a	temporary presentation space so	that	*/
		       /* the system's font metrics can be found and    */
		       /* the proper sizing of owner draw list boxes	*/
		       /* can be performed properly			*/

if ( (hPS = WinGetPS(hwndClient)) != (HPS)NULL )
   {
   GpiQueryFontMetrics(hPS, sizeof(FONTMETRICS), &fm);

		       /* Release the temporary	presentation space	*/
   WinReleasePS(hPS);
   }

if ( pszWindowListTitle	)
   {
		       /* Fill Switch Entry structure with required	*/
		       /* values before	adding program name to Task	*/
		       /* Manager switch list				*/

   swCtl.hwnd	       = hwndFrame;
   swCtl.hwndIcon      = (HWND)NULL;
   swCtl.hprog	       = (HPROGRAM)NULL;
   swCtl.idProcess     =
   swCtl.idSession     = 0;
   swCtl.uchVisibility = SWL_VISIBLE;
   swCtl.fbJump	       = SWL_JUMPABLE;
   strcpy(swCtl.szSwtitle, pszWindowListTitle);

   hSwitch = WinAddSwitchEntry(&swCtl);
   }
}
#pragma	subtitle("      Program Initialization - Window Creation Function")
#pragma	page( )

/* --- CreateStdWindow --------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	create a standard window using		*/
/*     WinCreateStdWindow and to place the window in the location	*/
/*     and size	specified if the shell position	style has not been	*/
/*     specified.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND    hwndParent;     = Parent	Window Handle			*/
/*     ULONG   flStyle;	       = Window	Style				*/
/*     ULONG   flCreateFlags;  = Frame Creation	Flags			*/
/*     PSZ     pszClientClass; = Client	Area Class			*/
/*     PSZ     pszTitle;       = Window	Title				*/
/*     HMODULE hmod;	       = Resources Module Handle		*/
/*     ULONG   idResources;    = Resource ID				*/
/*     PHWND   phwndClient;    = Client	Window Handle Pointer		*/
/*     LONG    x;	       = x Co-ordinate				*/
/*     LONG    y;	       = y Co-ordinate				*/
/*     LONG    cx;	       = Window	Width				*/
/*     LONG    cy;	       = Window	Height				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     CreateStdWindow = NULL :	Error Occurred,	No Window Created	*/
/*		       = > 0  :	Frame Window Handle			*/
/*									*/
/* --------------------------------------------------------------------	*/

HWND CreateStdWindow(HWND hwndParent, ULONG flStyle, ULONG flCreateFlags, PSZ pszClientClass, PSZ pszTitle, ULONG styleClient,
		     HMODULE hmod, ULONG idResources, PHWND phwndClient, LONG x, LONG y, LONG cx, LONG cy)

{
HWND   hwndFrame;		   /* Frame Window Handle		*/
POINTL aptl[2];			   /* Point Translation	Array		*/

if ( !(hwndFrame = WinCreateStdWindow(hwndParent, flStyle, &flCreateFlags, pszClientClass, pszTitle, styleClient,
				      hmod, idResources, phwndClient)) )
   return((HWND)NULL);

if ( !(flCreateFlags & FCF_SHELLPOSITION) )
   {
   aptl[0].x = x;
   aptl[0].y = y;
   aptl[1].x = cx;
   aptl[1].y = cy;
   WinMapDlgPoints(HWND_DESKTOP, aptl, 2UL, TRUE);
   WinSetWindowPos(hwndFrame, HWND_TOP,	aptl[0].x, aptl[0].y, aptl[1].x, aptl[1].y, SWP_ACTIVATE | SWP_SIZE | SWP_MOVE |
		   (ULONG)((flStyle & WS_VISIBLE) ? SWP_SHOW : 0UL));
   }
		       /* Return back the window handle			*/
return(hwndFrame);
}
