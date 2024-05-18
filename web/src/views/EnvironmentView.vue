<template>

  <div class="space"><br></div>
  <div class = 'container'>
    <div class="box">
      <!-- Custom-made tag <Temperature/>, is self-closing -->
      <Temperature/>
    </div>
    <div class="box">
        <DecibelLevel/>
    </div>
  </div>
  <div class="space"><br></div>
  <div class = 'container'>
    <div class="box_history">
      <DecibelHistory/>
    </div>
    <div class="box_history">
      <TemperatureHistory/>
    </div>
  </div>
  <div class="space"></div>
</template>

<script>
  /* Importing the desired components to this view */
  import Temperature from '../components/Temperature.vue'
  import DecibelLevel from '../components/DecibelLevel.vue'
  import DecibelHistory from '../components/DecibelHistory.vue'
  import TemperatureHistory from '../components/TemperatureHistory.vue'

  export default {
  /* Name of the view is EnvironmentView */
  name: 'EnvironmentView',

  /* Components that will be used as a custom-made tag
  in the EnviromentView*/
  components: {
    Temperature, 
    DecibelLevel,
    DecibelHistory,
    TemperatureHistory
  }
  }
</script>

<style scoped>
  .container{
    display: flex;
    justify-content: space-evenly;
  }

  .box{
    width: 500px;
    height: 170px;
    background-color: rgb(247, 247, 242);
    border-radius: 20px;
  }

  .box_history{
    width: 500px;
    height: 700px;
    background-color: rgb(247, 247, 242);
    border-radius: 20px;  
  }

  .space{
    margin:20px;
    width:auto;
  }
</style>
  
