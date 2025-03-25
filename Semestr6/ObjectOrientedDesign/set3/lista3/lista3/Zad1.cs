using System;
using System.Collections.Generic;
namespace lista3
{
    public class Order
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public Order(int id, string name)
        {
            Id = id;
            Name = name;
        }
    }

    public class OrderManager
    {
        private List<Order> _orders = new List<Order>();
        public Order CreateOrder(int id, string productName)
        {
            var order = new Order(id, productName);
            _orders.Add(order);
            return order;
        }
        public void DisplayOrders()
        {
            foreach(var order in _orders)
            {
                Console.WriteLine($"Order ID: {order.Id}, Product: {order.Name}");
            }
        }
    }

    public class OrderService
    {
        public void ProcessOrder(int id, string productName)
        {
            Console.WriteLine($"Processing order: {id} - {productName}");
        }
    }
    public class OrderController
    {
        private readonly OrderService _service;
        public OrderController(OrderService service)
        {
            _service = service;
        }
        public void HandleOrder(int id, string name)
        {
            Console.WriteLine("Controller: Received order request.");
            _service.ProcessOrder(id, name);
        }
    }

    internal class Zad1
    {
        static void Main1(string[] args)
        {
            var manager = new OrderManager();
            manager.CreateOrder(1, "laptop");
            manager.CreateOrder(2, "pc");
            manager.DisplayOrders();

            var service = new OrderService();
            var controller = new OrderController(service);
            controller.HandleOrder(1, "laptop");
        }
    }
}
