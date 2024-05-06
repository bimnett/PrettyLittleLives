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



# Install NodeJS & npm
curl -fsSL https://deb.nodesource.com/setup_18.x | sh
apt-get install nodejs -y


# Install npm and mqtt library in web app directory
cd ../../Web/pll-web-app

npm install mqtt
npm install