#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int verify_n(int n) {
  if (n < 2)
    return -1;
  return 0;
}

void inp_n(int *n) {
  printf("Enter square matrix size: ");
  scanf("%d", n);
  if (verify_n(*n) == -1) {
    printf("Invalid input, try again: ");
    inp_n(n);
  }
}

void fill_mat(int **mat, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      mat[i][j] = rand() % (n * n) + 1;
  }
}

void print_mat(int **mat, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", mat[i][j]);
    printf("\n\n");
  }
}

void alloc_mat(int ***mat, int n) {
  int i;
  *mat = malloc(n * sizeof(int *));
  for (i = 0; i < n; i++)
    (*mat)[i] = malloc(n * sizeof(int));
}

void free_mat(int ***mat, int n) {
  int i;
  for (i = 0; i < n; i++)
    free((*mat)[i]);
  free(*mat);
  *mat = 0;
}

void copy_mat(int **dest, int **src, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      dest[i][j] = src[i][j];
  }
}

void rotate(int **mat, int n) {
  int **mat_copy;
  alloc_mat(&mat_copy, n);
  copy_mat(mat_copy, mat, n);
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      mat[i][j] = mat_copy[n - j - 1][i];
  }
  free_mat(&mat_copy, n);
}

void update_score(int *puan, int **mat, int n) {
  int row = n - 1;
  int col;
  int sum = 0;
  for (col = 0; col < n; ++col)
    sum += mat[row][col];
  *puan += sum;
}

void play_once(int *betul_puan, int *ayse_puan, int **mat, int n,
               int betulun_sirasi) {
  rotate(mat, n);
  printf("The matrix after being rotated 90 degrees: \n\n");
  print_mat(mat, n);
  if (betulun_sirasi == 1)
    update_score(betul_puan, mat, n);
  else
    update_score(ayse_puan, mat, n);
  printf("Player A: %d      Player B: %d\n\n\n", *betul_puan, *ayse_puan);
}

void print_winner(int betul_puan, int ayse_puan) {
  if (betul_puan > ayse_puan)
    printf("Player A won\n");
  else if (betul_puan < ayse_puan)
    printf("Player B won\n");
  else
    printf("Draw\n");
  printf("\n");
}

void play() {
  int n;
  inp_n(&n);
  int **mat;
  alloc_mat(&mat, n);
  fill_mat(mat, n);
  printf("\nThe matrix: \n\n");
  print_mat(mat, n);
  int betul_puan = 0, ayse_puan = 0;
  int i;
  int betulun_sirasi = 1;
  for (i = 0; i < 6; ++i) {
    play_once(&betul_puan, &ayse_puan, mat, n, betulun_sirasi);
    betulun_sirasi = !betulun_sirasi;
  }
  print_winner(betul_puan, ayse_puan);
  free_mat(&mat, n);
}

void print_rules() {
  printf("An n x n matrix is randomly generated. Then, it is rotated 6 times, "
         "each time adding sum of the numbers in the last row to the score of "
         "a player that is selected in alternating pattern\n\n");
}

int main() {
  srand(time(0));

  print_rules();

  char response = 'e';
  do {
    play();
    printf("Continue? (y/Y): ");
    scanf(" %c", &response);
  } while (response == 'y' || response == 'Y');

  printf("\n");
  return 0;
}
