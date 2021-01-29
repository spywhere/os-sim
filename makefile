CC=g++

CPPFLAGS=

# Library
LIBS=

# Source goes here
SOURCEDIR=src

# Source files
SOURCES=\
asm/instruction.cpp \
asm/f0instruction.cpp \
asm/f1instruction.cpp \
asm/f2instruction.cpp \
asm/f3instruction.cpp \
asm/format0/halt.cpp \
asm/format1/add.cpp \
asm/format1/cmp.cpp \
asm/format1/div.cpp \
asm/format1/mov.cpp \
asm/format1/mul.cpp \
asm/format1/sub.cpp \
asm/format2/in.cpp \
asm/format2/mov.cpp \
asm/format2/out.cpp \
asm/format3/jeq.cpp \
asm/format3/jmp.cpp \
asm/format3/jne.cpp \
asm/format3/jneg.cpp \
asm/format3/jpl.cpp \
os/process.cpp \
os/processReport.cpp \
ui/table.cpp \
logger.cpp \
os.cpp \
utils.cpp \
main.cpp

# Info
OBJDIR=objs
ALL_OBJS=$(SOURCES:%.cpp=%.o)
APP_OBJS=$(ALL_OBJS:%.o=$(OBJDIR)/%.o)

OUTDIR=bin
APPEXE=OSSim

all: preclean link

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(FULL_FLAGS) -c $< -o $@

link: $(APP_OBJS)
	@echo "Linking..."
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$(APPEXE) $+ $(LIBS)

run:
	@echo "Running..."
	@$(OUTDIR)/$(APPEXE)

preclean:
	@echo "Pre Cleaning..."
	@rm -rf $(OUTDIR)/$(APPEXE)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR) $(OUTDIR)