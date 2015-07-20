typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef int wchar_t;
typedef ptrdiff_t MPI_Aint;
typedef long long MPI_Offset;
typedef struct ompi_communicator_t *MPI_Comm;
typedef struct ompi_datatype_t *MPI_Datatype;
typedef struct ompi_errhandler_t *MPI_Errhandler;
typedef struct ompi_file_t *MPI_File;
typedef struct ompi_group_t *MPI_Group;
typedef struct ompi_info_t *MPI_Info;
typedef struct ompi_op_t *MPI_Op;
typedef struct ompi_request_t *MPI_Request;
typedef struct ompi_status_public_t MPI_Status;
typedef struct ompi_win_t *MPI_Win;
struct ompi_status_public_t
{
        int MPI_SOURCE;
        int MPI_TAG;
        int MPI_ERROR;
        int _cancelled;
        size_t _ucount;
};
typedef struct ompi_status_public_t ompi_status_public_t;
typedef int (MPI_Copy_function)(MPI_Comm, int, void *, void *, void *, int *);
typedef int (MPI_Delete_function)(MPI_Comm, int, void *, void *);
typedef int (MPI_Datarep_extent_function)(MPI_Datatype, MPI_Aint *, void *);
typedef int (MPI_Datarep_conversion_function)(void *, MPI_Datatype, int, void *, MPI_Offset, void *);
typedef void (MPI_Comm_errhandler_function)(MPI_Comm *, int *, ...);
typedef MPI_Comm_errhandler_function MPI_Comm_errhandler_fn;
typedef void (ompi_file_errhandler_fn)(MPI_File *, int *, ...);
typedef ompi_file_errhandler_fn MPI_File_errhandler_fn;
typedef ompi_file_errhandler_fn MPI_File_errhandler_function;
typedef void (MPI_Win_errhandler_function)(MPI_Win *, int *, ...);
typedef MPI_Win_errhandler_function MPI_Win_errhandler_fn;
typedef void (MPI_Handler_function)(MPI_Comm *, int *, ...);
typedef void (MPI_User_function)(void *, void *, int *, MPI_Datatype *);
typedef int (MPI_Comm_copy_attr_function)(MPI_Comm, int, void *, void *, void *, int *);
typedef int (MPI_Comm_delete_attr_function)(MPI_Comm, int, void *, void *);
typedef int (MPI_Type_copy_attr_function)(MPI_Datatype, int, void *, void *, void *, int *);
typedef int (MPI_Type_delete_attr_function)(MPI_Datatype, int, void *, void *);
typedef int (MPI_Win_copy_attr_function)(MPI_Win, int, void *, void *, void *, int *);
typedef int (MPI_Win_delete_attr_function)(MPI_Win, int, void *, void *);
typedef int (MPI_Grequest_query_function)(void *, MPI_Status *);
typedef int (MPI_Grequest_free_function)(void *);
typedef int (MPI_Grequest_cancel_function)(void *, int);
enum 
{
    MPI_TAG_UB, 
    MPI_HOST, 
    MPI_IO, 
    MPI_WTIME_IS_GLOBAL, 
    MPI_APPNUM, 
    MPI_LASTUSEDCODE, 
    MPI_UNIVERSE_SIZE, 
    MPI_WIN_BASE, 
    MPI_WIN_SIZE, 
    MPI_WIN_DISP_UNIT, 
    IMPI_CLIENT_SIZE, 
    IMPI_CLIENT_COLOR, 
    IMPI_HOST_SIZE, 
    IMPI_HOST_COLOR
};
enum 
{
    MPI_IDENT, 
    MPI_CONGRUENT, 
    MPI_SIMILAR, 
    MPI_UNEQUAL
};
enum 
{
    MPI_THREAD_SINGLE, 
    MPI_THREAD_FUNNELED, 
    MPI_THREAD_SERIALIZED, 
    MPI_THREAD_MULTIPLE
};
enum 
{
    MPI_COMBINER_NAMED, 
    MPI_COMBINER_DUP, 
    MPI_COMBINER_CONTIGUOUS, 
    MPI_COMBINER_VECTOR, 
    MPI_COMBINER_HVECTOR_INTEGER, 
    MPI_COMBINER_HVECTOR, 
    MPI_COMBINER_INDEXED, 
    MPI_COMBINER_HINDEXED_INTEGER, 
    MPI_COMBINER_HINDEXED, 
    MPI_COMBINER_INDEXED_BLOCK, 
    MPI_COMBINER_STRUCT_INTEGER, 
    MPI_COMBINER_STRUCT, 
    MPI_COMBINER_SUBARRAY, 
    MPI_COMBINER_DARRAY, 
    MPI_COMBINER_F90_REAL, 
    MPI_COMBINER_F90_COMPLEX, 
    MPI_COMBINER_F90_INTEGER, 
    MPI_COMBINER_RESIZED
};
__attribute__((visibility("default"))) int OMPI_C_MPI_TYPE_NULL_DELETE_FN(MPI_Datatype datatype, int type_keyval, void *attribute_val_out, void *extra_state);
__attribute__((visibility("default"))) int OMPI_C_MPI_TYPE_NULL_COPY_FN(MPI_Datatype datatype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_TYPE_DUP_FN(MPI_Datatype datatype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_COMM_NULL_DELETE_FN(MPI_Comm comm, int comm_keyval, void *attribute_val_out, void *extra_state);
__attribute__((visibility("default"))) int OMPI_C_MPI_COMM_NULL_COPY_FN(MPI_Comm comm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_COMM_DUP_FN(MPI_Comm comm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_NULL_DELETE_FN(MPI_Comm comm, int comm_keyval, void *attribute_val_out, void *extra_state);
__attribute__((visibility("default"))) int OMPI_C_MPI_NULL_COPY_FN(MPI_Comm comm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_DUP_FN(MPI_Comm comm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_WIN_NULL_DELETE_FN(MPI_Win window, int win_keyval, void *attribute_val_out, void *extra_state);
__attribute__((visibility("default"))) int OMPI_C_MPI_WIN_NULL_COPY_FN(MPI_Win window, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) int OMPI_C_MPI_WIN_DUP_FN(MPI_Win window, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
__attribute__((visibility("default"))) extern struct ompi_predefined_communicator_t ompi_mpi_comm_world;
__attribute__((visibility("default"))) extern struct ompi_predefined_communicator_t ompi_mpi_comm_self;
__attribute__((visibility("default"))) extern struct ompi_predefined_communicator_t ompi_mpi_comm_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_group_t ompi_mpi_group_empty;
__attribute__((visibility("default"))) extern struct ompi_predefined_group_t ompi_mpi_group_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_request_t ompi_request_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_min;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_max;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_sum;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_prod;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_land;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_band;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_lor;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_bor;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_lxor;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_bxor;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_maxloc;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_minloc;
__attribute__((visibility("default"))) extern struct ompi_predefined_op_t ompi_mpi_op_replace;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_datatype_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_lb;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_ub;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_char;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_signed_char;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_char;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_byte;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_short;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_short;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_unsigned;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_long;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_long;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_long_long_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_long_long;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_float;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_double;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_long_double;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_wchar;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_packed;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_cxx_bool;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_cxx_cplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_cxx_dblcplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_cxx_ldblcplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_logical;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_character;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_real;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_dblprec;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_cplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_dblcplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_ldblcplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2integer;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2real;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2dblprec;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2cplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_2dblcplex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_float_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_double_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_longdbl_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_short_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_long_int;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_logical1;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_logical2;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_logical4;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_logical8;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer1;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer2;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer4;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer8;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_integer16;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_real2;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_real4;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_real8;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_real16;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_complex8;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_complex16;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_complex32;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_int8_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_uint8_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_int16_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_uint16_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_int32_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_uint32_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_int64_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_uint64_t;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_aint;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_offset;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_c_bool;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_c_complex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_c_float_complex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_c_double_complex;
__attribute__((visibility("default"))) extern struct ompi_predefined_datatype_t ompi_mpi_c_long_double_complex;
__attribute__((visibility("default"))) extern struct ompi_predefined_errhandler_t ompi_mpi_errhandler_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_errhandler_t ompi_mpi_errors_are_fatal;
__attribute__((visibility("default"))) extern struct ompi_predefined_errhandler_t ompi_mpi_errors_return;
__attribute__((visibility("default"))) extern struct ompi_predefined_win_t ompi_mpi_win_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_file_t ompi_mpi_file_null;
__attribute__((visibility("default"))) extern struct ompi_predefined_info_t ompi_mpi_info_null;
__attribute__((visibility("default"))) extern int *MPI_F_STATUS_IGNORE;
__attribute__((visibility("default"))) extern int *MPI_F_STATUSES_IGNORE;
__attribute__((visibility("default"))) int MPI_Abort(MPI_Comm comm, int errorcode);
__attribute__((visibility("default"))) int MPI_Accumulate(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Add_error_class(int *errorclass);
__attribute__((visibility("default"))) int MPI_Add_error_code(int errorclass, int *errorcode);
__attribute__((visibility("default"))) int MPI_Add_error_string(int errorcode, char *string);
__attribute__((visibility("default"))) int MPI_Address(void *location, MPI_Aint *address);
__attribute__((visibility("default"))) int MPI_Allgather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Allgatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr);
__attribute__((visibility("default"))) int MPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Alltoallv(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Alltoallw(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype *sendtypes, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype *recvtypes, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Attr_delete(MPI_Comm comm, int keyval);
__attribute__((visibility("default"))) int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val);
__attribute__((visibility("default"))) int MPI_Barrier(MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Bsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Bsend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Buffer_attach(void *buffer, int size);
__attribute__((visibility("default"))) int MPI_Buffer_detach(void *buffer, int *size);
__attribute__((visibility("default"))) int MPI_Cancel(MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int *coords);
__attribute__((visibility("default"))) int MPI_Cart_create(MPI_Comm old_comm, int ndims, int *dims, int *periods, int reorder, MPI_Comm *comm_cart);
__attribute__((visibility("default"))) int MPI_Cart_get(MPI_Comm comm, int maxdims, int *dims, int *periods, int *coords);
__attribute__((visibility("default"))) int MPI_Cart_map(MPI_Comm comm, int ndims, int *dims, int *periods, int *newrank);
__attribute__((visibility("default"))) int MPI_Cart_rank(MPI_Comm comm, int *coords, int *rank);
__attribute__((visibility("default"))) int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest);
__attribute__((visibility("default"))) int MPI_Cart_sub(MPI_Comm comm, int *remain_dims, MPI_Comm *new_comm);
__attribute__((visibility("default"))) int MPI_Cartdim_get(MPI_Comm comm, int *ndims);
__attribute__((visibility("default"))) int MPI_Close_port(char *port_name);
__attribute__((visibility("default"))) int MPI_Comm_accept(char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int MPI_Comm_c2f(MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode);
__attribute__((visibility("default"))) int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
__attribute__((visibility("default"))) int MPI_Comm_connect(char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
__attribute__((visibility("default"))) int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
__attribute__((visibility("default"))) int MPI_Comm_disconnect(MPI_Comm *comm);
__attribute__((visibility("default"))) int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) MPI_Comm MPI_Comm_f2c(int comm);
__attribute__((visibility("default"))) int MPI_Comm_free_keyval(int *comm_keyval);
__attribute__((visibility("default"))) int MPI_Comm_free(MPI_Comm *comm);
__attribute__((visibility("default"))) int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler);
__attribute__((visibility("default"))) int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
__attribute__((visibility("default"))) int MPI_Comm_get_parent(MPI_Comm *parent);
__attribute__((visibility("default"))) int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
__attribute__((visibility("default"))) int MPI_Comm_join(int fd, MPI_Comm *intercomm);
__attribute__((visibility("default"))) int MPI_Comm_rank(MPI_Comm comm, int *rank);
__attribute__((visibility("default"))) int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group);
__attribute__((visibility("default"))) int MPI_Comm_remote_size(MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
__attribute__((visibility("default"))) int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int MPI_Comm_set_name(MPI_Comm comm, char *comm_name);
__attribute__((visibility("default"))) int MPI_Comm_size(MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int MPI_Comm_spawn(char *command, char **argv, int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes);
__attribute__((visibility("default"))) int MPI_Comm_spawn_multiple(int count, char **array_of_commands, char ***array_of_argv, int *array_of_maxprocs, MPI_Info *array_of_info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes);
__attribute__((visibility("default"))) int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int MPI_Comm_test_inter(MPI_Comm comm, int *flag);
__attribute__((visibility("default"))) int MPI_Dims_create(int nnodes, int ndims, int *dims);
__attribute__((visibility("default"))) int MPI_Errhandler_c2f(MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) MPI_Errhandler MPI_Errhandler_f2c(int errhandler);
__attribute__((visibility("default"))) int MPI_Errhandler_free(MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int MPI_Error_class(int errorcode, int *errorclass);
__attribute__((visibility("default"))) int MPI_Error_string(int errorcode, char *string, int *resultlen);
__attribute__((visibility("default"))) int MPI_Exscan(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_File_c2f(MPI_File file);
__attribute__((visibility("default"))) MPI_File MPI_File_f2c(int file);
__attribute__((visibility("default"))) int MPI_File_call_errhandler(MPI_File fh, int errorcode);
__attribute__((visibility("default"))) int MPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh);
__attribute__((visibility("default"))) int MPI_File_close(MPI_File *fh);
__attribute__((visibility("default"))) int MPI_File_delete(char *filename, MPI_Info info);
__attribute__((visibility("default"))) int MPI_File_set_size(MPI_File fh, MPI_Offset size);
__attribute__((visibility("default"))) int MPI_File_preallocate(MPI_File fh, MPI_Offset size);
__attribute__((visibility("default"))) int MPI_File_get_size(MPI_File fh, MPI_Offset *size);
__attribute__((visibility("default"))) int MPI_File_get_group(MPI_File fh, MPI_Group *group);
__attribute__((visibility("default"))) int MPI_File_get_amode(MPI_File fh, int *amode);
__attribute__((visibility("default"))) int MPI_File_set_info(MPI_File fh, MPI_Info info);
__attribute__((visibility("default"))) int MPI_File_get_info(MPI_File fh, MPI_Info *info_used);
__attribute__((visibility("default"))) int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info);
__attribute__((visibility("default"))) int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep);
__attribute__((visibility("default"))) int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_iwrite(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
__attribute__((visibility("default"))) int MPI_File_get_position(MPI_File fh, MPI_Offset *offset);
__attribute__((visibility("default"))) int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);
__attribute__((visibility("default"))) int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_iwrite_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence);
__attribute__((visibility("default"))) int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset);
__attribute__((visibility("default"))) int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_write_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_write_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_write_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_File_write_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent);
__attribute__((visibility("default"))) int MPI_File_set_atomicity(MPI_File fh, int flag);
__attribute__((visibility("default"))) int MPI_File_get_atomicity(MPI_File fh, int *flag);
__attribute__((visibility("default"))) int MPI_File_sync(MPI_File fh);
__attribute__((visibility("default"))) int MPI_Finalize(void);
__attribute__((visibility("default"))) int MPI_Finalized(int *flag);
__attribute__((visibility("default"))) int MPI_Free_mem(void *base);
__attribute__((visibility("default"))) int MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Gatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Get_address(void *location, MPI_Aint *address);
__attribute__((visibility("default"))) int MPI_Get_count(MPI_Status *status, MPI_Datatype datatype, int *count);
__attribute__((visibility("default"))) int MPI_Get_elements(MPI_Status *status, MPI_Datatype datatype, int *count);
__attribute__((visibility("default"))) int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Get_processor_name(char *name, int *resultlen);
__attribute__((visibility("default"))) int MPI_Get_version(int *version, int *subversion);
__attribute__((visibility("default"))) int MPI_Graph_create(MPI_Comm comm_old, int nnodes, int *index, int *edges, int reorder, MPI_Comm *comm_graph);
__attribute__((visibility("default"))) int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int *index, int *edges);
__attribute__((visibility("default"))) int MPI_Graph_map(MPI_Comm comm, int nnodes, int *index, int *edges, int *newrank);
__attribute__((visibility("default"))) int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors);
__attribute__((visibility("default"))) int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int *neighbors);
__attribute__((visibility("default"))) int MPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges);
__attribute__((visibility("default"))) int MPI_Grequest_complete(MPI_Request request);
__attribute__((visibility("default"))) int MPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Group_c2f(MPI_Group group);
__attribute__((visibility("default"))) int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
__attribute__((visibility("default"))) int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__attribute__((visibility("default"))) MPI_Group MPI_Group_f2c(int group);
__attribute__((visibility("default"))) int MPI_Group_free(MPI_Group *group);
__attribute__((visibility("default"))) int MPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Group_rank(MPI_Group group, int *rank);
__attribute__((visibility("default"))) int MPI_Group_size(MPI_Group group, int *size);
__attribute__((visibility("default"))) int MPI_Group_translate_ranks(MPI_Group group1, int n, int *ranks1, MPI_Group group2, int *ranks2);
__attribute__((visibility("default"))) int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int MPI_Ibsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Info_c2f(MPI_Info info);
__attribute__((visibility("default"))) int MPI_Info_create(MPI_Info *info);
__attribute__((visibility("default"))) int MPI_Info_delete(MPI_Info info, char *key);
__attribute__((visibility("default"))) int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
__attribute__((visibility("default"))) MPI_Info MPI_Info_f2c(int info);
__attribute__((visibility("default"))) int MPI_Info_free(MPI_Info *info);
__attribute__((visibility("default"))) int MPI_Info_get(MPI_Info info, char *key, int valuelen, char *value, int *flag);
__attribute__((visibility("default"))) int MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
__attribute__((visibility("default"))) int MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
__attribute__((visibility("default"))) int MPI_Info_get_valuelen(MPI_Info info, char *key, int *valuelen, int *flag);
__attribute__((visibility("default"))) int MPI_Info_set(MPI_Info info, char *key, char *value);
__attribute__((visibility("default"))) int MPI_Init(int *argc, char ***argv);
__attribute__((visibility("default"))) int MPI_Initialized(int *flag);
__attribute__((visibility("default"))) int MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
__attribute__((visibility("default"))) int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
__attribute__((visibility("default"))) int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm);
__attribute__((visibility("default"))) int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Irsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Issend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Is_thread_main(int *flag);
__attribute__((visibility("default"))) int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state);
__attribute__((visibility("default"))) int MPI_Keyval_free(int *keyval);
__attribute__((visibility("default"))) int MPI_Lookup_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int MPI_Op_c2f(MPI_Op op);
__attribute__((visibility("default"))) int MPI_Op_commutative(MPI_Op op, int *commute);
__attribute__((visibility("default"))) int MPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op);
__attribute__((visibility("default"))) int MPI_Open_port(MPI_Info info, char *port_name);
__attribute__((visibility("default"))) MPI_Op MPI_Op_f2c(int op);
__attribute__((visibility("default"))) int MPI_Op_free(MPI_Op *op);
__attribute__((visibility("default"))) int MPI_Pack_external(char *datarep, void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position);
__attribute__((visibility("default"))) int MPI_Pack_external_size(char *datarep, int incount, MPI_Datatype datatype, MPI_Aint *size);
__attribute__((visibility("default"))) int MPI_Pack(void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int MPI_Pcontrol(const int level, ...);
__attribute__((visibility("default"))) int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Publish_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int MPI_Put(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Query_thread(int *provided);
__attribute__((visibility("default"))) int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Reduce_local(void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);
__attribute__((visibility("default"))) int MPI_Reduce_scatter(void *sendbuf, void *recvbuf, int *recvcounts, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Register_datarep(char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
__attribute__((visibility("default"))) int MPI_Request_c2f(MPI_Request request);
__attribute__((visibility("default"))) MPI_Request MPI_Request_f2c(int request);
__attribute__((visibility("default"))) int MPI_Request_free(MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Rsend(void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Rsend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Scan(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Scatterv(void *sendbuf, int *sendcounts, int *displs, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Send_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Sendrecv(void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Ssend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Ssend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Start(MPI_Request *request);
__attribute__((visibility("default"))) int MPI_Startall(int count, MPI_Request *array_of_requests);
__attribute__((visibility("default"))) int MPI_Status_c2f(MPI_Status *c_status, int *f_status);
__attribute__((visibility("default"))) int MPI_Status_f2c(int *f_status, MPI_Status *c_status);
__attribute__((visibility("default"))) int MPI_Status_set_cancelled(MPI_Status *status, int flag);
__attribute__((visibility("default"))) int MPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count);
__attribute__((visibility("default"))) int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
__attribute__((visibility("default"))) int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Test_cancelled(MPI_Status *status, int *flag);
__attribute__((visibility("default"))) int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
__attribute__((visibility("default"))) int MPI_Topo_test(MPI_Comm comm, int *status);
__attribute__((visibility("default"))) int MPI_Type_c2f(MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_Type_commit(MPI_Datatype *type);
__attribute__((visibility("default"))) int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_darray(int size, int rank, int ndims, int gsize_array[], int distrib_array[], int darg_array[], int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_f90_integer(int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state);
__attribute__((visibility("default"))) int MPI_Type_create_indexed_block(int count, int blocklength, int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_struct(int count, int array_of_block_lengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_subarray(int ndims, int size_array[], int subsize_array[], int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_delete_attr(MPI_Datatype type, int type_keyval);
__attribute__((visibility("default"))) int MPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_extent(MPI_Datatype type, MPI_Aint *extent);
__attribute__((visibility("default"))) int MPI_Type_free(MPI_Datatype *type);
__attribute__((visibility("default"))) int MPI_Type_free_keyval(int *type_keyval);
__attribute__((visibility("default"))) MPI_Datatype MPI_Type_f2c(int datatype);
__attribute__((visibility("default"))) int MPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int MPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]);
__attribute__((visibility("default"))) int MPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
__attribute__((visibility("default"))) int MPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent);
__attribute__((visibility("default"))) int MPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen);
__attribute__((visibility("default"))) int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
__attribute__((visibility("default"))) int MPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_indexed(int count, int array_of_blocklengths[], int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_lb(MPI_Datatype type, MPI_Aint *lb);
__attribute__((visibility("default"))) int MPI_Type_match_size(int typeclass, int size, MPI_Datatype *type);
__attribute__((visibility("default"))) int MPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val);
__attribute__((visibility("default"))) int MPI_Type_set_name(MPI_Datatype type, char *type_name);
__attribute__((visibility("default"))) int MPI_Type_size(MPI_Datatype type, int *size);
__attribute__((visibility("default"))) int MPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub);
__attribute__((visibility("default"))) int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int MPI_Unpack(void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);
__attribute__((visibility("default"))) int MPI_Unpublish_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int MPI_Unpack_external(char *datarep, void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype);
__attribute__((visibility("default"))) int MPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses);
__attribute__((visibility("default"))) int MPI_Waitany(int count, MPI_Request *array_of_requests, int *index, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Wait(MPI_Request *request, MPI_Status *status);
__attribute__((visibility("default"))) int MPI_Waitsome(int incount, MPI_Request *array_of_requests, int *outcount, int *array_of_indices, MPI_Status *array_of_statuses);
__attribute__((visibility("default"))) int MPI_Win_c2f(MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_call_errhandler(MPI_Win win, int errorcode);
__attribute__((visibility("default"))) int MPI_Win_complete(MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
__attribute__((visibility("default"))) int MPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state);
__attribute__((visibility("default"))) int MPI_Win_delete_attr(MPI_Win win, int win_keyval);
__attribute__((visibility("default"))) MPI_Win MPI_Win_f2c(int win);
__attribute__((visibility("default"))) int MPI_Win_fence(int assert, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_free(MPI_Win *win);
__attribute__((visibility("default"))) int MPI_Win_free_keyval(int *win_keyval);
__attribute__((visibility("default"))) int MPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int MPI_Win_get_group(MPI_Win win, MPI_Group *group);
__attribute__((visibility("default"))) int MPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen);
__attribute__((visibility("default"))) int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val);
__attribute__((visibility("default"))) int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int MPI_Win_set_name(MPI_Win win, char *win_name);
__attribute__((visibility("default"))) int MPI_Win_start(MPI_Group group, int assert, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_test(MPI_Win win, int *flag);
__attribute__((visibility("default"))) int MPI_Win_unlock(int rank, MPI_Win win);
__attribute__((visibility("default"))) int MPI_Win_wait(MPI_Win win);
__attribute__((visibility("default"))) double MPI_Wtick(void);
__attribute__((visibility("default"))) double MPI_Wtime(void);
__attribute__((visibility("default"))) int PMPI_Abort(MPI_Comm comm, int errorcode);
__attribute__((visibility("default"))) int PMPI_Accumulate(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Add_error_class(int *errorclass);
__attribute__((visibility("default"))) int PMPI_Add_error_code(int errorclass, int *errorcode);
__attribute__((visibility("default"))) int PMPI_Add_error_string(int errorcode, char *string);
__attribute__((visibility("default"))) int PMPI_Address(void *location, MPI_Aint *address);
__attribute__((visibility("default"))) int PMPI_Allgather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Allgatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr);
__attribute__((visibility("default"))) int PMPI_Allreduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Alltoallv(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Alltoallw(void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype *sendtypes, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype *recvtypes, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Attr_delete(MPI_Comm comm, int keyval);
__attribute__((visibility("default"))) int PMPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int PMPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val);
__attribute__((visibility("default"))) int PMPI_Barrier(MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Bsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Bsend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Buffer_attach(void *buffer, int size);
__attribute__((visibility("default"))) int PMPI_Buffer_detach(void *buffer, int *size);
__attribute__((visibility("default"))) int PMPI_Cancel(MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int *coords);
__attribute__((visibility("default"))) int PMPI_Cart_create(MPI_Comm old_comm, int ndims, int *dims, int *periods, int reorder, MPI_Comm *comm_cart);
__attribute__((visibility("default"))) int PMPI_Cart_get(MPI_Comm comm, int maxdims, int *dims, int *periods, int *coords);
__attribute__((visibility("default"))) int PMPI_Cart_map(MPI_Comm comm, int ndims, int *dims, int *periods, int *newrank);
__attribute__((visibility("default"))) int PMPI_Cart_rank(MPI_Comm comm, int *coords, int *rank);
__attribute__((visibility("default"))) int PMPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest);
__attribute__((visibility("default"))) int PMPI_Cart_sub(MPI_Comm comm, int *remain_dims, MPI_Comm *new_comm);
__attribute__((visibility("default"))) int PMPI_Cartdim_get(MPI_Comm comm, int *ndims);
__attribute__((visibility("default"))) int PMPI_Close_port(char *port_name);
__attribute__((visibility("default"))) int PMPI_Comm_accept(char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int PMPI_Comm_c2f(MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Comm_call_errhandler(MPI_Comm comm, int errorcode);
__attribute__((visibility("default"))) int PMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
__attribute__((visibility("default"))) int PMPI_Comm_connect(char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int PMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
__attribute__((visibility("default"))) int PMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int PMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
__attribute__((visibility("default"))) int PMPI_Comm_disconnect(MPI_Comm *comm);
__attribute__((visibility("default"))) int PMPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
__attribute__((visibility("default"))) MPI_Comm PMPI_Comm_f2c(int comm);
__attribute__((visibility("default"))) int PMPI_Comm_free_keyval(int *comm_keyval);
__attribute__((visibility("default"))) int PMPI_Comm_free(MPI_Comm *comm);
__attribute__((visibility("default"))) int PMPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int PMPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler);
__attribute__((visibility("default"))) int PMPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
__attribute__((visibility("default"))) int PMPI_Comm_get_parent(MPI_Comm *parent);
__attribute__((visibility("default"))) int PMPI_Comm_group(MPI_Comm comm, MPI_Group *group);
__attribute__((visibility("default"))) int PMPI_Comm_join(int fd, MPI_Comm *intercomm);
__attribute__((visibility("default"))) int PMPI_Comm_rank(MPI_Comm comm, int *rank);
__attribute__((visibility("default"))) int PMPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group);
__attribute__((visibility("default"))) int PMPI_Comm_remote_size(MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int PMPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
__attribute__((visibility("default"))) int PMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int PMPI_Comm_set_name(MPI_Comm comm, char *comm_name);
__attribute__((visibility("default"))) int PMPI_Comm_size(MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int PMPI_Comm_spawn(char *command, char **argv, int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes);
__attribute__((visibility("default"))) int PMPI_Comm_spawn_multiple(int count, char **array_of_commands, char ***array_of_argv, int *array_of_maxprocs, MPI_Info *array_of_info, int root, MPI_Comm comm, MPI_Comm *intercomm, int *array_of_errcodes);
__attribute__((visibility("default"))) int PMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
__attribute__((visibility("default"))) int PMPI_Comm_test_inter(MPI_Comm comm, int *flag);
__attribute__((visibility("default"))) int PMPI_Dims_create(int nnodes, int ndims, int *dims);
__attribute__((visibility("default"))) int PMPI_Errhandler_c2f(MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int PMPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) MPI_Errhandler PMPI_Errhandler_f2c(int errhandler);
__attribute__((visibility("default"))) int PMPI_Errhandler_free(MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int PMPI_Error_class(int errorcode, int *errorclass);
__attribute__((visibility("default"))) int PMPI_Error_string(int errorcode, char *string, int *resultlen);
__attribute__((visibility("default"))) int PMPI_Exscan(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_File_c2f(MPI_File file);
__attribute__((visibility("default"))) MPI_File PMPI_File_f2c(int file);
__attribute__((visibility("default"))) int PMPI_File_call_errhandler(MPI_File fh, int errorcode);
__attribute__((visibility("default"))) int PMPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int PMPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh);
__attribute__((visibility("default"))) int PMPI_File_close(MPI_File *fh);
__attribute__((visibility("default"))) int PMPI_File_delete(char *filename, MPI_Info info);
__attribute__((visibility("default"))) int PMPI_File_set_size(MPI_File fh, MPI_Offset size);
__attribute__((visibility("default"))) int PMPI_File_preallocate(MPI_File fh, MPI_Offset size);
__attribute__((visibility("default"))) int PMPI_File_get_size(MPI_File fh, MPI_Offset *size);
__attribute__((visibility("default"))) int PMPI_File_get_group(MPI_File fh, MPI_Group *group);
__attribute__((visibility("default"))) int PMPI_File_get_amode(MPI_File fh, int *amode);
__attribute__((visibility("default"))) int PMPI_File_set_info(MPI_File fh, MPI_Info info);
__attribute__((visibility("default"))) int PMPI_File_get_info(MPI_File fh, MPI_Info *info_used);
__attribute__((visibility("default"))) int PMPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info);
__attribute__((visibility("default"))) int PMPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep);
__attribute__((visibility("default"))) int PMPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_iwrite(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
__attribute__((visibility("default"))) int PMPI_File_get_position(MPI_File fh, MPI_Offset *offset);
__attribute__((visibility("default"))) int PMPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);
__attribute__((visibility("default"))) int PMPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_iwrite_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence);
__attribute__((visibility("default"))) int PMPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset);
__attribute__((visibility("default"))) int PMPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_write_at_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_write_all_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_write_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_File_write_ordered_end(MPI_File fh, void *buf, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent);
__attribute__((visibility("default"))) int PMPI_File_set_atomicity(MPI_File fh, int flag);
__attribute__((visibility("default"))) int PMPI_File_get_atomicity(MPI_File fh, int *flag);
__attribute__((visibility("default"))) int PMPI_File_sync(MPI_File fh);
__attribute__((visibility("default"))) int PMPI_Finalize(void);
__attribute__((visibility("default"))) int PMPI_Finalized(int *flag);
__attribute__((visibility("default"))) int PMPI_Free_mem(void *base);
__attribute__((visibility("default"))) int PMPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Gatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Get_address(void *location, MPI_Aint *address);
__attribute__((visibility("default"))) int PMPI_Get_count(MPI_Status *status, MPI_Datatype datatype, int *count);
__attribute__((visibility("default"))) int PMPI_Get_elements(MPI_Status *status, MPI_Datatype datatype, int *count);
__attribute__((visibility("default"))) int PMPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Get_processor_name(char *name, int *resultlen);
__attribute__((visibility("default"))) int PMPI_Get_version(int *version, int *subversion);
__attribute__((visibility("default"))) int PMPI_Graph_create(MPI_Comm comm_old, int nnodes, int *index, int *edges, int reorder, MPI_Comm *comm_graph);
__attribute__((visibility("default"))) int PMPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int *index, int *edges);
__attribute__((visibility("default"))) int PMPI_Graph_map(MPI_Comm comm, int nnodes, int *index, int *edges, int *newrank);
__attribute__((visibility("default"))) int PMPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors);
__attribute__((visibility("default"))) int PMPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int *neighbors);
__attribute__((visibility("default"))) int PMPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges);
__attribute__((visibility("default"))) int PMPI_Grequest_complete(MPI_Request request);
__attribute__((visibility("default"))) int PMPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Group_c2f(MPI_Group group);
__attribute__((visibility("default"))) int PMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
__attribute__((visibility("default"))) int PMPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__attribute__((visibility("default"))) MPI_Group PMPI_Group_f2c(int group);
__attribute__((visibility("default"))) int PMPI_Group_free(MPI_Group *group);
__attribute__((visibility("default"))) int PMPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Group_rank(MPI_Group group, int *rank);
__attribute__((visibility("default"))) int PMPI_Group_size(MPI_Group group, int *size);
__attribute__((visibility("default"))) int PMPI_Group_translate_ranks(MPI_Group group1, int n, int *ranks1, MPI_Group group2, int *ranks2);
__attribute__((visibility("default"))) int PMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__attribute__((visibility("default"))) int PMPI_Ibsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Info_c2f(MPI_Info info);
__attribute__((visibility("default"))) int PMPI_Info_create(MPI_Info *info);
__attribute__((visibility("default"))) int PMPI_Info_delete(MPI_Info info, char *key);
__attribute__((visibility("default"))) int PMPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
__attribute__((visibility("default"))) MPI_Info PMPI_Info_f2c(int info);
__attribute__((visibility("default"))) int PMPI_Info_free(MPI_Info *info);
__attribute__((visibility("default"))) int PMPI_Info_get(MPI_Info info, char *key, int valuelen, char *value, int *flag);
__attribute__((visibility("default"))) int PMPI_Info_get_nkeys(MPI_Info info, int *nkeys);
__attribute__((visibility("default"))) int PMPI_Info_get_nthkey(MPI_Info info, int n, char *key);
__attribute__((visibility("default"))) int PMPI_Info_get_valuelen(MPI_Info info, char *key, int *valuelen, int *flag);
__attribute__((visibility("default"))) int PMPI_Info_set(MPI_Info info, char *key, char *value);
__attribute__((visibility("default"))) int PMPI_Init(int *argc, char ***argv);
__attribute__((visibility("default"))) int PMPI_Initialized(int *flag);
__attribute__((visibility("default"))) int PMPI_Init_thread(int *argc, char ***argv, int required, int *provided);
__attribute__((visibility("default"))) int PMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
__attribute__((visibility("default"))) int PMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm);
__attribute__((visibility("default"))) int PMPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Irsend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Issend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Is_thread_main(int *flag);
__attribute__((visibility("default"))) int PMPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state);
__attribute__((visibility("default"))) int PMPI_Keyval_free(int *keyval);
__attribute__((visibility("default"))) int PMPI_Lookup_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int PMPI_Op_c2f(MPI_Op op);
__attribute__((visibility("default"))) int PMPI_Op_commutative(MPI_Op op, int *commute);
__attribute__((visibility("default"))) int PMPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op);
__attribute__((visibility("default"))) int PMPI_Open_port(MPI_Info info, char *port_name);
__attribute__((visibility("default"))) MPI_Op PMPI_Op_f2c(int op);
__attribute__((visibility("default"))) int PMPI_Op_free(MPI_Op *op);
__attribute__((visibility("default"))) int PMPI_Pack_external(char *datarep, void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position);
__attribute__((visibility("default"))) int PMPI_Pack_external_size(char *datarep, int incount, MPI_Datatype datatype, MPI_Aint *size);
__attribute__((visibility("default"))) int PMPI_Pack(void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
__attribute__((visibility("default"))) int PMPI_Pcontrol(const int level, ...);
__attribute__((visibility("default"))) int PMPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Publish_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int PMPI_Put(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Query_thread(int *provided);
__attribute__((visibility("default"))) int PMPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Reduce_local(void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op);
__attribute__((visibility("default"))) int PMPI_Reduce_scatter(void *sendbuf, void *recvbuf, int *recvcounts, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Register_datarep(char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
__attribute__((visibility("default"))) int PMPI_Request_c2f(MPI_Request request);
__attribute__((visibility("default"))) MPI_Request PMPI_Request_f2c(int request);
__attribute__((visibility("default"))) int PMPI_Request_free(MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Rsend(void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Rsend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Scan(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Scatter(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Scatterv(void *sendbuf, int *sendcounts, int *displs, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Send_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Sendrecv(void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Ssend_init(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Ssend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Start(MPI_Request *request);
__attribute__((visibility("default"))) int PMPI_Startall(int count, MPI_Request *array_of_requests);
__attribute__((visibility("default"))) int PMPI_Status_c2f(MPI_Status *c_status, int *f_status);
__attribute__((visibility("default"))) int PMPI_Status_f2c(int *f_status, MPI_Status *c_status);
__attribute__((visibility("default"))) int PMPI_Status_set_cancelled(MPI_Status *status, int flag);
__attribute__((visibility("default"))) int PMPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count);
__attribute__((visibility("default"))) int PMPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
__attribute__((visibility("default"))) int PMPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Test_cancelled(MPI_Status *status, int *flag);
__attribute__((visibility("default"))) int PMPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
__attribute__((visibility("default"))) int PMPI_Topo_test(MPI_Comm comm, int *status);
__attribute__((visibility("default"))) int PMPI_Type_c2f(MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_Type_commit(MPI_Datatype *type);
__attribute__((visibility("default"))) int PMPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_darray(int size, int rank, int ndims, int gsize_array[], int distrib_array[], int darg_array[], int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_f90_integer(int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state);
__attribute__((visibility("default"))) int PMPI_Type_create_indexed_block(int count, int blocklength, int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_struct(int count, int array_of_block_lengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_subarray(int ndims, int size_array[], int subsize_array[], int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_delete_attr(MPI_Datatype type, int type_keyval);
__attribute__((visibility("default"))) int PMPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_extent(MPI_Datatype type, MPI_Aint *extent);
__attribute__((visibility("default"))) int PMPI_Type_free(MPI_Datatype *type);
__attribute__((visibility("default"))) int PMPI_Type_free_keyval(int *type_keyval);
__attribute__((visibility("default"))) MPI_Datatype PMPI_Type_f2c(int datatype);
__attribute__((visibility("default"))) int PMPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int PMPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]);
__attribute__((visibility("default"))) int PMPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
__attribute__((visibility("default"))) int PMPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent);
__attribute__((visibility("default"))) int PMPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen);
__attribute__((visibility("default"))) int PMPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
__attribute__((visibility("default"))) int PMPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_indexed(int count, int array_of_blocklengths[], int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_lb(MPI_Datatype type, MPI_Aint *lb);
__attribute__((visibility("default"))) int PMPI_Type_match_size(int typeclass, int size, MPI_Datatype *type);
__attribute__((visibility("default"))) int PMPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val);
__attribute__((visibility("default"))) int PMPI_Type_set_name(MPI_Datatype type, char *type_name);
__attribute__((visibility("default"))) int PMPI_Type_size(MPI_Datatype type, int *size);
__attribute__((visibility("default"))) int PMPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub);
__attribute__((visibility("default"))) int PMPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
__attribute__((visibility("default"))) int PMPI_Unpack(void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);
__attribute__((visibility("default"))) int PMPI_Unpublish_name(char *service_name, MPI_Info info, char *port_name);
__attribute__((visibility("default"))) int PMPI_Unpack_external(char *datarep, void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype);
__attribute__((visibility("default"))) int PMPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses);
__attribute__((visibility("default"))) int PMPI_Waitany(int count, MPI_Request *array_of_requests, int *index, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Wait(MPI_Request *request, MPI_Status *status);
__attribute__((visibility("default"))) int PMPI_Waitsome(int incount, MPI_Request *array_of_requests, int *outcount, int *array_of_indices, MPI_Status *array_of_statuses);
__attribute__((visibility("default"))) int PMPI_Win_c2f(MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_call_errhandler(MPI_Win win, int errorcode);
__attribute__((visibility("default"))) int PMPI_Win_complete(MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
__attribute__((visibility("default"))) int PMPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state);
__attribute__((visibility("default"))) int PMPI_Win_delete_attr(MPI_Win win, int win_keyval);
__attribute__((visibility("default"))) MPI_Win PMPI_Win_f2c(int win);
__attribute__((visibility("default"))) int PMPI_Win_fence(int assert, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_free(MPI_Win *win);
__attribute__((visibility("default"))) int PMPI_Win_free_keyval(int *win_keyval);
__attribute__((visibility("default"))) int PMPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag);
__attribute__((visibility("default"))) int PMPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler);
__attribute__((visibility("default"))) int PMPI_Win_get_group(MPI_Win win, MPI_Group *group);
__attribute__((visibility("default"))) int PMPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen);
__attribute__((visibility("default"))) int PMPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_post(MPI_Group group, int assert, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val);
__attribute__((visibility("default"))) int PMPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler);
__attribute__((visibility("default"))) int PMPI_Win_set_name(MPI_Win win, char *win_name);
__attribute__((visibility("default"))) int PMPI_Win_start(MPI_Group group, int assert, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_test(MPI_Win win, int *flag);
__attribute__((visibility("default"))) int PMPI_Win_unlock(int rank, MPI_Win win);
__attribute__((visibility("default"))) int PMPI_Win_wait(MPI_Win win);
__attribute__((visibility("default"))) double PMPI_Wtick(void);
__attribute__((visibility("default"))) double PMPI_Wtime(void);
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
__extension__
typedef signed long long int __int64_t;
__extension__
typedef unsigned long long int __uint64_t;
__extension__
typedef long long int __quad_t;
__extension__
typedef unsigned long long int __u_quad_t;
__extension__
typedef __u_quad_t __dev_t;
__extension__
typedef unsigned int __uid_t;
__extension__
typedef unsigned int __gid_t;
__extension__
typedef unsigned long int __ino_t;
__extension__
typedef __u_quad_t __ino64_t;
__extension__
typedef unsigned int __mode_t;
__extension__
typedef unsigned int __nlink_t;
__extension__
typedef long int __off_t;
__extension__
typedef __quad_t __off64_t;
__extension__
typedef int __pid_t;
__extension__
typedef struct 
{
        int __val[2];
} __fsid_t;
__extension__
typedef long int __clock_t;
__extension__
typedef unsigned long int __rlim_t;
__extension__
typedef __u_quad_t __rlim64_t;
__extension__
typedef unsigned int __id_t;
__extension__
typedef long int __time_t;
__extension__
typedef unsigned int __useconds_t;
__extension__
typedef long int __suseconds_t;
__extension__
typedef int __daddr_t;
__extension__
typedef int __key_t;
__extension__
typedef int __clockid_t;
__extension__
typedef void *__timer_t;
__extension__
typedef long int __blksize_t;
__extension__
typedef long int __blkcnt_t;
__extension__
typedef __quad_t __blkcnt64_t;
__extension__
typedef unsigned long int __fsblkcnt_t;
__extension__
typedef __u_quad_t __fsblkcnt64_t;
__extension__
typedef unsigned long int __fsfilcnt_t;
__extension__
typedef __u_quad_t __fsfilcnt64_t;
__extension__
typedef int __fsword_t;
__extension__
typedef int __ssize_t;
__extension__
typedef long int __syscall_slong_t;
__extension__
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
__extension__
typedef int __intptr_t;
__extension__
typedef unsigned int __socklen_t;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef struct _IO_FILE __FILE;
typedef struct 
{
        int __count;
        union 
        {
                unsigned int __wch;
                char __wchb[4];
        } __value;
} __mbstate_t;
typedef struct 
{
        __off_t __pos;
        __mbstate_t __state;
} _G_fpos_t;
typedef struct 
{
        __off64_t __pos;
        __mbstate_t __state;
} _G_fpos64_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t;
struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker
{
        struct _IO_marker *_next;
        struct _IO_FILE *_sbuf;
        int _pos;
};
enum __codecvt_result
{
    __codecvt_ok, 
    __codecvt_partial, 
    __codecvt_error, 
    __codecvt_noconv
};
struct _IO_FILE
{
        int _flags;
        char *_IO_read_ptr;
        char *_IO_read_end;
        char *_IO_read_base;
        char *_IO_write_base;
        char *_IO_write_ptr;
        char *_IO_write_end;
        char *_IO_buf_base;
        char *_IO_buf_end;
        char *_IO_save_base;
        char *_IO_backup_base;
        char *_IO_save_end;
        struct _IO_marker *_markers;
        struct _IO_FILE *_chain;
        int _fileno;
        int _flags2;
        __off_t _old_offset;
        unsigned short _cur_column;
        signed char _vtable_offset;
        char _shortbuf[1];
        _IO_lock_t *_lock;
        __off64_t _offset;
        void *__pad1;
        void *__pad2;
        void *__pad3;
        void *__pad4;
        size_t __pad5;
        int _mode;
        char _unused2[15 * sizeof(int) - 4 * sizeof(void *) - sizeof(size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn(void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn(void *__cookie, const char *__buf, size_t __n);
typedef int __io_seek_fn(void *__cookie, __off64_t *__pos, int __w);
typedef int __io_close_fn(void *__cookie);
extern int __underflow(_IO_FILE *);
extern int __uflow(_IO_FILE *);
extern int __overflow(_IO_FILE *, int);
extern int _IO_getc(_IO_FILE *__fp);
extern int _IO_putc(int __c, _IO_FILE *__fp);
extern int _IO_feof(_IO_FILE *__fp) __attribute__((__nothrow__));
extern int _IO_ferror(_IO_FILE *__fp) __attribute__((__nothrow__));
extern int _IO_peekc_locked(_IO_FILE *__fp);
extern void _IO_flockfile(_IO_FILE *) __attribute__((__nothrow__));
extern void _IO_funlockfile(_IO_FILE *) __attribute__((__nothrow__));
extern int _IO_ftrylockfile(_IO_FILE *) __attribute__((__nothrow__));
extern int _IO_vfscanf(_IO_FILE *__restrict , const char *__restrict , __gnuc_va_list, int *__restrict );
extern int _IO_vfprintf(_IO_FILE *__restrict , const char *__restrict , __gnuc_va_list);
extern __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn(_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area(_IO_FILE *) __attribute__((__nothrow__));
typedef _G_fpos_t fpos_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;
extern int remove(const char *__filename) __attribute__((__nothrow__));
extern int rename(const char *__old, const char *__new) __attribute__((__nothrow__));
extern FILE *tmpfile(void);
extern char *tmpnam(char *__s) __attribute__((__nothrow__));
extern int fclose(FILE *__stream);
extern int fflush(FILE *__stream);
extern FILE *fopen(const char *__restrict __filename, const char *__restrict __modes);
extern FILE *freopen(const char *__restrict __filename, const char *__restrict __modes, FILE *__restrict __stream);
extern void setbuf(FILE *__restrict __stream, char *__restrict __buf) __attribute__((__nothrow__));
extern int setvbuf(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __n) __attribute__((__nothrow__));
extern int fprintf(FILE *__restrict __stream, const char *__restrict __format, ...);
extern int printf(const char *__restrict __format, ...);
extern int sprintf(char *__restrict __s, const char *__restrict __format, ...) __attribute__((__nothrow__));
extern int vfprintf(FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg);
extern int vprintf(const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf(char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__));
extern int snprintf(char *__restrict __s, size_t __maxlen, const char *__restrict __format, ...) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 4)));
extern int vsnprintf(char *__restrict __s, size_t __maxlen, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 0)));
extern int fscanf(FILE *__restrict __stream, const char *__restrict __format, ...);
extern int scanf(const char *__restrict __format, ...);
extern int sscanf(const char *__restrict __s, const char *__restrict __format, ...) __attribute__((__nothrow__));
extern int fscanf(FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("""__isoc99_fscanf");
extern int scanf(const char *__restrict __format, ...) __asm__ ("""__isoc99_scanf");
extern int sscanf(const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("""__isoc99_sscanf") __attribute__((__nothrow__));
extern int vfscanf(FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__format__(__scanf__, 2, 0)));
extern int vscanf(const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__format__(__scanf__, 1, 0)));
extern int vsscanf(const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__)) __attribute__((__format__(__scanf__, 2, 0)));
extern int vfscanf(FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("""__isoc99_vfscanf") __attribute__((__format__(__scanf__, 2, 0)));
extern int vscanf(const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("""__isoc99_vscanf") __attribute__((__format__(__scanf__, 1, 0)));
extern int vsscanf(const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("""__isoc99_vsscanf") __attribute__((__nothrow__)) __attribute__((__format__(__scanf__, 2, 0)));
extern int fgetc(FILE *__stream);
extern int getc(FILE *__stream);
extern int getchar(void);
extern int fputc(int __c, FILE *__stream);
extern int putc(int __c, FILE *__stream);
extern int putchar(int __c);
extern char *fgets(char *__restrict __s, int __n, FILE *__restrict __stream);
extern char *gets(char *__s) __attribute__((__deprecated__));
extern int fputs(const char *__restrict __s, FILE *__restrict __stream);
extern int puts(const char *__s);
extern int ungetc(int __c, FILE *__stream);
extern size_t fread(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern size_t fwrite(const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __s);
extern int fseek(FILE *__stream, long int __off, int __whence);
extern long int ftell(FILE *__stream);
extern void rewind(FILE *__stream);
extern int fgetpos(FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos(FILE *__stream, const fpos_t *__pos);
extern void clearerr(FILE *__stream) __attribute__((__nothrow__));
extern int feof(FILE *__stream) __attribute__((__nothrow__));
extern int ferror(FILE *__stream) __attribute__((__nothrow__));
extern void perror(const char *__s);
typedef struct 
{
        int quot;
        int rem;
} div_t;
typedef struct 
{
        long int quot;
        long int rem;
} ldiv_t;
__extension__
typedef struct 
{
        long long int quot;
        long long int rem;
} lldiv_t;
extern size_t __ctype_get_mb_cur_max(void) __attribute__((__nothrow__));
extern double atof(const char *__nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern int atoi(const char *__nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern long int atol(const char *__nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int atoll(const char *__nptr) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern double strtod(const char *__restrict __nptr, char **__restrict __endptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern float strtof(const char *__restrict __nptr, char **__restrict __endptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long double strtold(const char *__restrict __nptr, char **__restrict __endptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int strtol(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern unsigned long int strtoul(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern long long int strtoll(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
__extension__
extern unsigned long long int strtoull(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int rand(void) __attribute__((__nothrow__));
extern void srand(unsigned int __seed) __attribute__((__nothrow__));
extern void *malloc(size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern void *calloc(size_t __nmemb, size_t __size) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern void *realloc(void *__ptr, size_t __size) __attribute__((__nothrow__)) __attribute__((__warn_unused_result__));
extern void free(void *__ptr) __attribute__((__nothrow__));
extern void abort(void) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern int atexit(void (*__func)(void)) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void exit(int __status) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern void _Exit(int __status) __attribute__((__nothrow__)) __attribute__((__noreturn__));
extern char *getenv(const char *__name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int system(const char *__command);
typedef int (*__compar_fn_t)(const void *, const void *);
extern void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__((__nonnull__(1, 2, 5)));
extern void qsort(void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar) __attribute__((__nonnull__(1, 4)));
extern int abs(int __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long int labs(long int __x) __attribute__((__nothrow__)) __attribute__((__const__));
__extension__
extern long long int llabs(long long int __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern div_t div(int __numer, int __denom) __attribute__((__nothrow__)) __attribute__((__const__));
extern ldiv_t ldiv(long int __numer, long int __denom) __attribute__((__nothrow__)) __attribute__((__const__));
__extension__
extern lldiv_t lldiv(long long int __numer, long long int __denom) __attribute__((__nothrow__)) __attribute__((__const__));
extern int mblen(const char *__s, size_t __n) __attribute__((__nothrow__));
extern int mbtowc(wchar_t *__restrict __pwc, const char *__restrict __s, size_t __n) __attribute__((__nothrow__));
extern int wctomb(char *__s, wchar_t __wchar) __attribute__((__nothrow__));
extern size_t mbstowcs(wchar_t *__restrict __pwcs, const char *__restrict __s, size_t __n) __attribute__((__nothrow__));
extern size_t wcstombs(char *__restrict __s, const wchar_t *__restrict __pwcs, size_t __n) __attribute__((__nothrow__));
typedef long double float_t;
typedef long double double_t;
extern double acos(double __x) __attribute__((__nothrow__));
extern double __acos(double __x) __attribute__((__nothrow__));
extern double asin(double __x) __attribute__((__nothrow__));
extern double __asin(double __x) __attribute__((__nothrow__));
extern double atan(double __x) __attribute__((__nothrow__));
extern double __atan(double __x) __attribute__((__nothrow__));
extern double atan2(double __y, double __x) __attribute__((__nothrow__));
extern double __atan2(double __y, double __x) __attribute__((__nothrow__));
extern double cos(double __x) __attribute__((__nothrow__));
extern double __cos(double __x) __attribute__((__nothrow__));
extern double sin(double __x) __attribute__((__nothrow__));
extern double __sin(double __x) __attribute__((__nothrow__));
extern double tan(double __x) __attribute__((__nothrow__));
extern double __tan(double __x) __attribute__((__nothrow__));
extern double cosh(double __x) __attribute__((__nothrow__));
extern double __cosh(double __x) __attribute__((__nothrow__));
extern double sinh(double __x) __attribute__((__nothrow__));
extern double __sinh(double __x) __attribute__((__nothrow__));
extern double tanh(double __x) __attribute__((__nothrow__));
extern double __tanh(double __x) __attribute__((__nothrow__));
extern double acosh(double __x) __attribute__((__nothrow__));
extern double __acosh(double __x) __attribute__((__nothrow__));
extern double asinh(double __x) __attribute__((__nothrow__));
extern double __asinh(double __x) __attribute__((__nothrow__));
extern double atanh(double __x) __attribute__((__nothrow__));
extern double __atanh(double __x) __attribute__((__nothrow__));
extern double exp(double __x) __attribute__((__nothrow__));
extern double __exp(double __x) __attribute__((__nothrow__));
extern double frexp(double __x, int *__exponent) __attribute__((__nothrow__));
extern double __frexp(double __x, int *__exponent) __attribute__((__nothrow__));
extern double ldexp(double __x, int __exponent) __attribute__((__nothrow__));
extern double __ldexp(double __x, int __exponent) __attribute__((__nothrow__));
extern double log(double __x) __attribute__((__nothrow__));
extern double __log(double __x) __attribute__((__nothrow__));
extern double log10(double __x) __attribute__((__nothrow__));
extern double __log10(double __x) __attribute__((__nothrow__));
extern double modf(double __x, double *__iptr) __attribute__((__nothrow__));
extern double __modf(double __x, double *__iptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern double expm1(double __x) __attribute__((__nothrow__));
extern double __expm1(double __x) __attribute__((__nothrow__));
extern double log1p(double __x) __attribute__((__nothrow__));
extern double __log1p(double __x) __attribute__((__nothrow__));
extern double logb(double __x) __attribute__((__nothrow__));
extern double __logb(double __x) __attribute__((__nothrow__));
extern double exp2(double __x) __attribute__((__nothrow__));
extern double __exp2(double __x) __attribute__((__nothrow__));
extern double log2(double __x) __attribute__((__nothrow__));
extern double __log2(double __x) __attribute__((__nothrow__));
extern double pow(double __x, double __y) __attribute__((__nothrow__));
extern double __pow(double __x, double __y) __attribute__((__nothrow__));
extern double sqrt(double __x) __attribute__((__nothrow__));
extern double __sqrt(double __x) __attribute__((__nothrow__));
extern double hypot(double __x, double __y) __attribute__((__nothrow__));
extern double __hypot(double __x, double __y) __attribute__((__nothrow__));
extern double cbrt(double __x) __attribute__((__nothrow__));
extern double __cbrt(double __x) __attribute__((__nothrow__));
extern double ceil(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __ceil(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fabs(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __fabs(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double floor(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __floor(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fmod(double __x, double __y) __attribute__((__nothrow__));
extern double __fmod(double __x, double __y) __attribute__((__nothrow__));
extern int __isinf(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finite(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double nan(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __nan(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnan(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double erf(double) __attribute__((__nothrow__));
extern double __erf(double) __attribute__((__nothrow__));
extern double erfc(double) __attribute__((__nothrow__));
extern double __erfc(double) __attribute__((__nothrow__));
extern double lgamma(double) __attribute__((__nothrow__));
extern double __lgamma(double) __attribute__((__nothrow__));
extern double tgamma(double) __attribute__((__nothrow__));
extern double __tgamma(double) __attribute__((__nothrow__));
extern double rint(double __x) __attribute__((__nothrow__));
extern double __rint(double __x) __attribute__((__nothrow__));
extern double nextafter(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __nextafter(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double nexttoward(double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __nexttoward(double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double remainder(double __x, double __y) __attribute__((__nothrow__));
extern double __remainder(double __x, double __y) __attribute__((__nothrow__));
extern double scalbn(double __x, int __n) __attribute__((__nothrow__));
extern double __scalbn(double __x, int __n) __attribute__((__nothrow__));
extern int ilogb(double __x) __attribute__((__nothrow__));
extern int __ilogb(double __x) __attribute__((__nothrow__));
extern double scalbln(double __x, long int __n) __attribute__((__nothrow__));
extern double __scalbln(double __x, long int __n) __attribute__((__nothrow__));
extern double nearbyint(double __x) __attribute__((__nothrow__));
extern double __nearbyint(double __x) __attribute__((__nothrow__));
extern double round(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __round(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double trunc(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __trunc(double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern double remquo(double __x, double __y, int *__quo) __attribute__((__nothrow__));
extern double __remquo(double __x, double __y, int *__quo) __attribute__((__nothrow__));
extern long int lrint(double __x) __attribute__((__nothrow__));
extern long int __lrint(double __x) __attribute__((__nothrow__));
__extension__
extern long long int llrint(double __x) __attribute__((__nothrow__));
extern long long int __llrint(double __x) __attribute__((__nothrow__));
extern long int lround(double __x) __attribute__((__nothrow__));
extern long int __lround(double __x) __attribute__((__nothrow__));
__extension__
extern long long int llround(double __x) __attribute__((__nothrow__));
extern long long int __llround(double __x) __attribute__((__nothrow__));
extern double fdim(double __x, double __y) __attribute__((__nothrow__));
extern double __fdim(double __x, double __y) __attribute__((__nothrow__));
extern double fmax(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __fmax(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fmin(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __fmin(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __fpclassify(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __signbit(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double fma(double __x, double __y, double __z) __attribute__((__nothrow__));
extern double __fma(double __x, double __y, double __z) __attribute__((__nothrow__));
extern float acosf(float __x) __attribute__((__nothrow__));
extern float __acosf(float __x) __attribute__((__nothrow__));
extern float asinf(float __x) __attribute__((__nothrow__));
extern float __asinf(float __x) __attribute__((__nothrow__));
extern float atanf(float __x) __attribute__((__nothrow__));
extern float __atanf(float __x) __attribute__((__nothrow__));
extern float atan2f(float __y, float __x) __attribute__((__nothrow__));
extern float __atan2f(float __y, float __x) __attribute__((__nothrow__));
extern float cosf(float __x) __attribute__((__nothrow__));
extern float __cosf(float __x) __attribute__((__nothrow__));
extern float sinf(float __x) __attribute__((__nothrow__));
extern float __sinf(float __x) __attribute__((__nothrow__));
extern float tanf(float __x) __attribute__((__nothrow__));
extern float __tanf(float __x) __attribute__((__nothrow__));
extern float coshf(float __x) __attribute__((__nothrow__));
extern float __coshf(float __x) __attribute__((__nothrow__));
extern float sinhf(float __x) __attribute__((__nothrow__));
extern float __sinhf(float __x) __attribute__((__nothrow__));
extern float tanhf(float __x) __attribute__((__nothrow__));
extern float __tanhf(float __x) __attribute__((__nothrow__));
extern float acoshf(float __x) __attribute__((__nothrow__));
extern float __acoshf(float __x) __attribute__((__nothrow__));
extern float asinhf(float __x) __attribute__((__nothrow__));
extern float __asinhf(float __x) __attribute__((__nothrow__));
extern float atanhf(float __x) __attribute__((__nothrow__));
extern float __atanhf(float __x) __attribute__((__nothrow__));
extern float expf(float __x) __attribute__((__nothrow__));
extern float __expf(float __x) __attribute__((__nothrow__));
extern float frexpf(float __x, int *__exponent) __attribute__((__nothrow__));
extern float __frexpf(float __x, int *__exponent) __attribute__((__nothrow__));
extern float ldexpf(float __x, int __exponent) __attribute__((__nothrow__));
extern float __ldexpf(float __x, int __exponent) __attribute__((__nothrow__));
extern float logf(float __x) __attribute__((__nothrow__));
extern float __logf(float __x) __attribute__((__nothrow__));
extern float log10f(float __x) __attribute__((__nothrow__));
extern float __log10f(float __x) __attribute__((__nothrow__));
extern float modff(float __x, float *__iptr) __attribute__((__nothrow__));
extern float __modff(float __x, float *__iptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern float expm1f(float __x) __attribute__((__nothrow__));
extern float __expm1f(float __x) __attribute__((__nothrow__));
extern float log1pf(float __x) __attribute__((__nothrow__));
extern float __log1pf(float __x) __attribute__((__nothrow__));
extern float logbf(float __x) __attribute__((__nothrow__));
extern float __logbf(float __x) __attribute__((__nothrow__));
extern float exp2f(float __x) __attribute__((__nothrow__));
extern float __exp2f(float __x) __attribute__((__nothrow__));
extern float log2f(float __x) __attribute__((__nothrow__));
extern float __log2f(float __x) __attribute__((__nothrow__));
extern float powf(float __x, float __y) __attribute__((__nothrow__));
extern float __powf(float __x, float __y) __attribute__((__nothrow__));
extern float sqrtf(float __x) __attribute__((__nothrow__));
extern float __sqrtf(float __x) __attribute__((__nothrow__));
extern float hypotf(float __x, float __y) __attribute__((__nothrow__));
extern float __hypotf(float __x, float __y) __attribute__((__nothrow__));
extern float cbrtf(float __x) __attribute__((__nothrow__));
extern float __cbrtf(float __x) __attribute__((__nothrow__));
extern float ceilf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __ceilf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fabsf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __fabsf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float floorf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __floorf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fmodf(float __x, float __y) __attribute__((__nothrow__));
extern float __fmodf(float __x, float __y) __attribute__((__nothrow__));
extern int __isinff(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finitef(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float nanf(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __nanf(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float erff(float) __attribute__((__nothrow__));
extern float __erff(float) __attribute__((__nothrow__));
extern float erfcf(float) __attribute__((__nothrow__));
extern float __erfcf(float) __attribute__((__nothrow__));
extern float lgammaf(float) __attribute__((__nothrow__));
extern float __lgammaf(float) __attribute__((__nothrow__));
extern float tgammaf(float) __attribute__((__nothrow__));
extern float __tgammaf(float) __attribute__((__nothrow__));
extern float rintf(float __x) __attribute__((__nothrow__));
extern float __rintf(float __x) __attribute__((__nothrow__));
extern float nextafterf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __nextafterf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float nexttowardf(float __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __nexttowardf(float __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float remainderf(float __x, float __y) __attribute__((__nothrow__));
extern float __remainderf(float __x, float __y) __attribute__((__nothrow__));
extern float scalbnf(float __x, int __n) __attribute__((__nothrow__));
extern float __scalbnf(float __x, int __n) __attribute__((__nothrow__));
extern int ilogbf(float __x) __attribute__((__nothrow__));
extern int __ilogbf(float __x) __attribute__((__nothrow__));
extern float scalblnf(float __x, long int __n) __attribute__((__nothrow__));
extern float __scalblnf(float __x, long int __n) __attribute__((__nothrow__));
extern float nearbyintf(float __x) __attribute__((__nothrow__));
extern float __nearbyintf(float __x) __attribute__((__nothrow__));
extern float roundf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __roundf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float truncf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __truncf(float __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern float remquof(float __x, float __y, int *__quo) __attribute__((__nothrow__));
extern float __remquof(float __x, float __y, int *__quo) __attribute__((__nothrow__));
extern long int lrintf(float __x) __attribute__((__nothrow__));
extern long int __lrintf(float __x) __attribute__((__nothrow__));
__extension__
extern long long int llrintf(float __x) __attribute__((__nothrow__));
extern long long int __llrintf(float __x) __attribute__((__nothrow__));
extern long int lroundf(float __x) __attribute__((__nothrow__));
extern long int __lroundf(float __x) __attribute__((__nothrow__));
__extension__
extern long long int llroundf(float __x) __attribute__((__nothrow__));
extern long long int __llroundf(float __x) __attribute__((__nothrow__));
extern float fdimf(float __x, float __y) __attribute__((__nothrow__));
extern float __fdimf(float __x, float __y) __attribute__((__nothrow__));
extern float fmaxf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __fmaxf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fminf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __fminf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __fpclassifyf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __signbitf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float fmaf(float __x, float __y, float __z) __attribute__((__nothrow__));
extern float __fmaf(float __x, float __y, float __z) __attribute__((__nothrow__));
extern long double acosl(long double __x) __attribute__((__nothrow__));
extern long double __acosl(long double __x) __attribute__((__nothrow__));
extern long double asinl(long double __x) __attribute__((__nothrow__));
extern long double __asinl(long double __x) __attribute__((__nothrow__));
extern long double atanl(long double __x) __attribute__((__nothrow__));
extern long double __atanl(long double __x) __attribute__((__nothrow__));
extern long double atan2l(long double __y, long double __x) __attribute__((__nothrow__));
extern long double __atan2l(long double __y, long double __x) __attribute__((__nothrow__));
extern long double cosl(long double __x) __attribute__((__nothrow__));
extern long double __cosl(long double __x) __attribute__((__nothrow__));
extern long double sinl(long double __x) __attribute__((__nothrow__));
extern long double __sinl(long double __x) __attribute__((__nothrow__));
extern long double tanl(long double __x) __attribute__((__nothrow__));
extern long double __tanl(long double __x) __attribute__((__nothrow__));
extern long double coshl(long double __x) __attribute__((__nothrow__));
extern long double __coshl(long double __x) __attribute__((__nothrow__));
extern long double sinhl(long double __x) __attribute__((__nothrow__));
extern long double __sinhl(long double __x) __attribute__((__nothrow__));
extern long double tanhl(long double __x) __attribute__((__nothrow__));
extern long double __tanhl(long double __x) __attribute__((__nothrow__));
extern long double acoshl(long double __x) __attribute__((__nothrow__));
extern long double __acoshl(long double __x) __attribute__((__nothrow__));
extern long double asinhl(long double __x) __attribute__((__nothrow__));
extern long double __asinhl(long double __x) __attribute__((__nothrow__));
extern long double atanhl(long double __x) __attribute__((__nothrow__));
extern long double __atanhl(long double __x) __attribute__((__nothrow__));
extern long double expl(long double __x) __attribute__((__nothrow__));
extern long double __expl(long double __x) __attribute__((__nothrow__));
extern long double frexpl(long double __x, int *__exponent) __attribute__((__nothrow__));
extern long double __frexpl(long double __x, int *__exponent) __attribute__((__nothrow__));
extern long double ldexpl(long double __x, int __exponent) __attribute__((__nothrow__));
extern long double __ldexpl(long double __x, int __exponent) __attribute__((__nothrow__));
extern long double logl(long double __x) __attribute__((__nothrow__));
extern long double __logl(long double __x) __attribute__((__nothrow__));
extern long double log10l(long double __x) __attribute__((__nothrow__));
extern long double __log10l(long double __x) __attribute__((__nothrow__));
extern long double modfl(long double __x, long double *__iptr) __attribute__((__nothrow__));
extern long double __modfl(long double __x, long double *__iptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern long double expm1l(long double __x) __attribute__((__nothrow__));
extern long double __expm1l(long double __x) __attribute__((__nothrow__));
extern long double log1pl(long double __x) __attribute__((__nothrow__));
extern long double __log1pl(long double __x) __attribute__((__nothrow__));
extern long double logbl(long double __x) __attribute__((__nothrow__));
extern long double __logbl(long double __x) __attribute__((__nothrow__));
extern long double exp2l(long double __x) __attribute__((__nothrow__));
extern long double __exp2l(long double __x) __attribute__((__nothrow__));
extern long double log2l(long double __x) __attribute__((__nothrow__));
extern long double __log2l(long double __x) __attribute__((__nothrow__));
extern long double powl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __powl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double sqrtl(long double __x) __attribute__((__nothrow__));
extern long double __sqrtl(long double __x) __attribute__((__nothrow__));
extern long double hypotl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __hypotl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double cbrtl(long double __x) __attribute__((__nothrow__));
extern long double __cbrtl(long double __x) __attribute__((__nothrow__));
extern long double ceill(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __ceill(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fabsl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __fabsl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double floorl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __floorl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fmodl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __fmodl(long double __x, long double __y) __attribute__((__nothrow__));
extern int __isinfl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __finitel(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double nanl(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __nanl(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double erfl(long double) __attribute__((__nothrow__));
extern long double __erfl(long double) __attribute__((__nothrow__));
extern long double erfcl(long double) __attribute__((__nothrow__));
extern long double __erfcl(long double) __attribute__((__nothrow__));
extern long double lgammal(long double) __attribute__((__nothrow__));
extern long double __lgammal(long double) __attribute__((__nothrow__));
extern long double tgammal(long double) __attribute__((__nothrow__));
extern long double __tgammal(long double) __attribute__((__nothrow__));
extern long double rintl(long double __x) __attribute__((__nothrow__));
extern long double __rintl(long double __x) __attribute__((__nothrow__));
extern long double nextafterl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __nextafterl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double nexttowardl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __nexttowardl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double remainderl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __remainderl(long double __x, long double __y) __attribute__((__nothrow__));
extern long double scalbnl(long double __x, int __n) __attribute__((__nothrow__));
extern long double __scalbnl(long double __x, int __n) __attribute__((__nothrow__));
extern int ilogbl(long double __x) __attribute__((__nothrow__));
extern int __ilogbl(long double __x) __attribute__((__nothrow__));
extern long double scalblnl(long double __x, long int __n) __attribute__((__nothrow__));
extern long double __scalblnl(long double __x, long int __n) __attribute__((__nothrow__));
extern long double nearbyintl(long double __x) __attribute__((__nothrow__));
extern long double __nearbyintl(long double __x) __attribute__((__nothrow__));
extern long double roundl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __roundl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double truncl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __truncl(long double __x) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double remquol(long double __x, long double __y, int *__quo) __attribute__((__nothrow__));
extern long double __remquol(long double __x, long double __y, int *__quo) __attribute__((__nothrow__));
extern long int lrintl(long double __x) __attribute__((__nothrow__));
extern long int __lrintl(long double __x) __attribute__((__nothrow__));
__extension__
extern long long int llrintl(long double __x) __attribute__((__nothrow__));
extern long long int __llrintl(long double __x) __attribute__((__nothrow__));
extern long int lroundl(long double __x) __attribute__((__nothrow__));
extern long int __lroundl(long double __x) __attribute__((__nothrow__));
__extension__
extern long long int llroundl(long double __x) __attribute__((__nothrow__));
extern long long int __llroundl(long double __x) __attribute__((__nothrow__));
extern long double fdiml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __fdiml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double fmaxl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __fmaxl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fminl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __fminl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __fpclassifyl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __signbitl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double fmal(long double __x, long double __y, long double __z) __attribute__((__nothrow__));
extern long double __fmal(long double __x, long double __y, long double __z) __attribute__((__nothrow__));
enum 
{
    FP_NAN = 0, 
    FP_INFINITE = 1, 
    FP_ZERO = 2, 
    FP_SUBNORMAL = 3, 
    FP_NORMAL = 4
};
typedef int boolean;
typedef struct 
{
        double real;
        double imag;
} dcomplex;
extern double randlc(double *, double);
extern void vranlc(int, double *, double, double *);
extern void timer_clear(int);
extern void timer_start(int);
extern void timer_stop(int);
extern double timer_read(int);
extern void c_print_results(char *name, char class, int n1, int n2, int n3, int niter, int nthreads, double t, double mops, char *optype, int passed_verification, char *npbversion, char *compiletime, char *cc, char *clink, char *c_lib, char *c_inc, char *cflags, char *clinkflags, char *rand);
static int grid_points[3];
static double tx1, tx2, tx3, ty1, ty2, ty3, tz1, tz2, tz3;
static double dx1, dx2, dx3, dx4, dx5;
static double dy1, dy2, dy3, dy4, dy5;
static double dz1, dz2, dz3, dz4, dz5;
static double dssp, dt;
static double ce[5][13];
static double dxmax, dymax, dzmax;
static double xxcon1, xxcon2, xxcon3, xxcon4, xxcon5;
static double dx1tx1, dx2tx1, dx3tx1, dx4tx1, dx5tx1;
static double yycon1, yycon2, yycon3, yycon4, yycon5;
static double dy1ty1, dy2ty1, dy3ty1, dy4ty1, dy5ty1;
static double zzcon1, zzcon2, zzcon3, zzcon4, zzcon5;
static double dz1tz1, dz2tz1, dz3tz1, dz4tz1, dz5tz1;
static double dnxm1, dnym1, dnzm1, c1c2, c1c5, c3c4, c1345;
static double conz1, c1, c2, c3, c4, c5, c4dssp, c5dssp, dtdssp;
static double dttx1, dttx2, dtty1, dtty2, dttz1, dttz2;
static double c2dttx1, c2dtty1, c2dttz1, comz1, comz4, comz5, comz6;
static double c3c4tx3, c3c4ty3, c3c4tz3, c2iv, con43, con16;
static double us[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double vs[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double ws[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double qs[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double rho_i[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double square[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1];
static double forcing[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1][5 + 1];
static double u[(12 + 1) / 2 * 2 + 1][(12 + 1) / 2 * 2 + 1][(12 + 1) / 2 * 2 + 1][5];
static double rhs[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1][5];
static double lhs[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 / 2 * 2 + 1][3][5][5];
static double cuf[12];
static double q[12];
static double ue[12][5];
static double buf[12][5];
#pragma omp threadprivate (cuf, q, ue, buf) 
static double fjac[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 - 1 + 1][5][5];
static double njac[12 / 2 * 2 + 1][12 / 2 * 2 + 1][12 - 1 + 1][5][5];
static double tmp1, tmp2, tmp3;
static void add(void);
static void adi(void);
static void error_norm(double rms[5]);
static void rhs_norm(double rms[5]);
static void exact_rhs(void);
static void exact_solution(double xi, double eta, double zeta, double dtemp[5]);
static void initialize(void);
static void lhsinit(void);
static void lhsx(void);
static void lhsy(void);
static void lhsz(void);
static void compute_rhs(void);
static void set_constants(void);
static void verify(int no_time_steps, char *class, boolean *verified);
static void x_solve(void);
static void x_backsubstitute(void);
static void x_solve_cell(void);
static void matvec_sub(double ablock[5][5], double avec[5], double bvec[5]);
static void matmul_sub(double ablock[5][5], double bblock[5][5], double cblock[5][5]);
static void binvcrhs(double lhs[5][5], double c[5][5], double r[5]);
static void binvrhs(double lhs[5][5], double r[5]);
static void y_solve(void);
static void y_backsubstitute(void);
static void y_solve_cell(void);
static void z_solve(void);
static void z_backsubstitute(void);
static void z_solve_cell(void);
int main(int argc, char **argv)
{
    int myid;
    MPI_Status stat;
    int size;
    int *argcVar = NULL;
    char ***argvVar = NULL;
    MPI_Init(argcVar, argvVar);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    int niter, step, n3;
    int nthreads = 1;
    double navg, mflops;
    double tmax;
    boolean verified;
    char class;
    FILE *fp;
    if (myid == 0)
    {
        printf("\n\n NAS Parallel Benchmarks 2.3 OpenMP C version"" - BT Benchmark\n\n");
        fp = fopen("inputbt.data", "r");
        fp != ((void *) 0);
        printf(" Reading from input file inputbt.data");
        fscanf(fp, "%d", &niter);
        while (fgetc(fp) != '\n')
            ;
        fscanf(fp, "%lg", &dt);
        while (fgetc(fp) != '\n')
            ;
        fscanf(fp, "%d%d%d", &grid_points[0], &grid_points[1], &grid_points[2]);
        fclose(fp);
        printf(" No input file inputbt.data. Using compiled defaults\n");
        printf(" Size: %3dx%3dx%3d\n", grid_points[0], grid_points[1], grid_points[2]);
        printf(" Iterations: %3d   dt: %10.6f\n", niter, dt);
        grid_points[0] > 12 || grid_points[1] > 12 || grid_points[2] > 12;
        printf(" %dx%dx%d\n", grid_points[0], grid_points[1], grid_points[2]);
        printf(" Problem size too big for compiled array sizes\n");
        exit(1);
        set_constants();
#pragma omp parallel 
        {
            initialize();
            lhsinit();
            exact_rhs();
            adi();
            initialize();
        }
        timer_clear(1);
        timer_start(1);
#pragma omp parallel firstprivate(niter) private(step)
        {
            for (step = 1;
                step <= niter;
                step++)
            {
                if (step % 20 == 0 || step == 1)
                {
#pragma omp master 
                    printf(" Time step %4d\n", step);
                }
                adi();
            }
        }
        timer_stop(1);
        tmax = timer_read(1);
        verify(niter, &class, &verified);
        n3 = grid_points[0] * grid_points[1] * grid_points[2];
        navg = (grid_points[0] + grid_points[1] + grid_points[2]) / 3.0;
        tmax != 0.0;
        c_print_results("BT", class, grid_points[0], grid_points[1], grid_points[2], niter, nthreads, tmax, mflops, "          floating point", verified, "2.3", "16 Jun 2015", "cc", "cc", "(none)", "-I../common", "-O3 ", "(none)", "(none)");
    }
}
static void add(void)
{
    int i, j, k, m;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    u[i][j][k][m] = u[i][j][k][m] + rhs[i][j][k][m];
                }
            }
        }
    }
}
static void adi(void)
{
    compute_rhs();
    x_solve();
    y_solve();
    z_solve();
    add();
}
static void error_norm(double rms[5])
{
    int i, j, k, m, d;
    double xi, eta, zeta, u_exact[5], add;
    for (m = 0;
        m < 5;
        m++)
    {
        rms[m] = 0.0;
    }
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            eta = (double) j * dnym1;
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                zeta = (double) k * dnzm1;
                exact_solution(xi, eta, zeta, u_exact);
                for (m = 0;
                    m < 5;
                    m++)
                {
                    add = u[i][j][k][m] - u_exact[m];
                    rms[m] = rms[m] + add * add;
                }
            }
        }
    }
    for (m = 0;
        m < 5;
        m++)
    {
        for (d = 0;
            d <= 2;
            d++)
        {
            rms[m] = rms[m] / (double) (grid_points[d] - 2);
        }
        rms[m] = sqrt(rms[m]);
    }
}
static void rhs_norm(double rms[5])
{
    int i, j, k, d, m;
    double add;
    for (m = 0;
        m < 5;
        m++)
    {
        rms[m] = 0.0;
    }
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    add = rhs[i][j][k][m];
                    rms[m] = rms[m] + add * add;
                }
            }
        }
    }
    for (m = 0;
        m < 5;
        m++)
    {
        for (d = 0;
            d <= 2;
            d++)
        {
            rms[m] = rms[m] / (double) (grid_points[d] - 2);
        }
        rms[m] = sqrt(rms[m]);
    }
}
static void exact_rhs(void)
{
    double dtemp[5], xi, eta, zeta, dtpp;
    int m, i, j, k, ip1, im1, jp1, jm1, km1, kp1;
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    forcing[i][j][k][m] = 0.0;
                }
            }
        }
    }
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        eta = (double) j * dnym1;
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            zeta = (double) k * dnzm1;
            for (i = 0;
                i < grid_points[0];
                i++)
            {
                xi = (double) i * dnxm1;
                exact_solution(xi, eta, zeta, dtemp);
                for (m = 0;
                    m < 5;
                    m++)
                {
                    ue[i][m] = dtemp[m];
                }
                dtpp = 1.0 / dtemp[0];
                for (m = 1;
                    m <= 4;
                    m++)
                {
                    buf[i][m] = dtpp * dtemp[m];
                }
                cuf[i] = buf[i][1] * buf[i][1];
                buf[i][0] = cuf[i] + buf[i][2] * buf[i][2] + buf[i][3] * buf[i][3];
                q[i] = 0.5 * (buf[i][1] * ue[i][1] + buf[i][2] * ue[i][2] + buf[i][3] * ue[i][3]);
            }
            for (i = 1;
                i < grid_points[0] - 1;
                i++)
            {
                im1 = i - 1;
                ip1 = i + 1;
                forcing[i][j][k][0] = forcing[i][j][k][0] - tx2 * (ue[ip1][1] - ue[im1][1]) + dx1tx1 * (ue[ip1][0] - 2.0 * ue[i][0] + ue[im1][0]);
                forcing[i][j][k][1] = forcing[i][j][k][1] - tx2 * ((ue[ip1][1] * buf[ip1][1] + c2 * (ue[ip1][4] - q[ip1])) - (ue[im1][1] * buf[im1][1] + c2 * (ue[im1][4] - q[im1]))) + xxcon1 * (buf[ip1][1] - 2.0 * buf[i][1] + buf[im1][1]) + dx2tx1 * (ue[ip1][1] - 2.0 * ue[i][1] + ue[im1][1]);
                forcing[i][j][k][2] = forcing[i][j][k][2] - tx2 * (ue[ip1][2] * buf[ip1][1] - ue[im1][2] * buf[im1][1]) + xxcon2 * (buf[ip1][2] - 2.0 * buf[i][2] + buf[im1][2]) + dx3tx1 * (ue[ip1][2] - 2.0 * ue[i][2] + ue[im1][2]);
                forcing[i][j][k][3] = forcing[i][j][k][3] - tx2 * (ue[ip1][3] * buf[ip1][1] - ue[im1][3] * buf[im1][1]) + xxcon2 * (buf[ip1][3] - 2.0 * buf[i][3] + buf[im1][3]) + dx4tx1 * (ue[ip1][3] - 2.0 * ue[i][3] + ue[im1][3]);
                forcing[i][j][k][4] = forcing[i][j][k][4] - tx2 * (buf[ip1][1] * (c1 * ue[ip1][4] - c2 * q[ip1]) - buf[im1][1] * (c1 * ue[im1][4] - c2 * q[im1])) + 0.5 * xxcon3 * (buf[ip1][0] - 2.0 * buf[i][0] + buf[im1][0]) + xxcon4 * (cuf[ip1] - 2.0 * cuf[i] + cuf[im1]) + xxcon5 * (buf[ip1][4] - 2.0 * buf[i][4] + buf[im1][4]) + dx5tx1 * (ue[ip1][4] - 2.0 * ue[i][4] + ue[im1][4]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                i = 1;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (5.0 * ue[i][m] - 4.0 * ue[i + 1][m] + ue[i + 2][m]);
                i = 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (- 4.0 * ue[i - 1][m] + 6.0 * ue[i][m] - 4.0 * ue[i + 1][m] + ue[i + 2][m]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                for (i = 1 * 3;
                    i <= grid_points[0] - 3 * 1 - 1;
                    i++)
                {
                    forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[i - 2][m] - 4.0 * ue[i - 1][m] + 6.0 * ue[i][m] - 4.0 * ue[i + 1][m] + ue[i + 2][m]);
                }
            }
            for (m = 0;
                m < 5;
                m++)
            {
                i = grid_points[0] - 3;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[i - 2][m] - 4.0 * ue[i - 1][m] + 6.0 * ue[i][m] - 4.0 * ue[i + 1][m]);
                i = grid_points[0] - 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[i - 2][m] - 4.0 * ue[i - 1][m] + 5.0 * ue[i][m]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        xi = (double) i * dnxm1;
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            zeta = (double) k * dnzm1;
            for (j = 0;
                j < grid_points[1];
                j++)
            {
                eta = (double) j * dnym1;
                exact_solution(xi, eta, zeta, dtemp);
                for (m = 0;
                    m < 5;
                    m++)
                {
                    ue[j][m] = dtemp[m];
                }
                dtpp = 1.0 / dtemp[0];
                for (m = 1;
                    m <= 4;
                    m++)
                {
                    buf[j][m] = dtpp * dtemp[m];
                }
                cuf[j] = buf[j][2] * buf[j][2];
                buf[j][0] = cuf[j] + buf[j][1] * buf[j][1] + buf[j][3] * buf[j][3];
                q[j] = 0.5 * (buf[j][1] * ue[j][1] + buf[j][2] * ue[j][2] + buf[j][3] * ue[j][3]);
            }
            for (j = 1;
                j < grid_points[1] - 1;
                j++)
            {
                jm1 = j - 1;
                jp1 = j + 1;
                forcing[i][j][k][0] = forcing[i][j][k][0] - ty2 * (ue[jp1][2] - ue[jm1][2]) + dy1ty1 * (ue[jp1][0] - 2.0 * ue[j][0] + ue[jm1][0]);
                forcing[i][j][k][1] = forcing[i][j][k][1] - ty2 * (ue[jp1][1] * buf[jp1][2] - ue[jm1][1] * buf[jm1][2]) + yycon2 * (buf[jp1][1] - 2.0 * buf[j][1] + buf[jm1][1]) + dy2ty1 * (ue[jp1][1] - 2.0 * ue[j][1] + ue[jm1][1]);
                forcing[i][j][k][2] = forcing[i][j][k][2] - ty2 * ((ue[jp1][2] * buf[jp1][2] + c2 * (ue[jp1][4] - q[jp1])) - (ue[jm1][2] * buf[jm1][2] + c2 * (ue[jm1][4] - q[jm1]))) + yycon1 * (buf[jp1][2] - 2.0 * buf[j][2] + buf[jm1][2]) + dy3ty1 * (ue[jp1][2] - 2.0 * ue[j][2] + ue[jm1][2]);
                forcing[i][j][k][3] = forcing[i][j][k][3] - ty2 * (ue[jp1][3] * buf[jp1][2] - ue[jm1][3] * buf[jm1][2]) + yycon2 * (buf[jp1][3] - 2.0 * buf[j][3] + buf[jm1][3]) + dy4ty1 * (ue[jp1][3] - 2.0 * ue[j][3] + ue[jm1][3]);
                forcing[i][j][k][4] = forcing[i][j][k][4] - ty2 * (buf[jp1][2] * (c1 * ue[jp1][4] - c2 * q[jp1]) - buf[jm1][2] * (c1 * ue[jm1][4] - c2 * q[jm1])) + 0.5 * yycon3 * (buf[jp1][0] - 2.0 * buf[j][0] + buf[jm1][0]) + yycon4 * (cuf[jp1] - 2.0 * cuf[j] + cuf[jm1]) + yycon5 * (buf[jp1][4] - 2.0 * buf[j][4] + buf[jm1][4]) + dy5ty1 * (ue[jp1][4] - 2.0 * ue[j][4] + ue[jm1][4]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                j = 1;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (5.0 * ue[j][m] - 4.0 * ue[j + 1][m] + ue[j + 2][m]);
                j = 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (- 4.0 * ue[j - 1][m] + 6.0 * ue[j][m] - 4.0 * ue[j + 1][m] + ue[j + 2][m]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                for (j = 1 * 3;
                    j <= grid_points[1] - 3 * 1 - 1;
                    j++)
                {
                    forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[j - 2][m] - 4.0 * ue[j - 1][m] + 6.0 * ue[j][m] - 4.0 * ue[j + 1][m] + ue[j + 2][m]);
                }
            }
            for (m = 0;
                m < 5;
                m++)
            {
                j = grid_points[1] - 3;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[j - 2][m] - 4.0 * ue[j - 1][m] + 6.0 * ue[j][m] - 4.0 * ue[j + 1][m]);
                j = grid_points[1] - 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[j - 2][m] - 4.0 * ue[j - 1][m] + 5.0 * ue[j][m]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        xi = (double) i * dnxm1;
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            eta = (double) j * dnym1;
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                zeta = (double) k * dnzm1;
                exact_solution(xi, eta, zeta, dtemp);
                for (m = 0;
                    m < 5;
                    m++)
                {
                    ue[k][m] = dtemp[m];
                }
                dtpp = 1.0 / dtemp[0];
                for (m = 1;
                    m <= 4;
                    m++)
                {
                    buf[k][m] = dtpp * dtemp[m];
                }
                cuf[k] = buf[k][3] * buf[k][3];
                buf[k][0] = cuf[k] + buf[k][1] * buf[k][1] + buf[k][2] * buf[k][2];
                q[k] = 0.5 * (buf[k][1] * ue[k][1] + buf[k][2] * ue[k][2] + buf[k][3] * ue[k][3]);
            }
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                km1 = k - 1;
                kp1 = k + 1;
                forcing[i][j][k][0] = forcing[i][j][k][0] - tz2 * (ue[kp1][3] - ue[km1][3]) + dz1tz1 * (ue[kp1][0] - 2.0 * ue[k][0] + ue[km1][0]);
                forcing[i][j][k][1] = forcing[i][j][k][1] - tz2 * (ue[kp1][1] * buf[kp1][3] - ue[km1][1] * buf[km1][3]) + zzcon2 * (buf[kp1][1] - 2.0 * buf[k][1] + buf[km1][1]) + dz2tz1 * (ue[kp1][1] - 2.0 * ue[k][1] + ue[km1][1]);
                forcing[i][j][k][2] = forcing[i][j][k][2] - tz2 * (ue[kp1][2] * buf[kp1][3] - ue[km1][2] * buf[km1][3]) + zzcon2 * (buf[kp1][2] - 2.0 * buf[k][2] + buf[km1][2]) + dz3tz1 * (ue[kp1][2] - 2.0 * ue[k][2] + ue[km1][2]);
                forcing[i][j][k][3] = forcing[i][j][k][3] - tz2 * ((ue[kp1][3] * buf[kp1][3] + c2 * (ue[kp1][4] - q[kp1])) - (ue[km1][3] * buf[km1][3] + c2 * (ue[km1][4] - q[km1]))) + zzcon1 * (buf[kp1][3] - 2.0 * buf[k][3] + buf[km1][3]) + dz4tz1 * (ue[kp1][3] - 2.0 * ue[k][3] + ue[km1][3]);
                forcing[i][j][k][4] = forcing[i][j][k][4] - tz2 * (buf[kp1][3] * (c1 * ue[kp1][4] - c2 * q[kp1]) - buf[km1][3] * (c1 * ue[km1][4] - c2 * q[km1])) + 0.5 * zzcon3 * (buf[kp1][0] - 2.0 * buf[k][0] + buf[km1][0]) + zzcon4 * (cuf[kp1] - 2.0 * cuf[k] + cuf[km1]) + zzcon5 * (buf[kp1][4] - 2.0 * buf[k][4] + buf[km1][4]) + dz5tz1 * (ue[kp1][4] - 2.0 * ue[k][4] + ue[km1][4]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                k = 1;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (5.0 * ue[k][m] - 4.0 * ue[k + 1][m] + ue[k + 2][m]);
                k = 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (- 4.0 * ue[k - 1][m] + 6.0 * ue[k][m] - 4.0 * ue[k + 1][m] + ue[k + 2][m]);
            }
            for (m = 0;
                m < 5;
                m++)
            {
                for (k = 1 * 3;
                    k <= grid_points[2] - 3 * 1 - 1;
                    k++)
                {
                    forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[k - 2][m] - 4.0 * ue[k - 1][m] + 6.0 * ue[k][m] - 4.0 * ue[k + 1][m] + ue[k + 2][m]);
                }
            }
            for (m = 0;
                m < 5;
                m++)
            {
                k = grid_points[2] - 3;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[k - 2][m] - 4.0 * ue[k - 1][m] + 6.0 * ue[k][m] - 4.0 * ue[k + 1][m]);
                k = grid_points[2] - 2;
                forcing[i][j][k][m] = forcing[i][j][k][m] - dssp * (ue[k - 2][m] - 4.0 * ue[k - 1][m] + 5.0 * ue[k][m]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    forcing[i][j][k][m] = - 1.0 * forcing[i][j][k][m];
                }
            }
        }
    }
}
static void exact_solution(double xi, double eta, double zeta, double dtemp[5])
{
    int m;
    for (m = 0;
        m < 5;
        m++)
    {
        dtemp[m] = ce[m][0] + xi * (ce[m][1] + xi * (ce[m][4] + xi * (ce[m][7] + xi * ce[m][10]))) + eta * (ce[m][2] + eta * (ce[m][5] + eta * (ce[m][8] + eta * ce[m][11]))) + zeta * (ce[m][3] + zeta * (ce[m][6] + zeta * (ce[m][9] + zeta * ce[m][12])));
    }
}
static void initialize(void)
{
    int i, j, k, m, ix, iy, iz;
    double xi, eta, zeta, Pface[2][3][5], Pxi, Peta, Pzeta, temp[5];
#pragma omp for 
    for (i = 0;
        i < 12;
        i++)
    {
        for (j = 0;
            j < 12;
            j++)
        {
            for (k = 0;
                k < 12;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    u[i][j][k][m] = 1.0;
                }
            }
        }
    }
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            eta = (double) j * dnym1;
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                zeta = (double) k * dnzm1;
                for (ix = 0;
                    ix < 2;
                    ix++)
                {
                    exact_solution((double) ix, eta, zeta, &(Pface[ix][0][0]));
                }
                for (iy = 0;
                    iy < 2;
                    iy++)
                {
                    exact_solution(xi, (double) iy, zeta, &Pface[iy][1][0]);
                }
                for (iz = 0;
                    iz < 2;
                    iz++)
                {
                    exact_solution(xi, eta, (double) iz, &Pface[iz][2][0]);
                }
                for (m = 0;
                    m < 5;
                    m++)
                {
                    Pxi = xi * Pface[1][0][m] + (1.0 - xi) * Pface[0][0][m];
                    Peta = eta * Pface[1][1][m] + (1.0 - eta) * Pface[0][1][m];
                    Pzeta = zeta * Pface[1][2][m] + (1.0 - zeta) * Pface[0][2][m];
                    u[i][j][k][m] = Pxi + Peta + Pzeta - Pxi * Peta - Pxi * Pzeta - Peta * Pzeta + Pxi * Peta * Pzeta;
                }
            }
        }
    }
    i = 0;
    xi = 0.0;
#pragma omp for nowait
    for (j = 0;
        j < grid_points[1];
        j++)
    {
        eta = (double) j * dnym1;
        for (k = 0;
            k < grid_points[2];
            k++)
        {
            zeta = (double) k * dnzm1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
    i = grid_points[0] - 1;
    xi = 1.0;
#pragma omp for 
    for (j = 0;
        j < grid_points[1];
        j++)
    {
        eta = (double) j * dnym1;
        for (k = 0;
            k < grid_points[2];
            k++)
        {
            zeta = (double) k * dnzm1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
    j = 0;
    eta = 0.0;
#pragma omp for nowait
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (k = 0;
            k < grid_points[2];
            k++)
        {
            zeta = (double) k * dnzm1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
    j = grid_points[1] - 1;
    eta = 1.0;
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (k = 0;
            k < grid_points[2];
            k++)
        {
            zeta = (double) k * dnzm1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
    k = 0;
    zeta = 0.0;
#pragma omp for nowait
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            eta = (double) j * dnym1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
    k = grid_points[2] - 1;
    zeta = 1.0;
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        xi = (double) i * dnxm1;
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            eta = (double) j * dnym1;
            exact_solution(xi, eta, zeta, temp);
            for (m = 0;
                m < 5;
                m++)
            {
                u[i][j][k][m] = temp[m];
            }
        }
    }
}
static void lhsinit(void)
{
    int i, j, k, m, n;
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    for (n = 0;
                        n < 5;
                        n++)
                    {
                        lhs[i][j][k][0][m][n] = 0.0;
                        lhs[i][j][k][1][m][n] = 0.0;
                        lhs[i][j][k][2][m][n] = 0.0;
                    }
                }
            }
        }
    }
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    lhs[i][j][k][1][m][m] = 1.0;
                }
            }
        }
    }
}
static void lhsx(void)
{
    int i, j, k;
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (i = 0;
                i < grid_points[0];
                i++)
            {
                tmp1 = 1.0 / u[i][j][k][0];
                tmp2 = tmp1 * tmp1;
                tmp3 = tmp1 * tmp2;
                fjac[i][j][k][0][0] = 0.0;
                fjac[i][j][k][0][1] = 1.0;
                fjac[i][j][k][0][2] = 0.0;
                fjac[i][j][k][0][3] = 0.0;
                fjac[i][j][k][0][4] = 0.0;
                fjac[i][j][k][1][0] = - (u[i][j][k][1] * tmp2 * u[i][j][k][1]) + c2 * 0.50 * (u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][1][1] = (2.0 - c2) * (u[i][j][k][1] / u[i][j][k][0]);
                fjac[i][j][k][1][2] = - c2 * (u[i][j][k][2] * tmp1);
                fjac[i][j][k][1][3] = - c2 * (u[i][j][k][3] * tmp1);
                fjac[i][j][k][1][4] = c2;
                fjac[i][j][k][2][0] = - (u[i][j][k][1] * u[i][j][k][2]) * tmp2;
                fjac[i][j][k][2][1] = u[i][j][k][2] * tmp1;
                fjac[i][j][k][2][2] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][2][3] = 0.0;
                fjac[i][j][k][2][4] = 0.0;
                fjac[i][j][k][3][0] = - (u[i][j][k][1] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][3][1] = u[i][j][k][3] * tmp1;
                fjac[i][j][k][3][2] = 0.0;
                fjac[i][j][k][3][3] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][3][4] = 0.0;
                fjac[i][j][k][4][0] = (c2 * (u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2 - c1 * (u[i][j][k][4] * tmp1)) * (u[i][j][k][1] * tmp1);
                fjac[i][j][k][4][1] = c1 * u[i][j][k][4] * tmp1 - 0.50 * c2 * (3.0 * u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][4][2] = - c2 * (u[i][j][k][2] * u[i][j][k][1]) * tmp2;
                fjac[i][j][k][4][3] = - c2 * (u[i][j][k][3] * u[i][j][k][1]) * tmp2;
                fjac[i][j][k][4][4] = c1 * (u[i][j][k][1] * tmp1);
                njac[i][j][k][0][0] = 0.0;
                njac[i][j][k][0][1] = 0.0;
                njac[i][j][k][0][2] = 0.0;
                njac[i][j][k][0][3] = 0.0;
                njac[i][j][k][0][4] = 0.0;
                njac[i][j][k][1][0] = - con43 * c3c4 * tmp2 * u[i][j][k][1];
                njac[i][j][k][1][1] = con43 * c3c4 * tmp1;
                njac[i][j][k][1][2] = 0.0;
                njac[i][j][k][1][3] = 0.0;
                njac[i][j][k][1][4] = 0.0;
                njac[i][j][k][2][0] = - c3c4 * tmp2 * u[i][j][k][2];
                njac[i][j][k][2][1] = 0.0;
                njac[i][j][k][2][2] = c3c4 * tmp1;
                njac[i][j][k][2][3] = 0.0;
                njac[i][j][k][2][4] = 0.0;
                njac[i][j][k][3][0] = - c3c4 * tmp2 * u[i][j][k][3];
                njac[i][j][k][3][1] = 0.0;
                njac[i][j][k][3][2] = 0.0;
                njac[i][j][k][3][3] = c3c4 * tmp1;
                njac[i][j][k][3][4] = 0.0;
                njac[i][j][k][4][0] = - (con43 * c3c4 - c1345) * tmp3 * (((u[i][j][k][1]) * (u[i][j][k][1]))) - (c3c4 - c1345) * tmp3 * (((u[i][j][k][2]) * (u[i][j][k][2]))) - (c3c4 - c1345) * tmp3 * (((u[i][j][k][3]) * (u[i][j][k][3]))) - c1345 * tmp2 * u[i][j][k][4];
                njac[i][j][k][4][1] = (con43 * c3c4 - c1345) * tmp2 * u[i][j][k][1];
                njac[i][j][k][4][2] = (c3c4 - c1345) * tmp2 * u[i][j][k][2];
                njac[i][j][k][4][3] = (c3c4 - c1345) * tmp2 * u[i][j][k][3];
                njac[i][j][k][4][4] = (c1345) * tmp1;
            }
            for (i = 1;
                i < grid_points[0] - 1;
                i++)
            {
                tmp1 = dt * tx1;
                tmp2 = dt * tx2;
                lhs[i][j][k][0][0][0] = - tmp2 * fjac[i - 1][j][k][0][0] - tmp1 * njac[i - 1][j][k][0][0] - tmp1 * dx1;
                lhs[i][j][k][0][0][1] = - tmp2 * fjac[i - 1][j][k][0][1] - tmp1 * njac[i - 1][j][k][0][1];
                lhs[i][j][k][0][0][2] = - tmp2 * fjac[i - 1][j][k][0][2] - tmp1 * njac[i - 1][j][k][0][2];
                lhs[i][j][k][0][0][3] = - tmp2 * fjac[i - 1][j][k][0][3] - tmp1 * njac[i - 1][j][k][0][3];
                lhs[i][j][k][0][0][4] = - tmp2 * fjac[i - 1][j][k][0][4] - tmp1 * njac[i - 1][j][k][0][4];
                lhs[i][j][k][0][1][0] = - tmp2 * fjac[i - 1][j][k][1][0] - tmp1 * njac[i - 1][j][k][1][0];
                lhs[i][j][k][0][1][1] = - tmp2 * fjac[i - 1][j][k][1][1] - tmp1 * njac[i - 1][j][k][1][1] - tmp1 * dx2;
                lhs[i][j][k][0][1][2] = - tmp2 * fjac[i - 1][j][k][1][2] - tmp1 * njac[i - 1][j][k][1][2];
                lhs[i][j][k][0][1][3] = - tmp2 * fjac[i - 1][j][k][1][3] - tmp1 * njac[i - 1][j][k][1][3];
                lhs[i][j][k][0][1][4] = - tmp2 * fjac[i - 1][j][k][1][4] - tmp1 * njac[i - 1][j][k][1][4];
                lhs[i][j][k][0][2][0] = - tmp2 * fjac[i - 1][j][k][2][0] - tmp1 * njac[i - 1][j][k][2][0];
                lhs[i][j][k][0][2][1] = - tmp2 * fjac[i - 1][j][k][2][1] - tmp1 * njac[i - 1][j][k][2][1];
                lhs[i][j][k][0][2][2] = - tmp2 * fjac[i - 1][j][k][2][2] - tmp1 * njac[i - 1][j][k][2][2] - tmp1 * dx3;
                lhs[i][j][k][0][2][3] = - tmp2 * fjac[i - 1][j][k][2][3] - tmp1 * njac[i - 1][j][k][2][3];
                lhs[i][j][k][0][2][4] = - tmp2 * fjac[i - 1][j][k][2][4] - tmp1 * njac[i - 1][j][k][2][4];
                lhs[i][j][k][0][3][0] = - tmp2 * fjac[i - 1][j][k][3][0] - tmp1 * njac[i - 1][j][k][3][0];
                lhs[i][j][k][0][3][1] = - tmp2 * fjac[i - 1][j][k][3][1] - tmp1 * njac[i - 1][j][k][3][1];
                lhs[i][j][k][0][3][2] = - tmp2 * fjac[i - 1][j][k][3][2] - tmp1 * njac[i - 1][j][k][3][2];
                lhs[i][j][k][0][3][3] = - tmp2 * fjac[i - 1][j][k][3][3] - tmp1 * njac[i - 1][j][k][3][3] - tmp1 * dx4;
                lhs[i][j][k][0][3][4] = - tmp2 * fjac[i - 1][j][k][3][4] - tmp1 * njac[i - 1][j][k][3][4];
                lhs[i][j][k][0][4][0] = - tmp2 * fjac[i - 1][j][k][4][0] - tmp1 * njac[i - 1][j][k][4][0];
                lhs[i][j][k][0][4][1] = - tmp2 * fjac[i - 1][j][k][4][1] - tmp1 * njac[i - 1][j][k][4][1];
                lhs[i][j][k][0][4][2] = - tmp2 * fjac[i - 1][j][k][4][2] - tmp1 * njac[i - 1][j][k][4][2];
                lhs[i][j][k][0][4][3] = - tmp2 * fjac[i - 1][j][k][4][3] - tmp1 * njac[i - 1][j][k][4][3];
                lhs[i][j][k][0][4][4] = - tmp2 * fjac[i - 1][j][k][4][4] - tmp1 * njac[i - 1][j][k][4][4] - tmp1 * dx5;
                lhs[i][j][k][1][0][0] = 1.0 + tmp1 * 2.0 * njac[i][j][k][0][0] + tmp1 * 2.0 * dx1;
                lhs[i][j][k][1][0][1] = tmp1 * 2.0 * njac[i][j][k][0][1];
                lhs[i][j][k][1][0][2] = tmp1 * 2.0 * njac[i][j][k][0][2];
                lhs[i][j][k][1][0][3] = tmp1 * 2.0 * njac[i][j][k][0][3];
                lhs[i][j][k][1][0][4] = tmp1 * 2.0 * njac[i][j][k][0][4];
                lhs[i][j][k][1][1][0] = tmp1 * 2.0 * njac[i][j][k][1][0];
                lhs[i][j][k][1][1][1] = 1.0 + tmp1 * 2.0 * njac[i][j][k][1][1] + tmp1 * 2.0 * dx2;
                lhs[i][j][k][1][1][2] = tmp1 * 2.0 * njac[i][j][k][1][2];
                lhs[i][j][k][1][1][3] = tmp1 * 2.0 * njac[i][j][k][1][3];
                lhs[i][j][k][1][1][4] = tmp1 * 2.0 * njac[i][j][k][1][4];
                lhs[i][j][k][1][2][0] = tmp1 * 2.0 * njac[i][j][k][2][0];
                lhs[i][j][k][1][2][1] = tmp1 * 2.0 * njac[i][j][k][2][1];
                lhs[i][j][k][1][2][2] = 1.0 + tmp1 * 2.0 * njac[i][j][k][2][2] + tmp1 * 2.0 * dx3;
                lhs[i][j][k][1][2][3] = tmp1 * 2.0 * njac[i][j][k][2][3];
                lhs[i][j][k][1][2][4] = tmp1 * 2.0 * njac[i][j][k][2][4];
                lhs[i][j][k][1][3][0] = tmp1 * 2.0 * njac[i][j][k][3][0];
                lhs[i][j][k][1][3][1] = tmp1 * 2.0 * njac[i][j][k][3][1];
                lhs[i][j][k][1][3][2] = tmp1 * 2.0 * njac[i][j][k][3][2];
                lhs[i][j][k][1][3][3] = 1.0 + tmp1 * 2.0 * njac[i][j][k][3][3] + tmp1 * 2.0 * dx4;
                lhs[i][j][k][1][3][4] = tmp1 * 2.0 * njac[i][j][k][3][4];
                lhs[i][j][k][1][4][0] = tmp1 * 2.0 * njac[i][j][k][4][0];
                lhs[i][j][k][1][4][1] = tmp1 * 2.0 * njac[i][j][k][4][1];
                lhs[i][j][k][1][4][2] = tmp1 * 2.0 * njac[i][j][k][4][2];
                lhs[i][j][k][1][4][3] = tmp1 * 2.0 * njac[i][j][k][4][3];
                lhs[i][j][k][1][4][4] = 1.0 + tmp1 * 2.0 * njac[i][j][k][4][4] + tmp1 * 2.0 * dx5;
                lhs[i][j][k][2][0][0] = tmp2 * fjac[i + 1][j][k][0][0] - tmp1 * njac[i + 1][j][k][0][0] - tmp1 * dx1;
                lhs[i][j][k][2][0][1] = tmp2 * fjac[i + 1][j][k][0][1] - tmp1 * njac[i + 1][j][k][0][1];
                lhs[i][j][k][2][0][2] = tmp2 * fjac[i + 1][j][k][0][2] - tmp1 * njac[i + 1][j][k][0][2];
                lhs[i][j][k][2][0][3] = tmp2 * fjac[i + 1][j][k][0][3] - tmp1 * njac[i + 1][j][k][0][3];
                lhs[i][j][k][2][0][4] = tmp2 * fjac[i + 1][j][k][0][4] - tmp1 * njac[i + 1][j][k][0][4];
                lhs[i][j][k][2][1][0] = tmp2 * fjac[i + 1][j][k][1][0] - tmp1 * njac[i + 1][j][k][1][0];
                lhs[i][j][k][2][1][1] = tmp2 * fjac[i + 1][j][k][1][1] - tmp1 * njac[i + 1][j][k][1][1] - tmp1 * dx2;
                lhs[i][j][k][2][1][2] = tmp2 * fjac[i + 1][j][k][1][2] - tmp1 * njac[i + 1][j][k][1][2];
                lhs[i][j][k][2][1][3] = tmp2 * fjac[i + 1][j][k][1][3] - tmp1 * njac[i + 1][j][k][1][3];
                lhs[i][j][k][2][1][4] = tmp2 * fjac[i + 1][j][k][1][4] - tmp1 * njac[i + 1][j][k][1][4];
                lhs[i][j][k][2][2][0] = tmp2 * fjac[i + 1][j][k][2][0] - tmp1 * njac[i + 1][j][k][2][0];
                lhs[i][j][k][2][2][1] = tmp2 * fjac[i + 1][j][k][2][1] - tmp1 * njac[i + 1][j][k][2][1];
                lhs[i][j][k][2][2][2] = tmp2 * fjac[i + 1][j][k][2][2] - tmp1 * njac[i + 1][j][k][2][2] - tmp1 * dx3;
                lhs[i][j][k][2][2][3] = tmp2 * fjac[i + 1][j][k][2][3] - tmp1 * njac[i + 1][j][k][2][3];
                lhs[i][j][k][2][2][4] = tmp2 * fjac[i + 1][j][k][2][4] - tmp1 * njac[i + 1][j][k][2][4];
                lhs[i][j][k][2][3][0] = tmp2 * fjac[i + 1][j][k][3][0] - tmp1 * njac[i + 1][j][k][3][0];
                lhs[i][j][k][2][3][1] = tmp2 * fjac[i + 1][j][k][3][1] - tmp1 * njac[i + 1][j][k][3][1];
                lhs[i][j][k][2][3][2] = tmp2 * fjac[i + 1][j][k][3][2] - tmp1 * njac[i + 1][j][k][3][2];
                lhs[i][j][k][2][3][3] = tmp2 * fjac[i + 1][j][k][3][3] - tmp1 * njac[i + 1][j][k][3][3] - tmp1 * dx4;
                lhs[i][j][k][2][3][4] = tmp2 * fjac[i + 1][j][k][3][4] - tmp1 * njac[i + 1][j][k][3][4];
                lhs[i][j][k][2][4][0] = tmp2 * fjac[i + 1][j][k][4][0] - tmp1 * njac[i + 1][j][k][4][0];
                lhs[i][j][k][2][4][1] = tmp2 * fjac[i + 1][j][k][4][1] - tmp1 * njac[i + 1][j][k][4][1];
                lhs[i][j][k][2][4][2] = tmp2 * fjac[i + 1][j][k][4][2] - tmp1 * njac[i + 1][j][k][4][2];
                lhs[i][j][k][2][4][3] = tmp2 * fjac[i + 1][j][k][4][3] - tmp1 * njac[i + 1][j][k][4][3];
                lhs[i][j][k][2][4][4] = tmp2 * fjac[i + 1][j][k][4][4] - tmp1 * njac[i + 1][j][k][4][4] - tmp1 * dx5;
            }
        }
    }
}
static void lhsy(void)
{
    int i, j, k;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                tmp1 = 1.0 / u[i][j][k][0];
                tmp2 = tmp1 * tmp1;
                tmp3 = tmp1 * tmp2;
                fjac[i][j][k][0][0] = 0.0;
                fjac[i][j][k][0][1] = 0.0;
                fjac[i][j][k][0][2] = 1.0;
                fjac[i][j][k][0][3] = 0.0;
                fjac[i][j][k][0][4] = 0.0;
                fjac[i][j][k][1][0] = - (u[i][j][k][1] * u[i][j][k][2]) * tmp2;
                fjac[i][j][k][1][1] = u[i][j][k][2] * tmp1;
                fjac[i][j][k][1][2] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][1][3] = 0.0;
                fjac[i][j][k][1][4] = 0.0;
                fjac[i][j][k][2][0] = - (u[i][j][k][2] * u[i][j][k][2] * tmp2) + 0.50 * c2 * ((u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2);
                fjac[i][j][k][2][1] = - c2 * u[i][j][k][1] * tmp1;
                fjac[i][j][k][2][2] = (2.0 - c2) * u[i][j][k][2] * tmp1;
                fjac[i][j][k][2][3] = - c2 * u[i][j][k][3] * tmp1;
                fjac[i][j][k][2][4] = c2;
                fjac[i][j][k][3][0] = - (u[i][j][k][2] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][3][1] = 0.0;
                fjac[i][j][k][3][2] = u[i][j][k][3] * tmp1;
                fjac[i][j][k][3][3] = u[i][j][k][2] * tmp1;
                fjac[i][j][k][3][4] = 0.0;
                fjac[i][j][k][4][0] = (c2 * (u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2 - c1 * u[i][j][k][4] * tmp1) * u[i][j][k][2] * tmp1;
                fjac[i][j][k][4][1] = - c2 * u[i][j][k][1] * u[i][j][k][2] * tmp2;
                fjac[i][j][k][4][2] = c1 * u[i][j][k][4] * tmp1 - 0.50 * c2 * ((u[i][j][k][1] * u[i][j][k][1] + 3.0 * u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2);
                fjac[i][j][k][4][3] = - c2 * (u[i][j][k][2] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][4][4] = c1 * u[i][j][k][2] * tmp1;
                njac[i][j][k][0][0] = 0.0;
                njac[i][j][k][0][1] = 0.0;
                njac[i][j][k][0][2] = 0.0;
                njac[i][j][k][0][3] = 0.0;
                njac[i][j][k][0][4] = 0.0;
                njac[i][j][k][1][0] = - c3c4 * tmp2 * u[i][j][k][1];
                njac[i][j][k][1][1] = c3c4 * tmp1;
                njac[i][j][k][1][2] = 0.0;
                njac[i][j][k][1][3] = 0.0;
                njac[i][j][k][1][4] = 0.0;
                njac[i][j][k][2][0] = - con43 * c3c4 * tmp2 * u[i][j][k][2];
                njac[i][j][k][2][1] = 0.0;
                njac[i][j][k][2][2] = con43 * c3c4 * tmp1;
                njac[i][j][k][2][3] = 0.0;
                njac[i][j][k][2][4] = 0.0;
                njac[i][j][k][3][0] = - c3c4 * tmp2 * u[i][j][k][3];
                njac[i][j][k][3][1] = 0.0;
                njac[i][j][k][3][2] = 0.0;
                njac[i][j][k][3][3] = c3c4 * tmp1;
                njac[i][j][k][3][4] = 0.0;
                njac[i][j][k][4][0] = - (c3c4 - c1345) * tmp3 * (((u[i][j][k][1]) * (u[i][j][k][1]))) - (con43 * c3c4 - c1345) * tmp3 * (((u[i][j][k][2]) * (u[i][j][k][2]))) - (c3c4 - c1345) * tmp3 * (((u[i][j][k][3]) * (u[i][j][k][3]))) - c1345 * tmp2 * u[i][j][k][4];
                njac[i][j][k][4][1] = (c3c4 - c1345) * tmp2 * u[i][j][k][1];
                njac[i][j][k][4][2] = (con43 * c3c4 - c1345) * tmp2 * u[i][j][k][2];
                njac[i][j][k][4][3] = (c3c4 - c1345) * tmp2 * u[i][j][k][3];
                njac[i][j][k][4][4] = (c1345) * tmp1;
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                tmp1 = dt * ty1;
                tmp2 = dt * ty2;
                lhs[i][j][k][0][0][0] = - tmp2 * fjac[i][j - 1][k][0][0] - tmp1 * njac[i][j - 1][k][0][0] - tmp1 * dy1;
                lhs[i][j][k][0][0][1] = - tmp2 * fjac[i][j - 1][k][0][1] - tmp1 * njac[i][j - 1][k][0][1];
                lhs[i][j][k][0][0][2] = - tmp2 * fjac[i][j - 1][k][0][2] - tmp1 * njac[i][j - 1][k][0][2];
                lhs[i][j][k][0][0][3] = - tmp2 * fjac[i][j - 1][k][0][3] - tmp1 * njac[i][j - 1][k][0][3];
                lhs[i][j][k][0][0][4] = - tmp2 * fjac[i][j - 1][k][0][4] - tmp1 * njac[i][j - 1][k][0][4];
                lhs[i][j][k][0][1][0] = - tmp2 * fjac[i][j - 1][k][1][0] - tmp1 * njac[i][j - 1][k][1][0];
                lhs[i][j][k][0][1][1] = - tmp2 * fjac[i][j - 1][k][1][1] - tmp1 * njac[i][j - 1][k][1][1] - tmp1 * dy2;
                lhs[i][j][k][0][1][2] = - tmp2 * fjac[i][j - 1][k][1][2] - tmp1 * njac[i][j - 1][k][1][2];
                lhs[i][j][k][0][1][3] = - tmp2 * fjac[i][j - 1][k][1][3] - tmp1 * njac[i][j - 1][k][1][3];
                lhs[i][j][k][0][1][4] = - tmp2 * fjac[i][j - 1][k][1][4] - tmp1 * njac[i][j - 1][k][1][4];
                lhs[i][j][k][0][2][0] = - tmp2 * fjac[i][j - 1][k][2][0] - tmp1 * njac[i][j - 1][k][2][0];
                lhs[i][j][k][0][2][1] = - tmp2 * fjac[i][j - 1][k][2][1] - tmp1 * njac[i][j - 1][k][2][1];
                lhs[i][j][k][0][2][2] = - tmp2 * fjac[i][j - 1][k][2][2] - tmp1 * njac[i][j - 1][k][2][2] - tmp1 * dy3;
                lhs[i][j][k][0][2][3] = - tmp2 * fjac[i][j - 1][k][2][3] - tmp1 * njac[i][j - 1][k][2][3];
                lhs[i][j][k][0][2][4] = - tmp2 * fjac[i][j - 1][k][2][4] - tmp1 * njac[i][j - 1][k][2][4];
                lhs[i][j][k][0][3][0] = - tmp2 * fjac[i][j - 1][k][3][0] - tmp1 * njac[i][j - 1][k][3][0];
                lhs[i][j][k][0][3][1] = - tmp2 * fjac[i][j - 1][k][3][1] - tmp1 * njac[i][j - 1][k][3][1];
                lhs[i][j][k][0][3][2] = - tmp2 * fjac[i][j - 1][k][3][2] - tmp1 * njac[i][j - 1][k][3][2];
                lhs[i][j][k][0][3][3] = - tmp2 * fjac[i][j - 1][k][3][3] - tmp1 * njac[i][j - 1][k][3][3] - tmp1 * dy4;
                lhs[i][j][k][0][3][4] = - tmp2 * fjac[i][j - 1][k][3][4] - tmp1 * njac[i][j - 1][k][3][4];
                lhs[i][j][k][0][4][0] = - tmp2 * fjac[i][j - 1][k][4][0] - tmp1 * njac[i][j - 1][k][4][0];
                lhs[i][j][k][0][4][1] = - tmp2 * fjac[i][j - 1][k][4][1] - tmp1 * njac[i][j - 1][k][4][1];
                lhs[i][j][k][0][4][2] = - tmp2 * fjac[i][j - 1][k][4][2] - tmp1 * njac[i][j - 1][k][4][2];
                lhs[i][j][k][0][4][3] = - tmp2 * fjac[i][j - 1][k][4][3] - tmp1 * njac[i][j - 1][k][4][3];
                lhs[i][j][k][0][4][4] = - tmp2 * fjac[i][j - 1][k][4][4] - tmp1 * njac[i][j - 1][k][4][4] - tmp1 * dy5;
                lhs[i][j][k][1][0][0] = 1.0 + tmp1 * 2.0 * njac[i][j][k][0][0] + tmp1 * 2.0 * dy1;
                lhs[i][j][k][1][0][1] = tmp1 * 2.0 * njac[i][j][k][0][1];
                lhs[i][j][k][1][0][2] = tmp1 * 2.0 * njac[i][j][k][0][2];
                lhs[i][j][k][1][0][3] = tmp1 * 2.0 * njac[i][j][k][0][3];
                lhs[i][j][k][1][0][4] = tmp1 * 2.0 * njac[i][j][k][0][4];
                lhs[i][j][k][1][1][0] = tmp1 * 2.0 * njac[i][j][k][1][0];
                lhs[i][j][k][1][1][1] = 1.0 + tmp1 * 2.0 * njac[i][j][k][1][1] + tmp1 * 2.0 * dy2;
                lhs[i][j][k][1][1][2] = tmp1 * 2.0 * njac[i][j][k][1][2];
                lhs[i][j][k][1][1][3] = tmp1 * 2.0 * njac[i][j][k][1][3];
                lhs[i][j][k][1][1][4] = tmp1 * 2.0 * njac[i][j][k][1][4];
                lhs[i][j][k][1][2][0] = tmp1 * 2.0 * njac[i][j][k][2][0];
                lhs[i][j][k][1][2][1] = tmp1 * 2.0 * njac[i][j][k][2][1];
                lhs[i][j][k][1][2][2] = 1.0 + tmp1 * 2.0 * njac[i][j][k][2][2] + tmp1 * 2.0 * dy3;
                lhs[i][j][k][1][2][3] = tmp1 * 2.0 * njac[i][j][k][2][3];
                lhs[i][j][k][1][2][4] = tmp1 * 2.0 * njac[i][j][k][2][4];
                lhs[i][j][k][1][3][0] = tmp1 * 2.0 * njac[i][j][k][3][0];
                lhs[i][j][k][1][3][1] = tmp1 * 2.0 * njac[i][j][k][3][1];
                lhs[i][j][k][1][3][2] = tmp1 * 2.0 * njac[i][j][k][3][2];
                lhs[i][j][k][1][3][3] = 1.0 + tmp1 * 2.0 * njac[i][j][k][3][3] + tmp1 * 2.0 * dy4;
                lhs[i][j][k][1][3][4] = tmp1 * 2.0 * njac[i][j][k][3][4];
                lhs[i][j][k][1][4][0] = tmp1 * 2.0 * njac[i][j][k][4][0];
                lhs[i][j][k][1][4][1] = tmp1 * 2.0 * njac[i][j][k][4][1];
                lhs[i][j][k][1][4][2] = tmp1 * 2.0 * njac[i][j][k][4][2];
                lhs[i][j][k][1][4][3] = tmp1 * 2.0 * njac[i][j][k][4][3];
                lhs[i][j][k][1][4][4] = 1.0 + tmp1 * 2.0 * njac[i][j][k][4][4] + tmp1 * 2.0 * dy5;
                lhs[i][j][k][2][0][0] = tmp2 * fjac[i][j + 1][k][0][0] - tmp1 * njac[i][j + 1][k][0][0] - tmp1 * dy1;
                lhs[i][j][k][2][0][1] = tmp2 * fjac[i][j + 1][k][0][1] - tmp1 * njac[i][j + 1][k][0][1];
                lhs[i][j][k][2][0][2] = tmp2 * fjac[i][j + 1][k][0][2] - tmp1 * njac[i][j + 1][k][0][2];
                lhs[i][j][k][2][0][3] = tmp2 * fjac[i][j + 1][k][0][3] - tmp1 * njac[i][j + 1][k][0][3];
                lhs[i][j][k][2][0][4] = tmp2 * fjac[i][j + 1][k][0][4] - tmp1 * njac[i][j + 1][k][0][4];
                lhs[i][j][k][2][1][0] = tmp2 * fjac[i][j + 1][k][1][0] - tmp1 * njac[i][j + 1][k][1][0];
                lhs[i][j][k][2][1][1] = tmp2 * fjac[i][j + 1][k][1][1] - tmp1 * njac[i][j + 1][k][1][1] - tmp1 * dy2;
                lhs[i][j][k][2][1][2] = tmp2 * fjac[i][j + 1][k][1][2] - tmp1 * njac[i][j + 1][k][1][2];
                lhs[i][j][k][2][1][3] = tmp2 * fjac[i][j + 1][k][1][3] - tmp1 * njac[i][j + 1][k][1][3];
                lhs[i][j][k][2][1][4] = tmp2 * fjac[i][j + 1][k][1][4] - tmp1 * njac[i][j + 1][k][1][4];
                lhs[i][j][k][2][2][0] = tmp2 * fjac[i][j + 1][k][2][0] - tmp1 * njac[i][j + 1][k][2][0];
                lhs[i][j][k][2][2][1] = tmp2 * fjac[i][j + 1][k][2][1] - tmp1 * njac[i][j + 1][k][2][1];
                lhs[i][j][k][2][2][2] = tmp2 * fjac[i][j + 1][k][2][2] - tmp1 * njac[i][j + 1][k][2][2] - tmp1 * dy3;
                lhs[i][j][k][2][2][3] = tmp2 * fjac[i][j + 1][k][2][3] - tmp1 * njac[i][j + 1][k][2][3];
                lhs[i][j][k][2][2][4] = tmp2 * fjac[i][j + 1][k][2][4] - tmp1 * njac[i][j + 1][k][2][4];
                lhs[i][j][k][2][3][0] = tmp2 * fjac[i][j + 1][k][3][0] - tmp1 * njac[i][j + 1][k][3][0];
                lhs[i][j][k][2][3][1] = tmp2 * fjac[i][j + 1][k][3][1] - tmp1 * njac[i][j + 1][k][3][1];
                lhs[i][j][k][2][3][2] = tmp2 * fjac[i][j + 1][k][3][2] - tmp1 * njac[i][j + 1][k][3][2];
                lhs[i][j][k][2][3][3] = tmp2 * fjac[i][j + 1][k][3][3] - tmp1 * njac[i][j + 1][k][3][3] - tmp1 * dy4;
                lhs[i][j][k][2][3][4] = tmp2 * fjac[i][j + 1][k][3][4] - tmp1 * njac[i][j + 1][k][3][4];
                lhs[i][j][k][2][4][0] = tmp2 * fjac[i][j + 1][k][4][0] - tmp1 * njac[i][j + 1][k][4][0];
                lhs[i][j][k][2][4][1] = tmp2 * fjac[i][j + 1][k][4][1] - tmp1 * njac[i][j + 1][k][4][1];
                lhs[i][j][k][2][4][2] = tmp2 * fjac[i][j + 1][k][4][2] - tmp1 * njac[i][j + 1][k][4][2];
                lhs[i][j][k][2][4][3] = tmp2 * fjac[i][j + 1][k][4][3] - tmp1 * njac[i][j + 1][k][4][3];
                lhs[i][j][k][2][4][4] = tmp2 * fjac[i][j + 1][k][4][4] - tmp1 * njac[i][j + 1][k][4][4] - tmp1 * dy5;
            }
        }
    }
}
static void lhsz(void)
{
    int i, j, k;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                tmp1 = 1.0 / u[i][j][k][0];
                tmp2 = tmp1 * tmp1;
                tmp3 = tmp1 * tmp2;
                fjac[i][j][k][0][0] = 0.0;
                fjac[i][j][k][0][1] = 0.0;
                fjac[i][j][k][0][2] = 0.0;
                fjac[i][j][k][0][3] = 1.0;
                fjac[i][j][k][0][4] = 0.0;
                fjac[i][j][k][1][0] = - (u[i][j][k][1] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][1][1] = u[i][j][k][3] * tmp1;
                fjac[i][j][k][1][2] = 0.0;
                fjac[i][j][k][1][3] = u[i][j][k][1] * tmp1;
                fjac[i][j][k][1][4] = 0.0;
                fjac[i][j][k][2][0] = - (u[i][j][k][2] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][2][1] = 0.0;
                fjac[i][j][k][2][2] = u[i][j][k][3] * tmp1;
                fjac[i][j][k][2][3] = u[i][j][k][2] * tmp1;
                fjac[i][j][k][2][4] = 0.0;
                fjac[i][j][k][3][0] = - (u[i][j][k][3] * u[i][j][k][3] * tmp2) + 0.50 * c2 * ((u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2);
                fjac[i][j][k][3][1] = - c2 * u[i][j][k][1] * tmp1;
                fjac[i][j][k][3][2] = - c2 * u[i][j][k][2] * tmp1;
                fjac[i][j][k][3][3] = (2.0 - c2) * u[i][j][k][3] * tmp1;
                fjac[i][j][k][3][4] = c2;
                fjac[i][j][k][4][0] = (c2 * (u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * tmp2 - c1 * (u[i][j][k][4] * tmp1)) * (u[i][j][k][3] * tmp1);
                fjac[i][j][k][4][1] = - c2 * (u[i][j][k][1] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][4][2] = - c2 * (u[i][j][k][2] * u[i][j][k][3]) * tmp2;
                fjac[i][j][k][4][3] = c1 * (u[i][j][k][4] * tmp1) - 0.50 * c2 * ((u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + 3.0 * u[i][j][k][3] * u[i][j][k][3]) * tmp2);
                fjac[i][j][k][4][4] = c1 * u[i][j][k][3] * tmp1;
                njac[i][j][k][0][0] = 0.0;
                njac[i][j][k][0][1] = 0.0;
                njac[i][j][k][0][2] = 0.0;
                njac[i][j][k][0][3] = 0.0;
                njac[i][j][k][0][4] = 0.0;
                njac[i][j][k][1][0] = - c3c4 * tmp2 * u[i][j][k][1];
                njac[i][j][k][1][1] = c3c4 * tmp1;
                njac[i][j][k][1][2] = 0.0;
                njac[i][j][k][1][3] = 0.0;
                njac[i][j][k][1][4] = 0.0;
                njac[i][j][k][2][0] = - c3c4 * tmp2 * u[i][j][k][2];
                njac[i][j][k][2][1] = 0.0;
                njac[i][j][k][2][2] = c3c4 * tmp1;
                njac[i][j][k][2][3] = 0.0;
                njac[i][j][k][2][4] = 0.0;
                njac[i][j][k][3][0] = - con43 * c3c4 * tmp2 * u[i][j][k][3];
                njac[i][j][k][3][1] = 0.0;
                njac[i][j][k][3][2] = 0.0;
                njac[i][j][k][3][3] = con43 * c3 * c4 * tmp1;
                njac[i][j][k][3][4] = 0.0;
                njac[i][j][k][4][0] = - (c3c4 - c1345) * tmp3 * (((u[i][j][k][1]) * (u[i][j][k][1]))) - (c3c4 - c1345) * tmp3 * (((u[i][j][k][2]) * (u[i][j][k][2]))) - (con43 * c3c4 - c1345) * tmp3 * (((u[i][j][k][3]) * (u[i][j][k][3]))) - c1345 * tmp2 * u[i][j][k][4];
                njac[i][j][k][4][1] = (c3c4 - c1345) * tmp2 * u[i][j][k][1];
                njac[i][j][k][4][2] = (c3c4 - c1345) * tmp2 * u[i][j][k][2];
                njac[i][j][k][4][3] = (con43 * c3c4 - c1345) * tmp2 * u[i][j][k][3];
                njac[i][j][k][4][4] = (c1345) * tmp1;
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                tmp1 = dt * tz1;
                tmp2 = dt * tz2;
                lhs[i][j][k][0][0][0] = - tmp2 * fjac[i][j][k - 1][0][0] - tmp1 * njac[i][j][k - 1][0][0] - tmp1 * dz1;
                lhs[i][j][k][0][0][1] = - tmp2 * fjac[i][j][k - 1][0][1] - tmp1 * njac[i][j][k - 1][0][1];
                lhs[i][j][k][0][0][2] = - tmp2 * fjac[i][j][k - 1][0][2] - tmp1 * njac[i][j][k - 1][0][2];
                lhs[i][j][k][0][0][3] = - tmp2 * fjac[i][j][k - 1][0][3] - tmp1 * njac[i][j][k - 1][0][3];
                lhs[i][j][k][0][0][4] = - tmp2 * fjac[i][j][k - 1][0][4] - tmp1 * njac[i][j][k - 1][0][4];
                lhs[i][j][k][0][1][0] = - tmp2 * fjac[i][j][k - 1][1][0] - tmp1 * njac[i][j][k - 1][1][0];
                lhs[i][j][k][0][1][1] = - tmp2 * fjac[i][j][k - 1][1][1] - tmp1 * njac[i][j][k - 1][1][1] - tmp1 * dz2;
                lhs[i][j][k][0][1][2] = - tmp2 * fjac[i][j][k - 1][1][2] - tmp1 * njac[i][j][k - 1][1][2];
                lhs[i][j][k][0][1][3] = - tmp2 * fjac[i][j][k - 1][1][3] - tmp1 * njac[i][j][k - 1][1][3];
                lhs[i][j][k][0][1][4] = - tmp2 * fjac[i][j][k - 1][1][4] - tmp1 * njac[i][j][k - 1][1][4];
                lhs[i][j][k][0][2][0] = - tmp2 * fjac[i][j][k - 1][2][0] - tmp1 * njac[i][j][k - 1][2][0];
                lhs[i][j][k][0][2][1] = - tmp2 * fjac[i][j][k - 1][2][1] - tmp1 * njac[i][j][k - 1][2][1];
                lhs[i][j][k][0][2][2] = - tmp2 * fjac[i][j][k - 1][2][2] - tmp1 * njac[i][j][k - 1][2][2] - tmp1 * dz3;
                lhs[i][j][k][0][2][3] = - tmp2 * fjac[i][j][k - 1][2][3] - tmp1 * njac[i][j][k - 1][2][3];
                lhs[i][j][k][0][2][4] = - tmp2 * fjac[i][j][k - 1][2][4] - tmp1 * njac[i][j][k - 1][2][4];
                lhs[i][j][k][0][3][0] = - tmp2 * fjac[i][j][k - 1][3][0] - tmp1 * njac[i][j][k - 1][3][0];
                lhs[i][j][k][0][3][1] = - tmp2 * fjac[i][j][k - 1][3][1] - tmp1 * njac[i][j][k - 1][3][1];
                lhs[i][j][k][0][3][2] = - tmp2 * fjac[i][j][k - 1][3][2] - tmp1 * njac[i][j][k - 1][3][2];
                lhs[i][j][k][0][3][3] = - tmp2 * fjac[i][j][k - 1][3][3] - tmp1 * njac[i][j][k - 1][3][3] - tmp1 * dz4;
                lhs[i][j][k][0][3][4] = - tmp2 * fjac[i][j][k - 1][3][4] - tmp1 * njac[i][j][k - 1][3][4];
                lhs[i][j][k][0][4][0] = - tmp2 * fjac[i][j][k - 1][4][0] - tmp1 * njac[i][j][k - 1][4][0];
                lhs[i][j][k][0][4][1] = - tmp2 * fjac[i][j][k - 1][4][1] - tmp1 * njac[i][j][k - 1][4][1];
                lhs[i][j][k][0][4][2] = - tmp2 * fjac[i][j][k - 1][4][2] - tmp1 * njac[i][j][k - 1][4][2];
                lhs[i][j][k][0][4][3] = - tmp2 * fjac[i][j][k - 1][4][3] - tmp1 * njac[i][j][k - 1][4][3];
                lhs[i][j][k][0][4][4] = - tmp2 * fjac[i][j][k - 1][4][4] - tmp1 * njac[i][j][k - 1][4][4] - tmp1 * dz5;
                lhs[i][j][k][1][0][0] = 1.0 + tmp1 * 2.0 * njac[i][j][k][0][0] + tmp1 * 2.0 * dz1;
                lhs[i][j][k][1][0][1] = tmp1 * 2.0 * njac[i][j][k][0][1];
                lhs[i][j][k][1][0][2] = tmp1 * 2.0 * njac[i][j][k][0][2];
                lhs[i][j][k][1][0][3] = tmp1 * 2.0 * njac[i][j][k][0][3];
                lhs[i][j][k][1][0][4] = tmp1 * 2.0 * njac[i][j][k][0][4];
                lhs[i][j][k][1][1][0] = tmp1 * 2.0 * njac[i][j][k][1][0];
                lhs[i][j][k][1][1][1] = 1.0 + tmp1 * 2.0 * njac[i][j][k][1][1] + tmp1 * 2.0 * dz2;
                lhs[i][j][k][1][1][2] = tmp1 * 2.0 * njac[i][j][k][1][2];
                lhs[i][j][k][1][1][3] = tmp1 * 2.0 * njac[i][j][k][1][3];
                lhs[i][j][k][1][1][4] = tmp1 * 2.0 * njac[i][j][k][1][4];
                lhs[i][j][k][1][2][0] = tmp1 * 2.0 * njac[i][j][k][2][0];
                lhs[i][j][k][1][2][1] = tmp1 * 2.0 * njac[i][j][k][2][1];
                lhs[i][j][k][1][2][2] = 1.0 + tmp1 * 2.0 * njac[i][j][k][2][2] + tmp1 * 2.0 * dz3;
                lhs[i][j][k][1][2][3] = tmp1 * 2.0 * njac[i][j][k][2][3];
                lhs[i][j][k][1][2][4] = tmp1 * 2.0 * njac[i][j][k][2][4];
                lhs[i][j][k][1][3][0] = tmp1 * 2.0 * njac[i][j][k][3][0];
                lhs[i][j][k][1][3][1] = tmp1 * 2.0 * njac[i][j][k][3][1];
                lhs[i][j][k][1][3][2] = tmp1 * 2.0 * njac[i][j][k][3][2];
                lhs[i][j][k][1][3][3] = 1.0 + tmp1 * 2.0 * njac[i][j][k][3][3] + tmp1 * 2.0 * dz4;
                lhs[i][j][k][1][3][4] = tmp1 * 2.0 * njac[i][j][k][3][4];
                lhs[i][j][k][1][4][0] = tmp1 * 2.0 * njac[i][j][k][4][0];
                lhs[i][j][k][1][4][1] = tmp1 * 2.0 * njac[i][j][k][4][1];
                lhs[i][j][k][1][4][2] = tmp1 * 2.0 * njac[i][j][k][4][2];
                lhs[i][j][k][1][4][3] = tmp1 * 2.0 * njac[i][j][k][4][3];
                lhs[i][j][k][1][4][4] = 1.0 + tmp1 * 2.0 * njac[i][j][k][4][4] + tmp1 * 2.0 * dz5;
                lhs[i][j][k][2][0][0] = tmp2 * fjac[i][j][k + 1][0][0] - tmp1 * njac[i][j][k + 1][0][0] - tmp1 * dz1;
                lhs[i][j][k][2][0][1] = tmp2 * fjac[i][j][k + 1][0][1] - tmp1 * njac[i][j][k + 1][0][1];
                lhs[i][j][k][2][0][2] = tmp2 * fjac[i][j][k + 1][0][2] - tmp1 * njac[i][j][k + 1][0][2];
                lhs[i][j][k][2][0][3] = tmp2 * fjac[i][j][k + 1][0][3] - tmp1 * njac[i][j][k + 1][0][3];
                lhs[i][j][k][2][0][4] = tmp2 * fjac[i][j][k + 1][0][4] - tmp1 * njac[i][j][k + 1][0][4];
                lhs[i][j][k][2][1][0] = tmp2 * fjac[i][j][k + 1][1][0] - tmp1 * njac[i][j][k + 1][1][0];
                lhs[i][j][k][2][1][1] = tmp2 * fjac[i][j][k + 1][1][1] - tmp1 * njac[i][j][k + 1][1][1] - tmp1 * dz2;
                lhs[i][j][k][2][1][2] = tmp2 * fjac[i][j][k + 1][1][2] - tmp1 * njac[i][j][k + 1][1][2];
                lhs[i][j][k][2][1][3] = tmp2 * fjac[i][j][k + 1][1][3] - tmp1 * njac[i][j][k + 1][1][3];
                lhs[i][j][k][2][1][4] = tmp2 * fjac[i][j][k + 1][1][4] - tmp1 * njac[i][j][k + 1][1][4];
                lhs[i][j][k][2][2][0] = tmp2 * fjac[i][j][k + 1][2][0] - tmp1 * njac[i][j][k + 1][2][0];
                lhs[i][j][k][2][2][1] = tmp2 * fjac[i][j][k + 1][2][1] - tmp1 * njac[i][j][k + 1][2][1];
                lhs[i][j][k][2][2][2] = tmp2 * fjac[i][j][k + 1][2][2] - tmp1 * njac[i][j][k + 1][2][2] - tmp1 * dz3;
                lhs[i][j][k][2][2][3] = tmp2 * fjac[i][j][k + 1][2][3] - tmp1 * njac[i][j][k + 1][2][3];
                lhs[i][j][k][2][2][4] = tmp2 * fjac[i][j][k + 1][2][4] - tmp1 * njac[i][j][k + 1][2][4];
                lhs[i][j][k][2][3][0] = tmp2 * fjac[i][j][k + 1][3][0] - tmp1 * njac[i][j][k + 1][3][0];
                lhs[i][j][k][2][3][1] = tmp2 * fjac[i][j][k + 1][3][1] - tmp1 * njac[i][j][k + 1][3][1];
                lhs[i][j][k][2][3][2] = tmp2 * fjac[i][j][k + 1][3][2] - tmp1 * njac[i][j][k + 1][3][2];
                lhs[i][j][k][2][3][3] = tmp2 * fjac[i][j][k + 1][3][3] - tmp1 * njac[i][j][k + 1][3][3] - tmp1 * dz4;
                lhs[i][j][k][2][3][4] = tmp2 * fjac[i][j][k + 1][3][4] - tmp1 * njac[i][j][k + 1][3][4];
                lhs[i][j][k][2][4][0] = tmp2 * fjac[i][j][k + 1][4][0] - tmp1 * njac[i][j][k + 1][4][0];
                lhs[i][j][k][2][4][1] = tmp2 * fjac[i][j][k + 1][4][1] - tmp1 * njac[i][j][k + 1][4][1];
                lhs[i][j][k][2][4][2] = tmp2 * fjac[i][j][k + 1][4][2] - tmp1 * njac[i][j][k + 1][4][2];
                lhs[i][j][k][2][4][3] = tmp2 * fjac[i][j][k + 1][4][3] - tmp1 * njac[i][j][k + 1][4][3];
                lhs[i][j][k][2][4][4] = tmp2 * fjac[i][j][k + 1][4][4] - tmp1 * njac[i][j][k + 1][4][4] - tmp1 * dz5;
            }
        }
    }
}
static void compute_rhs(void)
{
    int i, j, k, m;
    double rho_inv, uijk, up1, um1, vijk, vp1, vm1, wijk, wp1, wm1;
#pragma omp for nowait
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                rho_inv = 1.0 / u[i][j][k][0];
                rho_i[i][j][k] = rho_inv;
                us[i][j][k] = u[i][j][k][1] * rho_inv;
                vs[i][j][k] = u[i][j][k][2] * rho_inv;
                ws[i][j][k] = u[i][j][k][3] * rho_inv;
                square[i][j][k] = 0.5 * (u[i][j][k][1] * u[i][j][k][1] + u[i][j][k][2] * u[i][j][k][2] + u[i][j][k][3] * u[i][j][k][3]) * rho_inv;
                qs[i][j][k] = square[i][j][k] * rho_inv;
            }
        }
    }
#pragma omp for 
    for (i = 0;
        i < grid_points[0];
        i++)
    {
        for (j = 0;
            j < grid_points[1];
            j++)
        {
            for (k = 0;
                k < grid_points[2];
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    rhs[i][j][k][m] = forcing[i][j][k][m];
                }
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                uijk = us[i][j][k];
                up1 = us[i + 1][j][k];
                um1 = us[i - 1][j][k];
                rhs[i][j][k][0] = rhs[i][j][k][0] + dx1tx1 * (u[i + 1][j][k][0] - 2.0 * u[i][j][k][0] + u[i - 1][j][k][0]) - tx2 * (u[i + 1][j][k][1] - u[i - 1][j][k][1]);
                rhs[i][j][k][1] = rhs[i][j][k][1] + dx2tx1 * (u[i + 1][j][k][1] - 2.0 * u[i][j][k][1] + u[i - 1][j][k][1]) + xxcon2 * con43 * (up1 - 2.0 * uijk + um1) - tx2 * (u[i + 1][j][k][1] * up1 - u[i - 1][j][k][1] * um1 + (u[i + 1][j][k][4] - square[i + 1][j][k] - u[i - 1][j][k][4] + square[i - 1][j][k]) * c2);
                rhs[i][j][k][2] = rhs[i][j][k][2] + dx3tx1 * (u[i + 1][j][k][2] - 2.0 * u[i][j][k][2] + u[i - 1][j][k][2]) + xxcon2 * (vs[i + 1][j][k] - 2.0 * vs[i][j][k] + vs[i - 1][j][k]) - tx2 * (u[i + 1][j][k][2] * up1 - u[i - 1][j][k][2] * um1);
                rhs[i][j][k][3] = rhs[i][j][k][3] + dx4tx1 * (u[i + 1][j][k][3] - 2.0 * u[i][j][k][3] + u[i - 1][j][k][3]) + xxcon2 * (ws[i + 1][j][k] - 2.0 * ws[i][j][k] + ws[i - 1][j][k]) - tx2 * (u[i + 1][j][k][3] * up1 - u[i - 1][j][k][3] * um1);
                rhs[i][j][k][4] = rhs[i][j][k][4] + dx5tx1 * (u[i + 1][j][k][4] - 2.0 * u[i][j][k][4] + u[i - 1][j][k][4]) + xxcon3 * (qs[i + 1][j][k] - 2.0 * qs[i][j][k] + qs[i - 1][j][k]) + xxcon4 * (up1 * up1 - 2.0 * uijk * uijk + um1 * um1) + xxcon5 * (u[i + 1][j][k][4] * rho_i[i + 1][j][k] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i - 1][j][k][4] * rho_i[i - 1][j][k]) - tx2 * ((c1 * u[i + 1][j][k][4] - c2 * square[i + 1][j][k]) * up1 - (c1 * u[i - 1][j][k][4] - c2 * square[i - 1][j][k]) * um1);
            }
        }
    }
    i = 1;
#pragma omp for nowait
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (5.0 * u[i][j][k][m] - 4.0 * u[i + 1][j][k][m] + u[i + 2][j][k][m]);
            }
        }
    }
    i = 2;
#pragma omp for nowait
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (- 4.0 * u[i - 1][j][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i + 1][j][k][m] + u[i + 2][j][k][m]);
            }
        }
    }
#pragma omp for nowait
    for (i = 3;
        i < grid_points[0] - 3;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i - 2][j][k][m] - 4.0 * u[i - 1][j][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i + 1][j][k][m] + u[i + 2][j][k][m]);
                }
            }
        }
    }
    i = grid_points[0] - 3;
#pragma omp for nowait
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i - 2][j][k][m] - 4.0 * u[i - 1][j][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i + 1][j][k][m]);
            }
        }
    }
    i = grid_points[0] - 2;
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i - 2][j][k][m] - 4. * u[i - 1][j][k][m] + 5.0 * u[i][j][k][m]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                vijk = vs[i][j][k];
                vp1 = vs[i][j + 1][k];
                vm1 = vs[i][j - 1][k];
                rhs[i][j][k][0] = rhs[i][j][k][0] + dy1ty1 * (u[i][j + 1][k][0] - 2.0 * u[i][j][k][0] + u[i][j - 1][k][0]) - ty2 * (u[i][j + 1][k][2] - u[i][j - 1][k][2]);
                rhs[i][j][k][1] = rhs[i][j][k][1] + dy2ty1 * (u[i][j + 1][k][1] - 2.0 * u[i][j][k][1] + u[i][j - 1][k][1]) + yycon2 * (us[i][j + 1][k] - 2.0 * us[i][j][k] + us[i][j - 1][k]) - ty2 * (u[i][j + 1][k][1] * vp1 - u[i][j - 1][k][1] * vm1);
                rhs[i][j][k][2] = rhs[i][j][k][2] + dy3ty1 * (u[i][j + 1][k][2] - 2.0 * u[i][j][k][2] + u[i][j - 1][k][2]) + yycon2 * con43 * (vp1 - 2.0 * vijk + vm1) - ty2 * (u[i][j + 1][k][2] * vp1 - u[i][j - 1][k][2] * vm1 + (u[i][j + 1][k][4] - square[i][j + 1][k] - u[i][j - 1][k][4] + square[i][j - 1][k]) * c2);
                rhs[i][j][k][3] = rhs[i][j][k][3] + dy4ty1 * (u[i][j + 1][k][3] - 2.0 * u[i][j][k][3] + u[i][j - 1][k][3]) + yycon2 * (ws[i][j + 1][k] - 2.0 * ws[i][j][k] + ws[i][j - 1][k]) - ty2 * (u[i][j + 1][k][3] * vp1 - u[i][j - 1][k][3] * vm1);
                rhs[i][j][k][4] = rhs[i][j][k][4] + dy5ty1 * (u[i][j + 1][k][4] - 2.0 * u[i][j][k][4] + u[i][j - 1][k][4]) + yycon3 * (qs[i][j + 1][k] - 2.0 * qs[i][j][k] + qs[i][j - 1][k]) + yycon4 * (vp1 * vp1 - 2.0 * vijk * vijk + vm1 * vm1) + yycon5 * (u[i][j + 1][k][4] * rho_i[i][j + 1][k] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i][j - 1][k][4] * rho_i[i][j - 1][k]) - ty2 * ((c1 * u[i][j + 1][k][4] - c2 * square[i][j + 1][k]) * vp1 - (c1 * u[i][j - 1][k][4] - c2 * square[i][j - 1][k]) * vm1);
            }
        }
    }
    j = 1;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (5.0 * u[i][j][k][m] - 4.0 * u[i][j + 1][k][m] + u[i][j + 2][k][m]);
            }
        }
    }
    j = 2;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (- 4.0 * u[i][j - 1][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j + 1][k][m] + u[i][j + 2][k][m]);
            }
        }
    }
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 3;
            j < grid_points[1] - 3;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j - 2][k][m] - 4.0 * u[i][j - 1][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j + 1][k][m] + u[i][j + 2][k][m]);
                }
            }
        }
    }
    j = grid_points[1] - 3;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j - 2][k][m] - 4.0 * u[i][j - 1][k][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j + 1][k][m]);
            }
        }
    }
    j = grid_points[1] - 2;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j - 2][k][m] - 4. * u[i][j - 1][k][m] + 5. * u[i][j][k][m]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                wijk = ws[i][j][k];
                wp1 = ws[i][j][k + 1];
                wm1 = ws[i][j][k - 1];
                rhs[i][j][k][0] = rhs[i][j][k][0] + dz1tz1 * (u[i][j][k + 1][0] - 2.0 * u[i][j][k][0] + u[i][j][k - 1][0]) - tz2 * (u[i][j][k + 1][3] - u[i][j][k - 1][3]);
                rhs[i][j][k][1] = rhs[i][j][k][1] + dz2tz1 * (u[i][j][k + 1][1] - 2.0 * u[i][j][k][1] + u[i][j][k - 1][1]) + zzcon2 * (us[i][j][k + 1] - 2.0 * us[i][j][k] + us[i][j][k - 1]) - tz2 * (u[i][j][k + 1][1] * wp1 - u[i][j][k - 1][1] * wm1);
                rhs[i][j][k][2] = rhs[i][j][k][2] + dz3tz1 * (u[i][j][k + 1][2] - 2.0 * u[i][j][k][2] + u[i][j][k - 1][2]) + zzcon2 * (vs[i][j][k + 1] - 2.0 * vs[i][j][k] + vs[i][j][k - 1]) - tz2 * (u[i][j][k + 1][2] * wp1 - u[i][j][k - 1][2] * wm1);
                rhs[i][j][k][3] = rhs[i][j][k][3] + dz4tz1 * (u[i][j][k + 1][3] - 2.0 * u[i][j][k][3] + u[i][j][k - 1][3]) + zzcon2 * con43 * (wp1 - 2.0 * wijk + wm1) - tz2 * (u[i][j][k + 1][3] * wp1 - u[i][j][k - 1][3] * wm1 + (u[i][j][k + 1][4] - square[i][j][k + 1] - u[i][j][k - 1][4] + square[i][j][k - 1]) * c2);
                rhs[i][j][k][4] = rhs[i][j][k][4] + dz5tz1 * (u[i][j][k + 1][4] - 2.0 * u[i][j][k][4] + u[i][j][k - 1][4]) + zzcon3 * (qs[i][j][k + 1] - 2.0 * qs[i][j][k] + qs[i][j][k - 1]) + zzcon4 * (wp1 * wp1 - 2.0 * wijk * wijk + wm1 * wm1) + zzcon5 * (u[i][j][k + 1][4] * rho_i[i][j][k + 1] - 2.0 * u[i][j][k][4] * rho_i[i][j][k] + u[i][j][k - 1][4] * rho_i[i][j][k - 1]) - tz2 * ((c1 * u[i][j][k + 1][4] - c2 * square[i][j][k + 1]) * wp1 - (c1 * u[i][j][k - 1][4] - c2 * square[i][j][k - 1]) * wm1);
            }
        }
    }
    k = 1;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (5.0 * u[i][j][k][m] - 4.0 * u[i][j][k + 1][m] + u[i][j][k + 2][m]);
            }
        }
    }
    k = 2;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (- 4.0 * u[i][j][k - 1][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j][k + 1][m] + u[i][j][k + 2][m]);
            }
        }
    }
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 3;
                k < grid_points[2] - 3;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j][k - 2][m] - 4.0 * u[i][j][k - 1][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j][k + 1][m] + u[i][j][k + 2][m]);
                }
            }
        }
    }
    k = grid_points[2] - 3;
#pragma omp for nowait
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j][k - 2][m] - 4.0 * u[i][j][k - 1][m] + 6.0 * u[i][j][k][m] - 4.0 * u[i][j][k + 1][m]);
            }
        }
    }
    k = grid_points[2] - 2;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                rhs[i][j][k][m] = rhs[i][j][k][m] - dssp * (u[i][j][k - 2][m] - 4.0 * u[i][j][k - 1][m] + 5.0 * u[i][j][k][m]);
            }
        }
    }
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            for (m = 0;
                m < 5;
                m++)
            {
                for (i = 1;
                    i < grid_points[0] - 1;
                    i++)
                {
                    rhs[i][j][k][m] = rhs[i][j][k][m] * dt;
                }
            }
        }
    }
}
static void set_constants(void)
{
    ce[0][0] = 2.0;
    ce[0][1] = 0.0;
    ce[0][2] = 0.0;
    ce[0][3] = 4.0;
    ce[0][4] = 5.0;
    ce[0][5] = 3.0;
    ce[0][6] = 0.5;
    ce[0][7] = 0.02;
    ce[0][8] = 0.01;
    ce[0][9] = 0.03;
    ce[0][10] = 0.5;
    ce[0][11] = 0.4;
    ce[0][12] = 0.3;
    ce[1][0] = 1.0;
    ce[1][1] = 0.0;
    ce[1][2] = 0.0;
    ce[1][3] = 0.0;
    ce[1][4] = 1.0;
    ce[1][5] = 2.0;
    ce[1][6] = 3.0;
    ce[1][7] = 0.01;
    ce[1][8] = 0.03;
    ce[1][9] = 0.02;
    ce[1][10] = 0.4;
    ce[1][11] = 0.3;
    ce[1][12] = 0.5;
    ce[2][0] = 2.0;
    ce[2][1] = 2.0;
    ce[2][2] = 0.0;
    ce[2][3] = 0.0;
    ce[2][4] = 0.0;
    ce[2][5] = 2.0;
    ce[2][6] = 3.0;
    ce[2][7] = 0.04;
    ce[2][8] = 0.03;
    ce[2][9] = 0.05;
    ce[2][10] = 0.3;
    ce[2][11] = 0.5;
    ce[2][12] = 0.4;
    ce[3][0] = 2.0;
    ce[3][1] = 2.0;
    ce[3][2] = 0.0;
    ce[3][3] = 0.0;
    ce[3][4] = 0.0;
    ce[3][5] = 2.0;
    ce[3][6] = 3.0;
    ce[3][7] = 0.03;
    ce[3][8] = 0.05;
    ce[3][9] = 0.04;
    ce[3][10] = 0.2;
    ce[3][11] = 0.1;
    ce[3][12] = 0.3;
    ce[4][0] = 5.0;
    ce[4][1] = 4.0;
    ce[4][2] = 3.0;
    ce[4][3] = 2.0;
    ce[4][4] = 0.1;
    ce[4][5] = 0.4;
    ce[4][6] = 0.3;
    ce[4][7] = 0.05;
    ce[4][8] = 0.04;
    ce[4][9] = 0.03;
    ce[4][10] = 0.1;
    ce[4][11] = 0.3;
    ce[4][12] = 0.2;
    c1 = 1.4;
    c2 = 0.4;
    c3 = 0.1;
    c4 = 1.0;
    c5 = 1.4;
    dnxm1 = 1.0 / (double) (grid_points[0] - 1);
    dnym1 = 1.0 / (double) (grid_points[1] - 1);
    dnzm1 = 1.0 / (double) (grid_points[2] - 1);
    c1c2 = c1 * c2;
    c1c5 = c1 * c5;
    c3c4 = c3 * c4;
    c1345 = c1c5 * c3c4;
    conz1 = (1.0 - c1c5);
    tx1 = 1.0 / (dnxm1 * dnxm1);
    tx2 = 1.0 / (2.0 * dnxm1);
    tx3 = 1.0 / dnxm1;
    ty1 = 1.0 / (dnym1 * dnym1);
    ty2 = 1.0 / (2.0 * dnym1);
    ty3 = 1.0 / dnym1;
    tz1 = 1.0 / (dnzm1 * dnzm1);
    tz2 = 1.0 / (2.0 * dnzm1);
    tz3 = 1.0 / dnzm1;
    dx1 = 0.75;
    dx2 = 0.75;
    dx3 = 0.75;
    dx4 = 0.75;
    dx5 = 0.75;
    dy1 = 0.75;
    dy2 = 0.75;
    dy3 = 0.75;
    dy4 = 0.75;
    dy5 = 0.75;
    dz1 = 1.0;
    dz2 = 1.0;
    dz3 = 1.0;
    dz4 = 1.0;
    dz5 = 1.0;
    dxmax = (((dx3) > (dx4)) ? (dx3) : (dx4));
    dymax = (((dy2) > (dy4)) ? (dy2) : (dy4));
    dzmax = (((dz2) > (dz3)) ? (dz2) : (dz3));
    dssp = 0.25 * (((dx1) > ((((dy1) > (dz1)) ? (dy1) : (dz1)))) ? (dx1) : ((((dy1) > (dz1)) ? (dy1) : (dz1))));
    c4dssp = 4.0 * dssp;
    c5dssp = 5.0 * dssp;
    dttx1 = dt * tx1;
    dttx2 = dt * tx2;
    dtty1 = dt * ty1;
    dtty2 = dt * ty2;
    dttz1 = dt * tz1;
    dttz2 = dt * tz2;
    c2dttx1 = 2.0 * dttx1;
    c2dtty1 = 2.0 * dtty1;
    c2dttz1 = 2.0 * dttz1;
    dtdssp = dt * dssp;
    comz1 = dtdssp;
    comz4 = 4.0 * dtdssp;
    comz5 = 5.0 * dtdssp;
    comz6 = 6.0 * dtdssp;
    c3c4tx3 = c3c4 * tx3;
    c3c4ty3 = c3c4 * ty3;
    c3c4tz3 = c3c4 * tz3;
    dx1tx1 = dx1 * tx1;
    dx2tx1 = dx2 * tx1;
    dx3tx1 = dx3 * tx1;
    dx4tx1 = dx4 * tx1;
    dx5tx1 = dx5 * tx1;
    dy1ty1 = dy1 * ty1;
    dy2ty1 = dy2 * ty1;
    dy3ty1 = dy3 * ty1;
    dy4ty1 = dy4 * ty1;
    dy5ty1 = dy5 * ty1;
    dz1tz1 = dz1 * tz1;
    dz2tz1 = dz2 * tz1;
    dz3tz1 = dz3 * tz1;
    dz4tz1 = dz4 * tz1;
    dz5tz1 = dz5 * tz1;
    c2iv = 2.5;
    con43 = 4.0 / 3.0;
    con16 = 1.0 / 6.0;
    xxcon1 = c3c4tx3 * con43 * tx3;
    xxcon2 = c3c4tx3 * tx3;
    xxcon3 = c3c4tx3 * conz1 * tx3;
    xxcon4 = c3c4tx3 * con16 * tx3;
    xxcon5 = c3c4tx3 * c1c5 * tx3;
    yycon1 = c3c4ty3 * con43 * ty3;
    yycon2 = c3c4ty3 * ty3;
    yycon3 = c3c4ty3 * conz1 * ty3;
    yycon4 = c3c4ty3 * con16 * ty3;
    yycon5 = c3c4ty3 * c1c5 * ty3;
    zzcon1 = c3c4tz3 * con43 * tz3;
    zzcon2 = c3c4tz3 * tz3;
    zzcon3 = c3c4tz3 * conz1 * tz3;
    zzcon4 = c3c4tz3 * con16 * tz3;
    zzcon5 = c3c4tz3 * c1c5 * tz3;
}
static void verify(int no_time_steps, char *class, boolean *verified)
{
    double xcrref[5], xceref[5], xcrdif[5], xcedif[5], epsilon, xce[5], xcr[5], dtref;
    int m;
    epsilon = 1.0e-08;
    error_norm(xce);
    compute_rhs();
    rhs_norm(xcr);
    for (m = 0;
        m < 5;
        m++)
    {
        xcr[m] = xcr[m] / dt;
    }
    *class = 'U';
    *verified = 1;
    for (m = 0;
        m < 5;
        m++)
    {
        xcrref[m] = 1.0;
        xceref[m] = 1.0;
    }
    if (grid_points[0] == 12 && grid_points[1] == 12 && grid_points[2] == 12 && no_time_steps == 60)
    {
        *class = 'S';
        dtref = 1.0e-2;
        xcrref[0] = 1.7034283709541311e-01;
        xcrref[1] = 1.2975252070034097e-02;
        xcrref[2] = 3.2527926989486055e-02;
        xcrref[3] = 2.6436421275166801e-02;
        xcrref[4] = 1.9211784131744430e-01;
        xceref[0] = 4.9976913345811579e-04;
        xceref[1] = 4.5195666782961927e-05;
        xceref[2] = 7.3973765172921357e-05;
        xceref[3] = 7.3821238632439731e-05;
        xceref[4] = 8.9269630987491446e-04;
    }
    else
        if (grid_points[0] == 24 && grid_points[1] == 24 && grid_points[2] == 24 && no_time_steps == 200)
        {
            *class = 'W';
            dtref = 0.8e-3;
            xcrref[0] = 0.1125590409344e+03;
            xcrref[1] = 0.1180007595731e+02;
            xcrref[2] = 0.2710329767846e+02;
            xcrref[3] = 0.2469174937669e+02;
            xcrref[4] = 0.2638427874317e+03;
            xceref[0] = 0.4419655736008e+01;
            xceref[1] = 0.4638531260002e+00;
            xceref[2] = 0.1011551749967e+01;
            xceref[3] = 0.9235878729944e+00;
            xceref[4] = 0.1018045837718e+02;
        }
        else
            if (grid_points[0] == 64 && grid_points[1] == 64 && grid_points[2] == 64 && no_time_steps == 200)
            {
                *class = 'A';
                dtref = 0.8e-3;
                xcrref[0] = 1.0806346714637264e+02;
                xcrref[1] = 1.1319730901220813e+01;
                xcrref[2] = 2.5974354511582465e+01;
                xcrref[3] = 2.3665622544678910e+01;
                xcrref[4] = 2.5278963211748344e+02;
                xceref[0] = 4.2348416040525025e+00;
                xceref[1] = 4.4390282496995698e-01;
                xceref[2] = 9.6692480136345650e-01;
                xceref[3] = 8.8302063039765474e-01;
                xceref[4] = 9.7379901770829278e+00;
            }
            else
                if (grid_points[0] == 102 && grid_points[1] == 102 && grid_points[2] == 102 && no_time_steps == 200)
                {
                    *class = 'B';
                    dtref = 3.0e-4;
                    xcrref[0] = 1.4233597229287254e+03;
                    xcrref[1] = 9.9330522590150238e+01;
                    xcrref[2] = 3.5646025644535285e+02;
                    xcrref[3] = 3.2485447959084092e+02;
                    xcrref[4] = 3.2707541254659363e+03;
                    xceref[0] = 5.2969847140936856e+01;
                    xceref[1] = 4.4632896115670668e+00;
                    xceref[2] = 1.3122573342210174e+01;
                    xceref[3] = 1.2006925323559144e+01;
                    xceref[4] = 1.2459576151035986e+02;
                }
                else
                    if (grid_points[0] == 162 && grid_points[1] == 162 && grid_points[2] == 162 && no_time_steps == 200)
                    {
                        *class = 'C';
                        dtref = 1.0e-4;
                        xcrref[0] = 0.62398116551764615e+04;
                        xcrref[1] = 0.50793239190423964e+03;
                        xcrref[2] = 0.15423530093013596e+04;
                        xcrref[3] = 0.13302387929291190e+04;
                        xcrref[4] = 0.11604087428436455e+05;
                        xceref[0] = 0.16462008369091265e+03;
                        xceref[1] = 0.11497107903824313e+02;
                        xceref[2] = 0.41207446207461508e+02;
                        xceref[3] = 0.37087651059694167e+02;
                        xceref[4] = 0.36211053051841265e+03;
                    }
                    else
                    {
                        *verified = 0;
                    }
    for (m = 0;
        m < 5;
        m++)
    {
        xcrdif[m] = fabs((xcr[m] - xcrref[m]) / xcrref[m]);
        xcedif[m] = fabs((xce[m] - xceref[m]) / xceref[m]);
    }
    if (*class != 'U')
    {
        printf(" Verification being performed for class %1c\n", *class);
        printf(" accuracy setting for epsilon = %20.13e\n", epsilon);
        if (fabs(dt - dtref) > epsilon)
        {
            *verified = 0;
            *class = 'U';
            printf(" DT does not match the reference value of %15.8e\n", dtref);
        }
    }
    else
    {
        printf(" Unknown class\n");
    }
    if (*class != 'U')
    {
        printf(" Comparison of RMS-norms of residual\n");
    }
    else
    {
        printf(" RMS-norms of residual\n");
    }
    for (m = 0;
        m < 5;
        m++)
    {
        if (*class == 'U')
        {
            printf("          %2d%20.13e\n", m, xcr[m]);
        }
        else
            if (xcrdif[m] > epsilon)
            {
                *verified = 0;
                printf(" FAILURE: %2d%20.13e%20.13e%20.13e\n", m, xcr[m], xcrref[m], xcrdif[m]);
            }
            else
            {
                printf("          %2d%20.13e%20.13e%20.13e\n", m, xcr[m], xcrref[m], xcrdif[m]);
            }
    }
    if (*class != 'U')
    {
        printf(" Comparison of RMS-norms of solution error\n");
    }
    else
    {
        printf(" RMS-norms of solution error\n");
    }
    for (m = 0;
        m < 5;
        m++)
    {
        if (*class == 'U')
        {
            printf("          %2d%20.13e\n", m, xce[m]);
        }
        else
            if (xcedif[m] > epsilon)
            {
                *verified = 0;
                printf(" FAILURE: %2d%20.13e%20.13e%20.13e\n", m, xce[m], xceref[m], xcedif[m]);
            }
            else
            {
                printf("          %2d%20.13e%20.13e%20.13e\n", m, xce[m], xceref[m], xcedif[m]);
            }
    }
    if (*class == 'U')
    {
        printf(" No reference values provided\n");
        printf(" No verification performed\n");
    }
    else
        if (*verified == 1)
        {
            printf(" Verification Successful\n");
        }
        else
        {
            printf(" Verification failed\n");
        }
}
static void x_solve(void)
{
    lhsx();
    x_solve_cell();
    x_backsubstitute();
}
static void x_backsubstitute(void)
{
    int i, j, k, m, n;
    for (i = grid_points[0] - 2;
        i >= 0;
        i--)
    {
#pragma omp for 
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    for (n = 0;
                        n < 5;
                        n++)
                    {
                        rhs[i][j][k][m] = rhs[i][j][k][m] - lhs[i][j][k][2][m][n] * rhs[i + 1][j][k][n];
                    }
                }
            }
        }
    }
}
static void x_solve_cell(void)
{
    int i, j, k, isize;
    isize = grid_points[0] - 1;
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            binvcrhs(lhs[0][j][k][1], lhs[0][j][k][2], rhs[0][j][k]);
        }
    }
    for (i = 1;
        i < isize;
        i++)
    {
#pragma omp for 
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                matvec_sub(lhs[i][j][k][0], rhs[i - 1][j][k], rhs[i][j][k]);
                matmul_sub(lhs[i][j][k][0], lhs[i - 1][j][k][2], lhs[i][j][k][1]);
                binvcrhs(lhs[i][j][k][1], lhs[i][j][k][2], rhs[i][j][k]);
            }
        }
    }
#pragma omp for 
    for (j = 1;
        j < grid_points[1] - 1;
        j++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            matvec_sub(lhs[isize][j][k][0], rhs[isize - 1][j][k], rhs[isize][j][k]);
            matmul_sub(lhs[isize][j][k][0], lhs[isize - 1][j][k][2], lhs[isize][j][k][1]);
            binvrhs(lhs[i][j][k][1], rhs[i][j][k]);
        }
    }
}
static void matvec_sub(double ablock[5][5], double avec[5], double bvec[5])
{
    int i;
    for (i = 0;
        i < 5;
        i++)
    {
        bvec[i] = bvec[i] - ablock[i][0] * avec[0] - ablock[i][1] * avec[1] - ablock[i][2] * avec[2] - ablock[i][3] * avec[3] - ablock[i][4] * avec[4];
    }
}
static void matmul_sub(double ablock[5][5], double bblock[5][5], double cblock[5][5])
{
    int j;
    for (j = 0;
        j < 5;
        j++)
    {
        cblock[0][j] = cblock[0][j] - ablock[0][0] * bblock[0][j] - ablock[0][1] * bblock[1][j] - ablock[0][2] * bblock[2][j] - ablock[0][3] * bblock[3][j] - ablock[0][4] * bblock[4][j];
        cblock[1][j] = cblock[1][j] - ablock[1][0] * bblock[0][j] - ablock[1][1] * bblock[1][j] - ablock[1][2] * bblock[2][j] - ablock[1][3] * bblock[3][j] - ablock[1][4] * bblock[4][j];
        cblock[2][j] = cblock[2][j] - ablock[2][0] * bblock[0][j] - ablock[2][1] * bblock[1][j] - ablock[2][2] * bblock[2][j] - ablock[2][3] * bblock[3][j] - ablock[2][4] * bblock[4][j];
        cblock[3][j] = cblock[3][j] - ablock[3][0] * bblock[0][j] - ablock[3][1] * bblock[1][j] - ablock[3][2] * bblock[2][j] - ablock[3][3] * bblock[3][j] - ablock[3][4] * bblock[4][j];
        cblock[4][j] = cblock[4][j] - ablock[4][0] * bblock[0][j] - ablock[4][1] * bblock[1][j] - ablock[4][2] * bblock[2][j] - ablock[4][3] * bblock[3][j] - ablock[4][4] * bblock[4][j];
    }
}
static void binvcrhs(double lhs[5][5], double c[5][5], double r[5])
{
    double pivot, coeff;
    pivot = 1.00 / lhs[0][0];
    lhs[0][1] = lhs[0][1] * pivot;
    lhs[0][2] = lhs[0][2] * pivot;
    lhs[0][3] = lhs[0][3] * pivot;
    lhs[0][4] = lhs[0][4] * pivot;
    c[0][0] = c[0][0] * pivot;
    c[0][1] = c[0][1] * pivot;
    c[0][2] = c[0][2] * pivot;
    c[0][3] = c[0][3] * pivot;
    c[0][4] = c[0][4] * pivot;
    r[0] = r[0] * pivot;
    coeff = lhs[1][0];
    lhs[1][1] = lhs[1][1] - coeff * lhs[0][1];
    lhs[1][2] = lhs[1][2] - coeff * lhs[0][2];
    lhs[1][3] = lhs[1][3] - coeff * lhs[0][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[0][4];
    c[1][0] = c[1][0] - coeff * c[0][0];
    c[1][1] = c[1][1] - coeff * c[0][1];
    c[1][2] = c[1][2] - coeff * c[0][2];
    c[1][3] = c[1][3] - coeff * c[0][3];
    c[1][4] = c[1][4] - coeff * c[0][4];
    r[1] = r[1] - coeff * r[0];
    coeff = lhs[2][0];
    lhs[2][1] = lhs[2][1] - coeff * lhs[0][1];
    lhs[2][2] = lhs[2][2] - coeff * lhs[0][2];
    lhs[2][3] = lhs[2][3] - coeff * lhs[0][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[0][4];
    c[2][0] = c[2][0] - coeff * c[0][0];
    c[2][1] = c[2][1] - coeff * c[0][1];
    c[2][2] = c[2][2] - coeff * c[0][2];
    c[2][3] = c[2][3] - coeff * c[0][3];
    c[2][4] = c[2][4] - coeff * c[0][4];
    r[2] = r[2] - coeff * r[0];
    coeff = lhs[3][0];
    lhs[3][1] = lhs[3][1] - coeff * lhs[0][1];
    lhs[3][2] = lhs[3][2] - coeff * lhs[0][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[0][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[0][4];
    c[3][0] = c[3][0] - coeff * c[0][0];
    c[3][1] = c[3][1] - coeff * c[0][1];
    c[3][2] = c[3][2] - coeff * c[0][2];
    c[3][3] = c[3][3] - coeff * c[0][3];
    c[3][4] = c[3][4] - coeff * c[0][4];
    r[3] = r[3] - coeff * r[0];
    coeff = lhs[4][0];
    lhs[4][1] = lhs[4][1] - coeff * lhs[0][1];
    lhs[4][2] = lhs[4][2] - coeff * lhs[0][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[0][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[0][4];
    c[4][0] = c[4][0] - coeff * c[0][0];
    c[4][1] = c[4][1] - coeff * c[0][1];
    c[4][2] = c[4][2] - coeff * c[0][2];
    c[4][3] = c[4][3] - coeff * c[0][3];
    c[4][4] = c[4][4] - coeff * c[0][4];
    r[4] = r[4] - coeff * r[0];
    pivot = 1.00 / lhs[1][1];
    lhs[1][2] = lhs[1][2] * pivot;
    lhs[1][3] = lhs[1][3] * pivot;
    lhs[1][4] = lhs[1][4] * pivot;
    c[1][0] = c[1][0] * pivot;
    c[1][1] = c[1][1] * pivot;
    c[1][2] = c[1][2] * pivot;
    c[1][3] = c[1][3] * pivot;
    c[1][4] = c[1][4] * pivot;
    r[1] = r[1] * pivot;
    coeff = lhs[0][1];
    lhs[0][2] = lhs[0][2] - coeff * lhs[1][2];
    lhs[0][3] = lhs[0][3] - coeff * lhs[1][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[1][4];
    c[0][0] = c[0][0] - coeff * c[1][0];
    c[0][1] = c[0][1] - coeff * c[1][1];
    c[0][2] = c[0][2] - coeff * c[1][2];
    c[0][3] = c[0][3] - coeff * c[1][3];
    c[0][4] = c[0][4] - coeff * c[1][4];
    r[0] = r[0] - coeff * r[1];
    coeff = lhs[2][1];
    lhs[2][2] = lhs[2][2] - coeff * lhs[1][2];
    lhs[2][3] = lhs[2][3] - coeff * lhs[1][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[1][4];
    c[2][0] = c[2][0] - coeff * c[1][0];
    c[2][1] = c[2][1] - coeff * c[1][1];
    c[2][2] = c[2][2] - coeff * c[1][2];
    c[2][3] = c[2][3] - coeff * c[1][3];
    c[2][4] = c[2][4] - coeff * c[1][4];
    r[2] = r[2] - coeff * r[1];
    coeff = lhs[3][1];
    lhs[3][2] = lhs[3][2] - coeff * lhs[1][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[1][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[1][4];
    c[3][0] = c[3][0] - coeff * c[1][0];
    c[3][1] = c[3][1] - coeff * c[1][1];
    c[3][2] = c[3][2] - coeff * c[1][2];
    c[3][3] = c[3][3] - coeff * c[1][3];
    c[3][4] = c[3][4] - coeff * c[1][4];
    r[3] = r[3] - coeff * r[1];
    coeff = lhs[4][1];
    lhs[4][2] = lhs[4][2] - coeff * lhs[1][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[1][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[1][4];
    c[4][0] = c[4][0] - coeff * c[1][0];
    c[4][1] = c[4][1] - coeff * c[1][1];
    c[4][2] = c[4][2] - coeff * c[1][2];
    c[4][3] = c[4][3] - coeff * c[1][3];
    c[4][4] = c[4][4] - coeff * c[1][4];
    r[4] = r[4] - coeff * r[1];
    pivot = 1.00 / lhs[2][2];
    lhs[2][3] = lhs[2][3] * pivot;
    lhs[2][4] = lhs[2][4] * pivot;
    c[2][0] = c[2][0] * pivot;
    c[2][1] = c[2][1] * pivot;
    c[2][2] = c[2][2] * pivot;
    c[2][3] = c[2][3] * pivot;
    c[2][4] = c[2][4] * pivot;
    r[2] = r[2] * pivot;
    coeff = lhs[0][2];
    lhs[0][3] = lhs[0][3] - coeff * lhs[2][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[2][4];
    c[0][0] = c[0][0] - coeff * c[2][0];
    c[0][1] = c[0][1] - coeff * c[2][1];
    c[0][2] = c[0][2] - coeff * c[2][2];
    c[0][3] = c[0][3] - coeff * c[2][3];
    c[0][4] = c[0][4] - coeff * c[2][4];
    r[0] = r[0] - coeff * r[2];
    coeff = lhs[1][2];
    lhs[1][3] = lhs[1][3] - coeff * lhs[2][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[2][4];
    c[1][0] = c[1][0] - coeff * c[2][0];
    c[1][1] = c[1][1] - coeff * c[2][1];
    c[1][2] = c[1][2] - coeff * c[2][2];
    c[1][3] = c[1][3] - coeff * c[2][3];
    c[1][4] = c[1][4] - coeff * c[2][4];
    r[1] = r[1] - coeff * r[2];
    coeff = lhs[3][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[2][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[2][4];
    c[3][0] = c[3][0] - coeff * c[2][0];
    c[3][1] = c[3][1] - coeff * c[2][1];
    c[3][2] = c[3][2] - coeff * c[2][2];
    c[3][3] = c[3][3] - coeff * c[2][3];
    c[3][4] = c[3][4] - coeff * c[2][4];
    r[3] = r[3] - coeff * r[2];
    coeff = lhs[4][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[2][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[2][4];
    c[4][0] = c[4][0] - coeff * c[2][0];
    c[4][1] = c[4][1] - coeff * c[2][1];
    c[4][2] = c[4][2] - coeff * c[2][2];
    c[4][3] = c[4][3] - coeff * c[2][3];
    c[4][4] = c[4][4] - coeff * c[2][4];
    r[4] = r[4] - coeff * r[2];
    pivot = 1.00 / lhs[3][3];
    lhs[3][4] = lhs[3][4] * pivot;
    c[3][0] = c[3][0] * pivot;
    c[3][1] = c[3][1] * pivot;
    c[3][2] = c[3][2] * pivot;
    c[3][3] = c[3][3] * pivot;
    c[3][4] = c[3][4] * pivot;
    r[3] = r[3] * pivot;
    coeff = lhs[0][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[3][4];
    c[0][0] = c[0][0] - coeff * c[3][0];
    c[0][1] = c[0][1] - coeff * c[3][1];
    c[0][2] = c[0][2] - coeff * c[3][2];
    c[0][3] = c[0][3] - coeff * c[3][3];
    c[0][4] = c[0][4] - coeff * c[3][4];
    r[0] = r[0] - coeff * r[3];
    coeff = lhs[1][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[3][4];
    c[1][0] = c[1][0] - coeff * c[3][0];
    c[1][1] = c[1][1] - coeff * c[3][1];
    c[1][2] = c[1][2] - coeff * c[3][2];
    c[1][3] = c[1][3] - coeff * c[3][3];
    c[1][4] = c[1][4] - coeff * c[3][4];
    r[1] = r[1] - coeff * r[3];
    coeff = lhs[2][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[3][4];
    c[2][0] = c[2][0] - coeff * c[3][0];
    c[2][1] = c[2][1] - coeff * c[3][1];
    c[2][2] = c[2][2] - coeff * c[3][2];
    c[2][3] = c[2][3] - coeff * c[3][3];
    c[2][4] = c[2][4] - coeff * c[3][4];
    r[2] = r[2] - coeff * r[3];
    coeff = lhs[4][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[3][4];
    c[4][0] = c[4][0] - coeff * c[3][0];
    c[4][1] = c[4][1] - coeff * c[3][1];
    c[4][2] = c[4][2] - coeff * c[3][2];
    c[4][3] = c[4][3] - coeff * c[3][3];
    c[4][4] = c[4][4] - coeff * c[3][4];
    r[4] = r[4] - coeff * r[3];
    pivot = 1.00 / lhs[4][4];
    c[4][0] = c[4][0] * pivot;
    c[4][1] = c[4][1] * pivot;
    c[4][2] = c[4][2] * pivot;
    c[4][3] = c[4][3] * pivot;
    c[4][4] = c[4][4] * pivot;
    r[4] = r[4] * pivot;
    coeff = lhs[0][4];
    c[0][0] = c[0][0] - coeff * c[4][0];
    c[0][1] = c[0][1] - coeff * c[4][1];
    c[0][2] = c[0][2] - coeff * c[4][2];
    c[0][3] = c[0][3] - coeff * c[4][3];
    c[0][4] = c[0][4] - coeff * c[4][4];
    r[0] = r[0] - coeff * r[4];
    coeff = lhs[1][4];
    c[1][0] = c[1][0] - coeff * c[4][0];
    c[1][1] = c[1][1] - coeff * c[4][1];
    c[1][2] = c[1][2] - coeff * c[4][2];
    c[1][3] = c[1][3] - coeff * c[4][3];
    c[1][4] = c[1][4] - coeff * c[4][4];
    r[1] = r[1] - coeff * r[4];
    coeff = lhs[2][4];
    c[2][0] = c[2][0] - coeff * c[4][0];
    c[2][1] = c[2][1] - coeff * c[4][1];
    c[2][2] = c[2][2] - coeff * c[4][2];
    c[2][3] = c[2][3] - coeff * c[4][3];
    c[2][4] = c[2][4] - coeff * c[4][4];
    r[2] = r[2] - coeff * r[4];
    coeff = lhs[3][4];
    c[3][0] = c[3][0] - coeff * c[4][0];
    c[3][1] = c[3][1] - coeff * c[4][1];
    c[3][2] = c[3][2] - coeff * c[4][2];
    c[3][3] = c[3][3] - coeff * c[4][3];
    c[3][4] = c[3][4] - coeff * c[4][4];
    r[3] = r[3] - coeff * r[4];
}
static void binvrhs(double lhs[5][5], double r[5])
{
    double pivot, coeff;
    pivot = 1.00 / lhs[0][0];
    lhs[0][1] = lhs[0][1] * pivot;
    lhs[0][2] = lhs[0][2] * pivot;
    lhs[0][3] = lhs[0][3] * pivot;
    lhs[0][4] = lhs[0][4] * pivot;
    r[0] = r[0] * pivot;
    coeff = lhs[1][0];
    lhs[1][1] = lhs[1][1] - coeff * lhs[0][1];
    lhs[1][2] = lhs[1][2] - coeff * lhs[0][2];
    lhs[1][3] = lhs[1][3] - coeff * lhs[0][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[0][4];
    r[1] = r[1] - coeff * r[0];
    coeff = lhs[2][0];
    lhs[2][1] = lhs[2][1] - coeff * lhs[0][1];
    lhs[2][2] = lhs[2][2] - coeff * lhs[0][2];
    lhs[2][3] = lhs[2][3] - coeff * lhs[0][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[0][4];
    r[2] = r[2] - coeff * r[0];
    coeff = lhs[3][0];
    lhs[3][1] = lhs[3][1] - coeff * lhs[0][1];
    lhs[3][2] = lhs[3][2] - coeff * lhs[0][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[0][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[0][4];
    r[3] = r[3] - coeff * r[0];
    coeff = lhs[4][0];
    lhs[4][1] = lhs[4][1] - coeff * lhs[0][1];
    lhs[4][2] = lhs[4][2] - coeff * lhs[0][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[0][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[0][4];
    r[4] = r[4] - coeff * r[0];
    pivot = 1.00 / lhs[1][1];
    lhs[1][2] = lhs[1][2] * pivot;
    lhs[1][3] = lhs[1][3] * pivot;
    lhs[1][4] = lhs[1][4] * pivot;
    r[1] = r[1] * pivot;
    coeff = lhs[0][1];
    lhs[0][2] = lhs[0][2] - coeff * lhs[1][2];
    lhs[0][3] = lhs[0][3] - coeff * lhs[1][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[1][4];
    r[0] = r[0] - coeff * r[1];
    coeff = lhs[2][1];
    lhs[2][2] = lhs[2][2] - coeff * lhs[1][2];
    lhs[2][3] = lhs[2][3] - coeff * lhs[1][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[1][4];
    r[2] = r[2] - coeff * r[1];
    coeff = lhs[3][1];
    lhs[3][2] = lhs[3][2] - coeff * lhs[1][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[1][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[1][4];
    r[3] = r[3] - coeff * r[1];
    coeff = lhs[4][1];
    lhs[4][2] = lhs[4][2] - coeff * lhs[1][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[1][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[1][4];
    r[4] = r[4] - coeff * r[1];
    pivot = 1.00 / lhs[2][2];
    lhs[2][3] = lhs[2][3] * pivot;
    lhs[2][4] = lhs[2][4] * pivot;
    r[2] = r[2] * pivot;
    coeff = lhs[0][2];
    lhs[0][3] = lhs[0][3] - coeff * lhs[2][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[2][4];
    r[0] = r[0] - coeff * r[2];
    coeff = lhs[1][2];
    lhs[1][3] = lhs[1][3] - coeff * lhs[2][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[2][4];
    r[1] = r[1] - coeff * r[2];
    coeff = lhs[3][2];
    lhs[3][3] = lhs[3][3] - coeff * lhs[2][3];
    lhs[3][4] = lhs[3][4] - coeff * lhs[2][4];
    r[3] = r[3] - coeff * r[2];
    coeff = lhs[4][2];
    lhs[4][3] = lhs[4][3] - coeff * lhs[2][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[2][4];
    r[4] = r[4] - coeff * r[2];
    pivot = 1.00 / lhs[3][3];
    lhs[3][4] = lhs[3][4] * pivot;
    r[3] = r[3] * pivot;
    coeff = lhs[0][3];
    lhs[0][4] = lhs[0][4] - coeff * lhs[3][4];
    r[0] = r[0] - coeff * r[3];
    coeff = lhs[1][3];
    lhs[1][4] = lhs[1][4] - coeff * lhs[3][4];
    r[1] = r[1] - coeff * r[3];
    coeff = lhs[2][3];
    lhs[2][4] = lhs[2][4] - coeff * lhs[3][4];
    r[2] = r[2] - coeff * r[3];
    coeff = lhs[4][3];
    lhs[4][4] = lhs[4][4] - coeff * lhs[3][4];
    r[4] = r[4] - coeff * r[3];
    pivot = 1.00 / lhs[4][4];
    r[4] = r[4] * pivot;
    coeff = lhs[0][4];
    r[0] = r[0] - coeff * r[4];
    coeff = lhs[1][4];
    r[1] = r[1] - coeff * r[4];
    coeff = lhs[2][4];
    r[2] = r[2] - coeff * r[4];
    coeff = lhs[3][4];
    r[3] = r[3] - coeff * r[4];
}
static void y_solve(void)
{
    lhsy();
    y_solve_cell();
    y_backsubstitute();
}
static void y_backsubstitute(void)
{
    int i, j, k, m, n;
    for (j = grid_points[1] - 2;
        j >= 0;
        j--)
    {
#pragma omp for 
        for (i = 1;
            i < grid_points[0] - 1;
            i++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    for (n = 0;
                        n < 5;
                        n++)
                    {
                        rhs[i][j][k][m] = rhs[i][j][k][m] - lhs[i][j][k][2][m][n] * rhs[i][j + 1][k][n];
                    }
                }
            }
        }
    }
}
static void y_solve_cell(void)
{
    int i, j, k, jsize;
    jsize = grid_points[1] - 1;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            binvcrhs(lhs[i][0][k][1], lhs[i][0][k][2], rhs[i][0][k]);
        }
    }
    for (j = 1;
        j < jsize;
        j++)
    {
#pragma omp for 
        for (i = 1;
            i < grid_points[0] - 1;
            i++)
        {
            for (k = 1;
                k < grid_points[2] - 1;
                k++)
            {
                matvec_sub(lhs[i][j][k][0], rhs[i][j - 1][k], rhs[i][j][k]);
                matmul_sub(lhs[i][j][k][0], lhs[i][j - 1][k][2], lhs[i][j][k][1]);
                binvcrhs(lhs[i][j][k][1], lhs[i][j][k][2], rhs[i][j][k]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (k = 1;
            k < grid_points[2] - 1;
            k++)
        {
            matvec_sub(lhs[i][jsize][k][0], rhs[i][jsize - 1][k], rhs[i][jsize][k]);
            matmul_sub(lhs[i][jsize][k][0], lhs[i][jsize - 1][k][2], lhs[i][jsize][k][1]);
            binvrhs(lhs[i][jsize][k][1], rhs[i][jsize][k]);
        }
    }
}
static void z_solve(void)
{
    lhsz();
    z_solve_cell();
    z_backsubstitute();
}
static void z_backsubstitute(void)
{
    int i, j, k, m, n;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            for (k = grid_points[2] - 2;
                k >= 0;
                k--)
            {
                for (m = 0;
                    m < 5;
                    m++)
                {
                    for (n = 0;
                        n < 5;
                        n++)
                    {
                        rhs[i][j][k][m] = rhs[i][j][k][m] - lhs[i][j][k][2][m][n] * rhs[i][j][k + 1][n];
                    }
                }
            }
        }
    }
}
static void z_solve_cell(void)
{
    int i, j, k, ksize;
    ksize = grid_points[2] - 1;
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            binvcrhs(lhs[i][j][0][1], lhs[i][j][0][2], rhs[i][j][0]);
        }
    }
    for (k = 1;
        k < ksize;
        k++)
    {
#pragma omp for 
        for (i = 1;
            i < grid_points[0] - 1;
            i++)
        {
            for (j = 1;
                j < grid_points[1] - 1;
                j++)
            {
                matvec_sub(lhs[i][j][k][0], rhs[i][j][k - 1], rhs[i][j][k]);
                matmul_sub(lhs[i][j][k][0], lhs[i][j][k - 1][2], lhs[i][j][k][1]);
                binvcrhs(lhs[i][j][k][1], lhs[i][j][k][2], rhs[i][j][k]);
            }
        }
    }
#pragma omp for 
    for (i = 1;
        i < grid_points[0] - 1;
        i++)
    {
        for (j = 1;
            j < grid_points[1] - 1;
            j++)
        {
            matvec_sub(lhs[i][j][ksize][0], rhs[i][j][ksize - 1], rhs[i][j][ksize]);
            matmul_sub(lhs[i][j][ksize][0], lhs[i][j][ksize - 1][2], lhs[i][j][ksize][1]);
            binvrhs(lhs[i][j][ksize][1], rhs[i][j][ksize]);
        }
    }
}
