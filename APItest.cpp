#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

int main() {
	WinExec("D:\\Study\\SDL_program\\̹�˴�ս\\Debug\\̹�˴�ս.exe", SW_SHOWMAXIMIZED);
	ShellExecute(NULL, NULL, "www.baidu.com", NULL, NULL, SW_SHOWNA);
	return 0;
}
