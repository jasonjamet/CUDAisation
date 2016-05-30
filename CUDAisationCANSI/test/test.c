int x1 = 2;
int y2 = 2;



#pragma cuda thread_loop(j) block_size(x1,y2) grid_size(16,16)
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

int main() {
  return 0;
}
