<template>
    <div>
      <h1>Guess the Animal!</h1>
      <button @click="playSound">Play Sound</button>
      <audio :src="selectedSound" ref="audioPlayer"></audio>
      <div class="animal-images">
        <div v-for="animal in displayedAnimals" :key="animal.name" @click="checkAnswer(animal)" class="animal">
          <img :src="animal.image" :alt="animal.name">
          <p>{{ animal.name }}</p>
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

    return { displayedAnimals, selectedSound, audioPlayer, playSound, checkAnswer, test };
  }
};
</script>

<style>
    .animal-images {
    display: flex;
    padding:10px;
    justify-content: space-around;
    }
    .animal img {
    width: auto;
    height: auto;
    cursor: pointer;
    }
</style>
  