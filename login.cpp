/*
代码说明：
login.cpp文件内容为VIP登录代码，头文件部分请自行补全
为防止用户信息泄露，我们将用户登录账号与密码的判定使用一个函数 getdata() 代替，请直接使用下面测试文件进行编译
任务：进行登录窗口美化，请使用WinAPI进行页面重构，并请保证能正确实现登录

请先Fork本项目，修改代码后再创建一个Pull Request，正式开发组成员将对其进行审核并讨论，也可能会Request Changes
开发组成员审查完毕后，会@code004Accepted进行复查，code004Accepted将把相关代码直接应用到GC Server的实际代码中进行测试
如果任务完成成功，将会成为正式开发组成员并会将用户名记录在新版本的关于窗口；如果滥用PR和Issue进行捣乱，将会考虑踢出开发组
GC Server开发组欢迎您的加入！
*/

//测试程序专用 getdata()
int getdata(char username[],string inputpass)
{
	return 1;
}
int log()
{
	closegraph();
	system("cls");
	char username[10000] = { '\0' };
	namereg = false;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\n\n\n\n\n");
	printf("                                   +=============GC Server-VIP Login=============+\n");
	printf("                                   | 账号 Username:                              |\n");
	printf("                                   |---------------------------------------------|\n");
	printf("                                   | 密码 Password:                              |\n");
	printf("                                   +=============================================+\n");
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("                                             如需退出请在账号栏中输入exit\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("                                             免费体验账号:test 密码:test");
	gotoxy(52, 6);
	scanf("%s", username);
	if (strcmp(username, "exit") == 0)
	{
		return -1;
	}
	string config;
	gotoxy(52, 8);
	char ch = 0;
	int chcnt = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch == '\b')
		{
			cout << ch;
			cout << ' ';
			cout << ch;
			if (!(config.empty()) != 0)
			{
				config.erase(config.size() - 1, 1);
			}
			if (chcnt <= 0)
			{
				cout << '\a';
				cout << ' ';
				chcnt++;
				config.erase();
			}
			chcnt--;
		}
		else
		{
			if (isprint(ch) != 0)
			{
				config += ch;
				cout << '*';
				chcnt++;
			}
		}
	}
	system("cls");
	getdata(username,config);
  return 1;
}
int main()
{
  printf("\n\n\t\tLogin Testing Program - GC Server Beta\n\n\t\tDevelopers Only\n");
  Sleep(1500);
  log();
}
