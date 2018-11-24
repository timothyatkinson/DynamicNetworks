#include "dataset.h"
#include "string.h"
#include "matrix_util.h"
dataset* alloc_dataset(){
  dataset* d = malloc(sizeof(dataset));
  return d;
}

void free_dataset(dataset* d){
  for(int i = 0; i < d->train_input_sequence_length; i++){
    gsl_matrix_free(d->train_input_sequence[i]);
  }
  free(d->train_input_sequence);
  gsl_matrix_free(d->train_output);
  for(int i = 0; i < d->validation_input_sequence_length; i++){
    gsl_matrix_free(d->validation_input_sequence[i]);
  }
  gsl_matrix_free(d->validation_output);
  free(d->validation_input_sequence);
  for(int i = 0; i < d->test_input_sequence_length; i++){
    gsl_matrix_free(d->test_input_sequence[i]);
  }
  gsl_matrix_free(d->test_output);
  free(d->test_input_sequence);
  free(d);
}

void read_csv(int row, int col, char *filename, double **data);
void read_csv(int row, int col, char *filename, double **data){
	FILE *file;
  char buffer[10000];
	file = fopen(filename, "r");
  setbuf(file, buffer);
	int i = 0;
    char line[20000];
	while (fgets(line, 20000, file) && (i < row))
    {
    	// double row[ssParams->nreal + 1];
        char* tmp = strdup(line);

	    int j = 0;
	    const char* tok;
	    for (tok = strtok(line, "\t"); tok && *tok; j++, tok = strtok(NULL, "\t\n"))
	    {
	        data[i][j] = atof(tok);
	    }

        free(tmp);
        i++;
    }
    fclose(file);
}

//Loads a dataset
dataset* load_data_set(char* train_file, char* validation_file, char* test_file, int inputs, int outputs, int train_rows, int validation_rows, int test_rows, int warmups){

  dataset* d = alloc_dataset();
  d->train_input_sequence_length = train_rows;
  d->train_input_sequence = malloc(train_rows * sizeof(gsl_matrix*));
  d->train_output = gsl_matrix_calloc(outputs, train_rows);
  d->validation_input_sequence_length = validation_rows;
  d->validation_input_sequence = malloc(validation_rows * sizeof(gsl_matrix*));
  d->validation_output = gsl_matrix_calloc(outputs, validation_rows);
  d->test_input_sequence_length = test_rows;
  d->test_input_sequence = malloc(test_rows * sizeof(gsl_matrix*));
  d->test_output = gsl_matrix_calloc(outputs, test_rows);

  double** train_data = malloc(train_rows * sizeof(double*));
  for(int i = 0; i < train_rows; i++){
    train_data[i] = malloc((inputs + outputs) * sizeof(double));
  }
  double** validation_data = malloc(validation_rows * sizeof(double*));
  for(int i = 0; i < validation_rows; i++){
    validation_data[i] = malloc((inputs + outputs) * sizeof(double));
  }
  double** test_data = malloc(test_rows * sizeof(double*));
  for(int i = 0; i < test_rows; i++){
    test_data[i] = malloc((inputs + outputs) * sizeof(double));
  }

  read_csv(train_rows, inputs + outputs, train_file, train_data);
  read_csv(validation_rows, inputs + outputs, validation_file, validation_data);
  read_csv(test_rows, inputs + outputs, test_file, test_data);

  for(int i = 0; i < train_rows; i++){
    gsl_matrix* in = gsl_matrix_calloc(inputs + 1, 1);
    for(int j = 0; j < inputs; j++){
      gsl_matrix_set(in, j, 0, train_data[i][j]);
    }
    gsl_matrix_set(in, inputs, 0, 1.0);
    for(int j = 0; j < outputs; j++){
      gsl_matrix_set(d->train_output, j, i, train_data[i][j + inputs]);
    }
    d->train_input_sequence[i] = in;
    free(train_data[i]);
  }
  free(train_data);

  for(int i = 0; i < validation_rows; i++){
    gsl_matrix* in = gsl_matrix_calloc(inputs + 1, 1);
    for(int j = 0; j < inputs; j++){
      gsl_matrix_set(in, j, 0, validation_data[i][j]);
    }
    gsl_matrix_set(in, inputs, 0, 1.0);
    for(int j = 0; j < outputs; j++){
      gsl_matrix_set(d->validation_output, j, i, validation_data[i][j + inputs]);
    }
    d->validation_input_sequence[i] = in;
    free(validation_data[i]);
  }
  free(validation_data);

  for(int i = 0; i < test_rows; i++){
    gsl_matrix* in = gsl_matrix_calloc(inputs + 1, 1);
    for(int j = 0; j < inputs; j++){
      gsl_matrix_set(in, j, 0, test_data[i][j]);
    }
    gsl_matrix_set(in, inputs, 0, 1.0);
    for(int j = 0; j < outputs; j++){
      gsl_matrix_set(d->test_output, j, i, test_data[i][j + inputs]);
    }
    d->test_input_sequence[i] = in;
    free(test_data[i]);
  }
  free(test_data);


  d->warmups = warmups;

  return d;
}
