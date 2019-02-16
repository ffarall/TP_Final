#include "QuadTree.h"






bool QuadTree::insert(string child, string father)
{
	if (!father.empty())
	{
		QuadTreeNode* parent = find(father);
		if (parent->childrenCount() < 4)
		{
			parent->addChild(child);
			tree.push_back(child);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		tree.push_back(child);
		return true;
	}
}

QuadTreeNode* QuadTree::find(string contentToFind)
{
	if (isInTree(contentToFind))
	{
		for (int i = 0; i < tree.size(); i++)
		{
			if (tree[i].content == contentToFind)
			{
				return &tree[i];
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
	if (startingNodeChildren > 1)
	{
		BranchDepthRecorder deepestBranch, secondDeepestBranch;
		deepestBranch.depth = 0;
		secondDeepestBranch.depth = 0;
		for (auto child : find(startingNode)->children)
		{
			size_t branchDepth = auxGetDepth(child);
			if (branchDepth > deepestBranch.depth)
			{
				deepestBranch.depth = branchDepth;
				deepestBranch.startingNode = child;
			}
			else if (branchDepth > secondDeepestBranch.depth)
			{
				secondDeepestBranch.depth = branchDepth;
				secondDeepestBranch.startingNode = child;
			}
		}

		if ((deepestBranch.startingNode)[0] == (secondDeepestBranch.startingNode)[0] || (deepestBranch.startingNode)[1] == (secondDeepestBranch.startingNode)[1])
		{
			return deepestBranch.depth + secondDeepestBranch.depth;
		}
		else
		{
			return deepestBranch.depth + secondDeepestBranch.depth + 1;
		}
	}
	else
	{
		return auxGetDepth(startingNode) + 1;
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

 void QuadTreeNode::addChild(string child)
 {
	 children.push_back(child);
 }

 QuadTree::QuadTree()
 {
 }

 QuadTree::~QuadTree()
 {
 }
