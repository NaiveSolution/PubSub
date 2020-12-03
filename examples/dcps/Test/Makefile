LDFLAGS= -L"/home/tariq/tariq/opensplice/install/HDE/x86_64.linux/lib"
LIB_LANG=isocpp2

LDLIBS= -l"dcps${LIB_LANG}$(LIBSUFFIX)" -l"ddskernel" -ldl $(subst lib,-l,$(sort $(basename $(notdir $(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread

all:
	g++ -std=c++17 -Wall -g -o sub TempControl.cpp TempControlSplDcps.cpp sub.cpp \
	-I "/home/tariq/tariq/opensplice/install/HDE/x86_64.linux/include/sys/" \
	-I "/home/tariq/tariq/opensplice/install/HDE/x86_64.linux/include/dcps/C++/isocpp2/" \
	-I "/home/tariq/tariq/opensplice/install/HDE/x86_64.linux/include/dcps/C++/SACPP/" ${LDFLAGS} ${LDLIBS} 
