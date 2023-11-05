/*
Borys Adamiak
Programowanie Obiektowe - Lista 4
Zadanie 3
mcs grafy.cs ./grafy.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;

interface IGraph
{
    int vertex{get;}
    int edge{get;}
    void addEdge(string parent, string kid);
    void remove(string parent, string kid);
    List<string> graph(string node);

}
class MatrixGraph : IGraph
{
    int vertecies;
    int edges;
    Dictionary <string, int> v;
    Dictionary <int, string> names;
    bool[,] matrix;
    public MatrixGraph(int vertecies)
    {
        this.vertecies = vertecies;
        edges = 0;
        matrix = new bool[vertecies, vertecies];
        v = new Dictionary<string, int>();
        names = new Dictionary<int, string>();
    }
    public int vertex
    {
        get {return this.vertecies;}
    }
    public int edge
    {
        get {return this.edges;}
    }
    int find(string s)
    {
        return v.ContainsKey(s) ? v[s] : v.Count;
    }


    public void addEdge(string parent, string kid)
    {
        int parent_pointer = find(parent);
        if(parent_pointer == v.Count)
        {
            v.Add(parent, parent_pointer);
            names.Add(parent_pointer, parent);
        }
        int kid_pointer = find(kid);
        if(kid_pointer == names.Count)
        {
            names.Add(kid_pointer, kid);
            v.Add(kid, kid_pointer);
        }
        matrix[kid_pointer, parent_pointer] = true;
        matrix[parent_pointer, kid_pointer] = true;
        edges++;
    }

    public void remove(string kid, string parent)
    {
        int kid_pointer = find(kid);
        int parent_pointer = find(parent);
        if(parent_pointer == v.Count || kid_pointer == names.Count) return;
        matrix[kid_pointer, parent_pointer] = false;
        matrix[parent_pointer, kid_pointer] = false;
        edges--;
    }

    public List<string> graph(string node)
    {
        int node_ptr = find(node);
        List<string> neighbours = new List<string>();
        if(node_ptr == v.Count) return neighbours;
        for(int i = 0; i < vertecies; i++)
        {
            if(matrix[node_ptr, i])
            {
                neighbours.Add(names[i]);
            }
        }
        return neighbours;
    }

    public string print(){
        string res = "";
        foreach(KeyValuePair<int, string> name in names){
            res += name.Value + " -> ";
            res += string.Join(", ", graph(name.Value));
            res += "\n";
        }
        return res;
    }

}
class ListGraph : IGraph
{
    int vertecies;
    int edges;
    Dictionary <string, int> v;
    Dictionary <int, string> names;
    List<string>[] Graph;
    public ListGraph(int vertecies)
    {
        this.vertecies = vertecies;
        edges = 0;
        Graph = new List<string>[vertecies];
        for(int i = 0; i < vertecies; i++)
        {
            Graph[i] = new List<string>();
        }
        names = new Dictionary <int, string>();
        v = new Dictionary<string, int>();
    }
    public int vertex
    {
        get {return this.vertecies;}
    }
    public int edge
    {
        get {return this.edges;}
    }

    int find(string s)
    {
        return v.ContainsKey(s) ? v[s] : v.Count;
    }


    public void addEdge(string parent, string kid)
    {
        int parent_pointer = find(parent);
        if(parent_pointer == v.Count)
        {
            v.Add(parent, parent_pointer);
            names.Add(parent_pointer, parent);
        }
        int kid_pointer = find(kid);
        if(kid_pointer == names.Count)
        {
            names.Add(kid_pointer, kid);
            v.Add(kid, kid_pointer);
        }
        Graph[kid_pointer].Add(parent);
        Graph[parent_pointer].Add(kid); 
        edges++;
    }

    public void remove(string kid, string parent)
    {
        int kid_pointer = find(kid);
        int parent_pointer = find(parent);
        if(parent_pointer == v.Count || kid_pointer == names.Count) return;
        Graph[kid_pointer].Remove(parent);
        Graph[parent_pointer].Remove(kid);
        edges--;
    }
    public List<string> graph(string node)
    {
        if(!v.ContainsKey(node)) return new List<string>();
        int node_pointer = v[node];
        return Graph[node_pointer];
    }

    public string print(){
        string res = "";
        foreach(KeyValuePair<int, string> name in names){
            res += name.Value + " -> ";
            res += string.Join(", ", Graph[name.Key]);
            res += "\n";
        }
        return res;
    }
    
}

class Randomm : Random
{
    public int rand_int(int min, int max)
    {
        return Next(min, max);
    }
    public string rand_string(int n)
    {
        string res = "";
        for(int i = 0; i < n; i++)
        {
            res += (char)(rand_int('a', 'z'+1));
        }
        return res;
    }
    public string create()
    {
        return rand_string(rand_int(1, 32));
    }
}

class GraphOperations
{
    public static IGraph create_random(IGraph G, int vertecies, int edges)
    {
        Randomm rnd = new Randomm();
        List<string> v = new List<string>();
        if(G is ListGraph) G = new ListGraph(vertecies);
        if(G is MatrixGraph) G = new MatrixGraph(vertecies);
        for(int i = 0; i < vertecies; i++)
        {
            v.Add(rnd.create());
        }
        for(int i = 0; i < edges; i++)
        {
            int x = rnd.rand_int(0, vertecies), y = rnd.rand_int(0, vertecies);
            while(x == y)
            {
                x = rnd.rand_int(0, vertecies);
                y = rnd.rand_int(0, vertecies);
            }
            G.addEdge(v[x], v[y]);
        }
        return G;
    }

    public static List<string> shortest_path(IGraph G, string start, string end)
    {
        Queue<string> q = new Queue<string>();
        HashSet<string> vis = new HashSet<string>();
        Dictionary<string, string> father = new Dictionary <string, string>();
        q.Enqueue(start);
        while(q.Count != 0)
        {
            string current = q.Dequeue();
            vis.Add(current);
            if(current == end) break;
            foreach(string s in G.graph(current))
            {
                if(!vis.Contains(s))
                {
                    father.Add(s, current);
                    q.Enqueue(s);
                }
            }
        }
        List<string> res = new List<string>();
        for(string s = end; father.ContainsKey(s); s = father[s])
        {
            res.Add(s);
        }
        if(res.Count > 0 || start == end) res.Add(start);
        res.Reverse();
        return res;
    }

}

class Program
{
    public static void Main()
    {
        ListGraph G = new ListGraph(5);
        G.addEdge("a", "d");
        G.addEdge("b", "a");
        G.addEdge("c", "d");
        G.addEdge("e", "a");
        Console.WriteLine(G.print());
        MatrixGraph M = new MatrixGraph(10);
        Randomm rnd = new Randomm();
        Console.WriteLine(rnd.create());
        M = (MatrixGraph)GraphOperations.create_random(M, 10, 12);
        Console.WriteLine(M.print());
        G.remove("a", "e");
        Console.WriteLine(G.print());
        List<string> path = new List<string>();
        path = GraphOperations.shortest_path(G, "a", "c");
        for(int i = 0; i < path.Count; i++)
        {
            Console.Write(path[i]);
            Console.Write(" ");
        }
    }
}