using System.Data.SqlClient;

class StudentDatabase
{
    private readonly string _connectionString;
    public StudentDatabase(string connectionString)
    {
        _connectionString = connectionString;
    }

    public int CheckIfPersonExists(string name, string surname, DateTime date)
    {
        try
        {
            using(SqlConnection con = new SqlConnection(_connectionString))
            {
                con.Open();
 
                using(SqlCommand cmd = con.CreateCommand())
                {
                    cmd.CommandText = "SELECT ID FROM Students WHERE Name = @Name AND Surname = @Surname AND Date = @Date";
                    cmd.Parameters.AddWithValue("@Name", name);
                    cmd.Parameters.AddWithValue("@Surname", surname);
                    cmd.Parameters.AddWithValue("@Date", date);
                    
                    SqlDataReader reader = cmd.ExecuteReader();
                    if(reader.HasRows)
                    {
                        return reader.GetInt32(0);
                    }
                    else
                    {
                        cmd.CommandText = "INSERT INTO Students (Name, Surname, Date) VALUES (@Name, @Surname, @Date)";
                        cmd.ExecuteNonQuery();
                        cmd.CommandText = "SELECT ID FROM Students WHERE Name = @Name AND Surname = @Surname AND Date = @Date";
                        reader = cmd.ExecuteReader();
                        reader.Read();
                        return reader.GetInt32(0);

                    }
                }
            }
        }
        catch(SqlException ex)
        {
            Console.WriteLine(ex.Message);
        }
        return -1 ;
    }

    public int getCityId(string name)
    {
        try
        {
            using (SqlConnection con = new SqlConnection(_connectionString))
            {
                con.Open();

                using (SqlCommand cmd = con.CreateCommand())
                {
                    cmd.CommandText = "SELECT Id FROM Cities WHERE Name = @Name";
                    cmd.Parameters.AddWithValue("@Name", name);

                    SqlDataReader reader = cmd.ExecuteReader();
                    if (reader.HasRows)
                    {
                        reader.Read();
                        return reader.GetInt32(0);
                    }
                    else
                    {
                        cmd.CommandText = "INSERT INTO Cities (Name) VALUES (@Name)";
                        cmd.ExecuteNonQuery();
                        return getCityId(name);
                    }
                }
            }
        }
        catch (SqlException ex)
        {
            Console.WriteLine(ex.Message);
        }
        return -1;
    }

    public int addAddress(string street, string houseNum, string flatNum, string zipCode, string city)
    {
        try
        {
            using (SqlConnection con = new SqlConnection(_connectionString))
            {
                con.Open();

                using (SqlCommand cmd = con.CreateCommand())
                {
                    cmd.CommandText = "INSERT INTO Addresses (Street, HouseNum, FlatNum, ZipCode, CityId) VALUES (@Street, @HouseNum, @FlatNum, @ZipCode, @CityId)";
                    cmd.Parameters.AddWithValue("@Street", street);
                    cmd.Parameters.AddWithValue("@HouseNum", houseNum);
                    cmd.Parameters.AddWithValue("@FlatNum", flatNum);
                    cmd.Parameters.AddWithValue("@ZipCode", zipCode);
                    cmd.Parameters.AddWithValue("@CityId", getCityId(city));
                    cmd.ExecuteNonQuery();
                    cmd.CommandText = "SELECT Id FROM Addresses WHERE Street = @Street AND HouseNum = @HouseNum AND FlatNum = @FlatNum AND ZipCode = @ZipCode AND CityId = @CityId";
                    SqlDataReader reader = cmd.ExecuteReader();
                    reader.Read();
                    return reader.GetInt32(0);
                }
            }
        }
        catch (SqlException ex)
        {
            Console.WriteLine(ex.Message);
        }
        return -1;
    }



    public void AddStudent(string name, string surname, DateTime date, string street, string houseNum, string flatNum, string zipCode, string city)
    {
        try
        {
            using(SqlConnection con = new SqlConnection(_connectionString))
            {
                con.Open();
 
                using(SqlCommand cmd = con.CreateCommand())
                {
                    int Student_ID = CheckIfPersonExists(name, surname, date);
                    int AddressID =  addAddress(street, houseNum, flatNum, zipCode, city);
                    cmd.Parameters.AddWithValue("@StudentId", Student_ID);
                    cmd.Parameters.AddWithValue("@AddressId", AddressID);
                    cmd.CommandText = "INSERT INTO StudentAddresses (StudentId, AddressId) VALUES (@StudentId, @AddressId)";
                }
            }
        }
        catch(SqlException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        string connectionString = "Data Source=(localdb)\\MSSQLLocalDB;Initial Catalog=Students;";
    }
}