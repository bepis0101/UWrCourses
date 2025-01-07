// Please see documentation at https://learn.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

"use strict";
let connection = new signalR.HubConnectionBuilder().withUrl("/chatHub").build();

connection.on("ReceiveMessage", function (user, message) {
    const messageDiv = document.createElement("div");
    messageDiv.className = "alert alert-primary";
    messageDiv.innerHTML = `<strong>${user}:</strong> ${message}`;
    document.getElementById("chatBox").appendChild(messageDiv);
});

async function start() {
    try {
        await connection.start();
        console.log("SignalR connected")
    } catch (e) {
        console.log(e);
    }
}

connection.onclose(async () => {
    await start();
});

start();

