echo "Enter a limit"
read n
a=0
b=1
i=1
echo "Fibo series:"
echo "$a"
sum=0
while [ $i -le $n ]
do
sum=$(($a+$b))
a=$b
b=$sum
i=$(($i+1))
echo "$sum"
done
