#pragma	title("Java - PM Sample  --  Version 1.0  --  (SampWnd.C)")
#pragma	subtitle("   Module Purpose - Interface Definitions")

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>

#include "appdefs.h"
#include "java.h"

#include "jempower.h"

/* This	module contains	routine	used to	handle the main	client window.	*/

/* Filename:   SampWnd.C						*/

/*  Version:   1.0							*/
/*  Created:   1996-10-10						*/
/*  Revised:   1996-10-10						*/

/* Routines:   MRESULT EXPENTRY	JavaPMSampleWndProc(HWND hWnd,		*/
/*						    ULONG msg,		*/
/*						    MPARAM mp1,		*/
/*						    MPARAM mp2);	*/


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

/* --- Module Data Definitions ----------------------------------------	*/

static JEAPPLETHND hApplet = 0;	   /* Applet Handle			*/

#pragma	subtitle("   Client Window - Client Window Procedure")
#pragma	page( )

/* --- JavaPMSampleWndProc ----------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages sent to the	*/
/*     applications client window.					*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Window Handle					*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     JavaPMSampleWndProc = Message Handling Result			*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY JavaPMSampleWndProc(HWND hWnd,	ULONG msg, MPARAM mp1, MPARAM mp2)

{
PCREATESTRUCT pcrst;		   /* Creation Structure Pointer	*/
RECTL rcl;			   /* Window Rectangle			*/
HPS   hPS;			   /* Presentation Space Handle		*/
CHAR  *argv[2];

switch ( msg )
   {

/************************************************************************/
/* Window being	created, perform window	initialization			*/
/************************************************************************/

   case	WM_CREATE :
       pcrst = (PCREATESTRUCT)PVOIDFROMMP(mp2);
       argv[0] = "lbl=This is the next best thing to sliced bread! Toast, toast, toast, butter, jam, toast, marmite, toast.";
       argv[1] = "speed=4";
       jeAppletInit(&hApplet, 1, (JENATIVEWND)hWnd, "file:", "Blink.class", pcrst->cx, pcrst->cy, 2, (const CHAR**)argv);
       WinSetWindowPos((HWND)jeHWNDFromHandle(hApplet),	HWND_TOP, 0L, 0L, 0L, 0L, SWP_MOVE | SWP_SHOW);
       break;

/************************************************************************/
/* Window being	sized							*/
/************************************************************************/

   case	WM_SIZE	:
       jeAppletResize(hApplet, (LONG)SHORT1FROMMP(mp2),	(LONG)SHORT2FROMMP(mp2));
       break;

/************************************************************************/
/* Process menu	and button selections					*/
/************************************************************************/

   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	IDM_START :
	       if ( hApplet )
		   jeAppletStart(hApplet);
	       break;

	   case	IDM_STOP :
	       if ( hApplet )
		   jeAppletStop(hApplet);
	       break;

	   case	IDM_HIDE :
	       jeConsoleShow(FALSE);
	       break;

	   case	IDM_SHOW :
	       jeConsoleShow(TRUE);
	       break;
	   }
       break;

/************************************************************************/
/* Erase window	background						*/
/************************************************************************/

   case	WM_ERASEBACKGROUND :
       WinQueryWindowRect(hWnd,	&rcl);
       WinFillRect((HPS)LONGFROMMP(mp1), &rcl, SYSCLR_WINDOW);
       break;

/************************************************************************/
/* Perform menu	initialization						*/
/************************************************************************/

   case	WM_INITMENU :
       switch (	SHORT1FROMMP(mp1) )
	   {
	   case	IDM_CONSOLE :
		break;

	   case	IDM_APPLET :
		break;

	   }
       break;

/************************************************************************/
/* Paint client	window							*/
/************************************************************************/

   case	WM_PAINT :
       WinFillRect(hPS = WinBeginPaint(hWnd, (HPS)NULL,	&rcl),
		   &rcl, SYSCLR_WINDOW);
       WinEndPaint(hPS);
       break;

/************************************************************************/
/* Window being	destroyed, perform clean-up operations			*/
/************************************************************************/

   case	WM_DESTROY :
       if ( hApplet )
	   jeAppletDestroy(hApplet);
       break;
			/* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
