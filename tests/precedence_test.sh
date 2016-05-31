#!/bin/sh

#tests commands with precedence operators

cd ..

echo ""
echo ""
echo "Testing precedence operators () now:"

echo ""
echo "Testing '(echo hello)':"
echo "(echo hello); exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo hello)

echo ""
echo "Testing '(echo A && echo B)':"
echo "(echo A && echo B); exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A && echo B)

echo ""
echo "Testing 'echo A || echo B && echo C':"
echo "echo A || echo B && echo C; exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A || echo B && echo C)

echo ""
echo "Testing '(echo A || echo B) && echo C':"
echo "(echo A || echo B) && echo C; exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A || echo B) && echo C

echo ""
echo "Testing 'echo A || (echo B && echo C)':"
echo "echo A || (echo B && echo C); exit;" | ./bin/rshell
echo "Testing in real bash:"
echo A || (echo B && echo C)

echo ""
echo "Testing '(echo A && echo B && error) || ls':"
echo "(echo A && echo B && error) || ls; exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A && echo B && error) || ls

echo ""
echo "Testing '(echo A && echo B) || (echo C && echo D)':"
echo "(echo A && echo B) || (echo C && echo D); exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A && echo B) || (echo C && echo D)

echo ""
echo "Testing 'echo A || echo B; echo C && echo D':"
echo "echo A || echo B; echo C && echo D; exit;" | ./bin/rshell
echo "Testing in real bash:"
echo A || echo B; echo C && echo D

echo ""
echo "Testing 'echo A || (echo B; echo C && echo D)':"
echo "echo A || (echo B; echo C && echo D); exit;" | ./bin/rshell
echo "Testing in real bash:"
echo A || (echo B; echo C && echo D)

echo ""
echo "Testing 'echo A || echo B; echo C; echo D || echo E; echo F':"
echo "echo A || echo B; echo C; echo D || echo E; echo F; exit;" | ./bin/rshell
echo "Testing in real bash:"
echo A || echo B; echo C; echo D || echo E; echo F

echo ""
echo "Testing '(echo A || echo B; echo C; echo D) || (echo E; echo F)':"
echo "(echo A || echo B; echo C; echo D) || (echo E; echo F); exit;" | ./bin/rshell
echo "Testing in real bash:"
(echo A || echo B; echo C; echo D) || (echo E; echo F)

echo ""
echo "Testing '([ -f src/command.h ] && echo hello) || ([ -f src/error ]; echo test)':"
echo "([ -f src/command.h ] && echo hello) && ([ -f src/error ]; echo test); exit;" | ./bin/rshell

echo ""
echo "End testing the 'test' command."
echo ""
echo ""

