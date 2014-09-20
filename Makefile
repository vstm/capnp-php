#
#	Makefile template
#
#	This is an example Makefile that can be used by anyone who is building
#	his or her own PHP extensions using the PHP-CPP library. 
#
#	In the top part of this file we have included variables that can be
#	altered to fit your configuration, near the bottom the instructions and
#	dependencies for the compiler are defined. The deeper you get into this
#	file, the less likely it is that you will have to change anything in it.
#

#
#	Name of your extension
#
#	This is the name of your extension. Based on this extension name, the
#	name of the library file (name.so) and the name of the config file (name.ini)
#	are automatically generated
#

NAME				=	capnp-php


#
#	Php.ini directories
#
#	In the past, PHP used a single php.ini configuration file. Today, most
#	PHP installations use a conf.d directory that holds a set of config files,
#	one for each extension. Use this variable to specify this directory.
#

INI_DIR				=	/etc/php5/conf.d


#
#	The extension dirs
#
#	This is normally a directory like /usr/lib/php5/20121221 (based on the 
#	PHP version that you use. We make use of the command line 'php-config' 
#	instruction to find out what the extension directory is, you can override
#	this with a different fixed directory
#

EXTENSION_DIR		=	$(shell php-config --extension-dir)


#
#	The name of the extension and the name of the .ini file
#
#	These two variables are based on the name of the extension. We simply add
#	a certain extension to them (.so or .ini)
#

EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini


#
#	Compiler
#
#	By default, the GNU C++ compiler is used. If you want to use a different
#	compiler, you can change that here. You can change this for both the 
#	compiler (the program that turns the c++ files into object files) and for
#	the linker (the program that links all object files into the single .so
#	library file. By default, g++ (the GNU C++ compiler) is used for both.
#

COMPILER			=	g++
LINKER				=	g++


#
#	Compiler and linker flags
#
#	This variable holds the flags that are passed to the compiler. By default, 
# 	we include the -O2 flag. This flag tells the compiler to optimize the code, 
#	but it makes debugging more difficult. So if you're debugging your application, 
#	you probably want to remove this -O2 flag. At the same time, you can then 
#	add the -g flag to instruct the compiler to include debug information in
#	the library (but this will make the final libphpcpp.so file much bigger, so
#	you want to leave that flag out on production servers).
#
#	If your extension depends on other libraries (and it does at least depend on
#	one: the PHP-CPP library), you should update the LINKER_DEPENDENCIES variable
#	with a list of all flags that should be passed to the linker.
#

#COMPILER_FLAGS		=	-Wall -c -O2 -std=c++11 -fpic -o
COMPILER_FLAGS		=	-Wall -c -g -std=c++11 -fpic -o
LINKER_FLAGS		=	-shared 
LINKER_DEPENDENCIES	=	-lphpcpp -lcapnp -lcapnpc -lkj


#
#	Command to remove files, copy files and create directories.
#
#	I've never encountered a *nix environment in which these commands do not work. 
#	So you can probably leave this as it is
#

RM					=	rm -f
CP					=	cp -f
MKDIR				=	mkdir -p


#
#	All source files are simply all *.cpp files found in the current directory
#
#	A builtin Makefile macro is used to scan the current directory and find 
#	all source files. The object files are all compiled versions of the source
#	file, with the .cpp extension being replaced by .o.
#

SOURCES				=	$(wildcard *.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)

EGREP = grep -E
SHTOOL = shtool
PHP_EXECUTABLE = /usr/bin/php
PHP_TEST_SETTINGS = -d 'open_basedir=' -d 'output_buffering=0' -d 'memory_limit=-1'
PHP_DEPRECATED_DIRECTIVES_REGEX = '^(magic_quotes_(gpc|runtime|sybase)?|(zend_)?extension(_debug)?(_ts)?)[\t\ ]*='
top_builddir = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
top_srcdir = ${top_builddir}

#
#	From here the build instructions start
#

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

%.o: %.cpp %.h
						${COMPILER} ${COMPILER_FLAGS} $@ $<
%.o: %.cpp
						${COMPILER} ${COMPILER_FLAGS} $@ $<

install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR}
				
clean:
						${RM} ${EXTENSION} ${OBJECTS}

test: all
	@if test ! -z "$(PHP_EXECUTABLE)" && test -x "$(PHP_EXECUTABLE)"; then \
		INI_FILE=`$(PHP_EXECUTABLE) -d 'display_errors=stderr' -r 'echo php_ini_loaded_file();' 2> /dev/null`; \
		if test "$$INI_FILE"; then \
			$(EGREP) -h -v $(PHP_DEPRECATED_DIRECTIVES_REGEX) "$$INI_FILE" > $(top_builddir)/tmp-php.ini; \
		else \
			echo > $(top_builddir)/tmp-php.ini; \
		fi; \
		INI_SCANNED_PATH=`$(PHP_EXECUTABLE) -d 'display_errors=stderr' -r '$$a = explode(",\n", trim(php_ini_scanned_files())); echo $$a[0];' 2> /dev/null`; \
		if test "$$INI_SCANNED_PATH"; then \
			INI_SCANNED_PATH=`$(SHTOOL) path -d $$INI_SCANNED_PATH`; \
			$(EGREP) -h -v $(PHP_DEPRECATED_DIRECTIVES_REGEX) "$$INI_SCANNED_PATH"/*.ini >> $(top_builddir)/tmp-php.ini; \
		fi; \
		cat "$(INI)" >> $(top_builddir)/tmp-php.ini; \
		TEST_PHP_EXECUTABLE=$(PHP_EXECUTABLE) \
		TEST_PHP_SRCDIR=$(top_srcdir) \
		CC="$(CC)" \
			$(PHP_EXECUTABLE) -n -d extension_dir=$(top_builddir)/ -c $(top_builddir)/tmp-php.ini $(PHP_TEST_SETTINGS) $(top_srcdir)/run-tests.php -n -c $(top_builddir)/tmp-php.ini -d extension_dir=$(top_builddir)/ $(PHP_TEST_SHARED_EXTENSIONS) $(TESTS); \
		TEST_RESULT_EXIT_CODE=$$?; \
		exit $$TEST_RESULT_EXIT_CODE; \
	else \
		echo "ERROR: Cannot run tests without CLI sapi."; \
	fi
