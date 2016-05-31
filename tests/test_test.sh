#!/bin/sh

#tests for the 'test' command

cd ..

echo ""
echo "Testing the 'test' command now:"

echo "Testing 'test hello':"
echo "test hello; exit;" | ./bin/rshell
echo "Testing 'test README.md':"
echo "test README.md; exit;" | ./bin/rshell
echo "Testing 'test -e README.md':"
echo "test -e README.md; exit;" | ./bin/rshell
echo "Testing 'test -f README.md':"
echo "test -f README.md; exit;" | ./bin/rshell
echo "Testing 'test -d README.md':"
echo "test -d README.md; exit;" | ./bin/rshell
echo "Testing 'test -e -f README.md':"
echo "test -e -f README.md; exit;" | ./bin/rshell
echo "Testing 'test src/command.h':"
echo "test src/command.h; exit;" | ./bin/rshell
echo "Testing 'test -d src/command.h':"
echo "test -d src/command.h; exit;" | ./bin/rshell
echo "Testing 'test -f src/command.h':"
echo "test -f src/command.h; exit;" | ./bin/rshell
echo "Testing '[ src/command.h ]':"
echo "[ src/command.h ]; exit;" | ./bin/rshell
echo "Testing '[ -f src/command.h ]':"
echo "[ -f src/command.h ]; exit;" | ./bin/rshell
echo "Testing '[ -f src/command.h ] && echo hello && [ -f src/error ]':"
echo "[ -f src/command.h ] && echo hello && [ -f src/error ]; exit;" | ./bin/rshell
echo "Testing 'test -f error && echo hello && echo hi':"
echo "test -f error && echo hello && echo hi; exit;" | ./bin/rshell
echo "Testing 'test -f src/command.h; [ src/and.h ]; test -f src/main.cpp':"
echo "test -f src/command.h; [ src/and.h ]; test -f src/main.cpp; exit;" | ./bin/rshell
echo "Testing '[ src/and.h ] || echo notshown || [ src/or.h ]; echo hello"
echo "[ src/and.h ] || echo notshown || [ src/or.h ]; echo hello; exit;" | ./bin/rshell

echo "End testing the 'test' command."
echo ""

