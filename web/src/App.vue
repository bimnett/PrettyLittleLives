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
