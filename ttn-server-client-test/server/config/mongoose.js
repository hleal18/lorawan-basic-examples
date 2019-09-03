const mongoose = require('mongoose');
const local = 'mongodb://localhost:27017/test';

mongoose.connect(local, {useNewUrlParser: true});