<template>
    <!-- Display the latest MQTT message -->
  <div>mqtt msg: {{ latestMessage }}</div>
</template>

<script>
  // Import the MQTT library and credentials for cluster
  import mqtt from "mqtt";
  import { HOST } from "./credentials";

  export default {
    name: "App",

    data() {
      return {
        // Before any message is received, none as default. 
        latestMessage: "None.",
      };
    },

    mounted() {

      // Connect to MQTT broker
      const client = mqtt.connect(HOST);

      // Subscribe to the MQTT topic
      client.on("connect", () => {
        client.subscribe("pll/#");
      });

      // When connection failed
      client.on('error', (error) => {
        console.error('Connection failed:', error);
        client.end();
      });

      // Receive messages
      client.on("message", (topic, message) => {
        // Update the latest message
        this.latestMessage = message.toString();
      });

    },

  };

</script>

<style>
</style>