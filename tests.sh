for t in tests/broken-1.sol ; do
    #tests/*.sol; do
  echo $t
  i=tests/$(basename $t .sol).in
  o=tests/$(basename $t .sol).sol
  ./mydht <$i | diff -u --color $o -
done

