<template> 
    <div class="games">
        <h1>Games</h1>
        <div>Here you find the two games the PLL offers</div>
        <DanceStop></DanceStop>
        <SoundGame></SoundGame>
    </div>
</template>


<script>
import DanceStop from '../components/DanceStop.vue'
import SoundGame from '../components/SoundGame.vue'


export default{ 
    name: 'GameView',
    components: {
        DanceStop,
        SoundGame
        
    }
}
</script>
