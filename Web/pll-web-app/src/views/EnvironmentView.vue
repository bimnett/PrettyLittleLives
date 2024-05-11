<template>
   <div class = 'environment'>
        <Temperature/>
        <DecibelLevel/>
   </div> 
</template>

<script>
    import Temperature from '../components/Temperature.vue'
    import DecibelLevel from '../components/DecibelLevel.vue'

    export default {
    name: 'EnvironmentView',
    components: {
      Temperature, 
      DecibelLevel
    }
  }
</script>

<style>

</style>
