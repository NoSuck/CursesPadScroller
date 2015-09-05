/*
	Grady Martin
	2015年09月01日、17時46分
	Curses Prototyping Suite: Test (C)
*/

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void Gtfo (unsigned long luLine, const char *cpMessage, ...)
{
	/*
	Tits or this.
	*/

	endwin ();
	va_list args;
	va_start (args, cpMessage);
	vfprintf (stderr, cpMessage, args);
	va_end (args);
	fprintf (stderr, "\n%lu行目にエラーが発生しました。\n", luLine);
	exit ((int) luLine);
}

int main (const int argc, const char * const * argv)
{
	if (argc < 2)
	{
		Gtfo (__LINE__, "読み取るパッドが渡されませんでした。");
	}

	initscr ();
	keypad (stdscr, TRUE);
	noecho ();
	start_color ();
	curs_set (0);

	int nMaxY, nMaxX;
	getmaxyx (stdscr, nMaxY, nMaxX);
	nMaxY--;
	nMaxX--;

	FILE * file = fopen (argv[1], "r");
	if (file == NULL)
	{
		Gtfo (__LINE__, "%sを読み取れませんでした。", argv[1]);
	}

	// Load window and store dimensions.
	WINDOW * pad = getwin (file);
	int nPadH, nPadW;
	getmaxyx (pad, nPadH, nPadW);
	int nPadBegY, nPadBegX;
	getbegyx (pad, nPadBegY, nPadBegX);
	nPadH -= nPadBegY;
	nPadW -= nPadBegX;

	bool bEnd = false;
	unsigned uPosY = 0;
	while (!bEnd)
	{
		int n = getch ();
		switch (n)
		{
			case 'j':
				if (! (uPosY + 1 + nMaxY >= nPadH))
					uPosY++;
				break;
			case 'k':
				if (uPosY)
					uPosY--;
				break;
			case 'q':
				bEnd = true;
				break;
		}
		prefresh (pad, uPosY, 0, 0, 0, nMaxY, nMaxX);
	}

	endwin ();
}

