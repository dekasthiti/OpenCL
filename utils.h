//
//  utils.h
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//

#ifndef Microbenchmarks_utils_h
#define Microbenchmarks_utils_h

#include <vector>
#include <assert.h>
#include <string>
#include <Opencl/cl.h>

namespace cl_utils
{
    
    static bool is_initialized = false;

    // Initialize OpenCL. Should be called only once.
    int initializeOpenCL();
    
    cl_context getContext();
    
    cl_command_queue getCommandQ();
    
    cl_device_id getIntelDeviceID();
    
    int64_t getTickCount();
    
    double getTickFrequency();
    
    const char* getProgramSource( const char* file );
    
    void parseCommandLine( int argc, char* argv[] );
    
    const char* getCompileOptions();
}

#endif
