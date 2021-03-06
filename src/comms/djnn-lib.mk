lib_djnn_deps = core


# Ivy dependancy
# 1 - download ivy-c on with : svn co https://svn.tls.cena.fr/svn/ivy/ivy-c/trunk
# 2 - cd ivy-c/trunc/src
# 3 - make -f Makefile.osx
# 4 - sudo make -f Makefile.osx install

ifeq ($(os),Darwin)
lib_cppflags = -I/opt/local/include/
lib_ldflags = -L/opt/local/lib -livy
#lib_ldflags = -L/usr/local/lib64 -livy -lpcre
endif
ifeq ($(os),Linux)
#lib_cppflags = -I/opt/local/include/
#lib_ldflags = -L/opt/local/lib -livy
endif

lib_srcs := $(shell find src/comms -name "*.cpp")