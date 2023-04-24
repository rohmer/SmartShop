#pragma once

#include <memory>
#include <string>
#include <dlfcn.h>
#include <iostream>

template <class T>
class DeviceLoader {

public:
	DeviceLoader(std::string module_name);
	~DeviceLoader();

    template <typename... Args>
    std::shared_ptr<T> make_obj(Args... args);
    
private:
    struct shared_obj {
        typename T::create_t *create = NULL;
        typename T::destroy_t *destroy = NULL;
        void * dll_handle = NULL;

        ~shared_obj();
        bool open_module(std::string module);
        void close_module();
    };

    std::string module;
    std::shared_ptr<shared_obj> shared;
};

#include "DeviceLoader.cpp"
