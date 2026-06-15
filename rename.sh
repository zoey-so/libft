#! /bin/bash

for file in ft_ft*.c; do
	newname=ft_"$(echo "$file" | cut -c5-)"
	mv "$file" "$newname"
done
