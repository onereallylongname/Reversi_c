/**
 *       @file  keypress.c
 *      @brief  Function to wait for key press
 *
 * This header files contains common declations, global variables
 * and possibily it can includean extra header files with the prototypes.
 *
 *     @Referencias: http://michael.dipperstein.com/keypress.html - adaptado
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
 #include"keypress.h"
 
 
/* sleep until a key is pressed and return value. echo = 0 disables key echo. */
// O segundo paramatro n e o parametro iforam acrescentados, assim como o ciclo for. estes permitem ler mais que u caracter  
char *keypress(unsigned char echo, int n)
{
    struct termios savedState, newState;
    char *c = malloc(3+1);
	int i;
    if (-1 == tcgetattr(STDIN_FILENO, &savedState))
    {
        c[0] = EOF; //adapted the return of error
        c[1] = '\0';
        return c;    /* error on tcsetattr */
    }

    newState = savedState;

    if ((echo = !echo)) /* yes i'm doing an assignment in an if clause */
    {
        echo = ECHO;    /* echo bit to disable echo */
    }

    /* disable canonical input and disable echo.  set minimal input to 1. */
    newState.c_lflag &= ~(echo | ICANON);
    newState.c_cc[VMIN] = 1;

    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState))
    {
        c[0] = EOF; //adapted the return of error
        c[1] = '\0';
        return c;    /* error on tcsetattr */
    }
	for(i = 0; i < 3; i++)
    	{
    		c[i] = getchar();      /* block (withot spinning) until we get a keypress */
    		if(c[i] != '\033' && i == n-1)
    			break;	
	}
	c[i+1] = '\0';
    /* restore the saved state */
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState))
    {
        c[0] = EOF; //adapted the return of error
        c[1] = '\0';
        return c;    /* error on tcsetattr */
    }

    return c;
}
