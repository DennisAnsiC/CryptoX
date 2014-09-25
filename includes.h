#pragma comment(lib, "Shlwapi.lib")

/* Definições */
#define CRYPTOX_ERROR			1
#define CRYPTOX_ERROR_SUCCESS	0

#define True					0
#define False					1

#define nil						NULL

/* Windows headers */
#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <string.h>
#include <libtext.h>

void dbg(const char * format, ...);

/**
 * Ofuscação string.
 *   0 = G
 *   1 = z
 *   2 = s
 *   3 = d
 *   4 = P
 *   5 = f
 *   6 = U
 *   7 = c
 *   8 = k
 *   9 = j
 *   D = Q
 *   M = J
 *   R = H
 *   
 * Ofuscação chave.
 *   0 = ;
 *   1 = !
 *   2 = )
 *   3 = #
 *   4 = (
 *   5 = @
 *   6 = *
 *   7 = $
 *   8 = &
 *   9 = %
 */
