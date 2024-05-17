<template>

  <div class="space"><br></div>
  <div class = 'container'>
    <div class="box">
      <!-- custom-made tag <Temperature/>, is self-closing -->
      <Temperature/>
    </div>
    <div class="box">
        <DecibelLevel/>
    </div>
  </div>
  <div class="space"><br></div>
  <div class = 'container'>
    <div class="box_history">
      <!-- insert the custom-made tag for tempHistory-->
    </div>
    <div class="box_history">
        <SensorDataHistory/>
    </div>
  </div>
  <div class="space"></div>
</template>

<script>
  /* importing the components to this view */
  import Temperature from '../components/Temperature.vue'
  import DecibelLevel from '../components/DecibelLevel.vue'
  import SensorDataHistory from '../components/SensorDataHistory.vue'

  export default {
  /* name of the view is EnvironmentView */
  name: 'EnvironmentView',

  /* components that will be used as a custom-made tag
  in the EnviromentView*/
  components: {
    Temperature, 
    DecibelLevel,
    SensorDataHistory
  }
  }
</script>

<style scoped src="../../assets/css/EnvironmentView.css"/>
  
