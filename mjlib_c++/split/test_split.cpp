#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include "split.h"

using namespace std;

void print_cards(char* cards)
{
	for (int i = 0; i<9; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");

	for (int i = 9; i<18; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");
	for (int i = 18; i<27; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("  ");
	for (int i = 27; i<34; ++i)
	{
		printf("%d,", cards[i]);
	}
	printf("\n");
}

#define MAX_COUNT (80000 * 10000)
static BYTE s_HuCardAll[136];

void test_split()
{
	char cards[] = {
		0,1,1,0,0,0,0,1,0,
		1,1,0,1,0,4,1,1,1,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,2
	};
	int hu = 0;
	DWORD dwTimeBegin = GetTickCount();
	//for (int i = 0; i < MAX_COUNT; i++){
		hu += split::get_hu_info(cards, 34, 33);
	//}

	cout << "拆分法，相同牌型，总次数: " << MAX_COUNT / 10000 << "万次" << endl;
	cout << "time: " << GetTickCount() - dwTimeBegin << "ms" << endl;
	cout << "hu:" << hu <<endl;
}

void main()
{
	test_split();
	return;
	for (int i = 0; i < 34; i++)
	{
		s_HuCardAll[i * 4] = i;
		s_HuCardAll[i * 4 + 1] = i;
		s_HuCardAll[i * 4 + 2] = i;
		s_HuCardAll[i * 4 + 3] = i;
	}

	int hu = 0;
	char cards[34] = { 0 };
	// 纯随机跑10000*9次，每次将第一个牌值设为赖子
	srand(1);
	DWORD dwTimeBegin = clock();
	for (int n = 0; n<MAX_COUNT; ++n)
	{
		random_shuffle(s_HuCardAll, s_HuCardAll + 126);		// 这个函数对计算有影响
		for (int i = 0; i<9; ++i)	// 136/14 -> 9
		{
			memset(cards, 0, sizeof(cards));
			for (int j = i * 14; j < i * 14 + 12; j++)
				++cards[s_HuCardAll[j]];

			cards[33] = 2;
			hu += split::get_hu_info(cards, 34, 33);
		}
	}
	cout << "拆分法，总次数: " << MAX_COUNT*9/10000 <<"万次"<< endl;
	cout <<"time: " << clock() - dwTimeBegin << "ms" << endl;
	cout << "Hu: " << hu << endl;
	cin >> hu;
}
