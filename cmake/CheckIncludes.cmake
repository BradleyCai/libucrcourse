include(CheckIncludeFiles)
include(CheckFunctionExists)

macro(CHECK_INCLUDE_VAR VARIABLE MSG)
    if(NOT ${VARIABLE})
        message(FATAL_ERROR ${MSG})
    endif()
endmacro()

check_include_files("errno.h;stdarg.h;stddef.h;stdint.h;stdio.h;stdlib.h;string.h;time.h" HAVE_STDLIB)
check_include_files("locale.h;signal.h;unistd.h;sys/stat.h;sys/types.h" HAVE_POSIX)
check_include_files("curl/curl.h" HAVE_CURL)

check_include_var(HAVE_STDLIB "Missing C standard library headers")
check_include_var(HAVE_POSIX "Missing POSIX headers")
check_include_var(HAVE_CURL "Missing cURL headers")

