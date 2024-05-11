# Set path to arduino-cli installation folder
export PATH=$PATH:/root/bin


# Change directory to EnvironmentTerminal folder
cd WioTerminal/EnvironmentTerminal


# Assign connection credential variables
echo "#define SSID \"$SSID\"" > connectionCredentials.h
echo "#define WIFI_PASSWORD \"$WIFI_PASSWORD\"" >> connectionCredentials.h
echo "#define MQTT_SERVER \"$MQTT_SERVER\"" >> connectionCredentials.h
echo "#define MQTT_CLIENT_ID \"$TERMINAL_MQTT_CLIENT_ID\"" >> connectionCredentials.h
echo "#define MQTT_PORT $TERMINAL_MQTT_PORT" >> connectionCredentials.h


# Compile EnvironmentTerminal sketch
arduino-cli compile --fqbn Seeeduino:samd:seeed_wio_terminal


# Change directory to GameTerminal folder
cd ../GameTerminal

# Re-assign connection credential variables
echo "#define SSID \"$SSID\"" > connectionCredentials.h
echo "#define WIFI_PASSWORD \"$WIFI_PASSWORD\"" >> connectionCredentials.h
echo "#define MQTT_SERVER \"$MQTT_SERVER\"" >> connectionCredentials.h
echo "#define MQTT_CLIENT_ID \"$TERMINAL_MQTT_CLIENT_ID\"" >> connectionCredentials.h
echo "#define MQTT_PORT $TERMINAL_MQTT_PORT" >> connectionCredentials.h

# Compile GameTerminal sketch
arduino-cli compile --fqbn Seeeduino:samd:seeed_wio_terminal