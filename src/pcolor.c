/**
 *       @file  pcolor.c
 *      @brief  File to set printf() colors - adapted
 *
 * Not much on detailed description about pcolor
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *     
 *
 * =====================================================================
 */

#include <stdio.h>
#include "pcolor.h"


/**
 * @brief  Set the color of text that follows upon the next printf.
 *
 * @param  attr Type of attribute (RESET, BRIGHT, BLINK, etc...)
 * @param  fg Color of foreground
 * @param  bg Color of background
 * @return Nothing
 */
void textcolor1(int attr, int fg, int bg)
{
	printf("%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
}

/**
 * @brief  Set the color of text that follows upon the next printf.
 *
 * @param  attr Type of attribute (RESET, BRIGHT, BLINK, etc...)
 * @param  fg Color of foreground
 * @return Nothing
 */
void textcolor2(int fg)
{
	if(fg == 9)
	printf(RESETc);
	else
	printf("%c[%dm", 0x1B, fg + 30);
}
