
#pragma comment(lib, "Shlwapi.lib")

/* Definições */
#define CRYPTOX_ERROR              1
#define CRYPTOX_ERROR_SUCCESS      0

#define True                       0
#define False                      1

#define nil                        NULL

/* Windows headers */
#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <string.h>

void dbg(const char * format, ...);
