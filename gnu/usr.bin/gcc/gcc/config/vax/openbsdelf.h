/* Configuration fragment for a VAX OpenBSD target.
   Copyright (C) 2000, 2002 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Amend common OpenBSD definitions for VAX target.  */

#define TARGET_OS_CPP_BUILTINS()		\
  do						\
    {						\
      OPENBSD_OS_CPP_BUILTINS_ELF();		\
    }						\
  while (0)

/* Layout of source language data types.  */

/* This must agree with <machine/_types.h>  */
#undef SIZE_TYPE
#define SIZE_TYPE "long unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "long int"

#undef INTMAX_TYPE
#define INTMAX_TYPE "long long int"

#undef UINTMAX_TYPE
#define UINTMAX_TYPE "long long unsigned int"

#undef WCHAR_TYPE
#define WCHAR_TYPE "int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

/* No structure field wants to be aligned rounder than this.
   The huge 0x40000000 value should be enough to turn the
   BIGGEST_FIELD_ALIGNMENT logic into a nop.  */
#undef BIGGEST_FIELD_ALIGNMENT
#define BIGGEST_FIELD_ALIGNMENT (TARGET_VAXC_ALIGNMENT ? 8 : 0x40000000)

#undef LINK_SPEC
#ifdef OBSD_NO_DYNAMIC_LIBRARIES
#define LINK_SPEC \
  "%{!nostdlib:%{!r*:%{!e*:-e _start}}} %{assert*}"
#else
#define LINK_SPEC \
  "%{!shared:%{!nostdlib:%{!r*:%{!e*:-e _start}}}} \
   %{shared:-shared} %{R*} \
   %{static:-Bstatic} \
   %{!static:-Bdynamic} \
   %{rdynamic:-export-dynamic} \
   %{assert*} \
   %{!dynamic-linker:-dynamic-linker /usr/libexec/ld.so}"
#endif

/* As an elf system, we need crtbegin/crtend stuff.  */
#undef STARTFILE_SPEC
#ifdef OBSD_NO_DYNAMIC_LIBRARIES
#define STARTFILE_SPEC \
  "%{pg:gcrt0%O%s} %{!pg:%{p:gcrt0%O%s} %{!p:crt0%O%s}} crtbegin%O%s"
#else
#define STARTFILE_SPEC "\
	%{!shared: %{pg:gcrt0%O%s} %{!pg:%{p:gcrt0%O%s} %{!p:crt0%O%s}} \
	crtbegin%O%s} %{shared:crtbeginS%O%s}"
#endif

#undef ENDFILE_SPEC
#ifdef OBSD_NO_DYNAMIC_LIBRARIES
#define ENDFILE_SPEC "crtend%O%s"
#else
#define ENDFILE_SPEC "%{!shared:crtend%O%s} %{shared:crtendS%O%s}"
#endif

/* We use gas, not the UNIX assembler.  */
#undef TARGET_DEFAULT
#define TARGET_DEFAULT 0
