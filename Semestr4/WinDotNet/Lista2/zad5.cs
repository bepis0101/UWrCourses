using System;

public class Grid
{
    private int[,] _data;

    public Grid(int rows, int cols)
    {
        if (rows <= 0 || cols <= 0)
        {
            throw new ArgumentException("Rows and columns must be greater than zero.");
        }

        _data = new int[rows, cols];
    }

    public int this[int row, int col]
    {
        get
        {
            ValidateIndices(row, col);
            return _data[row, col];
        }
        set
        {
            ValidateIndices(row, col);
            _data[row, col] = value;
        }
    }

    public int[] this[int row]
    {
        get
        {
            if (row < 0 || row >= _data.GetLength(0))
            {
                throw new IndexOutOfRangeException("Row index out of range.");
            }

            int[] rowData = new int[_data.GetLength(1)];
            for (int i = 0; i < _data.GetLength(1); i++)
            {
                rowData[i] = _data[row, i];
            }
            return rowData;
        }
    }

    private void ValidateIndices(int row, int col)
    {
        if (row < 0 || row >= _data.GetLength(0) || col < 0 || col >= _data.GetLength(1))
        {
            throw new IndexOutOfRangeException("Row or column index out of range.");
        }
    }
}

public class Program5
{
    public static void Main5(string[] args)
    {
        Grid grid = new Grid(4, 4);

        // Ustawianie wartości dla poszczególnych elementów
        grid[2, 2] = 5;
        grid[1, 3] = 8;

        // Pobieranie wartości konkretnego elementu
        int element = grid[1, 3]; // element będzie równy 8

        // Pobieranie całego wiersza
        int[] rowData = grid[1]; // rowData będzie tablicą {0, 0, 0, 8}

        Console.WriteLine(element);
        for(int i = 0; i < rowData.Length ; i++)
        {
            Console.Write(rowData[i]);
            Console.Write(" ");
        }

    }
}