#include "utils.h"
#include <switch.h>

bool CreateDummyFile(const char* fname)
{
	FILE* f = fopen(fname, "w");
	if (f)
	{
		fwrite(".", 1, 1, f);
		fclose(f);
		return true;
	}
	return false;
}

bool FileExists(const char* fname)
{
	FILE* f = fopen(fname, "rb");
	if (f)
	{
		fclose(f);
		return true;
	}
	return false;
}

int ConnectToSysmodule()
{
	int sockfd;
	struct sockaddr_in servaddr = { 0 };

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return ERR_SOCK;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(6668);

	struct timeval tv;
	tv.tv_sec = 8;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

	if (connect(sockfd, (struct sockaddr*) & servaddr, sizeof(servaddr)) != 0)
		return ERR_CONNECT;

	return sockfd;
}

const u64 kHelper[] = { BIT(13),BIT(13) ,BIT(15) ,BIT(15), BIT(12), BIT(14), BIT(12), BIT(14) , BIT(1), BIT(0) };
u8 KhlpIndex = 0;
u8 KhlpMax = sizeof(kHelper) / sizeof(kHelper[0]);

const char* const ConsoleColors[] =
{
	"\033[0;34;44m"	"\333",
	"\033[1;37;47m"	"\333",
	"\033[0;30;40m"	"\333",
	"\033[1;37;47m"	"\333",
	"\033[1;35;45m"	"\333",
	"\033[1;31;41m"	"\333",
	"\033[1;31;41m"	"\333",
	"\033[0;33;43m"	"\333",
	"\033[1;33;43m"	"\333",
	"\033[1;32;42m"	"\333",
	"\033[1;34;44m"	"\333",
	"\033[0;34;44m"	"\333",
	"\033[1;30;40m"	"\333",
	"\033[1;35;45m"	"\333",
};

void PrintBuffer(const char *buf) {
	printf("\x1b[9;0H\x1b[0J");
	for (int i = 0; i < strlen(buf); i++)
		printf("%s", buf[i] == '\n' ? "\n" : ConsoleColors[buf[i] - '0']);
	consoleUpdate(NULL);
	do hidScanInput();
	while (!hidKeysDown(CONTROLLER_P1_AUTO));
	printf("\x1b[0m\x1b[9;0H\x1b[0J");
}

const char H264_testBuf[] = {
	0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30 ,0x0A,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x32,0x32,
	0x32,0x32,0x32,0x32 ,0x32,0x32,0x32,0x32 ,0x32,0x32,0x32,0x32 ,0x32,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x30,0x0A,0x30,0x30 ,0x36,0x36,0x36,0x36,
	0x36,0x36,0x36,0x36 ,0x30,0x30,0x30,0x30 ,0x30,0x30,0x30,0x30 ,0x36,0x36,0x36,0x36,
	0x36,0x36,0x32,0x33 ,0x33,0x33,0x33,0x33 ,0x33,0x33,0x33,0x33 ,0x33,0x33,0x33,0x33,
	0x33,0x33,0x32,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x0A,0x36,
	0x36,0x36,0x36,0x36, 0x36,0x36,0x36,0x36, 0x36,0x36,0x36,0x36, 0x36,0x36,0x36,0x36,
	0x36,0x36,0x36,0x36, 0x36,0x36,0x32,0x33, 0x33,0x33,0x34,0x34, 0x34,0x34,0x34,0x34,
	0x34,0x34,0x34,0x34, 0x34,0x33,0x33,0x33, 0x32,0x30,0x30,0x30, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x0A, 0x36,0x36,0x37,0x37, 0x37,0x37,0x37,0x37, 0x37,0x37,0x36,0x36,
	0x36,0x36,0x36,0x36, 0x36,0x36,0x37,0x37, 0x37,0x37,0x37,0x32, 0x33,0x33,0x34,0x34,
	0x34,0x34,0x34,0x35, 0x34,0x34,0x35,0x34, 0x34,0x34,0x34,0x33, 0x33,0x32,0x30,0x30,
	0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x0A,0x37,0x37,0x37, 0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37,
	0x32,0x33,0x34,0x34, 0x35,0x34,0x34,0x34, 0x34,0x34,0x34,0x32, 0x32,0x34,0x35,0x34,
	0x34,0x33,0x32,0x30, 0x32,0x32,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x0A,0x37,0x37,
	0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37, 0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37, 0x37,0x32,0x33,0x34, 0x34,0x34,0x34,0x34, 0x34,0x34,0x34,0x32,
	0x3C,0x3C,0x32,0x34, 0x34,0x34,0x33,0x32, 0x32,0x3C,0x3C,0x32, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x0A,0x37, 0x37,0x38,0x38,0x38, 0x38,0x38,0x38,0x38, 0x38,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37, 0x37,0x32,0x32,0x32, 0x38,0x38,0x32,0x33, 0x34,0x34,0x34,0x34,
	0x34,0x35,0x34,0x34, 0x32,0x3C,0x3C,0x3C, 0x34,0x34,0x34,0x33, 0x32,0x3C,0x3C,0x3C,
	0x32,0x30,0x30,0x30, 0x30,0x30,0x30,0x0A, 0x38,0x38,0x38,0x38, 0x38,0x38,0x38,0x38,
	0x38,0x38,0x38,0x38, 0x38,0x38,0x38,0x38, 0x38,0x38,0x3C,0x3C, 0x32,0x32,0x38,0x32,
	0x33,0x34,0x34,0x34, 0x34,0x34,0x34,0x34, 0x34,0x32,0x3C,0x3C, 0x3C,0x32,0x32,0x32,
	0x32,0x3C,0x3C,0x3C, 0x3C,0x32,0x30,0x30, 0x30,0x30,0x30,0x30, 0x0A,0x38,0x38,0x38,
	0x38,0x38,0x38,0x38, 0x38,0x38,0x38,0x38, 0x38,0x38,0x38,0x38, 0x38,0x38,0x38,0x32,
	0x3C,0x3C,0x32,0x32, 0x32,0x33,0x34,0x34, 0x34,0x34,0x34,0x34, 0x34,0x34,0x32,0x3C,
	0x3C,0x3C,0x3C,0x3C, 0x3C,0x3C,0x3C,0x3C, 0x3C,0x3C,0x32,0x30, 0x30,0x30,0x30,0x30,
	0x30,0x0A,0x38,0x38, 0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39, 0x38,0x38,0x38,0x38,
	0x38,0x38,0x38,0x38, 0x32,0x32,0x3C,0x3C, 0x32,0x32,0x33,0x34, 0x34,0x34,0x34,0x34,
	0x34,0x35,0x32,0x3C, 0x3C,0x3C,0x3C,0x3C, 0x3C,0x3C,0x3C,0x3C, 0x3C,0x3C,0x3C,0x3C,
	0x32,0x30,0x30,0x30, 0x30,0x30,0x0A,0x39, 0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39,
	0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39, 0x39,0x39,0x32,0x32, 0x3C,0x3C,0x32,0x33,
	0x34,0x35,0x34,0x34, 0x34,0x34,0x34,0x32, 0x3C,0x3C,0x3C,0x31, 0x32,0x3C,0x3C,0x3C,
	0x3C,0x31,0x32,0x3C, 0x3C,0x32,0x30,0x30, 0x30,0x30,0x30,0x0A, 0x39,0x39,0x39,0x39,
	0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39, 0x39,0x39,0x39,0x39,
	0x32,0x32,0x32,0x32, 0x33,0x34,0x34,0x34, 0x34,0x34,0x34,0x34, 0x32,0x3C,0x3C,0x3C,
	0x32,0x32,0x3C,0x3C, 0x32,0x3C,0x32,0x32, 0x3C,0x3C,0x32,0x30, 0x30,0x30,0x30,0x30,
	0x0A,0x39,0x39,0x3A, 0x3A,0x3A,0x3A,0x3A, 0x3A,0x3A,0x3A,0x39, 0x39,0x39,0x39,0x39,
	0x39,0x39,0x39,0x3A, 0x3A,0x3A,0x3A,0x32, 0x32,0x33,0x33,0x34, 0x34,0x34,0x35,0x34,
	0x34,0x32,0x3C,0x3D, 0x3D,0x3C,0x3C,0x3C, 0x3C,0x3C,0x3C,0x3C, 0x3C,0x3D,0x3D,0x32,
	0x30,0x30,0x30,0x30, 0x30,0x0A,0x3A,0x3A, 0x3A,0x3A,0x3A,0x3A, 0x3A,0x3A,0x3A,0x3A,
	0x3A,0x3A,0x3A,0x3A, 0x3A,0x3A,0x3A,0x3A, 0x3A,0x3A,0x3A,0x3A, 0x3A,0x32,0x33,0x33,
	0x33,0x34,0x34,0x34, 0x34,0x34,0x34,0x32, 0x3C,0x3C,0x3C,0x32, 0x32,0x32,0x32,0x32,
	0x32,0x3C,0x3C,0x32, 0x30,0x30,0x30,0x30, 0x30,0x30,0x0A,0x3A, 0x3A,0x3B,0x3B,0x3B,
	0x3B,0x3B,0x3B,0x3B, 0x3B,0x31,0x3A,0x3A, 0x3A,0x3A,0x3A,0x3A, 0x3A,0x3B,0x3B,0x3B,
	0x3B,0x32,0x32,0x32, 0x33,0x33,0x33,0x33, 0x33,0x33,0x33,0x33, 0x33,0x32,0x3C,0x3C,
	0x3C,0x3C,0x3C,0x3C, 0x3C,0x3C,0x3C,0x32, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x0A,
	0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B,
	0x3B,0x3B,0x3B,0x3B, 0x3B,0x32,0x3C,0x3C, 0x3C,0x32,0x32,0x32, 0x32,0x32,0x32,0x32,
	0x32,0x32,0x32,0x32, 0x32,0x32,0x32,0x32, 0x32,0x32,0x32,0x32, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30, 0x0A,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B,
	0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x3B,0x3B, 0x3B,0x3B,0x32,0x3C, 0x3C,0x32,0x32,0x30,
	0x32,0x3C,0x32,0x30, 0x30,0x30,0x30,0x30, 0x32,0x3C,0x32,0x30, 0x32,0x3C,0x3C,0x32,
	0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x0A,0x3B,0x3B, 0x30,0x30,0x30,0x30,
	0x30,0x31,0x30,0x30, 0x3B,0x3B,0x3B,0x31, 0x3B,0x3B,0x3B,0x3B, 0x30,0x30,0x30,0x32,
	0x32,0x32,0x32,0x30, 0x30,0x32,0x32,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x32,0x32,
	0x30,0x30,0x32,0x32, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x0A,0x30,
	0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30, 0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x0A
};
	