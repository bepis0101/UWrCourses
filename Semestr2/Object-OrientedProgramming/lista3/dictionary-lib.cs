using System

public class Dictionary <K, V>
{
    Tuple<K, V>[] dic;
    public Dictionary()
    {
        dic = new Tuple<K, V>[6000000];
    }
}