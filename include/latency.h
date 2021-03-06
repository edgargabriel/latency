#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

#include "mpi.h"

#include <aio.h>

#include "latconfig.h"
#include "lat_sys.h"

#ifdef SR8K
#include <unistd.h>
#include <hmpp/nalloc.h>
#endif


#ifndef __LATENCY_H__
#define __LATENCY_H__

/* some prototypes for utils*/
void LAT_print_status (void);
void LAT_print_hostname (int sender);
void LAT_print_description (char * msg, char *comstr, MPI_Info info);
char* LAT_alloc_memory ( int count, MPI_Datatype datatype );
void LAT_free_memory ( char *buf );
void LAT_print_lat (double sum, double max, double min, double E);
void LAT_print_band (long len, double sum, double max, double min, double E, int caclen);
void LAT_print_init ( char *filename, int partner, MPI_Comm comm, int sender );
void LAT_print_finalize ();
void LAT_print_bandinit ();
void LAT_print ( char *form, ...);

/* some prototypes for transfer */
int LAT_send_recv (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		   char *msg, char *filename, MPI_Info info );
int LAT_sendrecv (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		  char *msg, char *filename, MPI_Info info  );
int LAT_isend_recv (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
                    char *msg, char *filename, MPI_Info info  );
int LAT_send_irecv (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		    char *msg, char *filename, MPI_Info info  );
int LAT_isend_irecv (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
                     char *msg, char *filename, MPI_Info info  );



int LAT_put_startpost (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		       char *msg, char *filename, MPI_Info info );
int LAT_get_startpost (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		       char *msg, char *filename, MPI_Info info );
int LAT_get_winfence (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		      char *msg, char *filename, MPI_Info info );
int LAT_put_winfence (MPI_Comm comm, MPI_Datatype dat, int maxcount, int partner, int sender, 
		      char *msg, char *filename, MPI_Info info );


int LAT_put_winfence_duplex (MPI_Comm comm, MPI_Datatype dat, int maxcount, 
			     int partner, int sender, char *msg, char *filename,
                             MPI_Info info );
int LAT_get_winfence_duplex (MPI_Comm comm, MPI_Datatype dat, int maxcount, 
			     int partner, int sender, char *msg, 
			     char *filename, MPI_Info info );
int LAT_put_startpost_duplex (MPI_Comm comm, MPI_Datatype dat, int maxcount, 
			      int partner, int sender, char *msg, char *filename,
                              MPI_Info info );
int LAT_get_startpost_duplex (MPI_Comm comm, MPI_Datatype dat, int maxcount, 
			      int partner, int sender, char *msg, char *filename,
                              MPI_Info info );


/* some prototypes for datatypes */
MPI_Datatype LAT_twocontint ();
MPI_Datatype LAT_twovecint_nogap ();
MPI_Datatype LAT_twovecint_twointgap ();
MPI_Datatype LAT_92elements ();
MPI_Datatype LAT_hpl_type (int numblocks, int blocklength, int distance);

/*prototypes for communicator creation */
MPI_Comm LAT_comm_connect_brother (MPI_Comm comm, MPI_Info info );
MPI_Comm LAT_comm_connect_sister (MPI_Comm c, MPI_Info i, int ac, char **av);
void LAT_comm_connect_end (MPI_Comm *comm, MPI_Info info );
MPI_Comm LAT_comm_spawn_father (char *cm, int s, MPI_Comm c, MPI_Info i);
MPI_Comm LAT_comm_spawn_son (void);
MPI_Comm LAT_comm_join_brother(MPI_Info info );
MPI_Comm LAT_comm_join_sister(MPI_Info info, int argc, char **argv);


/* prototypes for file I/O benchmarks */
int LAT_seq_write (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_seq_writev (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		    char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_seq_pwrite (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_aio_write (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_seq_fwrite (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_iwrite (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		    char *msg, char *filename, char *path, char *testfile, MPI_Info info);

int LAT_mpi_write_all (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
                   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write_at_all (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
                   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write_ordered (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
                   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write_all_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		    char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write_at_all_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		    char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_write_ordered_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
                   char *msg, char *filename, char *path, char *testfile, MPI_Info info);

int LAT_seq_read (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_seq_fread (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_iread (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		   char *msg, char *filename, char *path, char *testfile, MPI_Info info);

int LAT_mpi_read_all (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read_at_all (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read_ordered (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read_all_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read_at_all_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);
int LAT_mpi_read_ordered_begin (MPI_Comm comm, MPI_Datatype dat, int maxcount, int active,
		  char *msg, char *filename, char *path, char *testfile, MPI_Info info);

int lat_calc_get_size (int msglen, double ttime, int partner, int method, int verbose);
double lat_calc_exec (int problemsize);

int LAT_coll_adcl_ibcast (MPI_Comm comm, MPI_Datatype dat, int maxcount,
                          int active, char *msg, char *filename, MPI_Info info );


#endif /* __LATENCY_H__ */
