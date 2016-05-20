#pragma cuda thread_loop(i) block_size(x,y,z) gridsize(x,y,z)
void sum(float *x, float *y, float *z, int size) {
  int i;
  for(i=0; i<size; i++) {
    z[i] = x[i] + y[i];
  }
}
