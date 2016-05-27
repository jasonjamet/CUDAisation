#pragma cuda thread_loop(j) block_size(x1,y1,z1) grid_size(x2,y2,z2)
void sum(float *x, float *y, float *z, int size) {
 int i;
 for(i=0; i<size; ++i) {
   z[i] = x[i] + y[i];
 }
 int j;
 for(j=0; j<w; j++) {
         z[i] = x[i] + y[i];
 }
}
