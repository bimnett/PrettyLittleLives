<template>
  <div class="picture_box">
    <img alt="PLL logo" src="../../assets/images/pll.png" height="250" width="250">
  </div>

  <h1>Welcome to Pretty Little Lives (PLL)</h1>

  <div class="container">
    <div class="box">
      <InfoPLL/>
    </div>

    <div class="box">
      <About/>
    </div>
  </div>

  <div class="space"></div>

  <div class="center">
    <div class="box">
      <Contact></Contact>
    </div>
  </div>
  
  <div class="space"></div>

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


<style scoped src="../../assets/css/HomeView.css"/>