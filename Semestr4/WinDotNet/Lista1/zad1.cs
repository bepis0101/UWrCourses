class zad1
{
    public void numbers()
    {
        for (int i = 1; i <= 100000; i++)
        {
            if (checkValidity(i))
            {
                Console.WriteLine(i);
            }
        }
    }
    private bool checkValidity(int n)
    {
        string s = n.ToString();
        int sum = 0;
        for (int i = 0; i < s.Length; i++)
        {
            int k = s[i] - '0';
            sum += k;
            if (k == 0)
            {
                continue;
            }
            if (n % k != 0)
            {
                return false;
            }
        }
        if (n % sum != 0)
        {
            return false;
        }

        return true;
    }
}

class Program
{
    public static void Main1(string[] args)
    {
        zad1 p = new();
        p.numbers();
    }
}