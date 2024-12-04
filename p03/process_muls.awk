BEGIN {skip = 0; sum = 0}  # Initialize skip and sum to 0

$1 == "don" {skip = 1; next}  # Set skip to 1 when "don't()" is encountered
$1 == "do" {skip = 0; next}      # Reset skip to 0 when "do()" is encountered

skip == 0 && $1 == "mul" {sum += $2 * $3}  # Add only when not skipping

END {print sum}  # Print the total sum
