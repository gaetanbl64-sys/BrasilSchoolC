# Compilers
CROSS_CXX = sparc-elf-g++
HOST_CXX  = g++
CXXFLAGS  = -O2 -Wall

# Files
SRCS      = calendar_PC_LEON333.cpp
BITSTREAM = leon3mp.bit

# Output Binary Names
TARGET_LEON = calendar_leon3
TARGET_PC   = calendar_pc.exe

# Digilent Adept Tool Path
DJTGCFG = "C:/Program Files (x86)/Digilent/AdeptUtilities/djtgcfg.exe"

.PHONY: all leon pc flash clean

# Default rule: builds both LEON3 and PC binaries
all: leon pc

# Compile for LEON3 (SPARC architecture)
leon: $(SRCS)
	$(CROSS_CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET_LEON)

# Compile for local PC testing
pc: $(SRCS)
	$(HOST_CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET_PC)

# Flash the FPGA board with the bitstream
flash:
	$(DJTGCFG) prog -d Atlys -i 0 -f $(BITSTREAM)

# Clean up built binaries
clean:
	rm -f $(TARGET_LEON) $(TARGET_PC) *.o