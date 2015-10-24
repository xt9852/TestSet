/*************************************************
 *  红黑树的几个性质:
 *  1) 每个结点只有红和黑两种颜色
 *  2) 根结点是黑色的
 *  3)空节点是黑色的（红黑树中，根节点的parent以及所有叶节点lchild、rchild都不指向NULL，而是指向一个定义好的空节点）。
 *  4) 如果一个结点是红色的,那么它的左右两个子结点的颜色是黑色的
 *  5) 对于每个结点而言,从这个结点到叶子结点的任何路径上的黑色结点的数目相同
 *************************************************/
#ifndef LIM_RBTREE_H_INCLUDED
#define LIM_RBTREE_H_INCLUDED
#include <pthread.h>

typedef void (*rbtree_free_kv)(void *key, void *value);
typedef void *(*rbtree_copy_key)(const void *src);
typedef int (*rbtree_compare_key)(const void *key1, const void *key2);
typedef int (*rbtree_filter)(const void *key);

typedef enum color_t
{
    RED = 0,
    BLACK = 1
}color_t;

typedef struct _lim_rbtree_item
{
    const void const *key;
    void *value;
    struct _lim_rbtree_item *next;
} lim_rbtree_item;

typedef struct _lim_rbtree_node
{
    struct _lim_rbtree_node *left, *right, *parent;
    void *key;
    void *bucket;
    int amount;
    color_t color;
}lim_rbtree_node;

typedef struct _lim_rbtree
{
    int size;
    pthread_mutex_t lock;
    lim_rbtree_node *root;
    lim_rbtree_node *minnode;
    lim_rbtree_node *maxnode;
    rbtree_free_kv cleaner;         // use to release key and value memory
    rbtree_copy_key copyer;         // use to copy key
    rbtree_compare_key comparator;  // use to locate node in the tree
} lim_rbtree;

/**
 *\fn        int lim_rbtree_create(lim_rbtree *tree)
 *\brief     创建红黑树结构，默认创建一个根节点
 *\param[in] lim_rbtree *tree               树结构，调用者需要设置cleaner, copyer, comparator
 *                                          创建时填充root, color, lock等字段
 *\param[in] lim_mem_free_func cleaner      负责清除树节点的value
 *\param[in] lim_compare_func comparator    负责比较树节点的key
 *\return    0成功， -1 失败
 */
int lim_rbtree_create(lim_rbtree *tree);

/**
 *\fn           void *lim_rbtree_get(lim_rbtree *tree, void *key)
 *\brief        根据key使用comparator定位红黑树上的节点
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      key
 *\parem[out]   lim_rbtree_item *result        节点上的记录集，调用者不需要释放Key和value，只须释放lim_rbtree_item
 *\return       0成功， -1 失败
 */
int lim_rbtree_get(lim_rbtree *tree, void *key, lim_rbtree_item *result);

/**
 *\fn           int lim_rbtree_add(lim_rbtree *tree, void *key, void *value)
 *\brief        添加红黑树上节点值,key将被拷贝,但value不复制,第一个插入的节点替换默认的根节点
 *              comparator计算结果相同的key数据挂在同一个节点上，数据用链表组织
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      树节点的key
 *\param[in]    void *value                    树节点的数据
 *\return       0成功， -1 失败
 */
int lim_rbtree_add(lim_rbtree *tree, void *key, void *value);

/**
 *\fn           int lim_rbtree_find(lim_rbtree *tree, rbtree_filter filter, lim_rbtree_list result)
 *\brief        遍历树节点根据filter找出所有key符合条件的节点
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    lrbtree_filter filter          函数指针用于过滤key
 *\param[out]   lim_rbtree_item result         符合条件的节点Key-Value列表，
 *              调用者自己释放链表节点但不用释放key和value
 *\return       0成功， -1 失败
 */
int lim_rbtree_find(lim_rbtree *tree, rbtree_filter filter, lim_rbtree_item *result);


/**
 *\fn           int lim_rbtree_delete(lim_rbtree *tree, void *key, rbtree_compare_key matcher)
 *\brief        根据KEY使用tree的comparator进行节点定位，若matcher不为空将对调用该函数进行匹配
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      树节点的key
 *\param[in]    rbtree_compare_key matcher     节点键匹配函数指针，
 *\return       0成功， -1 失败
 */
int lim_rbtree_delete(lim_rbtree *tree, void *key, rbtree_compare_key matcher);

/**
 *\fn           int lim_rbtree_destroy(lim_rbtree *tree)
 *\brief        释放树上所有节点，lim_rbtree结构由调用者负责清除
 *\param[in]    lim_rbtree *tree               树结构
 */
void lim_rbtree_destroy(lim_rbtree *tree);

/**
 *\fn           void lim_rbtree_poll_min(lim_rbtree *tree, void *borderkey, lim_rbtree_item *result)
 *\brief        从树上最小节点开始进行遍历，一直删除到key大于borderkey的节点，删除的值记录放入result,由调用者释放
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *borderkey                上限key
 *\param[out]   lim_rbtree_item result         符合条件的节点Key-Value列表
 *\return       0成功， -1 失败
 */
int lim_rbtree_poll_min(lim_rbtree *tree, void *borderkey, lim_rbtree_item *result);

#endif
