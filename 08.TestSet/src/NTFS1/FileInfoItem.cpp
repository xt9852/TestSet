#include <FileInfoItem.h>
#include <LWStringList.h>

LSTP_BASICUTILS_NS_BEGIN

FileInfoItem::FileInfoItem(FileInfoItem* parent, const wchar_t* path, ITEMTYPE type,FILETIME& ft)
	: type_(type)
	, subdirCount_(0)
	, filesCount_(0)
	, totalSize_(0)
	, parent_(parent)
	, name_(path)
{
	if (type_ == IT_DIRECTORY)
		lastChangedTime_ = ft;
	else
		memset(&lastChangedTime_,0,sizeof(FILETIME));
}

FileInfoItem::FileInfoItem(FileInfoItem* parent, const wchar_t* filename, const uint64 filesize, FILETIME& ft)
	: type_(IT_FILE)
	, subdirCount_(0)
	, filesCount_(0)
	, totalSize_(filesize)
	, parent_(parent)
	, name_(filename)
{
	lastChangedTime_ = ft;
}

FileInfoItem::~FileInfoItem()
{
	FileInfoItems::iterator it = fileItems_.begin();
	for (; it != fileItems_.end(); ++it)
		delete *it;
	fileItems_.clear();

	it = subdirItems_.begin();
	for (; it != subdirItems_.end(); ++it)
		delete *it;
	subdirItems_.clear();
}

void FileInfoItem::UpdateAllData(uint64 updateSize, uint32 updateFileCount
	, uint32 updateDirCount, FILETIME& lastChangeTime)
{
	totalSize_ += updateSize;
	filesCount_ += updateFileCount;
	subdirCount_ += updateDirCount;
	if (lastChangedTime_ < lastChangeTime)
		lastChangedTime_ = lastChangeTime;
	if (GetParent() != NULL)
		GetParent()->UpdateAllData(updateSize,updateFileCount,updateDirCount,lastChangeTime);
}

void FileInfoItem::AddChildDirectory(FileInfoItem* childItem)
{
	subdirItems_.push_back(childItem);
}

void FileInfoItem::AddChildFile(FileInfoItem* childItem)
{
	fileItems_.push_back(childItem);
}

const LWString FileInfoItem::GetFullname() const
{
	if (NULL == GetParent())
		return GetName();
	LWStringList l;
	l.Append(GetName());
	FileInfoItem* parent = GetParent();
	while (NULL != parent) {
		l.Insert(0,parent->GetName());
		parent = parent->GetParent();
	}
	return l.Join(L"\\");
}

LSTP_BASICUTILS_NS_END
