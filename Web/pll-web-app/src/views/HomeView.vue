<template>
    <div class="home">
      <h1>Welcome to Pretty Little Lives (PLL)</h1>
      <img alt="Vue logo" src="../../assets/images/Favicon.png" height="300" width="300">
    </div>
    <InfoPLL></InfoPLL>
    <About></About>  
    <Contact></Contact>
  </template>
  
  <script>
  // @ is an alias to /src

  import InfoPLL from '@/components/InfoPLL.vue'
  import About from '@/components/About.vue'
  import Contact from '@/components/Contact.vue'
  
  export default {
    name: 'HomeView',
    components: { 
      InfoPLL,
      About,
      Contact
    }
  }
  </script>


<style scoped>

</style>