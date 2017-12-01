#include <nan.h>

#define BOOST_ERROR_CODE_HEADER_ONLY 1
#include <boost/system/error_code.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void TryLock(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    if (info.Length() != 1)
    {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString())
    {
        Nan::ThrowTypeError("Wrong arguments");
        return;
    }

    v8::String::Utf8Value pathArg(info[0]->ToString());
    fs::path pathLockFile = std::string(*pathArg);

    FILE* file = fopen(pathLockFile.c_str(), "a"); // empty lock file; created if it doesn't exist.
    if (file) fclose(file);

    try {
        boost::interprocess::file_lock lock(pathLockFile.string().c_str());
        if (!lock.try_lock()) {
            info.GetReturnValue().Set(false);
            return;
        }
        lock.unlock();
    } catch(const boost::interprocess::interprocess_exception& e) {
        info.GetReturnValue().Set(false);
        return;
    }

    info.GetReturnValue().Set(true);
}

void Lock(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    if (info.Length() != 1)
    {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString())
    {
        Nan::ThrowTypeError("Wrong arguments");
        return;
    }

    v8::String::Utf8Value pathArg(info[0]->ToString());
    fs::path pathLockFile = std::string(*pathArg);

    FILE* file = fopen(pathLockFile.c_str(), "a"); // empty lock file; created if it doesn't exist.
    if (file) fclose(file);

    try {
        boost::interprocess::file_lock lock(pathLockFile.string().c_str());
        if (!lock.try_lock()) {
            info.GetReturnValue().Set(false);
            return;
        }
    } catch(const boost::interprocess::interprocess_exception& e) {
        info.GetReturnValue().Set(false);
        return;
    }

    info.GetReturnValue().Set(true);
}

void Unlock(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    if (info.Length() != 1)
    {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString())
    {
        Nan::ThrowTypeError("Wrong arguments");
        return;
    }

    v8::String::Utf8Value pathArg(info[0]->ToString());
    fs::path pathLockFile = std::string(*pathArg);

    FILE* file = fopen(pathLockFile.c_str(), "a"); // empty lock file; created if it doesn't exist.
    if (file) fclose(file);

    try {
        boost::interprocess::file_lock lock(pathLockFile.string().c_str());
        lock.unlock();
    } catch(const boost::interprocess::interprocess_exception& e) {
        info.GetReturnValue().Set(false);
        return;
    }

    info.GetReturnValue().Set(true);
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("tryLock").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(TryLock)->GetFunction());
    exports->Set(Nan::New("lock").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Lock)->GetFunction());
    exports->Set(Nan::New("unlock").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Unlock)->GetFunction());
}

NODE_MODULE(boost_file_lock, Init)
