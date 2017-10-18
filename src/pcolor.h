/**
 *       @file  pcolor.h
 *      @brief Definitions for Text attributes and colors - adapted
 *
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================================
 */

/**
* @Attributes
*/

#define RESET		0
#define BRIGHT 		1
#define DIM	        2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

/**
* @Colors
*/

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	GRAY		7
#define	WHITE		8
#define NORMAL          9
/**
* @RESET
*/
#define RESETc "\033[0m"

void textcolor(int attr, int fg, int bg);
