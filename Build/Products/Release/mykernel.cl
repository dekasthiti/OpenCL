__kernel void fadd(__global float* in1, __global float* in2, __global float* out)
{
    int idx = get_global_id(0);
    
    out[idx] = in1[idx] * 3.174f + in2[idx];
}

__kernel void fsqrt(__global float* in1, __global float* in2, __global float* out)
{
    int idx = get_global_id(0);
    
    out[idx] = sqrt(in1[idx]) + sqrt(in2[idx]) + powr(in1[idx], 2);
}

__kernel void fsqrt_native(__global float* in1, __global float* in2, __global float* out)
{
    int idx = get_global_id(0);
    
    out[idx] = native_sqrt(in1[idx]) + native_sqrt(in2[idx]) + native_powr(in1[idx], 2);
}

__kernel void condition(__global float* in, __global float* out )
{
    int idx = get_global_id(0);
    
//    if( idx%2 == 0)
//        out[idx] = 0;
//    else
//        out[idx] = 1;
    
    if( idx > 0)
        out[idx] = in[idx];
    
    
}

__kernel void optimizedCondition(__global float* in, __global float* out )
{
    int idx = get_global_id(0) + 1;
    
    //out[idx] = (idx %2 )== 0;
    
    out[idx] = in[idx];
    
}
