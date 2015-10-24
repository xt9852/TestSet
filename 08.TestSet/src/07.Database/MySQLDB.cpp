
#include "stdafx.h"
#include "MySQLDB.h"

#pragma comment(lib,"../10.thirdParty/lib/mysql/libmysql.lib")

/**
	// SqlServer
	// Command对象在进行存储过程的调用中能真正体现它的作用
	m_pCommand.CreateInstance("ADODB.Command");
	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;									// 定义为无参数
	m_pCommand->ActiveConnection = m_pConnection;						// 非常关键的一句，将建立的连接赋值给它
	m_pCommand->CommandText = "SELECT * FROM users";					// 命令字串
	m_pRecordset = m_pCommand- >Execute(&vNULL, &vNULL, adCmdText);		// 执行命令，取得记录集
	
	m_pRecordset->Update();												// 对记录集做修改，保存回库中

	exec pr_checkuservip @username='123123'								// 调用存储过程,存储过程定义的变量@username


	// MySQL
	// 符加包含目录：	D:\Program Files\MySQL\MySQL Server 5.0\include
	// 符加库目录：		D:\Program Files\MySQL\MySQL Server 5.0\lib\opt
	// 符加依赖项：		libmysql.dll
	show grants for user					// 显示user的权限
	show global variables,show variables	// 显示变量
	set  collation_connection = gbk_bin;	// 设置变量
	flush privileges						// 显示权限

	// 只要charactor set database 为gb2312就可以调用存储过程
**/

CMySQLDB::CMySQLDB()
{	
	memset(&mysql_, 0, sizeof(mysql_));
}

CMySQLDB::~CMySQLDB()
{
	Close();
}

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
int CMySQLDB::OpenDB(const char *host, unsigned short port, 
	const char *name, const char *username, const char *password)
{
	if (!mysql_init(&mysql_))
	{
		return -1;
	}

	if (mysql_options(&mysql_, MYSQL_OPT_RECONNECT, "1")) // 自动重连
	{
		return -2;
	}

	if (!mysql_real_connect(&mysql_,
		host,
		username,
		password,
		name,
		port,
		NULL,
		REFRESH_QUERY_CACHE_FREE)) // 不加就不能调用存储过程
	{
		return -3;
	}

	if (0 != mysql_query(&mysql_, "SET NAMES 'gb2312'")) // 设置连接字符集
	{
		return -4;
	}

	timeout_ = GetWaitTimeout();

	nextSet_ = ::GetTickCount() + timeout_ * 500;

	return 0;
}

/**
 *\fn         Close()
 *\brief      关闭数据库
 */
void CMySQLDB::Close(void)
{
	mysql_close(&mysql_);
}

/**
 *\fn         Exec(const char *sql)
 *\brief      执行SQL语句
 *\param[in]  sql		SQL语句。
 *\return     是否成功
 */
bool CMySQLDB::Exec(const char *sql)
{
	if (NULL == sql) return false;

	if (::GetTickCount() > nextSet_)
	{
		if (0 != mysql_query(&mysql_, "SET NAMES 'gb2312'"))	// 设置连接字符集
		{
			return false;
		}

		nextSet_ = ::GetTickCount() + timeout_;
	}

	if (0 == mysql_query(&mysql_, sql))// 0成功
	{
		TRACE("OK! %s\n", sql);
		return true;
	}
	else
	{
		LOG(ERROR) << "CMySQLDB::ExecSQL Fail! " << mysql_error(&mysql_) << sql;
	}

	return false;
}

/**
 *\fn         Procedure(const char *name, const char *param, ...)
 *\brief      调用存储过程
 *\param[in]  name		存储过程名。
 *\param[in]  param		存储过程参数。
 *\return     是否成功
 */
bool CMySQLDB::Procedure(const char *name, const char *param, ...)
{
	if (NULL == name) return false;

	if (::GetTickCount() > nextSet_)
	{
		if (0 != mysql_query(&mysql_, "SET NAMES 'gb2312'"))	// 设置连接字符集
		{
			return false;
		}

		nextSet_ = ::GetTickCount() + timeout_;
	}

	char fullParam[MAX_PATH] = "";

	if (NULL != param)
	{
		va_list argptr;
		va_start(argptr, param);
		_vstprintf(fullParam, param, argptr);
		va_end(argptr);
	}

	char fullSql[MAX_PATH*2] = "";
	sprintf(fullSql, "CALL %s (%s);", name, fullParam);

	if (0 == mysql_query(&mysql_, fullSql))// 0成功
	{
		return true;
	}
	else
	{
		LOG(ERROR) << "CMySQLDB::Procedure Fail! " << mysql_error(&mysql_) << fullSql;

		return false;
	}
}

/**
 *\fn         InsertBlob(const char *tableName, const char *fieldName, char *data, int len)
 *\brief      向数据表中插入BLOB二进制数据,如果数据大于1M则需要设置 max_allowed_packet 变量
 *\param[in]  tableName		表名。
 *\param[in]  fieldName		字段名。
 *\param[in]  data			数据。
 *\param[in]  len			数据长。
 *\return     是否成功
 */
bool CMySQLDB::InsertBlob(const char *tableName, const char *fieldName, char *data, int len)
{
	if ((NULL == tableName) ||
		(NULL == fieldName) ||
		(NULL == data))
	{
		return false;
	}

	MYSQL_STMT*	mysqlStmt = mysql_stmt_init(&mysql_); // 预处理对象

	if (NULL != mysqlStmt)
	{
		char sql[MAX_PATH] = "";
		sprintf(sql, "UPDATE %s SET %s = ?", tableName, fieldName); // ?代表的就是要插入的数据

		if (0 != mysql_stmt_prepare(mysqlStmt, sql, strlen(sql)))
		{
			TRACE("mysql_stmt_prepare failed!\n");
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;
			return false;
		}

		MYSQL_BIND mysqlBind = {0};
		mysqlBind.buffer_type = MYSQL_TYPE_BLOB;
		mysqlBind.buffer_length = len;
		mysqlBind.is_null = 0;
		mysqlBind.length = (unsigned long *)&len;
		mysqlBind.buffer = data;

		if (0 != mysql_stmt_bind_param(mysqlStmt, &mysqlBind))
		{
			TRACE("BIND ERROR!\n");
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;
			return false;
		}

		if (0 != mysql_stmt_execute(mysqlStmt))
		{
			TRACE("EXECUTE ERROR! %s\n", mysql_error(&mysql_));
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;				
			return false;
		}

		mysql_stmt_close(mysqlStmt);
		mysqlStmt = NULL;

		return true;
	}

	return false;
}

/**
 *\fn         GetBlob(const char *tableName, const char *fieldName, char *data, int len)
 *\brief      从数据表中得到BLOB二进制数据
 *\param[in]  tableName		表名。
 *\param[in]  fieldName		字段名。
 *\param[in]  data			数据。
 *\param[in]  len			数据长。
 *\return     是否成功
 */
bool CMySQLDB::GetBlob(const char *tableName, const char *fieldName, char *data, int &len)
{
	if ((NULL == tableName) ||
		(NULL == fieldName) ||
		(NULL == data))
	{
		return false;
	}

	MYSQL_STMT*	mysqlStmt = mysql_stmt_init(&mysql_); // 预处理对象

	if (NULL != mysqlStmt)
	{
		char sql[MAX_PATH] = "";
		sprintf(sql, "SELECT %s FROM %s", tableName, fieldName); // ?代表的就是要插入的数据

		if (0 != mysql_stmt_prepare(mysqlStmt, sql, strlen(sql)))
		{
			TRACE("mysql_stmt_prepare failed!\n");
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;
			return false;
		}

		ULONG count= mysql_stmt_param_count(mysqlStmt);

		if (0 != count)
		{
			TRACE("mysql_stmt_param_count() failed!\n");
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;
			return false;
		}

		MYSQL_RES *mysqlResult = mysql_stmt_result_metadata(mysqlStmt);

		if (NULL == mysqlResult)
		{
			TRACE("mysql_stmt_result_metadata() failed!\n");
			mysql_stmt_close(mysqlStmt);
			mysqlStmt = NULL;
			return false;
		}

		if (0 != mysql_stmt_execute(mysqlStmt))
		{
			TRACE("EXECUTE ERROR!\n");
			mysql_free_result(mysqlResult);
			mysql_stmt_close(mysqlStmt);
			mysqlResult = NULL;
			mysqlStmt = NULL;				
			return FALSE;
		}

		my_bool bNULL = 0;

		MYSQL_BIND mysqlBind_;
		memset(&mysqlBind_, 0, sizeof(mysqlBind_));
		mysqlBind_.buffer_type = MYSQL_TYPE_BLOB;
		mysqlBind_.buffer_length = len;
		mysqlBind_.is_null = &bNULL;
		mysqlBind_.length = (unsigned long *)&len;
		mysqlBind_.buffer = data;
		len = 0;

		if (mysql_stmt_bind_result(mysqlStmt, &mysqlBind_))
		{
			TRACE(_T("mysql_stmt_bind_result() failed\n"));
			mysql_free_result(mysqlResult);
			mysql_stmt_close(mysqlStmt);
			mysqlResult = NULL;
			mysqlStmt = NULL;
			return false;
		}

		if (mysql_stmt_store_result(mysqlStmt))
		{
			TRACE("mysql_stmt_store_result() failed\n");
			mysql_free_result(mysqlResult);
			mysql_stmt_close(mysqlStmt);
			mysqlResult = NULL;
			mysqlStmt = NULL;
			return false;
		}

		while (!mysql_stmt_fetch(mysqlStmt))// 得到其中的一行(可能有多行)
		{
		}

		mysql_free_result(mysqlResult);
		mysql_stmt_close(mysqlStmt);
		mysqlResult = NULL;
		mysqlStmt = NULL;

		return true;
	}

	return false;
}

/**
 *\fn         GetWaitTimeout()
 *\brief      得到等待超时值
 *\return     超时值
 */
int CMySQLDB::GetWaitTimeout()
{
    if (0 != mysql_query(&mysql_, "show global variables like 'wait_timeout';"))// 0成功
    {
        LOG(ERROR) << "CMySQLDB::GetWaitTimeout Fail! Error:" << mysql_error(&mysql_);
        return 0;
    }
    else
    {
        VECTOR_STR data;
        int rows = 0;
        int fields = 0;

        GetData(data, rows, fields);

        return atoi(data[1].c_str());
    }
}

/**
 *\fn         GetData(VECTOR_STR &data, int &rows, int &fields)
 *\brief      得到数据
 *\param[out] data		数据。
 *\param[out] rows		记录行数。
 *\param[out] fields	字段个数。
 *\return     是否成功
 */
bool CMySQLDB::GetData(VECTOR_STR &data, int &rows, int &fields)
{
	MYSQL_RES *mysqlResult = mysql_store_result(&mysql_);

	if (NULL != mysqlResult)
	{
		rows = mysql_num_rows(mysqlResult);
		fields = mysql_num_fields(mysqlResult);

		for (int i = 0; i < rows; i++)
		{
			MYSQL_ROW mysqlRow = mysql_fetch_row(mysqlResult);

			for (int j = 0; j < fields; j++)
			{
				data.push_back(mysqlRow[j]);
			}
		}
	}

	mysql_free_result(mysqlResult);

	for( ; !mysql_next_result(&mysql_););//如果没有此语句，就不能再执行SQL语句了

	if (rows > 0)
	{
		return true;
	}

	return false;
}

/**
 *\fn         GetDataStr()
 *\brief      得到SELECT后的数据
 *\return     字符串数据
 */
std::string CMySQLDB::GetDataStr()
{
	std::string data;

	MYSQL_RES *mysqlResult = mysql_store_result(&mysql_);

	if (NULL != mysqlResult)
	{
		int rows = mysql_num_rows(mysqlResult);
		int fields = mysql_num_fields(mysqlResult);

		std::string data;

		MYSQL_FIELD *mysqlField = NULL;

		while (mysqlField = mysql_fetch_field(mysqlResult))
		{
			data += mysqlField->name;
			data += " ";
		}

		data += "\n";

		for (int i = 0; i < rows; i++)
		{
			MYSQL_ROW mysqlRow = mysql_fetch_row(mysqlResult);

			for (int j = 0; j < fields; j++)
			{
				data += mysqlRow[j];
				data += " ";
			}
		}
	}

	mysql_free_result(mysqlResult);
	for( ; ! mysql_next_result(&mysql_););//如果没有此语句，就不能再执行SQL语句了

	return data;
}