<template>
  <div class="game-container">
    <div class="header">
      <h1 class="title">Guess the Animal!</h1>
      <!-- <button class="sound-button" @click="playSound">Play Sound</button> -->
      <button class="sound-button" @click="testPublishPlay">Test Publish</button> <!-- New button for testing -->
      <audio :src="selectedSound" ref="audioPlayer"></audio>
    </div>
    <div class="images-grid">
        <!-- <div class="image-box" v-for="(animal, index) in displayedAnimals" :key="animal.name" @click="checkAnswer(animal)"> -->
        <div class="image-box" v-for="(animal, index) in displayedAnimals" :key="animal.name" @click="testPublishCheckAnswer(animal)">
          <img :src="animal.image" :alt="animal.name" class="animal-image">
          <p class="animal-name">{{ animal.name }}</p>
        </div>
    </div>
  </div>
</template>
  
<script>
  import { ref } from 'vue';
  import { animals } from '@/assets/animal.js'; 
  import * as mqtt from 'mqtt';
  import MockBroker from '@/utils/MockBroker';
  
  export default {
  name: 'SoundGame',
  setup() {
    // const mqttClient = ref(null);
    // const mqttTopic1 = 'pll/game-terminal/sound-game/replay-sound';
    // const mqttTopic2 = 'pll/game-terminal/sound-game/answer';   
    const broker = new MockBroker();
    const mockTopic1 = 'game/playSound';
    const mockTopic2 = 'game/answer';       

    const audioPlayer = ref(null);
    var arrDisplayedAnimals = [];
    const size = 4; // number of animals displayed

    function generateIndexArray(size) {
        const uniqueIndexes = new Set(); // no repeats

        while (uniqueIndexes.size < size) {
            const randomNumber = Math.floor(Math.random() * 20); // number between 0-19
            uniqueIndexes.add(randomNumber);
        }
        return Array.from(uniqueIndexes);
    }
    const arrIndexDisplayedAnimals = generateIndexArray(size); // array of displayed animals
    for (var i = 0, t = size; i < t; i++) {
        arrDisplayedAnimals.push(animals[arrIndexDisplayedAnimals[i]])
    }

    const selectedIndex = Math.floor(Math.random() * size); // 0-3 
    const selectedAnimal = ref(arrDisplayedAnimals[selectedIndex]);
    const selectedSound = ref(selectedAnimal.value.sound);
    const displayedAnimals = ref(arrDisplayedAnimals); // 4 animals being displayed 

    const playSound = () => {
      audioPlayer.value.play();
    };

    const checkAnswer = (animal) => {
      if (animal.name === selectedAnimal.value.name) {
    // const checkAnswer = (animalName) => {
    //   if (animalName === selectedAnimal.value.name) {
        alert("Correct!");
      } else {
        alert("Try again!");
      }
    };

    // const initialiseMQTT = () => {
    //   mqttClient.value = mqtt.connect('ws://broker.hivemq.com:1883'); // is the the correct broker's address?
      
    //   mqttClient.value.on('connect', () => {
    //     console.log('Connected to MQTT broker');
    //     mqttClient.value.subscribe([mqttTopic1, mqttTopic2]);
    //   });

    //   mqttClient.value.on('message', (mqttTopic, message) => {
    //     console.log(`Received message on ${topic}: ${message.toString()}`);
    //     if (mqttTopic === mqttTopic1 && message.toString() === 'replay') {
    //       playSound();
    //       console.log(`Received message: ${message.toString()}`);
    //     } else if (mqttTopic === mqttTopic2) {
    //       console.log(`Received message: ${message.toString()}`);
    //       checkAnswer(message.toString()); // message is name of selected animal from wio terminal
    //     }
    //   });
    // };

    // initialiseMQTT();

    broker.subscribe(mockTopic1, (topic, message) => {
      console.log(`Received message on ${topic}: ${message}`);
      if (topic === mockTopic1 && message === 'play') {
        playSound();
      }
    });

    broker.subscribe(mockTopic2, (topic, message) => {
      console.log(`Received message on ${topic}: ${message}`);
      if (topic === mockTopic2) {
        checkAnswer(message); // message is the name of the selected animal from the Wio Terminal
      }
    });

    function testPublishPlay() {
      broker.publish(mockTopic1, 'play');
    }

    function testPublishCheckAnswer(animal) {
      const animalName = animal.name;
      broker.publish(mockTopic2, animalName);
    }    

    return { displayedAnimals, selectedSound, audioPlayer, playSound, checkAnswer, testPublishPlay, testPublishCheckAnswer }; // mqttClient
  }
};

</script>

<style>
  .game-container {
    margin: auto;
    justify-content: left;
    text-align: center;
    background-color: #FCF3CF;
    min-width: 90vh;
    height: auto;
    padding: 0;
  }

  .header {
    display: flex;
    justify-content: space-between; 
    margin: 10px;
  }

  .title {
    font-size: 3rem;
    line-height: 1.8;
    margin: 0;
    color: #7D6608;
    font-family:'Impact';    
  }


  .sound-button {
    background-color: #B7950B;
    border: none;
    color: white;
    margin: 10px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 1.5rem;
    padding: 15px 32px;
    cursor: pointer;
  }

  .sound-button:hover{
     background: #7D6608;
  }

  .images-grid {
    display: grid;
    grid-template-columns: 1fr 1fr;
    grid-template-rows: 1fr 1fr;
    width: 100%;
    height: auto;
    gap: 0px;
  }

  .image-box {
    display: flex;
    flex-direction: column;
    align-items: center;
    width: 100%;
    position: relative;
    cursor: pointer;
  }

  .animal-image {
    width: 100%;
    height: 100%;
    margin: 5px;
    object-fit: cover;
    display: block;
    overflow: hidden; /* hides parts of the animal image if it's over image-box's dimensions */
  }

  .animal-name {
    font-size: 2rem;
    color: black;
    font-family:'Comic Sans MS';
  }

</style>
  