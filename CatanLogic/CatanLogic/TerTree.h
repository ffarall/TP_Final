#pragma once
#include <list>
#include <array>
#include <string>
#include <cinttypes>

using namespace std;

class TerTreeNode
{
public:
	TerTreeNode();
	TerTreeNode(string content_);
	virtual ~TerTreeNode();

	string content;
	array< string, 3 > children;
};

class TerTree
{
public:
	TerTree();
	virtual ~TerTree();

	// Inserts the given node as a child of the given father.
	void insert(string child, string father = string());
	// Returns pointer to TerTreeNode whose content is the given, otherwise nullptr;
	TerTreeNode* find(string contentToFind);
	// Checks if there is a node in the tree whose content is the given.
	bool isInTree(string contentToCheck);
	// Returns depth of the tree.
	size_t getDepth(string startingNode);
	// Clears the tree.
	void clear();

private:
	list< TerTreeNode > tree;
	size_t depth;

	// Recursively calculates the depth of the tree and modifies depth;
	void recursiveDepthCalculator(TerTreeNode* startingNode);
};
