#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h> 
#define ca_ROW 20
#define ca_COL 20
#define mid_COL 9
#define bl_NUM 4
#define Sle_NUM 300
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define NUMMAX 81

//Debug turning error num: 0 , 4 , 6         error:right line - right turning
//Debug turning direction error num: 6       error:A/D reverse



char canvas[ca_ROW][ca_COL];        //游戏画板 
char block[bl_NUM][bl_NUM];         //每种方块 
char block_now[bl_NUM][bl_NUM];
int blocklist[NUMMAX];              //方块顺序 
int blockdirection[NUMMAX];         //方块的方向 
int record = 0;
int score = 0;
int block_count = 0;
int block_num;

void Initialize(){
	char alter;
	char diff[3][10] = {"简单","普通","困难"};
	
	while(true){
		printf("\n\n\n                                        游戏即将开始，请选择游戏难度:\n\n");
		for(int row = 0; row < 3; row ++){        
			printf("                                     "); 
			if(row == record) 
			printf("             -->%s<--\n\n",diff[row]);
			else
			printf("                %s\n\n",diff[row]); 
		}
		printf("\n                                按'↑'或'↓'来调整难度，按Enter键确认进入下一界面\n");
		switch(alter = getch()){
			case UP:
				if(record > 0)
				record --;
				break;
			case DOWN:
				if(record < 2)
				record ++;
				break;	
			default: break;
		}
		system("CLS");
		
		if(alter == ENTER) break;		
	}
	
	return;
}

void Copy_block(int block_count, char block[bl_NUM][bl_NUM]){
	FILE *fp = NULL;
	int num = 0;
	char mid[7] = {0};
	while(fp == NULL)
	switch(blocklist[block_count]){
		case 0:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_a/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_a/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 2:
					fp = fopen("sample/size_a/dire_2.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 3:
					fp = fopen("sample/size_a/dire_3.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
		case 1:
			fp = fopen("sample/size_b/dire_0.txt", "r");
			while(num < bl_NUM){
				fgets(mid, bl_NUM + 2, fp);
				strncpy(block[num ++], mid, 4);
			}
			break;
		case 2:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_c/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_c/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
		case 3:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_d/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_d/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
			break;
		case 4:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_e/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_e/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 2:
					fp = fopen("sample/size_e/dire_2.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 3:
					fp = fopen("sample/size_e/dire_3.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
		case 5:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_f/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_f/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
		case 6:
			switch(blockdirection[block_count]){
				case 0:
					fp = fopen("sample/size_g/dire_0.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 1:
					fp = fopen("sample/size_g/dire_1.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 2:
					fp = fopen("sample/size_g/dire_2.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
				case 3:
					fp = fopen("sample/size_g/dire_3.txt", "r");
					while(num < bl_NUM){
						fgets(mid, bl_NUM + 2, fp);
						strncpy(block[num ++], mid, 4);
					}
					break;
			}
	}
	block_count ++;
	
	fp = stdin;
}

void Output_HEAD(){
//	FILE *fp = NULL;
	Copy_block(block_count ++, block);
//	fclose(fp);
	
	printf("\n          游戏边界:");
	printf("                      第一个方块:");
	printf("          操作:\n");
	printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	
	printf("          ");
	
	for(int y = 0; y < bl_NUM + 2; y ++)
	printf("-");
	
	printf("\n");
	
	for(int h = 0; h < ca_ROW; h ++){
		printf("          |");
		for(int k = 0; k < ca_COL; k ++)
		printf("%c",canvas[h][k]);
		printf("|");
		
		if(h < bl_NUM){
			printf("          |");
			for(int k = 0; k < bl_NUM; k ++)
			printf("%c",block[h][k]);
			printf("|");
			
			printf("              ");
			switch(h){
				case 0:
					printf("按'←'或'→'左右移动");
					break;
				case 1:
					printf("按'A'或'D'逆时针或顺时针旋转");
					break;
				case 2:
					printf("按'↓'快速下落");
				default : break;
			}
		}else if(h == bl_NUM){
			printf("          ");
			for(int y = 0; y < bl_NUM + 2; y ++)
			printf("-");
		}else if(h == 12){
			printf("          ");
			printf("得分:%d",score);
		}
			
		
		printf("\n");
	}
	
	printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	printf("\n\n            ");
	printf("-->按任意键开始<--\n");
	printf("record = %d",record);
	
	int temp;
	if(temp = getch()){
		system("CLS");
		return;
	}

}

void Prepare(){
		
	block_num = (int)(pow(2, record + 1) * 10);
	printf("一共有%d个方块\n",block_num);
	Sleep(2000);	
	
	memset(blocklist, 0, sizeof(NUMMAX));
	
	srand(time(NULL));
	for(int i = 0; i < block_num; i ++){
		blocklist[i] = rand() % 7;
		
		if(blocklist[i] == 0 || blocklist[i] == 4 || blocklist[i] == 6)
		blockdirection[i] = rand() % 4;
		else if(blocklist[i] == 2 || blocklist[i] == 3 || blocklist[i] == 5)
		blockdirection[i] = rand() % 2;
		else blockdirection[i] = 0;
	}
	
	
	for(int g = 0; g < 3; g ++){
		char mid[100];

		FILE *fp = NULL;
		
		switch(g){
			case 0:
				fp = fopen("number/3.txt", "r");
				break;
			case 1:
				fp = fopen("number/2.txt", "r");
				break;
			case 2:
				fp = fopen("number/1.txt", "r");
		}
		
		while(fgets(mid, 100, fp) != NULL)
		for(int i = 0; i < strlen(mid); i ++)
		printf("%c",mid[i]);
		
//		fclose(fp);
		fp = stdin;
		Sleep(2 * Sle_NUM);
		system("CLS");
		
	}

	Output_HEAD(); 
	 
}

void Add(int row, int col){
	for(int u = row; u < ca_ROW; u ++)
	for(int j = col; j < ca_COL; j ++)
	if(u - row < bl_NUM && j - col < bl_NUM && block_now[u - row][j - col] == '*')
	canvas[u][j] = '*';
	
	return;
}

int Check_down(int check_down, int row, int col, int blo_kind, int blo_dire){
	char info_down_row[19][5] = {"33","333","13","322",
								 "33",
								 "3","2222",
								 "23","332",
								 "333","23","232","32",
								 "32","233",
								 "33","223","31","333"};
							
	char info_down_col[19][5] = {"12","123","12","123",
							  	 "12",
								 "1","0123",
								 "12","123",
								 "123","12","123","12",
								 "12","123",
								 "12","123","12","123"};	
		
	char mid_row[5];
	char mid_col[5];
	memset(mid_row, 0, sizeof(mid_row));
	memset(mid_col, 0, sizeof(mid_col));
	int list[7];
	list[0] = 0; list[1] = 4; list[2] = 5; list[3] = 7; 
	list[4] = 9; list[5] = 13; list[6] = 15;
	
	strcpy(mid_row, info_down_row[list[blo_kind] + blo_dire]);
	strcpy(mid_col, info_down_col[list[blo_kind] + blo_dire]);
	
	int length = strlen(mid_row);
	for(int i = 0; i < length; i ++){
		int loc_row = row + mid_row[i];
		int loc_col = col + mid_col[i];
		
		if(canvas[loc_row + 1 - '0'][loc_col - '0'] == '*' || loc_row - '0' == ca_ROW - 1){

			check_down = false;
			Add(row, col);
			
			printf("checkerror  ");
			printf("check = %d\n",check_down);
			
			break;
		}
	}
	
	
	return check_down;
}

int Check_left(int check_left, int row, int col, int blo_kind, int blo_dire){
	char info_left_row[19][5] = {"123","23","123","23",
								 "23",
								 "0123","2",
								 "123","23",
								 "23","123","23","123",
								 "123","23",
								 "123","23","123","23"};
							
	char info_letf_col[19][5] = {"111","31","122","11",
							  	 "11",
								 "1111","0",
								 "112","21",
								 "21","212","12","111",
								 "211","12",
								 "221","13","111","11"};
	char mid_row[5];
	char mid_col[5];
	memset(mid_row, 0, sizeof(mid_row));
	memset(mid_col, 0, sizeof(mid_col));
	int list[7];
	list[0] = 0; list[1] = 4; list[2] = 5; list[3] = 7; 
	list[4] = 9; list[5] = 13; list[6] = 15;
	
	strcpy(mid_row, info_left_row[list[blo_kind] + blo_dire]);
	strcpy(mid_col, info_letf_col[list[blo_kind] + blo_dire]);
	int length = strlen(mid_row);
	for(int i = 0; i < length; i ++){
		int loc_row = row + mid_row[i];
		int loc_col = col + mid_col[i];
		
		if(loc_col - '0' <= 0 || canvas[loc_row - '0'][loc_col - '0' - 1] == '*'){
			check_left = false;
			printf("check_letf = %d",check_left);
			
			break;
		}
	}
	
	return check_left;
}

int Check_right(int check_right, int row, int col, int blo_kind, int blo_dire){
	char info_right_row[19][5] = {"123","23","123","23",
								 "23",
								 "0123","2",
								 "123","23",
								 "23","123","23","123",
								 "123","23",
								 "123","23","123","23"};
							
	char info_right_col[19][5] = {"112","33","222","31",
							  	 "22",
								 "1111","3",
								 "122","32",
								 "23","222","32","121",
								 "221","23",
								 "222","33","211","13"};
	char mid_row[5];
	char mid_col[5];
	memset(mid_row, 0, sizeof(mid_row));
	memset(mid_col, 0, sizeof(mid_col));
	int list[7];
	list[0] = 0; list[1] = 4; list[2] = 5; list[3] = 7; 
	list[4] = 9; list[5] = 13; list[6] = 15;
	
	strcpy(mid_row, info_right_row[list[blo_kind] + blo_dire]);
	strcpy(mid_col, info_right_col[list[blo_kind] + blo_dire]);
	int length = strlen(mid_row);
	for(int i = 0; i < length; i ++){
		int loc_row = row + mid_row[i];
		int loc_col = col + mid_col[i];
		
		if(loc_col - '0' >= ca_COL - 1 || canvas[loc_row - '0'][loc_col - '0' + 1] == '*'){
			check_right = false;
			printf("check_right = %d",check_right);
			
			break;
		}
	}
	
	return check_right;
}

int Check_tD(int check_D, int row, int col, int blo_kind, int blo_dire){
	int blo_dire_ke = blockdirection[block_count - 1];
	
	if(!blo_dire)
	switch(blo_kind){
		case 0: case 4: case 6:
			blockdirection[block_count - 1] = 3;
			break;
		case 1:
			blockdirection[block_count - 1] = 0;
			break;
		case 2: case 3: case 5:
			blockdirection[block_count - 1] = 1;
			break;	
	}else if(blo_dire) 
			blockdirection[block_count - 1] = blo_dire - 1;
	
	char block_check[bl_NUM][bl_NUM];
	Copy_block(block_count - 1, block_check);
	for(int h = row; h < row + bl_NUM; h ++)
	for(int g = col; g < col + bl_NUM; g ++)
	if(block_check[h - row][g - col] == '*'){
		if(h < 0 || h > ca_ROW - 1 || g < 0 || g > ca_COL - 1){
			check_D = false;
			blockdirection[block_count - 1] = blo_dire_ke;
			break;
		}
		if(canvas[h][g] == '*'){
			check_D = false;
			blockdirection[block_count - 1] = blo_dire_ke;
			break;
 		}	
	}
	if(!check_D)
	printf("Warnning:当前位置不可以顺时针旋转\n");
	
	return check_D;
}

int Check_tA(int check_A, int row, int col, int blo_kind, int blo_dire){
	int blo_dire_ke = blockdirection[block_count - 1];
	
	switch(blo_kind){
		case 0: case 4: case 6:
			if(blo_dire == 3) 
			blockdirection[block_count - 1] = 0;
			else blockdirection[block_count - 1] = blo_dire + 1; 
			break;
		case 1:
			blockdirection[block_count - 1] = 0;
			break;
		case 2: case 3: case 5:
			if(blo_dire == 1)
			blockdirection[block_count - 1] = 0;
			else blockdirection[block_count - 1] = blo_dire + 1;
			break;	
	}
	
	char block_check[bl_NUM][bl_NUM];
	Copy_block(block_count - 1, block_check);
	
	for(int h = row; h < row + bl_NUM; h ++)
	for(int g = col; g < col + bl_NUM; g ++)
	if(block_check[h - row][g - col] == '*'){
		if(h < 0 || h > ca_ROW - 1 || g < 0 || g > ca_COL - 1){
			check_A = false;
			blockdirection[block_count - 1] = blo_dire_ke;
			break;
		}
		if(canvas[h][g] == '*'){
			check_A = false;
			blockdirection[block_count - 1] = blo_dire_ke;
			break;
 		}	
	}
	if(!check_A)
	printf("Warnning:当前位置不可以逆时针旋转\n");
	
	return check_A;
}

void Output_BODY(int row, int col, int score){
	Copy_block(block_count, block);
	Copy_block(block_count - 1, block_now);
	
	printf("此时block_count = %d\nblock_num = %d",block_count,block_num);
	printf("还有%d个方块\n",block_num - block_count + 1);
	printf("下一个方块编号%d\n",blocklist[block_count]);
	printf("\n          游戏边界:");
	printf("                      下一个方块:");
	printf("          操作:\n");
	printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	
	printf("          ");
	
	for(int y = 0; y < bl_NUM + 2; y ++)
	printf("-");
	
	printf("\n");
	
	for(int h = 0; h < ca_ROW; h ++){
		printf("          |");
		for(int k = 0; k < ca_COL; k ++){
			int row_inner = 0;
			int col_inner = 0;
			if(h >= row && h < row + bl_NUM && k >= col && k < col + bl_NUM){
				if(block_now[h - row][k - col] == ' ')
				printf("%c",canvas[h][k]);
				else
				printf("%c",block_now[h - row][k - col]);
			}else printf("%c",canvas[h][k]);
		}
		printf("|");
		
		if(h < bl_NUM){
			printf("          |");
			for(int k = 0; k < bl_NUM; k ++)
			printf("%c",block[h][k]);
			printf("|");
			
			printf("              ");
			switch(h){
				case 0:
					printf("按'←'或'→'左右移动");
					break;
				case 1:
					printf("按'A'或'D'逆时针或顺时针旋转");
					break;
				case 2:
					printf("按'↓'快速下落");
				default : break;
			}
		}else if(h == bl_NUM){
			printf("          ");
			for(int y = 0; y < bl_NUM + 2; y ++)
			printf("-");
		}else if(h == 12){
			printf("          ");
			printf("得分:%d",score);
		}	
    	printf("\n");
	}
	
    printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	
	switch(record){
		case 0:
			Sleep(Sle_NUM);
			break;
		case 1:
			Sleep(Sle_NUM / 2);
			break;
		case 2:
			Sleep(Sle_NUM / 4);
			break;
	}
	system("CLS");
	return;
}

int Control_LR(int row, int col, int blo_kind, int blo_dire, char get_if){
	int check_left = true;
	int check_right = true;
	
	if(get_if == LEFT){
		check_left = 
		Check_left(check_left, row, col, blo_kind, blo_dire);
		
		if(check_left) col --;
	}
	
	if(get_if == RIGHT){
		check_right = 
		Check_right(check_right, row, col, blo_kind, blo_dire);
		
		if(check_right) col ++;
	}
	
	return col;
}

int Control_AD(int row, int col, int blo_kind, int blo_dire, char get_if){
	int check_A = true;
	int check_D = true;
	
	if(get_if == 'd' || get_if == 'D'){
		check_D =
		Check_tD(check_D, row, col, blo_kind, blo_dire);
		
		if(check_D && !blo_dire){	
			if(blo_kind == 0 || blo_kind == 4 || blo_kind == 6)
			blo_dire = 3;
			if(blo_kind == 2 || blo_kind == 3 || blo_kind == 5)
			blo_dire = 1;
		}else if(check_D && blo_dire)
			blo_dire --;
	}
	
	if(get_if == 'a' || get_if == 'A'){
		check_A =
		Check_tA(check_A, row, col, blo_kind, blo_dire);
		
		if(check_A){	
			switch(blo_kind){
				case 0: case 4: case 6:
					if(blo_dire == 3) 
					blo_dire = 0;
					else blo_dire ++; 
					break;
				case 1:
					blo_dire = 0;
					break;
				case 2: case 3: case 5:
					if(blo_dire == 1)
					blo_dire = 0;
					else blo_dire ++;
					break;	
			}
		}
	}
	
	blockdirection[block_count - 1] = blo_dire;
	return blo_dire;
}

void Output_TAIL(int row, int col, int score){

	Copy_block(block_count - 1, block_now);
	
	printf("此时block_count = %d\nblock_num = %d",block_count,block_num);
	printf("还有%d个方块\n",block_num - block_count);
	printf("下一个方块编号%d\n",blocklist[block_count]);
	printf("\n          游戏边界:");
	printf("                      下一个方块:");
	printf("          操作:\n");
	printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	
	printf("          ");
	
	for(int y = 0; y < bl_NUM + 2; y ++)
	printf("-");
	
	printf("\n");
	
	for(int h = 0; h < ca_ROW; h ++){
		printf("          |");
		for(int k = 0; k < ca_COL; k ++){
			int row_inner = 0;
			int col_inner = 0;
			if(h >= row && h < row + bl_NUM && k >= col && k < col + bl_NUM){
				if(block_now[h - row][k - col] == ' ')
				printf("%c",canvas[h][k]);
				else
				printf("%c",block_now[h - row][k - col]);
			}else printf("%c",canvas[h][k]);
		}
		printf("|");
		
		if(h < bl_NUM){
			printf("          |");
			for(int k = 0; k < bl_NUM; k ++)
			printf(" ");
			printf("|");
			
			printf("              ");
			switch(h){
				case 0:
					printf("按'←'或'→'左右移动");
					break;
				case 1:
					printf("按'A'或'D'逆时针或顺时针旋转");
					break;
				case 2:
					printf("按'↓'快速下落");
				default : break;
			}
		}else if(h == bl_NUM){
			printf("          ");
			for(int y = 0; y < bl_NUM + 2; y ++)
			printf("-");
		}else if(h == 12){
			printf("          ");
			printf("得分:%d",score);
		}	
    	printf("\n");
	}
	
    printf("          ");
	for(int y = 0; y < ca_COL + 2; y ++)
	printf("-");
	
	switch(record){
		case 0:
			Sleep(Sle_NUM);
			break;
		case 1:
			Sleep(Sle_NUM / 2);
			break;
		case 2:
			Sleep(Sle_NUM / 4);
			break;
	}
	system("CLS");
	return;
}

int Score_count(char canvas[ca_ROW][ca_COL], int score){
	int count = 0;
	for(int i = ca_ROW - 1; i >= 0; ){    //计分 & 消除 
		int flag = 1;
		for(int j = 0; j < ca_COL; j ++)
		if(canvas[i][j] == ' '){
			flag = 0;
			break;
		}
		if(flag){
			for(int u = i; u > 0; u --)
			for(int g = 0; g < ca_COL; g ++)
			canvas[u][g] = canvas[u - 1][g];
			
			for(int h = 0; h < ca_COL; h ++)
			canvas[0][h] = ' ';
			count ++;
		}else i --;
		
	}
	score += count;
	
	return score;
}


void Start(){
	
	int row, col;
	int blo_kind, blo_dire;
	
	while(block_count <= block_num){
		
		blo_kind = blocklist[block_count - 1];
		blo_dire = blockdirection[block_count - 1];
		col = mid_COL;
		
		switch(blo_kind){
			case 0:
				if(!blo_dire || blo_dire == 2) row = -1;
				else row = -2;
				break;
			case 1:
				row = -2;
				break;
			case 2:
				if(blo_dire) row = -2;
				else row = 0;
				break;
			case 3:
				if(blo_dire) row = -2;
				else row = -1;
				break;
			case 4:
				if(!blo_dire || blo_dire == 2) row = -2;
				else row = -1;
				break;
			case 5:
				if(blo_dire) row = -2;
				else row = -1;
				break;
			case 6:
				if(!blo_dire || blo_dire == 2) row = -1;
				else row = -2;
				break;
		}
		
		if(block_count < block_num)
		Output_BODY(row, col, score);
		else
		Output_TAIL(row, col, score);
		
		while(row < ca_ROW){
			int check_down = true;
			char get_if = NULL;
			
			if(kbhit()){
				get_if = NULL;
				get_if = getch();
				
				if(get_if == LEFT || get_if == RIGHT)
				col = Control_LR(row, col, blo_kind, blo_dire, get_if);
				
				if(get_if == 'a' || 'A' || 'd' || 'D')
				blo_dire = Control_AD(row, col, blo_kind, blo_dire, get_if);
				
				if(get_if == DOWN){
					while(check_down){
						check_down = 
						Check_down(check_down, row, col, blo_kind, blo_dire);
						row ++;
					}
					if(check_down && block_count < block_num)
					Output_BODY(row, col, score);
					else if(check_down && block_count == block_num)
					Output_TAIL(row, col, score);
					break;
				}
				
			}else{
				check_down = 
				Check_down(check_down, row, col, blo_kind, blo_dire);
				row ++;
				
				switch(record){
					case 0:
						printf("当前难度:简单\n");
						break;
					case 1:
						printf("当前难度:普通\n");
						break;
					case 2:
						printf("当前难度:困难\n");
						break;
				}
			
				if(check_down && block_count < block_num)
				Output_BODY(row, col, score);
				else if(check_down && block_count == block_num)
				Output_TAIL(row, col, score);
				else break;
			}
		
		}
		score = Score_count(canvas, score);
		block_count ++;
		system("CLS");
		printf("结束\n");
	}
	printf("block_count = %d\n",block_count);
	
	
	
	
	return;
}

void Hide_cursor(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);   //隐藏光标 
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	return;
}

int main(){
	
	FILE *fp = NULL;
	Hide_cursor();
	
	
	for(int r = 0; r < ca_ROW; r ++)
	for(int c = 0; c < ca_COL; c ++)
	canvas[r][c] = ' ';
	
	for(int c = 0; c < ca_COL; c ++)
	canvas[ca_ROW][c] = '*';
	
	for(int r = 0; r < bl_NUM; r ++)
	for(int c = 0; c < bl_NUM; c ++)
	block[r][c] = '*';
	
	
	
	
	
    Initialize();
	
	Prepare();
	
	Start();
	
	fclose(fp);
	
	return 0;	
}
