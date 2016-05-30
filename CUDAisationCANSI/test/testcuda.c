int x1 = 2;
int y1 = 2;

__global__
void kernel_sum(float *x, float *y, float *z, int size)
{
	int i;
	for ( i = 0; i < size; ++i )
	{
		z[i] = x[i] + y[i];
	}
	int j = (((blockIdx.x * gridDim.y + blockIdx.y) * blockDim.x + threadIdx.x) * blockDim.y + threadIdx.y);
	if (j < size)
	{
		z[i] = x[i] + y[i];
	}
}
void sum(float *x, float *y, float *z, int size)
{
	 kernel_sum <<< dim3((16 + x1*y1 - 1 ) / x1*y1, (16 + x1*y1 - 1 ) / x1*y1), dim3(x1, y1) >>> (x, y, z, size);
}
int main()
{
	return 0;
}
