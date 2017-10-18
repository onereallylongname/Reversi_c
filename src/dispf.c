/**
 *       @file  dispf.c
 *      @brief  Display functions
 *
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
 * =========================================================================*/
/*=== Includes ===============================================================*/
#include "myf.h"
/*=== Debug module ===========================================================*/
#define Debug1 Off
#define Debug0 On
/*============================================================================*/

/**
 * @Auxiliary_Functions -> Funções de display
**/

/**
 * @brief  Faz o print do menu de controlos
 * @param  void
 * @return void
 */
void disp_controls_(void)
{
	printf("Comandos de jogo: \n >a1 to h8  = cell number (jogada válida); \n >z(enter) or Z(enter) = passar a vez; \n >s(número = 0-9) or S(número = 0-9) = grava jogo no ficheiro (de 0 até 9); \n");
	printf(" >l(número 0-9) or L(número 0-9)  = load do ficherio (de 0 até 9); \n >q(enter) or Q(enter)  = sai do jogo; \n \n Press any key to return...");
	keypress(0,1);
}

/**
 * @brief  Faz o print do menu e mostra qual a opção selecionada
 * @param  int pos - opção selecionada , int m - menu a mostrar (1 ou 2)
 * @return void
 */
 void print_menu_(int pos,int m, int npl)
 {
 	char ast[5];
 	char *mop1[] = {"1 Player ","2 Player ","Controls ","Rules    ","Quit     "};
 	char *mop2[] = {"New Game ","Load Game","Return   ","Quit     " };
 	int i, k, kk, aux;
 	kk = ((55 - 9 - 4)/2);
 	for(k = 0; k < (6-m); k++)
 	{
 		aux = (k==pos);
 		ast[k] = 32 * (!aux) + 42 * (aux);
 	}
 	switch(m)
 	{
 		/*Imprimir menu 1 na pagina actual*/
 		case 1:
	 		make_header_();
	 		display_screen_str_("", 2,2);
	 		for(i = 0; i < 6-m; i++)
	 		{
	 		    display_first_space_(kk-1, 2);
	 			printf("%c%s",ast[i],mop1[i]);
	 			display_last_space_(kk, 2);	
	 		}
	 		display_screen_str_("", 2,2);
	 		break;
 		case 2:
 			make_header_();
 			display_first_space_(20, 2);
	 		printf(">%1d Player<",npl);
	 		display_last_space_(21, 2);
	 		display_screen_1_(2);
	 		display_screen_str_("", 2,2);
	 		for(i = 0; i < 6-m; i++)
	 		{
	 		    display_first_space_(kk-1, 2);
	 			printf("%c%s",ast[i],mop2[i]);
	 			display_last_space_(kk, 2);	
	 		}
	 		display_screen_str_("", 2,2);
	 		break;
 	}
 }
 
/**
 * @brief  Faz o print do menu load e mostra qual o save selecionado - menu especial
 * @param  int pos - opção selecionada , int m - menu a mostrar (1 ou 2)
 * @return void
 */
 int print_menu_load_(int pos,int m, int * saves)
 {
 	m++;
 	char ast[m];
 	int i, k, kk, aux;
 	kk = ((55 - 7 - 4)/2);
 	for(k = 0; k < (m); k++)
 	{
 		aux = (k==pos);
 		ast[k] = 32 * (!aux) + 42 * (aux);
 	}
	make_header_();
	display_first_space_(19, 2);
	printf(" >Load Game<");
	display_last_space_(20, 2);
	display_screen_1_(2);
	display_screen_str_("  ", 2,2);
	if(m > 1)
	{
		for(i = 0; i < m-1; i++)
		{
			display_first_space_(kk-1, 2);
			printf("%cSave %d ",ast[i],saves[i]);
			display_last_space_(kk, 2);	
		}
	}
	else if(m == 1)
	{
		display_first_space_(kk, 2);
		printf(" Empty!");
		display_last_space_(kk+1, 2);	
	}	
	display_screen_str_("  ", 2,2);
	display_first_space_(kk-1, 2);
	printf("%cReturn ",ast[i]);
	display_last_space_(kk, 2);	
	display_screen_str_("  ", 2,2);
 	return 0;
 }
 
/**
 * @brief  Faz o display da borda do tabuleiro
 * @param  void
 * @return void
*/
void print_board_border_(void)
{
	display_first_space_(8, 2);
	textcolor2(6);
	printf(" • • • • • • • • • • • • • • • • • ");
	display_last_space_(8, 2);
}

/**
 * @brief  Faz o display de uma celula
 * @param  void
 * @return void
*/
void print_board_cell_(char cell, int cellc)
{
	textcolor2(cellc);
	printf(" %c ",cell);
	print_c_("•", 6);
}

/**
 * @brief  Faz o display dos dados do load
 * @param  void
 * @return void
*/
void print_load_resolt_(othello * jg)
{
	printf("\n          _Jogo a carregar_\n"); usleep(1e5);
	printf("          _save numero :  %d\n",jg->saven); usleep(1e5);
	if(jg->tipe == 1)
	{
		printf("          _Pc vs Player \n"); usleep(1e5);
	}
	else
	{
		printf("          _Player vs Player \n"); usleep(1e5);
		printf("          _vez de jogar : Player %d\n",jg->vez); usleep(1e5);
	}
	printf("          _jogada numero :  %d\n",jg->jogaNum); usleep(1e5);
}

/**
 * @brief  Faz o display dos dados do save
 * @param  void
 * @return void
*/
void print_save_resolt_(othello * jg)
{
	printf("\n          _Jogo a guardar_\n"); usleep(1e5);
	printf("          _save numero :  %d\n",jg->saven); usleep(1e5);
	if(jg->tipe == 1)
	{
		printf("          _Pc vs Player \n"); usleep(1e5);
	}
	else
	{
		printf("          _Player vs Player \n"); usleep(1e5);
		printf("          _vez de jogar : Player %d\n",jg->vez); usleep(1e5);
	}
	printf("          _jogada numero :  %d\n",jg->jogaNum); usleep(1e5);
}

/**
 * @brief  Faz o topo da pagina de game over
 * @param  void 
 * @return void
 */
void make_game_ovre_(void)
{
	limparshell_();
	display_screen_1_(2);
	display_screen_str_("Fim do jogo! ",9,2);
	display_screen_1_(2);
}
/*============================================================================*/

/**
 * @Auxiliary_Functions -> Funções internas display de myf.c
**/

/**
 * @brief  Faz o topo
 * @param  void 
 * @return void
 */
void make_header_(void)
{
	limparshell_();
	display_screen_1_(2);
	display_screen_str_("OTHELLO ",9,2);
	display_screen_1_(2);
}

/**
 * @brief  Faz o base
 * @param  void 
 * @return void
 */
 
void make_base_(void)
{
	display_screen_1_(2);
	display_screen_1_(4);
}
/**
 * @brief  Limpa a chell e mantem o relogio no topo do ecrã
 * @param  void 
 * @return void
 */
 void limparshell_(void)
 {
 	fflush(stdout);
 	system("clear");
 }
 
 /**
 * @brief  Imprime uma string centrada com a cor escolhida 
 * @param  char * tit - string, int n - cor
 * @return void
 */
void display_screen_str_(char * tit, int n, int n1)
{
	int kk, k = strlen(tit);
	if((k/50) <= 1)
	{
		kk = ((55 - k - 3)/2);
		display_first_space_(kk-1, n1);
		textcolor2(n);
		printf("%s",tit);
		display_last_space_(kk, n1);
	}
	else
	{
	printf("too long,%d -  %d \n",k,(k/50)+1);
	}
}

/**
 * @brief  Cria os primeiros espaços para centrar uma string
 * @param  int kk -  = (largura da pagina - comp string - 3)/2 , int n - cor
 * @return void
 */
void display_first_space_(int kk, int n)
{
	int i;
	textcolor2(n);
	printf("<>");
	for(i = 0; i < kk; i++)
		printf(" ");
	textcolor2(9);
}	
/**
 * @brief  Cria os primeiros espaços para centrar uma string
 * @param  int kk -  = (largura da pagina - comp string - 3)/2 , int n - cor
 * @return void
 */
void display_last_space_(int kk, int n)
{
	int i;
	for(i = 0; i < kk; i++)
		printf(" ");
	textcolor2(n);
	printf("<>");
	printf("\n");
	textcolor2(9);
}

/**
 * @brief  Imprime o topo do ecra 
 * @param  void 
 * @return void
 */
void display_screen_1_(int color)
{
	int i;
	for(i = 0; i < 11; i++)
	{
		textcolor2(color);
		printf("<>:<>");
	}
	printf("\n");
	textcolor2(9);
}

/**
 * @brief  Imprime com a cor n
 * @param  int n 
 * @return void
 */
 void print_c_(char * s, int n)
{
	textcolor2(n);
	printf("%s",s);
	textcolor2(9);
}