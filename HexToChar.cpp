// HexToChar.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>

#define	BUFFSIZE	64

int main(int argc, char* argv[])
{
	const char* in_filename = argv[1];
	const char* out_filename = argv[2];

	FILE* in_fp = fopen(in_filename, "rb");
	if (in_fp == NULL)
	{
		printf("%s open fail\n", in_filename);
		return -1;
	}
	
	FILE* out_fp = fopen(out_filename, "wb");
	if (out_fp == NULL)
	{
		printf("%s open fail\n", out_filename);
		return -1;
	}

	unsigned char* buf = new unsigned char[BUFFSIZE];
	unsigned char* out_buf = new unsigned char[2*BUFFSIZE];

	while (true)
	{
		size_t num = fread(buf, 1, BUFFSIZE, in_fp);
		if (num == 0)
		{
			break;
		}
		else
		{
			for(size_t i = 0; i < num; i++)
			{
				unsigned char high = (buf[i] & 0xf0) >> 4;
				if (high <= 0x09)
				{
					out_buf[2 * i] = high + '0';
				}
				else
				{
					out_buf[2 * i] = high - 0x0A + 'A';
				}

				unsigned char low = buf[i] & 0x0f;
				if (low <= 0x09)
				{
					out_buf[2 * i + 1] = low + '0';
				}
				else
				{
					out_buf[2 * i + 1] = low - 0x0A + 'A';
				}
			}

			fwrite(out_buf, 1, 2 * num, out_fp);
		//	fwrite("\r\n", 2, 1, out_fp);

		}
	}

	delete[] buf;
	delete[] out_buf;
	_CrtDumpMemoryLeaks();
	return 0;
}
