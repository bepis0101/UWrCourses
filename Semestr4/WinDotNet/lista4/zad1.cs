public static class StringExtension
{
    public static bool isPalindrome(this string str)
    {
        int i = 0;
        int j = str.Length - 1;
        while (i < j)
        {
            while (str[i] == ' ')
            {
                i++;
            }
            while (str[j] == ' ')
            {
                j--;
            }
            if (str[i] != str[j])
            {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
}

public class Task1
{
    public static void Main1(string[] args)
    {
        string str = "madam";
        Console.WriteLine(str.isPalindrome());
        str = "hello";
        Console.WriteLine(str.isPalindrome());
    }
}