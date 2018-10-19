#ifndef MU_H
#define MU_H

#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>
#include "moore_penrose.h"
#include <assert.h>

/**print_matrix - PRINT MATRIX
  *Prints a gsl_matrix.
    * m. The matrix to print.
*/
void print_matrix(const gsl_matrix *m);

/**print_vector - PRINT VECTOR
  *Prints a gsl_vector.
    * v. The vector to print.
*/
void print_vector (const gsl_vector * v);

/**gsl_matrix_multiply - GSL MATRIX MULTIPLY
  *Multiplies 2 gsl_matrices together a.b, returning the produced matrix as a pointer. Preserves existing matrices. Multiplication is done using the CBLAS function gsl_blas_dgemm.
    * a. The first (left) matrix.
    * b. The second (right) matrix.
*/
gsl_matrix* gsl_matrix_multiply(gsl_matrix* a, gsl_matrix* b);

/**gsl_matrix_sum - GSL MATRIX SUM
  *Add 2 gsl_matrices together a+b, returning the produced matrix as a pointer. Preserves existing matrices.
    * a. The first (left) matrix.
    * b. The second (right) matrix.
*/
gsl_matrix* gsl_matrix_sum(gsl_matrix* a, gsl_matrix* b);

/**gsl_matrix_det - GSL MATRIX DET
	*Computes the determinant of a matrix using its LU decomposition.
		*a. The matrix to get the determinant of.
*/
double gsl_matrix_det(gsl_matrix* a);

/**gsl_matrix_inverse - GSL MATRIX INVERSE
	*Computes the inverse of a matrix based on its LU decomposition.
		*a. The matrix to inverse.
*/
gsl_matrix* gsl_matrix_inverse(gsl_matrix* a);

/**gsl_matrix_pinv - GSL MATRIX PSEUDOINVERSE
  *A non-destructive wrapper for moore_penrose_pinv (see moore_penrose.c).
    * a. The matrix to inverse.
    * rcond. 	A real number specifying the singular value threshold for inclusion. NumPy default for ``rcond`` is 1E-15.
*/
gsl_matrix* gsl_matrix_pinv(gsl_matrix* a, double rcond);



/**Multiplies 2 gsl_matrices together at.b, returning the produced matrix as a pointer. Preserves existing matrices. Multiplication is done using the CBLAS function gsl_blas_dgemm.
    * a. The first (left) matrix. This is transposed.
    * b. The second (right) matrix.
*/
gsl_matrix* gsl_matrix_multiply_transpose_a(gsl_matrix* a, gsl_matrix* b);

/**Multiplies 2 gsl_matrices together a.bt, returning the produced matrix as a pointer. Preserves existing matrices. Multiplication is done using the CBLAS function gsl_blas_dgemm.
    * a. The first (left) matrix.
    * b. The second (right) matrix. This is transposed.
*/
gsl_matrix* gsl_matrix_multiply_transpose_b(gsl_matrix* a, gsl_matrix* b);

/** gsl_matrix_eigenvalues - GSL MATRIX EIGENVALUES
	* A non-destructive computation of a matrix's eigenvalues using gsl_eigen_symm.
		* The matrix to get the eigenvalues of.
*/
gsl_vector* gsl_matrix_eigen_values(gsl_matrix* a);

/** gsl_matrix_max_eigenvalue - GSL MATRIX MAX EIGENVALUE
	* Computes the maximum eigenvalue of a matrix.
		* a. The matrix to get the maximum eigenvalue of.
*/
double gsl_matrix_max_eigenvalue(gsl_matrix* a);

//Generate vector. Generates a rows * 1 matrix all set to the default value given.
/*
Inputs:
	int rows. The number of rows.
	double default_value. The value in each element of the matrix.
Returns:
	gsl_matrix* matrix. The generated rows * 1 matrix.
*/
gsl_matrix* generate_vector(int rows, double default_value);

//Applies a transformation to every element of a matrix. Non-destructive.
/*
Inputs:
  gsl_matrix* a. The matrix to transform.
  double (*function)(double value). The linear transformation.
Returns
  gsl_matrix* b. The transformed matrix.
*/
gsl_matrix* apply_function(gsl_matrix* a, double (*function)(double value));

//Adds a column to every column of a matrix.
/*
Inputs:
  gsl_matrix* a. The matrix to add a column to.
  gsl_matrix* column. The column to add.
*/
gsl_matrix* add_column(gsl_matrix* a, gsl_matrix* column);

//Does a dot Multiplication
/*
Inputs:
  gsl_matrix* a.
  gsl_matrix* b.
*/
gsl_matrix* gsl_matrix_dot(gsl_matrix* a, gsl_matrix* b);
#endif
