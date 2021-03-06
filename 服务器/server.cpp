
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "server.h"
#include <iostream>


using std::cout;
using std::string;


ClientInformation GameServer::AcceptSocket[GameServer::MAX_NUM];
/*
名称：构造函数
描述：用于Socket初始化
*/

GameServer::GameServer()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)   //判断一下有没有这个版本
	{
		cout << "无法加载套接字协议栈.\n";
		fflush(stdout);
		return;
	}

	//设置监听套接字
	ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4 STREAM TCP

	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "套接字初始化错误，错误号：" << WSAGetLastError() << "\n";
		fflush(stdout);
		return;
	}

	int port = 8888;

	//设置服务器的信息
	Server.sin_family = PF_INET;
	Server.sin_port = htons(port);
	Server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int errorNum;
	//绑定
	bind(ListenSocket, (LPSOCKADDR)& Server, sizeof(Server));
	while ((errorNum = WSAGetLastError()) == 10048)
	{
		port++;
		Server.sin_port = htons(port);
		int retval = bind(ListenSocket, (LPSOCKADDR)& Server, sizeof(Server));
		cout << "绑定错误，错误号10048\n";
		fflush(stdout);

	}
	cout << "服务器IP:" << Server.sin_addr.S_un.S_addr
		<< " 端口号: " << port << "\n";
	fflush(stdout);
	//监听   有listen就有accept
	if (listen(ListenSocket, 5) == SOCKET_ERROR)
	{
		cout << "监听出错，错误号：" << WSAGetLastError() << "\n";
		fflush(stdout);
		return;
	}

	//将所有信息初始化
	for (int i = 0; i < MAX_NUM; i++)
		AcceptSocket[i].clientSock = INVALID_SOCKET;

	cout << "网络初始化成功\n";
	fflush(stdout);
	return;
}

/*
名称：析构函数
作用：用于资源释放
*/
GameServer::~GameServer()
{
	if (ListenSocket != INVALID_SOCKET)
		closesocket(ListenSocket);
	cout << "服务器关闭\n";
	fflush(stdout);
	WSACleanup();
	return;
}


/*
名称：检测ID
描述：用于检测当前没有用的ID号
*/
int GameServer::CheckSocket()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (AcceptSocket[i].clientSock == INVALID_SOCKET)
			return i;
	}
	return -1;
}

/*
名称：线程处理
描述：为每一个新玩家创建一个接受线程
	  如果人数达到上限，就拒绝
*/
int GameServer::ProcessGameServer()
{
	while (true)
	{
		int index = CheckSocket();
		sockaddr_in Client;

		int ClntLen = sizeof(Client);

		if (index != -1) //玩家未满
		{

			//对应前面的listen，这里是对应操作accept

			cout << "等待Client连接...\n";
			fflush(stdout);
			AcceptSocket[index].clientSock = accept(
				ListenSocket,
				(struct sockaddr*) & AcceptSocket[index].Client,
				&ClntLen);
			//cout << "#1 AcceptSocket[index].ClientSock: " << AcceptSocket[index].ClientSock << "\n";
			AcceptSocket[index].ID = index;       //记录这个Client的ID啊，以后要寻找它
			AcceptSocket[index].Active = false;

			if (AcceptSocket[index].clientSock == INVALID_SOCKET)
			{
				cout << "连接错误\n";
				fflush(stdout);
				break;
			}
			//cout << "#2 AcceptSocket[index].ClientSock: " << AcceptSocket[index].ClientSock << "\n";
			cout << "连接成功\n";
			fflush(stdout);
			//至此client与server连接成功,欢呼

			cout << "新玩家加入，IP地址：" << inet_ntoa(AcceptSocket[index].Client.sin_addr)
				<< "  端口号：" << ntohs(AcceptSocket[index].Client.sin_port) << "\n";
			fflush(stdout);
			//创建接受者线程
			int ThreadID;     //线程ID

			//把刚刚连接成功的Client建立一个新的线程
			ThreadID = (int)CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE)(GameServer::ListenThread), //线程点函数
				(LPVOID)& AcceptSocket[index], 0,              //参数
				&AcceptSocket[index].RecvThreadID          //系统分配的ID
			);

			if (!ThreadID)
			{
				cout << "创建线程错误\n";
				fflush(stdout);
				ExitThread(AcceptSocket[index].RecvThreadID);
			}

			//至此，新的线程创建成功，可以传输数据了

			cout << "新玩家" << index << "的接受线程创建成功\n";
			fflush(stdout);
		}
		else   //玩家已满
		{
			SOCKET Accept = accept(ListenSocket,
				(struct sockaddr*) & Client, &ClntLen);

			if (Accept == INVALID_SOCKET)
			{
				cout << "连接错误\n";
				fflush(stdout);
				break;
			}


			cout << "非法请求的玩家的IP的地址为:" << inet_ntoa(Client.sin_addr)
				<< " 端口号为 :" << ntohs(Client.sin_port) << "\n";
			fflush(stdout);
			send(Accept, "当前用户已满", strlen("当前用户已满") + sizeof(char), 0);

			closesocket(Accept);

			cout << "非法连接玩家已断开\n";
			fflush(stdout);
			break;
		}
	}

	return 0;
}

/*
名称：接受线程
描述：Select模式
	首先判断该线程是否可读，如果可读就读取其上的信息
*/
DWORD WINAPI GameServer::ListenThread(void* data) //传进来具体哪个AcceptSocket[xx]的地址
{

	ClientInformation* GameSocket = (ClientInformation*)data;

	while (true)
	{

		fflush(stdout);

		//接收命令 

		char recvBuf[1024];
		//		char recvBuf[40];
		fflush(stdout);

		fd_set Read;//基于select模式对IO进行管理  

		fflush(stdout);

		FD_ZERO(&Read);    //初始化为0
		FD_SET(GameSocket->clientSock, &Read); //将ClientSock加入队列

		fflush(stdout);

		//we only care read
		select(0, &Read, NULL, NULL, NULL);

		fflush(stdout);

		if (FD_ISSET(GameSocket->clientSock, &Read))
		{
			//接受客户端的数据
			int result = recv(GameSocket->clientSock, recvBuf, sizeof(recvBuf), 0);
			//cout << "recv 返回值: " << result << "\n";
			fflush(stdout);
			if (result > 0)
			{
				recvBuf[result] = 0;
				cout << "玩家" << GameSocket->ID << "发送了消息:"
					<< recvBuf << "\n";
				fflush(stdout);
			}
		}

		//发送命令 
		char sendBuf[1024];
		//		char sendBuf[40];
		fd_set write;//基于select模式对IO进行管理  
		FD_ZERO(&write);    //初始化为0
		FD_SET(GameSocket->clientSock, &write); //将ClientSock加入队列
		//we only care read
		select(0, NULL, &write, NULL, NULL);

		if (FD_ISSET(GameSocket->clientSock, &write))
		{
			//接受客户端的数据复制到
			strcpy(sendBuf, recvBuf);
			//cout << "Just Before Enter TOALL func, AcceptSocket[ID].ClientSock: " << GameSocket->ClientSock << "\n";
			SendMessageToAllClient(sendBuf, GameSocket->ID);
		}

	}
	return 1;
}

/*
名称：发送信息给一个client
描述：发送信息给一个client
*/
int GameServer::SendMessageToOneClient(int ID, const string  str)
{
	if (ID < 0)
		return 0;

	int oneSend = send(AcceptSocket[ID].clientSock,
		str.c_str(), str.length() + sizeof(char), 0);
	cout << "向玩家" << ID << "发送了" << oneSend << "个bits的消息\n";
	fflush(stdout);
	if (oneSend == SOCKET_ERROR)
	{
		cout << "向玩家" << ID << "发送消息失败\n";
		fflush(stdout);
		return 0;
	}

	return 1;
}

/*
名称：全发送
描述：给所有Client发送信息
*/
void GameServer::SendMessageToAllClient(const string  str, int ID)
{

	bool flag = true;
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (ID != i)/////////////////////////////////////////////////////////////////////////////////////////////////////////

		{
			if (AcceptSocket[i].clientSock != INVALID_SOCKET &&
				!SendMessageToOneClient(i, str))
				flag = false;
		}
	}
	if (flag) {
		cout << "服务器向全体(除了玩家" << ID << ")发送了消息:"
			<< str << "\n";
	}
	else {
		cout << "发送存在问题\n";
	}
	fflush(stdout);
}

/*
名称：清理Socket
描述：清理退出游戏的线程
*/
void GameServer::CleanSocket(int ID)
{
	if (ID < 0)
		return;

	char send[20];
	sprintf(send, "#DD i%d*", ID);
	SendMessageToAllClient(send, ID);


	cout << " 玩家" << ID << "退出游戏\n";
	fflush(stdout);

	AcceptSocket[ID].Active = false;
	closesocket(AcceptSocket[ID].clientSock);
	AcceptSocket[ID].clientSock = INVALID_SOCKET;

	cout << "正在关闭其接受线程:" << AcceptSocket[ID].RecvThreadID << "\n";
	fflush(stdout);
	ExitThread(AcceptSocket[ID].RecvThreadID);



	cout << "关闭成功!\n";
	fflush(stdout);
}