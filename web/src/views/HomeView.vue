<template>
  <div class="picture_box">
    <img alt="PLL logo" src="../../assets/images/pll.png" height="250" width="250">
  </div>

  <h1 class="bodytext">Welcome to Pretty Little Lives (PLL)</h1>

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

  .bodytext{
    text-align: 10px;
    font-family: 'Comic Sans MS';
  }

  .picture_box{
    width:auto;
    height:250px;
    background-color: #FFDE59;
    position: center;
  }

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

  .center{
    display: flex;
    justify-content: center;
  }

  .space{
    margin:30px;
    width:auto;
  }

  .bodytext{
    text-align: 10px;
  }
</style>