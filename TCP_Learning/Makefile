# 定义源文件目录和输出目录
SRCDIR = src
BINDIR = bin

# 获取所有.c文件路径并生成对应的可执行文件名
SOURCES := $(wildcard $(SRCDIR)/*.c)
EXECUTABLES := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SOURCES))

.PHONY: all ones clean

# 默认编译规则为all，将所有.c文件编译成myprogram，并保存到bin目录中
all: $(BINDIR)/myprogram

$(BINDIR)/myprogram: $(SOURCES)
	gcc $^ -o $@

# 编译规则ones，将src目录中的每个.c文件分别编译成对应的可执行文件，并保存到bin目录中
ones: $(EXECUTABLES)

$(BINDIR)/% : $(SRCDIR)/%.c
	gcc $< -o $@

new:
	mkdir bin
	mkdir src
	mkdir inc


# 清理命令，删除bin目录下所有可执行文件
clean:
	rm -f $(BINDIR)/*
