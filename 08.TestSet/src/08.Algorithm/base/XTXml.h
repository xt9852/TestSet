#pragma once
#include "tinyxml/tinyxml.h"
#include <list>

#ifndef S_OK
#define S_OK 0
#endif

namespace XT_XML
{
	// 此注释是为了用Doxygen生成文档
	// 使用google代码规则


	enum{
		ERROR_INPUT_NULL,			// 输入为空
		ERROR_OPEN_FAIL,			// 打开文件失败
		ERROR_FIND_ROOTNODE_FAIL,	// 查找根节点失败
	};

	class TiXmlElementEx;
	class TiXmlElementExs;

	/**
	 *\class  xml
	 *\brief  该类主要是XML文档
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类,使用tinyXML库。
	 */
	class xml : public TiXmlDocument
	{
	public:
		/**
		 *\fn         xml()
		 *\brief      缺省构造函数。
	     */
		xml();

		/**
		 *\fn         ~xml()
		 *\brief      析构函数。
		 */
		~xml();

		/**
		 *\fn         LoadXml(const char *xmlContent, int length)
		 *\brief      加载内存XML数据。
		 *\param[in]  xmlContent XML数据。
         *\param[in]  length     XML数据长。
		 *\return     加载XML是否成功。
		 */
		bool LoadXml(const char *xmlContent, int length);

		/**
		 *\fn         GetXml()
		 *\brief      得到XML字符串。
		 *\return     XML字符串。
		 */
		std::string GetXml();

		/**
		 *\fn         GetRoot()
		 *\brief      得到XML根节点。
		 *\return     XML根节点。
		 */
		TiXmlElementEx* GetRoot() { return (TiXmlElementEx*)RootElement(); }
	};

	/**
	 *\class  TiXmlElementEx
	 *\brief  该类主要是XML节点
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类,使用tinyXML库。
	 */
	class TiXmlElementEx : public TiXmlElement
	{
	public:
		/**
		 *\fn         TiXmlElementEx()
		 *\brief      缺省构造函数。
	     */
		TiXmlElementEx();

		/**
		 *\fn         ~TiXmlElementEx()
		 *\brief      析构函数。
		 */
		~TiXmlElementEx();

		/**
		 *\fn         operator[](const char *name)
		 *\brief      通过节点名查找节点指针。
		 *\param[in]  index 节点集的序号。
		 *\return     节点指针。
		 */
		TiXmlElementEx* operator[] (const char *name);

		/**
		 *\fn         SelectSingleNode(const char *path)
		 *\brief      查找第一个节点，可直接查找多个，如：a\b\c，表示a节点的b子节点的c子节点。
		 *\param[in]  path XML节点名。
		 *\return     节点指针。
		 */
		TiXmlElementEx* SelectSingleNode(const char *path);

		/**
		 *\fn         SelectNodes(const char *path)
		 *\brief      查找多个同名节点，可直接查找多个，如：a\b\c，表示a节点的b子节点的多个c子节点。
		 *\param[in]  path XML节点名。
		 *\return     节点指针集。
		 */
		TiXmlElementExs SelectNodes(const char *path);

		/**
		 *\fn         SetName(const char *name)
		 *\brief      设置节点名字。
		 *\param[in]  name XML节点名。
		 */
		void setName(const char *name);

		/**
		 *\fn         setValue(const char *value)
		 *\brief      设置节点值。
		 *\param[in]  value XML节点值。
		 */
		void setValue(const char *value);
	};
	

	typedef std::list<TiXmlElementEx*> LIST_ELEMENT;

	/**
	 *\class  TiXmlElementExs
	 *\brief  该类主要是XML节点集
	 *\date   2012-07-03
	 *\author 张海涛
	 *\par    Revision History:
	 *\n      0.1     2007-07-03   张海涛   创建此类,使用tinyXML库。
	 */
	class TiXmlElementExs
	{
	public:
		/**
		 *\fn         TiXmlElementEx()
		 *\brief      缺省构造函数。
	     */
		TiXmlElementExs();

		/**
		 *\fn         ~TiXmlElementEx()
		 *\brief      析构函数。
		 */
		~TiXmlElementExs();
		
		/**
		 *\fn         operator[](int index)
		 *\brief      通过序号查找节点指针。
		 *\param[in]  index 节点集的序号。
		 *\return     节点指针。
		 */
		TiXmlElementEx* operator[] (int index);

		/**
		 *\fn         operator[](const char *name)
		 *\brief      通过节点名查找节点指针。
		 *\param[in]  index 节点集的序号。
		 *\return     节点指针。
		 */
		TiXmlElementEx* operator[] (const char *name);

		/**
		 *\fn         GetItem(int index)
		 *\brief      通过序号查找节点指针。
		 *\param[in]  index 节点集的序号。
		 *\return     节点指针。
		 */
		TiXmlElementEx* GetItem(int index);

		/**
		 *\fn         GetItem(const char *name)
		 *\brief      通过节点名查找节点指针。
		 *\param[in]  index 节点集的序号。
		 *\return     节点指针。
		 */
		TiXmlElementEx* GetItem(const char *name);

		/**
		 *\fn         getCount()
		 *\brief      得到节点集的节点数量。
		 *\return     节点数量。
		 */
		int getCount() { return elementes_.size(); }

		/**
		 *\fn         release()
		 *\brief      释放节点集。
		 */
		void release() { elementes_.clear(); }
		
		/**
		 *\fn         Add(TiXmlElementEx* node)
		 *\brief      添加节点。
		 *\param[in]  node 要添加的节点。
		 */
		void Add(TiXmlElementEx* node);

	private:
		LIST_ELEMENT elementes_;		
	};


	

}