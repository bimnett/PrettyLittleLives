const mqtt = require("mqtt");

// HiveMQ cloud cluster configurations
var options = {
  host: '8f604f862afd4b6fbefc164717077e89.s1.eu.hivemq.cloud',
  port: 8883,
  protocol: 'mqtts',
  username: 'lingsv',
  password: 'Ling1234'
}

const client = mqtt.connect(options);

// publish message 
client.on("connect", () => {
  client.publish("pll/sensor", (err) => {
    if (err) {
      console.error("Error publishing message:", err);
    } 
  });
});


