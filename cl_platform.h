//
//  cl_platform.h
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//

#ifndef Microbenchmarks_cl_platform_h
#define Microbenchmarks_cl_platform_h

#include <vector>
#include <assert.h>
#include <string>
#include <Opencl/cl.h>
#define MAX_LENGTH 256

namespace cl_utils
{
    cl_int getPlatformIDs( std::vector<cl_platform_id>& platformIDs );
    cl_int getPlatformInfo( cl_platform_id platformID, cl_platform_info platformInfo, void* info );
}

#endif
