import { uri } from './src/credentials.js';

//MongoClient : to connect to MongoDB
import { MongoClient} from 'mongodb';

async function main(){
    const client = new MongoClient(uri);

    //connect to cluster 
    // await - to block further execution until 
    // this operation has completed 
    try {
        await client.connect();
        await listDatabases(client);
    } catch (e){
        console.error(e);
    } finally{
        await client.close();
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

