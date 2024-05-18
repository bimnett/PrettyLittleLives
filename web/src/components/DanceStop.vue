<template>
    <h2> <br>Let's play DanceStop </h2>
    <div class="space"></div>

    <!-- Different content is shown when clicking on button -->
    <div v-if="showDanceNow">
        <h2>{{ dance }}<br></h2>
        <img src="../../assets/images/dance.png" alt="Dancing stick figure" height="400" width="400"> 
    </div>

    <div v-else> 
        <h2>{{ standStill }}<br></h2> 
        <img src="../../assets/images/stop.png" alt="Stop sign" height="400" width="400">
    </div>

    <!-- When the buttom is clicked the method 
        toggleStartDance & sendDanceState are executed -->
    <button class="control-button" @click="toggleStartDance">
        <!-- Different names gets displayed on button -->
        <span v-if="showDanceNow">Stop</span>
        <span v-else>Start dance</span>
    </button>
    
</template>

<script> 
    import mqtt from "mqtt"; 
    import { HOST } from '@/credentials';
    let client = mqtt.connect(HOST);

    export default {
        name : "DanceStop", 

        data() {
            
            return {
                showDanceNow: false,
                executeDance: 1,
                executeStill: 0,
                dance: "Dance now!",
                standStill: "Stand still!"
            };  
        }, 

        methods: {
            // Change so it shifts between dance and stop on webpage
            toggleStartDance() {
                this.showDanceNow = !this.showDanceNow;
                this.sendDanceState(this.showDanceNow); // Send MQTT message about the dance state. If it's stop or dance.
            },

            // Function to send MQTT message so that the wio terminal can change its screen color accordingly and change state from dancing to standing still 
            sendDanceState(showDanceNow) {
                // Determine the state to send
                const moveState = showDanceNow ? this.executeDance : this.executeStill;
                
                // Connect to MQTT broker
                const client = mqtt.connect(HOST);
                
                // When connected, publish the moveState
                client.on("connect", () => {
                    client.publish("pll/game/dancestop/state", moveState.toString());
                });
            },
        },

        mounted() { 
            // When connection fails, log error
            client.on('error', (error) => {
                console.error('Connection failed:', error);
                client.end();
            });
        },
    };
</script>

<style scoped>

    .bodytext{
        text-align: 10px;
        font-family: 'Comic Sans MS';
    }

    .control-button {
        background-color: #FFDE59;
        border: none;
        color: #2c3e50;
        padding: 15px 32px;
        text-align: center;
        font-size: 16px;
        margin: 4px 2px;
        cursor: pointer;
        border-radius: 20px;
        text-align: 10px;
        font-family: 'Comic Sans MS';
    }

    .control-button:hover{
        background: #7D6608;
    }

    .space{
        margin:40px;
        width:auto;
    }
</style>
