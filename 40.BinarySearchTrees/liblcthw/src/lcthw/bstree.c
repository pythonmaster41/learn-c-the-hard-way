#include <lcthw/bstree.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>

static int BSTree_default_compare(void *a, void *b);
static int BSTreeNode_traverse(BSTreeNode *node, BSTree_traverse_cb traverse_cb);
static int BSTreeNode_set(BSTreeNode *node, void *key, void *value, BSTree_compare compare_cb);
static BSTreeNode *BSTreeNode_create(void *key, void *value, BSTreeNode *parent);
static BSTreeNode *BSTreeNode_getNode(BSTreeNode *node, void *key, BSTree_compare compare_cb);

BSTree *BSTree_create(BSTree_compare compare_cb)
{
	BSTree *tree = malloc(sizeof(BSTree));
	check_mem(tree);

	tree->count = 0;
	tree->root = NULL;
	tree->compare_cb =
		compare_cb != NULL ? compare_cb : BSTree_default_compare;

	return tree;

error:
	return NULL;
}

void BSTree_destroy(BSTree *map)
{
	// TODO:
}

int BSTree_set(BSTree *map, void *key, void *value)
{
	check(map != NULL, "Map cannot be NULL");

	if (!map->root)
	{
		map->root = BSTreeNode_create(key, value, NULL);
	}
	else
	{
		return BSTreeNode_set(map->root, key, value, map->compare_cb);
	}

	return 0;

error:
	return -1;
}

void *BSTree_get(BSTree *map, void *key)
{
	if (map->root)
	{
		BSTreeNode *node = BSTreeNode_getNode(map->root, key, map->compare_cb);

		return node != NULL ? node->value : NULL;
	}

	return NULL;
}

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb)
{
	check(map != NULL, "Map cannot be NULL");
	check(traverse_cb != NULL, "Traverse callback cannot be NULL");

	if (map->root)
	{
		return BSTreeNode_traverse(map->root, traverse_cb);
	}
	else
	{
		return 0;
	}

error:
	return -1;
}

void *BSTree_delete(BSTree *map, void *key)
{
	if (map->root)
	{
		// TODO:
	}

	return NULL;
}

static int BSTree_default_compare(void *a, void *b)
{
	return bstrcmp((bstring)a, (bstring)b);
}

static int BSTreeNode_traverse(BSTreeNode *node, BSTree_traverse_cb traverse_cb)
{
	check(node != NULL, "Node cannot be NULL");
	check(traverse_cb != NULL, "Traverse callback cannot be NULL");
	int rc = 0;

	if (node->left)
	{
		rc = BSTreeNode_traverse(node->left, traverse_cb);
		if (rc != 0) return rc;
	}

	if (node->right)
	{
		rc = BSTreeNode_traverse(node->right, traverse_cb);
		if (rc != 0) return rc;
	}

	return traverse_cb(node);

error: // fallthrough
	return -1;
}

static int BSTreeNode_set(BSTreeNode *node, void *key, void *value, BSTree_compare compare_cb)
{
	check(node != NULL, "Node cannot be NULL");

	int compareResult = compare_cb(key, node->key);
	if (compareResult == 0)
	{
		node->value = value;
	}
	else if (compareResult > 0)
	{
		if (node->right != NULL)
		{
			return BSTreeNode_set(node->right, key, value, compare_cb);
		}
		else
		{
			node->right = BSTreeNode_create(key, value, node);
		}
	}
	else
	{
		if (node->left != NULL)
		{
			return BSTreeNode_set(node->left, key, value, compare_cb);
		}
		else
		{
			node->left = BSTreeNode_create(key, value, node);
		}
	}

	return 0;

error:
	return -1;
}

static BSTreeNode *BSTreeNode_create(void *key, void *value, BSTreeNode *parent)
{
	BSTreeNode *node = malloc(sizeof(BSTreeNode));
	check_mem(node);

	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;

	return node;

error:
	return NULL;
}

static BSTreeNode *BSTreeNode_getNode(BSTreeNode *node, void *key, BSTree_compare compare_cb)
{
	check(node != NULL, "Node cannot be NULL");
	check(compare_cb != NULL, "Compare callback cannot be NULL");

	int compareResult = compare_cb(key, node->key);
	if (compareResult == 0)
	{
		return node;
	}
	else if (compareResult > 0)
	{
		if (node->right)
		{
			return BSTreeNode_getNode(node->right, key, compare_cb);
		}
	}
	else
	{
		if (node->left)
		{
			return BSTreeNode_getNode(node->left, key, compare_cb);
		}
	}

error:
	return NULL;
}

void BSTreeNode_print(bstring indent, BSTreeNode *node)
{
	check(node != NULL, "Node cannot be NULL");

	if (node->left)
	{
		bstring leftIndent = bformat("%s\t", bdata(indent));
		BSTreeNode_print(leftIndent, node->left);
	}

	printf("%s%s\n", bdata(indent), bdata((bstring)node->key));

	if (node->right)
	{
		bstring rightIndent = bformat("%s\t", bdata(indent));
		BSTreeNode_print(rightIndent, node->right);
	}

error: // fallthrough
	return;
}