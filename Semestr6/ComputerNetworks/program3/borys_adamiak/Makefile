CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = downloader

SRCDIR = src
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/downloader.o

# Create obj directory if not exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/downloader.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/downloader.o: $(SRCDIR)/downloader.cpp $(SRCDIR)/downloader.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
distclean: clean
	rm -rf $(OBJDIR) $(TARGET) *.tar.gz

.PHONY: all clean
