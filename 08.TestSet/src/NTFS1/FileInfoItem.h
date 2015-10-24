#ifndef BASICUTILS_FILEINFOITEM_H_
#define BASICUTILS_FILEINFOITEM_H_

/**
 *\class  FileInfoItem
 *\brief  扫描后获得的文件信息节点项，通过该类的对象指针，可构成整个文件信息树模型。
 *\date   2012-07-10
 *\author 刘磊
 *\par    Revision History:
 */

#include <list>

// #include <BasicUtils.h>
// #include <LWString.h>

// LSTP_BASICUTILS_NS_BEGIN
// USE_LSTP_BASICLIBRARY_NS
// USE_STD_NS

enum ITEMTYPE {
	IT_MYCOMPUTER = 0,
	IT_DRIVE,
	IT_DIRECTORY,
	IT_FILE,
};
class FileInfoItem;

typedef std::list<FileInfoItem*> FileInfoItems;

class /*BASICUTILS_API*/ FileInfoItem
{
private:
	/**
	 *\fn         FileInfoItem(FileInfoItem* parent, const wchar_t* path, ITEMTYPE type,FILETIME& ft)
	 *\brief      构造函数。其中该构造函数仅用于生成目录和驱动器的文件节点项。
	 *\param[in]  parent 父节点，如果该值为NULL，表示当前节点为根节点。
	 *\param[in]  path 该节点表示的目录名或驱动器。其中目录名仅包含当前目录名，而不是全路径名。
	 *\param[in]  type 节点的类型。
	 *\param[in]  ft 当前节点的最新修改时间。
	 */	
	void FileInfoItem(FileInfoItem* parent, const wchar_t* path, ITEMTYPE type,FILETIME& ft);
	/**
	 *\fn         FileInfoItem(FileInfoItem* parent, const wchar_t* filename, const uint64 filesize,FILETIME& ft)
	 *\brief      构造函数。其中该构造函数仅用于生成普通文件的文件节点项。
	 *\param[in]  parent 父节点。
	 *\param[in]  filename 实际的文件名，而不是全路径文件名。
	 *\param[in]  filesize 文件的长度。
	 *\param[in]  ft 当前节点的最新修改时间。
	 */	
	void FileInfoItem(FileInfoItem* parent, const wchar_t* filename, const uint64 filesize,FILETIME& ft);
	/**
	 *\fn         ~FileInfoItem()
	 *\brief      析构函数。
	 */
	void ~FileInfoItem();

public:
	/**
	 *\fn         const LWString GetFullname() const
	 *\brief      获取当前节点的全目录名或全文件名。
	 *\return     返回当前节点的全目录名或全文件名。
	 */	
	const std::wstring GetFullname() const;
	/**
	 *\fn         const LWString GetName() const
	 *\brief      仅获取当前节点的目录名或文件名。
	 *\return     仅返回当前节点的目录名或文件名。
	 */	
	inline const std::wstring GetName() const {
		return name_;
	}
	/**
	 *\fn         ITEMTYPE GetType() const
	 *\brief      获取当前节点的类型。
	 *\return     返回当前节点的类型。
	 */	
	inline ITEMTYPE GetType() const {
		return type_;
	}
	/**
	 *\fn         size_t SubdirCount() const
	 *\brief      获取当前节点所包含的子目录数量。
	 *\return     返回当前节点所包含的子目录数量。
	 */	
	inline size_t SubdirCount() const {
		return subdirCount_;
	}
	/**
	 *\fn         size_t FileCount() const
	 *\brief      获取当前节点所包含的文件数量。
	 *\return     返回当前节点所包含的文件数量。
	 */	
	inline size_t FileCount() const {
		return filesCount_;
	}
	/**
	 *\fn         uint64 GetTotalSize() const
	 *\brief      获取当前节点所占用的磁盘空间字节数。
	 *\return     如果当前节点为文件，返回文件自身的长度，否则返回其子目录下所有文件的长度总和。
	 */	
	inline uint64 GetTotalSize() const {
		return totalSize_;
	}
	/**
	 *\fn         const FileInfoItems& ChildrenSubdirs() const
	 *\brief      获取当前节点的所有一级子目录节点。
	 *\return     返回当前节点的所有一级子目录节点。
	 */	
	inline const FileInfoItems& ChildrenSubdirs() const {
		return subdirItems_;
	}
	/**
	 *\fn         const FileInfoItems& ChildrenFiles() const
	 *\brief      获取当前节点的所有一级子文件节点。
	 *\return     返回当前节点的所有一级子文件节点。
	 */	
	inline const FileInfoItems& ChildrenFiles() const {
		return fileItems_;
	}
	/**
	 *\fn         FileInfoItem* GetParent() const
	 *\brief      获取当前节点的父节点。
	 *\return     返回当前节点的父节点，如果该值为NULL，则表示当前节点为根节点。
	 */	
	inline FileInfoItem* GetParent() const {
		return parent_;
	}
	/**
	 *\fn         bool IsRootItem() const
	 *\brief      判断当前节点是否为根节点。
	 *\return     是返回true，否则false。
	 */	
	inline bool IsRootItem() const {
		return NULL == parent_;
	}
	
private:
	void AddChildDirectory(FileInfoItem* childItem);
	void AddChildFile(FileInfoItem* childItem);
	void UpdateAllData(uint64 updateSize, uint32 updateFileCount, uint32 updateDirCount, FILETIME& lastChangeTime);

private:
	ITEMTYPE type_;
	uint64 totalSize_;
	uint32 filesCount_;
	uint32 subdirCount_;
	FILETIME lastChangedTime_;
	std::wstring name_;
	FileInfoItems subdirItems_;
	FileInfoItems fileItems_;
	FileInfoItem* parent_;
	friend class FileScanner;
	friend class FileScanRunnable;
	friend class NtfsDiskScanRunnable;
};

inline bool operator< (const FILETIME& t1, const FILETIME& t2)
{
	if (t1.dwHighDateTime < t2.dwHighDateTime) {
		return true;
	} else if (t1.dwHighDateTime == t2.dwHighDateTime) {
		return t1.dwLowDateTime < t2.dwLowDateTime;
	} else {
		return false;
	}
}

inline bool operator == (const FILETIME& t1, const FILETIME& t2)
{
	return t1.dwLowDateTime == t2.dwLowDateTime && t1.dwHighDateTime == t2.dwHighDateTime;
}

//LSTP_BASICUTILS_NS_END
#endif /*BASICUTILS_FILEINFOITEM_H_*/
