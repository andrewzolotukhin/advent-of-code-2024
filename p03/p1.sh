grep -oP 'mul\(\d{1,3},\d{1,3}\)' p02data | awk -F'[(),]' '{sum+= $2 * $3} END { print sum }'
