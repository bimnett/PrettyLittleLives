<template>
    <div>Current decibel level: {{ soundLevel }} db</div>
  </template>
  
  <script>
  import mqtt from "mqtt"; 
  import {HOST} from "@/credentials";
  
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
        });

    },

};
  

  </script>
  
  <style></style>