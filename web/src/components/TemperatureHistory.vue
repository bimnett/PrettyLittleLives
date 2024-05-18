<template>
    <div class="data-history">
        <h2>Top 10 Highest Temperature Readings Today</h2>
        <ul class="readings">
            <li v-for="reading in topTempReadings" :key="reading._id">
                {{ reading.temperature }} °C at {{ new Date(reading.timestamp).toLocaleTimeString() }}
            </li>
        </ul>
    </div>
</template>

<script>
    import axios from "axios";

    export default {
        name: "TemperatureHistory",

        data() {
            return {
                topTempReadings: [],
            };
        },

        async mounted() {
            this.topTempReadings = await this.getTopTempReadings();
        },

        methods: {
            // Function to make HTTP GET request to retrieve top temperature readings
            async getTopTempReadings() {
                try {
                    const response = await axios.get('http://localhost:3000/api/topTemperatureReadings');
                    return response.data;
                } catch (error) {
                    console.error('Failed to get top temperature readings:', error);
                    return [];
                }
            }
        }
    };
</script>

<style scoped src="../../assets/css/displaySensorReadings.css"/>
