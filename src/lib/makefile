# libdaijoubu
# Copyright (C) 2015 David Jolly
# ----------------------
#
# libdaijoubu is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libdaijoubu is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=clang++
CC_FLAGS=-march=native -pthread -std=gnu++11 -O3 -Wall -Werror -fPIC
DIR_BIN=./../../bin/
DIR_BUILD=./../../build/
DIR_INC=./include/
DIR_SRC=./src/
LIB=libdaijoubu.a

all: build archive

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)daijoubu.o $(DIR_BUILD)daijoubu_exception.o $(DIR_BUILD)daijoubu_language.o $(DIR_BUILD)daijoubu_lexer.o $(DIR_BUILD)daijoubu_token.o $(DIR_BUILD)daijoubu_uid.o $(DIR_BUILD)daijoubu_unicode.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: daijoubu.o daijoubu_exception.o daijoubu_language.o daijoubu_lexer.o daijoubu_token.o daijoubu_uid.o daijoubu_unicode.o

daijoubu.o: $(DIR_SRC)daijoubu.cpp $(DIR_INC)daijoubu.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu.cpp -o $(DIR_BUILD)daijoubu.o

daijoubu_exception.o: $(DIR_SRC)daijoubu_exception.cpp $(DIR_INC)daijoubu_exception.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_exception.cpp -o $(DIR_BUILD)daijoubu_exception.o

# COMPONENTS

daijoubu_token.o: $(DIR_SRC)daijoubu_token.cpp $(DIR_INC)daijoubu_token.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_token.cpp -o $(DIR_BUILD)daijoubu_token.o

daijoubu_uid.o: $(DIR_SRC)daijoubu_uid.cpp $(DIR_INC)daijoubu_uid.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_uid.cpp -o $(DIR_BUILD)daijoubu_uid.o

daijoubu_unicode.o: $(DIR_SRC)daijoubu_unicode.cpp $(DIR_INC)daijoubu_unicode.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_unicode.cpp -o $(DIR_BUILD)daijoubu_unicode.o

# LANGUAGE

daijoubu_language.o: $(DIR_SRC)daijoubu_language.cpp $(DIR_INC)daijoubu_language.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_language.cpp -o $(DIR_BUILD)daijoubu_language.o

daijoubu_lexer.o: $(DIR_SRC)daijoubu_lexer.cpp $(DIR_INC)daijoubu_lexer.h
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)daijoubu_lexer.cpp -o $(DIR_BUILD)daijoubu_lexer.o
