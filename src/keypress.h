/**
 *       @file  myf.h
 *      @brief  Header file for keypress
 *
 * This header files contains common declations, global variables
 * and possibily it can includean extra header files with the prototypes.
 *
 *     @Referencias: http://michael.dipperstein.com/keypress.html
 * 
 *
 *     @author  António Almeida, almeid@ua.pt
 *     @nºmec   64960
 *
 *   @internal
 *     Disciplina PARI
 *     University of Aveiro
 *
 * =========================================================================*/

//=== Inclusdes ============================================================
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

char *keypress(unsigned char echo, int n);