// backend

import express from 'express'; // Node.js web app framework to set up server
import { MongoClient } from 'mongodb';
import cors from 'cors'; // Cross-Origin Resource Sharing
import dotenv from 'dotenv';
import { uri } from './src/credentials.js';

dotenv.config(); // Load environment variable (from .env to process.env)

const app = express();
const port = process.env.PORT || 3000; // Default port is 3000

// Declare global variables
let client;
let temperatureDb;
let soundDb;

async function connectToMongoDB() {
  client = new MongoClient(uri);
  try {
    await client.connect();
    temperatureDb = client.db('temperature');
    soundDb = client.db('sound');
    console.log('Connected to MongoDB');
  } catch (err) {
    console.error('Failed to connect to MongoDB', err);
  }
}

connectToMongoDB();

// CORS setup
app.use(cors());
app.use(express.json()); // Parse incoming JSON requests

// At API endpoint, receive temp data and save it to 'temp_values' collection in MongoDB
app.post('/api/saveTemperature', async (req, res) => {
    try {
      const { temperatureValue } = req.body;
      const temperatureFloat = parseFloat(temperatureValue); // Convert temperature to float. Note: float and double same type in js
      
      if (isNaN(temperatureFloat)) {
        // If temperatureFloat is not a valid number, return error
        return res.status(400).json({ message: 'Invalid temperature value' });
      }
  
      const result = await temperatureDb.collection('temp_values').insertOne({ temperature: temperatureFloat, timestamp: new Date() });
      res.status(200).json({ message: 'Temperature saved', id: result.insertedId });
    } catch (err) {
      res.status(500).json({ message: 'Failed to save temperature', error: err });
    }
  });
  

// At API endpoint, retrieve top 10 temperature readings for current day
app.get('/api/topTemperatureReadings', async (req, res) => {
  try {
    const today = new Date();
    today.setHours(0, 0, 0, 0);
    const readings = await temperatureDb.collection('temp_values')
                                        .find({ timestamp: { $gte: today } })
                                        .sort({ temperature: -1 })
                                        .limit(10)
                                        .toArray();
    res.status(200).json(readings);
  } catch (err) {
    res.status(500).json({ message: 'Failed to retrieve top temperature readings', error: err });
  }
});

// At API endpoint, receive sound level data and save it to 'decibel_values' collection in MongoDB
app.post('/api/saveSoundLevel', async (req, res) => {
    try {
      const { soundLevelValue } = req.body;
      const soundLevelFloat = parseFloat(soundLevelValue); // Convert sound level to float
      
      if (isNaN(soundLevelFloat)) {
        // If soundLevelFloat is not a valid number, return error
        return res.status(400).json({ message: 'Invalid sound level value' });
      }
  
      const result = await soundDb.collection('decibel_values').insertOne({ soundLevelFloat, timestamp: new Date() });
      res.status(200).json({ message: 'Sound level saved', id: result.insertedId });
    } catch (err) {
      res.status(500).json({ message: 'Failed to save sound level', error: err });
    }
  });

// At API endpoint, retrieve top 10 sound level readings for current day
app.get('/api/topSoundReadings', async (req, res) => {
  try {
    const today = new Date();
    today.setHours(0, 0, 0, 0);
    const readings = await soundDb.collection('decibel_values')
                                  .find({ timestamp: { $gte: today } })
                                  .sort({ soundLevel: -1 })
                                  .limit(10)
                                  .toArray();
    res.status(200).json(readings);
  } catch (err) {
    res.status(500).json({ message: 'Failed to retrieve top sound level readings', error: err });
  }
});

// Start server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});