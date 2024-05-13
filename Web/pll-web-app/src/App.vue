<template>
  <div class="menu">
    <nav>
      <router-link :to=" { name : 'home'}">Home</router-link> |
      <router-link :to=" { name : 'environment'}">Environment readings</router-link> |
      <router-link :to="{ name : 'dancestop'}">DanceStop</router-link> |
      <router-link :to="{ name : 'soundgame'}">SoundGame</router-link>
    </nav>
  </div>
  <router-view/>

  <div class="corporation">
    <br> 
    <sub>© 2024 Pretty Little Lives, Inc.</sub>
  </div>
</template>

<script>

</script>


<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 30px;
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

menu{
  position: fixed;
  top:0px;
}

corporation{
  color: black;
  bottom: 0px;
}
</style>
