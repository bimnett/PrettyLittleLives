<template>
    <div class="data-history">
        <h2>Top 10 Highest Sound Level Readings Today</h2>
        <ul class="readings">
            <li v-for="reading in topSoundReadings" :key="reading._id">
                {{ reading.soundLevel }} dB at {{ new Date(reading.timestamp).toLocaleTimeString() }}
            </li>
        </ul>
    </div>
</template>

<script>
    import axios from "axios";

    export default {
        name: "DecibelHistory",

        data() {
            return {
                topSoundReadings: []
            };
        },

        async mounted() {
            this.topSoundReadings = await this.getTopSoundReadings();
        },

        methods: {
            // Function to make HTTP GET request to retrieve top sound level readings
            async getTopSoundReadings() {
                try {
                    const response = await axios.get('http://localhost:3000/api/topSoundReadings');
                    return response.data;
                } catch (error) {
                    console.error('Failed to get top sound level readings:', error);
                    return [];
                }
            }
        }
    };
</script>

<style scoped src="../../assets/css/displaySensorReadings.css"/>
