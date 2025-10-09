#!/bin/bash

# Define the path to the cub3d executable
CUB3D_EXECUTABLE="./cub3d"

# Define the folder containing the maps
MAPS_FOLDER="./maps/bad/"

# Define the output file
OUTPUT_FILE="cub3d_bad_output.log"

# Loop through each file in the maps folder
for map_file in "$MAPS_FOLDER"*
do
    # Check if the file is a regular file
    if [ -f "$map_file" ]; then
        # Execute cub3d with the current map file
        echo "Executing cub3d with map file: $map_file" >> "$OUTPUT_FILE"
        "$CUB3D_EXECUTABLE" "$map_file" >> "$OUTPUT_FILE" 2>&1
        echo >> "$OUTPUT_FILE"
    fi
done
