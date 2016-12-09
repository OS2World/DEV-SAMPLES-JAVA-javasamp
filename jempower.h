/******************************************************************************
 *  IBM JEmpower                                                              *
 *                                                                            *
 *  (C) Copyright IBM Corp. 1996                                              *
 *  All Rights Reserved.                                                      *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 *  Module Name: JEmppower.h - JEmpower functions                             *
 *                                                                            *
 *****************************************************************************/

#ifndef _JEMPOWER_H_
#define _JEMPOWER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __OS2__
#define JELINKAGE _System
#ifdef  JEMPOWER_DYNAMIC
#define JE_HAS_ORDINALS
#endif
#elif defined(_WIN32) || defined(WIN32)
#define JELINKAGE __cdecl
#ifdef  JEMPOWER_DYNAMIC
#define JE_HAS_ORDINALS
#endif
#else
#define JELINKAGE
#endif

typedef unsigned long JEAPPLETHND;
typedef unsigned long JECONTEXTID;
typedef int           JERESULT;

/* JENATIVEWND is the type used for windows in the native operating system.
 * For example, it is an HWND on WIN32 and OS2, an X Window under UNIX, etc.
 * To avoid having to load os2.h, windows.h, etc in this header file,
 * we are declaring as an opaque pointer to a struct. 
 * When using the functions that take an JENATIVEWND
 * (jeAppletInit and jeHWNDFromHandle), explicitly cast to and from HWND,
 * Window, or whatever.
 */
struct rec_jenativewnd;
typedef struct rec_jenativewnd* JENATIVEWND;

/*******************************************************************/

/* 
 * This API can be used statically or dynamically.  
 *
 * For statically, simply link with the JEmpower library and call functions
 * such as jeInitJavaRuntime or jeAppletInit.  
 *
 * For dynamically, load each of the functions using operating system 
 * functions such as GetProcAddress (for windows) and assign variables
 * of the correct type to the results for later use.  For example,
 *    JE_FP_jeAppletInit jeAppletInit;
 *    jeAppletInit = (JE_FP_jeAppletInit)GetProcAddress(lib, "jeAppletInit");
 *    ...
 *    jeAppletInit(usual arguments);
 * To use this library dynamically, 
 * #define JEMPOWER_DYNAMIC before loading jempower.h
 * Notice that the call site of jeAppletInit looks identical regardless
 * of whether JEMPOWER is used statically or dynamically
 */
#ifndef JEMPOWER_DYNAMIC
#define JE_FN_DECL(rettype, fnName, fnTypeName) \
   rettype JELINKAGE fnName
#else
#define JE_FN_DECL(rettype, fnName, fnTypeName) \
   typedef rettype (JELINKAGE fnTypeName)
#endif

JE_FN_DECL(void, jeVersion, JE_FP_jeVersion)
   (int *majorVersion, int *minorVersion);

JE_FN_DECL(JERESULT, jeInitJavaRuntime, JE_FP_jeInitJavaRuntime)
   (void);
JE_FN_DECL(JERESULT, jeInitJavaRuntimeEx, JE_FP_jeInitJavaRuntimeEx)
   (int extraArgc, char **extraArgv);

JE_FN_DECL(JERESULT, jeAppletInit, JE_FP_jeAppletInit)
   (JEAPPLETHND *pAppResult,
    JECONTEXTID contextID, JENATIVEWND parent,
    const char *documentURL,
    const char *code, long width, long height,
    int parmCount, const char **parms);

JE_FN_DECL(JERESULT, jeAppletStart, JE_FP_jeAppletStart)
   (JEAPPLETHND applet);
JE_FN_DECL(JERESULT, jeAppletStop, JE_FP_jeAppletStop)
   (JEAPPLETHND applet);
JE_FN_DECL(JERESULT, jeAppletDestroy, JE_FP_jeAppletDestroy)
   (JEAPPLETHND applet);
JE_FN_DECL(JERESULT, jeAppletToolBarShow, JE_FP_jeAppletToolBarShow)
   (JEAPPLETHND applet, int show);
JE_FN_DECL(JERESULT, jeAppletInformationShow, JE_FP_jeAppletInformationShow)
   (JEAPPLETHND applet, int show);
JE_FN_DECL(JERESULT, jeAppletResize, JE_FP_jeAppletResize)
   (JEAPPLETHND applet, long width, long height);

JE_FN_DECL(JENATIVEWND, jeHWNDFromHandle, JE_FP_jeHWNDFromHandle)
   (JEAPPLETHND applet);

JE_FN_DECL(JERESULT, jeAppletsIconify, JE_FP_jeAppletsIconify)
   (JECONTEXTID contextID);
JE_FN_DECL(JERESULT, jeAppletsUniconify, JE_FP_jeAppletsUniconify)
   (JECONTEXTID contextID);
JE_FN_DECL(JERESULT, jeAppletsDestroy, JE_FP_jeAppletsDestroy)
   (JECONTEXTID contextID);   

JE_FN_DECL(JERESULT, jeConsoleShow, JE_FP_jeConsoleShow)
   (int show);

JE_FN_DECL(JERESULT, jeGetProperty, JE_FP_jeGetProperty)
   (const char *key, char *value, 
    int valueLength, int *trueLength);
JE_FN_DECL(JERESULT, jeSetProperty, JE_FP_jeSetProperty)
   (const char *key, const char *value);

typedef void (* JELINKAGE jeShowDocumentFnPtr)(JECONTEXTID contextID, 
                                               const char *url,
                                               const char *target);
JE_FN_DECL(JERESULT, jeRegisterShowDocument, JE_FP_jeRegisterShowDocument)
   (jeShowDocumentFnPtr fnPtr);

typedef int (* JELINKAGE jeShowStatusFnPtr)(JECONTEXTID contextID, 
                                            const char *status);
JE_FN_DECL(JERESULT, jeRegisterShowStatus, JE_FP_jeRegisterShowStatus)
   (jeShowStatusFnPtr fnPtr);

typedef int (* JELINKAGE jeShowConsoleFnPtr)(const char *string);
JE_FN_DECL(JERESULT, jeRegisterShowConsole, JE_FP_jeRegisterShowConsole)
   (jeShowConsoleFnPtr fnPtr);

/*******************************************************************/

#ifdef  JEMPOWER_DYNAMIC
/* To make dynamic loading easier.  The names and ordinals for the API */
#define JE_NAM_jeVersion               "jeVersion"
#define JE_NAM_jeInitJavaRuntime       "jeInitJavaRuntime"
#define JE_NAM_jeInitJavaRuntimeEx     "jeInitJavaRuntimeEx"
#define JE_NAM_jeAppletInit            "jeAppletInit"
#define JE_NAM_jeAppletStart           "jeAppletStart"
#define JE_NAM_jeAppletStop            "jeAppletStop"
#define JE_NAM_jeAppletDestroy         "jeAppletDestroy"
#define JE_NAM_jeAppletToolBarShow     "jeAppletToolBarShow"
#define JE_NAM_jeAppletInformationShow "jeAppletInformationShow"
#define JE_NAM_jeAppletResize          "jeAppletResize"
#define JE_NAM_jeAppletsIconify        "jeAppletsIconify"
#define JE_NAM_jeAppletsUniconify      "jeAppletsUniconify"
#define JE_NAM_jeAppletsDestroy        "jeAppletsDestroy"
#define JE_NAM_jeConsoleShow           "jeConsoleShow"
#define JE_NAM_jeGetProperty           "jeGetProperty"   
#define JE_NAM_jeSetProperty           "jeSetProperty"   
#define JE_NAM_jeRegisterShowDocument  "jeRegisterShowDocument"
#define JE_NAM_jeRegisterShowStatus    "jeRegisterShowStatus"
#define JE_NAM_jeRegisterShowConsole   "jeRegisterShowConsole"

#ifdef  JE_HAS_ORDINALS
#define JE_ORD_jeVersion               1000
#define JE_ORD_jeInitJavaRuntime       1001
#define JE_ORD_jeInitJavaRuntimeEx     1002
#define JE_ORD_jeAppletInit            1050
#define JE_ORD_jeAppletStart           1051
#define JE_ORD_jeAppletStop            1052
#define JE_ORD_jeAppletDestroy         1053
#define JE_ORD_jeAppletToolBarShow     1054
#define JE_ORD_jeAppletInformationShow 1055
#define JE_ORD_jeAppletResize          1056
#define JE_ORD_jeAppletsIconify        1100
#define JE_ORD_jeAppletsUniconify      1101
#define JE_ORD_jeAppletsDestroy        1102
#define JE_ORD_jeConsoleShow           1150
#define JE_ORD_jeGetProperty           1200
#define JE_ORD_jeSetProperty           1201
#define JE_ORD_jeRegisterShowDocument  1152
#define JE_ORD_jeRegisterShowStatus    1153
#define JE_ORD_jeRegisterShowConsole   1151
#endif  /* JE_HAS_ORDINALS */
   
#endif  /* JEMPOWER_DYNAMIC */

#ifdef __cplusplus
}
#endif

#endif

