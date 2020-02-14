/* Standard error macro for reporting API errors */
#include <Windows.h>
#include <stdio.h>
#include <sddl.h>
#include <stdlib.h>
#include <time.h>

#define PERR(bSuccess, api) {if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

COORD pos;
int frame[26][5];

void cls(HANDLE hConsole);
void print_frame(HANDLE handle);
void hidecursor(HANDLE handle);
void move_location();
void input_first_value(HANDLE handle);
void display_frame(HANDLE handle);
void initialize_frame(HANDLE handle);

int
main()
{
	HANDLE handle;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	memset(frame, 0, 4 * 26 * 4);

	hidecursor(handle);
	cls(handle);

	print_frame(handle); //frame 출력

	srand((unsigned)time(NULL)); 

	while (1)
	{
		move_location(); //위치이동

		input_first_value(handle);//입력

		display_frame(handle); //출력

		Sleep(1000 * 10);

//		initialize_frame(handle);
	}

	pos.X = 1;
	pos.Y = 30;
	SetConsoleCursorPosition(handle, pos);

	return 0;
}


void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
									 cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
									 the current buffer */

									 /* get the number of character cells in the current buffer */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "GetConsoleScreenBufferInfo");
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputCharacter");

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	PERR(bSuccess, "ConsoleScreenBufferInfo");

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
	PERR(bSuccess, "FillConsoleOutputAttribute");

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	PERR(bSuccess, "SetConsoleCursorPosition");
	return;
}

void hidecursor(HANDLE handle)
{
	CONSOLE_CURSOR_INFO info;

	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &info);
}

void print_frame(HANDLE handle)
{
	int i;

	pos.X = 1;
	pos.Y = 1;
	SetConsoleCursorPosition(handle, pos);
	printf("\u250D\u2501\u2501\u2501\u2501\u2501\u252F\u2501\u2501\u2501\u2501\u2501\u252F\u2501\u2501\u2501\u2501\u2501\u252F\u2501\u2501\u2501\u2501\u2501\u2511");

	for (i = 2; i < 25; i++)
	{
		pos.X = 1;
		pos.Y = i;
		SetConsoleCursorPosition(handle, pos);
		printf("\u2502          \u2502          \u2502          \u2502          \u2502");
	}

	pos.X = 1;
	pos.Y = 25;
	SetConsoleCursorPosition(handle, pos);
	printf("\u251D\u2501\u2501\u2501\u2501\u2501\u253F\u2501\u2501\u2501\u2501\u2501\u253F\u2501\u2501\u2501\u2501\u2501\u253F\u2501\u2501\u2501\u2501\u2501\u2525");

	for (i = 26; i <= 27; i++)
	{
		pos.X = 1;
		pos.Y = i;
		SetConsoleCursorPosition(handle, pos);
		printf("\u2502          \u2502          \u2502          \u2502          \u2502");
	}

	pos.X = 1;
	pos.Y = 28;
	SetConsoleCursorPosition(handle, pos);
	printf("\u2515\u2501\u2501\u2501\u2501\u2501\u2537\u2501\u2501\u2501\u2501\u2501\u2537\u2501\u2501\u2501\u2501\u2501\u2537\u2501\u2501\u2501\u2501\u2501\u2519");
}

void move_location()
{
	//감소하는 방향
	int x, y;

	for (y = 25; y > 0; y--)
	{
		if (y == 24)
		{
			for (x = 4; x >= 0; x--)
			{
				frame[y][x] = frame[y - 2][x];
			}
			continue;
		}

		if (y == 23)
			continue;

		for (x = 4; x >= 0; x--)
		{
			frame[y][x] = frame[y - 1][x];
		}
	}

	for (x = 4; x >= 0; x--)
		frame[0][x] = 0;
}

void input_first_value(HANDLE handle)
{
	//4칸 중에 하나만 있어야 된다
	int rnd_space, rnd_point;

	rnd_space = rand() % 4; //rnd_space : 0~3
	frame[0][rnd_space] = 1; //exist_box = 1, no_exist_box = 0

	rnd_point = rand() % 10 + 1; // rnd = 1~10, 이 rnd는 점수이다.
	frame[0][4] = rnd_point; //점수

	//시험 보는 것
	int i;

	pos.X = 1;
	pos.Y = 30;
	SetConsoleCursorPosition(handle, pos);
	for (i = 0; i < 80; i++)
		printf(" ");

	pos.X = 1;
	pos.Y = 30;
	SetConsoleCursorPosition(handle, pos);
	for (i = 0; i < 4; i++)
	{
		printf("[%d]  ", frame[0][i]);
		if (frame[0][i] < 0 || frame[0][i] > 3)
			printf("******************");
	}
	printf("///%d", rnd_space);
}

void display_frame(HANDLE handle)
{
  //현재 위치를 기준으로, 역시 감소하는 방향으로
	int x, y;

	for (y = 25; y >= 0; y--)
	{
		if (y == 23)
			continue;

		for (x = 3; x >= 0; x--)
		{
#ifdef __XXX__
			if (frame[y][x] == 1) //box가 존재한다면
			{
				pos.X = x * 11 + 4;
				pos.Y = y + 2;
				SetConsoleCursorPosition(handle, pos);
				printf("\u25A0\u25A0\u25A0\u25A0");
			}
#else
			pos.X = x * 11 + 3;
			pos.Y = y + 2;
			SetConsoleCursorPosition(handle, pos);
			if (frame[y][x] == 1) //box가 존재한다면
				printf("\u25A0\u25A0\u25A0\u25A0");
			else
				printf("\u25A1\u25A1\u25A1\u25A1");
				//printf("\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020");
#endif
		}
		Sleep(1);
	}

	//fflush(stdout);

#ifdef __XXX__
	pos.X = 1;
	pos.Y = 31;
	SetConsoleCursorPosition(handle, pos);
#endif
}

void initialize_frame(HANDLE handle)
{
	int x, y;

	for (y = 25; y >= 0; y--)
	{
		if (y == 23)
			continue;

		for (x = 3; x >= 0; x--)
		{
			pos.X = x * 11 + 3;
			pos.Y = y + 2;
			SetConsoleCursorPosition(handle, pos);
			printf("\u0020\u0020\u0020\u0020\u0020\u0020\u0020\u0020");
			
		}
	}

	pos.X = 1;
	pos.Y = 31;
	SetConsoleCursorPosition(handle, pos);
}
