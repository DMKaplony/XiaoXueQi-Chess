#############################################################################
# Makefile for building: project
# Generated by qmake (2.01a) (Qt 4.8.2) on: Wed Jun 27 21:02:38 2012
# Project:  project.pro
# Template: app
# Command: /usr/local/Trolltech/Qt-4.8.2/bin/qmake -spec /usr/local/Trolltech/Qt-4.8.2/mkspecs/linux-g++ -o Makefile project.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/Qt-4.8.2/mkspecs/linux-g++ -I. -I/usr/local/Trolltech/Qt-4.8.2/include/QtCore -I/usr/local/Trolltech/Qt-4.8.2/include/QtGui -I/usr/local/Trolltech/Qt-4.8.2/include -I. -I.
LINK          = g++
LFLAGS        = -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.2/lib
LIBS          = $(SUBLIBS)  -L/usr/local/Trolltech/Qt-4.8.2/lib -lQtGui -L/usr/local/Trolltech/Qt-4.8.2/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/local/Trolltech/Qt-4.8.2/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Chessman.cpp \
		Image.cpp \
		main.cpp \
		Button.cpp \
		LeftFrame.cpp \
		RightFrame.cpp \
		Chess.cpp moc_Image.cpp \
		moc_Button.cpp \
		moc_LeftFrame.cpp \
		moc_RightFrame.cpp \
		moc_Chess.cpp
OBJECTS       = Chessman.o \
		Image.o \
		main.o \
		Button.o \
		LeftFrame.o \
		RightFrame.o \
		Chess.o \
		moc_Image.o \
		moc_Button.o \
		moc_LeftFrame.o \
		moc_RightFrame.o \
		moc_Chess.o
DIST          = /usr/local/Trolltech/Qt-4.8.2/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/include_source_dir.prf \
		project.pro
QMAKE_TARGET  = project
DESTDIR       = 
TARGET        = project

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: project.pro  /usr/local/Trolltech/Qt-4.8.2/mkspecs/linux-g++/qmake.conf /usr/local/Trolltech/Qt-4.8.2/mkspecs/common/unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/linux.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/qconfig.pri \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/debug.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/moc.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/resources.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/uic.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/lex.prf \
		/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/include_source_dir.prf \
		/usr/local/Trolltech/Qt-4.8.2/lib/libQtGui.prl \
		/usr/local/Trolltech/Qt-4.8.2/lib/libQtCore.prl
	$(QMAKE) -spec /usr/local/Trolltech/Qt-4.8.2/mkspecs/linux-g++ -o Makefile project.pro
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/unix.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/linux.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/gcc-base-unix.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-base.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/common/g++-unix.conf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/qconfig.pri:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/debug.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/default_post.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/warn_on.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/qt.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/moc.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/resources.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/uic.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/yacc.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/lex.prf:
/usr/local/Trolltech/Qt-4.8.2/mkspecs/features/include_source_dir.prf:
/usr/local/Trolltech/Qt-4.8.2/lib/libQtGui.prl:
/usr/local/Trolltech/Qt-4.8.2/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Trolltech/Qt-4.8.2/mkspecs/linux-g++ -o Makefile project.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/project1.0.0 || $(MKDIR) .tmp/project1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/project1.0.0/ && $(COPY_FILE) --parents Chessman.h def.h Image.h Button.h LeftFrame.h RightFrame.h Chess.h .tmp/project1.0.0/ && $(COPY_FILE) --parents Chessman.cpp Image.cpp main.cpp Button.cpp LeftFrame.cpp RightFrame.cpp Chess.cpp .tmp/project1.0.0/ && (cd `dirname .tmp/project1.0.0` && $(TAR) project1.0.0.tar project1.0.0 && $(COMPRESS) project1.0.0.tar) && $(MOVE) `dirname .tmp/project1.0.0`/project1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/project1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_Image.cpp moc_Button.cpp moc_LeftFrame.cpp moc_RightFrame.cpp moc_Chess.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_Image.cpp moc_Button.cpp moc_LeftFrame.cpp moc_RightFrame.cpp moc_Chess.cpp
moc_Image.cpp: Chessman.h \
		def.h \
		Image.h \
		Image.h
	/usr/local/Trolltech/Qt-4.8.2/bin/moc $(DEFINES) $(INCPATH) Image.h -o moc_Image.cpp

moc_Button.cpp: Button.h
	/usr/local/Trolltech/Qt-4.8.2/bin/moc $(DEFINES) $(INCPATH) Button.h -o moc_Button.cpp

moc_LeftFrame.cpp: def.h \
		Image.h \
		Chessman.h \
		Button.h \
		LeftFrame.h
	/usr/local/Trolltech/Qt-4.8.2/bin/moc $(DEFINES) $(INCPATH) LeftFrame.h -o moc_LeftFrame.cpp

moc_RightFrame.cpp: def.h \
		Button.h \
		RightFrame.h
	/usr/local/Trolltech/Qt-4.8.2/bin/moc $(DEFINES) $(INCPATH) RightFrame.h -o moc_RightFrame.cpp

moc_Chess.cpp: def.h \
		LeftFrame.h \
		Image.h \
		Chessman.h \
		Button.h \
		RightFrame.h \
		Chess.h
	/usr/local/Trolltech/Qt-4.8.2/bin/moc $(DEFINES) $(INCPATH) Chess.h -o moc_Chess.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

Chessman.o: Chessman.cpp Chessman.h \
		def.h \
		Image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Chessman.o Chessman.cpp

Image.o: Image.cpp Image.h \
		Chessman.h \
		def.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Image.o Image.cpp

main.o: main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

Button.o: Button.cpp Button.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Button.o Button.cpp

LeftFrame.o: LeftFrame.cpp LeftFrame.h \
		def.h \
		Image.h \
		Chessman.h \
		Button.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LeftFrame.o LeftFrame.cpp

RightFrame.o: RightFrame.cpp RightFrame.h \
		def.h \
		Button.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RightFrame.o RightFrame.cpp

Chess.o: Chess.cpp Chess.h \
		def.h \
		LeftFrame.h \
		Image.h \
		Chessman.h \
		Button.h \
		RightFrame.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Chess.o Chess.cpp

moc_Image.o: moc_Image.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Image.o moc_Image.cpp

moc_Button.o: moc_Button.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Button.o moc_Button.cpp

moc_LeftFrame.o: moc_LeftFrame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_LeftFrame.o moc_LeftFrame.cpp

moc_RightFrame.o: moc_RightFrame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_RightFrame.o moc_RightFrame.cpp

moc_Chess.o: moc_Chess.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Chess.o moc_Chess.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

