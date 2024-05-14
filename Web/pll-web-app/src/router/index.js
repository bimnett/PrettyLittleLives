// setting up all of our different routes

import { createRouter, createWebHistory } from 'vue-router'

// import the needed compoents 
import HomeView from '../views/HomeView.vue'
import EnvironmentView from '../views/EnvironmentView.vue'
import DanceStopView from '../views/DanceStopView.vue'
import SoundGameView from '../views/SoundGameView.vue'

// object array with all different webpages view and their url
const routes = [
  // a object and one object represent a route : 
  // path - what the url for each webpage view will have, relative to the root of the site
  // name - name of the route
  // component - what component that will be shown when a user goes to this route
  {
    path: '/',
    name: 'home',
    component: HomeView
  }, 
  {
    path: '/environment',
    name: 'environment',
    component: EnvironmentView
  },
  {
    path: '/dancestop',
    name: 'dancestop',
    component: DanceStopView
  }, 
  {
    path: '/soundgame',
    name: 'soundgame',
    component: SoundGameView
  }

]

// set up the router instance - creats the router for the app
// pass an object into the function
const router = createRouter({

  // createWebHistory : use the api history in the web browser 
  // so the user can click forward and back to different routes
  // process.env.BASE_URL : base url of the project
  history: createWebHistory(process.env.BASE_URL),

  // routes : the routes array itself
  routes
})

export default router
