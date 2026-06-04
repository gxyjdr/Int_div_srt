#=============================================================================
# sim/Makefile — Verilator Simulation for SRT-4 Divider
#=============================================================================

TOP     = div_srt4_top
RTL_DIR = ../rtl
RTL     = $(RTL_DIR)/div_srt4_pkg.sv \
          $(RTL_DIR)/div_srt4_qds.sv \
          $(RTL_DIR)/div_srt4_datapath.sv \
          $(RTL_DIR)/div_srt4_top.sv

OBJ_DIR = obj_dir
CFLAGS  = -O2

.PHONY: all clean run wave100

all: $(OBJ_DIR)/V$(TOP)

$(OBJ_DIR)/V$(TOP): $(RTL) sim_main.cpp
	verilator --cc --build -j \
		-Wall -Wno-UNUSED \
		-sv --trace \
		-CFLAGS "$(CFLAGS)" \
		--Mdir $(OBJ_DIR) \
		--top-module $(TOP) \
		--exe sim_main.cpp \
		$(RTL)

run: $(OBJ_DIR)/V$(TOP)
	./$(OBJ_DIR)/V$(TOP)

wave100: $(OBJ_DIR)/V$(TOP)
	./$(OBJ_DIR)/V$(TOP) wave100

clean:
	rm -rf $(OBJ_DIR)