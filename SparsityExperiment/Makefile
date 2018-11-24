INCDIRS=../P-GP2/include ../Math ../Datasets ../Train
LIBDIR=../P-GP2/lib
ATOMIC_MUTATIONS = ../AtomicMutations/mutate_add_edge ../AtomicMutations/mutate_bias ../AtomicMutations/mutate_delete_edge ../AtomicMutations/mutate_edge ../AtomicMutations/mutate_param ../AtomicMutations/mutate_weight
GP2_OBJECTS = $(ATOMIC_MUTATIONS)
OBJECTS := ../Math/*.c ../Datasets/dataset.c ../Datasets/narma.c ../Train/*.c *.c ../d_graph.c ../dnet.c ../P-GP2/lib/util.c
CC=gcc

CFLAGS = 	$(foreach var,$(INCDIRS),-I $(var)) $(foreach var,$(GP2_OBJECTS),-I $(var)) -L $(LIBDIR) -O2 -lgp2 -lgsl -lgslcblas -lm -g


default:	$(OBJECTS)
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o sparsity_exp

clean:
		rm -f -r store_narma_exec
