#!/bin/bash

make gcov_report >> report
cat ./report
coverage_lines=$(awk '/lines/' report | awk '{print $2}')
IFS=%
for coverage in $coverage_lines
do
  coverage_lines=$(printf %.0f "$(echo "$coverage"*100 | bc)")
done
coverage_functions=$(awk '/functions/' report | awk '{print $2}')
for coverage in $coverage_functions
do
  coverage_functions=$(printf %.0f "$(echo "$coverage"*100 | bc)")
done
if [ "$coverage_lines" -gt 8000 ] && [ "$coverage_functions" -gt 8000 ]
then exit 0
else exit 1
fi