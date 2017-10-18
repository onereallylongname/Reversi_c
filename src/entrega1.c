/**
 *       @file  entrega1.c
 *      @brief  Primeira etapa do trabalho
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
 * @Myf_Functions -> Funções primeira entrega tpc 6
**/

/**
 * @brief  Cria um tabuleiro de jogo novo  
 * @param  othello *jg
 * @return void
 */
void InitGame( othello *jg)  // todas as céluas a VAZIO exceto as 4 centrais
{
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			jg->T[i][j] = ' ';
	jg->T[3][3] = PL1;
	jg->T[4][4] = PL1;
	jg->T[3][4] = PL2;
	jg->T[4][3] = PL2;
	
	jg->vez = 1;
	jg->terminado = 0;
	jg->jogaNum = 1;
	jg->saven  = 99;
	jg->score[0] = 0;
	jg->score[1] = 0;
	jg->pcrnd = 2;
}

/**
 * @brief  Cria um tabuleiro de jogo novo  
 * @param  othello *jg
 * @return void
 */
int PrintGameBoard(othello *jg)
{
	int i, j, cor;
	char *p1 = malloc(3);
	char *p2 = malloc(3);
	make_header_();
	display_first_space_(22, 2);
	printf(">Jogo!<");
	display_last_space_(22, 2);
	display_screen_1_(2);
	display_screen_str_("", 2,2);
	display_first_space_(19, 2);
	if(jg->tipe == 1)
	{
		strcpy(p1," P1 ");
		strcpy(p2," Pc ");
	}
	if(jg->tipe == 2)
	{
		strcpy(p1," P1 ");
		strcpy(p2," P2 ");
	}
	//only if you change the save file
	if(jg->tipe == 3)
	{
		strcpy(p1," Pc1");
		strcpy(p2," Pc2");
	}
	printf(" %s vs %s",p1,p2);
	display_last_space_(19, 2);
	display_screen_str_("", 2,2);
	print_c_("<>",2);
	printf("           a   b   c   d   e   f   g   h           ");
	print_c_("<>\n",2);
	for(i = 0; i < 8; i++)
	{	
		print_board_border_();
		display_first_space_(7, 2);
		printf("%d ",i+1);
		print_c_("•",6);
		for(j = 0; j < 8; j++)
		{
			if(jg->T[i][j] == PL1)
				cor = 3;
		 	else if(jg->T[i][j] == PL2)
				cor = 4;
			else if(jg->T[i][j] == '~')
				cor = 5;
		 	else
		 		cor = 0;
		 		
			print_board_cell_(jg->T[i][j],cor);
		}
		printf(" %d",i+1);
		display_last_space_(7, 2);			
	}
	print_board_border_();
	print_c_("<>",2);
	printf("           a   b   c   d   e   f   g   h           ");
	print_c_("<>\n",2);
	display_screen_str_("", 2,2);
	make_base_();
	display_screen_str_("", 2,2);
	display_screen_str_("Score ", 2,2);
	print_c_("<>",2);
	printf("             %s:%03d       %s:%03d               ",p1, jg->score[0], p2, jg->score[1]);
	print_c_("<>\n",2);
	display_screen_str_("", 2,2);
	make_base_();
	free(p1);
	free(p2);
	return 0;
}

/**
 * @brief  Guarda o jogo actual num ficheiro de save game (otsvg)
 * @param  othello *jg
 * @return int - resultado da execução
 */
int SaveGame(othello *jg, int savenum)
{
	if(num_saves_in_dir_() == -1)
		return -1;
		
	char saveName[] = "saves/otsvg_.otsvg";
	char c;
	int i, j;
	saveName[11] = savenum+48;
 
	jg->saven = savenum;
	
	FILE *fp;
	fp = fopen(&saveName[0], "w");
	
	fprintf(fp,">Tabuleiro:\n");
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			c = jg->T[i][j];
			if(c == ' ')
			 c = 35;
			fprintf(fp,"%c",c);
		}
		fprintf(fp,"\n");	
	}
	fprintf(fp,"==================\n");
	fprintf(fp,"> vez : \n%d; \n",jg->vez);
	fprintf(fp,"> terminado : \n%d; \n",jg->terminado);
	fprintf(fp,"> jogaNum : \n%d; \n",jg->jogaNum);
/*	fprintf(fp,"> regJogo[] :\n");
	for(i = 0; i < jg->jogaNum; i++)
		fprintf(fp,"%d,",jg->regJogo[i]);
*/	fprintf(fp,"> tipe : \n%d; \n",jg->tipe);
	fprintf(fp,"> saven : \n%d; \n",jg->saven);
	fprintf(fp,"> score1 : \n%d; \n",jg->score[0]);
	fprintf(fp,"> score2 : \n%d; \n",jg->score[1]);
	fprintf(fp,"> pc type : \n%d; \n",jg->pcrnd);
	fprintf(fp,"\n\n#/*Comments*/#; \n");
	fclose(fp);
	return 0;
}

/**
 * @brief  Lê um ficheiro de save game e cria um tabuleiro (otsvg) - pagina especial
 * @param  othello *jg
 * @return int - resultado da execução
 */
int LoadGame(othello *jg)
{
	int numSaves, aux, go = 0, pos = 0;
	numSaves = num_saves_in_dir_();
	if(numSaves == -1)
		return 1;

	int saves[numSaves];
	get_saves_in_dir_(&saves[0]);
	
	do
	{
	
		aux = pos;
		print_menu_load_(pos, numSaves, &saves[0]);//, saves[numSaves]
		make_base_();
		pos = get_pos_m_(pos,numSaves+1);
		if(pos == 99)
		{
			if(aux == numSaves)
			{
				go = 1;
			}
			else if(aux != numSaves)
			{
				load_bord_(jg, saves[aux]);
				go = 7;
			}
		}
		
	}while(!go);
	return go;
}

/**
 * @brief  Recebe input da jogada
 * @param  void
 * @return int - resultado da execução
 */
int GetPlayerMove(void)
{
	/*Move code:
	
	A : up    = 2
	B : down  = 6
	C : right = 4
	D : left  = 8   <- not in use
	
	a1 to h8  = 11 to 88 cell number
	z or Z    = 1010
	s or S    = 1000 to 1009 last digit is the save file name
	l or L    = 1020 to 1029 last digit is the load file name
	q or Q    = 1999 (quit)
	*/
	
	int move = 0;
	char *c = malloc(CHIN);
	char c1[2]; 
	c = keypress(1,2);
	
#if 0
	if(!strncmp(c,"\033[",2))
	{
		switch(c[2])
		{
			case 'B': 
				move = 6;
				return move;
			case 'A':
				move = 2;
				return move;
			case 'C': 
				move = 4;
				return move;
			case 'D':
				move = 8;
				return move;
		}				
	}
#endif

	if(c[0] == 'q' || c[0] == 'Q')
	{
		free(c);
		return 1999;
	}
	if(c[0] == 'z' || c[0] == 'Z')
	{
		free(c);
		return 1010;
	}
	else if(c[0] == 's' || c[0] == 'S')
	{
		move = 1000 + isanumber_(c[1]);
		return move;
	}
	else if(c[0] == 'l' || c[0] == 'L')
	{
		move = 1020 + isanumber_(c[1]);
		free(c);
		return move;
	}
	// check coordinates order
	if(isanumber_(c[0]) != 111 )//&& isanumber_(c[1]) == 111) 
	{
		c1[0] = c[1];
		c1[1] = c[0];
	}
	if(isanumber_(c[0]) == 111 ) //&& isanumber_(c[1]) != 111)
	{
		c1[0] = c[0];
		c1[1] = c[1];
	}
	if(c1[0] >= 97 && c1[0] <= 104)
		move = (c1[0]-96 )*10 + c1[1]-48;
	if(c1[0] <= 72 && c1[0] >= 65 )
		move = (c1[0]-64 )*10 + c1[1]-48;
	
	free(c);	
		dbg1	printf("\nlllllllllllllllllllllllmove - %d\n ",move);////////////////////77777debug
	dbg1	keypress(0,1);
	return move;
}

/*============================================================================*/

/**
 * @Myf_Functions -> Funções auxiliares primeira entrega tpc 6
**/

/**
 * @brief  Cria um jogo a partir de um save file
 * @param  othello *jg
 * @return int - resultado da execução
 */
int load_bord_(othello *jg, int savenum)
{
	
	if(num_saves_in_dir_() == -1)
	{
		call_error_(3);
		call_error_(0);
		call_error_(-1);
		return -1;
	}	
	char saveName[] = "saves/otsvg_.otsvg";
	char * str = malloc(81);
	int j, i = 0, cnt;
	saveName[11] = savenum+48;
	
	FILE *fp;
	fp = fopen(&saveName[0], "r");
	if(fp == NULL)
	{
		call_error_(3);
		call_error_(0);
		call_error_(-1);
		return -1;
	}
	else
	{
		fgets(str, 74, fp);
		do{
			if(i >= 1 && i <= 10)
			{
				for(j = 0; j < 8; j++)
				{
					if(str[j] == '#')
						jg->T[i-1][j] = ' ';
					else
						jg->T[i-1][j] = str[j];
				}
			}
			switch(i)
			{
				case 11:
					jg->vez = isanumber_(str[0]);
					break;
				case 13:
					jg->terminado = isanumber_(str[0]);
					break;
				case 15:
					jg->jogaNum = 0;
					cnt = 0;
					while(str[cnt] != ';'|| cnt > 6)
					{	
						jg->jogaNum = jg->jogaNum *10+isanumber_(str[cnt]);
						cnt++;
					}
					break;
	/*			case 17:
					char *token = strtok(str,",");
					j = 0;
					while(token[j] != '\n')
					{
						jg->regJogo[j] = isanumber_(token[j][0])*10 + isanumber_(token[j][1]);
					printf("%d,",jg->regJogo[j]); //////////////////////////////////
						j++;
					}
				
					printf("\nç-ç-çççç\n"); //////////////////////////////////
				
				
					break;
	*/			case 17:
					jg->tipe = isanumber_(str[0]);
					break;
				case 19:
					jg->saven = isanumber_(str[0]);
					break;
				case 21:
					cnt = 0;
					jg->score[0] = 0;
					while(str[cnt] != ';' || cnt > 6)
					{	
						jg->score[0] = jg->score[0]*10+isanumber_(str[cnt]);
						cnt++;
					}
					break;
				case 23:
					cnt = 0;
					jg->score[1] = 0;
					while(str[cnt] != ';' || cnt > 6)
					{	
						jg->score[1] = jg->score[1]*10+isanumber_(str[cnt]);
						cnt++;
					}
					break;
				case 25:
					jg->pcrnd = isanumber_(str[cnt]);
					break;
			}
			i++;	
		}while(fgets(str, 81, fp) != NULL);
	}
	free(str);
	possible_moves_(jg);
	return 1;
}

/**
 * @brief  Conta quantos save games há no directório
 * @param  void
 * @return int - resultado da execução
 */
int num_saves_in_dir_(void)
{
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;
	
	dirp = opendir("./saves/"); /* There should be error handling after this */
	if(dirp == NULL)
	{
		disp_error_(1);
		printf("Press any key to continue...");
		return -1;
	}	
	while ((entry = readdir(dirp)) != NULL ) {
		if (entry->d_type == DT_REG && compare_string_(entry->d_name,".otsvg",7,12) ) { /* && !strncmp(entry->d_name,"otsvg",5)  If the entry is a regular file */
		     file_count++;
		     dbg1 printf("%s\n",entry->d_name);
		}
	}
	closedir(dirp);
    return file_count;
}

/**
 * @brief  Conta quantos save games há no directório
 * @param  void
 * @return int - resultado da execução
 */
int get_saves_in_dir_(int * saves)
{
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;
	
	dirp = opendir("./saves/"); /* There should be error handling after this */
	if(dirp == NULL)
	{
		disp_error_(1);
		printf("Press any key to continue...");
		return -1;
	}	
	while ((entry = readdir(dirp)) != NULL) {
		if (entry->d_type == DT_REG && compare_string_(entry->d_name,".otsvg",7,12) ) { /* && !strncmp(entry->d_name,"otsvg",5)  If the entry is a regular file */
		    saves[file_count] = isanumber_(entry->d_name[5]);
		    file_count++;
		    dbg1 printf("%s\n",entry->d_name);
		}
	}
	closedir(dirp);
    return 0;
}

/**
 * @brief  Conta quantos save games há no directório
 * @param  void
 * @return int - resultado da execução
 
int save_move_(othello * jg, int  move)
{
	jg->regJogo[jg->jogaNum] = move;
	return 0;
}*/