const mongoose = require('mongoose');

const LoraPacketsSchema = new mongoose.Schema({
    app_id: String,
    dev_id: String,
    hardware_serial: String,
    port: Number,
    counter: Number,
    payload_raw: Buffer,
    metadata: {
        time: Date,
        frequency: Number,
        data_rate: String,
        airtime: Number,
        coding_rate: String,
        gateways: [Object]
    }
});

module.exports = mongoose.model('lora_packets', LoraPacketsSchema);