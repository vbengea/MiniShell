#!/bin/bash

extensions=("txt" "log" "csv" "json" "xml" "html" "js" "css" "sh" "md" "pdf" "c" "cpp" "h" "hpp" "tpp" "supp" "tif" "dll" "py" "doc" "odt")

for i in {1..100}; do
	name=$(tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 8) # Generate random 8-character name
	ext=${extensions[$RANDOM % ${#extensions[@]}]} # Pick a random extension
	touch "gen_${name}.${ext}"
done

echo "Done"
