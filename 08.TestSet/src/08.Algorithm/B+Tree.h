
#pragma once

#define MLEVEL			4
#define MAX				MLEVEL+1		// 结点中关键字的最大数目：Max = m-1，m是B-树的阶
#define MIN				MLEVEL/2-1		// 非根结点中关键字的最小数目：Min=┌m/2┐-1
#define RIGHT_SON(x)	(x+1)			// 右子节点号
#define LEFT_SON(x)		(x)				// 左子节点号

typedef struct _tagData
{
	int nKey;
	void *pData;

}DATA, *PDATA;


typedef struct node				// 结点定义中省略了指向关键字代表的记录的指针
{
	int nKeyNum;				// 结点中当前拥有的关键字的个数，nKeyNum《Max
	DATA Key[MLEVEL];			// 关键字向量为key[1..nKeyNum]，key[0]不用。
	struct node *pParent;		// 指向双亲结点
	struct node *pSon[MAX];		// 孩子指针向量为son[0..nKeyNum]

}BTreeNode;



class CBTree
{
public:
	CBTree();
	~CBTree();

protected:
	BTreeNode *m_pRoot;

	bool InsertKey(BTreeNode *pNode, int nKey, void *pData, BTreeNode *pRightSonNode);
	bool DeleteKey(BTreeNode *pNode, int nKey);
	BTreeNode* SelectKey(BTreeNode *pNode, int nKey);

public:
	bool Insert(int nKey, void *pData);
};