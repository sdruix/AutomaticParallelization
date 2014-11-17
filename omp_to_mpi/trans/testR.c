typedef unsigned int size_t;
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
typedef __gnuc_va_list va_list;
typedef __off_t off_t;
typedef __ssize_t ssize_t;
typedef _G_fpos_t fpos_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;
extern int remove(const char *__filename) __attribute__((__nothrow__));
extern int rename(const char *__old, const char *__new) __attribute__((__nothrow__));
extern int renameat(int __oldfd, const char *__old, int __newfd, const char *__new) __attribute__((__nothrow__));
extern FILE *tmpfile(void);
extern char *tmpnam(char *__s) __attribute__((__nothrow__));
extern char *tmpnam_r(char *__s) __attribute__((__nothrow__));
extern char *tempnam(const char *__dir, const char *__pfx) __attribute__((__nothrow__)) __attribute__((__malloc__));
extern int fclose(FILE *__stream);
extern int fflush(FILE *__stream);
extern int fflush_unlocked(FILE *__stream);
extern FILE *fopen(const char *__restrict __filename, const char *__restrict __modes);
extern FILE *freopen(const char *__restrict __filename, const char *__restrict __modes, FILE *__restrict __stream);
extern FILE *fdopen(int __fd, const char *__modes) __attribute__((__nothrow__));
extern FILE *fmemopen(void *__s, size_t __len, const char *__modes) __attribute__((__nothrow__));
extern FILE *open_memstream(char **__bufloc, size_t *__sizeloc) __attribute__((__nothrow__));
extern void setbuf(FILE *__restrict __stream, char *__restrict __buf) __attribute__((__nothrow__));
extern int setvbuf(FILE *__restrict __stream, char *__restrict __buf, int __modes, size_t __n) __attribute__((__nothrow__));
extern void setbuffer(FILE *__restrict __stream, char *__restrict __buf, size_t __size) __attribute__((__nothrow__));
extern void setlinebuf(FILE *__stream) __attribute__((__nothrow__));
extern int fprintf(FILE *__restrict __stream, const char *__restrict __format, ...);
extern int printf(const char *__restrict __format, ...);
extern int sprintf(char *__restrict __s, const char *__restrict __format, ...) __attribute__((__nothrow__));
extern int vfprintf(FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg);
extern int vprintf(const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf(char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__));
extern int snprintf(char *__restrict __s, size_t __maxlen, const char *__restrict __format, ...) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 4)));
extern int vsnprintf(char *__restrict __s, size_t __maxlen, const char *__restrict __format, __gnuc_va_list __arg) __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 0)));
extern int vdprintf(int __fd, const char *__restrict __fmt, __gnuc_va_list __arg) __attribute__((__format__(__printf__, 2, 0)));
extern int dprintf(int __fd, const char *__restrict __fmt, ...) __attribute__((__format__(__printf__, 2, 3)));
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
extern int getc_unlocked(FILE *__stream);
extern int getchar_unlocked(void);
extern int fgetc_unlocked(FILE *__stream);
extern int fputc(int __c, FILE *__stream);
extern int putc(int __c, FILE *__stream);
extern int putchar(int __c);
extern int fputc_unlocked(int __c, FILE *__stream);
extern int putc_unlocked(int __c, FILE *__stream);
extern int putchar_unlocked(int __c);
extern int getw(FILE *__stream);
extern int putw(int __w, FILE *__stream);
extern char *fgets(char *__restrict __s, int __n, FILE *__restrict __stream);
extern char *gets(char *__s) __attribute__((__deprecated__));
extern __ssize_t __getdelim(char **__restrict __lineptr, size_t *__restrict __n, int __delimiter, FILE *__restrict __stream);
extern __ssize_t getdelim(char **__restrict __lineptr, size_t *__restrict __n, int __delimiter, FILE *__restrict __stream);
extern __ssize_t getline(char **__restrict __lineptr, size_t *__restrict __n, FILE *__restrict __stream);
extern int fputs(const char *__restrict __s, FILE *__restrict __stream);
extern int puts(const char *__s);
extern int ungetc(int __c, FILE *__stream);
extern size_t fread(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern size_t fwrite(const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __s);
extern size_t fread_unlocked(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern size_t fwrite_unlocked(const void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream);
extern int fseek(FILE *__stream, long int __off, int __whence);
extern long int ftell(FILE *__stream);
extern void rewind(FILE *__stream);
extern int fseeko(FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello(FILE *__stream);
extern int fgetpos(FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos(FILE *__stream, const fpos_t *__pos);
extern void clearerr(FILE *__stream) __attribute__((__nothrow__));
extern int feof(FILE *__stream) __attribute__((__nothrow__));
extern int ferror(FILE *__stream) __attribute__((__nothrow__));
extern void clearerr_unlocked(FILE *__stream) __attribute__((__nothrow__));
extern int feof_unlocked(FILE *__stream) __attribute__((__nothrow__));
extern int ferror_unlocked(FILE *__stream) __attribute__((__nothrow__));
extern void perror(const char *__s);
extern int sys_nerr;
extern const char *const sys_errlist[];
extern int fileno(FILE *__stream) __attribute__((__nothrow__));
extern int fileno_unlocked(FILE *__stream) __attribute__((__nothrow__));
extern FILE *popen(const char *__command, const char *__modes);
extern int pclose(FILE *__stream);
extern char *ctermid(char *__s) __attribute__((__nothrow__));
extern void flockfile(FILE *__stream) __attribute__((__nothrow__));
extern int ftrylockfile(FILE *__stream) __attribute__((__nothrow__));
extern void funlockfile(FILE *__stream) __attribute__((__nothrow__));
typedef __gid_t gid_t;
typedef __uid_t uid_t;
typedef __useconds_t useconds_t;
typedef __pid_t pid_t;
typedef __intptr_t intptr_t;
typedef __socklen_t socklen_t;
extern int access(const char *__name, int __type) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int faccessat(int __fd, const char *__file, int __type, int __flag) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern __off_t lseek(int __fd, __off_t __offset, int __whence) __attribute__((__nothrow__));
extern int close(int __fd);
extern ssize_t read(int __fd, void *__buf, size_t __nbytes);
extern ssize_t write(int __fd, const void *__buf, size_t __n);
extern ssize_t pread(int __fd, void *__buf, size_t __nbytes, __off_t __offset);
extern ssize_t pwrite(int __fd, const void *__buf, size_t __n, __off_t __offset);
extern int pipe(int __pipedes[2]) __attribute__((__nothrow__));
extern unsigned int alarm(unsigned int __seconds) __attribute__((__nothrow__));
extern unsigned int sleep(unsigned int __seconds);
extern __useconds_t ualarm(__useconds_t __value, __useconds_t __interval) __attribute__((__nothrow__));
extern int usleep(__useconds_t __useconds);
extern int pause(void);
extern int chown(const char *__file, __uid_t __owner, __gid_t __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int fchown(int __fd, __uid_t __owner, __gid_t __group) __attribute__((__nothrow__));
extern int lchown(const char *__file, __uid_t __owner, __gid_t __group) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int fchownat(int __fd, const char *__file, __uid_t __owner, __gid_t __group, int __flag) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int chdir(const char *__path) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int fchdir(int __fd) __attribute__((__nothrow__));
extern char *getcwd(char *__buf, size_t __size) __attribute__((__nothrow__));
extern char *getwd(char *__buf) __attribute__((__nothrow__)) __attribute__((__nonnull__(1))) __attribute__((__deprecated__));
extern int dup(int __fd) __attribute__((__nothrow__));
extern int dup2(int __fd, int __fd2) __attribute__((__nothrow__));
extern char **__environ;
extern int execve(const char *__path, char *const __argv[], char *const __envp[]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int fexecve(int __fd, char *const __argv[], char *const __envp[]) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int execv(const char *__path, char *const __argv[]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int execle(const char *__path, const char *__arg, ...) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int execl(const char *__path, const char *__arg, ...) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int execvp(const char *__file, char *const __argv[]) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int execlp(const char *__file, const char *__arg, ...) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int nice(int __inc) __attribute__((__nothrow__));
extern void _exit(int __status) __attribute__((__noreturn__));
enum 
{
    _PC_LINK_MAX, 
    _PC_MAX_CANON, 
    _PC_MAX_INPUT, 
    _PC_NAME_MAX, 
    _PC_PATH_MAX, 
    _PC_PIPE_BUF, 
    _PC_CHOWN_RESTRICTED, 
    _PC_NO_TRUNC, 
    _PC_VDISABLE, 
    _PC_SYNC_IO, 
    _PC_ASYNC_IO, 
    _PC_PRIO_IO, 
    _PC_SOCK_MAXBUF, 
    _PC_FILESIZEBITS, 
    _PC_REC_INCR_XFER_SIZE, 
    _PC_REC_MAX_XFER_SIZE, 
    _PC_REC_MIN_XFER_SIZE, 
    _PC_REC_XFER_ALIGN, 
    _PC_ALLOC_SIZE_MIN, 
    _PC_SYMLINK_MAX, 
    _PC_2_SYMLINKS
};
enum 
{
    _SC_ARG_MAX, 
    _SC_CHILD_MAX, 
    _SC_CLK_TCK, 
    _SC_NGROUPS_MAX, 
    _SC_OPEN_MAX, 
    _SC_STREAM_MAX, 
    _SC_TZNAME_MAX, 
    _SC_JOB_CONTROL, 
    _SC_SAVED_IDS, 
    _SC_REALTIME_SIGNALS, 
    _SC_PRIORITY_SCHEDULING, 
    _SC_TIMERS, 
    _SC_ASYNCHRONOUS_IO, 
    _SC_PRIORITIZED_IO, 
    _SC_SYNCHRONIZED_IO, 
    _SC_FSYNC, 
    _SC_MAPPED_FILES, 
    _SC_MEMLOCK, 
    _SC_MEMLOCK_RANGE, 
    _SC_MEMORY_PROTECTION, 
    _SC_MESSAGE_PASSING, 
    _SC_SEMAPHORES, 
    _SC_SHARED_MEMORY_OBJECTS, 
    _SC_AIO_LISTIO_MAX, 
    _SC_AIO_MAX, 
    _SC_AIO_PRIO_DELTA_MAX, 
    _SC_DELAYTIMER_MAX, 
    _SC_MQ_OPEN_MAX, 
    _SC_MQ_PRIO_MAX, 
    _SC_VERSION, 
    _SC_PAGESIZE, 
    _SC_RTSIG_MAX, 
    _SC_SEM_NSEMS_MAX, 
    _SC_SEM_VALUE_MAX, 
    _SC_SIGQUEUE_MAX, 
    _SC_TIMER_MAX, 
    _SC_BC_BASE_MAX, 
    _SC_BC_DIM_MAX, 
    _SC_BC_SCALE_MAX, 
    _SC_BC_STRING_MAX, 
    _SC_COLL_WEIGHTS_MAX, 
    _SC_EQUIV_CLASS_MAX, 
    _SC_EXPR_NEST_MAX, 
    _SC_LINE_MAX, 
    _SC_RE_DUP_MAX, 
    _SC_CHARCLASS_NAME_MAX, 
    _SC_2_VERSION, 
    _SC_2_C_BIND, 
    _SC_2_C_DEV, 
    _SC_2_FORT_DEV, 
    _SC_2_FORT_RUN, 
    _SC_2_SW_DEV, 
    _SC_2_LOCALEDEF, 
    _SC_PII, 
    _SC_PII_XTI, 
    _SC_PII_SOCKET, 
    _SC_PII_INTERNET, 
    _SC_PII_OSI, 
    _SC_POLL, 
    _SC_SELECT, 
    _SC_UIO_MAXIOV, 
    _SC_IOV_MAX = _SC_UIO_MAXIOV, 
    _SC_PII_INTERNET_STREAM, 
    _SC_PII_INTERNET_DGRAM, 
    _SC_PII_OSI_COTS, 
    _SC_PII_OSI_CLTS, 
    _SC_PII_OSI_M, 
    _SC_T_IOV_MAX, 
    _SC_THREADS, 
    _SC_THREAD_SAFE_FUNCTIONS, 
    _SC_GETGR_R_SIZE_MAX, 
    _SC_GETPW_R_SIZE_MAX, 
    _SC_LOGIN_NAME_MAX, 
    _SC_TTY_NAME_MAX, 
    _SC_THREAD_DESTRUCTOR_ITERATIONS, 
    _SC_THREAD_KEYS_MAX, 
    _SC_THREAD_STACK_MIN, 
    _SC_THREAD_THREADS_MAX, 
    _SC_THREAD_ATTR_STACKADDR, 
    _SC_THREAD_ATTR_STACKSIZE, 
    _SC_THREAD_PRIORITY_SCHEDULING, 
    _SC_THREAD_PRIO_INHERIT, 
    _SC_THREAD_PRIO_PROTECT, 
    _SC_THREAD_PROCESS_SHARED, 
    _SC_NPROCESSORS_CONF, 
    _SC_NPROCESSORS_ONLN, 
    _SC_PHYS_PAGES, 
    _SC_AVPHYS_PAGES, 
    _SC_ATEXIT_MAX, 
    _SC_PASS_MAX, 
    _SC_XOPEN_VERSION, 
    _SC_XOPEN_XCU_VERSION, 
    _SC_XOPEN_UNIX, 
    _SC_XOPEN_CRYPT, 
    _SC_XOPEN_ENH_I18N, 
    _SC_XOPEN_SHM, 
    _SC_2_CHAR_TERM, 
    _SC_2_C_VERSION, 
    _SC_2_UPE, 
    _SC_XOPEN_XPG2, 
    _SC_XOPEN_XPG3, 
    _SC_XOPEN_XPG4, 
    _SC_CHAR_BIT, 
    _SC_CHAR_MAX, 
    _SC_CHAR_MIN, 
    _SC_INT_MAX, 
    _SC_INT_MIN, 
    _SC_LONG_BIT, 
    _SC_WORD_BIT, 
    _SC_MB_LEN_MAX, 
    _SC_NZERO, 
    _SC_SSIZE_MAX, 
    _SC_SCHAR_MAX, 
    _SC_SCHAR_MIN, 
    _SC_SHRT_MAX, 
    _SC_SHRT_MIN, 
    _SC_UCHAR_MAX, 
    _SC_UINT_MAX, 
    _SC_ULONG_MAX, 
    _SC_USHRT_MAX, 
    _SC_NL_ARGMAX, 
    _SC_NL_LANGMAX, 
    _SC_NL_MSGMAX, 
    _SC_NL_NMAX, 
    _SC_NL_SETMAX, 
    _SC_NL_TEXTMAX, 
    _SC_XBS5_ILP32_OFF32, 
    _SC_XBS5_ILP32_OFFBIG, 
    _SC_XBS5_LP64_OFF64, 
    _SC_XBS5_LPBIG_OFFBIG, 
    _SC_XOPEN_LEGACY, 
    _SC_XOPEN_REALTIME, 
    _SC_XOPEN_REALTIME_THREADS, 
    _SC_ADVISORY_INFO, 
    _SC_BARRIERS, 
    _SC_BASE, 
    _SC_C_LANG_SUPPORT, 
    _SC_C_LANG_SUPPORT_R, 
    _SC_CLOCK_SELECTION, 
    _SC_CPUTIME, 
    _SC_THREAD_CPUTIME, 
    _SC_DEVICE_IO, 
    _SC_DEVICE_SPECIFIC, 
    _SC_DEVICE_SPECIFIC_R, 
    _SC_FD_MGMT, 
    _SC_FIFO, 
    _SC_PIPE, 
    _SC_FILE_ATTRIBUTES, 
    _SC_FILE_LOCKING, 
    _SC_FILE_SYSTEM, 
    _SC_MONOTONIC_CLOCK, 
    _SC_MULTI_PROCESS, 
    _SC_SINGLE_PROCESS, 
    _SC_NETWORKING, 
    _SC_READER_WRITER_LOCKS, 
    _SC_SPIN_LOCKS, 
    _SC_REGEXP, 
    _SC_REGEX_VERSION, 
    _SC_SHELL, 
    _SC_SIGNALS, 
    _SC_SPAWN, 
    _SC_SPORADIC_SERVER, 
    _SC_THREAD_SPORADIC_SERVER, 
    _SC_SYSTEM_DATABASE, 
    _SC_SYSTEM_DATABASE_R, 
    _SC_TIMEOUTS, 
    _SC_TYPED_MEMORY_OBJECTS, 
    _SC_USER_GROUPS, 
    _SC_USER_GROUPS_R, 
    _SC_2_PBS, 
    _SC_2_PBS_ACCOUNTING, 
    _SC_2_PBS_LOCATE, 
    _SC_2_PBS_MESSAGE, 
    _SC_2_PBS_TRACK, 
    _SC_SYMLOOP_MAX, 
    _SC_STREAMS, 
    _SC_2_PBS_CHECKPOINT, 
    _SC_V6_ILP32_OFF32, 
    _SC_V6_ILP32_OFFBIG, 
    _SC_V6_LP64_OFF64, 
    _SC_V6_LPBIG_OFFBIG, 
    _SC_HOST_NAME_MAX, 
    _SC_TRACE, 
    _SC_TRACE_EVENT_FILTER, 
    _SC_TRACE_INHERIT, 
    _SC_TRACE_LOG, 
    _SC_LEVEL1_ICACHE_SIZE, 
    _SC_LEVEL1_ICACHE_ASSOC, 
    _SC_LEVEL1_ICACHE_LINESIZE, 
    _SC_LEVEL1_DCACHE_SIZE, 
    _SC_LEVEL1_DCACHE_ASSOC, 
    _SC_LEVEL1_DCACHE_LINESIZE, 
    _SC_LEVEL2_CACHE_SIZE, 
    _SC_LEVEL2_CACHE_ASSOC, 
    _SC_LEVEL2_CACHE_LINESIZE, 
    _SC_LEVEL3_CACHE_SIZE, 
    _SC_LEVEL3_CACHE_ASSOC, 
    _SC_LEVEL3_CACHE_LINESIZE, 
    _SC_LEVEL4_CACHE_SIZE, 
    _SC_LEVEL4_CACHE_ASSOC, 
    _SC_LEVEL4_CACHE_LINESIZE, 
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50, 
    _SC_RAW_SOCKETS, 
    _SC_V7_ILP32_OFF32, 
    _SC_V7_ILP32_OFFBIG, 
    _SC_V7_LP64_OFF64, 
    _SC_V7_LPBIG_OFFBIG, 
    _SC_SS_REPL_MAX, 
    _SC_TRACE_EVENT_NAME_MAX, 
    _SC_TRACE_NAME_MAX, 
    _SC_TRACE_SYS_MAX, 
    _SC_TRACE_USER_EVENT_MAX, 
    _SC_XOPEN_STREAMS, 
    _SC_THREAD_ROBUST_PRIO_INHERIT, 
    _SC_THREAD_ROBUST_PRIO_PROTECT
};
enum 
{
    _CS_PATH, 
    _CS_V6_WIDTH_RESTRICTED_ENVS, 
    _CS_GNU_LIBC_VERSION, 
    _CS_GNU_LIBPTHREAD_VERSION, 
    _CS_V5_WIDTH_RESTRICTED_ENVS, 
    _CS_V7_WIDTH_RESTRICTED_ENVS, 
    _CS_LFS_CFLAGS = 1000, 
    _CS_LFS_LDFLAGS, 
    _CS_LFS_LIBS, 
    _CS_LFS_LINTFLAGS, 
    _CS_LFS64_CFLAGS, 
    _CS_LFS64_LDFLAGS, 
    _CS_LFS64_LIBS, 
    _CS_LFS64_LINTFLAGS, 
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100, 
    _CS_XBS5_ILP32_OFF32_LDFLAGS, 
    _CS_XBS5_ILP32_OFF32_LIBS, 
    _CS_XBS5_ILP32_OFF32_LINTFLAGS, 
    _CS_XBS5_ILP32_OFFBIG_CFLAGS, 
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS, 
    _CS_XBS5_ILP32_OFFBIG_LIBS, 
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS, 
    _CS_XBS5_LP64_OFF64_CFLAGS, 
    _CS_XBS5_LP64_OFF64_LDFLAGS, 
    _CS_XBS5_LP64_OFF64_LIBS, 
    _CS_XBS5_LP64_OFF64_LINTFLAGS, 
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS, 
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS, 
    _CS_XBS5_LPBIG_OFFBIG_LIBS, 
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS, 
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS, 
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS, 
    _CS_POSIX_V6_ILP32_OFF32_LIBS, 
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS, 
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS, 
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS, 
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS, 
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS, 
    _CS_POSIX_V6_LP64_OFF64_CFLAGS, 
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS, 
    _CS_POSIX_V6_LP64_OFF64_LIBS, 
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS, 
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS, 
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS, 
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS, 
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS, 
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS, 
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS, 
    _CS_POSIX_V7_ILP32_OFF32_LIBS, 
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS, 
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS, 
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS, 
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS, 
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS, 
    _CS_POSIX_V7_LP64_OFF64_CFLAGS, 
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS, 
    _CS_POSIX_V7_LP64_OFF64_LIBS, 
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS, 
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS, 
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS, 
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS, 
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS, 
    _CS_V6_ENV, 
    _CS_V7_ENV
};
extern long int pathconf(const char *__path, int __name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern long int fpathconf(int __fd, int __name) __attribute__((__nothrow__));
extern long int sysconf(int __name) __attribute__((__nothrow__));
extern size_t confstr(int __name, char *__buf, size_t __len) __attribute__((__nothrow__));
extern __pid_t getpid(void) __attribute__((__nothrow__));
extern __pid_t getppid(void) __attribute__((__nothrow__));
extern __pid_t getpgrp(void) __attribute__((__nothrow__));
extern __pid_t __getpgid(__pid_t __pid) __attribute__((__nothrow__));
extern __pid_t getpgid(__pid_t __pid) __attribute__((__nothrow__));
extern int setpgid(__pid_t __pid, __pid_t __pgid) __attribute__((__nothrow__));
extern int setpgrp(void) __attribute__((__nothrow__));
extern __pid_t setsid(void) __attribute__((__nothrow__));
extern __pid_t getsid(__pid_t __pid) __attribute__((__nothrow__));
extern __uid_t getuid(void) __attribute__((__nothrow__));
extern __uid_t geteuid(void) __attribute__((__nothrow__));
extern __gid_t getgid(void) __attribute__((__nothrow__));
extern __gid_t getegid(void) __attribute__((__nothrow__));
extern int getgroups(int __size, __gid_t __list[]) __attribute__((__nothrow__));
extern int setuid(__uid_t __uid) __attribute__((__nothrow__));
extern int setreuid(__uid_t __ruid, __uid_t __euid) __attribute__((__nothrow__));
extern int seteuid(__uid_t __uid) __attribute__((__nothrow__));
extern int setgid(__gid_t __gid) __attribute__((__nothrow__));
extern int setregid(__gid_t __rgid, __gid_t __egid) __attribute__((__nothrow__));
extern int setegid(__gid_t __gid) __attribute__((__nothrow__));
extern __pid_t fork(void) __attribute__((__nothrow__));
extern __pid_t vfork(void) __attribute__((__nothrow__));
extern char *ttyname(int __fd) __attribute__((__nothrow__));
extern int ttyname_r(int __fd, char *__buf, size_t __buflen) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int isatty(int __fd) __attribute__((__nothrow__));
extern int ttyslot(void) __attribute__((__nothrow__));
extern int link(const char *__from, const char *__to) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int linkat(int __fromfd, const char *__from, int __tofd, const char *__to, int __flags) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 4)));
extern int symlink(const char *__from, const char *__to) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern ssize_t readlink(const char *__restrict __path, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int symlinkat(const char *__from, int __tofd, const char *__to) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 3)));
extern ssize_t readlinkat(int __fd, const char *__restrict __path, char *__restrict __buf, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern int unlink(const char *__name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int unlinkat(int __fd, const char *__name, int __flag) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern int rmdir(const char *__path) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern __pid_t tcgetpgrp(int __fd) __attribute__((__nothrow__));
extern int tcsetpgrp(int __fd, __pid_t __pgrp_id) __attribute__((__nothrow__));
extern char *getlogin(void);
extern int getlogin_r(char *__name, size_t __name_len) __attribute__((__nonnull__(1)));
extern int setlogin(const char *__name) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt(int ___argc, char *const *___argv, const char *__shortopts) __attribute__((__nothrow__));
extern int gethostname(char *__name, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int sethostname(const char *__name, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int sethostid(long int __id) __attribute__((__nothrow__));
extern int getdomainname(char *__name, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int setdomainname(const char *__name, size_t __len) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int vhangup(void) __attribute__((__nothrow__));
extern int revoke(const char *__file) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int profil(unsigned short int *__sample_buffer, size_t __size, size_t __offset, unsigned int __scale) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int acct(const char *__name) __attribute__((__nothrow__));
extern char *getusershell(void) __attribute__((__nothrow__));
extern void endusershell(void) __attribute__((__nothrow__));
extern void setusershell(void) __attribute__((__nothrow__));
extern int daemon(int __nochdir, int __noclose) __attribute__((__nothrow__));
extern int chroot(const char *__path) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern char *getpass(const char *__prompt) __attribute__((__nonnull__(1)));
extern int fsync(int __fd);
extern long int gethostid(void);
extern void sync(void) __attribute__((__nothrow__));
extern int getpagesize(void) __attribute__((__nothrow__)) __attribute__((__const__));
extern int getdtablesize(void) __attribute__((__nothrow__));
extern int truncate(const char *__file, __off_t __length) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int ftruncate(int __fd, __off_t __length) __attribute__((__nothrow__));
extern int brk(void *__addr) __attribute__((__nothrow__));
extern void *sbrk(intptr_t __delta) __attribute__((__nothrow__));
extern long int syscall(long int __sysno, ...) __attribute__((__nothrow__));
extern int lockf(int __fd, int __cmd, __off_t __len);
extern int fdatasync(int __fildes);
extern void *memcpy(void *__restrict __dest, const void *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void *memmove(void *__dest, const void *__src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void *memccpy(void *__restrict __dest, const void *__restrict __src, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void *memset(void *__s, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int memcmp(const void *__s1, const void *__s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern void *memchr(const void *__s, int __c, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char *strcpy(char *__restrict __dest, const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *strncpy(char *__restrict __dest, const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *strcat(char *__restrict __dest, const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *strncat(char *__restrict __dest, const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern int strcmp(const char *__s1, const char *__s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strncmp(const char *__s1, const char *__s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strcoll(const char *__s1, const char *__s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern size_t strxfrm(char *__restrict __dest, const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
typedef struct __locale_struct
{
        struct __locale_data *__locales[13];
        const unsigned short int *__ctype_b;
        const int *__ctype_tolower;
        const int *__ctype_toupper;
        const char *__names[13];
} *__locale_t;
typedef __locale_t locale_t;
extern int strcoll_l(const char *__s1, const char *__s2, __locale_t __l) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2, 3)));
extern size_t strxfrm_l(char *__dest, const char *__src, size_t __n, __locale_t __l) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 4)));
extern char *strdup(const char *__s) __attribute__((__nothrow__)) __attribute__((__malloc__)) __attribute__((__nonnull__(1)));
extern char *strndup(const char *__string, size_t __n) __attribute__((__nothrow__)) __attribute__((__malloc__)) __attribute__((__nonnull__(1)));
extern char *strchr(const char *__s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char *strrchr(const char *__s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern size_t strcspn(const char *__s, const char *__reject) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern size_t strspn(const char *__s, const char *__accept) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char *strpbrk(const char *__s, const char *__accept) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char *strstr(const char *__haystack, const char *__needle) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char *strtok(char *__restrict __s, const char *__restrict __delim) __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern char *__strtok_r(char *__restrict __s, const char *__restrict __delim, char **__restrict __save_ptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern char *strtok_r(char *__restrict __s, const char *__restrict __delim, char **__restrict __save_ptr) __attribute__((__nothrow__)) __attribute__((__nonnull__(2, 3)));
extern size_t strlen(const char *__s) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern size_t strnlen(const char *__string, size_t __maxlen) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char *strerror(int __errnum) __attribute__((__nothrow__));
extern int strerror_r(int __errnum, char *__buf, size_t __buflen) __asm__ ("""__xpg_strerror_r") __attribute__((__nothrow__)) __attribute__((__nonnull__(2)));
extern char *strerror_l(int __errnum, __locale_t __l) __attribute__((__nothrow__));
extern void __bzero(void *__s, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern void bcopy(const void *__src, void *__dest, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern void bzero(void *__s, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1)));
extern int bcmp(const void *__s1, const void *__s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char *index(const char *__s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern char *rindex(const char *__s, int __c) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
extern int ffs(int __i) __attribute__((__nothrow__)) __attribute__((__const__));
extern int strcasecmp(const char *__s1, const char *__s2) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern int strncasecmp(const char *__s1, const char *__s2, size_t __n) __attribute__((__nothrow__)) __attribute__((__pure__)) __attribute__((__nonnull__(1, 2)));
extern char *strsep(char **__restrict __stringp, const char *__restrict __delim) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *strsignal(int __sig) __attribute__((__nothrow__));
extern char *__stpcpy(char *__restrict __dest, const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *stpcpy(char *__restrict __dest, const char *__restrict __src) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *__stpncpy(char *__restrict __dest, const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
extern char *stpncpy(char *__restrict __dest, const char *__restrict __src, size_t __n) __attribute__((__nothrow__)) __attribute__((__nonnull__(1, 2)));
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
extern int isinf(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finite(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double drem(double __x, double __y) __attribute__((__nothrow__));
extern double __drem(double __x, double __y) __attribute__((__nothrow__));
extern double significand(double __x) __attribute__((__nothrow__));
extern double __significand(double __x) __attribute__((__nothrow__));
extern double copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __copysign(double __x, double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern double nan(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern double __nan(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnan(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnan(double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern double j0(double) __attribute__((__nothrow__));
extern double __j0(double) __attribute__((__nothrow__));
extern double j1(double) __attribute__((__nothrow__));
extern double __j1(double) __attribute__((__nothrow__));
extern double jn(int, double) __attribute__((__nothrow__));
extern double __jn(int, double) __attribute__((__nothrow__));
extern double y0(double) __attribute__((__nothrow__));
extern double __y0(double) __attribute__((__nothrow__));
extern double y1(double) __attribute__((__nothrow__));
extern double __y1(double) __attribute__((__nothrow__));
extern double yn(int, double) __attribute__((__nothrow__));
extern double __yn(int, double) __attribute__((__nothrow__));
extern double erf(double) __attribute__((__nothrow__));
extern double __erf(double) __attribute__((__nothrow__));
extern double erfc(double) __attribute__((__nothrow__));
extern double __erfc(double) __attribute__((__nothrow__));
extern double lgamma(double) __attribute__((__nothrow__));
extern double __lgamma(double) __attribute__((__nothrow__));
extern double tgamma(double) __attribute__((__nothrow__));
extern double __tgamma(double) __attribute__((__nothrow__));
extern double gamma(double) __attribute__((__nothrow__));
extern double __gamma(double) __attribute__((__nothrow__));
extern double lgamma_r(double, int *__signgamp) __attribute__((__nothrow__));
extern double __lgamma_r(double, int *__signgamp) __attribute__((__nothrow__));
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
extern double scalb(double __x, double __n) __attribute__((__nothrow__));
extern double __scalb(double __x, double __n) __attribute__((__nothrow__));
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
extern int isinff(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finitef(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float dremf(float __x, float __y) __attribute__((__nothrow__));
extern float __dremf(float __x, float __y) __attribute__((__nothrow__));
extern float significandf(float __x) __attribute__((__nothrow__));
extern float __significandf(float __x) __attribute__((__nothrow__));
extern float copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __copysignf(float __x, float __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern float nanf(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern float __nanf(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnanf(float __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern float j0f(float) __attribute__((__nothrow__));
extern float __j0f(float) __attribute__((__nothrow__));
extern float j1f(float) __attribute__((__nothrow__));
extern float __j1f(float) __attribute__((__nothrow__));
extern float jnf(int, float) __attribute__((__nothrow__));
extern float __jnf(int, float) __attribute__((__nothrow__));
extern float y0f(float) __attribute__((__nothrow__));
extern float __y0f(float) __attribute__((__nothrow__));
extern float y1f(float) __attribute__((__nothrow__));
extern float __y1f(float) __attribute__((__nothrow__));
extern float ynf(int, float) __attribute__((__nothrow__));
extern float __ynf(int, float) __attribute__((__nothrow__));
extern float erff(float) __attribute__((__nothrow__));
extern float __erff(float) __attribute__((__nothrow__));
extern float erfcf(float) __attribute__((__nothrow__));
extern float __erfcf(float) __attribute__((__nothrow__));
extern float lgammaf(float) __attribute__((__nothrow__));
extern float __lgammaf(float) __attribute__((__nothrow__));
extern float tgammaf(float) __attribute__((__nothrow__));
extern float __tgammaf(float) __attribute__((__nothrow__));
extern float gammaf(float) __attribute__((__nothrow__));
extern float __gammaf(float) __attribute__((__nothrow__));
extern float lgammaf_r(float, int *__signgamp) __attribute__((__nothrow__));
extern float __lgammaf_r(float, int *__signgamp) __attribute__((__nothrow__));
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
extern float scalbf(float __x, float __n) __attribute__((__nothrow__));
extern float __scalbf(float __x, float __n) __attribute__((__nothrow__));
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
extern int isinfl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int finitel(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double dreml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double __dreml(long double __x, long double __y) __attribute__((__nothrow__));
extern long double significandl(long double __x) __attribute__((__nothrow__));
extern long double __significandl(long double __x) __attribute__((__nothrow__));
extern long double copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __copysignl(long double __x, long double __y) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double nanl(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double __nanl(const char *__tagb) __attribute__((__nothrow__)) __attribute__((__const__));
extern int __isnanl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern int isnanl(long double __value) __attribute__((__nothrow__)) __attribute__((__const__));
extern long double j0l(long double) __attribute__((__nothrow__));
extern long double __j0l(long double) __attribute__((__nothrow__));
extern long double j1l(long double) __attribute__((__nothrow__));
extern long double __j1l(long double) __attribute__((__nothrow__));
extern long double jnl(int, long double) __attribute__((__nothrow__));
extern long double __jnl(int, long double) __attribute__((__nothrow__));
extern long double y0l(long double) __attribute__((__nothrow__));
extern long double __y0l(long double) __attribute__((__nothrow__));
extern long double y1l(long double) __attribute__((__nothrow__));
extern long double __y1l(long double) __attribute__((__nothrow__));
extern long double ynl(int, long double) __attribute__((__nothrow__));
extern long double __ynl(int, long double) __attribute__((__nothrow__));
extern long double erfl(long double) __attribute__((__nothrow__));
extern long double __erfl(long double) __attribute__((__nothrow__));
extern long double erfcl(long double) __attribute__((__nothrow__));
extern long double __erfcl(long double) __attribute__((__nothrow__));
extern long double lgammal(long double) __attribute__((__nothrow__));
extern long double __lgammal(long double) __attribute__((__nothrow__));
extern long double tgammal(long double) __attribute__((__nothrow__));
extern long double __tgammal(long double) __attribute__((__nothrow__));
extern long double gammal(long double) __attribute__((__nothrow__));
extern long double __gammal(long double) __attribute__((__nothrow__));
extern long double lgammal_r(long double, int *__signgamp) __attribute__((__nothrow__));
extern long double __lgammal_r(long double, int *__signgamp) __attribute__((__nothrow__));
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
extern long double scalbl(long double __x, long double __n) __attribute__((__nothrow__));
extern long double __scalbl(long double __x, long double __n) __attribute__((__nothrow__));
extern int signgam;
enum 
{
    FP_NAN = 0, 
    FP_INFINITE = 1, 
    FP_ZERO = 2, 
    FP_SUBNORMAL = 3, 
    FP_NORMAL = 4
};
typedef enum 
{
    _IEEE_ = - 1, 
    _SVID_, 
    _XOPEN_, 
    _POSIX_, 
    _ISOC_
} _LIB_VERSION_TYPE;
extern _LIB_VERSION_TYPE _LIB_VERSION;
struct exception
{
        int type;
        char *name;
        double arg1;
        double arg2;
        double retval;
};
extern int matherr(struct exception *__exc);
typedef int ptrdiff_t;
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
double alpha1;
double beta1;
double alpha2;
double beta2;
double C[4000][4000];
double A[4000][4000];
double B[4000][4000];
double D[4000][4000];
double E[4000][4000];
static void init_array()
{
    int i, j;
    alpha1 = 32412;
    beta1 = 2123;
    alpha2 = 132412;
    beta2 = 92123;
    for (i = 0;
        i < 4000;
        )
    {
        for (j = 0;
            j < 4000;
            )
        {
            A[i][j] = ((double) i * j) / 4000;
            j++;
        }
        i++;
    }
    for (i = 0;
        i < 4000;
        )
    {
        for (j = 0;
            j < 4000;
            )
        {
            B[i][j] = ((double) i * j + 1) / 4000;
            j++;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    MPI_Status stat;
    int size, myid;
    int *n1;
    char ***n2;
    MPI_Init(n1, n2);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    const int FTAG = 0;
    const int ATAG = 1;
    int partSize = 4000 / (size - 1), offset;
    int i, j, k;
    int ni = 4000;
    int nj = 4000;
    int nk = 4000;
    int nl = 4000;
    init_array();
    for (i = 0;
        i < 4000;
        )
    {
        for (j = 0;
            j < 4000;
            )
        {
            C[i][j] = ((double) i * j + 2) / 4000;
            j++;
        }
        i++;
    }
    if (myid == 0)
    {
        int followIN = 0;
        int killed = 0;
        for (int to = 1;
            to < size;
            ++to)
        {
            MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
            MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);
            MPI_Send(&C[followIN], partSize, MPI_DOUBLE, to, ATAG, MPI_COMM_WORLD);
            followIN += partSize;
        }
        while (1)
        {
            MPI_Recv(&offset, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            int source = stat.MPI_SOURCE;
            MPI_Recv(&partSize, 1, MPI_INT, 0, source, MPI_COMM_WORLD, &stat);
            MPI_Recv(&C[offset], partSize, MPI_DOUBLE, source, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            if ((followIN + partSize) < 4000)
            {
                MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                MPI_Send(&C[followIN], partSize, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
            }
            else
                if ((4000 - followIN) < partSize && (4000 - followIN) > 0)
                {
                    partSize = 4000 - followIN;
                    MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);
                    MPI_Send(&C[followIN], partSize, MPI_DOUBLE, source, ATAG, MPI_COMM_WORLD);
                }
            if ((followIN + partSize) > 4000)
            {
                MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);
                killed++;
            }
            followIN += partSize;
            if (killed == size - 1)
            {
                break;
            }
        }
    }
    if (myid != 0)
    {
        while (1)
        {
            MPI_Recv(&offset, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            if (stat.MPI_TAG == ATAG)
            {
                MPI_Recv(&partSize, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
                MPI_Recv(&C[offset], partSize, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                for (int i = offset;
                    i < offset + partSize;
                    ++i)
                    for (j = 0;
                        j < nj;
                        j++)
                    {
                        C[i][j] = 0;
                        for (k = 0;
                            k < nk;
                            ++k)
                            C[i][j] += A[i][k] * B[k][j];
                    }
                MPI_Send(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&partSize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&C[offset], partSize, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            }
            else
                if (stat.MPI_TAG == FTAG)
                {
                    break;
                }
        }
    }
    MPI_Finalize();
    double a = C[0][0];
    return 0;
}
