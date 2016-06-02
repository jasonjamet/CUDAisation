int x1 = 2;
int y2 = 2;




#pragma cuda thread_loop(j) block_size(x1,y2) nbr_threads(16)
void sum(float *x, float *y, float *z, int size) {
 int i;
 for(i=0; i<size; ++i) {
   z[i] = x[i] + y[i];
 }
 int j;
 for(j=0; j<size; j++) {
    z[j] = x[j] + y[i];
 }
}

int main(int argc, char *argv[]) {
  int vector_size = 10;
  float h_x[vector_size], h_y[vector_size], h_z[vector_size];
  int i = 0;

  for (i = 0;i < vector_size; i++) {
		h_x[i] = i;
		h_y[i] = i;
	}

  sum(h_x, h_y, h_z, vector_size);

  return 0;
}
