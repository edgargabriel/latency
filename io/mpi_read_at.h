#ifndef __LAT_MPI_READ_AT__
#define __LAT_MPI_READ_AT__

/* Public interface */
#define LAT_FD      MPI_File

#define LAT_FILE_METHODOLOGY_STRING "MPI_File_read_at()"
#define LAT_FILE_METHODOLOGY        LAT_mpi_read_at

/* set for methods doing simplex data transfer to 1, 
   set for methods doing duplex data transfer  to 2 */
#define LAT_FACTOR       1

/* define whether you need a second buffer:
   set to 0 if not, to 1 if you need */
#define LAT_NEED_SECOND_BUF  0

/* define LAT_BUF_FACTOR to 1, if you would like to 
   allocate maxcount * extent(datatype) buffer length.
   Some methods need this size * 2 */
#define LAT_BUF_FACTOR     1

/* define LAT_TIME_FACTOR to 2 for ping-pong tests
   (you are dividing the measured time by two)
   and to 1 for duplex tests */
#define LAT_TIME_FACTOR     1

/* internal interfaces */
#define LAT_FILE_MEASUREMENT       LAT_mpi_read_at_test

/* define whether we are reading or writing */
#define LAT_WRITE 0

/* define how the file shall be opened */
#define LAT_FILE_MODE  MPI_MODE_RDONLY

/* Implementation of methodology specific initialization functions */
#define LAT_FILE_OPEN_FN(_c,_name,_mode){                    \
    int _ret;                                                \
    _ret = MPI_File_open ( MPI_COMM_SELF, _name, _mode,      \
                           _c.info, &_c.fd);                 \
    if (_ret != MPI_SUCCESS ) MPI_Abort (MPI_COMM_WORLD, 1); \
    MPI_File_set_view (_c.fd,0,_c.dat,_c.dat,"native",_c.info); \
    _c.offset = 0;                                           \
}

#define LAT_FILE_CLOSE_FN(_c)  MPI_File_close(&_c.fd)                    
#define LAT_FILE_SYNC_FN(_c)   MPI_File_sync(_c.fd)


/* bandwidth measurement functions */
#define LAT_FILE_MEASUREMENT_INIT_FN(_c) {         \
  MPI_Status _status;                              \
  MPI_File_read_at ( _c.fd, (MPI_Offset) _c.offset, _c.buf, \
                      _c.cnt, _c.dat, &_status);   \
  _c.offset += _c.len;                             \
} 

#define LAT_FILE_MEASUREMENT_FIN_FN(_c)

#endif /* __LAT_SEQ_READ__ */