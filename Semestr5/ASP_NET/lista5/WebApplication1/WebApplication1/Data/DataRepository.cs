﻿using System.Data.SqlClient;
using WebApplication1.Models;
using Microsoft.Data.SqlClient;
using System.Data;

namespace WebApplication1.Data
{
    public interface IDataRepository : IDisposable
    {
        Task<List<BookModel>> GetAll();
        Task<BookModel>? Get(Guid id);
        Task Add(BookModel model);
        Task Update(BookModel model);
        Task Delete(Guid id);
    }
    public class DataRepository : IDataRepository
    {
        private readonly SqlConnection _connection;
        public DataRepository(IConfiguration configuration)
        {
            _connection = new SqlConnection(configuration.GetConnectionString("DefaultConnection"));
        }
        public async Task<List<BookModel>> GetAll()
        {
            var books = new List<BookModel>();
            using(var connection = _connection)
            {
                await connection.OpenAsync();
                using (var command = new SqlCommand("SELECT * FROM dbo.Books", connection))
                {
                    using (var reader = await command.ExecuteReaderAsync())
                    {
                        while (await reader.ReadAsync())
                        {
                            books.Add(new BookModel
                            {
                                ID = reader.GetGuid(0),
                                Title = reader.GetString(1),
                                Author = reader.GetString(2),
                                ISBN = reader.GetString(3),
                                YearOfRelease = reader.GetInt32(4)
                            });
                        }
                    }
                }
            }    
            return books;
        }
        public async Task<BookModel>? Get(Guid id)
        {
            using(var connection = _connection)
            {
                await connection.OpenAsync();
                using (var command = new SqlCommand("SELECT * FROM Books WHERE ID = @Id", connection))
                {
                    command.Parameters.Add("@Id", SqlDbType.UniqueIdentifier).Value = id;
                    using (var reader = await command.ExecuteReaderAsync())
                    {
                        if (await reader.ReadAsync())
                        {
                            return new BookModel
                            {
                                ID = reader.GetGuid(0),
                                Title = reader.GetString(1),
                                Author = reader.GetString(2),
                                ISBN = reader.GetString(3),
                                YearOfRelease = reader.GetInt32(4)
                            };
                        }
                    }
                }
            }
            return new BookModel();
        }
        public async Task Add(BookModel model)
        {
            using (var connection = _connection)
            {
                await connection.OpenAsync();
                using (var command = new SqlCommand("INSERT INTO Books (ID, Title, Author, ISBN, YearOfRelease) VALUES (@Id, @Title, @Author, @ISBN, @YearOfRelease)", connection))
                {
                    command.Parameters.AddWithValue("@Id", model.ID);
                    command.Parameters.AddWithValue("@Title", model.Title);
                    command.Parameters.AddWithValue("@Author", model.Author);
                    command.Parameters.AddWithValue("@ISBN", model.ISBN);
                    command.Parameters.AddWithValue("@YearOfRelease", model.YearOfRelease);

                    await command.ExecuteNonQueryAsync();
                }
            }
        }

        public async Task Update(BookModel model)
        {
            using (var connection = _connection)
            {
                await connection.OpenAsync();
                using (var command = new SqlCommand("UPDATE Books SET Title = @Title, Author = @Author, ISBN = @ISBN, YearOfRelease = @YearOfRelease WHERE ID = @Id", connection))
                {
                    command.Parameters.AddWithValue("@Id", model.ID);
                    command.Parameters.AddWithValue("@Title", model.Title);
                    command.Parameters.AddWithValue("@Author", model.Author);
                    command.Parameters.AddWithValue("@ISBN", model.ISBN);
                    command.Parameters.AddWithValue("@YearOfRelease", model.YearOfRelease);

                    await command.ExecuteNonQueryAsync();
                }
            }
        }

        public async Task Delete(Guid id)
        {
            using (var connection = _connection)
            {
                await connection.OpenAsync();
                using (var command = new SqlCommand("DELETE FROM Books WHERE ID = @Id", connection))
                {
                    command.Parameters.AddWithValue("@Id", id);

                    await command.ExecuteNonQueryAsync();
                }
            }
        }
        public void Dispose()
        {
            _connection.Dispose();
        }
    }
}
