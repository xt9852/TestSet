#include "StdAfx.h"
#include "XTXml.h"

#ifdef DEBUG
#pragma comment(lib,"../10.thirdParty/lib/tinyxml/tinyxmld.lib")
#else
#pragma comment(lib,"../10.thirdParty/lib/tinyxml/tinyxml.lib")
#endif


namespace XT_XML
{
	// 此注释是为了用Doxygen生成文档
	// 使用google代码规则

	/**
	 *\fn         xml()
	 *\brief      缺省构造函数。
	 */
	xml::xml()
	{
	}

	/**
	 *\fn         ~xml()
	 *\brief      析构函数。
	 */
	xml::~xml()
	{
	}

    /**
	 *\fn         LoadXml(const char *xmlContent, int length)
	 *\brief      加载内存XML数据。
	 *\param[in]  xmlContent XML数据。
     *\param[in]  length     XML数据长。
	 *\return     加载XML是否成功。
	 */
	bool xml::LoadXml(const char *xmlContent, int length)
	{
		if (xmlContent == NULL || length <= 0) return ERROR_INPUT_NULL;

		TIXML_STRING data;
		data.reserve(length);

		const char* buf = xmlContent;
		const char* lastPos = xmlContent;
		const char* p = xmlContent;

		while(*p && (p < (buf+length)))
        {
			if (*p == 0xa)
            {
				// Newline character. No special rules for this. Append all the characters
				// since the last string, and include the newline.
				data.append( lastPos, (p-lastPos+1) );	// append, include the newline
				++p;									// move past the newline
				lastPos = p;							// and point to the new buffer (may be 0)
				assert(p <= (buf+length));
			}
			else if (*p == 0xd)
            {
				// Carriage return. Append what we have so far, then
				// handle moving forward in the buffer.
				if ((p-lastPos) > 0)
                {
					data.append(lastPos, p-lastPos);	// do not add the CR
				}

				data += (char)0xa;						// a proper newline

				if (*(p+1) == 0xa)
                {
					// Carriage return - new line sequence
					p += 2;
					lastPos = p;
					assert(p <= (buf+length));
				}
				else
                {
					// it was followed by something else...that is presumably characters again.
					++p;
					lastPos = p;
					assert(p <= (buf+length));
				}
			}
			else
            {
				++p;
			}
		}

		// Handle any left over characters.
		if (p-lastPos)
        {
			data.append(lastPos, p-lastPos);
		}		

		Parse(data.c_str(), 0, TIXML_ENCODING_UNKNOWN);

		return !Error();
	}

	/**
	 *\fn         GetXml()
	 *\brief      得到XML字符串。
	 *\return     XML字符串。
	 */
	std::string xml::GetXml()
	{
		TiXmlPrinter printer;
		this->Accept(&printer);

		return printer.CStr();
	}

	/**
	 *\fn         operator[](const char *name)
	 *\brief      通过节点名查找节点指针。
	 *\param[in]  index 节点集的序号。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementEx::operator[] (const char *name)
	{
		return SelectSingleNode(name);
	}

	/**
	 *\fn         SelectSingleNode(const char *path)
	 *\brief      查找第一个节点，可直接查找多个，如：a\b\c，表示a节点的b子节点的c子节点。
	 *\param[in]  path XML节点名。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementEx::SelectSingleNode(const char *path)
	{
		TiXmlElement *next = NULL;
		TiXmlElement *node = this;

		char seps[] = "\\";
		char temp[MAX_PATH] = "";
        char *content = NULL;

		strcpy_s(temp, path);

		char *token = strtok_s(temp, seps, &content);

		while (token != NULL)
		{
			next = node->FirstChildElement(token);

			if (next != NULL)
			{
				node = next;
			}
			else
			{
				return NULL;
			}

			token = (char*)strtok_s(NULL, seps, &content);
		}

		return (TiXmlElementEx*)next;
	}

	/**
	 *\fn         SelectNodes(const char *path)
	 *\brief      查找多个同名节点，可直接查找多个，如：a\b\c，表示a节点的b子节点的多个c子节点。
	 *\param[in]  path XML节点名。
	 *\return     节点指针集。
	 */
	TiXmlElementExs TiXmlElementEx::SelectNodes(const char *path)
	{
		TiXmlElementExs elementes;

		char nodeName[MAX_PATH] = "";
		
		char *name = strrchr((char*)path, '\\');

		strcpy_s(nodeName, (name == NULL)?path:(name+1));

		TiXmlElementEx *node = SelectSingleNode(path);

		while (node != NULL)
		{
			elementes.Add(node);
			
			node = (TiXmlElementEx*)node->NextSiblingElement(nodeName);			
		}

		return elementes;
	}

	/**
	 *\fn         SetName(const char *name)
	 *\brief      设置节点名字。
	 *\param[in]  name XML节点名。
	 */
	void TiXmlElementEx::setName(const char *name)
	{
		SetValue(name);
	}

	/**
	 *\fn         setValue(const char *value)
	 *\brief      设置节点值。
	 *\param[in]  value XML节点值。
	 */
	void TiXmlElementEx::setValue(const char *value)
	{
		Clear(); // 首先清除所有文本		
		InsertEndChild(TiXmlText(value)); // 然后插入文本，保存文件
	}

	

	/**
	 *\fn         TiXmlElementExs()
	 *\brief      缺省构造函数。
	 */
	TiXmlElementExs::TiXmlElementExs()
	{
	}

	/**
	 *\fn         ~TiXmlElementExs()
	 *\brief      析构函数。
	 */
	TiXmlElementExs::~TiXmlElementExs()
	{
	}

	/**
	 *\fn         operator[](int index)
	 *\brief      通过序号查找节点指针。
	 *\param[in]  index 节点集的序号。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementExs::operator[] (int index)
	{
		return GetItem(index);
	}

	/**
	 *\fn         operator[](const char *name)
	 *\brief      通过节点名查找节点指针。
	 *\param[in]  index 节点集的序号。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementExs::operator[] (const char *name)
	{
		return GetItem(name);
	}

	/**
	 *\fn         GetItem(int index)
	 *\brief      通过序号查找节点指针。
	 *\param[in]  index 节点集的序号。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementExs::GetItem(int index)
	{
		if ((index < 0) || (index >= getCount()))
		{
			return NULL;
		}

		LIST_ELEMENT::iterator iter = elementes_.begin();
		for (int i = 0; i < index; i++)
		{
			++iter;
		}

		return *iter;
	}

	/**
	 *\fn         GetItem(const char *name)
	 *\brief      通过节点名查找节点指针。
	 *\param[in]  index 节点集的序号。
	 *\return     节点指针。
	 */
	TiXmlElementEx* TiXmlElementExs::GetItem(const char *name)
	{
		if (name == NULL)
		{
			return NULL;
		}

		LIST_ELEMENT::iterator iter = elementes_.begin();
		for (; iter != elementes_.end(); ++iter)
		{
			if (0 == strcmp(name, (*iter)->Value()))
			{
				return *iter;
			}

			++iter;
		}

		return NULL;
	}

	/**
	 *\fn         Add(TiXmlElementEx* node)
	 *\brief      添加节点。
	 *\param[in]  node 要添加的节点。
	 */
	void TiXmlElementExs::Add(TiXmlElementEx* node)
	{
		elementes_.push_back(node);
	}
}