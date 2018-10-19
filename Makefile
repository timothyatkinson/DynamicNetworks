INCDIRS=P-GP2/include Math GP2_Programs/random_d_graph
LIBDIR=P-GP2/lib
GP2_OBJECTS =
OBJECTS := Math/*.c GP2_Programs/random_d_graph/*.c *.c
CC=gcc

CFLAGS = 	$(foreach var,$(INCDIRS),-I $(var)) $(foreach var,$(GP2_OBJECTS),-I $(var)) -L $(LIBDIR) -O2 -lgp2 -lgsl -lgslcblas -lm -g

default:	$(OBJECTS)
		$(foreach var,$(GP2_OBJECTS),rm -f -r $(var); mkdir -p $(var);	echo '$(var) compile'; P-GP2/bin/gp2 -l P-GP2 -m $(notdir $(var)) -o $(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o $(output)

clean:
		rm -f -r $(output)
		rm -f -r pgp2
