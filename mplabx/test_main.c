/* main.c
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */


#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfcrypt/test/test.h>

#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
    #define MICROCHIP_PIC32
    #include <stdio.h>
    #include <stdlib.h>
    #include "PIC32MZ-serial.h"
    #include <xc.h>
    #define SYSTEMConfigPerformance(a) /* void out SYSTEMConfigPerformance(); */
    #define SYS_CLK 200000000
#else
    #define PIC32_STARTER_KIT
    #include <stdio.h>
    #include <stdlib.h>
    #include <p32xxxx.h>
    #define _SUPPRESS_PLIB_WARNING
    #define _DISABLE_OPENADC10_CONFIGPORT_WARNING
    #include <plib.h>
    #include <sys/appio.h>
    #define init_serial(x)  /* void out init_serial() */
    #define SYS_CLK 80000000
#endif

/* func_args from test.h, so don't have to pull in other junk */
typedef struct func_args {
    int    argc;
    char** argv;
    int    return_code;
} func_args;


#if 1
/* enable this if ReadCoreTimer and WriteCoreTimer are missing */
unsigned int ReadCoreTimer(void)
{
    unsigned int timer;
    timer = __builtin_mfc0(9, 0);
    return timer;
}
void WriteCoreTimer(unsigned int t)
{
    /* do nothing here */
    (void)t;
}
#endif

/*
 * Main driver for WolfCrypt tests.
 */
int main(int argc, char** argv)
{
    func_args args;

    SYSTEMConfigPerformance(SYS_CLK);
    DBINIT();

    init_serial(SYS_CLK) ;  /* initialize PIC32MZ serial I/O */

    printf("WolfCrypt Test:\n");

    args.argc = argc;
    args.argv = argv;

    wolfcrypt_test(&args);

    if (args.return_code == 0) {
        printf("All tests passed!\n");
    }

    return 0;
}

