#!/bin/bash

# var[index_position]

transport=('car' 'train' 'bike' 'bus')

# @ means all the arguments
echo "${transport[@]}"

# To simply output "train"
echo "${transport[1]}"

# To change an element, or delete it, it's used 'unset'
# This will remove 'train' 
unset transport[1]

# To set anything else, it can be done:
transport[1]='trainride'

echo "${transport[@]}"
