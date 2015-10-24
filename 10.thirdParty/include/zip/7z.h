#ifndef __7Z_LIB_H__
#define __7Z_LIB_H__


//#pragma comment(lib, "../lib/7zip/7z.lib")

int __cdecl create7z(const char *filename_7z, int file_count, const char *files[]);
int __cdecl create_7z(const char *filename_7z, int file_count, ...);
int __cdecl exclude_7z(const char *filename_7z, const char *dir);


#endif
