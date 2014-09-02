//
//  cl_device.h
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//

#ifndef Microbenchmarks_cl_device_h
#define Microbenchmarks_cl_device_h

#include <vector>
#include <assert.h>
#include <string>
#include <Opencl/cl.h>

#define MAX_LENGTH 256

namespace cl_utils
{
    cl_int getDeviceIDs( cl_platform_id platform, cl_device_type type, std::vector<cl_device_id>& deviceIDs );
    cl_int getDeviceInfo( cl_device_id deviceID, cl_device_info deviceInfo, void* info );
}

#endif
