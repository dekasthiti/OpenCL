/***** GCL Generated File *********************/
/* Automatically generated file, do not edit! */
/**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dispatch/dispatch.h>
#include <OpenCL/opencl.h>
#include <OpenCL/gcl_priv.h>
#include "mykernel.cl.h"

static void initBlocks(void);

// Initialize static data structures
static block_kernel_pair pair_map[5] = {
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
};

static block_kernel_map bmap = { 0, 5, initBlocks, pair_map };

// Block function
void (^fadd_kernel)(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) =
^(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) {
  int err = 0;
  cl_kernel k = bmap.map[0].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[0].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel fadd does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 0, in1, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 1, in2, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 2, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for fadd failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing fadd failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

void (^fsqrt_kernel)(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) =
^(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) {
  int err = 0;
  cl_kernel k = bmap.map[1].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[1].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel fsqrt does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 0, in1, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 1, in2, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 2, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for fsqrt failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing fsqrt failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

void (^fsqrt_native_kernel)(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) =
^(const cl_ndrange *ndrange, cl_float* in1, cl_float* in2, cl_float* out) {
  int err = 0;
  cl_kernel k = bmap.map[2].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[2].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel fsqrt_native does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 0, in1, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 1, in2, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 2, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for fsqrt_native failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing fsqrt_native failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

void (^condition_kernel)(const cl_ndrange *ndrange, cl_float* in, cl_float* out) =
^(const cl_ndrange *ndrange, cl_float* in, cl_float* out) {
  int err = 0;
  cl_kernel k = bmap.map[3].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[3].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel condition does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 0, in, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 1, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for condition failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing condition failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

void (^optimizedCondition_kernel)(const cl_ndrange *ndrange, cl_float* in, cl_float* out) =
^(const cl_ndrange *ndrange, cl_float* in, cl_float* out) {
  int err = 0;
  cl_kernel k = bmap.map[4].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[4].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel optimizedCondition does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 0, in, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 1, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for optimizedCondition failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing optimizedCondition failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

// Initialization functions
static void initBlocks(void) {
  const char* build_opts = "";
  static dispatch_once_t once;
  dispatch_once(&once,
    ^{ int err = gclBuildProgramBinaryAPPLE("OpenCL/mykernel.cl", "", &bmap, build_opts);
       if (!err) {
          assert(bmap.map[0].block_ptr == fadd_kernel && "mismatch block");
          bmap.map[0].kernel = clCreateKernel(bmap.program, "fadd", &err);
          assert(bmap.map[1].block_ptr == fsqrt_kernel && "mismatch block");
          bmap.map[1].kernel = clCreateKernel(bmap.program, "fsqrt", &err);
          assert(bmap.map[2].block_ptr == fsqrt_native_kernel && "mismatch block");
          bmap.map[2].kernel = clCreateKernel(bmap.program, "fsqrt_native", &err);
          assert(bmap.map[3].block_ptr == condition_kernel && "mismatch block");
          bmap.map[3].kernel = clCreateKernel(bmap.program, "condition", &err);
          assert(bmap.map[4].block_ptr == optimizedCondition_kernel && "mismatch block");
          bmap.map[4].kernel = clCreateKernel(bmap.program, "optimizedCondition", &err);
       }
     });
}

__attribute__((constructor))
static void RegisterMap(void) {
  gclRegisterBlockKernelMap(&bmap);
  bmap.map[0].block_ptr = fadd_kernel;
  bmap.map[1].block_ptr = fsqrt_kernel;
  bmap.map[2].block_ptr = fsqrt_native_kernel;
  bmap.map[3].block_ptr = condition_kernel;
  bmap.map[4].block_ptr = optimizedCondition_kernel;
}

