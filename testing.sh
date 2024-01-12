./coolness >> testing.out
echo no input 
./coolness -100 >> testing.out
echo out of bounds
./coolness 1 2 3
echo too many args >> testing.out
./coolness 32.0
echo one input
./coolness 32.0 10.0 >> testing.out
echo two inputs


