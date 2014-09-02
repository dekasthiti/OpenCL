//
//  File.cpp : Back up for working functionality that creates cl_device, platform, context, command queue etc.
// Do not compile
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/17/14.
//
//

#include "File.h"
/// This file

std::vector<cl_platform_id>   platformIDs;
std::vector<cl_device_id>    deviceIDs;
cl_command_queue cmdQ = NULL;
cl_context       context = NULL;

cl_int           err;

cl_uint          numPlatforms;
cl_uint          numDevices;
cl_platform_id apple_platform_id;
cl_device_id   intel_device_id;

cl_kernel      kernel;
cl_kernel      nativeKernel;
cl_kernel      conditionKernel;
cl_kernel      optimizedConditionKernel;


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
        
        /// @todo: Get IDs of all device types
        
        
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


/// GFlops measurement

/// ops  = (2 ops per mad)
///double GFlops     = (ops * NUM_VALUES ) / kernelExecuteTime;
///printf("\n Throughput of a floating point addition operation: %f", GFlops );
