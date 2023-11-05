/* 
 * Borys Adamiak
 * Zadanie 4 lista 6
 * javac Program.java     java Program.class
 */

package lista6;
import java.util.Arrays;
import java.util.ArrayList;
class mergesort <T extends Comparable<T>> extends Thread
{
    public T[] array;

    public mergesort(T[] array)
    {
        this.array = array;
    }
    public int size()
    {
        return array.length;
    }

    private T[] merge(mergesort<T> l, mergesort<T> r) throws InterruptedException
    {
        l.start();
        r.start();
        l.join();
        r.join();

        ArrayList<T> res = new ArrayList<>();
        int i = 0;
        int j = 0;
        while(i < l.size() && j < r.size())
        {
            if(l.array[i].compareTo(r.array[j]) <= 0)
            {
                res.add(l.array[i++]);
            }
            else
            {
                res.add(r.array[j++]);
            }
        }
        while(i < l.size())
        {
            res.add(l.array[i++]);
        }
        while(j < r.size())
        {
            res.add(r.array[j++]);
        }
        return res.toArray(l.array);
    }
    public void run()
    {
        if(this.size() < 2) return;
        int mid = this.size()/2;
        try
        {
            mergesort<T> l = new mergesort<>(Arrays.copyOfRange(array, 0, mid));
            mergesort<T> r = new mergesort<>(Arrays.copyOfRange(array, mid, this.size()));
            array = merge(l, r);
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
    }   
    public static<T extends Comparable<T>> T[] sort(T[] array) throws InterruptedException
    {
        mergesort<T> ms = new mergesort<>(array);
        ms.start();
        ms.join();
        return ms.array;
    }
}
class Program
{
    public static void main(String[] args) throws InterruptedException
    {
        Integer[] array = {5, 7, 12, 8, 1, 3, 4};
        System.out.println(Arrays.toString(array));
        array = mergesort.sort(array);
        System.out.println(Arrays.toString(array));
        
        String[] array1 = {"pies", "kot", "zebra", "lew", "pingwin", "lama", "alpaka"};
        System.out.println(Arrays.toString(array1));
        array1 = mergesort.sort(array1);
        System.out.println(Arrays.toString(array1));
    }
}
