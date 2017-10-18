/**
 *       @file  entrega2.c
 *      @brief  Segunda etapa do trabalho
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
#define Debug0 Off
/*============================================================================*/

/**
 * @Myf_Functions -> Funções segunda entrega tpc 6
**/

/**
 * @brief  Confirma se a jogada é a final e declara a vitória
 * @param  ohtello *jg
 * @return int - resultado da execução
*/
int WinGame(othello * jg)
{
	int nmv = possible_moves_(jg);
	if(nmv == 0)
	{
		jg->terminado++;
		dbg0	printf("\nllllllllllllllllllllllljg->terminado - %d\n nmv - %d\n ",jg->terminado, nmv);////////////////////77777debug
		dbg0	keypress(0,1);
	}
	else
		jg->terminado = 0;
	
	dbg0	printf("\nllllllllllllllllllllllljg->terminado - %d\n nmv - %d\n",jg->terminado, nmv);////////////////////77777debug
		
	
	return jg->terminado;
}


/**
 * @brief  Confirma se a jogada é a final e declara a vitória
 * @param  ohtello *jg
 * @return int - resultado da execução
*/
int make_score_(othello * jg)
{
	int sc1 = 0, sc2 = 0, i, j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(jg->T[i][j] == PL1)
				sc1++;
			if(jg->T[i][j] == PL2)
				sc2++;
		}
	}
	jg->score[0] = sc1;
	jg->score[1] = sc2;			
	return 0;
}

/**
 * @brief  confirma se a jogada é válida
 * @param  int move
 * @return int - resultado da execução
*/
int CheckMove(othello * jg, int code)
{
	/*
	a1 to h8  = 11 to 88 cell number
	z or Z    = 1010
	s or S    = 1000 to 1009 last digit is the save file name
	l or L    = 1020 to 1029 last digit is the load file name
	q or Q    = 1999 (quit)
	*/
	
	if(code >= 11 && code <= 88)
	{
		int i, j;
		j = code/10-1;
		i = code%10-1;
		if(jg->T[i][j] == '~')
			return 1;
	}
	if(code >= 1000 && code <= 1009)
	{
		int saveNum = code%10;
		SaveGame(jg, saveNum);
		return 2;
	}
	if(code >= 1020 && code <= 1029)
	{
		int saveNum = code%10;
		if(load_bord_(jg, saveNum) == -1)
			return 0;
		else
			load_bord_(jg, saveNum);
		return 3;
	}
	if(code == 1010)
	{
		return 4;
	}
	if(code == 1999)
	{
		return 99;
	}
	return 0;
}

/**
 * @brief  Altera as peças conforme a jogada
 * @param  othello * jg, int move)
 * @return int - 
*/
int make_move_(othello * jg, int move)
{
	int i, j;
	j = move/10-1;
	i = move%10-1;	
		
	change_piece_1_(jg, i, j);
	PrintGameBoard(jg);
	usleep(5e5);
	dbg1	keypress(0,1);
	//Test column up
	if(check_up_(jg, i, j))
		change_line_up_(jg, i, j);
	
	//Test column down
	if(check_ri_(jg, i, j))
		change_line_ri_(jg, i, j);
	
	//Test column rigth
	if(check_do_(jg, i, j))
		change_line_do_(jg, i, j);
		
	//Test column left
	if(check_le_(jg, i, j))
		change_line_le_(jg, i, j);
		
	//Test column up & left
	if(check_up_le_(jg, i, j))
		change_line_up_le_(jg, i, j);
		
	//Test column up & right
	if(check_up_ri_(jg, i, j))
		change_line_up_ri_(jg, i, j);
	
	//Test column down & left
	if(check_do_le_(jg, i, j))
		change_line_do_le_(jg, i, j);
	

	//Test column down & right
	if(check_do_ri_(jg, i, j))
		change_line_do_ri_(jg, i, j);

	change_piece_(jg, i, j);
	PrintGameBoard(jg);
	usleep(5e5);
	return 0;
}
/*===== make lines ===========================================================*/

/**
 * @brief  Altera uma linha de peças para cima 
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_up_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint up");
	dbg1	keypress(0,1);
	int i3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	for(i3 = i-1; i3 > 0; i3--)
	{
		if(jg->T[i3][j] == pl)
			return 0;
		change_piece_(jg, i3, j);
		PrintGameBoard(jg);
		usleep(7e5);
	}
	return 0;
}
/**
 * @brief  Altera uma linha de peças para direita
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_ri_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint ri");
	dbg1	keypress(0,1);
	int j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	for(j3 = j+1; j3 < 7; j3++)
	{
		if(jg->T[i][j3] == pl)
			return 0;
		change_piece_(jg, i, j3);
		PrintGameBoard(jg);
		usleep(7e5);
	}
	return 0;
}
/**
 * @brief  Altera uma linha de peças para baixo 
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_do_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint do");
	dbg1	keypress(0,1);
	int i3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	for(i3 = i+1; i3 < 7; i3++)
	{
		if(jg->T[i3][j] == pl)
			return 0;
		change_piece_(jg, i3, j);
		PrintGameBoard(jg);
		usleep(7e5);
	}
	return 0;
}
/**
 * @brief  Altera uma linha de peças para esquerda
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_le_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint le");
	dbg1	keypress(0,1);
	int j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	for(j3 = j-1; j3 > 0; j3--)
	{
		if(jg->T[i][j3] == pl)
			return 0;
		change_piece_(jg, i, j3);
		PrintGameBoard(jg);
		usleep(7e5);
	}
	return 0;
}
/**
 * @brief  Altera uma linha de peças para cima e esquerda
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_up_le_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint up le");
	dbg1	keypress(0,1);
	int i3, j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	i3 = i-1;
	j3 = j-1;
	while((i3 >= 0) && (j3 >= 0))
	{
		if(jg->T[i3][j3] == pl)
			return 0;
		change_piece_(jg, i3, j3);
		PrintGameBoard(jg);
		usleep(7e5);
		i3--;
		j3--;
	}
	return 0;
}

/**
 * @brief  Altera uma linha de peças para cima e direita
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_up_ri_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint up ri");
	dbg1	keypress(0,1);
	int i3, j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	i3 = i-1;
	j3 = j+1;
	while((i3 >= 0) && (j3 <= 7))
	{
		if(jg->T[i3][j3] == pl)
			return 0;
		change_piece_(jg, i3, j3);
		PrintGameBoard(jg);
		usleep(7e5);
		i3--;
		j3++;
	}
	return 0;
}

/**
 * @brief  Altera uma linha de peças para baixo e direita
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_do_ri_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint do ri");
	dbg1	keypress(0,1);
	int i3, j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	i3 = i+1;
	j3 = j+1;
	while((i3 <= 7) && (j3 <= 7))
	{
		if(jg->T[i3][j3] == pl)
			return 0;
		change_piece_(jg, i3, j3);
		PrintGameBoard(jg);
		usleep(7e5);
		i3++;
		j3++;
	}
	return 0;
}

/**
 * @brief  Altera uma linha de peças para baixo e esquerda
 * @param  othello * jg, int p1, int p2 - ponto inicial e final
 * @return int - 
*/
int change_line_do_le_(othello * jg, int i, int j)
{
	dbg1    puts("\nprint do le");
	dbg1	keypress(0,1);
	int i3, j3;
	char pl;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	i3 = i+1;
	j3 = j-1;
	while((i3 <= 7) && (j3 >= 0))
	{
		if(jg->T[i3][j3] == pl)
			return 0;
		change_piece_(jg, i3, j3);
		PrintGameBoard(jg);
		usleep(7e5);
		i3++;
		j3--;
	}
	return 0;
}
/*===== end ==================================================================*/

/**
 * @brief  Altera uma peça 
 * @param  othello * jg, int i, int j
 * @return int - 
*/
int change_piece_(othello * jg, int i, int j)
{	
	char pl;
	if(jg->vez == 1)
		pl = PL1;
	if(jg->vez == 2)
		pl = PL2;
	jg->T[i][j] = pl;
	return 0;
}
/**
 * @brief  Altera a posição onde é posta a  primeira peça da jogada e assinala-a com letra minscula peça 
 * @param  othello * jg, int i, int j
 * @return int - 
*/
int change_piece_1_(othello * jg, int i, int j)
{	
	char pl;
	if(jg->vez == 1)
		pl = PL1+32;
	if(jg->vez == 2)
		pl = PL2+32;
	jg->T[i][j] = pl;
	return 0;
}

/**
 * @brief  Gera o movimento do pc - Se nao for possivel jogar retorna o codigo 1010, para passra a vez
 *			Tem dois modos :
 *							-  jg->pcrnd == 0 - O computador tenta fazer a jogada que faça a maior diferença entre pontuações
 *							-  jg->pcrnd == 1 - O computador joga aleatoriamente numa jogada possivel 
 * @param  othello * jg
 * @return int - move
*/
int GenerateMove(othello * jg)
{
	int rt, move, i, j, count = 0;
	int nmoves = possible_moves_(jg);
	if(nmoves == 0)
		return 1010; 
	int pmv[nmoves];
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(jg->T[i][j] == '~') 
			{
				pmv[count] = (i+1) + (j+1)*10;
				count++;
			}
		}
	}
	
	if(jg->pcrnd == 0)
	{
		
		if(nmoves > 1)
		{
			othello jgm0;
			othello *jgm = &jgm0;
			create_masck_(jg,jgm);
			int score[nmoves], ii;
			
				make_move_(jgm,pmv[0]);
				make_score_(jgm);
				if(jg->vez == 1)
					score[0] = jgm->score[0]-jgm->score[1]; 
				if(jg->vez == 2)
					score[0] = jgm->score[1]-jgm->score[0]; 
				
			for(i = 1; i < nmoves; i++)
			{
				make_move_(jgm,pmv[i]);
				make_score_(jgm);
				if(jg->vez == 1)
					 score[i] = jgm->score[0]-jgm->score[1]; 
				if(jg->vez == 2)
					score[i] = jgm->score[1]-jgm->score[0]; 
				ii = ii*(score[i-1] > score[i-1]) + i*(score[i-1] < score[i-1]);				
			}
			move = pmv[ii];	
		}
		else
			move = pmv[0];
		
	}
	else
	{
		srand(time(NULL));
		rt = rand()%nmoves;
		move = pmv[rt];
	dbg1	printf("\nllnmoves - %d \nmove - %d\n rt - %d \n",nmoves,move,rt);////////////////////77777debug
	dbg1	keypress(0,1);
		usleep(5e4);
	}
	return move;
}

/**
 * @brief  verifica quais as jogadas válidas
 * @param  othello * jg
 * @return int - numero de jogadas validas 
*/
int possible_moves_(othello * jg)
{
	int nmuves = 0, i, j, chk;
	
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
		if(jg->T[i][j] != PL1 && jg->T[i][j] != PL2) 
		{

				chk = 0;
				jg->T[i][j] = '~';
				//Test column up
				chk += check_up_(jg, i, j);
				//Test column down
				chk += check_do_(jg, i, j);
				//Test column rigth
				chk += check_ri_(jg, i, j);
				//Test column left
				chk += check_le_(jg, i, j);
				//Test column up & left
				chk += check_up_le_(jg, i, j);
				//Test column up & left
				chk += check_up_ri_(jg, i, j);
				//Test column down & left
				chk += check_do_le_(jg, i, j);
				//Test column down & right
				chk += check_do_ri_(jg, i, j);
				if(chk == 0)
					jg->T[i][j] = ' ';
				else
					nmuves++;			
			}		
		}
	}
	return nmuves;
}
/*===== check lines ==========================================================*/

/**
 * @brief  verifica se a jgada é válida para cima
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_up_(othello * jg, int ii, int jj)
{
	int i3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	
	if(ii <= 1)
		return 0;
	if(jg->T[ii-1][jj] != pn)
		return 0;
	for(i3 = ii-1; i3 >=0; i3--)
	{
		if(jg->T[i3][jj] == ' '|| jg->T[i3][jj] == '~')
			return 0;
		if(jg->T[i3][jj] == pl)
			return (i3+1)*10+jj+1;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para direita
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_ri_(othello * jg, int ii, int jj)
{
	int j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	
	if(jj >= 6)
		return 0;
	if(jg->T[ii][jj+1] != pn)
		return 0;
	for(j3 = jj+1; j3 <= 7; j3++)
	{
		if(jg->T[ii][j3] == ' '|| jg->T[ii][j3] == '~')
			return 0;
		if(jg->T[ii][j3] == pl)
			return (ii+1)*10+j3+1;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para esquerda
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_le_(othello * jg, int ii, int jj)
{
	int j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);

	if(jj <= 1)
		return 0;
	if(jg->T[ii][jj-1] != pn)
		return 0;
	for(j3 = jj-1; j3 >= 0; j3--)
	{
		if(jg->T[ii][j3] == ' '|| jg->T[ii][j3] == '~')
			return 0;
		if(jg->T[ii][j3] == pl)
			return (ii+1)*10+j3+1;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para baixo
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_do_(othello * jg, int ii, int jj)
{
	int i3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	
	if(ii >= 6)
		return 0;
	if(jg->T[ii+1][jj] != pn)
		return 0;
	for(i3 = ii+1; i3 <= 7; i3++)
	{
		if(jg->T[i3][jj] == ' '|| jg->T[i3][jj] == '~')
			return 0;
		if(jg->T[i3][jj] == pl)
			return (i3+1)*10+jj+1;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para diagonal cima-esquerda
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_up_le_(othello * jg, int ii, int jj)
{
	int i3, j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	
	if((ii <= 1) || (jj <= 1))
		return 0;
	if(jg->T[ii-1][jj-1] != pn)
		return 0;
	i3 = ii-1;
	j3 = jj-1;
	while((i3 >= 0) && (j3 >= 0))
	{
		if(jg->T[i3][j3] == ' '|| jg->T[i3][j3] == '~')
			return 0;
		if(jg->T[i3][j3] == pl)
			return (i3+1)*10+j3+1;
		i3--;
		j3--;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para diagonal cima - direita
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_up_ri_(othello * jg, int ii, int jj)
{
	int i3, j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	

	if((ii <= 1) || (jj >= 6))
		return 0;
	if(jg->T[ii-1][jj+1] != pn)
		return 0;
	i3 = ii-1;
	j3 = jj+1;
	while((i3 >= 0) && (j3 <= 7))
	{
		if(jg->T[i3][j3] == ' '|| jg->T[i3][j3] == '~')
			return 0;
		if(jg->T[i3][j3] == pl)
			return (i3+1)*10+j3+1;
		i3--;
		j3++;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para diagonal baixo - esquerda
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_do_le_(othello * jg, int ii, int jj)
{
	int i3, j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);
	

	if((ii >= 6) || (jj <= 1))
		return 0;
	if(jg->T[ii+1][jj-1] != pn)
		return 0;
	i3 = ii+1;
	j3 = jj-1;
	while((i3 <= 7) && (j3 >= 0))
	{
		if(jg->T[i3][j3] == ' '|| jg->T[i3][j3] == '~')
			return 0;
		if(jg->T[i3][j3] == pl)
			return (i3+1)*10+j3+1;
		i3++;
		j3--;
	}
	return 0;
}

/**
 * @brief  verifica se a jgada é válida para diagonal baixo - direita
 * @param  othello * jg, int ii, int jj - posições atuais
 * @return void 
*/
int check_do_ri_(othello * jg, int ii, int jj)
{
	int i3, j3;
	char pl, pn;
	pl = PL1*(jg->vez == 1)+PL2*(jg->vez == 2);
	pn = PL2*(jg->vez == 1)+PL1*(jg->vez == 2);

	if((ii >= 6) || (jj >= 6))
		return 0;
	if(jg->T[ii+1][jj+1] != pn)
		return 0;
	i3 = ii+1;
	j3 = jj+1;
	while((i3 <= 7) && (j3 <= 7))
	{
		if(jg->T[i3][j3] == ' '|| jg->T[i3][j3] == '~')
			return 0;
		if(jg->T[i3][j3] == pl)
			return (i3+1)*10+j3+1;
		i3++;
		j3++;
	}
	return 0;
}

/*===== end ==================================================================*/


/**
 * @brief  faz o update da vez de jogar
 * @param  othello * jg
 * @return void 
*/
void update_vez_(othello * jg)
{
	if(jg->vez == 2)
		jg->vez = 1;
	else if(jg->vez == 1)
		jg->vez = 2;
	
	jg->jogaNum++;		
}

/**
 * @brief  limpa do tabuleiro as opções de jogo antigas
 * @param  othello * jg
 * @return void 
*/
void clear_for_next_move_(othello * jg)
{
	int i, j;
	for(i = 0; i < 7; i++)
	{
		for(j = 0; j < 7; j++)
		{
				if(jg->T[i][j] == '~')
					jg->T[i][j] = ' ';
		}
	}
}