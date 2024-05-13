import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import EnvironmentView from '../views/EnvironmentView.vue'
import DanceStopView from '../views/DanceStopView.vue'
import SoundGameView from '../views/SoundGameView.vue'


const routes = [
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

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
