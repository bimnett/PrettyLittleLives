<template>
    <!-- Display the latest MQTT message -->
  <div class="title" >
    <h1 >Welcome to Pretty Little Lives (PLL)</h1>
  </div>
  <!-- <Temperature /> is a custom made self closing tag--> 
 
  <DecibelLevel />
  <div class="rectangle"></div>
  <DanceStop/>
  <div class="rectangle"></div>
  <Temperature />
  <div class="rectangle"></div>
  <SoundGame/>

</template>

<script>
  import Temperature from './components/Temperature.vue'
  import DecibelLevel from './components/DecibelLevel.vue'
  import DanceStop from './components/DanceStop.vue'
  import SoundGame from './components/SoundGame.vue'

  export default {
    name: "App",
    
    // connect the componens with the App.vue
    components : {
      Temperature : Temperature,
      DecibelLevel : DecibelLevel,
      DanceStop : DanceStop,
      SoundGame : SoundGame
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
.title {
  border: 0.0px solid;
  width: 100%;
  padding: 10px;
  background-color: #FFDE59;
  text-align:center
}
.rectangle {
  height: 20px;
  width: 5000;
  background-color:  #FFDE59;
}
</style>