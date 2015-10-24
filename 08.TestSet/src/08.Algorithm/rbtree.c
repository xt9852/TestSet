#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static lim_rbtree_node *rbtree_node_init(lim_rbtree *tree, void *key, void *value);
static lim_rbtree_node *rbtree_search(lim_rbtree *tree, void *key, lim_rbtree_node **parent);
static void rbtree_bucket_list(lim_rbtree_node *node, rbtree_filter filter, lim_rbtree_item *head);
static void rbtree_insert_rebalance(lim_rbtree *tree, lim_rbtree_node *node);
static lim_rbtree_node *rbtree_rotate_left(lim_rbtree_node *node, lim_rbtree_node *root);
static lim_rbtree_node *rbtree_rotate_right(lim_rbtree_node *node, lim_rbtree_node *root);
static void rbtree_iterate(lim_rbtree_node *node, lim_rbtree_item *head, rbtree_filter filter);
static void rbtree_remove_from_bucket(lim_rbtree *tree, lim_rbtree_node *node, void *key, rbtree_compare_key comparator);
static void rbtree_reset_minnode(lim_rbtree *tree);
static lim_rbtree_node *rbtree_erase_rebalance(lim_rbtree_node *node, lim_rbtree_node *parent, lim_rbtree_node *root);
static void rbtree_destroy_item(lim_rbtree *tree, lim_rbtree_node *node);
static void rbtree_delete_node(lim_rbtree *tree, lim_rbtree_node *old);

/**
 *\fn        int lim_rbtree_create(lim_rbtree *tree)
 *\brief     创建红黑树结构，默认创建一个根节点
 *\param[in] lim_rbtree *tree               树结构，调用者必需需要设置cleaner, copyer, comparator
 *                                          创建时填充root, color, lock等字段
 *\param[in] lim_mem_free_func cleaner      负责清除树节点的value
 *\param[in] lim_compare_func comparator    负责比较树节点的key
 *\return    0成功， -1 失败
 */
int lim_rbtree_create(lim_rbtree *tree)
{
    int ret = 0;
    if (tree == NULL || tree->cleaner == NULL || tree->copyer == NULL || tree->comparator == NULL)
        ret = -1;
    else
    {
        tree->size = 0;
        tree->minnode = NULL;
        tree->root = rbtree_node_init(tree, NULL, NULL);
        tree->root->color = BLACK;
        pthread_mutex_init(&tree->lock, NULL);
    }

    return ret;
}

static lim_rbtree_node *rbtree_node_init(lim_rbtree *tree, void *key, void *value)
{
    lim_rbtree_node *node = (lim_rbtree_node*)malloc(sizeof(lim_rbtree_node));
    if (node == NULL)
        printf("malloc error!\n");
    else
    {
        if (key == NULL)
        {
            node->key = node->bucket = NULL;
            node->amount = 0;
        }
        else
        {
            node->key = tree->copyer(key);
            node->bucket = value;
            node->amount = 1;
        }
        node->color = RED;
        node->parent = node->left = node->right = NULL;
    }

    return node;
}

/**
 *\fn           void *lim_rbtree_get(lim_rbtree *tree, void *key, lim_rbtree_item *result)
 *\brief        根据key使用comparator定位红黑树上的节点,返回key-value链表，可以直接改value值
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      key
 *\parem[out]   lim_rbtree_item *head        节点上的记录集，调用者不需要释放Key和value，只须释放lim_rbtree_item
 *\return       0成功， -1 失败
 */
int lim_rbtree_get(lim_rbtree *tree, void *key, lim_rbtree_item *head)
{
    int ret = 0;
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL || key == NULL || head == NULL)
        ret = -1;
    else
    {
        lim_rbtree_node *node, *parent;
        node = rbtree_search(tree, key, &parent);
        if (node == NULL)
            ret = -1;
        else
            rbtree_bucket_list(node, NULL, head);
    }
    pthread_mutex_unlock(&tree->lock);
    return ret;
}

static lim_rbtree_node *rbtree_search(lim_rbtree *tree, void *key, lim_rbtree_node **parent)
{
    int ret;
    lim_rbtree_node *node = tree->root;

    while (node)
    {
        *parent = node;
        ret = tree->comparator(node->key, key);
        if (0 < ret)
            node = node->left;
        else if (0 > ret)
            node = node->right;
        else
            return node;
    }

    return NULL;
}

static void rbtree_bucket_list(lim_rbtree_node *node, rbtree_filter filter, lim_rbtree_item *head)
{
    if (node->amount == 1)
    {
        if (filter == NULL || filter(node->key) == 0)
        {
            lim_rbtree_item *item = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
            item->key = node->key;
            item->value = node->bucket;
            item->next = head->next;
            head->next = item;
        }
    }
    else if (node->amount > 1)
    {
        lim_rbtree_item *src = ((lim_rbtree_item *)node->bucket)->next;
        while(src != NULL)
        {
            if (filter == NULL || filter(node->key) == 0)
            {
                lim_rbtree_item *item = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
                item->key = src->key;
                item->value = src->value;
                item->next = head->next;
                head->next = item;
                src = src->next;
            }
        }
    }
}
/**
 *\fn           int lim_rbtree_add(lim_rbtree *tree, void *key, void *value)
 *\brief        添加红黑树上节点值,key将被拷贝,但value不复制,第一个插入的节点替换默认的根节点
 *              comparator计算结果相同的key数据挂在同一个节点上，数据用链表组织
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      树节点的key
 *\param[in]    void *value                    树节点的数据
 *\return       0成功， -1 失败
 */
int lim_rbtree_add(lim_rbtree *tree, void *key, void *value)
{
    int ret = 0;
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL || key == NULL || value == NULL)
        ret = -1;
    else
    {
        // replace root node key and value at first insert
        if (tree->size == 0)
        {
            tree->root->key = tree->copyer(key);
            tree->root->bucket = value;
            tree->root->amount = 1;
            tree->size = 1;
            tree->minnode = tree->root;
        }
        else
        {
            // if found out same key node, replace its value, otherwise insert new node to tree
            lim_rbtree_node *node;
            lim_rbtree_node *parent;
            node = rbtree_search(tree, key, &parent);
            if (node == NULL)
            {
                node = rbtree_node_init(tree, key, value);
                node->parent = parent;
                node->left = node->right = NULL;
                node->color = RED;
                tree->size ++;
                if (tree->comparator(parent->key,key) > 0)
                    parent->left = node;
                else
                    parent->right = node;

                rbtree_insert_rebalance(tree, node);
            }
            else
            {
                lim_rbtree_item *head;
                if (node->amount == 1)
                {
                    head = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
                    head->key = head->value = head->next = NULL;
                    lim_rbtree_item *item = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
                    item->key = tree->copyer(node->key);
                    item->value = node->bucket;
                    item->next = head->next;
                    head->next = item;

                    node->bucket = head;
                }
                else
                    head = node->bucket;

                lim_rbtree_item *item = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
                item->key = tree->copyer(key);
                item->value = value;
                item->next = head->next;
                head->next = item;

                node->amount ++;
            }
            if (tree->comparator(node->key, tree->minnode->key) < 0)
                tree->minnode = node;
        }
    }

    pthread_mutex_unlock(&tree->lock);
    return ret;
}

static void rbtree_insert_rebalance(lim_rbtree *tree, lim_rbtree_node *node)
{
    lim_rbtree_node *parent, *gparent, *uncle, *tmp;
    while ((parent = node->parent) && parent->color == RED)
    {
        //when parent isn't null and parent is red, to get grandfather
        gparent = parent->parent;
        if (parent == gparent->left) //root is black, so parent->parent can't be NULL
        {
            uncle = gparent->right;
            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
            }
            else
            {
                if (parent->right == node)
                {
                    tree->root = rbtree_rotate_left(parent, tree->root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }

                parent->color = BLACK;
                gparent->color = RED;
                tree->root = rbtree_rotate_right(gparent, tree->root);
            }
        }
        else
        {
            uncle = gparent->left;
            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
            }
            else
            {
                if (parent->left == node)
                {
                    tree->root = rbtree_rotate_right(parent, tree->root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                parent->color = BLACK;
                gparent->color = RED;
                tree->root = rbtree_rotate_left(gparent, tree->root);
            }
        }
    }

    tree->root->color = BLACK;

    return;
}

/*-----------------------------------------------------------
|       node           left
|       / \            / \
|    left  y   ==>    a   node
|    / \                   / \
|   a   b                 b   y
-----------------------------------------------------------*/
static lim_rbtree_node *rbtree_rotate_right(lim_rbtree_node *node, lim_rbtree_node *root)
{
    lim_rbtree_node *left = node->left;
    if ((node->left = left->right))
        left->right->parent = node;

    left->right = node;

    if ((left->parent = node->parent))
    {
        if (node == node->parent->right)
            node->parent->right = left;
        else
            node->parent->left = left;
    }
    else
        root = left;

    node->parent = left;
    return root;
}

/*-----------------------------------------------------------
|   node          right
|   / \    ==>     / \
|  a  right     node  y
|       / \      / \
|      b   y    a   b

 -----------------------------------------------------------*/
static lim_rbtree_node *rbtree_rotate_left(lim_rbtree_node *node, lim_rbtree_node *root)
{
    lim_rbtree_node *right = node->right;     //point to right subtree of node
    if ((node->right = right->left))    //if b isn't null, link b to node
        right->left->parent = node;     //node become b's parent
    right->left = node;                 //node become right left subtree

    if ((right->parent = node->parent)) //check node parent whether is null
    {
        if (node == node->parent->right)
            node->parent->right = right;    //let node parent point to right
        else
            node->parent->left = right;
    }
    else
        root = right;                   //right become root

    node->parent = right;
    return root;
}

/**
 *\fn           int lim_rbtree_find(lim_rbtree *tree, rbtree_filter filter, lim_rbtree_list result)
 *\brief        遍历树节点根据filter找出所有key符合条件的节点
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    lrbtree_filter filter          函数指针用于过滤key
 *\param[out]   lim_rbtree_item result         符合条件的节点Key-Value列表，
 *              调用者自己释放链表节点但不用释放key和value
 *\return       0成功， -1 失败
 */
int lim_rbtree_find(lim_rbtree *tree, rbtree_filter filter, lim_rbtree_item *result)
{
    int ret = 0;
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL || result == NULL || filter == NULL)
        ret = -1;
    else
    {
        rbtree_iterate(tree->root, result, filter);
    }

    pthread_mutex_unlock(&tree->lock);
    return ret;
}

static void rbtree_iterate(lim_rbtree_node *node, lim_rbtree_item *head, rbtree_filter filter)
{
    if (node->left)
        rbtree_iterate(node->left, head, filter);
    if (node->right)
        rbtree_iterate(node->right, head, filter);

    rbtree_bucket_list(node, filter, head);
}

/**
 *\fn           int lim_rbtree_delete(lim_rbtree *tree, void *key, rbtree_compare_key matcher)
 *\brief        根据KEY使用tree的comparator进行节点定位，若matcher不为空将对调用该函数进行匹配
 *              comparator计算结果相同的key数据挂在同一个节点上，数据用链表组织
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *key                      树节点的key
 *\param[in]    rbtree_compare_key matcher     节点键匹配函数指针，
 *\return       0成功， -1 失败
 */
int lim_rbtree_delete(lim_rbtree *tree, void *key, rbtree_compare_key matcher)
{
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL || key == NULL)
    {
        pthread_mutex_unlock(&tree->lock);
        return -1;
    }

    lim_rbtree_node *node, *parent, *old;
    node = rbtree_search(tree, key, &parent);
    if (node == NULL)   //node has been deleted
    {
        pthread_mutex_unlock(&tree->lock);
        return -1;
    }

    // user special comparator may difference from key comparator
    if (matcher != NULL)
    {
        rbtree_remove_from_bucket(tree, node, key, matcher);
        if (node->amount > 0)
        {
            pthread_mutex_unlock(&tree->lock);
            return 0;
        }
    }

    // update min node
    if (node == tree->minnode)
        rbtree_reset_minnode(tree);

    old = node;
    rbtree_delete_node(tree, node);

    // relase node
    rbtree_remove_from_bucket(tree, old, key, NULL);
    tree->cleaner(old->key, NULL);
    old->left = old->right = old->parent = NULL;
    free(old);
    tree->size --;


    pthread_mutex_unlock(&tree->lock);
    return 0;
}

static void rbtree_delete_node(lim_rbtree *tree, lim_rbtree_node *node)
{
    lim_rbtree_node *old, *parent, *child, *left;
    color_t color;
    old = node;
    if (node->left && node->right)
    {
        node = node->right;
        while ((left = node->left) != NULL)
            node = left;

        child = node->right;
        parent = node->parent;
        color = node->color;

        if (child)
            child->parent = parent;

        if (parent)
        {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
        {
            tree->root = child;
        }

        if (node->parent == old)
            parent = node;

        node->parent = old->parent;
        node->color = old->color;
        node->right = old->right;
        node->left = old->left;

        if (old->parent)
        {
            if (old->parent->left == old)
                old->parent->left = node;
            else
                old->parent->right = node;
        }
        else
        {
            tree->root = node;
        }

        old->left->parent = node;
        if (old->right)
            old->right->parent = node;
    }
    else
    {
        if (node->left == NULL)
            child = node->right;
        else
            child = node->left;

        parent = node->parent;
        color = node->color;

        if (child)
            child->parent = parent;

        if (parent)
        {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
        {
            tree->root = child;
        }
    }

    if (color == BLACK)
        tree->root = rbtree_erase_rebalance(child, parent, tree->root);
}

static void rbtree_remove_from_bucket(lim_rbtree *tree, lim_rbtree_node *node, void *key, rbtree_compare_key comparator)
{
    if (node->amount == 1)
    {
        if (comparator == NULL || comparator(node->key, key) == 0)
        {
            tree->cleaner(NULL, node->bucket);
            node->amount = 0;
        }
    }
    else if (node->amount > 1)
    {
        lim_rbtree_item *prev = (lim_rbtree_item *)node->bucket;
        lim_rbtree_item *curr = prev->next;
        while(curr != NULL)
        {
            if (comparator == NULL || comparator(key, curr->key) == 0)
            {
                tree->cleaner((void *)curr->key, curr->value);
                prev->next = curr->next;
                curr->key = curr->value = curr->next = NULL;
                free(curr);
                node->amount --;
                curr = prev->next;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        if (node->amount == 0)
        {
            free(node->bucket);
        }
        else if (node->amount == 1)
        {
            tree->cleaner(node->key, NULL);
            lim_rbtree_item *bucket = (lim_rbtree_item *)node->bucket;
            node->key = (void *)bucket->next->key;
            node->bucket = bucket->next->value;
            free(bucket->next);
            free(bucket);
        }
    }
}

static lim_rbtree_node *rbtree_erase_rebalance(lim_rbtree_node *node, lim_rbtree_node *parent, lim_rbtree_node *root)
{
    lim_rbtree_node *other, *o_left, *o_right;  //point to uncle and uncle's left, right subtree
    while ((!node || node->color == BLACK) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)    //case1:
            {
                other->color = BLACK;
                parent->color = RED;
                root = rbtree_rotate_left(parent, root);
                other = parent->right;
            }

            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color == BLACK)
                {
                    if ((o_left = other->left))
                        o_left->color = BLACK;

                    other->color = RED;
                    root = rbtree_rotate_right(other, root);
                    other = parent->right;
                }

                other->color = parent->color;
                parent->color = BLACK;
                if (other->right)
                    other->right->color = BLACK;

                root = rbtree_rotate_left(parent, root);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                root = rbtree_rotate_right(parent, root);
                other = parent->left;
            }

            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    if ((o_right = other->right))
                        o_right->color = BLACK;

                    other->color = RED;
                    root = rbtree_rotate_left(other, root);
                    other = parent->left;
                }

                other->color = parent->color;
                parent->color = BLACK;
                if (other->left)
                    other->left->color = BLACK;

                root = rbtree_rotate_right(parent, root);
                node = root;
                break;
            }
        }
    }

    if (node)
        node->color = BLACK;

    return root;
}

static void rbtree_reset_minnode(lim_rbtree *tree)
{
    if (tree->minnode->parent == NULL)
        tree->minnode = tree->root;
    else if (tree->minnode->right != NULL)
    {
        //minnode < minnode->right->left < minnode->right
        //minnode->right < minnode->right->right < minnode->parent
        lim_rbtree_node *min = tree->minnode->right;
        lim_rbtree_node *node = tree->minnode->left;
        while (node)
        {
            min = node;
            if (node->left != NULL)
                node = node->left;
            else
                node = node->right;
        }
        tree->minnode = min;
    }
    else
        tree->minnode = tree->minnode->parent;
}

/**
 *\fn           int lim_rbtree_destroy(lim_rbtree *tree)
 *\brief        释放树上所有节点，lim_rbtree结构由调用者负责清除
 *\param[in]    lim_rbtree *tree               树结构
 */
void lim_rbtree_destroy(lim_rbtree *tree)
{
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL)
    {
        pthread_mutex_unlock(&tree->lock);
        return;
    }

    rbtree_destroy_item(tree, tree->root);
    tree->root = NULL;
    tree->cleaner = NULL;
    tree->comparator = NULL;
    tree->copyer = NULL;
    pthread_mutex_unlock(&tree->lock);
    pthread_mutex_destroy(&tree->lock);
    return;
}

static void rbtree_destroy_item(lim_rbtree *tree, lim_rbtree_node *node)
{
    if (node->left)
        rbtree_destroy_item(tree, node->left);
    if (node->right)
        rbtree_destroy_item(tree, node->right);

    rbtree_remove_from_bucket(tree, node, node->key, NULL);
    tree->cleaner(node->key, NULL);
    free(node);
    tree->size --;
}

/**
 *\fn           void lim_rbtree_poll_min(lim_rbtree *tree, void *borderkey, lim_rbtree_item *result)
 *\brief        从树上最小节点开始进行遍历，一直删除到key大于borderkey的节点，删除的值记录放入result,由调用者释放
 *\param[in]    lim_rbtree *tree               树结构
 *\param[in]    void *borderkey                上限key
 *\param[out]   lim_rbtree_item result         符合条件的节点Key-Value列表
 *\return       0成功， -1 失败
 */
int lim_rbtree_poll_min(lim_rbtree *tree, void *borderkey, lim_rbtree_item *result)
{
    pthread_mutex_lock(&tree->lock);
    if (tree == NULL || tree->root == NULL || borderkey == NULL || result == NULL)
    {
        pthread_mutex_unlock(&tree->lock);
        return -1;
    }

    lim_rbtree_node *node;
    while(tree->comparator(borderkey,tree->minnode->key) >= 0)
    {
        node = tree->minnode;
        rbtree_reset_minnode(tree);
        rbtree_delete_node(tree, node);

        // release node but don't release key and value
        if (node->amount == 1)
        {
            lim_rbtree_item *item = (lim_rbtree_item *)malloc(sizeof(lim_rbtree_item));
            item->key = node->key;
            item->value = node->bucket;
            item->next = result->next;
            result->next = item;
        }
        else if (node->amount > 1)
        {
            lim_rbtree_item *head = (lim_rbtree_item *)node->bucket;
            lim_rbtree_item *item = head->next;
            while(item != NULL)
            {
                lim_rbtree_item *next = item->next;
                item->next = result->next;
                result->next = item;
                item = next;
            }
            head->next = NULL;
            free(head);
            tree->cleaner(node->key, NULL);
        }
        free(node);
        tree->size --;
    }
    pthread_mutex_unlock(&tree->lock);
    return 0;
}
