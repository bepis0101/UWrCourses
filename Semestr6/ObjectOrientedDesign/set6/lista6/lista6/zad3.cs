using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lista6
{
    public abstract class Tree
    {
    }

    public class TreeLeaf : Tree
    {
    }

    public class TreeNode : Tree
    {
        public Tree Left { get; set; }
        public Tree Right { get; set; }
    }

    public abstract class TreeVisitor
    {
        public int Visit(Tree tree)
        {
            if (tree is TreeNode node)
                return VisitNode(node);
            else if (tree is TreeLeaf leaf)
                return VisitLeaf(leaf);
            else
                return 0;
        }

        public abstract int VisitNode(TreeNode node);
        public abstract int VisitLeaf(TreeLeaf leaf);
    }

    public class DepthVisitor : TreeVisitor
    {
        public override int VisitNode(TreeNode node)
        {
            int leftDepth = node.Left != null ? Visit(node.Left) : 0;
            int rightDepth = node.Right != null ? Visit(node.Right) : 0;

            return 1 + Math.Max(leftDepth, rightDepth);
        }

        public override int VisitLeaf(TreeLeaf leaf)
        {
            return 1;
        }
    }
}
