#pragma once

#ifdef DOVE_CPP_NATIVE
    #define DCORE
#else
    #define DCORE extern "C" __declspec(dllexport)
#endif
