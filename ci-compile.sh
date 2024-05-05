# Change directory to src folder of web app
cd /builds/bimnet/pll-ci-test/Web/pll-web-app/src

# Add mqtt credentials
echo "export const HOST = '$WEB_MQTT_HOST';" > credentials.js

# Move back to web app before build
cd ..

# Build
npm run build