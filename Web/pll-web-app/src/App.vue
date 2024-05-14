<template>
  <div class="menu">
    
    <nav>
      <router-link :to=" { name : 'home'}">Home</router-link> |
      <router-link :to=" { name : 'environment'}">Environment readings</router-link> |
      <router-link :to="{ name : 'dancestop'}">DanceStop</router-link> |
      <router-link :to="{ name : 'soundgame'}">SoundGame</router-link>
    </nav>
  </div>
  <!-- to make the content visable from the menu bar-->
  <div class="spaceing"></div>

  <router-view ></router-view>

  <div class="corporation">
    <sub>© 2024 Pretty Little Lives, Inc.</sub>
  </div>
</template>

<script>

</script>


<style scooped>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

.box_picture{
  width: 60px;
  height: 60px;
}

nav {
  padding: 30px;
  background-color: white;
  position: fixed; /* Set the navbar to fixed position */
  top: 0; /* Position the navbar at the top of the page */
  width: 100%;
  border-bottom: solid;
}

nav a {
  font-weight: bold;
  color: #2c3e50;
  padding:10px;
  border-radius: 4px;
  text-decoration: none; 
}

nav a.router-link-exact-active {
  color: #4b5e70;
  background: #FFDE59;
  text-decoration: underline;
}

.spaceing{
  margin:80px;
  width:auto;
}

.corporation{
  color: black;
  bottom: 0px;
  background-color: #FFDE59; 
}





</style>
