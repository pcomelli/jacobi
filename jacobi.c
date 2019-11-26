
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
// jacobi: soluzione dell'equazione di Laplace  
// ad ogni iterazione sostituisce ogni elemento interno della matrice con la media dei 4 vicini 
  size_t i, j, it;
  double * m, * m_new, * mTmp;
  size_t dim = 0, iters = 0;
  // dim dimensione della matrice quadrata
  // iters numero di iterazioni
  size_t dimByte = 0;
  
  if (argc != 3) {
    fprintf(stderr, "\nwrong number of arguments. Usage: ./jacobi dim iterations \n");
    return 1;
  }
  dim = atoi(argv[1]);
  iters = atoi(argv[2]);
  
  printf("m size = %zu\n", dim);
  printf("number of iter = %zu\n", iters);
  // calcolo l'occupazione di una matrice in size_t compresi i bordi
  dimByte = sizeof(double) * (dim + 2) * (dim + 2);
  // alloco lo spazio per le due matrici
  m     = (double * ) malloc(dimByte);
  m_new = (double * ) malloc(dimByte);
  
  
  // azzero le matrici
  for (i = 1; i < (dim + 2) * (dim + 2); ++i)
    m[i] = 0;
    
  // inizializzo i bordi della matrice che non verranno aggiornati
  double incr = 100.0 / (dim + 1);
  for (i = 1; i <= dim + 1; ++i) {
    m[i * (dim + 2)] = i * incr;
    m[((dim + 1) * (dim + 2)) + (dim + 1 - i)] = i * incr;
    m_new[i * (dim + 2)] = i * incr;
    m_new[((dim + 1) * (dim + 2)) + (dim + 1 - i)] = i * incr;
  }
  
  // ciclo principale sulle iterazioni
  for (it = 0; it < iters; ++it) {
    // per ogni elemento interno della matrice
    for (i = 1; i <= dim; ++i) {
      for (j = 1; j <= dim; ++j) {
        m_new[(i * (dim + 2)) + j] = 0.25 * (
	m[((i-1) * (dim + 2)) + j] + m[(i * (dim + 2)) + (j + 1)] + m[((i + 1) * (dim + 2)) + j] + m[(i * (dim + 2)) + (j - 1)]);
      }
    }      
    // faccio lo swap delle matrici
    mTmp = m;
    m = m_new;
    m_new = mTmp;
  }
  FILE * f;
  f = fopen("solution.dat", "w+");
  for (i = 0; i < dim + 2; ++i) {
    for (j = 0; j < dim + 2; ++j) {
      fprintf(f, "%f ", m[(i * (dim + 2)) + j]);
    }
    fprintf(f, "\n");
  }
  fclose(f);
  free(m);
  free(m_new);
  return 0;
}
