
#pragma once
#include "MySQL/mysql.h"
#include <vector>
#include <string>

typedef std::vector<std::string> VECTOR_STR;




/**
 *\class  CMySQLDB
 *\brief  该类主要是MySQL类
 *\date   2012-07-03
 *\author 张海涛
 *\par    Revision History:
 *\n      0.1     2007-07-03   张海涛   创建此类
 */
class CMySQLDB
{
public:
	/**
	 *\fn         CMySQLDB()
	 *\brief      缺省构造函数。
	 */
	CMySQLDB();

	/**
	 *\fn         ~CMySQLDB()
	 *\brief      析构函数。
	 */
	~CMySQLDB();

protected:
	MYSQL			mysql_;	  // MySQL对象
    int				nextSet_; // 下一次设置字符集时间
    int				timeout_; // 超时时间

public:
	/**
	 *\fn         OpenDB(const char *host, unsigned short port, const char *name, const char *username, const char *password)
	 *\brief      打开数据库
	 *\param[in]  host		主机地址。
	 *\param[in]  port		主机端口。
	 *\param[in]  name		数据库名。
	 *\param[in]  username	用户名。
	 *\param[in]  password	用户密码。
	 *\return     是否成功(0成功，其它失败)
	 */
	int OpenDB(const char *host, unsigned short port, const char *name, const char *username, const char *password);	
	
	/**
	 *\fn         Close()
	 *\brief      关闭数据库
	 */
	void Close();	

	/**
	 *\fn         Exec(const char *sql)
	 *\brief      执行SQL语句
	 *\param[in]  sql		SQL语句。
	 *\return     是否成功
	 */
	bool Exec(const char *sql);
	
	/**
	 *\fn         Procedure(const char *name, const char *param, ...)
	 *\brief      调用存储过程
	 *\param[in]  name		存储过程名。
	 *\param[in]  param		存储过程参数。
	 *\return     是否成功
	 */
	bool Procedure(const char *name, const char *param, ...);

	/**
	 *\fn         InsertBlob(const char *tableName, const char *fieldName, char *data, int len)
	 *\brief      向数据表中插入BLOB二进制数据,如果数据大于1M则需要设置 max_allowed_packet 变量
	 *\param[in]  tableName		表名。
	 *\param[in]  fieldName		字段名。
	 *\param[in]  data			数据。
	 *\param[in]  len			数据长。
	 *\return     是否成功
	 */
	bool InsertBlob(const char *tableName, const char *fieldName, char *data, int len);
	
	/**
	 *\fn         GetBlob(const char *tableName, const char *fieldName, char *data, int len)
	 *\brief      从数据表中得到BLOB二进制数据
	 *\param[in]  tableName		表名。
	 *\param[in]  fieldName		字段名。
	 *\param[in]  data			数据。
	 *\param[in]  len			数据长。
	 *\return     是否成功
	 */
	bool GetBlob(const char *tableName, const char *fieldName, char *data, int &len);

	/**
	 *\fn         GetWaitTimeout()
	 *\brief      得到等待超时值
	 *\return     超时值
	 */
    int GetWaitTimeout();
	
	/**
	 *\fn         GetData(VECTOR_STR &data, int &rows, int &fields)
	 *\brief      得到数据
	 *\param[out] data		数据。
	 *\param[out] rows		记录行数。
	 *\param[out] fields	字段个数。
	 *\return     是否成功
	 */
	bool GetData(VECTOR_STR &data, int &rows, int &fields);

	/**
	 *\fn         GetDataStr()
	 *\brief      得到SELECT后的数据
	 *\return     字符串数据
	 */
	std::string GetDataStr();
};

