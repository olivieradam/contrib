/*
**	GadTools layout toolkit
**
**	Copyright � 1993-1998 by Olaf `Olsen' Barthel
**		Freely distributable.
**
**	:ts=4
*/

#ifndef _GTLAYOUT_GLOBAL_H
#include "gtlayout_global.h"
#endif

/*****************************************************************************/

#include <stdarg.h>

/*****************************************************************************/

#include "Assert.h"

/*****************************************************************************/

#ifdef __AROS__
AROS_UFH2S(void, cpy_func,
    AROS_UFHA(UBYTE, chr, D0),
    AROS_UFHA(STRPTR *, strPtrPtr, A3))
{
    AROS_USERFUNC_INIT
    
    *(*strPtrPtr)++ = chr;
    
    AROS_USERFUNC_EXIT
}
#endif

VOID
SPrintf(STRPTR buffer, STRPTR formatString,...)
{
#ifdef __AROS__
	STRPTR buffer_ptr = buffer;
#endif
	va_list varArgs;

	va_start(varArgs,formatString);
#ifdef __AROS__
	VNewRawDoFmt(formatString,(VOID_FUNC)cpy_func,&buffer_ptr,varArgs);
#else
	RawDoFmt(formatString,varArgs,(VOID (*)())"\x16\xC0\x4E\x75",buffer);
#endif
	va_end(varArgs);
}
