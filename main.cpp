//
//  main.cpp
//  Microbenchmarks
//
//  Created by Sthiti Deka (Intel) on 8/2/14.
//
//

#include <stdio.h>
#include <vector>

// This include pulls in everything you need to develop with OpenCL in OS X.
#include <OpenCL/opencl.h>

#include "utils.h"
#include "cl_platform.h"
#include "cl_device.h"

// Hard-coded number of values to test, for convenience.
#define NUM_VALUES (1024 * 1024)
#define RUN_TIMES   5
#define PROFILE_RUN 1


using namespace cl_utils;

cl_context                  context;
cl_command_queue            cmdQ;
cl_device_id                intel_device_id;
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
                
                free(platformVendor);
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
                    free(deviceVendor);
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

int main( int argc, char *argv[] )
{
    float*    test_in1;
    float*    test_in2;
    float*    test_out;
    
    cl_mem mem_in1;
    cl_mem mem_in2;
    cl_mem mem_out;
    
    cl_int           err = CL_SUCCESS;
    
    cl_kernel      kernel;
    cl_kernel      nativeKernel;
    
    cl_utils::parseCommandLine(argc, argv);
    const char* compileOptions =  cl_utils::getCompileOptions();
    printf("\nCompile Options: %s", compileOptions );
    
    bool isInitialized = cl_utils::initializeOpenCL();
    if( isInitialized )
    {
        context = getContext();
        cmdQ    = getCommandQ();
        intel_device_id = getIntelDeviceID();

    }
    
    const char* programSrc = getProgramSource("mykernel.cl");
    
    // Build the kernel from source
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&programSrc, NULL, &err );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d creating program with source, exiting...", err );
        exit( 1 );
    }
    
    err = clBuildProgram(program, 1, (cl_device_id*)&intel_device_id, compileOptions, NULL, NULL );
   
    if( err != CL_SUCCESS )
    {
        printf( "Error %d building program, exiting...", err );
        exit( 1 );
    }
    
    
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
    if( err == CL_SUCCESS )
    mem_in1 = clCreateBuffer( context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_mem), (void*)test_in1, &err );
    if( err == CL_SUCCESS )
    mem_in2 = clCreateBuffer( context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_mem),  (void*)test_in2, &err );
    if( err == CL_SUCCESS )
    mem_out = clCreateBuffer( context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_mem), (void*)test_out, &err );

    /*************************************************************/
    /// Set up kernel start
    /*************************************************************/
    kernel = clCreateKernel(program, "fsqrt", &err );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d creating kernel fsqrt, exiting...", err );
        exit( 1 );
    }
    
    err = clSetKernelArg(kernel, 0, sizeof( cl_mem ), (void*)&mem_in1 );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 0, exiting...", err );
        exit( 1 );
    }
    err = clSetKernelArg(kernel, 1, sizeof( cl_mem ), (void*)&mem_in2 );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 0, exiting...", err );
        exit( 1 );
    }
    err = clSetKernelArg(kernel, 2, sizeof( cl_mem ), (void*)&mem_out );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 0, exiting...", err );
        exit( 1 );
    }
    
    nativeKernel = clCreateKernel(program, "fsqrt_native", &err );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d creating kernel fsqrt_native, exiting...", err );
        exit( 1 );
    }
    
    err = clSetKernelArg(nativeKernel, 0, sizeof( cl_mem ), (void*)&mem_in1 );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 0, exiting...", err);
        exit( 1 );
    }
    err = clSetKernelArg(nativeKernel, 1, sizeof( cl_mem ), (void*)&mem_in2 );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 1, exiting...", err );
        exit( 1 );
    }
    err = clSetKernelArg(nativeKernel, 2, sizeof( cl_mem ), (void*)&mem_out );
    if( err != CL_SUCCESS )
    {
        printf( "Error %d setting kernel argument 2, exiting...", err );
        exit( 1 );
    }

    
    
    /**********************************************************/
    // Configure execution parameters
    /**********************************************************/
    size_t wgs = 256;
    const size_t offset[3] = {0,0,0};
    const size_t globalWGS[3] = {NUM_VALUES, 0, 0};
    const size_t localWGS[3]  = {wgs, 0, 0 };
    
    cl_event event = NULL;
    cl_event nativeEvent = NULL;

    for( unsigned int profileRuns = 0; profileRuns < RUN_TIMES; profileRuns++ )
    {
        err = clEnqueueNDRangeKernel( cmdQ, kernel, 1, offset, globalWGS, localWGS, 0, NULL, &event );
        if( err != CL_SUCCESS )
        {
            printf( "\nError %d enqueueing kernel, exiting... ", err );
            exit(1);
        }
        clWaitForEvents(1, &event);
        
        err = clEnqueueNDRangeKernel( cmdQ, nativeKernel, 1, offset, globalWGS, localWGS, 0, NULL, &nativeEvent );
        if( err != CL_SUCCESS )
        {
            printf( "\nError %d enqueueing kernel, exiting... ", err );
            exit(1);
        }
        clWaitForEvents(1, &nativeEvent);
        
        /// Reading back is probably not required for benchmark measurements
        err = clEnqueueReadBuffer(cmdQ, mem_out, CL_TRUE, 0, sizeof(cl_float) * NUM_VALUES, (void*)test_out, 0, NULL, NULL);
        
        double kernelExecuteTime = 0.;

        int64_t startTime            = 0;
        int64_t endTime            = 0;
        
        printf("\n\n Interation %d", profileRuns );

        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &startTime, NULL);
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &endTime, NULL);
        kernelExecuteTime = (double)(endTime - startTime); // nano sec
        printf( "\n Kernel execution time : %10f ns", kernelExecuteTime );
        
        kernelExecuteTime = 0.f;
        clGetEventProfilingInfo(nativeEvent, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &startTime, NULL);
        clGetEventProfilingInfo(nativeEvent, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &endTime, NULL);
        kernelExecuteTime = (double)(endTime - startTime); // nano sec
        printf( "\n Native Kernel execution time : %10f ns", kernelExecuteTime );
    }
   
    
    clReleaseEvent(event);
    clReleaseEvent(nativeEvent);
    clReleaseMemObject(mem_in1);
    clReleaseMemObject(mem_in2);
    clReleaseMemObject(mem_out);
    
    free( test_in1 );
    free( test_in2 );
    free( test_out );

}