using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using System.Threading.Tasks;
using Dapper;
using System.Data;
using System.Data.SqlClient;

namespace Task3
{
    public interface IDapperRepository : IDisposable
    {
        public Task<IEnumerable<object>> GetAllAsync();
    }
    // You may need to install the Microsoft.AspNetCore.Http.Abstractions package into your project
    public class DapperRepository : IDapperRepository
    {
        private readonly IDbConnection _connection;

        public DapperRepository(IConfiguration configuration)
        {
            _connection = new SqlConnection(configuration.GetConnectionString("DefaultConnection"));
        }
        public async Task<IEnumerable<object>> GetAllAsync()
        {
            return await _connection.QueryAsync<object>("SELECT * FROM Table");
        }
        public void Dispose()
        {
            _connection?.Dispose();
        }   

    }

    // Extension method used to add the middleware to the HTTP request pipeline.
    public static class DapperRepositoryExtensions
    {
        public static IApplicationBuilder UseDapperRepository(this IApplicationBuilder builder)
        {
            return builder.UseMiddleware<DapperRepository>();
        }
    }
}
