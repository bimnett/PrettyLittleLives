<template>
    <div>
      <h1>Guess the Animal!</h1>
      <button @click="playSound">Play Sound</button>
      <audio :src="currentSound" ref="audioPlayer"></audio>
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
    // const randomIndex = Math.floor(Math.random() * animals.length); // add this later, hardcode first
    // const currentAnimal = ref(animals[randomIndex]); // add this later, hardcode first
    const currentAnimal = ref(animals[0]); // selected animal = dog
    const currentSound = ref(currentAnimal.value.sound); // selected animal sound = woof
    const displayedAnimals = ref(animals.slice(0, 4)); // 4 animals being displayed

    const playSound = () => {
      audioPlayer.value.play();
    };

    const checkAnswer = (animal) => {
      if (animal.name === currentAnimal.value.name) {
        alert("Correct!");
      } else {
        alert("Try again!");
      }
    };

    return { displayedAnimals, currentSound, audioPlayer, playSound, checkAnswer };
  }
};
</script>

<style>
    .animal-images {
    display: flex;
    justify-content: space-around;
    }
    .animal img {
    width: 100px;
    height: auto;
    cursor: pointer;
    }
</style>
  