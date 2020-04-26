for i in ka_data.*  # loop over testdata files
do
    old_ka $i >out1 # run the old version
    new_ka $i >out2 # run the new version
    if ! cmp -s out1 out2   # compare output files
    then
        echo $i: BAD    # different: print error message
    fi
done