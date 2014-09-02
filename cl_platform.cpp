//
//  cl_platform.cpp
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/3/14.
//
//


#include "cl_platform.h"

namespace cl_utils
{
    
    cl_int getPlatformIDs( std::vector<cl_platform_id>& platforms )
    {
        cl_int err = CL_SUCCESS;
        
        cl_uint numPlatforms = 0;
        
        err = clGetPlatformIDs( 0, NULL, &numPlatforms );
        
        if( err != CL_SUCCESS )
        {
            return err;
        }
        else
        {
            platforms.clear();
            platforms.resize( numPlatforms );
            
            err = clGetPlatformIDs( numPlatforms, &platforms[0], NULL );
            
            if( err != CL_SUCCESS )
            {
                return err;
            }
        }
        return CL_SUCCESS;
    }
    
    cl_int getPlatformInfo( cl_platform_id platformID, cl_platform_info platformInfo, void* info )
    {
        cl_int err = CL_SUCCESS;
        
        err = clGetPlatformInfo( platformID, platformInfo, MAX_LENGTH, info, NULL );
        
        return err;
    }
}