<template>
    <!-- Display the latest MQTT message -->
  <div>mqtt msg: {{ latestMessage }}</div>

  <!-- <Temperature /> is a custom made self closing tag-->
  <Temperature />
  <DecibelLevel/>
  <DanceStop/> 
  
</template>

<script>
  import Temperature from './components/Temperature.vue'
  import DecibelLevel from './components/DecibelLevel.vue'
  import DanceStop from './components/DanceStop.vue'

  export default {
    name: "App",
    
    // connect the componens with the App.vue
    components : {
      Temperature : Temperature,
      DecibelLevel : DecibelLevel,
      DanceStop : DanceStop,
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