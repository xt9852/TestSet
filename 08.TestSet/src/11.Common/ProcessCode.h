#pragma once
#include "Common/StrConver.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm> // find_if
#include <cctype>  // isspace

//#include "test.h"

#define ENTER "\r\n"
#define TAB_SIZE 4

enum
{
	RELINE,		// 换行
	COMMENT,	// 注释
	IDENTIFIER, // 标识符
	OPERATOR,	// 运算符
	BOUNDARY,	// 界限符
	STRING,		// 字符串
	SECTION,	// 区段
	KEYWORD,	// 关键字
};

typedef struct tagWordData
{
	std::string word;	// 词
	int type;			// 类型
	int enterCount;		// 空行数
	int headPos;		// 行头位置
	bool follow;		// 当是注释时，是否跟随同一行

	tagWordData()
	{
		type = 0;
		headPos = 0;
	}

}WordData, *PWordData;

typedef std::vector<WordData>		WORD_VECTOR; // 二元词组
typedef std::vector<std::string>	STR_VECTOR;  // 字符串列表
typedef std::map<std::string, int>	KEYWORD_MAP; // 关健字
typedef std::map<int, std::string>	INT_STR_MAP; // 关健字


class CProcessCode
{
public:
    CProcessCode();
    ~CProcessCode();

private:
	char		*data_;		// 文件数据
	int			len_;		// 文件数据长

	WORD_VECTOR word_;		// 二元组

	KEYWORD_MAP keyword_;	// 关键字

	INT_STR_MAP typeInfo_;	// 类型信息

	/**
	 *\fn         TokenizeWord(const char *data, int len)
	 *\brief      按行分割代码。
	 *\param[in]  data  数据。
	 *\param[in]  len   数据长。
	 *\return     无
	 */
	void TokenizeWord(const char *data, int len);

	/**
	 *\fn         ProcessWord(WORD_LIST &word)
	 *\brief      按行分割代码。
	 *\param[out] word  二元数据。
	 *\return     无
	 */
	void ProcessWord(WORD_VECTOR &word);

	/**
	 *\fn         ProcessDefine(WORD_LIST &word)
	 *\brief      处理函数定义,并生成注释。
	 *\param[out] word  二元数据。
	 *\return     无
	 */
	void ProcessDefine(WORD_VECTOR &word);

	/**
	 *\fn         ProcessComment(WORD_VECTOR &word, id, int headPos)
	 *\brief      处理注释。
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessComment(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         ProcessBoundary(WORD_VECTOR &word, id)
	 *\brief      处理界定符。'('')''['']'';''#''.'',''{''}'':'
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessBoundary(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         ProcessOperator(WORD_VECTOR &word, id, int headPos)
	 *\brief      处理操作符。
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessOperator(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         ProcessSection(WORD_VECTOR &word, id, int headPos)
	 *\brief      处理换行。
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessSection(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         ProcessSection(WORD_VECTOR &word, id, int headPos)
	 *\brief      处理换行。
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessKeyword(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         ProcessReline(WORD_VECTOR &word, id, int headPos)
	 *\brief      处理换行。
	 *\param[out] word  二元数据。
	 *\param[out] id  二元数据ID。
	 *\return     行头位置
	 */
	int ProcessReline(WORD_VECTOR &word, int id, int headPos);

	/**
	 *\fn         isNum(char c)
	 *\brief      是否是数字。
	 *\param[in]  c    数据。
	 *\return     是否是数字
	 */
	bool isNum(char c) { return (c >= '0'&& c <= '9'); }

	/**
	 *\fn         isLetter(char c)
	 *\brief      是否是字符。
	 *\param[in]  c    数据。
	 *\return     是否是字符
	 */
	bool isLetter(char c) { return (c >= 'a'&& c <= 'z') || (c >= 'A'&& c <= 'Z'); }

	/**
	 *\fn         isKeyword(const char *keyword)
	 *\brief      是否是关键字。
	 *\param[in]  c    数据。
	 *\return     是否是关键字
	 */
	bool isKeyword(const char *keyword) 
	{
		KEYWORD_MAP::iterator iter = keyword_.find(keyword); return iter != keyword_.end();
	}

	/**
	 *\fn         rtrim(std::string &s)
	 *\brief      删除右侧空白符。
	 *\param[in]  s    数据。
	 *\return     删除后的字符串
	 */
	std::string rtrim(std::string &s)
	{
		while (s != "" && s[s.length()-1] == ' ')
		{
			s.erase(s.length()-1, 1);
		}

		return s; 
	}

	/**
	 *\fn         AddWord(char ch, int type)
	 *\brief      向二元数组插入数据。
	 *\param[in]  ch    字符数据。
	 *\param[in]  type  数据类型。
	 *\return     无
	 */
	void AddWord(char ch, int type)
	{
		WordData wordData;
		wordData.word = ch;
		wordData.type = type;
		word_.push_back(wordData);

		TRACE("%s %s\n", wordData.word.c_str(), typeInfo_[type].c_str());
	}

	/**
	 *\fn         AddWord(const std::string &str, int type)
	 *\brief      向二元数组插入数据。
	 *\param[in]  str   字符串数据。
	 *\param[in]  type  数据类型。
	 *\return     无
	 */
	void AddWord(const std::string &str, int type)
	{
		WordData wordData;
		wordData.word = str;
		wordData.type = type;;
		word_.push_back(wordData);

		TRACE("%s %s\n", str.c_str(), typeInfo_[type].c_str());
	}

	/**
	 *\fn         AddSpace(std::string &str, int count)
	 *\brief      追加空格。
	 *\param[in]  str   字符串数据。
	 *\param[in]  count 空格数量。
	 *\return     无
	 */
	void AddSpace(std::string &str, int count)
	{
		for (int i = 0; i < count; i++)
		{
			str += " ";
		}
	}

public:
	/**
	 *\fn         load(const char *filename)
	 *\brief      从文件加载数据。
	 *\param[in]  filename   文件名。
	 *\return     是否成功
	 */
	bool load(const char *filename);

	/**
	 *\fn         load(const char *data, int len)
	 *\brief      加载数据。
	 *\param[in]  data   数据。
	 *\param[in]  len    数据长。
	 *\return     是否成功
	 */
	bool load(const char *data, int len);

	/**
	 *\fn         Save(const char *filename)
	 *\brief      将处理完的数据保存。
	 *\param[in]  filename   文件名。
	 *\return     是否成功
	 */
	bool Save(const char *filename);
};