/**
 * ===========================================================================
 *      @file  main.c
 *      @version 1.01
 *      @brief  Ficheiro 'main' para tpc 6: IMPLEMENTAÇÃO DO JOGO OTHELLO (ou REVERSI).
 *
 *	@Referencias: --- 
 *
 *     @author  António Almeida - almeid@ua.pt
 *     @nºmec   64960
 *
 *   @internal
 *     Disciplina PARI
 *     University of Aveiro
 * ===========================================================================*/

/*=== Prototipo da função a usar e Includes ==================================*/
#include "myf.h"
/*=== Function pointers ======================================================*/      
int (* pag[8])(othello *jg) = {pag0_,pag1_,pag2_,pag3_,pag4_,pag5_,pag6_,campo_de_jogo_};     

/*=== Debug module ===========================================================*/
#define Debug1 Off
#define Debug0 Off
/*============================================================================*/
/**
 * @brief  Main
 * @param  void
 * @return 0 
 */
 
int main (int argc, char *argv[])
{
	othello jg0;
	othello * jg = &jg0;
	int go = 0;
	
	system("printf '\e[8;42;56t'");
	
	while(go != 99)
	{
		usleep(1e5);
		go = pag[go](jg);
		dbg1 printf("go -> %d\n",go);
	}
	call_error_(0);
	display_screen_1_(4);
  	return 0;
}	



 
  
  
  
    