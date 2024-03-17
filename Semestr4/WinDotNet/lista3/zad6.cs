using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class BinaryTreeNode<T>
{
    public T value { get; set; }
    public BinaryTreeNode<T> left;
    public BinaryTreeNode<T> right;
    public BinaryTreeNode(T value, BinaryTreeNode<T> left, BinaryTreeNode<T> right)
    {
        this.value = value;
        this.left = left;
        this.right = right;
    }
    public BinaryTreeNode(T value) : this(value, null, null) { }

    public IEnumerable<T> DFS()
    {
        yield return value;
        if (left != null)
        {
            foreach (var v in left.DFS())
            {
                yield return v;
            }
        }
        if (right != null)
        {
            foreach (var v in right.DFS())
            {
                yield return v;
            }
        }
    }
    public IEnumerable<T> BFS()
    {
        Queue<BinaryTreeNode<T>> queue = new();
        queue.Enqueue(this);
        while (queue.Count > 0)
        {
            BinaryTreeNode<T> node = queue.Dequeue();
            yield return node.value;
            if (node.left != null)
            {
                queue.Enqueue(node.left);
            }
            if (node.right != null)
            {
                queue.Enqueue(node.right);
            }
        }
    }
}

public class Program6
{
    public static void Main(string[] args)
    {
        BinaryTreeNode<int> tree = new(1,
                       new(2, new(4), new(5)),
                                  new(3, new(6), new(7)));
        foreach (var v in tree.DFS())
        {
            Console.Write(v);
            Console.Write(' ');
        }
        Console.Write('\n');
        foreach (var v in tree.BFS())
        {
            Console.Write(v);
            Console.Write(' ');
        }
    }
}