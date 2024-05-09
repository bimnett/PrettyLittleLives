<template>
    <div>Current temperature : {{ temp }} celsius</div>
</template>

<script>
    // Import the MQTT library and credentials for cluster
    import mqtt from "mqtt";
    import { HOST } from "@/credentials";
    import { saveTemperature } from "@/databaseConnection";
    
    export default{
        // name of this component 
        name : "Temperature",  

        data() {
            return {
                // instantiate the placeholder 
                temp : "nothing",
            };
        },


        mounted() {
            // Connect to MQTT broker
            const client = mqtt.connect(HOST);

            // Subscribe to the MQTT topic
            client.on("connect", () => {
                // subscribing to the temparature topic 
            client.subscribe("pll/sensor/temp");
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
            saveTemperature(this.temp);
            });

        },
    
    };
</script>
