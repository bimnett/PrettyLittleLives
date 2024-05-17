<template>
  <h2>Decibel Level</h2>
<div>Current decibel level: {{ soundLevel }} db</div>
</template>

<script>
import mqtt from "mqtt";
import axios from "axios";
import { HOST } from "@/credentials";

export default {
name: "DecibelLevel",

  data() {
    return {
      soundLevel: '-', 
    };
  },

async mounted() {
  // Connect to MQTT broker
  const client = mqtt.connect(HOST);

  // Subscribe to the MQTT topic
  client.on("connect", () => {
    client.subscribe("pll/sensor/soundLevel");
  });

  // When connection fails
  client.on("error", (error) => {
    console.error("Connection failed:", error);
    client.end();
  });

  // Receive messages
  client.on("message", async (topic, message) => {
    // Update the latest message
    this.soundLevel = message.toString();
    try {
      // Save the sound level to MongoDB database
      await this.saveSoundLevel(this.soundLevel);
      console.log("Sound Level ${this.soundLevel} saved to MongoDB");
    } catch (error) {
      console.error("Failed to save sound level:", error);
    }
  });
},

methods: {
  // Function to send HTTP post request to express server "http://localhost:3000/api/saveSoundLevel"
  async saveSoundLevel(soundLevelValue) {
    try {
      await axios.post('http://localhost:3000/api/saveSoundLevel', { soundLevelValue: soundLevelValue })
    } catch (error) {
      console.error("Failed to save sound level:", error);
    }
  }
}
};
</script>

<style scoped></style>