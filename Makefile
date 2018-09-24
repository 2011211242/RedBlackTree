PROJECT := $(shell readlink $(dir $(lastword $(MAKEFILE_LIST))) -f)

CXX = g++
CXXFLAGS = -std=c++11 \
		   -g \
		   -Wall \
		   -fno-omit-frame-pointer \
		   -fPIC 

LFLAGS = -l pthread
INC_FLAGS= -I ${PROJECT}/include
BIN_DIR = $(PROJECT)/bin
LIB_DIR = $(PROJECT)/lib
MKDIR = $(BIN_DIR) \
		$(LIB_DIR)

OBJS =  $(shell find $(PROJECT) -type f -name "*.o")
BASE_SRC = $(shell find $(PROJECT)/src -type f -name "*.cpp" -type f ! -name "main.cpp")
BASE_OBJ = $(BASE_SRC:%.cpp=%.o)

MAIN_SRC = $(shell find $(PROJECT)/src -type f -name "main.cpp")
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
	RDTREE=$(BIN_DIR)/rdtree
	LIB_RDTREE=$(LIB_DIR)/librdtree.a
	LD_RDTREE=$(LIB_DIR)/librdtree.so

all: path \
   	rdtree \
   	rdtree_ld \
	rdtree_lib 

path: $(MKDIR)

$(MKDIR):
		mkdir -p $@

rdtree: path $(RDTREE)
rdtree_lib:	path $(LIB_RDTREE)
rdtree_ld: path $(LD_RDTREE)

$(LIB_RDTREE): $(BASE_OBJ)
		ar csrv $@ $^

$(LD_RDTREE): $(BASE_OBJ)
		${CXX} ${CXXFLAGS} -shared $^ -o $@

$(BASE_OBJ): %.o: %.cpp $(BASE_SRC)
		${CXX} ${CXXFLAGS} ${INC_FLAGS} -c $< -o $@

$(MAIN_OBJ): %.o: %.cpp $(MAIN_SRC)
		${CXX} ${CXXFLAGS} ${INC_FLAGS} -c $< -o $@

$(RDTREE): $(BASE_OBJ) $(MAIN_OBJ)
		${CXX} ${CXXFLAGS}  $^ ${LFLAGS} -o $@

make clean:
		rm -rf $(BIN_DIR) $(LIB_DIR) $(OBJS) 
