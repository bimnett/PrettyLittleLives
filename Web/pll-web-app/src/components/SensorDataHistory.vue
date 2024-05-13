<template>
    <div class="sensor-data-history">
        <h2>Top 10 Highest Temperature Readings Today</h2>
        <ul class="readings">
            <!-- reading._id is reading's unique identifier from database -->
            <li v-for="reading in topTempReadings" :key="reading._id">
                {{ reading.temperature }} °C at {{ new Date(reading.timestamp).toLocaleTimeString() }}
            </li>
        </ul>

        <h2>Top 10 Highest Sound Level Readings Today</h2>
        <ul class="readings">
            <li v-for="reading in topSoundReadings" :key="reading._id">
                {{ reading.soundLevel }} dB at {{ new Date(reading.timestamp).toLocaleTimeString() }}
            </li>
        </ul>
    </div>
</template>

<script>
    import { getTopTempReadings, getTopSoundReadings } from "../../databaseConnection";

    export default {
        name: "SensorDataHistory",

        data() {
            return {
                topTempReadings: [],
                topSoundReadings: []
            };
        },

        async mounted() {
            this.topTempReadings = await getTopTempReadings();
            this.topSoundReadings = await getTopSoundReadings();
        }
    };
</script>

<style>
.sensor-data-history {
    font-family:'Comic Sans MS';
    padding: 20px;
    max-width: 600px;
    margin: auto;
}

.sensor-data-history h2 {
    color: #333;
    border-bottom: 2px solid #ccc;
    padding-bottom: 10px;
    margin-bottom: 20px;
}

.readings {
    list-style-type: none;
    padding: 0;
}

.readings li {
    background-color: #f9f9f9;
    margin: 10px 0;
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 4px;
}
</style>