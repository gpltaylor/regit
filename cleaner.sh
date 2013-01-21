#!/bin/bash
echo "Cleanin the place up"
make clean
rm `find ./ -name "*.pro" -print`
rm `find ./ -name "Makefile" -print`
rm `find ./ -name "*~" -print`
rm `find ./ -name "*moc_*" -print`
rm Regit
