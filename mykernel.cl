__kernel void fadd(__global float* in1, __global float* in2, __global float* out)
{
    int idx = get_global_id(0);
    
    out[idx] = in1[idx] + in2[idx];
}