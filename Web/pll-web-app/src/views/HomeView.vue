<template>
    <div class="home">
      <h1>Welcome to Pretty Little Lives (PLL)</h1>
      <img alt="Vue logo" src="../../assets/Favicon.png" height="300" width="300">
    </div>
    <InfoPLL></InfoPLL>
  </template>
  
  <script>
  // @ is an alias to /src

  import InfoPLL from '@/components/InfoPLL.vue'
  
  export default {
    name: 'HomeView',
    components: { 
      InfoPLL
    }
  }
  </script>