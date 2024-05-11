<template>
  <nav>
    <router-link :to=" { name : 'home'}">Home</router-link> |
    <router-link :to=" { name : 'environment'}">Environment readings</router-link> |
  </nav>
  <router-view/>
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
</style>
