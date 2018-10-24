SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST: -$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc


#This wil configure the file locations for the kernel after compilation
# all of these will exist under the "sysroot" directory
#TODO: decide on a structure for the kernel files
export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

# Configure cross-compiler to use the sys root
# that we create on compile time
# This sysroot will contain folders defined above
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- '-elf($|-)' ; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
