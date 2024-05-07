

//MongoClient : to connect to MongoDB
const { MongoClient } = require('mongodb');

async function main(){
    const uri = "mongodb+srv://lingsv:Ling1234@pll.vpbsppm.mongodb.net/?retryWrites=true&w=majority&appName=pll";
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

// just to list 
async function listDatabases(client){
    const databasesList = await client.db().admin().listDatabases();

    console.log("Databases:" );
    databasesList.databases.forEach(db => {
        console.log(`- ${db.name}`);
    })
}

