<template>
    <!-- Display the latest MQTT message -->
  <div>mqtt msg: {{ latestMessage }}</div>
  <DecibelLevel/>
  
</template>

<script>
  // Import the MQTT library and credentials for cluster
  import mqtt from "mqtt";
  import { HOST } from "./credentials";
  import DecibelLevel from './components/DecibelLevel.vue'

  export default {
    name: "App",

    components : {
      DecibelLevel : DecibelLevel
    },

    data() {
      return {
        // Before any message is received, none as default. 
        latestMessage: "None.",
      };
    },
  };

  

</script>

<style>
</style>