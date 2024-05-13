import { createApp } from 'vue'
import App from './App.vue'
import router from './router'

// set the tab title to Pretty Little Lives
document.title = "Pretty Little Lives"

createApp(App).use(router).mount('#app')
