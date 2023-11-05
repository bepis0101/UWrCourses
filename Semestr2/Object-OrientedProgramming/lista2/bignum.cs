/*
Borys Adamiak
lista 2 Programowanie Obiektowe
kompilator mcs bignum.cs a nastepnie ./bignum.exe
zadanie 3
*/
using System;

class BigNum
{
    int num;
    string bignum;
    bool carry;
    public BigNum(int num)
    {
        this.num = num;
        this.bignum = this.num.ToString();
        carry = false;
    }

    string reverse(string s)
    {
        string x = "";
        for(int i = s.Length-1; i >= 0; i--)
        {
            x += s[i];
        }
        return x;
    }

    public void add(int another)
    {
        string x = another.ToString();
        string s = "";
        x = this.reverse(x);
        string y = this.reverse(bignum);
        for(int i = 0; i < Math.Max(x.Length, y.Length); i++)
        {
            if(x.Length <= i)
            {
                int sum = y[i]-'0';
                if(carry == true)
                {
                    sum++;
                    carry = false;
                }
                if(sum >= 10)
                {
                    carry = true;
                    sum %= 10;
                }
                s += sum.ToString();
            }
            else if(y.Length <= i)
            {
                int sum = x[i]-'0';
                if(carry == true)
                {
                    sum++;
                    carry = false;
                }
                if(sum >= 10)
                {
                    carry = true;
                    sum %= 10;
                }
                s += sum.ToString();
            }
            else
            {
                int sum = (x[i]-'0')+(y[i]-'0');
                if(carry == true)
                {
                    sum++;
                    carry = false;
                }
                if(sum >= 10)
                {
                    carry = true;
                    sum %= 10;
                }
                s += sum.ToString();
            } 
        }
        bignum = this.reverse(s);
    }

    public void sub(int another) // odejmuje od wartosci przetrzymywanej w klasie (zakladam ze liczby po wyniku beda nieujemne)
    {
        string x = another.ToString();
        string y = bignum;
        string S = "", s = "";

        if(x.Length < y.Length)
        {
            for(int i = 0; i < (y.Length-x.Length); i++)
            {
                s += "0";
            }
            s += x;
            for(int i = y.Length-1; i >= 0; i--)
            {
                if(s[i] < x[i])
                {
                    carry = true;
                    S += ((s[i]-'0'+10)-(x[i]-'0')).ToString();
                }
                else
                {
                    carry = false;
                    S += ((s[i]-'0')-(x[i]-'0')).ToString();
                }
            }
        }
        else
        {
            for(int i = y.Length-1; i >= 0; i--)
            {
                if(y[i] < x[i])
                {
                    carry = true;
                    S += ((y[i]-'0'+10)-(x[i]-'0')).ToString();
                }
                else
                {
                    carry = false;
                    S += ((y[i]-'0')-(x[i]-'0')).ToString();
                }
            }
        }
        bignum = S;
    }

    public void print()
    {
        Console.WriteLine(bignum);
    }
}

class Program
{
    public static void Main()
    {
        BigNum a;
        a = new BigNum(2546541);
        a.add(329);
        a.print();
        a.sub(458375);
        a.print();

    }
}