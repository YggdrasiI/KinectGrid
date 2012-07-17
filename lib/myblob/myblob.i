# 1 "myblob.c"
# 1 "/opt/kinect/MyBlobDetection//"
# 1 "<eingebaut>"
# 1 "<Kommandozeile>"
# 1 "myblob.c"



# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 324 "/usr/include/features.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/predefs.h" 1 3 4
# 325 "/usr/include/features.h" 2 3 4
# 357 "/usr/include/features.h" 3 4
# 1 "/usr/include/i386-linux-gnu/sys/cdefs.h" 1 3 4
# 378 "/usr/include/i386-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/wordsize.h" 1 3 4
# 379 "/usr/include/i386-linux-gnu/sys/cdefs.h" 2 3 4
# 358 "/usr/include/features.h" 2 3 4
# 389 "/usr/include/features.h" 3 4
# 1 "/usr/include/i386-linux-gnu/gnu/stubs.h" 1 3 4



# 1 "/usr/include/i386-linux-gnu/bits/wordsize.h" 1 3 4
# 5 "/usr/include/i386-linux-gnu/gnu/stubs.h" 2 3 4


# 1 "/usr/include/i386-linux-gnu/gnu/stubs-32.h" 1 3 4
# 8 "/usr/include/i386-linux-gnu/gnu/stubs.h" 2 3 4
# 390 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 3 4
typedef unsigned int size_t;
# 324 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 3 4
typedef int wchar_t;
# 34 "/usr/include/stdlib.h" 2 3 4








# 1 "/usr/include/i386-linux-gnu/bits/waitflags.h" 1 3 4
# 43 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/i386-linux-gnu/bits/waitstatus.h" 1 3 4
# 65 "/usr/include/i386-linux-gnu/bits/waitstatus.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 61 "/usr/include/endian.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/byteswap.h" 1 3 4
# 62 "/usr/include/endian.h" 2 3 4
# 66 "/usr/include/i386-linux-gnu/bits/waitstatus.h" 2 3 4

union wait
  {
    int w_status;
    struct
      {

 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;







      } __wait_terminated;
    struct
      {

 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;






      } __wait_stopped;
  };
# 44 "/usr/include/stdlib.h" 2 3 4
# 68 "/usr/include/stdlib.h" 3 4
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));
# 96 "/usr/include/stdlib.h" 3 4


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







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


# 140 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;




extern double atof (__const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (__const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (__const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





__extension__ extern long long int atoll (__const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





extern double strtod (__const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;





extern float strtof (__const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern long double strtold (__const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;





extern long int strtol (__const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




__extension__
extern long long int strtoq (__const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;





__extension__
extern long long int strtoll (__const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

# 311 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (__const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/i386-linux-gnu/sys/types.h" 1 3 4
# 28 "/usr/include/i386-linux-gnu/sys/types.h" 3 4


# 1 "/usr/include/i386-linux-gnu/bits/types.h" 1 3 4
# 28 "/usr/include/i386-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/wordsize.h" 1 3 4
# 29 "/usr/include/i386-linux-gnu/bits/types.h" 2 3 4


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




__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;







__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
# 131 "/usr/include/i386-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/typesizes.h" 1 3 4
# 132 "/usr/include/i386-linux-gnu/bits/types.h" 2 3 4


__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;

__extension__ typedef int __daddr_t;
__extension__ typedef long int __swblk_t;
__extension__ typedef int __key_t;


__extension__ typedef int __clockid_t;


__extension__ typedef void * __timer_t;


__extension__ typedef long int __blksize_t;




__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;


__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;


__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;

__extension__ typedef int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


__extension__ typedef int __intptr_t;


__extension__ typedef unsigned int __socklen_t;
# 31 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 61 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 99 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 58 "/usr/include/time.h" 3 4


typedef __clock_t clock_t;



# 74 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 92 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 134 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4
# 147 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 148 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 195 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 220 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/i386-linux-gnu/sys/select.h" 1 3 4
# 31 "/usr/include/i386-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/select.h" 1 3 4
# 32 "/usr/include/i386-linux-gnu/sys/select.h" 2 3 4


# 1 "/usr/include/i386-linux-gnu/bits/sigset.h" 1 3 4
# 24 "/usr/include/i386-linux-gnu/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/i386-linux-gnu/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/i386-linux-gnu/sys/select.h" 2 3 4

# 1 "/usr/include/i386-linux-gnu/bits/time.h" 1 3 4
# 31 "/usr/include/i386-linux-gnu/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/i386-linux-gnu/sys/select.h" 2 3 4


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 65 "/usr/include/i386-linux-gnu/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 97 "/usr/include/i386-linux-gnu/sys/select.h" 3 4

# 107 "/usr/include/i386-linux-gnu/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 119 "/usr/include/i386-linux-gnu/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 132 "/usr/include/i386-linux-gnu/sys/select.h" 3 4

# 221 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4


# 1 "/usr/include/i386-linux-gnu/sys/sysmacros.h" 1 3 4
# 30 "/usr/include/i386-linux-gnu/sys/sysmacros.h" 3 4


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 64 "/usr/include/i386-linux-gnu/sys/sysmacros.h" 3 4

# 224 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 271 "/usr/include/i386-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/pthreadtypes.h" 1 3 4
# 36 "/usr/include/i386-linux-gnu/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[36];
  long int __align;
} pthread_attr_t;


typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;




typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;


    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
  } __data;
  char __size[24];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  long int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  long int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;


    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
  char __size[32];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[20];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 272 "/usr/include/i386-linux-gnu/sys/types.h" 2 3 4



# 321 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));




extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;










extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));




extern void cfree (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/alloca.h" 1 3 4
# 25 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 26 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 498 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 531 "/usr/include/stdlib.h" 3 4





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
# 554 "/usr/include/stdlib.h" 3 4






extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));






extern char *getenv (__const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern char *__secure_getenv (__const char *__name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;





extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (__const char *__name, __const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (__const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 606 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 620 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 642 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 663 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 712 "/usr/include/stdlib.h" 3 4





extern int system (__const char *__command) ;

# 734 "/usr/include/stdlib.h" 3 4
extern char *realpath (__const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (__const void *, __const void *);
# 752 "/usr/include/stdlib.h" 3 4



extern void *bsearch (__const void *__key, __const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;



extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 771 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;



__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;







extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

# 808 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));







extern int mblen (__const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern int mbtowc (wchar_t *__restrict __pwc,
     __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__)) ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern size_t wcstombs (char *__restrict __s,
   __const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));








extern int rpmatch (__const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 896 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *__const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 948 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 964 "/usr/include/stdlib.h" 3 4

# 5 "myblob.c" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 30 "/usr/include/stdio.h" 3 4




# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 35 "/usr/include/stdio.h" 2 3 4
# 45 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 65 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 75 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 32 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 83 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4

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
# 53 "/usr/include/_G_config.h" 3 4
typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));
# 33 "/usr/include/libio.h" 2 3 4
# 53 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 54 "/usr/include/libio.h" 2 3 4
# 172 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 182 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 205 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 273 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

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
# 321 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 330 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 366 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, __const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 418 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 462 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 492 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 76 "/usr/include/stdio.h" 2 3 4




typedef __gnuc_va_list va_list;
# 109 "/usr/include/stdio.h" 3 4


typedef _G_fpos_t fpos_t;




# 165 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/stdio_lim.h" 1 3 4
# 166 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (__const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (__const char *__old, __const char *__new) __attribute__ ((__nothrow__ , __leaf__));




extern int renameat (int __oldfd, __const char *__old, int __newfd,
       __const char *__new) __attribute__ ((__nothrow__ , __leaf__));








extern FILE *tmpfile (void) ;
# 210 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
# 228 "/usr/include/stdio.h" 3 4
extern char *tempnam (__const char *__dir, __const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 253 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 267 "/usr/include/stdio.h" 3 4






extern FILE *fopen (__const char *__restrict __filename,
      __const char *__restrict __modes) ;




extern FILE *freopen (__const char *__restrict __filename,
        __const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 296 "/usr/include/stdio.h" 3 4

# 307 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, __const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
# 320 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, __const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));








extern int fprintf (FILE *__restrict __stream,
      __const char *__restrict __format, ...);




extern int printf (__const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      __const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, __const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (__const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, __const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       __const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        __const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

# 418 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, __const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, __const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     __const char *__restrict __format, ...) ;




extern int scanf (__const char *__restrict __format, ...) ;

extern int sscanf (__const char *__restrict __s,
     __const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 449 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, __const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (__const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (__const char *__restrict __s, __const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 469 "/usr/include/stdio.h" 3 4








extern int vfscanf (FILE *__restrict __s, __const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (__const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (__const char *__restrict __s,
      __const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 500 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (__const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (__const char *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 528 "/usr/include/stdio.h" 3 4









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 556 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 567 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 600 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;






extern char *gets (char *__s) ;

# 662 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;








extern int fputs (__const char *__restrict __s, FILE *__restrict __stream);





extern int puts (__const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (__const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

# 734 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (__const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

# 770 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 789 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, __const fpos_t *__pos);
# 812 "/usr/include/stdio.h" 3 4

# 821 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;








extern void perror (__const char *__s);






# 1 "/usr/include/i386-linux-gnu/bits/sys_errlist.h" 1 3 4
# 27 "/usr/include/i386-linux-gnu/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern __const char *__const sys_errlist[];
# 851 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 870 "/usr/include/stdio.h" 3 4
extern FILE *popen (__const char *__command, __const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 910 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 940 "/usr/include/stdio.h" 3 4

# 6 "myblob.c" 2
# 1 "/usr/include/time.h" 1 3 4
# 30 "/usr/include/time.h" 3 4








# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h" 1 3 4
# 39 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/i386-linux-gnu/bits/time.h" 1 3 4
# 43 "/usr/include/time.h" 2 3 4
# 131 "/usr/include/time.h" 3 4


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  __const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;
# 180 "/usr/include/time.h" 3 4



extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   __const char *__restrict __format,
   __const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

# 215 "/usr/include/time.h" 3 4
# 1 "/usr/include/xlocale.h" 1 3 4
# 28 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 216 "/usr/include/time.h" 2 3 4

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     __const char *__restrict __format,
     __const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 230 "/usr/include/time.h" 3 4



extern struct tm *gmtime (__const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (__const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));





extern struct tm *gmtime_r (__const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (__const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));





extern char *asctime (__const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime (__const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));







extern char *asctime_r (__const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime_r (__const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;





extern int stime (__const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
# 313 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 328 "/usr/include/time.h" 3 4
extern int nanosleep (__const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_settime (clockid_t __clock_id, __const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       __const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_settime (timer_t __timerid, int __flags,
     __const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
# 417 "/usr/include/time.h" 3 4

# 7 "myblob.c" 2

# 1 "myblob.h" 1



# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 1 3 4
# 34 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 3 4
# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 1 3 4
# 169 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 145 "/usr/include/limits.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/posix1_lim.h" 1 3 4
# 157 "/usr/include/i386-linux-gnu/bits/posix1_lim.h" 3 4
# 1 "/usr/include/i386-linux-gnu/bits/local_lim.h" 1 3 4
# 39 "/usr/include/i386-linux-gnu/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 40 "/usr/include/i386-linux-gnu/bits/local_lim.h" 2 3 4
# 158 "/usr/include/i386-linux-gnu/bits/posix1_lim.h" 2 3 4
# 146 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/i386-linux-gnu/bits/posix2_lim.h" 1 3 4
# 150 "/usr/include/limits.h" 2 3 4
# 170 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 2 3 4
# 8 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h" 2 3 4
# 5 "myblob.h" 2







# 1 "tree.h" 1







typedef struct {
 int x,y,width,height;
} MyBlobRect;


typedef struct Blob{
 int id;
 MyBlobRect roi;


 int area;
} Blob;


typedef struct Node Node;
 struct Node {
 Node *parent;
 Node *silbing;
 Node *child;
 int height;
 int width;
 Blob data;
};

static struct Node Leaf = { ((void *)0),((void *)0),((void *)0),0,0 };


static void gen_redundant_information(Node* root, int *pheight, int *psilbings){
 root->width = 0;
 if( root->child != ((void *)0) ){
  int height2=0;
  gen_redundant_information(root->child, &height2, &root->width);
  if( *pheight < height2+1 ) *pheight = height2+1;
 }
 if( root->silbing != ((void *)0) ){
  *psilbings++;
  gen_redundant_information(root->silbing,pheight,psilbings);
 }
}

static void add_child(Node *parent, Node *child){
 if( parent->child == ((void *)0) ){
  parent->child = child;
 }else{
  Node *cur = parent->child;
  while( cur->silbing != ((void *)0) ){
   cur = cur->silbing;
  }
  cur->silbing = child;
 }

 child->parent = parent;


 parent->width++;
 Node *p=parent, *c=child;
 while( p != ((void *)0) && p->height < c->height+1 ){
  p->height = c->height+1;
  c=p;
  p=p->parent;
 }
}

static int number_of_nodes(Node *root){
 int n = 1;
 Node *cur = root->child;
 while( cur != ((void *)0) ){
  n++;
  if( cur->child != ((void *)0) ) cur = cur->child;
  else if( cur->silbing != ((void *)0) ) cur = cur->silbing;
  else{
   cur = cur->parent;
   while(cur != root && cur->silbing == ((void *)0)) cur = cur->parent;
   cur = cur->silbing;
  }
 }
 return n;
}


static void print_tree(Node *root, int shift){
 int i;
 int shift2=0;


 printf("%2i (w%i,d%i) ",root->data.id, root->width, root->height);
 shift2+=12;
 if( root->child != ((void *)0)){
  printf("→");
  print_tree(root->child,shift+shift2);
 }else{
  printf("\n");
 }

 if( root->silbing != ((void *)0)){

  for(i=0;i<shift-1;i++) printf(" ");
  printf("↘");
  print_tree(root->silbing,shift);
 }}





static inline void swap_silbings(Node *a, Node *b)
{
 Node *p = a->parent;
 Node *c = p->child;
 Node *d = p->child;

 if(c==a) c == ((void *)0);
 else{
  while(c->silbing!=a) c=c->silbing;
 }
 if(d==b) d == ((void *)0);
 else{
  while(d->silbing!=b) d=d->silbing;
 }


 if( c == ((void *)0) ) p->child = b;
 else c->silbing = b;
 if( d == ((void *)0) ) p->child = a;
 else d->silbing = a;


 d = a->silbing;
 a->silbing = b->silbing;
 b->silbing = d;
}


static inline int cmp(Node *a, Node *b){
 if( a->height < b->height) return 0;
 if( a->height > b->height) return 1;
 if( a->width < b->width) return 0;
 if( a->width > b->width) return 1;





 int ret=0;
 Node *ca = a->child;
 Node *cb = b->child;
 while( ret == 0 && ca!=((void *)0) ){
  ret = cmp(ca,cb);
  ca=ca->silbing;
  cb=cb->silbing;
 }
 return ret;
}

static inline void swap_pnode(Node **a, Node **b)
{
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void quicksort_silbings(Node **begin, Node **end)
{
    Node **ptr;
    Node **split;
    if (end - begin <= 1)
        return;
    ptr = begin;
    split = begin + 1;
    while (++ptr != end) {

    if ( cmp(*ptr,*begin) ) {
            swap_pnode(ptr, split);
            ++split;
        }
    }
    swap_pnode(begin, split - 1);
    quicksort_silbings(begin, split - 1);
    quicksort_silbings(split, end);
}
# 198 "tree.h"
static void sort_tree(Node *root){
   if( root->width == 0) return;

   Node** children = malloc( root->width*sizeof(Node*) );
  Node** next = children;
  Node* c = root->child;
  while( c != ((void *)0) ){
   sort_tree(c);
   *next=c;
   c = c->silbing;
   next++;
  }

  if( root->width > 1){
   Node** end = next;

   quicksort_silbings(children, end);


   c = *children;
   root->child = c;
   next = children+1;
   while(next<end){
    c->silbing = *next;
    c=*next;
    next++;
   }
   c->silbing = ((void *)0);
  }

  free( children );
 }
# 238 "tree.h"
static void _gen_tree_id(Node *root,int **id, int *d){
 if( root->child != ((void *)0) ){

  **id = 0;
  (*id)++;
  _gen_tree_id(root->child, id, d);
 }else{
  *d = root->height;
 }
 if( root->silbing != ((void *)0) ){


  **id = (root->height - *d + 1);
  (*id)++;
  *d=root->height;
  _gen_tree_id(root->silbing, id, d);
 }
}




static void gen_tree_id(Node *root, int* id, int size){
 int last_height=0;

 *id = size;
 id++;
 _gen_tree_id(root,&id,&last_height);
 printf("\n");
}
# 276 "tree.h"
static const TREE_CHILDREN_MAX = 5;
static const TREE_DEPTH_MAX = 5;

static int tree_hashval( Node *root){
 return -1;
}
# 13 "myblob.h" 2
# 31 "myblob.h"
static Node* find_connection_components(
  const unsigned char *data,
  const int w, const int h,
  const unsigned char thresh,
  int* tree_size );


static Node* find_connection_components_with_roi(
  const unsigned char *data,
  const int w, const int h,
  const MyBlobRect roi,
  const unsigned char thresh,
  int* tree_size );


typedef enum { F_DEPTH_MIN=1, F_DEPTH_MAX=2, F_AREA_MIN=4, F_AREA_MAX=8 } FILTER;

typedef struct {
 int min_depth;
 int max_depth;
 int min_area;
 int max_area;
} Filter;

typedef struct {
 Node *tree;
 int tree_size;
 Filter filter;
 Node *it;
 int it_depth;
} Myblob;



extern Myblob *myblob_create();
extern void myblob_destroy(Myblob *blob );

extern void myblob_find_blobs( Myblob *blob,
  const unsigned char *data,
  const int w, const int h,
  const MyBlobRect roi,
  const unsigned char thresh );
extern void myblob_set_filter( Myblob *blob,const FILTER f,const int val);


extern Node *myblob_first( Myblob *blob);


extern Node *myblob_next( Myblob *blob);
# 9 "myblob.c" 2
# 44 "myblob.c"
static int sum_areas(const Node *root, const int *comp_size){
 int *val=&root->data.area;
 *val = *(comp_size + root->data.id );
 if( root->child != ((void *)0)) *val += sum_areas(root->child,comp_size);
 if( root->silbing != ((void *)0)) return *val+sum_areas(root->silbing, comp_size);
 else return *val;
}

static Node* find_connection_components(
  const unsigned char *data,
  const int w, const int h,
  const unsigned char thresh,
  int* tree_size )
{
 const MyBlobRect roi = {0,0,w,h};
 return find_connection_components_with_roi(data,w,h,roi,thresh,tree_size);
}


static Node* find_connection_components_with_roi(
  const unsigned char *data,
  const int w, const int h,
  const MyBlobRect roi,
  const unsigned char thresh,
  int* tree_size )
{

 int r=w-roi.x-roi.width;
  int b=h-roi.y-roi.height;
 if( r<0 || b<0 ){
  fprintf(stderr,"[blob.c] MyBlobRect not matching.\n");
  *tree_size = 0;
  return ((void *)0);
 }

 int id=-1;
 int a1,a2;
 int k;
 int max_comp = w+h;

 int* ids = malloc( w*h*sizeof(int) );

 int* anchors = malloc( max_comp*sizeof(int) );
 int* comp_size = malloc( max_comp*sizeof(int) );
 int* comp_same = malloc( max_comp*sizeof(int) );



 int* left_index = malloc( max_comp*sizeof(int) );
 int* right_index = malloc( max_comp*sizeof(int) );
 int* bottom_index = malloc( max_comp*sizeof(int) );
 int s=roi.x,z=roi.y;


 const unsigned char* dS = data+w*roi.y+roi.x;
 unsigned char* dR = dS+roi.width;

 const unsigned char* dE = dR + (roi.height-1)*w;


 unsigned char* dPi = dS;
 int* iPi = ids+(dS-data);
# 114 "myblob.c"
 id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }

 ++iPi; ++dPi;


 s++;






 for(;dPi<dR;++iPi,++dPi){
  if( *(dPi) > thresh ){
   if( *(dPi-1) > thresh ){

    *(iPi) = *(iPi-1);

    *(comp_size+ *(iPi)) += 1;


    ++*( right_index+*(iPi) );

   }else{
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }else{
   if( *(dPi-1) <= thresh ){

    *(iPi) = *(iPi-1);

    *(comp_size+ *(iPi)) += 1;


    ++*( right_index+*(iPi) );

   }else{
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }

  s++;




 }


 dPi+=r+roi.x;
 iPi+=r+roi.x;

 dR += w;

 s=roi.x;
 z++;




 for( ; dPi<dE ; dPi+=r+roi.x,iPi+=r+roi.x, dR+=w ){


  if( *(dPi) > thresh ){
   if( *(dPi-w) > thresh ){
    *(iPi) = *(iPi-w);
    *(comp_size+ *(iPi)) += 1;


    ++*( bottom_index+*(iPi) );


   }else if( *(dPi-w+1) > thresh ){
    *(iPi) = *(iPi-w+1);
    *(comp_size+ *(iPi)) += 1;


    ++*( bottom_index+*(iPi) );
    --*( left_index+*(iPi) );


   }else{
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }else{
   if( *(dPi-w) <= thresh){
    *(iPi) = *(iPi-w);
    *(comp_size+ *(iPi)) += 1;


    ++*( bottom_index+*(iPi) );


   }else if( *(dPi-w+1) <= thresh ){
    *(iPi) = *(iPi-w+1);
    *(comp_size+ *(iPi)) += 1;


    ++*( bottom_index+*(iPi) );
    --*( left_index+*(iPi) );


   }else{
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }


  ++iPi; ++dPi;

  s++;




  for( ; dPi<dR-1; ++iPi, ++dPi ){
   if( *(dPi) > thresh ){
    if( *(dPi-w) > thresh ){
     *(iPi) = *(iPi-w);
     *(comp_size+ *(iPi)) += 1;


     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );






     if( *(dPi-1) > thresh ){
      a1 = *(comp_same+*(iPi-1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-1)) = a2;
      }
     }
    }else if( *(dPi-1) > thresh ){
     *(iPi) = *(iPi-1);
     *(comp_size+ *(iPi)) += 1;


     if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );





     if( *(dPi-w+1) > thresh ){
      a1 = *(comp_same+*(iPi-w+1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-w+1)) = a2;
      }
     }



    }else if( *(dPi-w-1) > thresh ){
     *(iPi) = *(iPi-w-1);
     *(comp_size+ *(iPi)) += 1;


     if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );



     if( *(dPi-w+1) > thresh ){
      a1 = *(comp_same+*(iPi-w+1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-w+1)) = a2;
      }
     }



    }else if( *(dPi-w+1) > thresh ){
     *(iPi) = *(iPi-w+1);


     if( *( left_index+*(iPi) ) > s ) --*( left_index+*(iPi) );
     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );

     *(comp_size+ *(iPi)) += 1;

    }else{
     id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
    }
   }else{
    if( *(dPi-w) <= thresh ){
     *(iPi) = *(iPi-w);
     *(comp_size+ *(iPi)) += 1;


     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );






     if( *(dPi-1) <= thresh ){
      a1 = *(comp_same+*(iPi-1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-1)) = a2;
      }
     }
    }else if( *(dPi-1) <= thresh ){
     *(iPi) = *(iPi-1);
     *(comp_size+ *(iPi)) += 1;


     if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );





     if( *(dPi-w+1) <= thresh ){
      a1 = *(comp_same+*(iPi-w+1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-w+1)) = a2;
      }
     }



    }else if( *(dPi-w-1) <= thresh ){
     *(iPi) = *(iPi-w-1);
     *(comp_size+ *(iPi)) += 1;


     if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );



     if( *(dPi-w+1) <= thresh ){
      a1 = *(comp_same+*(iPi-w+1));
      a2 = *(comp_same+*(iPi ));
      if( a1<a2 ){
       *(comp_same+*(iPi )) = a1;
      }else if(a1>a2){
       *(comp_same+*(iPi-w+1)) = a2;
      }
     }



    }else if( *(dPi-w+1) <= thresh ){
     *(iPi) = *(iPi-w+1);


     if( *( left_index+*(iPi) ) > s ) --*( left_index+*(iPi) );
     if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );

     *(comp_size+ *(iPi)) += 1;

    }else{
     id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
    }
   }

   s++;


  }


  if( *(dPi) > thresh ){
   if( *(dPi-w) > thresh ){
    *(iPi) = *(iPi-w);
    *(comp_size+ *(iPi)) += 1;


    if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );






    if( *(dPi-1) > thresh ){
     a1 = *(comp_same+*(iPi-1));
     a2 = *(comp_same+*(iPi ));
     if( a1<a2 ){
      *(comp_same+*(iPi )) = a1;
     }else if(a1>a2){
      *(comp_same+*(iPi-1)) = a2;
     }
    }
   }else if( *(dPi-1) > thresh ){
    *(iPi) = *(iPi-1);
    *(comp_size+ *(iPi)) += 1;


    if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );


   }else if( *(dPi-w-1) > thresh ){
    *(iPi) = *(iPi-w-1);
    *(comp_size+ *(iPi)) += 1;


    if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
    if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );


   }else {
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }else{
   if( *(dPi-w) <= thresh ){
    *(iPi) = *(iPi-w);
    *(comp_size+ *(iPi)) += 1;


    if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );






    if( *(dPi-1) <= thresh ){
     a1 = *(comp_same+*(iPi-1));
     a2 = *(comp_same+*(iPi ));
     if( a1<a2 ){
      *(comp_same+*(iPi )) = a1;
     }else if(a1>a2){
      *(comp_same+*(iPi-1)) = a2;
     }
    }
   }else if( *(dPi-1) <= thresh ){
    *(iPi) = *(iPi-1);
    *(comp_size+ *(iPi)) += 1;


    if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );


   }else if( *(dPi-w-1) <= thresh ){
    *(iPi) = *(iPi-w-1);
    *(comp_size+ *(iPi)) += 1;


    if( *( right_index+*(iPi) ) < s ) ++*( right_index+*(iPi) );
    if( *( bottom_index+*(iPi) ) < z ) ++*( bottom_index+*(iPi) );


   }else {
    id++; *(iPi) = id; *(anchors+id) = dPi-dS; *(comp_same+id) = id; *(comp_size+id) = 1; *(left_index+id) = s; *(right_index+id) = s; *(bottom_index+id) = z; if( id>=max_comp ){ max_comp = (int) ( (float)w*h*max_comp/(dPi-data) ); anchors = realloc(anchors, max_comp*sizeof(int) ); comp_size = realloc(comp_size, max_comp*sizeof(int) ); comp_same = realloc(comp_same, max_comp*sizeof(int) ); left_index = realloc(left_index, max_comp*sizeof(int) ); right_index = realloc(right_index, max_comp*sizeof(int) ); bottom_index = realloc(bottom_index, max_comp*sizeof(int) ); }
   }
  }

  ++iPi; ++dPi;

 s=roi.x;
 z++;


 }
# 505 "myblob.c"
int nids = id+1;
int tmp_id,tmp_id2, real_ids_size=0,l;
int found;
int* real_ids = calloc( nids,sizeof(int) );
int* real_ids_inv = calloc( nids,sizeof(int) );

 for(k=0;k<nids;k++){
  tmp_id = k;
  tmp_id2 = *(comp_same+tmp_id);
  while( tmp_id2 != tmp_id ){

   *(comp_size+tmp_id2) += *(comp_size+tmp_id);
   *(comp_size+tmp_id) = 0;


   if( *( left_index+tmp_id2 ) > *( left_index+tmp_id ) )
    *( left_index+tmp_id2 ) = *( left_index+tmp_id );
   if( *( right_index+tmp_id2 ) < *( right_index+tmp_id ) )
    *( right_index+tmp_id2 ) = *( right_index+tmp_id );
   if( *( bottom_index+tmp_id2 ) < *( bottom_index+tmp_id ) )
    *( bottom_index+tmp_id2 ) = *( bottom_index+tmp_id );

   tmp_id = tmp_id2;
   tmp_id2 = *(comp_same+tmp_id);
  }


  found = 0;
  for(l=0;l<real_ids_size;l++){
   if( *(real_ids+l) == tmp_id ){
    found = 1;
    break;
   }
  }
  if( !found ){
   *(real_ids+real_ids_size) = tmp_id;
   *(real_ids_inv+tmp_id) = real_ids_size;
   real_ids_size++;
  }
 }







  int *tree_id_relation = malloc( (real_ids_size+1)*sizeof(int) );

  Node *tree = malloc( (real_ids_size+1)*sizeof(Node) );

 for(l=0;l<real_ids_size+1;l++) *(tree+l)=Leaf;

 Node *root = tree;
 Node *cur = tree;
 int anchor, parent_id;
 int end = w*h;
 root->data.id = -1;
 MyBlobRect *rect;

 for(l=0;l<real_ids_size;l++){
  cur++;
  rect = &cur->data.roi;

  cur->data.id = *(real_ids+l);

  anchor = *(anchors+*(real_ids+l));

  rect->y = anchor/w + roi.y;
  rect->height = *(bottom_index + *(real_ids+l)) - rect->y + 1;
  rect->x = *(left_index + *(real_ids+l));
  rect->width = *(right_index + *(real_ids+l)) - rect->x + 1;
  printf("MyBlobRect of %i: x=%i y=%i w=%i h=%i\n",cur->data.id,
    rect->x, rect->y,
    rect->width, rect->height);





  if( anchor<roi.width ){



   add_child(root, cur );
  }else{

   tmp_id = *(ids+anchor-w);

   tmp_id2 = *(comp_same+tmp_id);
   while( tmp_id != tmp_id2 ){
    tmp_id = tmp_id2;
    tmp_id2 = *(comp_same+tmp_id);
   }


   add_child( root + 1 + *(real_ids_inv+tmp_id ),
     cur );
  }

 }


 sum_areas(root->child, comp_size);

 sort_tree(root->child);


 free(tree_id_relation);

 free(real_ids);
 free(real_ids_inv);
 free(comp_same);
 free(comp_size);
 free(anchors);
 free(ids);
 free(left_index);
 free(right_index);
 free(bottom_index);


 *tree_size = real_ids_size+1;
 return tree;
}






Myblob *myblob_create(){
 Myblob *blob = malloc(sizeof(Myblob) );
 blob->tree = ((void *)0);
 blob->tree_size = 0;
 Filter filter = {0,2147483647,0,2147483647};
 blob->filter = filter;
 return blob;
}

void myblob_destroy(Myblob *blob){
 if( blob->tree != ((void *)0) ){
  free(blob->tree);
  blob->tree = ((void *)0);
  blob->tree_size = 0;
 }
 free(blob);
}

void myblob_set_filter(Myblob *blob, const FILTER f, const int val){
 switch(f){
  case F_DEPTH_MIN: blob->filter.min_depth=val;
           break;
  case F_DEPTH_MAX: blob->filter.max_depth=val;
           break;
  case F_AREA_MIN: blob->filter.min_area=val;
           break;
  case F_AREA_MAX: blob->filter.max_area=val;
           break;
 }
}

void myblob_find_blobs(Myblob *blob, const unsigned char *data, const int w, const int h, const MyBlobRect roi, const unsigned char thresh){

 if( blob->tree != ((void *)0)){
  free(blob->tree);
  blob->tree = ((void *)0);
  blob->tree_size = 0;
 }

 blob->tree = find_connection_components_with_roi( data, w, h, roi, thresh, &blob->tree_size);
}

Node *myblob_first( Myblob *blob){
 blob->it = blob->tree;
 blob->it_depth = -1;
 return myblob_next(blob);
}

Node *myblob_next(Myblob *blob){

 if( blob->it->child != ((void *)0)){
  blob->it = blob->it->child;
  blob->it_depth++;
 }else if( blob->it->silbing != ((void *)0) ){
  blob->it = blob->it->silbing;
 }else{
  blob->it = blob->it->parent;
  blob->it_depth--;
 }


 do{
  if( blob->it_depth < blob->filter.min_depth
    || blob->it->data.area > blob->filter.max_area ){
   if( blob->it->child != ((void *)0)){
    blob->it = blob->it->child;
    blob->it_depth++;
    continue;
   }
   if( blob->it->silbing != ((void *)0) ){
    blob->it = blob->it->silbing;
    continue;
   }
   blob->it = blob->it->parent;
   blob->it_depth--;
   continue;
  }
  if( blob->it_depth > blob->filter.max_depth ){
   blob->it = blob->it->parent;
   blob->it_depth--;
   continue;
  }
  if( blob->it->data.area < blob->filter.min_depth ){
   if( blob->it->silbing != ((void *)0) ){
    blob->it = blob->it->silbing;
    continue;
   }
   blob->it = blob->it->parent;
   blob->it_depth--;
   continue;
  }

  return blob->it;

 }while( blob->it != blob->tree );

 return ((void *)0);
}
