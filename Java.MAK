
# MAKE file for Java.MAK

# Revised:  1996-10-01

# Copyright ¸ 1987-1996  Prominare Inc.

C_SW=-G5 -O+ -W3 -C

Java.Exe: AppDefs.Obj Java.Obj Java.Res SampWnd.Obj Support.Obj
 ILink /FREE /EXEPACK:2 /ALIGN:4 /BASE:0x10000 /OUT:Java.Exe AppDefs.Obj Java.Obj SampWnd.Obj Support.Obj JEmpO10.lib Java.Def
 Rc -x2 Java.Res Java.Exe

AppDefs.Obj: AppDefs.C
 Icc $(C_SW) -Fo$*.Obj AppDefs.C

Java.Obj: Java.C
 Icc $(C_SW) -Fo$*.Obj Java.C

Java.Res: Java.Rc
 Rc -r Java.Rc $*.Res

SampWnd.Obj: SampWnd.C
 Icc $(C_SW) -Fo$*.Obj SampWnd.C

Support.Obj: Support.C
 Icc $(C_SW) -Fo$*.Obj Support.C

