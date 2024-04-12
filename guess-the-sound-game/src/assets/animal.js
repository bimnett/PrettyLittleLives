class Animal {
    constructor(name, sound, image) {
      this.name = name;
      this.sound = sound;
      this.image = image;
    }
  }
  
  const animals = [
    new Animal("Dog", "./sounds/1-dog.mp3", "./images/640x480/1-dog-640x480.jpg"),
    new Animal("Cat", "./sounds/2-dog.mp3", "./images/640x480/2-cat-640x480.jpg"),
    new Animal("Bird", "./sounds3-bird.mp3", "./images/640x480/3-bird-640x480.jpg"),
    new Animal("Lion", "./sounds/4-lion.mp3", "./images/640x480/4-lion-640x480.jpg"),
    new Animal("Horse", "./sounds/5-horse.mp3", "./images/640x480/5-horse-640x480.jpg"),
    new Animal("Wolf", "./sounds/6-wolf.mp3", "./images/640x480/6-wolf-640x480.jpg"),
    new Animal("Chicken", "./sounds/7-chicken.mp3", "./images/640x480/7-chicken-640x480.jpg"),
    new Animal("Cow", "./sounds/8-cow.mp3", "./images/640x480/8-cow-640x480.jpg"),
    new Animal("Snake", "./sounds/9-snake.mp3", "./images/640x480/9-snake-640x480.jpg"),
    new Animal("Duck", "./sounds/10-duck.mp3", "./images/640x480/10-duck-640x480.jpg"),
    new Animal("Frog", "./sounds/11-frog.mp3", "./images/640x480/11-frog-640x480.jpg"),
    new Animal("Elephant", "./sounds/12-elephant.mp3", "./images/640x480/12-elephant-640x480.jpg"),
    new Animal("Owl", "./sounds/13-owl.mp3", "./images/640x480/13-owl-640x480.jpg"),
    new Animal("Monkey", "./sounds/14-monkey.mp3", "./images/640x480/14-monkey-640x480.jpg"),
    new Animal("Sheep", "./sounds/15-sheep.mp3", "./images/640x480/15-sheep-640x480.jpg"),
    new Animal("Raven", "./sounds/16-raven.mp3", "./images/640x480/16-raven-640x480.jpg"),
    new Animal("Dolphin", "./sounds/17-dolphin.mp3", "./images/640x480/17-dolphin-640x480.jpg"),
    new Animal("Pig", "./sounds/18-pig.mp3", "./images/640x480/18-pig-640x480.jpg"),
    new Animal("Seagull", "./sounds/19-seagull.mp3", "./images/640x480/19-seagull-640x480.jpg"),
    new Animal("Eagle", "./sounds/20-eagle.mp3", "./images/640x480/20-eagle-640x480.jpg"),
  ];

  export { animals };