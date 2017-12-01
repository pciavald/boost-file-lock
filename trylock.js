const boost_file_lock = require('.');

console.log('trylock:', boost_file_lock.tryLock(".lock"));

console.log('lock:', boost_file_lock.lock(".lock"));

console.log('unlock:', boost_file_lock.unlock(".lock"));

