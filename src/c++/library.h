#pragma once

// - Standard C++
#include <cassert>
#include <string>
#include <type_traits>
#include <utility>

// - SDL2
#include <SDL.h>

namespace vl {
class library {
    void* mLib;
    std::string mLibName;

  public:
    library()
        : mLib(nullptr)
        , mLibName("") {
    }

    bool load(std::string filename) {
        if(mLib)
            release();

        mLib = SDL_LoadObject(filename.c_str());
        mLibName = filename;
        return isLoaded();
    }

    void release() {
        if(mLib) {
            SDL_UnloadObject(mLib);
            mLib = nullptr;
            mLibName = "";
        }
    }

    bool isLoaded() const {
        return mLib ? true : false;
    }

    std::string getName() const {
        return mLibName;
    }

    bool findFunction(std::string funcname) const {
        if(mLib)
            return ((SDL_LoadFunction(mLib, funcname.c_str()) != nullptr) ?
                        true :
                        false);

        return false;
    }

    template <typename T> T getFunction(std::string funcname) const {
        if(mLib)
            return reinterpret_cast<T>(
                SDL_LoadFunction(mLib, funcname.c_str()));

        return nullptr;
    }

    template <typename T, typename... Args>
    inline auto call(std::string funcname, Args&&... parameters)
        -> typename std::result_of<T(Args...)>::type const {
        T pFunc = getFunction<T>(funcname);
        assert(pFunc != nullptr);
        return pFunc(std::forward<Args>(parameters)...);
    }

    explicit operator const bool() const {
        return isLoaded();
    }

    library(const library&) = delete;
    library& operator=(const library&) = delete;

    ~library() {
        release();
    }
};
}
