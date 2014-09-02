//
//  cl_device.cpp
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//


#include "cl_device.h"

namespace cl_utils
{

    cl_int getDeviceIDs( cl_platform_id platform, cl_device_type type, std::vector<cl_device_id>& devices )
    {
        cl_int err = CL_SUCCESS;
        
        cl_uint numDevices = 0;
        
        err = clGetDeviceIDs( platform, type, 0, NULL, &numDevices );
        
        if( err == CL_SUCCESS )
        {
            //devices.clear;
            devices.resize( numDevices );
            
            err = clGetDeviceIDs( platform, type, numDevices, &devices[0], NULL );
            
        }
        
        return err;
    }
    
    cl_int getDeviceInfo( cl_device_id deviceID, cl_device_info deviceInfo, void* info )
    {
        cl_int err = CL_SUCCESS;
        
        err = clGetDeviceInfo( deviceID, deviceInfo, MAX_LENGTH, info, NULL );
        return err;
    }
} // end namespace