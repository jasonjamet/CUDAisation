#pragma cuda thread_loop(j) block_size(x,y,z) grid_size(x,y,z)
void sum(float *x, float *y, float *z, int size) {
  int i, j;
  for(i=0; i<size; ++i) {
    z[i] = x[i] + y[i];
  }
  for(j=0; j<size; j++) {
  }
}
