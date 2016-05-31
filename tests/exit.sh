#!/bin/sh

#tests the 'exit' command

cd ..

echo ""
echo "Testing commands with exit now:"

echo "Testing 'exit;':"
echo "exit;" | ./bin/rshell
echo "Testing 'echo hello && exit;':"
echo "echo hello && exit;" | ./bin/rshell
echo "Testing 'echo one; echo two; exit; echo three;':"
echo "echo one; echo two; exit; echo three;" | ./bin/rshell
echo "Testing 'errortest || exit':"
echo "errortest || exit;" | ./bin/rshell

echo "End testing exit commands."
echo ""

