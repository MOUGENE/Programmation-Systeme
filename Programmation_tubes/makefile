EXEC = Exercice3
OBJECTS = 
PROJECT_NAME = 


.SUFFIXES: .c .o

EXEC_O = $(EXEC:=.o)
OBJECTS_O = $(OBJECTS) $(EXEC_O)

CC = gcc
CFLAGS = -Wall


all: msg $(OBJECTS) $(EXEC_O)
	@echo "Create executables..."
	@for i in $(EXEC); do \
	$(CC) -o $$i $$i.o $(OBJECTS); \
	done
	@echo "Done."

msg:
	@echo "Create objects..."


%.o : %.c
	@cd $(dir $<) && $(CC) $(CFLAGS) -c $(notdir $<) -o $(notdir $@)


clean:
	@echo "Delete"
	@rm -f *.o
	@echo "Done."