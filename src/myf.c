/**
 * ===========================================================================
 *      @file  myf.c
 *      @version 1.00
 *      @brief  Ficheiro de funções para tpc 6. 
 *
 *     @Referencias: ---
 *
 *
 *     @author  António Almeida - almeid@ua.pt
 *     @nºmec   64960
 *
 *   @internal
 *     Disciplina PARI
 *     University of Aveiro
 * ===========================================================================*/

/*=== Includes ===============================================================*/
#include "myf.h"
/*=== Debug module ===========================================================*/
#define Debug1 Off
#define Debug0 Off
/*============================================================================*/

/**
 * @Myf_Functions -> Funções principais de myf.c
**/
     
/**
 * @brief  Pagina 0 - Cria o Menu inicial do jogo
 * @param  othello *jg
 * @return int - next page
 */
int pag0_(othello *jg)
{
	int pos = 0, go = 0, aux;
	do
	{
		aux = pos;
		print_menu_(pos,1,0);
		make_base_();
		pos = get_pos_m_(pos,5);
		if(pos == 99)
		{
			switch(aux)
			{
				case 0:
					go = 1;
					jg->tipe = 1;
					break;
				case 1:
					go = 1;
					jg->tipe = 2;
					break;
				default:
					go = aux;
			}
		}
	}while(!go);
	return go;
}

/**
 * @brief  Pagina 1 - Cria o Menu de inicio de jogo
 * @param  othello *jg
 * @return int - next page
 */
int pag1_(othello *jg)
{
	int pos = 0, go = 0, aux;
	do
	{
		aux = pos;
		print_menu_(pos,2,jg->tipe);
		make_base_();
		pos = get_pos_m_(pos,4);
		if(pos == 99)
		{
			switch(aux)
			{
				case 0:
					go = 8;
					InitGame(jg);
					break;
				case 1:
					go = 6;
					break;
				case 2:
					go = 1;
					break;
				case 3:
					go = 5;
					break;
				default:
					call_error_(2);
					go = 5;
			}
		}
	}while(!go);
	go--;
	return go;
}
  
/**
 * @brief  Pagina 2 - controlos
 * @param  othello *dummy
 * @return int - next page
 */
int pag2_(othello *dummy)
{
	disp_controls_();
	return 0;
}

/**
 * @brief  Pagina 3 - regras
 * @param  othello *dummy
 * @return int - next page
 */
int pag3_(othello *dummy)
{
	
	printf("Regras em - http://elearning.ua.pt/pluginfile.php/278336/mod_resource/content/1/TPCaula6.html");
	printf("\nPress any key to continue...");
	keypress(0,1);
	return 0;
}

/**
 * @brief  Pagina 4 - fim de programa
 * @param  othello *dummy
 * @return int - next page
 */
int pag4_(othello *dummy)
{
	
	printf("\n\n             FIM!\n");
	usleep(1e4);
	return 99;
}

/**
 * @brief  Pagina 5 - load games
 * @param  othello *jp
 * @return int - next page
 */
int pag5_(othello *jg)
{
	int go = LoadGame(jg);
	return go;
}

/**
 * @brief  Pagina 6 - winscreen
 * @param  othello *jp
 * @return int - next page
 */
int pag6_(othello *jg)
{
	char p1[] = "Player 1", p2[] = "Player 2" , pc[] = "Computer";
 	char * p[3];
 	if(jg->tipe == 1)
 	{
 		p[0] = "";
 		p[1] = &p1[0];
 		p[2] = &pc[0];
 		
	}
	else
	{
		p[0] = "";
 		p[1] = &p1[0];
 		p[2] = &p2[0];
	}	
	make_header_();
	make_game_ovre_();
	if(jg->score[1] < jg->score[0])
		printf("          Ganhou %s !!!!!!!!!!!\n          Com %d pontos.",p[1],jg->score[0]);
	else if(jg->score[0] < jg->score[1])
		printf("          Ganhou %s !!!!!!!!!!!\n          Com %d pontos.",p[2],jg->score[1]);
	else if(jg->score[1] == jg->score[0])
		printf("          Empate!");
	keypress(0,1);
	return 0;
}

/**
 * @brief  Pagina 6 - campo de jogo
 * @param  othello *jg
 * @return int - next page
 */
int campo_de_jogo_(othello *jg)
{
 	int go = 0, move, chkm;
 	char p1[] = "Player 1$", p2[] = "Player 2$" , pc[] = "Computer$";
 	char * p[3];
 	if(jg->tipe == 1)
 	{
 		p[0] = "";
 		p[1] = &p1[0];
 		p[2] = &pc[0];
 		
	}
	else
	{
		p[0] = "";
 		p[1] = &p1[0];
 		p[2] = &p2[0];
	}	
 	
 	PrintGameBoard(jg);
 	make_score_(jg);
 	printf("Press any key to continue...");
 	keypress(0,1);
 	do
 	{
	 	possible_moves_(jg);
	 	PrintGameBoard(jg);
	 	printf("<> %s ", p[jg->vez]);
	 	if(jg->tipe == 1)
	 		if(jg->vez == 2)
	 			move = GenerateMove(jg);
	 		else
	 			move = GetPlayerMove();
	 	else if(jg->tipe == 2)
	 		move = GetPlayerMove();
	 	else if(jg->tipe == 3)	
	 		move = GenerateMove(jg);
	 		
		chkm = CheckMove(jg,move);
	 	if(chkm == 1) 
	 	{  
			make_move_(jg,move);
			make_score_(jg);
			//save_move_(jg, move);
			WinGame(jg);
			clear_for_next_move_(jg);
			update_vez_(jg);
			if(jg->tipe != 3)
			{
				printf("\nPress any key to continue...");
				keypress(0,1);
			}
			else
				usleep(1e6);
		}
		else if(chkm == 99)
			go = 4;	
		else if(chkm == 2)
		{
			print_save_resolt_(jg);
			printf("\nPress any key to continue...");
			keypress(0,1);
		}
		else if(chkm == 3)
		{
		    print_load_resolt_(jg);
			//possible_moves_(jg);
			printf("\nPress any key to continue...");
			keypress(0,1);
		}
		else if(chkm == 4)
		{
			update_vez_(jg);
			clear_for_next_move_(jg);
			WinGame(jg);
			printf("Passou a vez...");
			usleep(5e4);
			printf("\nPress any key to continue...");
			keypress(0,1);
		}
		else
		{
			printf("\nJogada invalida"); 
			printf("\nPress any key to continue...");
			keypress(0,1);
	 	}
		
		if( jg->terminado == 3)
				go = 6;
	 	usleep(1e5);
 	}while(!go);
 	
	return go;
}

/*============================================================================*/

/**
 * @Auxiliary_Functions -> Funções internas de myf.c
**/

/**
 * @brief  Cria um tabuleiro de jogo novo  
 * @param  othello *jg
 * @return void
 */
void create_masck_( othello *jg , othello *jgm)  // todas as céluas a VAZIO exceto as 4 centrais
{
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			jg->T[i][j] = jgm->T[i][j];
	jg->vez = 1;
	jg->terminado = 0;
	jg->jogaNum = 1;
	jg->saven  = 99;
	jg->score[0] = 0;
	jg->score[1] = 0;
	jg->pcrnd = 0;
}


/**
 * @brief  Atualiza a posição no menu 
 * @param  int pos - posição atual ; int npos - numero de posições do menu 
 * @return pos
 */
int get_pos_m_(int pos, int npos)
{
	char *c = malloc(CHIN+1);
	c = keypress(0,1);
	if(!strncmp(c,"\033[",2))
	{
		switch(c[2])
		{
			case 'B': 
				pos++;
				if(pos > npos-1)
					pos = 0;
				break;
			case 'A':
				pos--;
				if(pos < 0)
					pos = npos-1;
				break;
		}				
	}
	if(!strncmp(c,"\n",1))
		pos = 99;
	free(c);
	return pos;
}

/**
 * @brief  Compara strings. Compara a first a partir de n1 ate n2 com a second integral
 * @param  char *first, char *second, int n1 , int n2
 * @return void
 */
 
int compare_string_(char *first, char *second, int n1, int n2)
{  
	char *aux; 
	aux = first;
	first += n1-1;
	while((*first == *second) && (*first < *aux + n2))
	{
	  if (*first == '\0' || *second == '\0')
		 break;
	  first++;
	  second++;
	}
	first -= n2;

	if (*second == '\0')
	  return 1;
	else
	  return 0;
}

/**
 * @brief  Faz display dde um erro e limpa o registo.
 * @param  int errorn - numero do erro a mostrar 
 * @return void
 */

void disp_error_(int errorn)
{
	call_error_(errorn);
	call_error_(0);
	call_error_(-1);
}

/**
 * @brief  Regista um erro para imprimir no ecran
 * @param  int errorn - numero do erro a mostrar 
 * @return void
 */

void call_error_(int errorn)
{
	static int error = 0;	
	char *titulo[] = { "" ,"Diretório ""saves"" inexistente.", "Ocurreu um erro na selecção do menu2.","Save file inexistente."};
	char *result[] = { "", "Impossível carregar jogos guardados.", "Programa Abortado.","Falha de load."};
	switch(errorn)
	{
		case -1:
			error = 0;
			break;
		case 0:
			if(error != 0)
			{
				textcolor2(RED);
				printf("\n	    Erro:");
				textcolor2(5);
				printf("  %s\n",titulo[error]);
				textcolor2(RED);
				printf("	Resultado:");
				textcolor2(5);			
				printf("  %s\n",result[error]);
				textcolor2(9);
			}
			break;
		default:
			error = errorn;
	}
}

/**
 * @brief  Determina se um caracter é um numero, a maneira inteligente de fazer esta função era compararar logo com os numeros entre 48 e 48+9 e deteraminar o numero fazendo c-48, mas esta ja estava feita 
 * @param  char ch - caracter 
 * @return int numero, ou 111 se não for um numero
 */
int isanumber_(char ch)
 {
 	switch(ch)
 	{
 	case '0': return 0; break;
 	case '1': return 1; break;
 	case '2': return 2; break;
 	case '3': return 3; break;
 	case '4': return 4; break;
 	case '5': return 5; break;
 	case '6': return 6; break;
 	case '7': return 7; break;
 	case '8': return 8; break;
 	case '9': return 9; break;
 	case '\n': return 110; break;
 	default:
 		return 111;
 		break;
 	}	
 }
 
/**
* @brief  troca dois catateres de ordem
* @param  char *a ,char * b
* @return void
*/
void SwapValues( char *a,  char *b)
{
        char *c;
        c = a; 
        a = b;  
        b = c;
}
/*============================================================================*/
