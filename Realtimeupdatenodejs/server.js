const express = require("express");
const http = require("http");
const { Server } = require("socket.io");
const mqtt = require("mqtt");
const cors = require("cors");

const app = express();
app.use(cors());

const server = http.createServer(app);
const io = new Server(server, {
  cors: { origin: "*" }
});

// ---------- MQTT (Adafruit IO) ----------
const AIO_USERNAME = "Anjin_AK";
const AIO_KEY = "aio_Tslr83yMfOv0DI15dihSDJXqIVDF";

const client = mqtt.connect("mqtt://io.adafruit.com", {
  username: AIO_USERNAME,
  password: AIO_KEY
});

// ---------- Feed ----------
const topic = `${AIO_USERNAME}/feeds/distance`;

// ---------- MQTT Connect ----------
client.on("connect", () => {
  console.log("MQTT Connected!");
  client.subscribe(topic);
});

client.on("error", (err) => {
  console.log("MQTT Error:", err);
});

// ---------- MQTT Receive ----------
client.on("message", (topic, message) => {
  const value = message.toString();
  console.log("Distance:", value);

  // Send to website in real-time
  io.emit("distance", value);
});

// ---------- WebSocket ----------
io.on("connection", (socket) => {
  console.log("Client connected");
});

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

// ---------- Server ----------
server.listen(3000, () => {
  console.log("Server running on http://localhost:3000");
});