#include "QuadTree.h"






bool QuadTree::insert(string child, string father)
{
	if (!father.empty() && find(father)->childrenCount() < 4)
	{
		(find(father)->children).push_back(child);
		tree.push_back(child);
		return true;
	}
	else
	{
		return false;
	}
}

QuadTreeNode* QuadTree::find(string contentToFind)
{
	if (isInTree(contentToFind))
	{
		for (auto node : tree)
		{
			if (node.content == contentToFind)
			{
				return &node;
			}
		}
	}
	else
	{
		return nullptr;
	}
}

bool QuadTree::isInTree(string contentToCheck)
{
	for (auto node : tree)
	{
		if (node.content == contentToCheck)
		{
			return true;
		}
	}
	return false;
}

size_t QuadTree::getDepth(string startingNode)
{
	size_t startingNodeChildren = find(startingNode)->childrenCount();
	if (startingNodeChildren)
	{
		size_t deepestBranch = 0, secondDeepestBranch = 0;
		for (auto child : find(startingNode)->children)
		{
			size_t branchDepth = auxGetDepth(child);
			if (branchDepth > deepestBranch)
			{
				deepestBranch = branchDepth;
			}
			else if (branchDepth > secondDeepestBranch)
			{
				secondDeepestBranch = branchDepth;
			}
		}

		return deepestBranch + secondDeepestBranch + 1;
	}
	else
	{
		return auxGetDepth(startingNode);
	}
}

void QuadTree::clear()
{
	tree.clear();
}

size_t QuadTree::auxGetDepth(string startingNode)
{
	QuadTreeNode* start = find(startingNode);
	depth = 1;
	recursiveDepthCalculator(start);
	return depth;
}

void QuadTree::recursiveDepthCalculator(QuadTreeNode* startingNode)
{
	size_t depthUntilNow = depth;
	size_t deepestBranch = depth;
	
	for (auto child : startingNode->children)
	{
		if (!child.empty())
		{
			depth = depthUntilNow;
			depth++;
			recursiveDepthCalculator(find(child));
			if (depth > deepestBranch)
			{
				deepestBranch = depth;
			}
		}
	}
	
	depth = deepestBranch;
}

 QuadTreeNode::QuadTreeNode()
 {
 }

 QuadTreeNode::QuadTreeNode(string content_)
 {
	 content = content_;
 }

 QuadTreeNode::~QuadTreeNode()
 {
 }

 size_t QuadTreeNode::childrenCount()
 {
	 return children.size();
 }

 QuadTree::QuadTree()
 {
 }

 QuadTree::~QuadTree()
 {
 }
