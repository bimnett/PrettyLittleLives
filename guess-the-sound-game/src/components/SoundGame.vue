<template>
  <div class="game-container">
    <div class="header">
      <h1 class="title">Guess the Animal!</h1>
      <button class="sound-button" @click="playSound">Play Sound</button>
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
  import { ref } from 'vue';
  import { animals } from '@/assets/animal.js'; 
  
  export default {
  name: 'SoundGame',
  setup() {
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

    // const test = ref(selectedAnimal);

    const playSound = () => {
      audioPlayer.value.play();
    };

    const checkAnswer = (animal) => {
      if (animal.name === selectedAnimal.value.name) {
        alert("Correct!");
      } else {
        alert("Try again!");
      }
    };

    return { displayedAnimals, selectedSound, audioPlayer, playSound, checkAnswer };
  }
};
</script>

<style>
  .game-container {
    text-align: center;
    background-color: #FCF3CF;
  }

  .header {
    display: flex;
    justify-content: space-between; 
    margin-bottom: 10px;
  }

  .title {
    font-size: 4rem;
    margin: 0;
    flex-grow: 1;
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
    width: 100vw;
    height: 100vw;
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
  