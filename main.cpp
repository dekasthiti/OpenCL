//
//  main.cpp
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/2/14.
//
//

#include <stdio.h>

// This include pulls in everything you need to develop with OpenCL in OS X.
#include <OpenCL/opencl.h>

// Include the header file generated by Xcode.  This header file contains the
//  kernel block declaration.                                             // 1
#include "mykernel.cl.h"


// Hard-coded number of values to test, for convenience.
#define NUM_VALUES 1024

int main( int argc, char *argv[] )
{
    float*    test_in1;
    float*    test_in2;
    float*    test_out;
    
    cl_float* mem_in1;
    cl_float* mem_in2;
    cl_float* mem_out;
    
    test_in1 = ( float* )malloc( NUM_VALUES * sizeof( cl_float ) );
    test_in2 = ( float* )malloc( NUM_VALUES * sizeof( cl_float ) );
    test_out = ( float* )malloc( NUM_VALUES * sizeof( cl_float ) );
    
    // Initialize system memory
    for( unsigned int i = 0; i < NUM_VALUES; i++ )
    {
        test_in1[i] = i;
        test_in2[i] = i;
        test_out[i] = 0;
    }
    
    // Initialize device memory
    mem_in1 = ( cl_float* )gcl_malloc( NUM_VALUES * sizeof( cl_float ), test_in1, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR );
    mem_in2 = ( cl_float* )gcl_malloc( NUM_VALUES * sizeof( cl_float ), test_in2, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR );
    mem_out = ( cl_float* )gcl_malloc( NUM_VALUES * sizeof( cl_float ), NULL, CL_MEM_WRITE_ONLY );
    
    dispatch_queue_t queue = gcl_create_dispatch_queue( CL_DEVICE_TYPE_GPU, NULL );
    
    if( queue != NULL )
    {
        dispatch_sync(
                      queue,
                      ^{
                          size_t wgs;
                          gcl_get_kernel_block_workgroup_info( fadd_kernel,
                                                              CL_KERNEL_WORK_GROUP_SIZE,
                                                              sizeof(wgs),
                                                              &wgs,
                                                              NULL
                                                              );
                          cl_ndrange range = {
                              1,
                              {0, 0, 0},
                              {NUM_VALUES, 0, 0},
                              {wgs, 0, 0},
                          };
                    
                          fadd_kernel( &range, ( cl_float* )mem_in1, ( cl_float* )mem_in2, ( cl_float* )mem_out);
                          gcl_memcpy( test_out, mem_out, sizeof( cl_float ) * NUM_VALUES );
                          
                         } );
       

    }
    
    // Clean up
    gcl_free( mem_in1 );
    gcl_free( mem_in2 );
    gcl_free( mem_out );
    
    dispatch_release( queue );
    
    free( test_in1 );
    free( test_in2 );
    free( test_out );

}