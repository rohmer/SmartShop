/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* allow SHA1 as an acceptable hash for digital signatures */
/* #undef ALLOW_SHA1 */

/* Define to the number of bits in type 'ptrdiff_t'. */
/* #undef BITSIZEOF_PTRDIFF_T */

/* Define to the number of bits in type 'sig_atomic_t'. */
/* #undef BITSIZEOF_SIG_ATOMIC_T */

/* Define to the number of bits in type 'size_t'. */
/* #undef BITSIZEOF_SIZE_T */

/* Define to the number of bits in type 'wchar_t'. */
/* #undef BITSIZEOF_WCHAR_T */

/* Define to the number of bits in type 'wint_t'. */
/* #undef BITSIZEOF_WINT_T */

/* C99 macros are supported */
#define C99_MACROS 1

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define as the bit index in the word where to find bit 0 of the exponent of
   'double'. */
#define DBL_EXPBIT0_BIT 20

/* Define as the word index where to find the exponent of 'double'. */
#define DBL_EXPBIT0_WORD 1

/* use the given certificate blacklist file */
/* #undef DEFAULT_BLACKLIST_FILE */

/* use the given CRL file */
/* #undef DEFAULT_CRL_FILE */

/* The default priority string */
#define DEFAULT_PRIORITY_STRING "NORMAL"

/* use the given directory as default trust store */
/* #undef DEFAULT_TRUST_STORE_DIR */

/* use the given file default trust store */
#define DEFAULT_TRUST_STORE_FILE "/etc/ssl/certs/ca-certificates.crt"

/* use the given pkcs11 uri as default trust store */
/* #undef DEFAULT_TRUST_STORE_PKCS11 */

/* Whether to disable system configuration */
/* #undef DISABLE_SYSTEM_CONFIG */

/* Dynamic use of ncrypt API (win32) */
/* #undef DYN_NCRYPT */

/* enable ALPN support */
#define ENABLE_ALPN 1

/* enable anonymous authentication */
#define ENABLE_ANON 1

/* Enable cryptodev support */
/* #undef ENABLE_CRYPTODEV */

/* enable DHE */
#define ENABLE_DHE 1

/* enable DTLS-SRTP support */
#define ENABLE_DTLS_SRTP 1

/* enable DHE */
#define ENABLE_ECDHE 1

/* Enable FIPS140-2 mode */
/* #undef ENABLE_FIPS140 */

/* enable GOST */
#define ENABLE_GOST 1

/* enable heartbeat support */
#define ENABLE_HEARTBEAT 1

/* nls support in libopts */
#define ENABLE_NLS 1

/* Enable all curves */
#define ENABLE_NON_SUITEB_CURVES 1

/* enable OCSP support */
#define ENABLE_OCSP 1

/* Enable padlock acceleration */
/* #undef ENABLE_PADLOCK */

/* Build PKCS#11 support */
#define ENABLE_PKCS11 1

/* enable PSK authentication */
#define ENABLE_PSK 1

/* enable SRP authentication */
#define ENABLE_SRP 1

/* enable SSL2.0 support for client hello */
#define ENABLE_SSL2 1

/* enable SSL3.0 support */
/* #undef ENABLE_SSL3 */

/* Define this to 1 if F_DUPFD behavior does not match POSIX */
/* #undef FCNTL_DUPFD_BUGGY */

/* The FIPS140-2 integrity key */
/* #undef FIPS_KEY */

/* Define to nothing if C supports flexible array members, and to 1 if it does
   not. That way, with a declaration like 'struct s { int n; short
   d[FLEXIBLE_ARRAY_MEMBER]; };', the struct hack can be used with pre-C99
   compilers. Use 'FLEXSIZEOF (struct s, d, N * sizeof (short))' to calculate
   the size in bytes of such a struct containing an N-element array. */
#define FLEXIBLE_ARRAY_MEMBER /**/

/* fopen(3) accepts a 'b' in the mode flag */
#define FOPEN_BINARY_FLAG "b"

/* fopen(3) accepts a 't' in the mode flag */
#define FOPEN_TEXT_FLAG "t"

/* Define to 1 if fopen() fails to recognize a trailing slash. */
/* #undef FOPEN_TRAILING_SLASH_BUG */

/* Define to 1 if the system's ftello function has the Solaris bug. */
/* #undef FTELLO_BROKEN_AFTER_SWITCHING_FROM_READ_TO_WRITE */

/* Define to 1 if ungetc is broken when used on arbitrary bytes. */
/* #undef FUNC_UNGETC_BROKEN */

/* Enable fuzzer target -not for production */
/* #undef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION */

/* Define if gettimeofday clobbers the localtime buffer. */
/* #undef GETTIMEOFDAY_CLOBBERS_LOCALTIME */

/* Define this to 'void' or 'struct timezone' to match the system's
   declaration of the second argument to gettimeofday. */
#define GETTIMEOFDAY_TIMEZONE void

/* The soname of gmp library */
#define GMP_LIBRARY_SONAME "libgmp.so.10"

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module fopen-gnu shall be considered present. */
#define GNULIB_FOPEN_GNU 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module fscanf shall be considered present. */
#define GNULIB_FSCANF 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module isblank shall be considered present. */
#define GNULIB_ISBLANK IN_GNUTLS_GNULIB_TESTS

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module lock shall be considered present. */
#define GNULIB_LOCK IN_GNUTLS_GNULIB_TESTS

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module msvc-nothrow shall be considered present. */
#define GNULIB_MSVC_NOTHROW 1

/* Define to 1 if printf and friends should be labeled with attribute
   "__gnu_printf__" instead of "__printf__" */
/* #undef GNULIB_PRINTF_ATTRIBUTE_FLAVOR_GNU */

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module scanf shall be considered present. */
#define GNULIB_SCANF 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module snprintf shall be considered present. */
#define GNULIB_SNPRINTF 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module strerror shall be considered present. */
#define GNULIB_STRERROR IN_GNUTLS_GNULIB_TESTS

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module strerror_r-posix shall be considered present. */
#define GNULIB_STRERROR_R_POSIX IN_GNUTLS_GNULIB_TESTS

/* Define to 1 when the gnulib module accept should be tested. */
#define GNULIB_TEST_ACCEPT 1

/* Define to 1 when the gnulib module bind should be tested. */
#define GNULIB_TEST_BIND 1

/* Define to 1 when the gnulib module cloexec should be tested. */
#define GNULIB_TEST_CLOEXEC 1

/* Define to 1 when the gnulib module close should be tested. */
#define GNULIB_TEST_CLOSE 1

/* Define to 1 when the gnulib module connect should be tested. */
#define GNULIB_TEST_CONNECT 1

/* Define to 1 when the gnulib module dup2 should be tested. */
#define GNULIB_TEST_DUP2 1

/* Define to 1 when the gnulib module environ should be tested. */
#define GNULIB_TEST_ENVIRON 1

/* Define to 1 when the gnulib module explicit_bzero should be tested. */
#define GNULIB_TEST_EXPLICIT_BZERO 1

/* Define to 1 when the gnulib module fcntl should be tested. */
#define GNULIB_TEST_FCNTL 1

/* Define to 1 when the gnulib module fdopen should be tested. */
#define GNULIB_TEST_FDOPEN 1

/* Define to 1 when the gnulib module fopen should be tested. */
#define GNULIB_TEST_FOPEN 1

/* Define to 1 when the gnulib module fseek should be tested. */
#define GNULIB_TEST_FSEEK 1

/* Define to 1 when the gnulib module fseeko should be tested. */
#define GNULIB_TEST_FSEEKO 1

/* Define to 1 when the gnulib module fstat should be tested. */
#define GNULIB_TEST_FSTAT 1

/* Define to 1 when the gnulib module ftell should be tested. */
#define GNULIB_TEST_FTELL 1

/* Define to 1 when the gnulib module ftello should be tested. */
#define GNULIB_TEST_FTELLO 1

/* Define to 1 when the gnulib module ftruncate should be tested. */
#define GNULIB_TEST_FTRUNCATE 1

/* Define to 1 when the gnulib module getaddrinfo should be tested. */
#define GNULIB_TEST_GETADDRINFO 1

/* Define to 1 when the gnulib module getcwd should be tested. */
#define GNULIB_TEST_GETCWD 1

/* Define to 1 when the gnulib module getdelim should be tested. */
#define GNULIB_TEST_GETDELIM 1

/* Define to 1 when the gnulib module getdtablesize should be tested. */
#define GNULIB_TEST_GETDTABLESIZE 1

/* Define to 1 when the gnulib module getline should be tested. */
#define GNULIB_TEST_GETLINE 1

/* Define to 1 when the gnulib module getpagesize should be tested. */
#define GNULIB_TEST_GETPAGESIZE 1

/* Define to 1 when the gnulib module getpass should be tested. */
#define GNULIB_TEST_GETPASS 1

/* Define to 1 when the gnulib module getpeername should be tested. */
#define GNULIB_TEST_GETPEERNAME 1

/* Define to 1 when the gnulib module gettimeofday should be tested. */
#define GNULIB_TEST_GETTIMEOFDAY 1

/* Define to 1 when the gnulib module ioctl should be tested. */
#define GNULIB_TEST_IOCTL 1

/* Define to 1 when the gnulib module listen should be tested. */
#define GNULIB_TEST_LISTEN 1

/* Define to 1 when the gnulib module localename should be tested. */
#define GNULIB_TEST_LOCALENAME 1

/* Define to 1 when the gnulib module lseek should be tested. */
#define GNULIB_TEST_LSEEK 1

/* Define to 1 when the gnulib module lstat should be tested. */
#define GNULIB_TEST_LSTAT 1

/* Define to 1 when the gnulib module malloc-posix should be tested. */
#define GNULIB_TEST_MALLOC_POSIX 1

/* Define to 1 when the gnulib module memchr should be tested. */
#define GNULIB_TEST_MEMCHR 1

/* Define to 1 when the gnulib module memmem should be tested. */
#define GNULIB_TEST_MEMMEM 1

/* Define to 1 when the gnulib module mktime should be tested. */
#define GNULIB_TEST_MKTIME 1

/* Define to 1 when the gnulib module nanosleep should be tested. */
#define GNULIB_TEST_NANOSLEEP 1

/* Define to 1 when the gnulib module open should be tested. */
#define GNULIB_TEST_OPEN 1

/* Define to 1 when the gnulib module perror should be tested. */
#define GNULIB_TEST_PERROR 1

/* Define to 1 when the gnulib module pipe should be tested. */
#define GNULIB_TEST_PIPE 1

/* Define to 1 when the gnulib module pthread_sigmask should be tested. */
#define GNULIB_TEST_PTHREAD_SIGMASK 1

/* Define to 1 when the gnulib module pthread-thread should be tested. */
#define GNULIB_TEST_PTHREAD_THREAD 1

/* Define to 1 when the gnulib module putenv should be tested. */
#define GNULIB_TEST_PUTENV 1

/* Define to 1 when the gnulib module raise should be tested. */
#define GNULIB_TEST_RAISE 1

/* Define to 1 when the gnulib module realloc-posix should be tested. */
#define GNULIB_TEST_REALLOC_POSIX 1

/* Define to 1 when the gnulib module recv should be tested. */
#define GNULIB_TEST_RECV 1

/* Define to 1 when the gnulib module recvfrom should be tested. */
#define GNULIB_TEST_RECVFROM 1

/* Define to 1 when the gnulib module secure_getenv should be tested. */
#define GNULIB_TEST_SECURE_GETENV 1

/* Define to 1 when the gnulib module select should be tested. */
#define GNULIB_TEST_SELECT 1

/* Define to 1 when the gnulib module send should be tested. */
#define GNULIB_TEST_SEND 1

/* Define to 1 when the gnulib module sendto should be tested. */
#define GNULIB_TEST_SENDTO 1

/* Define to 1 when the gnulib module setenv should be tested. */
#define GNULIB_TEST_SETENV 1

/* Define to 1 when the gnulib module setlocale should be tested. */
#define GNULIB_TEST_SETLOCALE 1

/* Define to 1 when the gnulib module setlocale_null should be tested. */
#define GNULIB_TEST_SETLOCALE_NULL 1

/* Define to 1 when the gnulib module setsockopt should be tested. */
#define GNULIB_TEST_SETSOCKOPT 1

/* Define to 1 when the gnulib module shutdown should be tested. */
#define GNULIB_TEST_SHUTDOWN 1

/* Define to 1 when the gnulib module sigaction should be tested. */
#define GNULIB_TEST_SIGACTION 1

/* Define to 1 when the gnulib module sigprocmask should be tested. */
#define GNULIB_TEST_SIGPROCMASK 1

/* Define to 1 when the gnulib module sleep should be tested. */
#define GNULIB_TEST_SLEEP 1

/* Define to 1 when the gnulib module snprintf should be tested. */
#define GNULIB_TEST_SNPRINTF 1

/* Define to 1 when the gnulib module socket should be tested. */
#define GNULIB_TEST_SOCKET 1

/* Define to 1 when the gnulib module stat should be tested. */
#define GNULIB_TEST_STAT 1

/* Define to 1 when the gnulib module strdup should be tested. */
#define GNULIB_TEST_STRDUP 1

/* Define to 1 when the gnulib module strerror should be tested. */
#define GNULIB_TEST_STRERROR 1

/* Define to 1 when the gnulib module strerror_r should be tested. */
#define GNULIB_TEST_STRERROR_R 1

/* Define to 1 when the gnulib module strndup should be tested. */
#define GNULIB_TEST_STRNDUP 1

/* Define to 1 when the gnulib module strnlen should be tested. */
#define GNULIB_TEST_STRNLEN 1

/* Define to 1 when the gnulib module strtok_r should be tested. */
#define GNULIB_TEST_STRTOK_R 1

/* Define to 1 when the gnulib module strverscmp should be tested. */
#define GNULIB_TEST_STRVERSCMP 1

/* Define to 1 when the gnulib module symlink should be tested. */
#define GNULIB_TEST_SYMLINK 1

/* Define to 1 when the gnulib module timegm should be tested. */
#define GNULIB_TEST_TIMEGM 1

/* Define to 1 when the gnulib module time_r should be tested. */
#define GNULIB_TEST_TIME_R 1

/* Define to 1 when the gnulib module time_rz should be tested. */
#define GNULIB_TEST_TIME_RZ 1

/* Define to 1 when the gnulib module tzset should be tested. */
#define GNULIB_TEST_TZSET 1

/* Define to 1 when the gnulib module uninorm/u16-normalize should be tested.
   */
#define GNULIB_TEST_UNINORM_U16_NORMALIZE 1

/* Define to 1 when the gnulib module uninorm/u32-normalize should be tested.
   */
#define GNULIB_TEST_UNINORM_U32_NORMALIZE 1

/* Define to 1 when the gnulib module uninorm/u8-normalize should be tested.
   */
#define GNULIB_TEST_UNINORM_U8_NORMALIZE 1

/* Define to 1 when the gnulib module unsetenv should be tested. */
#define GNULIB_TEST_UNSETENV 1

/* Define to 1 when the gnulib module vasprintf should be tested. */
#define GNULIB_TEST_VASPRINTF 1

/* Define to 1 when the gnulib module vsnprintf should be tested. */
#define GNULIB_TEST_VSNPRINTF 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u16-mbtoucr shall be considered present.
   */
#define GNULIB_UNISTR_U16_MBTOUCR 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u16-mbtouc-unsafe shall be considered
   present. */
#define GNULIB_UNISTR_U16_MBTOUC_UNSAFE 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u16-uctomb shall be considered present. */
#define GNULIB_UNISTR_U16_UCTOMB 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u32-mbtouc-unsafe shall be considered
   present. */
#define GNULIB_UNISTR_U32_MBTOUC_UNSAFE 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u32-uctomb shall be considered present. */
#define GNULIB_UNISTR_U32_UCTOMB 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u8-mbtoucr shall be considered present. */
#define GNULIB_UNISTR_U8_MBTOUCR 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u8-mbtouc-unsafe shall be considered
   present. */
#define GNULIB_UNISTR_U8_MBTOUC_UNSAFE 1

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u8-uctomb shall be considered present. */
#define GNULIB_UNISTR_U8_UCTOMB 1

/* Make sure we don't use old features in code. */
#define GNUTLS_COMPAT_H 1

/* We allow temporarily usage of deprecated functions - until they are
   removed. */
#define GNUTLS_INTERNAL_BUILD 1

/* The soname of gnutls library */
#define GNUTLS_LIBRARY_SONAME "libgnutls.so.30"

/* Additional cast to bring void* to a type castable to int. */
#define GNUTLS_POINTER_TO_INT_CAST (long)

/* Define to 1 if you have 'alloca' after including <alloca.h>, a header that
   may be supplied by this distribution. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if the system has the type `BCRYPT_ALG_HANDLE'. */
/* #undef HAVE_BCRYPT_ALG_HANDLE */

/* Define to 1 if you have the <bp-sym.h> header file. */
/* #undef HAVE_BP_SYM_H */

/* Define to 1 if nanosleep mishandles large arguments. */
/* #undef HAVE_BUG_BIG_NANOSLEEP */

/* Define to 1 if you have the <byteswap.h> header file. */
#define HAVE_BYTESWAP_H 1

/* Define to 1 if you have the `canonicalize_file_name' function. */
#define HAVE_CANONICALIZE_FILE_NAME 1

/* Define to 1 if you have the `catgets' function. */
#define HAVE_CATGETS 1

/* Define to 1 if you have the Mac OS X function
   CFLocaleCopyPreferredLanguages in the CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYPREFERREDLANGUAGES */

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if you have the `chmod' function. */
#define HAVE_CHMOD 1

/* Define to 1 if you have the `chsize' function. */
/* #undef HAVE_CHSIZE */

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the `clock_settime' function. */
#define HAVE_CLOCK_SETTIME 1

/* Define if you have compound literals. */
#define HAVE_COMPOUND_LITERALS 1

/* Define to 1 if you have the <cpuid.h> header file. */
/* #undef HAVE_CPUID_H */

/* Define to 1 if you have the <crtdefs.h> header file. */
/* #undef HAVE_CRTDEFS_H */

/* Define to 1 if you have the `daemon' function. */
#define HAVE_DAEMON 1

/* Enable the DANE library */
/* #undef HAVE_DANE */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `alarm', and to 0 if you don't.
   */
#define HAVE_DECL_ALARM 1

/* Define to 1 if you have the declaration of `fflush_unlocked', and to 0 if
   you don't. */
#define HAVE_DECL_FFLUSH_UNLOCKED 1

/* Define to 1 if you have the declaration of `flockfile', and to 0 if you
   don't. */
#define HAVE_DECL_FLOCKFILE 1

/* Define to 1 if you have the declaration of `fputs_unlocked', and to 0 if
   you don't. */
#define HAVE_DECL_FPUTS_UNLOCKED 1

/* Define to 1 if you have the declaration of `freeaddrinfo', and to 0 if you
   don't. */
#define HAVE_DECL_FREEADDRINFO 1

/* Define to 1 if you have the declaration of `fseeko', and to 0 if you don't.
   */
#define HAVE_DECL_FSEEKO 1

/* Define to 1 if you have the declaration of `ftello', and to 0 if you don't.
   */
#define HAVE_DECL_FTELLO 1

/* Define to 1 if you have the declaration of `funlockfile', and to 0 if you
   don't. */
#define HAVE_DECL_FUNLOCKFILE 1

/* Define to 1 if you have the declaration of `gai_strerror', and to 0 if you
   don't. */
#define HAVE_DECL_GAI_STRERROR 1

/* Define to 1 if you have the declaration of `gai_strerrorA', and to 0 if you
   don't. */
#define HAVE_DECL_GAI_STRERRORA 0

/* Define to 1 if you have the declaration of `getaddrinfo', and to 0 if you
   don't. */
#define HAVE_DECL_GETADDRINFO 1

/* Define to 1 if you have the declaration of `getc_unlocked', and to 0 if you
   don't. */
/* #undef HAVE_DECL_GETC_UNLOCKED */

/* Define to 1 if you have the declaration of `getdelim', and to 0 if you
   don't. */
#define HAVE_DECL_GETDELIM 1

/* Define to 1 if you have the declaration of `getdtablesize', and to 0 if you
   don't. */
#define HAVE_DECL_GETDTABLESIZE 1

/* Define to 1 if you have the declaration of `getline', and to 0 if you
   don't. */
#define HAVE_DECL_GETLINE 1

/* Define to 1 if you have the declaration of `getnameinfo', and to 0 if you
   don't. */
#define HAVE_DECL_GETNAMEINFO 1

/* Define to 1 if you have the declaration of `inet_ntop', and to 0 if you
   don't. */
#define HAVE_DECL_INET_NTOP 1

/* Define to 1 if you have the declaration of `inet_pton', and to 0 if you
   don't. */
#define HAVE_DECL_INET_PTON 1

/* Define to 1 if you have the declaration of `localtime_r', and to 0 if you
   don't. */
#define HAVE_DECL_LOCALTIME_R 1

/* Define to 1 if you have the declaration of `memmem', and to 0 if you don't.
   */
#define HAVE_DECL_MEMMEM 1

/* Define to 1 if you have the declaration of `program_invocation_name', and
   to 0 if you don't. */
#define HAVE_DECL_PROGRAM_INVOCATION_NAME 1

/* Define to 1 if you have the declaration of `program_invocation_short_name',
   and to 0 if you don't. */
#define HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME 1

/* Define to 1 if you have the declaration of `putc_unlocked', and to 0 if you
   don't. */
#define HAVE_DECL_PUTC_UNLOCKED 1

/* Define to 1 if you have the declaration of `setenv', and to 0 if you don't.
   */
#define HAVE_DECL_SETENV 1

/* Define to 1 if you have the declaration of `sleep', and to 0 if you don't.
   */
#define HAVE_DECL_SLEEP 1

/* Define to 1 if you have the declaration of `snprintf', and to 0 if you
   don't. */
#define HAVE_DECL_SNPRINTF 1

/* Define to 1 if you have the declaration of `strdup', and to 0 if you don't.
   */
#define HAVE_DECL_STRDUP 1

/* Define to 1 if you have the declaration of `strerror_r', and to 0 if you
   don't. */
#define HAVE_DECL_STRERROR_R 1

/* Define to 1 if you have the declaration of `strncasecmp', and to 0 if you
   don't. */
#define HAVE_DECL_STRNCASECMP 1

/* Define to 1 if you have the declaration of `strndup', and to 0 if you
   don't. */
#define HAVE_DECL_STRNDUP 1

/* Define to 1 if you have the declaration of `strnlen', and to 0 if you
   don't. */
#define HAVE_DECL_STRNLEN 1

/* Define to 1 if you have the declaration of `strtok_r', and to 0 if you
   don't. */
#define HAVE_DECL_STRTOK_R 1

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define to 1 if you have the declaration of `unsetenv', and to 0 if you
   don't. */
#define HAVE_DECL_UNSETENV 1

/* Define to 1 if you have the declaration of `vsnprintf', and to 0 if you
   don't. */
#define HAVE_DECL_VSNPRINTF 1

/* Define to 1 if you have the declaration of `_fseeki64', and to 0 if you
   don't. */
/* #undef HAVE_DECL__FSEEKI64 */

/* Define to 1 if you have the declaration of `_putenv', and to 0 if you
   don't. */
/* #undef HAVE_DECL__PUTENV */

/* Define to 1 if you have the declaration of `_snprintf', and to 0 if you
   don't. */
#define HAVE_DECL__SNPRINTF 0

/* Define to 1 if you have the declaration of `__fsetlocking', and to 0 if you
   don't. */
/* #undef HAVE_DECL___FSETLOCKING */

/* Define this if /dev/zero is readable device */
#define HAVE_DEV_ZERO 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define to 1 if you have the 'dup2' function. */
#define HAVE_DUP2 1

/* Define to 1 if you have the `duplocale' function. */
#define HAVE_DUPLOCALE 1

/* Define if you have the declaration of environ. */
#define HAVE_ENVIRON_DECL 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the `explicit_bzero' function. */
#define HAVE_EXPLICIT_BZERO 1

/* Define to 1 if you have the `explicit_memset' function. */
/* #undef HAVE_EXPLICIT_MEMSET */

/* Define if the locale_t type contains insufficient information, as on
   OpenBSD. */
/* #undef HAVE_FAKE_LOCALES */

/* Define to 1 if you have the `fchmod' function. */
#define HAVE_FCHMOD 1

/* Define to 1 if you have the `fcntl' function. */
#define HAVE_FCNTL 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <features.h> header file. */
#define HAVE_FEATURES_H 1

/* Define to 1 if you have the `flockfile' function. */
/* #undef HAVE_FLOCKFILE */

/* Define to 1 if you have the `fmemopen' function. */
#define HAVE_FMEMOPEN 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `freelocale' function. */
#define HAVE_FREELOCALE 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `fstat' function. */
#define HAVE_FSTAT 1

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `funlockfile' function. */
/* #undef HAVE_FUNLOCKFILE */

/* Define to 1 if getaddrinfo exists, or to 0 otherwise. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getauxval' function. */
#define HAVE_GETAUXVAL 1

/* Define to 1 if you have the `getdelim' function. */
#define HAVE_GETDELIM 1

/* Define to 1 if you have the `getdtablesize' function. */
#define HAVE_GETDTABLESIZE 1

/* Define to 1 if you have the `getegid' function. */
#define HAVE_GETEGID 1

/* Enable the OpenBSD getentropy function */
/* #undef HAVE_GETENTROPY */

/* Define to 1 if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define to 1 if you have the `getgid' function. */
#define HAVE_GETGID 1

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `getlocalename_l' function. */
/* #undef HAVE_GETLOCALENAME_L */

/* Define to 1 if you have the `getpass' function. */
#define HAVE_GETPASS 1

/* Define to 1 if you have the `getpid' function. */
#define HAVE_GETPID 1

/* Define to 1 if you have the `getpwuid_r' function. */
#define HAVE_GETPWUID_R 1

/* Enable the Linux getrandom function */
#define HAVE_GETRANDOM 1

/* Define to 1 if you have the `getrusage' function. */
#define HAVE_GETRUSAGE 1

/* Define to 1 if you have the `getservbyname' function. */
#define HAVE_GETSERVBYNAME 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* use __get_cpuid_count */
/* #undef HAVE_GET_CPUID_COUNT */

/* Define if you have the iconv() function and it works. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the `inet_ntop' function. */
/* #undef HAVE_INET_NTOP */

/* Define to 1 if you have the `inet_pton' function. */
/* #undef HAVE_INET_PTON */

/* Define to 1 if the compiler supports one of the keywords 'inline',
   '__inline__', '__inline' and effectively inlines functions marked as such.
   */
#define HAVE_INLINE 1

/* Define to 1 if the system has the type `int16_t'. */
#define HAVE_INT16_T 1

/* Define to 1 if the system has the type `int32_t'. */
#define HAVE_INT32_T 1

/* Define to 1 if the system has the type `int8_t'. */
#define HAVE_INT8_T 1

/* Define if you have the 'intmax_t' type in <stdint.h> or <inttypes.h>. */
#define HAVE_INTMAX_T 1

/* Define to 1 if the system has the type `intptr_t'. */
#define HAVE_INTPTR_T 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if <inttypes.h> exists, doesn't clash with <sys/types.h>, and
   declares uintmax_t. */
#define HAVE_INTTYPES_H_WITH_UINTMAX 1

/* Define to 1 if you have the `ioctl' function. */
#define HAVE_IOCTL 1

/* Define to 1 if <sys/socket.h> defines AF_INET. */
#define HAVE_IPV4 1

/* Define to 1 if <sys/socket.h> defines AF_INET6. */
#define HAVE_IPV6 1

/* Define to 1 if you have the `isblank' function. */
#define HAVE_ISBLANK 1

/* Define to 1 if you have the `issetugid' function. */
/* #undef HAVE_ISSETUGID */

/* Enable the BSD sysctl(KERN_ARND) function */
/* #undef HAVE_KERN_ARND */

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* Define to 1 if you have the <langinfo.h> header file. */
#define HAVE_LANGINFO_H 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define if you have the libcrypto library. */
#define HAVE_LIBCRYPTO 1

/* Define if you have the libdl library. */
#define HAVE_LIBDL 1

/* Define if you have the libev library. */
/* #undef HAVE_LIBEV */

/* Define to 1 if you have the `gen' library (-lgen). */
/* #undef HAVE_LIBGEN */

/* Define to 1 if you have the <libgen.h> header file. */
#define HAVE_LIBGEN_H 1

/* Define if IDNA 2008 support is enabled. */
#define HAVE_LIBIDN2 1

/* Define to 1 if you have the `intl' library (-lintl). */
/* #undef HAVE_LIBINTL */

/* Define to 1 if you have the <libintl.h> header file. */
#define HAVE_LIBINTL_H 1

/* nettle is enabled */
#define HAVE_LIBNETTLE 1

/* Define if you have the libpthread library. */
/* #undef HAVE_LIBPTHREAD */

/* Define if you have the librt library. */
#define HAVE_LIBRT 1

/* Define if you have the libseccomp library. */
/* #undef HAVE_LIBSECCOMP */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `localtime' function. */
#define HAVE_LOCALTIME 1

/* Define if localtime-like functions can loop forever on extreme arguments.
   */
/* #undef HAVE_LOCALTIME_INFLOOP_BUG */

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if the system has the type 'long long int'. */
#define HAVE_LONG_LONG_INT 1

/* Define to 1 if you have the `lstat' function. */
#define HAVE_LSTAT 1

/* Define if the 'malloc' function is POSIX compliant. */
#define HAVE_MALLOC_POSIX 1

/* Define to 1 if mmap()'s MAP_ANONYMOUS flag is available after including
   config.h and <sys/mman.h>. */
#define HAVE_MAP_ANONYMOUS 1

/* Define to 1 if you have the `mbrtowc' function. */
#define HAVE_MBRTOWC 1

/* Define to 1 if you have the `memmem' function. */
#define HAVE_MEMMEM 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset_s' function. */
/* #undef HAVE_MEMSET_S */

/* Define to 1 if <limits.h> defines the MIN and MAX macros. */
/* #undef HAVE_MINMAX_IN_LIMITS_H */

/* Define to 1 if <sys/param.h> defines the MIN and MAX macros. */
#define HAVE_MINMAX_IN_SYS_PARAM_H 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `mprotect' function. */
#define HAVE_MPROTECT 1

/* Define to 1 if you have the `mquery' function. */
/* #undef HAVE_MQUERY */

/* Define to 1 on MSVC platforms that have the "invalid parameter handler"
   concept. */
/* #undef HAVE_MSVC_INVALID_PARAMETER_HANDLER */

/* Define if the locale_t type does not contain the name of each locale
   category. */
/* #undef HAVE_NAMELESS_LOCALES */

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* Define to 1 if you have the `nettle_cfb8_encrypt' function. */
#define HAVE_NETTLE_CFB8_ENCRYPT 1

/* Define to 1 if you have the `nettle_chacha_set_counter' function. */
#define HAVE_NETTLE_CHACHA_SET_COUNTER 1

/* Define to 1 if you have the `nettle_cmac128_update' function. */
#define HAVE_NETTLE_CMAC128_UPDATE 1

/* Define to 1 if you have the `nettle_curve448_mul' function. */
#define HAVE_NETTLE_CURVE448_MUL 1

/* Define to 1 if you have the `nettle_ed448_shake256_sign' function. */
#define HAVE_NETTLE_ED448_SHAKE256_SIGN 1

/* Define to 1 if you have the `nettle_get_gost_gc256b' function. */
#define HAVE_NETTLE_GET_GOST_GC256B 1

/* Define to 1 if you have the `nettle_get_gost_gc512a' function. */
#define HAVE_NETTLE_GET_GOST_GC512A 1

/* Define to 1 if you have the `nettle_gost28147_set_key' function. */
/* #undef HAVE_NETTLE_GOST28147_SET_KEY */

/* Define to 1 if you have the `nettle_gostdsa_sign' function. */
#define HAVE_NETTLE_GOSTDSA_SIGN 1

/* Define to 1 if you have the `nettle_gosthash94cp_update' function. */
#define HAVE_NETTLE_GOSTHASH94CP_UPDATE 1

/* Define to 1 if you have the `nettle_rsa_sec_decrypt' function. */
#define HAVE_NETTLE_RSA_SEC_DECRYPT 1

/* Define to 1 if you have the `nettle_siv_cmac_aes128_set_key' function. */
#define HAVE_NETTLE_SIV_CMAC_AES128_SET_KEY 1

/* Define to 1 if you have the `nettle_streebog512_update' function. */
#define HAVE_NETTLE_STREEBOG512_UPDATE 1

/* Define to 1 if you have the `nettle_xts_encrypt_message' function. */
#define HAVE_NETTLE_XTS_ENCRYPT_MESSAGE 1

/* Define to 1 if you have the `newlocale' function. */
#define HAVE_NEWLOCALE 1

/* Define to 1 if you have the <OS.h> header file. */
/* #undef HAVE_OS_H */

/* Define this if pathfind(3) works */
/* #undef HAVE_PATHFIND */

/* Define to 1 if the system has the type `pid_t'. */
#define HAVE_PID_T 1

/* Define to 1 if you have the `pipe' function. */
#define HAVE_PIPE 1

/* Define to 1 if you have the `pstat_getprocvm' function. */
/* #undef HAVE_PSTAT_GETPROCVM */

/* Define if you have the <pthread.h> header and the POSIX threads API. */
#define HAVE_PTHREAD_API 1

/* Define to 1 if you have the `pthread_atfork' function. */
#define HAVE_PTHREAD_ATFORK 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if you have the `pthread_mutex_lock' function. */
#define HAVE_PTHREAD_MUTEX_LOCK 1

/* Define if the <pthread.h> defines PTHREAD_MUTEX_RECURSIVE. */
#define HAVE_PTHREAD_MUTEX_RECURSIVE 1

/* Define if the POSIX multithreading library has read/write locks. */
#define HAVE_PTHREAD_RWLOCK 1

/* Define if the 'pthread_rwlock_rdlock' function prefers a writer to a
   reader. */
/* #undef HAVE_PTHREAD_RWLOCK_RDLOCK_PREFER_WRITER */

/* Define to 1 if the pthread_sigmask function can be used (despite bugs). */
/* #undef HAVE_PTHREAD_SIGMASK */

/* Define to 1 if the system has the type `pthread_spinlock_t'. */
#define HAVE_PTHREAD_SPINLOCK_T 1

/* Define to 1 if the system has the type `pthread_t'. */
#define HAVE_PTHREAD_T 1

/* Define to 1 if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1

/* Define to 1 if you have the `raise' function. */
#define HAVE_RAISE 1

/* Define if the 'realloc' function is POSIX compliant. */
#define HAVE_REALLOC_POSIX 1

/* Define this if we have a functional realpath(3C) */
#define HAVE_REALPATH 1

/* Define to 1 if you have the <runetype.h> header file. */
/* #undef HAVE_RUNETYPE_H */

/* Define to 1 if you have run the test for working tzset. */
#define HAVE_RUN_TZSET_TEST 1

/* Define to 1 if the system has the type `sa_family_t'. */
#define HAVE_SA_FAMILY_T 1

/* Define to 1 if you have the <sched.h> header file. */
#define HAVE_SCHED_H 1

/* Define to 1 if you have the `scm_gc_malloc_pointerless' function. */
/* #undef HAVE_SCM_GC_MALLOC_POINTERLESS */

/* Define to 1 if you have the <search.h> header file. */
#define HAVE_SEARCH_H 1

/* Define to 1 if you have the `secure_getenv' function. */
#define HAVE_SECURE_GETENV 1

/* Define to 1 if you have the `setdtablesize' function. */
/* #undef HAVE_SETDTABLESIZE */

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setitimer' function. */
#define HAVE_SETITIMER 1

/* Define to 1 if you have the <setjmp.h> header file. */
#define HAVE_SETJMP_H 1

/* Define to 1 if you have the `shutdown' function. */
#define HAVE_SHUTDOWN 1

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the `sigaltstack' function. */
#define HAVE_SIGALTSTACK 1

/* Define to 1 if the system has the type `siginfo_t'. */
/* #undef HAVE_SIGINFO_T */

/* Define to 1 if you have the `siginterrupt' function. */
#define HAVE_SIGINTERRUPT 1

/* Define to 1 if 'sig_atomic_t' is a signed integer type. */
/* #undef HAVE_SIGNED_SIG_ATOMIC_T */

/* Define to 1 if 'wchar_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WCHAR_T */

/* Define to 1 if 'wint_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WINT_T */

/* Define to 1 if the system has the type `sigset_t'. */
#define HAVE_SIGSET_T 1

/* Define to 1 if the system has the type `size_t'. */
#define HAVE_SIZE_T 1

/* Define to 1 if you have the `sleep' function. */
#define HAVE_SLEEP 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define if the return value of the snprintf function is the number of of
   bytes (excluding the terminating NUL) that would have been produced if the
   buffer had been large enough. */
#define HAVE_SNPRINTF_RETVAL_C99 1

/* Define if the locale_t type is as on Solaris 11.4. */
/* #undef HAVE_SOLARIS114_LOCALES */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdatomic.h> header file. */
#define HAVE_STDATOMIC_H 1

/* Define to 1 if you have the <stdbool.h> header file. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if <stdint.h> exists, doesn't clash with <sys/types.h>, and declares
   uintmax_t. */
#define HAVE_STDINT_H_WITH_UINTMAX 1

/* Define to 1 if you have the <stdio_ext.h> header file. */
#define HAVE_STDIO_EXT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror_r' function. */
#define HAVE_STRERROR_R 1

/* Define this if strftime() works */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strsignal' function. */
#define HAVE_STRSIGNAL 1

/* Define to 1 if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define to 1 if the system has the type `struct addrinfo'. */
#define HAVE_STRUCT_ADDRINFO 1

/* Define to 1 if `iov_base' is a member of `struct iovec'. */
#define HAVE_STRUCT_IOVEC_IOV_BASE 1

/* Define to 1 if `sa_sigaction' is a member of `struct sigaction'. */
#define HAVE_STRUCT_SIGACTION_SA_SIGACTION 1

/* Define to 1 if `sa_len' is a member of `struct sockaddr'. */
/* #undef HAVE_STRUCT_SOCKADDR_SA_LEN */

/* Define to 1 if the system has the type `struct sockaddr_storage'. */
#define HAVE_STRUCT_SOCKADDR_STORAGE 1

/* Define to 1 if `ss_family' is a member of `struct sockaddr_storage'. */
#define HAVE_STRUCT_SOCKADDR_STORAGE_SS_FAMILY 1

/* Define to 1 if `st_atimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIMENSEC */

/* Define to 1 if `st_atimespec.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIMESPEC_TV_NSEC */

/* Define to 1 if `st_atim.st__tim.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_ATIM_ST__TIM_TV_NSEC */

/* Define to 1 if `st_atim.tv_nsec' is a member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC 1

/* Define to 1 if `st_birthtimensec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIMENSEC */

/* Define to 1 if `st_birthtimespec.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIMESPEC_TV_NSEC */

/* Define to 1 if `st_birthtim.tv_nsec' is a member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BIRTHTIM_TV_NSEC */

/* Define to 1 if `tm_zone' is a member of `struct tm'. */
#define HAVE_STRUCT_TM_TM_ZONE 1

/* Define to 1 if you have the `strverscmp' function. */
#define HAVE_STRVERSCMP 1

/* Define to 1 if you have the `symlink' function. */
#define HAVE_SYMLINK 1

/* Define to 1 if you have the <sysexits.h> header file. */
#define HAVE_SYSEXITS_H 1

/* Define to 1 if you have the <sys/bitypes.h> header file. */
/* #undef HAVE_SYS_BITYPES_H */

/* Define to 1 if you have the <sys/cdefs.h> header file. */
#define HAVE_SYS_CDEFS_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/inttypes.h> header file. */
/* #undef HAVE_SYS_INTTYPES_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/limits.h> header file. */
/* #undef HAVE_SYS_LIMITS_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/poll.h> header file. */
#define HAVE_SYS_POLL_H 1

/* Define to 1 if you have the <sys/procset.h> header file. */
/* #undef HAVE_SYS_PROCSET_H */

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/stropts.h> header file. */
/* #undef HAVE_SYS_STROPTS_H */

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if the system has the 'tcgetattr' function. */
/* #undef HAVE_TCGETATTR */

/* Define to 1 if the system has the 'tcsetattr' function. */
/* #undef HAVE_TCSETATTR */

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the `thrd_create' function. */
/* #undef HAVE_THRD_CREATE */

/* Define to 1 if you have the <threads.h> header file. */
#define HAVE_THREADS_H 1

/* Define to 1 if you have the `timegm' function. */
#define HAVE_TIMEGM 1

/* Define to 1 if the system has the type `timezone_t'. */
/* #undef HAVE_TIMEZONE_T */

/* Define if struct tm has the tm_gmtoff member. */
#define HAVE_TM_GMTOFF 1

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#define HAVE_TM_ZONE 1

/* Enable TPM */
/* #undef HAVE_TROUSERS */

/* Define to 1 if you have the `tsearch' function. */
#define HAVE_TSEARCH 1

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
/* #undef HAVE_TZNAME */

/* Define to 1 if you have the `tzset' function. */
#define HAVE_TZSET 1

/* Define to 1 if the system has the type `uint16_t'. */
#define HAVE_UINT16_T 1

/* Define to 1 if the system has the type `uint32_t'. */
#define HAVE_UINT32_T 1

/* Define to 1 if the system has the type `uint8_t'. */
#define HAVE_UINT8_T 1

/* Define to 1 if the system has the type `uintptr_t'. */
#define HAVE_UINTPTR_T 1

/* Define to 1 if the system has the type `uint_t'. */
/* #undef HAVE_UINT_T */

/* Define to 1 if the system has the type `union nettle_block8'. */
#define HAVE_UNION_NETTLE_BLOCK8 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Define to 1 if the system has the type 'unsigned long long int'. */
#define HAVE_UNSIGNED_LONG_LONG_INT 1

/* Define to 1 if you have the `uselocale' function. */
#define HAVE_USELOCALE 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if you have the <valgrind/memcheck.h> header file. */
#define HAVE_VALGRIND_MEMCHECK_H 1

/* Define to 1 if you have the <values.h> header file. */
/* #undef HAVE_VALUES_H */

/* Define to 1 if you have the <varargs.h> header file. */
/* #undef HAVE_VARARGS_H */

/* Define to 1 if you have the `vasnprintf' function. */
/* #undef HAVE_VASNPRINTF */

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 or 0, depending whether the compiler supports simple visibility
   declarations. */
/* #undef HAVE_VISIBILITY */

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define to 1 if the system has the type `wchar_t'. */
#define HAVE_WCHAR_T 1

/* Define to 1 if you have the `wcrtomb' function. */
#define HAVE_WCRTOMB 1

/* Define to 1 if you have the `wcslen' function. */
#define HAVE_WCSLEN 1

/* Define to 1 if you have the `wcsnlen' function. */
#define HAVE_WCSNLEN 1

/* Define to 1 if the compiler and linker support weak declarations of
   symbols. */
#define HAVE_WEAK_SYMBOLS 1

/* Define to 1 if you have the <winsock2.h> header file. */
/* #undef HAVE_WINSOCK2_H */

/* Define to 1 if the system has the type `wint_t'. */
#define HAVE_WINT_T 1

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if O_NOATIME works. */
#define HAVE_WORKING_O_NOATIME 1

/* Define to 1 if O_NOFOLLOW works. */
#define HAVE_WORKING_O_NOFOLLOW 1

/* Define if the uselocale function exists any may safely be called. */
#define HAVE_WORKING_USELOCALE 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to 1 if you have the <ws2tcpip.h> header file. */
/* #undef HAVE_WS2TCPIP_H */

/* Define to 1 if you have the <xlocale.h> header file. */
/* #undef HAVE_XLOCALE_H */

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Define to 1 if you have the `_fseeki64' function. */
/* #undef HAVE__FSEEKI64 */

/* Define to 1 if you have the `_ftelli64' function. */
/* #undef HAVE__FTELLI64 */

/* Define to 1 if you have the `_set_invalid_parameter_handler' function. */
/* #undef HAVE__SET_INVALID_PARAMETER_HANDLER */

/* Define to 1 if the compiler supports __builtin_expect,
   and to 2 if <builtins.h> does.  */
#define HAVE___BUILTIN_EXPECT 1
#ifndef HAVE___BUILTIN_EXPECT
# define __builtin_expect(e, c) (e)
#elif HAVE___BUILTIN_EXPECT == 2
# include <builtins.h>
#endif
    

/* Define to 1 if you have the `__fsetlocking' function. */
#define HAVE___FSETLOCKING 1

/* Define to 1 if the compiler supports the keyword '__inline'. */
#define HAVE___INLINE 1

/* Define to 1 if you have the `__register_atfork' function. */
#define HAVE___REGISTER_ATFORK 1

/* Define to 1 if you have the `__secure_getenv' function. */
/* #undef HAVE___SECURE_GETENV */

/* Define to 1 if you have the `__xpg_strerror_r' function. */
#define HAVE___XPG_STRERROR_R 1

/* The soname of hogweed library */
#define HOGWEED_LIBRARY_SONAME "libhogweed.so.6"

/* whether to allowin inline comments */
#define INI_ALLOW_INLINE_COMMENTS 1

/* The inline comment prefixes */
#define INI_INLINE_COMMENT_PREFIXES ";#"

/* inih maximum line size */
#define INI_MAX_LINE 2048

/* The comment prefixes */
#define INI_START_COMMENT_PREFIXES ";#"

/* whether to stop on first error */
#define INI_STOP_ON_FIRST_ERROR 1

/* Define to 1 if lseek does not detect pipes. */
/* #undef LSEEK_PIPE_BROKEN */

/* Define to 1 if 'lstat' dereferences a symlink specified with a trailing
   slash. */
#define LSTAT_FOLLOWS_SLASHED_SYMLINK 1

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* If malloc(0) is != NULL, define this to 1. Otherwise define this to 0. */
#define MALLOC_0_IS_NONNULL 1

/* Define to a substitute value for mmap()'s MAP_ANONYMOUS flag. */
/* #undef MAP_ANONYMOUS */

/* Use GNU style printf and scanf.  */
#ifndef __USE_MINGW_ANSI_STDIO
# define __USE_MINGW_ANSI_STDIO 1
#endif


/* Use backported Curve448/GOST R 34.10 DSA support */
/* #undef NEED_INT_ECC */

/* Define if the compilation of mktime.c should define 'mktime_internal'. */
#define NEED_MKTIME_INTERNAL 1

/* Define if the compilation of mktime.c should define 'mktime' with the
   native Windows TZ workaround. */
/* #undef NEED_MKTIME_WINDOWS */

/* Define if the compilation of mktime.c should define 'mktime' with the
   algorithmic workarounds. */
/* #undef NEED_MKTIME_WORKING */

/* Define to 1 to enable general improvements of setlocale. */
#define NEED_SETLOCALE_IMPROVED 0

/* Define to 1 to enable a multithread-safety fix of setlocale. */
#define NEED_SETLOCALE_MTSAFE 0

/* The soname of nettle library */
#define NETTLE_LIBRARY_SONAME "libnettle.so.8"

/* Define this if optional arguments are disallowed */
/* #undef NO_OPTIONAL_OPT_ARGS */

/* Define to 1 if open() fails to recognize a trailing slash. */
/* #undef OPEN_TRAILING_SLASH_BUG */

/* Name of package */
#define PACKAGE "gnutls"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "bugs@gnutls.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GnuTLS"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GnuTLS 3.6.16"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gnutls"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.6.16"

/* define to a working POSIX compliant shell */
#define POSIX_SHELL "/usr/bin/bash"

/* Define if <inttypes.h> exists and defines unusable PRI* macros. */
/* #undef PRI_MACROS_BROKEN */

/* Define to the type that is the result of default argument promotions of
   type mode_t. */
#define PROMOTED_MODE_T mode_t

/* Define if pthread_create is an inline function. */
/* #undef PTHREAD_CREATE_IS_INLINE */

/* Define if the pthread_in_use() detection is hard. */
/* #undef PTHREAD_IN_USE_DETECTION_HARD */

/* Define to 1 if pthread_sigmask(), when it fails, returns -1 and sets errno.
   */
/* #undef PTHREAD_SIGMASK_FAILS_WITH_ERRNO */

/* Define to 1 if pthread_sigmask may return 0 and have no effect. */
/* #undef PTHREAD_SIGMASK_INEFFECTIVE */

/* Define to 1 if pthread_sigmask() unblocks signals incorrectly. */
/* #undef PTHREAD_SIGMASK_UNBLOCK_BUG */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'ptrdiff_t'. */
/* #undef PTRDIFF_T_SUFFIX */

/* name of regex header file */
#define REGEX_HEADER <regex.h>

/* Define to 1 if stat needs help when passed a file name with a trailing
   slash */
/* #undef REPLACE_FUNC_STAT_FILE */

/* Define to 1 if strerror(0) does not return a message implying success. */
/* #undef REPLACE_STRERROR_0 */

/* Define if vasnprintf exists but is overridden by gnulib. */
/* #undef REPLACE_VASNPRINTF */

/* Define to 1 if setlocale (LC_ALL, NULL) is multithread-safe. */
#define SETLOCALE_NULL_ALL_MTSAFE 1

/* Define to 1 if setlocale (category, NULL) is multithread-safe. */
#define SETLOCALE_NULL_ONE_MTSAFE 1

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'sig_atomic_t'. */
/* #undef SIG_ATOMIC_T_SUFFIX */

/* The size of `char *', as computed by sizeof. */
#define SIZEOF_CHAR_P 4

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of `time_t', as computed by sizeof. */
#define SIZEOF_TIME_T 4

/* The size of `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT 4

/* The size of `unsigned long int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG_INT 4

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 4

/* Define as the maximum value of type 'size_t', if the system doesn't define
   it. */
#ifndef SIZE_MAX
/* # undef SIZE_MAX */
#endif

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'size_t'. */
/* #undef SIZE_T_SUFFIX */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* force strict DER time constraints */
#define STRICT_DER_TIME 1

/* The system-wide gnutls configuration file */
#define SYSTEM_PRIORITY_FILE "/etc/gnutls/config"

/* Define to 1 if time_t is signed. */
#define TIME_T_IS_SIGNED 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* the location of the trousers library */
#define TROUSERS_LIB ""

/* Define to 1 if the type of the st_atim member of a struct stat is struct
   timespec. */
#define TYPEOF_STRUCT_STAT_ST_ATIM_IS_STRUCT_TIMESPEC 1

/* Define if tzset clobbers localtime's static buffer. */
/* #undef TZSET_CLOBBERS_LOCALTIME */

/* The DNSSEC root key file */
#define UNBOUND_ROOT_KEY_FILE "/etc/unbound/root.key"

/* Define if the combination of the ISO C and POSIX multithreading APIs can be
   used. */
/* #undef USE_ISOC_AND_POSIX_THREADS */

/* Define if the ISO C multithreading library can be used. */
/* #undef USE_ISOC_THREADS */

/* Define if the POSIX multithreading library can be used. */
#define USE_POSIX_THREADS 1

/* Define if references to the POSIX multithreading library should be made
   weak. */
#define USE_POSIX_THREADS_WEAK 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable general extensions on macOS.  */
#ifndef _DARWIN_C_SOURCE
# define _DARWIN_C_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable NetBSD extensions on NetBSD.  */
#ifndef _NETBSD_SOURCE
# define _NETBSD_SOURCE 1
#endif
/* Enable OpenBSD extensions on NetBSD.  */
#ifndef _OPENBSD_SOURCE
# define _OPENBSD_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-5:2014.  */
#ifndef __STDC_WANT_IEC_60559_ATTRIBS_EXT__
# define __STDC_WANT_IEC_60559_ATTRIBS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-1:2014.  */
#ifndef __STDC_WANT_IEC_60559_BFP_EXT__
# define __STDC_WANT_IEC_60559_BFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-2:2015.  */
#ifndef __STDC_WANT_IEC_60559_DFP_EXT__
# define __STDC_WANT_IEC_60559_DFP_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-4:2015.  */
#ifndef __STDC_WANT_IEC_60559_FUNCS_EXT__
# define __STDC_WANT_IEC_60559_FUNCS_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TS 18661-3:2015.  */
#ifndef __STDC_WANT_IEC_60559_TYPES_EXT__
# define __STDC_WANT_IEC_60559_TYPES_EXT__ 1
#endif
/* Enable extensions specified by ISO/IEC TR 24731-2:2010.  */
#ifndef __STDC_WANT_LIB_EXT2__
# define __STDC_WANT_LIB_EXT2__ 1
#endif
/* Enable extensions specified by ISO/IEC 24747:2009.  */
#ifndef __STDC_WANT_MATH_SPEC_FUNCS__
# define __STDC_WANT_MATH_SPEC_FUNCS__ 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable X/Open extensions if necessary.  HP-UX 11.11 defines
   mbstate_t only if _XOPEN_SOURCE is defined to 500, regardless of
   whether compiling with -Ae or -D_HPUX_SOURCE=1.  */
#ifndef _XOPEN_SOURCE
/* # undef _XOPEN_SOURCE */
#endif
/* Enable X/Open compliant socket functions that do not require linking
   with -lxnet on HP-UX 11.11.  */
#ifndef _HPUX_ALT_XOPEN_SOCKET_API
# define _HPUX_ALT_XOPEN_SOCKET_API 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define if the native Windows multithreading API can be used. */
/* #undef USE_WINDOWS_THREADS */

/* Version number of package */
#define VERSION "3.6.16"

/* Define to 1 if unsetenv returns void instead of int. */
/* #undef VOID_UNSETENV */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wchar_t'. */
/* #undef WCHAR_T_SUFFIX */

/* Define if WSAStartup is needed. */
/* #undef WINDOWS_SOCKETS */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wint_t'. */
/* #undef WINT_T_SUFFIX */

/* Define this if a working libregex can be found */
#define WITH_LIBREGEX 1

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#define _FILE_OFFSET_BITS 64

/* True if the compiler says it groks GNU C version MAJOR.MINOR.  */
#if defined __GNUC__ && defined __GNUC_MINOR__
# define _GL_GNUC_PREREQ(major, minor) \
    ((major) < __GNUC__ + ((minor) <= __GNUC_MINOR__))
#else
# define _GL_GNUC_PREREQ(major, minor) 0
#endif


/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 on Solaris. */
/* #undef _LCONV_C99 */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 1 to make NetBSD features available. MINIX 3 needs this. */
#define _NETBSD_SOURCE 1

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)) \
      && 0)
    /* [[noreturn]] is not practically usable, because with it the syntax
         extern _Noreturn void func (...);
       would not be valid; such a declaration would only be valid with 'extern'
       and '_Noreturn' swapped, or without the 'extern' keyword.  However, some
       AIX system header files and several gnulib header files use precisely
       this syntax with 'extern'.  */
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0)  \
            || _GL_GNUC_PREREQ (4, 7) \
            || (defined __apple_build_version__ \
                ? 6000000 <= __apple_build_version__ \
                : 3 < __clang_major__ + (5 <= __clang_minor__))))
   /* _Noreturn works as-is.  */
# elif _GL_GNUC_PREREQ (2, 8) || 0x5110 <= __SUNPRO_C
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif


/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 in order to get the POSIX compatible declarations of socket
   functions. */
/* #undef _POSIX_PII_SOCKET */

/* Define to 1 if you need to in order for 'stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Defined to 1 for Unicode (wide chars) APIs */
/* #undef _UNICODE */

/* For standard stat data types on VMS. */
#define _USE_STD_STAT 1

/* Define to 1 if the system <stdint.h> predates C++11. */
/* #undef __STDC_CONSTANT_MACROS */

/* Define to 1 if the system <stdint.h> predates C++11. */
/* #undef __STDC_LIMIT_MACROS */

/* Define as a replacement for the ISO C99 __func__ variable. */
/* #undef __func__ */

/* The _GL_ASYNC_SAFE marker should be attached to functions that are
   signal handlers (for signals other than SIGABRT, SIGPIPE) or can be
   invoked from such signal handlers.  Such functions have some restrictions:
     * All functions that it calls should be marked _GL_ASYNC_SAFE as well,
       or should be listed as async-signal-safe in POSIX
       <https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_04>
       section 2.4.3.  Note that malloc(), sprintf(), and fwrite(), in
       particular, are NOT async-signal-safe.
     * All memory locations (variables and struct fields) that these functions
       access must be marked 'volatile'.  This holds for both read and write
       accesses.  Otherwise the compiler might optimize away stores to and
       reads from such locations that occur in the program, depending on its
       data flow analysis.  For example, when the program contains a loop
       that is intended to inspect a variable set from within a signal handler
           while (!signal_occurred)
             ;
       the compiler is allowed to transform this into an endless loop if the
       variable 'signal_occurred' is not declared 'volatile'.
   Additionally, recall that:
     * A signal handler should not modify errno (except if it is a handler
       for a fatal signal and ends by raising the same signal again, thus
       provoking the termination of the process).  If it invokes a function
       that may clobber errno, it needs to save and restore the value of
       errno.  */
#define _GL_ASYNC_SAFE


/* Attributes.  */
#ifdef __has_attribute
# define _GL_HAS_ATTRIBUTE(attr) __has_attribute (__##attr##__)
#else
# define _GL_HAS_ATTRIBUTE(attr) _GL_ATTR_##attr
# define _GL_ATTR_alloc_size _GL_GNUC_PREREQ (4, 3)
# define _GL_ATTR_always_inline _GL_GNUC_PREREQ (3, 2)
# define _GL_ATTR_artificial _GL_GNUC_PREREQ (4, 3)
# define _GL_ATTR_cold _GL_GNUC_PREREQ (4, 3)
# define _GL_ATTR_const _GL_GNUC_PREREQ (2, 95)
# define _GL_ATTR_deprecated _GL_GNUC_PREREQ (3, 1)
# define _GL_ATTR_error _GL_GNUC_PREREQ (4, 3)
# define _GL_ATTR_externally_visible _GL_GNUC_PREREQ (4, 1)
# define _GL_ATTR_fallthrough _GL_GNUC_PREREQ (7, 0)
# define _GL_ATTR_format _GL_GNUC_PREREQ (2, 7)
# define _GL_ATTR_leaf _GL_GNUC_PREREQ (4, 6)
# ifdef _ICC
#  define _GL_ATTR_may_alias 0
# else
#  define _GL_ATTR_may_alias _GL_GNUC_PREREQ (3, 3)
# endif
# define _GL_ATTR_malloc _GL_GNUC_PREREQ (3, 0)
# define _GL_ATTR_noinline _GL_GNUC_PREREQ (3, 1)
# define _GL_ATTR_nonnull _GL_GNUC_PREREQ (3, 3)
# define _GL_ATTR_nonstring _GL_GNUC_PREREQ (8, 0)
# define _GL_ATTR_nothrow _GL_GNUC_PREREQ (3, 3)
# define _GL_ATTR_packed _GL_GNUC_PREREQ (2, 7)
# define _GL_ATTR_pure _GL_GNUC_PREREQ (2, 96)
# define _GL_ATTR_returns_nonnull _GL_GNUC_PREREQ (4, 9)
# define _GL_ATTR_sentinel _GL_GNUC_PREREQ (4, 0)
# define _GL_ATTR_unused _GL_GNUC_PREREQ (2, 7)
# define _GL_ATTR_warn_unused_result _GL_GNUC_PREREQ (3, 4)
#endif


#if _GL_HAS_ATTRIBUTE (alloc_size)
# define _GL_ATTRIBUTE_ALLOC_SIZE(args) __attribute__ ((__alloc_size__ args))
#else
# define _GL_ATTRIBUTE_ALLOC_SIZE(args)
#endif

#if _GL_HAS_ATTRIBUTE (always_inline)
# define _GL_ATTRIBUTE_ALWAYS_INLINE __attribute__ ((__always_inline__))
#else
# define _GL_ATTRIBUTE_ALWAYS_INLINE
#endif

#if _GL_HAS_ATTRIBUTE (artificial)
# define _GL_ATTRIBUTE_ARTIFICIAL __attribute__ ((__artificial__))
#else
# define _GL_ATTRIBUTE_ARTIFICIAL
#endif

/* Avoid __attribute__ ((cold)) on MinGW; see thread starting at
   <https://lists.gnu.org/r/emacs-devel/2019-04/msg01152.html>. */
#if _GL_HAS_ATTRIBUTE (cold) && !defined __MINGW32__
# define _GL_ATTRIBUTE_COLD __attribute__ ((__cold__))
#else
# define _GL_ATTRIBUTE_COLD
#endif

#if _GL_HAS_ATTRIBUTE (const)
# define _GL_ATTRIBUTE_CONST __attribute__ ((__const__))
#else
# define _GL_ATTRIBUTE_CONST
#endif

#if 201710L < __STDC_VERSION__
# define _GL_ATTRIBUTE_DEPRECATED [[__deprecated__]]
#elif _GL_HAS_ATTRIBUTE (deprecated)
# define _GL_ATTRIBUTE_DEPRECATED __attribute__ ((__deprecated__))
#else
# define _GL_ATTRIBUTE_DEPRECATED
#endif

#if _GL_HAS_ATTRIBUTE (error)
# define _GL_ATTRIBUTE_ERROR(msg) __attribute__ ((__error__ (msg)))
# define _GL_ATTRIBUTE_WARNING(msg) __attribute__ ((__warning__ (msg)))
#else
# define _GL_ATTRIBUTE_ERROR(msg)
# define _GL_ATTRIBUTE_WARNING(msg)
#endif

#if _GL_HAS_ATTRIBUTE (externally_visible)
# define _GL_ATTRIBUTE_EXTERNALLY_VISIBLE __attribute__ ((externally_visible))
#else
# define _GL_ATTRIBUTE_EXTERNALLY_VISIBLE
#endif

/* FALLTHROUGH is special, because it always expands to something.  */
#if 201710L < __STDC_VERSION__
# define _GL_ATTRIBUTE_FALLTHROUGH [[__fallthrough__]]
#elif _GL_HAS_ATTRIBUTE (fallthrough)
# define _GL_ATTRIBUTE_FALLTHROUGH __attribute__ ((__fallthrough__))
#else
# define _GL_ATTRIBUTE_FALLTHROUGH ((void) 0)
#endif

#if _GL_HAS_ATTRIBUTE (format)
# define _GL_ATTRIBUTE_FORMAT(spec) __attribute__ ((__format__ spec))
#else
# define _GL_ATTRIBUTE_FORMAT(spec)
#endif

#if _GL_HAS_ATTRIBUTE (leaf)
# define _GL_ATTRIBUTE_LEAF __attribute__ ((__leaf__))
#else
# define _GL_ATTRIBUTE_LEAF
#endif

#if _GL_HAS_ATTRIBUTE (may_alias)
# define _GL_ATTRIBUTE_MAY_ALIAS __attribute__ ((__may_alias__))
#else
# define _GL_ATTRIBUTE_MAY_ALIAS
#endif

#if 201710L < __STDC_VERSION__
# define _GL_ATTRIBUTE_MAYBE_UNUSED [[__maybe_unused__]]
#elif _GL_HAS_ATTRIBUTE (unused)
# define _GL_ATTRIBUTE_MAYBE_UNUSED __attribute__ ((__unused__))
#else
# define _GL_ATTRIBUTE_MAYBE_UNUSED
#endif
/* Earlier spellings of this macro.  */
#define _GL_UNUSED _GL_ATTRIBUTE_MAYBE_UNUSED
#define _UNUSED_PARAMETER_ _GL_ATTRIBUTE_MAYBE_UNUSED

#if _GL_HAS_ATTRIBUTE (malloc)
# define _GL_ATTRIBUTE_MALLOC __attribute__ ((__malloc__))
#else
# define _GL_ATTRIBUTE_MALLOC
#endif

#if 201710L < __STDC_VERSION__
# define _GL_ATTRIBUTE_NODISCARD [[__nodiscard__]]
#elif _GL_HAS_ATTRIBUTE (warn_unused_result)
# define _GL_ATTRIBUTE_NODISCARD __attribute__ ((__warn_unused_result__))
#else
# define _GL_ATTRIBUTE_NODISCARD
#endif

#if _GL_HAS_ATTRIBUTE (noinline)
# define _GL_ATTRIBUTE_NOINLINE __attribute__ ((__noinline__))
#else
# define _GL_ATTRIBUTE_NOINLINE
#endif

#if _GL_HAS_ATTRIBUTE (nonnull)
# define _GL_ATTRIBUTE_NONNULL(args) __attribute__ ((__nonnull__ args))
#else
# define _GL_ATTRIBUTE_NONNULL(args)
#endif

#if _GL_HAS_ATTRIBUTE (nonstring)
# define _GL_ATTRIBUTE_NONSTRING __attribute__ ((__nonstring__))
#else
# define _GL_ATTRIBUTE_NONSTRING
#endif

/* There is no _GL_ATTRIBUTE_NORETURN; use _Noreturn instead.  */

#if _GL_HAS_ATTRIBUTE (nothrow) && !defined __cplusplus
# define _GL_ATTRIBUTE_NOTHROW __attribute__ ((__nothrow__))
#else
# define _GL_ATTRIBUTE_NOTHROW
#endif

#if _GL_HAS_ATTRIBUTE (packed)
# define _GL_ATTRIBUTE_PACKED __attribute__ ((__packed__))
#else
# define _GL_ATTRIBUTE_PACKED
#endif

#if _GL_HAS_ATTRIBUTE (pure)
# define _GL_ATTRIBUTE_PURE __attribute__ ((__pure__))
#else
# define _GL_ATTRIBUTE_PURE
#endif

#if _GL_HAS_ATTRIBUTE (returns_nonnull)
# define _GL_ATTRIBUTE_RETURNS_NONNULL __attribute__ ((__returns_nonnull__))
#else
# define _GL_ATTRIBUTE_RETURNS_NONNULL
#endif

#if _GL_HAS_ATTRIBUTE (sentinel)
# define _GL_ATTRIBUTE_SENTINEL(pos) __attribute__ ((__sentinel__ pos))
#else
# define _GL_ATTRIBUTE_SENTINEL(pos)
#endif


/* To support C++ as well as C, use _GL_UNUSED_LABEL with trailing ';'.  */
#if !defined __cplusplus || _GL_GNUC_PREREQ (4, 5)
# define _GL_UNUSED_LABEL _GL_ATTRIBUTE_MAYBE_UNUSED
#else
# define _GL_UNUSED_LABEL
#endif


/* Please see the Gnulib manual for how to use these macros.

   Suppress extern inline with HP-UX cc, as it appears to be broken; see
   <https://lists.gnu.org/r/bug-texinfo/2013-02/msg00030.html>.

   Suppress extern inline with Sun C in standards-conformance mode, as it
   mishandles inline functions that call each other.  E.g., for 'inline void f
   (void) { } inline void g (void) { f (); }', c99 incorrectly complains
   'reference to static identifier "f" in extern inline function'.
   This bug was observed with Sun C 5.12 SunOS_i386 2011/11/16.

   Suppress extern inline (with or without __attribute__ ((__gnu_inline__)))
   on configurations that mistakenly use 'static inline' to implement
   functions or macros in standard C headers like <ctype.h>.  For example,
   if isdigit is mistakenly implemented via a static inline function,
   a program containing an extern inline function that calls isdigit
   may not work since the C standard prohibits extern inline functions
   from calling static functions (ISO C 99 section 6.7.4.(3).
   This bug is known to occur on:

     OS X 10.8 and earlier; see:
     https://lists.gnu.org/r/bug-gnulib/2012-12/msg00023.html

     DragonFly; see
     http://muscles.dragonflybsd.org/bulk/clang-master-potential/20141111_102002/logs/ah-tty-0.3.12.log

     FreeBSD; see:
     https://lists.gnu.org/r/bug-gnulib/2014-07/msg00104.html

   OS X 10.9 has a macro __header_inline indicating the bug is fixed for C and
   for clang but remains for g++; see <https://trac.macports.org/ticket/41033>.
   Assume DragonFly and FreeBSD will be similar.

   GCC 4.3 and above with -std=c99 or -std=gnu99 implements ISO C99
   inline semantics, unless -fgnu89-inline is used.  It defines a macro
   __GNUC_STDC_INLINE__ to indicate this situation or a macro
   __GNUC_GNU_INLINE__ to indicate the opposite situation.
   GCC 4.2 with -std=c99 or -std=gnu99 implements the GNU C inline
   semantics but warns, unless -fgnu89-inline is used:
     warning: C99 inline functions are not supported; using GNU89
     warning: to disable this warning use -fgnu89-inline or the gnu_inline function attribute
   It defines a macro __GNUC_GNU_INLINE__ to indicate this situation.
 */
#if (((defined __APPLE__ && defined __MACH__) \
      || defined __DragonFly__ || defined __FreeBSD__) \
     && (defined __header_inline \
         ? (defined __cplusplus && defined __GNUC_STDC_INLINE__ \
            && ! defined __clang__) \
         : ((! defined _DONT_USE_CTYPE_INLINE_ \
             && (defined __GNUC__ || defined __cplusplus)) \
            || (defined _FORTIFY_SOURCE && 0 < _FORTIFY_SOURCE \
                && defined __GNUC__ && ! defined __cplusplus))))
# define _GL_EXTERN_INLINE_STDHEADER_BUG
#endif
#if ((__GNUC__ \
      ? defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__ \
      : (199901L <= __STDC_VERSION__ \
         && !defined __HP_cc \
         && !defined __PGI \
         && !(defined __SUNPRO_C && __STDC__))) \
     && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# define _GL_INLINE inline
# define _GL_EXTERN_INLINE extern inline
# define _GL_EXTERN_INLINE_IN_USE
#elif (2 < __GNUC__ + (7 <= __GNUC_MINOR__) && !defined __STRICT_ANSI__ \
       && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# if defined __GNUC_GNU_INLINE__ && __GNUC_GNU_INLINE__
   /* __gnu_inline__ suppresses a GCC 4.2 diagnostic.  */
#  define _GL_INLINE extern inline __attribute__ ((__gnu_inline__))
# else
#  define _GL_INLINE extern inline
# endif
# define _GL_EXTERN_INLINE extern
# define _GL_EXTERN_INLINE_IN_USE
#else
# define _GL_INLINE static _GL_UNUSED
# define _GL_EXTERN_INLINE static _GL_UNUSED
#endif

/* In GCC 4.6 (inclusive) to 5.1 (exclusive),
   suppress bogus "no previous prototype for 'FOO'"
   and "no previous declaration for 'FOO'" diagnostics,
   when FOO is an inline function in the header; see
   <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=54113> and
   <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63877>.  */
#if __GNUC__ == 4 && 6 <= __GNUC_MINOR__
# if defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__
#  define _GL_INLINE_HEADER_CONST_PRAGMA
# else
#  define _GL_INLINE_HEADER_CONST_PRAGMA \
     _Pragma ("GCC diagnostic ignored \"-Wsuggest-attribute=const\"")
# endif
# define _GL_INLINE_HEADER_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-prototypes\"") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-declarations\"") \
    _GL_INLINE_HEADER_CONST_PRAGMA
# define _GL_INLINE_HEADER_END \
    _Pragma ("GCC diagnostic pop")
#else
# define _GL_INLINE_HEADER_BEGIN
# define _GL_INLINE_HEADER_END
#endif

/* static lib rename */
#define fread_file _gnutls_fread_file

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to long or long long if <stdint.h> and <inttypes.h> don't define. */
/* #undef intmax_t */

/* Work around a bug in Apple GCC 4.0.1 build 5465: In C99 mode, it supports
   the ISO C 99 semantics of 'extern inline' (unlike the GNU C semantics of
   earlier versions), but does not display it by setting __GNUC_STDC_INLINE__.
   __APPLE__ && __MACH__ test for Mac OS X.
   __APPLE_CC__ tests for the Apple compiler and its version.
   __STDC_VERSION__ tests for the C99 mode.  */
#if defined __APPLE__ && defined __MACH__ && __APPLE_CC__ >= 5465 && !defined __cplusplus && __STDC_VERSION__ >= 199901L && !defined __GNUC_STDC_INLINE__
# define __GNUC_STDC_INLINE__ 1
#endif

/* Define to the real name of the mktime_internal function. */
/* #undef mktime_internal */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to the name of the strftime replacement function. */
#define my_strftime nstrftime

/* Define to the type of st_nlink in struct stat, or a supertype. */
/* #undef nlink_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define as the type of the result of subtracting two pointers, if the system
   doesn't define it. */
/* #undef ptrdiff_t */

/* static lib rename */
#define read_file _gnutls_read_file

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in older versions of Sun C++, which did not
   #define __restrict__ or support _Restrict or __restrict__
   even though the corresponding Sun C compiler ended up with
   "#define restrict _Restrict" or "#define restrict __restrict__"
   in the previous line.  This workaround can be removed once
   we assume Oracle Developer Studio 12.5 (2016) or later.  */
#if defined __SUNPRO_CC && !defined __RESTRICT && !defined __restrict__
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* type to use in place of socklen_t if not defined */
/* #undef socklen_t */

/* Define as a signed type of the same size as size_t. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */
