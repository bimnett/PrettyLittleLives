<template>
  <div class="game-container">
    <div class="header">
      <button class="control-button" @click="playSound">Play Sound</button>
      <h1 class="title">Guess the Animal!</h1>
      <button class="control-button" onclick="window.location.reload()">Next Animal</button>
      <audio :src="selectedSound" ref="audioPlayer"></audio>
    </div>
    <div class="images-grid">
        <div class="image-box" v-for="(animal, index) in displayedAnimals" :key="animal.name" @click="checkAnswer(animal)">
          <img :src="animal.image" :alt="animal.name" class="animal-image">
          <p class="animal-name">{{ animal.name }}</p>
        </div>
    </div>
  </div>
</template>
  
<script>
  import { ref, onMounted } from 'vue';
  import { animals } from '../../assets/animal.js'; 
  import mqtt from 'mqtt';
  import { HOST } from "../credentials";
  
  export default {
    name: 'SoundGame',
    setup() {
      const mqttClient = mqtt.connect(HOST);
      const mqttTopicReplay = 'pll/game-terminal/sound-game/replay-sound';
      const mqttTopicCheckAnswer = 'pll/game-terminal/sound-game/check-answer';
      const mqttTopicAnswer = 'pll/game-terminal/sound-game/answer';
      const mqttTopicOptions = 'pll/game-terminal/sound-game/options';

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
          alert("Correct!");
          mqttClient.publish(mqttTopicCheckAnswer, "correct");
        } else {
          alert("Try again!");
          mqttClient.publish(mqttTopicCheckAnswer, "incorrect");
        }
      };

      const initialiseMQTT = () => {
        
        // message published to mqtt
        const publishAnimalNames = () => {
          const animalNames = arrDisplayedAnimals.map(animal => animal.name).join(',') + ','; // example: 'Monkey,Cow,Pig,Dog,''
          mqttClient.publish(mqttTopicOptions, animalNames);
        };        
        
        mqttClient.on('connect', () => {
          console.log('Connected to MQTT broker');
          mqttClient.subscribe([mqttTopicReplay, mqttTopicAnswer]);
          publishAnimalNames(); // publishes a string of animal names to the broker
        });

        // messages subscribed to mqtt
        mqttClient.on('message', (mqttTopic, message) => {
          console.log(`Received message on ${mqttTopic}: ${message.toString()}`);
          if (mqttTopic === mqttTopicReplay && message.toString() === 'replay') {
            playSound();
            console.log(`Received message: ${message.toString()}`);
          } else if (mqttTopic === mqttTopicAnswer) {
            console.log(`Received message: ${message.toString()}`);
            checkAnswer(message.toString()); // message is name of selected animal from wio terminal
          }
        });

        mqttClient.on('error', (error) => {
          console.error('Connection failed:', error);
          mqttClient.end();
        });
      
    };

    onMounted(() => {
      initialiseMQTT();
    });

    return { displayedAnimals, selectedSound, audioPlayer, playSound, checkAnswer, mqttClient };
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
    text-align: center; 
  }


  .control-button {
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

  .control-button:hover{
     background: #7D6608;
  }

  /* 4x4 grid that contains the same component image-box */
  .images-grid {
    display: grid;
    grid-template-columns: 1fr 1fr;
    grid-template-rows: 1fr 1fr;
    width: 100%;
    height: auto;
    gap: 0px;
  }

  /* component that contains both animal-image and animal-name */
  .image-box {
    display: flex;
    flex-direction: column;
    align-items: center;
    width: 100%;
    position: relative;
    cursor: pointer;
  }

  /* image featuring the animal */
  .animal-image {
    width: 100%;
    height: 100%;
    margin: 5px;
    object-fit: cover;
    display: block;
    overflow: hidden; /* hides parts of the animal image if it's over image-box's dimensions */
  }

  /* text containing the animal name, shows below animal-image */
  .animal-name {
    font-size: 2rem;
    color: black;
    font-family:'Comic Sans MS';
  }

</style>