num1=5
num2=3
num3=2
if [[ num1 -lt $num2 && $num1 -lt $num2 ]]; then
echo "The minimum of $num1, $num2, and $num3 is $num1"
elif [[ $num2 -lt $num1 && $num2 -lt $num3 ]]; then
echo "The minimum of $num1, $num2, and $num3 is $num2"
else
echo "The minimum of $num1, $num2, and $num3 is $num3"
fi
