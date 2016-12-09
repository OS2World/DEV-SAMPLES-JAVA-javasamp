#pragma	title("Java - PM Sample  --  Version 1.0  --  (AppDefs.C)")
#pragma	subtitle("   Module Purpose - Interface Definitions")

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>

#include "appdefs.h"
#include "java.h"

/* This	module contains	routine	used to	define global application	*/
/* variables.								*/

/* Filename:   AppDefs.C						*/

/*  Version:   1.0							*/
/*  Created:   1996-10-10						*/
/*  Revised:   1996-10-10						*/

/* Routines:   None							*/


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

FONTMETRICS fm;			   /* Font Metrics Info			*/
HAB	    hAB;		   /* Program Anchor Block Handle	*/
HSWITCH	    hSwitch;		   /* Task List	Entry Handle		*/

HMQ  hmqJava;			   /* Program Message Queue Handle	*/
HWND hwndJava;			   /* Client Window Handle		*/
HWND hwndJavaFrame;		   /* Frame Window Handle		*/
HWND hmenuJava;			   /* Menu Handle			*/

