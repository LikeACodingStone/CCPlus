include GLOBAL.mak

DIR_INC = /home/listen/CodePRJ/R_16_ALL/code/tina/out/astar-parrot/compile_dir/target/alsa-lib-1.1.0 
CUR_INC += ${OUT_PATH}/include
DIR_SRC =  ./src
DIR_OBJ = $(OUT_PATH)/obj
DIR_BIN = $(OUT_PATH)/bin
DIR_LIB = $(OUT_PATH)/lib

FLAGS=-O3 -I$(DIR_INC) -I${CUR_INC} -L/home/listen/CodePRJ/R_16_ALL/code/tina/out/astar-parrot/compile_dir/target/alsa-lib-1.1.0/src/.libs -lasound -L${DIR_LIB} -lvoice -L${DIR_LIB}  -L${DIR_LIB} -lwakeup -lmad -lm -L${DIR_LIB} -lspeex_r16

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = main
BIN_TARGET = $(DIR_BIN)/$(TARGET)

.PHONY:all
all:testdir release

.PHONY:release
release:$(BIN_TARGET)

.PHONY:debug
debug:$(BIN_TARGET)

${BIN_TARGET}:${OBJ}
	$(CC) $(FLAGS) $(OBJ) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.c 
	$(CC) $(FLAGS) -c $< -o $@

testdir:
	@test -d $(DIR_OBJ) || mkdir -p $(DIR_OBJ)
	@test -d $(DIR_BIN) || mkdir -p $(DIR_BIN)

clean:
	rm -rf $(DIR_OBJ) $(DIR_BIN)
