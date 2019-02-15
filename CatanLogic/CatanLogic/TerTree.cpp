#include "TerTree.h"






void TerTree::insert(string child, string father)
{
	tree.push_back(child);
	if (!father.empty())
	{
		for (auto c : find(father)->children)
		{
			if (c.empty())
			{
				c = child;
			}
		}
	}
}

TerTreeNode* TerTree::find(string contentToFind)
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

bool TerTree::isInTree(string contentToCheck)
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

size_t TerTree::getDepth(string startingNode)
{
	TerTreeNode* start = find(startingNode);
	depth = 1;
	recursiveDepthCalculator(start);
	return depth;
}

void TerTree::clear()
{
	tree.clear();
}

void TerTree::recursiveDepthCalculator(TerTreeNode* startingNode)
{
	size_t depthUntilNow = depth;
	size_t deepestBranch = depth;
	
	if (!(startingNode->children)[0].empty())
	{
		depth = depthUntilNow;
		depth++;
		recursiveDepthCalculator(find((startingNode->children)[0]));
		if (depth > deepestBranch)
		{
			deepestBranch = depth;
		}
	}
	if (!(startingNode->children)[1].empty())
	{
		depth = depthUntilNow;
		depth++;
		recursiveDepthCalculator(find((startingNode->children)[1]));
		if (depth > deepestBranch)
		{
			deepestBranch = depth;
		}
	}
	if (!(startingNode->children)[2].empty())
	{
		depth++;
		recursiveDepthCalculator(find((startingNode->children)[2]));
		if (depth > deepestBranch)
		{
			deepestBranch = depth;
		}
	}
	
	depth = deepestBranch;
}

 TerTreeNode::TerTreeNode()
 {
 }

 TerTreeNode::TerTreeNode(string content_)
 {
	 content = content_;
 }

 TerTreeNode::~TerTreeNode()
 {
 }

 TerTree::TerTree()
 {
 }

 TerTree::~TerTree()
 {
 }
