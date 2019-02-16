#pragma once
#include <list>
#include <vector>
#include <string>
#include <cinttypes>

using namespace std;

class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(string content_);
	virtual ~QuadTreeNode();

	size_t childrenCount();
	void addChild(string child);

	string content;
	vector< string > children;
};

struct BranchDepthRecorder
{
	size_t depth;
	string startingNode;
};

class QuadTree
{
public:
	QuadTree();
	virtual ~QuadTree();

	// Inserts the given node as a child of the given father.
	bool insert(string child, string father = string());
	// Returns pointer to QuadTreeNode whose content is the given, otherwise nullptr;
	QuadTreeNode* find(string contentToFind);
	// Checks if there is a node in the tree whose content is the given.
	bool isInTree(string contentToCheck);
	// Returns depth of the tree.
	size_t getDepth(string startingNode);
	// Clears the tree.
	void clear();

private:
	vector< QuadTreeNode > tree;
	size_t depth;

	// For the special case when the last Road added is in uniting two other branches.
	size_t auxGetDepth(string startingNode);
	// Recursively calculates the depth of the tree and modifies depth;
	void recursiveDepthCalculator(QuadTreeNode* startingNode);
};
