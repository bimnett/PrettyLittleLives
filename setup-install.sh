# Fetch latest package versions
apt-get update
# Move to home directory
cd ~


# Install arduino-cli
apt-get install curl -y
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
export PATH=$PATH:/root/bin


# Install Seeed Wio Terminal core
printf "board_manager:\n  additional_urls:\n    - https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json\n" > .arduino-cli.yaml
arduino-cli core update-index --config-file .arduino-cli.yaml
arduino-cli core install Seeeduino:samd --config-file .arduino-cli.yaml


# Install 'native' packages (libraries that do not come with the core)
arduino-cli lib install "Seeed Arduino rpcWiFi@1.0.7"
arduino-cli lib install "PubSubClient@2.8"
arduino-cli lib install "Seeed Arduino FS@2.1.1"
arduino-cli lib install "Seeed Arduino rpcUnified@2.1.4"
arduino-cli lib install "Seeed Arduino SFUD@2.0.2"
arduino-cli lib install "Seeed_Arduino_mbedtls@3.0.1"
arduino-cli lib install "DHT sensor library@1.4.6"
arduino-cli lib install "Grove LED Bar@1.0.0"
arduino-cli lib install "Grove-3-Axis-Digital-Accelerometer-2g-to-16g-LIS3DHTR@1.2.4"



# Install NodeJS & npm
curl -fsSL https://deb.nodesource.com/setup_18.x | sh
apt-get install nodejs -y


# Install necessary node packages in web app directory
cd /builds/courses/dit113/2024/group-15/pll/web

npm install mqtt

# Install netlify for web app deployment
npm install netlify-cli -g
export PATH=$PATH:/root/bin

npm install
npm install --save-dev @babel/plugin-transform-private-methods
npm install vue-router@4
npm install axios 

# Install necessary node packages in database directory
cd ../database

npm install
npm install express
nom install cors
npm install dotenv 
npm install mongodb