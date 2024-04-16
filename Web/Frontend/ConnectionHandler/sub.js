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

// Connect to the broker
client.on("connect", () => {
    client.subscribe("pll/sensor/reading", (err) => {
        if (!err) {
            console.log("Subscribed to pll/sensor/reading topic");
        }
    });
});

// Subscribed topic and message will be displayed
client.on("message", (topic, message) => {
    console.log(`The current decibel in the room is ${topic}: ${message.toString()}`);
    // Cannot use document.querySelector in Node.js environment
});

function changeName(){
    list.textContent = "subbedMessage";
}