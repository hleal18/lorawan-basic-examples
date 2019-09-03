//import ttn from 'ttn';
require('./config');
const { data, application } = require('ttn');
const LoraPacket = require('./models/lora-packets');

const appID = process.env.APP_ID;
const accessKey = process.env.ACCESS_KEY;

// discover handler and open mqtt connection
data(appID, accessKey)
    .then(function (client) {
        client.on("uplink", function (devID, payload) {
            console.log("Received uplink from ", devID)
            console.log(payload)
            const packet = new LoraPacket(payload);
            return packet.save().then((doc) => console.log("Doc saved: ", doc));
        })
    })
    .catch(function (err) {
        console.error(err)
        process.exit(1)
    })

// discover handler and open application manager client
application(appID, accessKey)
    .then(function (client) {
        return client.get()
    })
    .then(function (app) {
        console.log("Got app", app)
    })
    .catch(function (err) {
        console.error(err)
        process.exit(1)
    })