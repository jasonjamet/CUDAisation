#pragma cuda thread_loop(j) block_size(x,y,z) grid_size(x,y,z)
void sum(float *x, float *y, float *z, int size) {
  int i;
  for(i=0; i<size; ++i) {
    z[i] = x[i] + y[i];
  }
  int j;
  for(j=0; j<size; j++) {
  		z[i] = x[i] + y[i];
  }
}

void sum(float *x, float *y, float *z, int size) {
  int i;
  for(i=0; i<size; ++i) {
    z[i] = x[i] + y[i];
  }
  int j;
  for(j=0; j<size; j++) {
  		z[i] = x[i] + y[i];
  }
}
