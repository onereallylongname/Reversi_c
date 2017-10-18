/**
 *       @file  myf.h
 *      @brief  Header file for myf project
 *
 * This header files contains common declations, global variables
 * and possibily it can includean extra header files with the prototypes.
 *
 *     @Referencias: 
 *
 *     @author  António Almeida, almeid@ua.pt
 *     @nºmec   64960
 *
 *   @internal
 *     Disciplina PARI
 *     University of Aveiro
 *
 * ===========================================================================*/

#ifndef _MYF_H_
#define _MYF_H_

//=== Debug module ===========================================================*/
#define On 1
#define Off 0
#define dbg1 if(Debug1)
#define dbg0 if(Debug0)

//=== Structs ================================================================*/
typedef struct {
        char T[8][8];       // Array bidimensional [8][8] com o estado das células
		int terminado;      // inteiro que indica se o jogo está terminado (3 se sim , 0 se não )
        int jogaNum;        // numero da jogada actual
       /* int regJogo[80];    // registo de todas as jogadas*/
        int tipe;           // 1 homem vs pc, 2 homem vs homem (ou 3 para pc vs pc só alterável no save file)
        int saven;          // numero do save 
        int score[2];       // pontos de cada jogador
        int vez;            // inteiro que designa quem é a vez do próximo a jogar (1-jogador1, 2-jogador2)
        int pcrnd;          // só alterável no save file - jogadas random (1) ou não (2) no pc ()
        } othello;
/*=== Define =================================================================*/
#define CHIN 3 //nº caracteres para key press
#define PL2 'O'
#define PL1 'X'
//=== Inclusdes ==============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
/*my files*/
#include "keypress.h"
#include "pcolor.h"
#include "prototypes.h"


#endif
