echo "Start main tests"

echo " Begin kw26-1 testing"
gcc kw26-m1.c kw26.c -o kw26-1x
./kw26-1x > kw26-stu1.log
diff kw26-stu1.log kw26-mb1.log

echo " Begin kw26-2 testing - expect fail in diff on line 3"
gcc kw26-m2.c kw26.c -o kw26-2x
./kw26-2x > kw26-stu2.log
diff kw26-stu2.log kw26-mb2.log

echo " Begin kw26-3 testing"
gcc kw26-m3.c kw26.c -o kw26-3x
./kw26-3x > kw26-stu3.log
diff kw26-stu3.log kw26-mb3.log

echo " Begin kw26-4 testing"
gcc kw26-m4.c kw26.c -o kw26-4x
./kw26-4x 100000 cryptoVarFile 0 > kw26-stu4.log 2>>stuPerfRatings
diff kw26-stu4.log kw26-mb4.log
  
echo " Begin kw26-5 testing"
gcc kw26-m5.c kw26.c -o kw26-5x
./kw26-5x cryptoVarFile 0 > kw26-stu5.log
diff kw26-stu5.log kw26-mb5.log

echo " Begin kw26-6 testing"
gcc kw26-m6.c kw26.c -o kw26-6x
./kw26-6x cryptoVarFile plainText2.txt 500 0 > kw26-stu6.log
diff kw26-stu6.log kw26-mb6.log

# add later
#echo "start memCheck - ^c to terminate"
#gcc memCheck.c kw26.c -o memCheckx
#./memCheckx

