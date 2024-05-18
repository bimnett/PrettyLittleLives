<template>
  <div class="data-history">
    <h2>Temperature</h2>
    <div>Current temperature : {{ temp }} celsius</div>
  </div>

</template>
  
<script>
  // Import the MQTT library and credentials for cluster
  import mqtt from "mqtt";
  import axios from "axios";
  import { HOST } from "@/credentials";

  export default {
    name: "Temperature",
  
    data() {
      return {
        temp: "-",
      };
    },
  
    async mounted() {
      const client = mqtt.connect(HOST);
  
      client.on("connect", () => {
        client.subscribe("pll/sensor/temp");
      });
  
      client.on('error', (error) => {
        console.error('Connection failed:', error);
        client.end();
      });
  
      client.on("message", async (topic, message) => {
        this.temp = message.toString().trim();
        console.log("Received temperature:", this.temp);
  
        try {
          await this.saveTemperature(this.temp);
          console.log(`Temperature ${this.temp} saved to MongoDB`);
        } catch (error) {
          console.error('Failed to save temperature:44444444444444444', error);
        }
      });
    },
  
    methods: {
    // Function to send HTTP post request to express server "http://localhost:3000/api/saveTemperature"
      async saveTemperature(temperatureValue) {
        try {
          await axios.post('http://localhost:3000/api/saveTemperature', { temperatureValue: parseFloat(temperatureValue) })
        } catch (error) {
          console.error("Failed to save temperature:555555555555", error);
        }
      }
    }
  };
</script>  

<style scoped src="../../assets/css/displaySensorReadings.css"/>