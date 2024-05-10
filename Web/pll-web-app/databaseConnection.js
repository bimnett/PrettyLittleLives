import { uri } from './src/credentials.js';

//MongoClient : to connect to MongoDB
import { MongoClient} from 'mongodb';

const client = new MongoClient(uri);

// Connect to MongoDB cluster
async function connectClient() {
    // await - to block further execution until 
    // this operation has completed 
    try {
        await client.connect();
        await listDatabases(client);
        console.log('Connected to MongoDB');
    } catch (e){
        cconsole.error('MongoDB connection failed:', e);
    }
}

// Close MongoDB connection
async function closeClient() {
    try {
        if (client.isConnected()) {
            await client.close();
            console.log('MongoDB connection closed');
        }
    } catch (e) {
        console.error('Failed to close MongoDB connection:', e);
    }
}

main().catch(console.error);

// List all databases
async function listDatabases(client){
    const databasesList = await client.db().admin().listDatabases();

    console.log("Databases:" );
    databasesList.databases.forEach(db => {
        console.log(`- ${db.name}`);
    })
}

// Save temperature data
export async function saveTemperature(temp) {
    await connectClient();
    try {
        const db = client.db('temperature'); // 'temperature' database 
        const collection = db.collection('temp_values'); // 'temp_values' collection

        // Insert temperature reading
        await collection.insertOne({ temperature: temp, timestamp: new Date() });

    } catch (e) {
        console.error("Failed to save temperature data:", e);
    } finally {
        await closeClient();
    }
}

// Returns array of top 10 highest temperature readings of the day
export async function getTopTempReadings() {
    await connectClient();
    try {
        const db = client.db('temperature');
        const collection = db.collection('temp_values');

        // Query for top 10 highest temperature readings of the day
        const today = new Date();
        today.setHours(0, 0, 0, 0); // Set time to midnight to retrieve 10 highest readings before current time
        const readings = await collection.find({ timestamp: { $gte: today } })
                                          .sort({ temperature: -1 }) // highest temperatures appear first
                                          .limit(10)
                                          .toArray();
        return readings;
    } catch (e) {
        console.error("Failed to retrieve top readings:", e);
    } finally {
        await closeClient();
    }
}

// Save sound level data
export async function saveSoundLevel(soundLevel) {
    await connectClient();
    try {
        const db = client.db('sound');
        const collection = db.collection('decibel_values');

        // Insert temperature reading
        await collection.insertOne({ soundLevel: soundLevel, timestamp: new Date() });

    } catch (e) {
        console.error("Failed to save sound level data:", e);
    } finally {
        await closeClient();
    }
}

// Returns array of top 10 highest sound level readings of the day
export async function getTopSoundReadings() {
    await connectClient();
    try {
        const db = client.db('sound');
        const collection = db.collection('decibel_values');

        // Query for top 10 highest sound readings of the day
        const today = new Date();
        today.setHours(0, 0, 0, 0); // Set time to midnight to retrieve 10 highest readings before current time
        const readings = await collection.find({ timestamp: { $gte: today } })
                                          .sort({ soundLevel: -1 }) // highest sound levels appear first
                                          .limit(10)
                                          .toArray();
        return readings;
    } catch (e) {
        console.error("Failed to retrieve top sound level readings:", e);
    } finally {
        await closeClient();
    }
}