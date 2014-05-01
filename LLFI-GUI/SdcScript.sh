value=`cat $1`

value1=`cat $2`

case $value in
     *"$value1"*) printf "Identical\n";;
     *) printf "Not Identical\n";;
esac

