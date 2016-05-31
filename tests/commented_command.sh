#!/bin/sh

#tests comment commands

cd ..
echo ""
echo "Testing commands with comments now:"


echo "Testing 'ls && echo hello; #comment at end':"
echo "ls && echo hello; exit; #comment at end" | ./bin/rshell
echo "Testing in real bash:"
ls && echo hello; #comment at end


echo "End testing comment commands."
echo ""
