//
//  utils.cpp
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//

#if defined __MACH__ && defined __APPLE__
#include <mach/mach_time.h>
#endif

#include <string>
#include "utils.h"
#include "cl_platform.h"
#include "cl_device.h"

namespace cl_utils
{
   
    cl_context                  context;
    cl_command_queue            cmdQ;
    cl_device_id                intel_device_id;
    
    char* compileOptions;

    int initializeOpenCL()
    {
        
        std::vector<cl_platform_id> platformIDs;
        std::vector<cl_device_id>   deviceIDs;
        
        cl_int err = CL_SUCCESS;
        
        assert( is_initialized == false );
        
        cl_platform_id apple_platform_id;
        cl_uint          numPlatforms;
        cl_uint          numDevices;

        
        err = clGetPlatformIDs( 0, NULL, &numPlatforms );
        if( err == CL_SUCCESS )
        {
            platformIDs.clear();
            platformIDs.resize( numPlatforms );
            err = clGetPlatformIDs(numPlatforms, (cl_platform_id *)(&platformIDs[0]), NULL );
            
            if( err == CL_SUCCESS )
            {
                
                for( unsigned int i = 0; i < platformIDs.size(); i++ )
                {
                    char* platformVendor = (char*)malloc( sizeof( char ) * MAX_LENGTH );
                    
                    if( platformVendor != NULL )
                    {
                        err = clGetPlatformInfo( platformIDs[i], CL_PLATFORM_VENDOR, MAX_LENGTH, (void*)platformVendor, NULL );
                        
                        if( strcmp((const char*)platformVendor, "Apple") == 0 )
                        {
                            apple_platform_id = platformIDs[i];
                            break;
                        }
                    }
                }
                
                err = clGetDeviceIDs( apple_platform_id, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices );
                
                if( err == CL_SUCCESS )
                {
                    deviceIDs.clear();
                    deviceIDs.resize( numDevices );
                    err = clGetDeviceIDs( apple_platform_id, CL_DEVICE_TYPE_GPU, numDevices, (cl_device_id*)(&deviceIDs[0]), NULL );
                    
                }
                
                if( err == CL_SUCCESS)
                {
                    for( unsigned int j = 0; j < deviceIDs.size(); j++ )
                    {
                        char* deviceVendor = (char*)malloc( sizeof( char ) * MAX_LENGTH );
                        err = clGetDeviceInfo(deviceIDs[j], CL_DEVICE_VENDOR, MAX_LENGTH, (void*)deviceVendor, NULL );
                        
                        if( strcmp( ( const char* )deviceVendor, "Intel") == 0 )
                        {
                            intel_device_id = deviceIDs[j];
                            break;
                        }
                    }
                    
                    if( err == CL_SUCCESS )
                    {
                        cl_context_properties ctxtProps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)apple_platform_id, 0 };
                        context = clCreateContext(ctxtProps, 1, &(intel_device_id), NULL, NULL, &err );
            
                        
                        if( err == CL_SUCCESS )
                        {
                            cl_command_queue_properties cmdQProps = { CL_QUEUE_PROFILING_ENABLE };
                            cmdQ = clCreateCommandQueue( context, intel_device_id, cmdQProps, &err );
                            
                        }
                    }
                    
                }
                
            }
            
        }

        is_initialized = true;
        
        /// returning dummy value;
        return is_initialized;
    }
    
    int64_t getTickCount()
    {
        return (int64_t)mach_absolute_time();
    }
    
    double getTickFrequency()
    {
        static double freq = 0;
        
        if( freq == 0 )
        {
            mach_timebase_info_data_t sTimebaseInfo;
            mach_timebase_info(&sTimebaseInfo);
            freq = sTimebaseInfo.denom * 1e9 / sTimebaseInfo.numer;
        }
        return freq;
    }
    
    const char* getProgramSource( const char* file )
    {
        // Load the program source from file
        FILE* fp = NULL;
        long numChars = 0;
        
        fp = fopen( file, "rb" );
        if( fp != NULL )
        {
            /// Get the size of the file
            fseek( fp, 0, SEEK_END );
            numChars = ftell( fp );
            fseek( fp, 0, SEEK_SET );
            
        }
        
        char* programSrc = (char*)malloc( sizeof( char ) * numChars );
        if( programSrc != NULL )
        {
            size_t len = fread( programSrc, sizeof(char), numChars, fp );
            if(len == 0)
            {
                printf( "\n Error reading program source file\n");
                
            }
        }
        return (const char*)programSrc;
    }
    
    
    cl_context getContext()
    {
        return context;
    }
    
    cl_command_queue getCommandQ()
    {
        return cmdQ;
    }
    
    cl_device_id getIntelDeviceID()
    {
        return intel_device_id;
    }
    
    void parseCommandLine( int argc, char* argv[])
    {
        for( size_t i = 1; i < argc; i++ )
        {
            char* start = strstr(argv[i], "options");
            
            if( start != NULL )
            {
                start = strstr( (const char*)start, "=");
                if( start != NULL )
                {
                    compileOptions = start + 1;
                }
            }
        }
    }
    
    const char* getCompileOptions()
    {
        return (const char*)compileOptions;
    }
    
}