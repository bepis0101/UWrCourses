/* 
 * Borys Adamiak
 * Zadanie 1 lista 6
 * javac Program.java     java Program.class
 */
package lista6;
import java.io.*;
import java.util.ArrayList;
class Elem<T> implements Serializable
{
    public Elem<T> prev;
    public Elem<T> next;
    public T val;
    public Elem(T val)
    {
        this.val = val;
    }
}

class List<T> implements Serializable
{
    private static final long serialVersionUID = 123L;
    Elem<T> front;
    Elem<T> back;
    int size;
    public List()
    {
        size = 0;
        front = back = null;
    }
    public int size()
    {
        return size;
    }
    public void push_back(T value)
    {
        if(back == null)
        {   
            back = new Elem<T>(value);
            front = back;
        }
        else
        {
            back.next = new Elem<T>(value);
            back.next.prev = back;
            back = back.next;
        }
        size++;
    }

    public void push_front(T value)
    {
        if(front == null)
        {
            front = new Elem<T>(value);
            back = front;
        }
        else
        {
            front.prev = new Elem<T>(value);
            front.prev.next = front;
            front = front.prev;
        }
        size++;
    }

    public T pop_back()
    {
        if(size == 1)
        {
            T res = back.val;
            front = null;
            back = null;
            size--;
            return res;
        }
        else 
        {
            T res = back.val;
            back = back.prev;
            back.next = null;
            size--;
            return res;
        }
    }
    public T pop_front()
    {
        if(size == 1)
        {
            T res = front.val;
            front = null;
            back = null;    
            size--;
            return res;
        }
        else
        {
            T res = front.val;
            front = front.next;
            front.prev = null;
            size--;
            return res;
        }
    }
    public T[] toArray(T[] arr)
    {
        ArrayList<T> res = new ArrayList<>();
        while(size > 0)
        {
            res.add(this.pop_front());
        }
        return res.toArray(arr);
    }
}
class Main
{
    public static void main(String[] args) throws IOException, ClassNotFoundException
    {
        List<Integer> lst = new List<>();
        lst.push_back(10);
        lst.push_front(18);
        lst.push_back(5);
        lst.push_back(15);
        try(ObjectOutputStream mem = new ObjectOutputStream(new FileOutputStream("memory"))) {
            mem.writeObject(lst);
        }
        try(ObjectInputStream red = new ObjectInputStream(new FileInputStream("memory")))
        {
            List<?> lst1 = (List<?>)red.readObject();
            while(lst1.size() > 0)
            {
                System.out.print(lst1.pop_front());
                System.out.print(' ');
            }
        }

            
    }
}
