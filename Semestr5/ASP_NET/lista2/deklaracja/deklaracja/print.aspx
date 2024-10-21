<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="print.aspx.cs" Inherits="deklaracja.print" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h2>Pasek zgłoszenia zadań</h2>
            <table border="1" style="border-collapse: collapse; width: 100%;">
            <!-- Pierwszy wiersz: podstawowe informacje -->
            <tr>
                <th>Imię</th>
                <td><%= Request.QueryString["name"] %></td>
                <th>Nazwisko</th>
                <td><%= Request.QueryString["surname"] %></td>
                <th>Data</th>
                <td><%= Request.QueryString["date"] %></td>
                <th>Nazwa zajęć</th>
                <td><%= Request.QueryString["course"] %></td>
                <th>Numer zestawu</th>
                <td><%= Request.QueryString["list_number"] %></td>
            </tr>

            <!-- Drugi wiersz: numery zadań i punkty -->
            <tr>
                <th colspan="8">Zadania i punkty</th>
            </tr>
            <tr>
                <!-- Kolumna z numerami zadań -->
                <% 
                    if (Session["tasks"] != null)
                    {
                        var tasks = (string[])Session["tasks"];
                        for (int i = 0; i < 10; i++)
                        {
                            %>
                            <td>Zadanie <%= i + 1 %></td>
                            <% 
                        }
                    } 
                %>
            </tr>
            <tr>
                <!-- Kolumna z punktami za zadania -->
                <% 
                    if (Session["tasks"] != null)
                    {
                        var tasks = (string[])Session["tasks"];
                        for (int i = 0; i < 10; i++)
                        {
                            %>
                            <td><%=tasks[i] %></td>
                            <% 
                        }
                    } 
                %>
            </tr>
        </table>
         </div>
    </form>
</body>
</html>
