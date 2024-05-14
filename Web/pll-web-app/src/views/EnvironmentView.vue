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
        <!-- insert the custom-made tag for decibelHistory-->
    </div>
  </div>
</template>

<script>
  /* impoerting the components to this view */
  import Temperature from '../components/Temperature.vue'
  import DecibelLevel from '../components/DecibelLevel.vue'

  export default {
  /* name of the view is EnvironmentView */
  name: 'EnvironmentView',

  /* components that will be used as a custom-made tag
  in the EnviromentView*/
  components: {
    Temperature, 
    DecibelLevel
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
    height: 200px;
    background-color: rgb(247, 247, 242);
    border-radius: 20px;
  }

  .box_history{
    width: 500px;
    height: 600px;
    background-color: rgb(247, 247, 242);
    border-radius: 20px;  
  }

  .space{
    margin:50px;
    width:auto;
  }

</style>
