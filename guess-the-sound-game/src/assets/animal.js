class Animal {
    constructor(name, sound, image) {
      this.name = name;
      this.sound = sound;
      this.image = image;
    }
  }
  
  const animals = [
    new Animal("Dog", "./sounds/1-dog.mp3", "./images/original size/1-dog.jpg"),
    new Animal("Cat", "./sounds/2-cat.mp3", "./images/original size/2-cat.jpg"),
    new Animal("Bird", "./sounds/3-bird.mp3", "./images/original size/3-bird.jpg"),
    new Animal("Lion", "./sounds/4-lion.mp3", "./images/original size/4-lion.jpg"),
    new Animal("Horse", "./sounds/5-horse.mp3", "./images/original size/5-horse.jpg"),
    new Animal("Wolf", "./sounds/6-wolf.mp3", "./images/original size/6-wolf.jpg"),
    new Animal("Chicken", "./sounds/7-chicken.mp3", "./images/original size/7-chicken.jpg"),
    new Animal("Cow", "./sounds/8-cow.mp3", "./images/original size/8-cow.jpg"),
    new Animal("Snake", "./sounds/9-snake.mp3", "./images/original size/9-snake.jpg"),
    new Animal("Duck", "./sounds/10-duck.mp3", "./images/original size/10-duck.jpg"),
    new Animal("Frog", "./sounds/11-frog.mp3", "./images/original size/11-frog.jpg"),
    new Animal("Elephant", "./sounds/12-elephant.mp3", "./images/original size/12-elephant.jpg"),
    new Animal("Owl", "./sounds/13-owl.mp3", "./images/original size/13-owl.jpg"),
    new Animal("Monkey", "./sounds/14-monkey.mp3", "./images/original size/14-monkey.jpg"),
    new Animal("Sheep", "./sounds/15-sheep.mp3", "./images/original size/15-sheep.jpg"),
    new Animal("Raven", "./sounds/16-raven.mp3", "./images/original size/16-raven.jpg"),
    new Animal("Dolphin", "./sounds/17-dolphin.mp3", "./images/original size/17-dolphin.jpg"),
    new Animal("Pig", "./sounds/18-pig.mp3", "./images/original size/18-pig.jpg"),
    new Animal("Seagull", "./sounds/19-seagull.mp3", "./images/original size/19-seagull.jpg"),
    new Animal("Eagle", "./sounds/20-eagle.mp3", "./images/original size/20-eagle.jpg"),
  ];

  export { animals };