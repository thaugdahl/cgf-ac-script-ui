# Outputs a help message if the needed parameters are not passed
help_message() {
    echo "File Processor"
    echo "Usage: ./process.sh {input_file} {output_file}"
}


# Resets the Internal Field Separator
reset_ifs() {
    IFS=$DEFAULT_IFS
}

arg_is_directory() {
    echo $INPUT_FILE
    if [ -d $1 ]; then
        result=1
    else
        result=0
    fi
}

file_checks() {
    if [ ! -f ${INPUT_FILE} ] && [ ! -d ${INPUT_FILE} ]; then
        echo "${INPUT_FILE} not found. Aborting."
        exit
    fi

    if [ -d ${INPUT_FILE} ]; then
        MODE=1
        # Create the output directory if it does not already exist
        if [ ! -d $OUTPUT_FILE ]; then
            mkdir -v $OUTPUT_FILE
        fi


    fi

    if [ -f ${OUTPUT_FILE} ]; then
        echo "${OUTPUT_FILE} exists. Do you want to overwrite it? (y/n)"
        read ANSWER

        if [ ${ANSWER} != "y" ]; then
            echo "Aborting..."
            exit
        fi

        echo "You have chosen to overwrite ${OUTPUT_FILE}"
    fi
}

add_single_replace() {
    SED_PATTERN="${SED_PATTERN};0,/${CURRENT_PATTERN[0]}/s/${CURRENT_PATTERN[0]}/${CURRENT_PATTERN[1]}/"
    echo "Replacing ONE occurence of ${CURRENT_PATTERN[0]} with ${CURRENT_PATTERN[1]}"
}

add_global_replace() {
    SED_PATTERN="${SED_PATTERN};s/${CURRENT_PATTERN[0]}/${CURRENT_PATTERN[1]}/"
    echo "Replacing ALL occurences of ${CURRENT_PATTERN[0]} with ${CURRENT_PATTERN[1]}"
}

read_patterns() {
    IFS=$'\n'
    if [ -f "patterns.txt" ]; then
        PATTERNS=($(cat patterns.txt))
    else
        result=0
        return
    fi

    result=1

    for num in $(seq 0 $((${#PATTERNS[@]} - 1))); do
        reset_ifs
        CURRENT_PATTERN=($(echo ${PATTERNS[$num]}))
        NUM_ELEMS=${#CURRENT_PATTERN[@]}

        if [ ${CURRENT_PATTERN[0]} == "#" ]; then
            continue
        fi


        if [ $NUM_ELEMS -eq 3 ] && [ ${CURRENT_PATTERN[2]} -eq "0" ];
        then
            add_single_replace
        else
            add_global_replace
        fi

    done
}

set_default_patterns() {
    PATTERNS_MATCH=("PCW" "PCW" "PCW")
    PATTERNS_REPLACE=("Pth_x" "Pth_y" "Pth_z")

    SED_PATTERN=

    for x in $(seq 0 $((${#PATTERNS_MATCH[@]} - 1))); do
        CURRENT_PATTERN=(${PATTERNS_MATCH[$x]} ${PATTERNS_REPLACE[$x]})
        add_single_replace
    done
}

replace_entire_directory() {
    IFS=$'\n'

    # Get the list of files to handle
    cd $INPUT_FILE
    FILES=($(ls *${FILE_SUFFIX}))
    cd ..

    # echo ${FILES} | xargs -I{} echo {}
    printf "%s\n" ${FILES[@]} | xargs -P 8 -I{} sh -c "sed \"${SED_PATTERN}\" $INPUT_FILE/{} > $OUTPUT_FILE/{}"

    # Apply `sed` to all files
    # for FILE in ${FILES[@]}; do
    #     sed "${SED_PATTERN}" $INPUT_FILE/${FILE} > $OUTPUT_FILE/${FILE}
    # done

    reset_ifs
}
