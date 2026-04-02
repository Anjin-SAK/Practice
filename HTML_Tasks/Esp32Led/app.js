// -------- Adafruit Details --------
const USERNAME = "Anjin_AK";   // 👉 Anjin_AK
const AIO_KEY  = "aio_sLUh39IpDGu0e9J0s9IO2T8eVCy1";   // 👉 paste your key here

// -------- MQTT Connection --------
const client = mqtt.connect("wss://io.adafruit.com:443/mqtt/", {
  username: USERNAME,
  password: AIO_KEY
});

// -------- Topic --------
const topic = USERNAME + "/feeds/led";

// -------- Connection Status --------
client.on("connect", () => {
  console.log("Connected to Adafruit MQTT");
  document.getElementById("status").innerText = "Connected";

  // subscribe to same feed (optional but useful)
  client.subscribe(topic);
});

// -------- Receive Data (optional sync) --------
client.on("message", (topic, message) => {
  console.log("Received:", message.toString());
});

// -------- Send Message --------
function sendMessage(msg) {

  if (msg === "ON") {
    client.publish(topic, "On");   // match Adafruit
  } 
  else if (msg === "OFF") {
    client.publish(topic, "Off");  // match Adafruit
  }

  console.log("Sent:", msg);
}


