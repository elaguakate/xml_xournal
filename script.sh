#!/bin/bash

cp $1 $1.copy

cat $1 | gunzip > $1.raw

xmlstarlet fo $1.raw > $1.xml

./xml_xournal $1.xml

cat $1.xml | gzip > $1 
