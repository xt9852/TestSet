#ifndef __MB_FILE_IO_H
#define __MB_FILE_IO_H

//#pragma warning(disable : 4244)
//#pragma warning(disable : 4312)

#define MB_OPEN_MODE_READING 0
#define MB_OPEN_MODE_WRITING 1

typedef void *(*mb_file_open_t)(const char *path, int mode);
typedef int (*mb_file_close_t)(void *file);
typedef int64_t (*mb_file_read_t)(void *file, void *buffer, int64_t bytes);
typedef int64_t (*mb_file_write_t)(void *file, const void *buffer,
                                   int64_t bytes);
typedef int64_t (*mb_file_tell_t)(void *file);
typedef int64_t (*mb_file_seek_t)(void *file, int64_t offset, int whence);

typedef struct {
  mb_file_open_t open;
  mb_file_close_t close;
  mb_file_read_t read;
  mb_file_write_t write;
  mb_file_tell_t tell;
  mb_file_seek_t seek;
} mb_file_io_t;

extern mb_file_io_t std_mb_file_io;

#endif /* __MB_FILE_IO */
