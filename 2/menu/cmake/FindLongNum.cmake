set(FIND_LONGNUM_PATHS
        /Users/danilishinyar/OOP/Lib/LongNum)

find_path(LONGNUM_INCLUDE_DIR LongNum.h
        PATH_SUFFIXES include
        PATHS ${FIND_LONGNUM_PATHS})

find_library(LONGNUM_LIBRARY
        NAMES LongNum
        PATH_SUFFIXES lib
        PATHS ${FIND_LONGNUM_PATHS})