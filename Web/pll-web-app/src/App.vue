<template>
    <!-- Display the latest MQTT message -->
  <div>mqtt msg: {{ latestMessage }}</div>

  <!-- <Temperature /> is a costume made self closing tag-->
  <Temperature />
</template>

<script>
  import Temperature from './components/Temperature.vue'

  export default {
    name: "App",
    
    // connect the componens with the App.vue
    components : {
      Temperature : Temperature
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