/*
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#ifndef _DL_OSINFO_H
#define _DL_OSINFO_H 1

#include <features.h>

#ifdef __UCLIBC_HAS_SSP__
#include <stdint.h>
#include <sys/time.h>

#ifdef IS_IN_libc
#include <ssp-internal.h>
#if 0
#ifndef __SSP_QUICK_CANARY__
#define OPEN __libc_open
#define READ __libc_read
#define CLOSE __libc_close
#endif
#define GETTIMEOFDAY gettimeofday
#endif
#else
#ifdef __SSP__
#error "file must not be compiled with stack protection enabled on it. Use -fno-stack-protector"
#endif
#ifndef __SSP_QUICK_CANARY__
#define OPEN _dl_open
#define READ _dl_read
#define CLOSE _dl_close
#endif
#define GETTIMEOFDAY _dl_gettimeofday
#endif

static __always_inline uintptr_t _dl_setup_stack_chk_guard(void)
{
	uintptr_t ret;
#ifndef __SSP_QUICK_CANARY__
	{
		int fd = OPEN("/dev/urandom", O_RDONLY, 0);
		if (fd >= 0) {
			size_t size = READ(fd, &ret, sizeof(ret));
			CLOSE(fd);
			if (size == (size_t) sizeof(ret))
				return ret;
		}
	}
#endif /* !__SSP_QUICK_CANARY__ */

	/* Start with the "terminator canary". */
	ret = 0xFF0A0D00UL;

	/* Everything failed? Or we are using a weakened model of the 
	 * terminator canary */
	{
		struct timeval tv;
		if (GETTIMEOFDAY(&tv, NULL) != (-1))
			ret ^= tv.tv_usec ^ tv.tv_sec;
	}
	return ret;
}
#endif /* __UCLIBC_HAS_SSP__ */

#endif /* _DL_OSINFO_H */
