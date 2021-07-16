#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <windows.h>
#include <winreg.h>

#define STR_LENGTH 4096

int main(int argc, char* argv[])
{
	FILE* f;
	HKEY r;
	UINT32 i = 0, to = 0x6E9D6F;
	long t, x, p, uc;
	size_t sz = 6;
	char out[6] = { 0xE9,0x9D,0x00,0x00,0x00,0x90 };
	char old[6] = { 0x0F,0x85,0x9C,0x00,0x00,0x00 };
	char buf[6];
	char s1[STR_LENGTH];
	char* s2;
	char* s3;
	char s4[STR_LENGTH];
	x = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\EA GAMES\\The Sims 2 Mansion and Garden Stuff", 0, KEY_QUERY_VALUE, &r);
	if (x != 0)
	{
		x = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\EA GAMES\\The Sims 2", 0, KEY_QUERY_VALUE, &r);
		uc = 1;
	}
	if (x == 0) {
		p = STR_LENGTH;
		if (uc == 1)
		{
			x = RegQueryValueEx(r, "Folder", 0, (LPDWORD)&t, (LPBYTE)s1, (LPDWORD)&p);
			if (x == 0 && t == REG_SZ) i = 1;
			RegCloseKey(r);
		}
		else
		{
			x = RegQueryValueEx(r, "Install Dir", 0, (LPDWORD)&t, (LPBYTE)s1, (LPDWORD)&p);
			if (x == 0 && t == REG_SZ) i = 1;
			RegCloseKey(r);
		}
	}

	int buffSize = GetCurrentDirectory(0, NULL);
	GetCurrentDirectory(buffSize, s4);
	strcat(s4, "\\Sims2EP9.exe");
	f = fopen(s4, "rb+");
	if (i > 0 && f == NULL) {
		if (uc == 1)
			s2 = strcat(s1, "Fun with Pets\\SP9\\TSBin\\Sims2EP9.exe");
		else
			s2 = strcat(s1, "TSBin\\Sims2EP9.exe");
		f = fopen(s2, "rb+");
	}
		if (f != NULL) {
			fseek(f, to, 0);
			fread(buf, 1, sz, f);
			x = 0;
			for (i = 0; i < sz; i++) {
				if (buf[i] != old[i]) x = 1;
			}
			if (x == 0) {
				fseek(f, to, 0);
				fwrite(out, 1, sz, f);
				printf("thumb4: file is patched\n");
			}
			else {
				printf("thumb4: file data does not match\n");
			}
			fclose(f);
		}
		else {
			printf("thumb4: file failed to open\n");
		}
		/*
	else {
		printf("thumb4: requires Sims 2 with the no-CD version of M&G\n");
	}*/
	system("PAUSE");
	return 0;
}
