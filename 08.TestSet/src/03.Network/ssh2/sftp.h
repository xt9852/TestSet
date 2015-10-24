/*
 * Sample showing how to do SFTP write transfers.
 *
 * The sample code has default values for host name, user name, password
 * and path to copy, but you can specify them on the command line like:
 *
 * "sftp 192.168.0.1 user password sftp_write.c /tmp/secrets"
 */

#ifndef TESTSET_SFTP
#define TESTSET_SFTP

struct _tag_my_ssh_param;
typedef struct _tag_my_ssh_param my_ssh_param, *p_my_ssh_param;

/**
 *\fn        void sftp_thread_func(p_my_ssh_param param)
 *\brief     ssh主线程
 *\param[in] p_my_ssh_param param p_my_ssh_param
 *\return    void 0成功,其它失败
 */
void sftp_thread_func(void *param);

/**
 *\fn        int sftp_make_dir(my_ssh_param *param, const char *dir)
 *\brief     创建目录
 *\param[in] my_ssh_param * param sftp连接
 *\param[in] const char * dir 目录
 *\return    int 0成功,其它失败
 */
int sftp_make_dir(my_ssh_param *param, const char *dir);

/**
 *\fn           int sftp_rm_dir(my_ssh_param *param, const char *dir)
 *\brief        删除目录
 *\param[in]    my_ssh_param * param sftp连接
 *\param[in]    const char * dir 目录
 *\return       int 0成功,其它失败
 */
int sftp_rm_dir(my_ssh_param *param, const char *dir);

/**
 *\fn           int sftp_rm(my_ssh_param *param, const char *filename)
 *\brief        删除文件
 *\param[in]    my_ssh_param * param sftp连接
 *\param[in]    const char * filename 文件名
 *\return       int 0成功,其它失败
 */
int sftp_rm(my_ssh_param *param, const char *filename);

/**
 *\fn        int sftp_get_dir(my_ssh_param *param, const char *path, char *dir, int dir_max_len)
 *\brief     得到目录结构
 *\param[in] my_ssh_param * param sftp连接
 *\param[in] const char * path 远程路径
 *\param[in] char * dir 目录结构, 文件或目录名长(1Byte),文件或目录类型(1Byte),文件或目录名
 *\param[in] int dir_max_len 目录结构缓冲区长
 *\return    int 0成功,其它失败
 */
int sftp_get_dir(my_ssh_param *param, const char *path, char *dir, int dir_max_len);

/**
 *\fn        int sftp_rename(my_ssh_param *param, const char *sourcefile, const char *destfile)
 *\brief     重命名文件
 *\param[in] my_ssh_param * param sftp连接
 *\param[in] const char * sourcefile 源文件
 *\param[in] const char * destfile 目标文件
 *\return    int 0成功,其它失败
 */
int sftp_rename(my_ssh_param *param, const char *sourcefile, const char *destfile);

/**
 *\fn           int sftp_get_link_path(my_ssh_param *param, const char *link, char *path, int path_max_len)
 *\brief        得到连接的目标路径
 *\param[in]    my_ssh_param * param sftp连接
 *\param[in]    const char * link 连接文件路径
 *\param[out]   char * path 目标路径
 *\param[in]    int path_max_len 目标路径最大长度
 *\return       int 0-文件连接,1-目录连接
 */
int sftp_get_link_path(my_ssh_param *param, const char *link, char *path, int path_max_len);

/**
 *\fn        int sftp_upload_file(my_ssh_param *param, const char *localFilename, 
                                  const char *remoteFilename)
 *\brief     上传文件
 *\param[in] my_ssh_param * param sftp连接
 *\param[in] const char * localFilename 本地文件名
 *\param[in] const char * remoteFilename 远程文件名
 *\return    int 0成功,其它失败
 */
int sftp_upload_file(my_ssh_param *param, const char *localFilename, const char *remoteFilename);

/**
 *\fn        int sftp_download_file(my_ssh_param *param, const char *localFilename, 
                                    const char *remoteFilename)
 *\brief     下载文件
 *\param[in] my_ssh_param * param sftp连接
 *\param[in] const char * localFilename 本地文件名
 *\param[in] const char * remoteFilename 远程文件名
 *\return    int 0成功,其它失败
 */
int sftp_download_file(my_ssh_param *param, const char *localFilename, const char *remoteFilename);

#endif
