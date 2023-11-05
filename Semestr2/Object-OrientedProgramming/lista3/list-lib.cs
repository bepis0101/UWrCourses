using System;

class Elem<T>
{
    public Elem<T> prev;
    public Elem<T> next;
    public T val;
    public Elem(T val)
    {
        this.val = val;
    }
}

public class List<T>
{
    Elem<T> front;
    Elem<T> back;
    int size;
    public List()
    {
        size = 0;
        front = back = null;
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
        if(size == 0)
        {
            throw new Exception("Empty list! Don't pop!!!");
        }
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
        if(size == 0)
        {
            throw new Exception("Empty list! Don't pop!!!");
        }
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

}

