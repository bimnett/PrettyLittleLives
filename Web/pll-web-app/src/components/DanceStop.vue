<template>
    <h2> Lest play DanceStop </h2>
    <div>
        
    </div>
    <!-- different content is shown when clicking on button -->
    <div v-if="showDanceNow">
        {{ dance }}
       <img src="../../assets/dance.png"> 
    </div>

    <div v-if="!showDanceNow"> 
        {{ standStill }}
        <img src="../../assets/stop.png">
    </div>

    <!-- when the buttom is clicked the method toggleStartDance is executed -->
    <button @click="[toggleStartDance(), sendDanceState(ShowDanceNow)]">
        <!-- different names gets displayed on button -->
        <span v-if="showDanceNow">Start dance</span>
        <span v-if="!showDanceNow">Stop</span>
    </button>
    
    
</template>

<script> 
    import mqtt from "mqtt"; 
    import {HOST} from '@/credentials';
    const client=mqtt.connect(HOST);

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
            },

            // to notify so the terminal can change its' screen color accordingly 
            sendDanceState(showDanceNow){
                
                // when kids shall dance send a 1
                if (showDanceNow==true){
                    moveState = executeDance;
                }else{
                    // when kids shall be still send 0
                    moveState = executeStill;
                }
                client.publish("pll/game/dancestop/state", moveState);
            }
        },

        mounted() {
            // Connect to MQTT broker
            //const client = mqtt.connect(HOST);

            // do not know if this is needed?
            // Subscribe to the MQTT topic
            client.on("connect", () => {
                // subscribing to the dancestop topic 
            client.subscribe("pll/game/dancestop");
            });

            // When connection failed
            client.on('error', (error) => {
            console.error('Connection failed:', error);
            client.end();
            });

            // Receive messages
            client.on("message", (topic, message) => {
            // Update the latest message
            this.temp = message.toString();
            });

        },


    } 

</script>