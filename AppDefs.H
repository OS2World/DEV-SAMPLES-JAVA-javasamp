
/* AppDefs.H	    Created:	Oct-01-1996  Revised:			*/

/* Module Definition Header						*/

/* Copyright ¸ 1995  Lead architect -- Prominare Inc.					*/



/************************************************************************/
/************************************************************************/
/*	Global Variable Definitions 					*/
/************************************************************************/
/************************************************************************/

extern FONTMETRICS fm;             /* Font Metrics Info                 */
extern HSWITCH     hSwitch;        /* Task List Entry Handle            */
extern HAB         hAB;            /* Program Anchor Block Handle       */

extern HMQ  hmqJava;               /* Program Message Queue Handle	*/
extern HWND hwndJava;              /* Client Window Handle		*/
extern HWND hwndJavaFrame;         /* Frame Window Handle		*/
extern HWND hmenuJava;             /* Menu Handle			*/


/************************************************************************/
/************************************************************************/
/*	Function Prototype Definitions 					*/
/************************************************************************/
/************************************************************************/

VOID    InitApp(HWND hwndFrame, HWND hwndClient, PSZ pszWindowListTitle);
HWND    CreateStdWindow(HWND hwndParent, ULONG flStyle, ULONG flCreateFlags,
                        PSZ pszClientClass, PSZ pszTitle, ULONG styleClient,
                        HMODULE hmod, ULONG idResources, PHWND phwndClient,
                        LONG x, LONG y, LONG cx, LONG cy);
MRESULT PDSKeyProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);
VOID    PDSGetTemplate(HWND hWnd, ULONG id);

MRESULT EXPENTRY JavaPMSampleWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);

