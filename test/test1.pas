//#pragma cuda thread_loop(i)
void sum(float *x, float *y, float *z, int size) {
  for(i=0;i<size; i++) {
    z[i] = x[i] + y[i];
  }
}
