# Pretty Little Lives (PLL)

![Logo](https://git.chalmers.se/courses/dit113/2024/group-15/pll/-/wikis/uploads/b312edb4cbc88e86fc050cfafa0a5341/PLLPic.png)

## Navigation Menu
- [Product Description](#product-description)
- [Purpose & Benefits](#purpose--benefits)
- [System Architecture & Components](#system-architecture--components)
- [Get Started](#setup-and-get-started-end-user)
- [Contributors](#contributors)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Product Description
Pretty Little Lives (PLL) offers teachers a real-time environment monitoring and game system for kindergarten classrooms. This system incorporates hardware components and a webpage to help maintain an optimal learning environment by continuously monitoring and displaying the sound level and the temperature, along with a small variety of educational and interactive games.

## Purpose & Benefits
Pretty Little Lives (PLL) is specifically designed with educators in mind, offering a comprehensive real-time environment monitoring solution tailored for kindergarten classrooms. The primary objectives and benefits of PLL are as follows:

**Purpose**
* **Optimal Learning Environment**: PLL wants to ensure that the classroom remains a optimal learning environment free from distractions or discomforts, by monitoring environmental factors such as sound levels and temperature.

* **Educator Support**: PLL wants to serve as a valuable tool for educators by providing them with real-time data and alerts regarding the classroom environment. This enables teachers to proactively address any issues that may arise, such as excessive noise levels, before they escalate and impact the learning experience.

* **Integration of Technology and Education**: PLL wants to bridge the gap between technology and education by incorporating hardware components and a dedicated webpage. It leverages innovative solutions to enhance the teaching and learning process, while also fostering a collaborative and interactive classroom environment.

<Styling command to add more space between paragraphs>
&nbsp;  

**Benefits**

* **Sound and Temperature Measurement**: PLL offers continuous monitoring of classroom environment, ensuring that the sound level and temperature remain within acceptable limits.

* **Web Integration for Real-time Monitoring**: PLL's integration with a dedicated webpage enables educators to monitor sound and temperature levels in real-time from any internet-enabled device, allowing teachers to have constant oversight even when they are not present. 

* **Educational Games**: In addition to environmental monitoring, PLL offers interactive educational games that engage students and promote learning. 

&nbsp;

## System Architecture & Components

**System Architecture Diagram**

A higher resolution diagram can be found [here](https://git.chalmers.se/courses/dit113/2024/group-15/pll/-/wikis/System-Architecture)

![diagram](https://lucid.app/publicSegments/view/49cf8195-51f9-4595-9f43-1b0e0c4a7ee4/image.png)

The PLL system consists of several hardware components:
- Sound level sensor
- Temperature sensor
- LED bar for visual alerts (green, yellow, and red).
- Environment Terminal for classroom.
- Game Terminal for students.
- Webpage for displaying real-time data and educational games.

## Get Started 

[Product video](https://www.youtube.com/watch?v=sclOhW9BAPA&ab_channel=LingSvahn)

To set up PLL for your kindergarten classroom:

1. **Hardware Installation**:
   - Plug in the loudness & temperature sensor into the environment terminal
   - Place the environment terminal at a fitting location, and plug in the power cable
   - Insert the battery for the game terminal, along with the vibration motor
   
2. **Web Integration**:
   - Access the dedicated webpage provided with the system.
   - Start monitoring sound and temperature levels in real-time.

3. **Utilize Educational Games**:
   - Engage students with educational games available on the webpage:
     - Little Lives DanceStop: A fun game for children to move around based on sound cues.
     - Little Lives SoundPairing: A game for matching animal sounds with pictures.


## Contributors
- [Bimnet Tesfamariam](https://git.chalmers.se/bimnet)
- [Sheenie Chan](https://git.chalmers.se/sheenie)
- [Fatma Ogoti Gichaba](https://git.chalmers.se/ogoti)
- [William Johansson](https://git.chalmers.se/willj)
- [Ling Svahn](https://git.chalmers.se/lingsv)

****Bimnet Tesfamariam****

Bimnet contributed to the CI pipeline and helped set up the environment between the Wio Terminal, MQTT, and the website. He established the Wio Terminal connection and managed the Wio Terminal side for the "Guess the Sound" game and, connecting it to MQTT. In addition, he contributed to the README and he created the user manual.

****Sheenie Chan****

Sheenie worked on the web side of the "Guess the Sound" game and contributed to establishing a connection to MQTT. She implemented the database connection to transfer reading data from the temperature and sound level sensors/MQTT to MongoDB and extracted these values from MongoDB to display past readings on the website. Sheenie also contributed to the README.

****Fatma Ogoti Gichaba****

Fatma worked on the "DanceStop" game. She managed the connection between the temperature and humidity sensor, the sound sensor, and MQTT to make sure the values are trasmitted and converted accurately. She also connected the LED lights from the LED bar, making more lights light up as the sound level increase.

****William Johansson****

William made the Wio Terminal play different melodies when the sound level reach certain thresholds. He refactored the entire project, helped set up the MongoDB database for temperature and sound level readings along with Ling, and helped in establishing the MQTT broker connection. William also layed a key role in creating the system architecture along with Ling.

****Ling Svahn****

Ling designed the layout of the website and helped set up the MongoDB database for temperature and sound level readings. She also collaborated with William in establishing the MQTT broker connection and creating the system architecture.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
Special thanks to our TAs [Adrian Hassa](https://git.chalmers.se/hassa) and [Teodora Portase](https://git.chalmers.se/portase), also our professor [Francisco Gomes](https://git.chalmers.se/francisco.gomes) for their help and expertise.
