var boost_file_lock = null;

// Load the precompiled binary for windows.
if (process.platform == "win32" && process.arch == "x64") {
    boost_file_lock = require('./bin/winx64/boost-file-lock');
} else if (process.platform == "win32" && process.arch == "ia32") {
    boost_file_lock = require('./bin/winx86/boost-file-lock');
} else {
    // Load the new built binary for other platforms.
    boost_file_lock = require('./build/Release/boost-file-lock');
}

module.exports = boost_file_lock;
