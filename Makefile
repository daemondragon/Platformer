TARGET      = prog
CC          = g++

FILE_TYPE	= cpp

OBJDIR      = obj
SRCDIR      = src
SOURCES     = $(wildcard $(SRCDIR)/*.$(FILE_TYPE))
OBJS        = $(SOURCES:$(SRCDIR)/%.$(FILE_TYPE)=$(OBJDIR)/%.o)

FLAGS       = -Wall -std=c++11 -g
LIBFLAGS    = -lsfml-graphics -lsfml-window -lsfml-system

all : makedir $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(FLAGS) $(LIBFLAGS)

$(OBJS) : $(OBJDIR)/%.o : $(SRCDIR)/%.$(FILE_TYPE)
	$(CC) $< -c -o $@ $(FLAGS) $(LIBFLAGS)

clean :
	rm -f $(OBJS) $(TARGET)

makedir :
	@mkdir -p $(OBJDIR)
