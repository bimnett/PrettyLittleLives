<template>
    <div>Current decibel level: {{ soundLevel }} db</div>
  </template>
  
  <script>
  // Import the MQTT library and credentials for cluster
  import mqtt from "mqtt"; 
  import {HOST} from "@/credentials";
  import { saveSoundLevel } from "../databaseConnection";
  
  export default {
    name: "DecibelLevel", 

    data() {
      return {
        soundLevel: 'null', 
      };
    },

    mounted() {

     // Connect to MQTT broker
        const client = mqtt.connect(HOST);

        // Subscribe to the MQTT topic
        client.on("connect", () => {
            client.subscribe("pll/sensor/soundLevel");
        });

        // When connection failed
        client.on('error', (error) => {
            console.error('Connection failed:', error);
            client.end();
        });

        // Receive messages
        client.on("message", (topic, message) => {
        // Update the latest message
            this.soundLevel = message.toString();
            saveSoundLevel(this.soundLevel);
        });

    },

};
  

  </script>
  
  <style></style>