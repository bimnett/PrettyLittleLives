<template>
    <div>Current temperature : {{ temp }} celsius</div>
  </template>
  
  <script>
  // Import the MQTT library and credentials for cluster
  import mqtt from "mqtt";
  import axios from "axios";
  import { HOST } from "@/credentials";

  export default {
    name: "Temperature",
  
    data() {
      return {
        temp: "nothing",
      };
    },
  
    async mounted() {
      const client = mqtt.connect(HOST);
  
      client.on("connect", () => {
        client.subscribe("pll/sensor/temp");
      });
  
      client.on('error', (error) => {
        console.error('Connection failed:', error);
        client.end();
      });
  
      client.on("message", async (topic, message) => {
        this.temp = message.toString();
  
        try {
          await this.saveTemperature(this.temp);
          console.log(`Temperature ${this.temp} saved to MongoDB`);
        } catch (error) {
          console.error('Failed to save temperature:', error);
        }
      });
        // test methods without connecting to mqtt
        // await this.saveTemperature("0");
        // console.log(`Temperature saved to MongoDB`);
    },
  
    methods: {
    // Function to send HTTP post request to express server "http://localhost:3000/api/saveTemperature"
      async saveTemperature(temp) {
        try {
          await axios.post("http://localhost:3000/api/saveTemperature", { temperature: temp });
        } catch (error) {
          console.error("Failed to save temperature:", error);
        }
      }
    }
  };
  </script>
  
  <style></style>