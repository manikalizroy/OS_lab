echo "Enter a num"
read n
org=$n
rev=0

while [ $n -gt 0 ]
do
rem=$((n % 10))
rev=$((rev * 10 + rem))
n=$((n / 10))
done

if [ $rev -eq $org ]
then
    echo "Palindrome"
else
    echo "Not Palindrome"
fi
