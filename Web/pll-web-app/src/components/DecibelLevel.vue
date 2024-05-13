<template>
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
      soundLevel: 'null',
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
        console.log(`Sound Level ${this.soundLevel} saved to MongoDB`);
      } catch (error) {
        console.error("Failed to save sound level:", error);
      }
    });
    // test methods without connecting to mqtt
    // await this.saveSoundLevel(this.soundLevel);
    // console.log(`Sound Level ${this.soundLevel} saved to MongoDB`);
  },
  
  methods: {
    async saveSoundLevel(soundLevel) {
      try {
        await axios.post("http://localhost:3000/api/saveSoundLevel", { soundLevel: soundLevel });
      } catch (error) {
        console.error("Failed to save sound level:", error);
      }
    }
  }
};
</script>

<style></style>