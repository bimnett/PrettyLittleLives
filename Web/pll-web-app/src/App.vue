<template>
  <div>mqtt msg: {{ latestMessage }}</div>
</template>

<script>

  import mqtt from "mqtt";
  import { HOST } from "./credentials";
  import { OPTIONS } from "./credentials";

  export default {
    name: "App",

    data() {
      return {
        latestMessage: "None.",
      };
    },

    mounted() {

      // Connect to MQTT broker
      const client = mqtt.connect(HOST, OPTIONS);

      // Subscribe to the MQTT topic
      client.on("connect", () => {
        client.subscribe("pll/#");
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