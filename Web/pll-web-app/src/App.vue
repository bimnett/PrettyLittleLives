<template>
    <!-- Display the latest MQTT message -->
  <div>mqtt msg: {{ latestMessage }}</div>

  <!-- <Temperature /> is a custom made self closing tag-->
  <Temperature />
  <DecibelLevel/>
  
</template>

<script>
  import Temperature from './components/Temperature.vue'
  import DecibelLevel from './components/DecibelLevel.vue'

  export default {
    name: "App",
    
    // connect the componens with the App.vue
    components : {
      Temperature : Temperature
    },

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