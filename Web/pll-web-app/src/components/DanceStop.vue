<template>
    <div>
        <h1> Lets play DanceStop </h1>

    <!-- different content is shown on the webpage by clicking on button -->
    <div v-if="showDanceNow">
        <h2>{{ dance }}</h2>
       <img src="../../assets/dance.png" alt ="Dancing stick figure"> 
    </div>

    <div v-else> 
        <h2>{{ standStill }}</h2>
        <img src="../../assets/stop.png" alt ="Stop sign">
    </div>


    <!-- when the buttom is clicked the method toggleStartDance is executed -->
    <button @click="toggleStartDance">
        <!-- different button-titles gets displayed on button -->
        <span v-if="showDanceNow">Stop</span>
        <span v-else>Start dance</span>
    </button>
    </div>
</template>

<script> 
    import mqtt from "mqtt"; 
    import {HOST} from '@/credentials';


    export default {
        name : "DanceStop", 

        data() {
            
            return {
                showDanceNow : false,
                executeDance : 1,
                executeStill : 0,
                dance : "Dance now!",
                standStill : "Stand still!"
            };  
        }, 

        methods:{
            // change so it shitfs between dance and stop on webpage
            toggleStartDance() {
                this.showDanceNow = !this.showDanceNow;
                this.sendDanceState(this.showDanceNow); // Sends MQTT message about the dance state. If its stop or dance.
            },

        // Function to send MQTT message so that the wio terminal can change it's screen color accordingly and change state from dancing to standing still 
        sendDanceState(showDanceNow) {
            const moveState = showDanceNow ? this.executeDance : this.executeStill;
            const client = mqtt.connect(HOST);
            client.on("connect", () => {
             client.publish("pll/game/dancestop/state", moveState.toString());
            });
        },
    },
    mounted() {

            // When connection failed
            client.on('error', (error) => {
            console.error('Connection failed:', error);
            client.end();
            });
        },
  };

  </script>

   