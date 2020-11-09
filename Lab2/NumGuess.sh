echo "input tar"
read tar

up=10
down=1

echo "input num between $down and $up"
read ges

while [ $tar -ne $ges ]; do
	if [ $ges -lt $tar ]; then
		down=`expr $ges + 1`
	else
		up=`expr $ges - 1`
	fi

	echo "input num between $down and $up"
	read ges
done
	
