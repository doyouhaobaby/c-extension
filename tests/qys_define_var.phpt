--TEST--
Check for qys presence
--SKIPIF--
<?php if (!extension_loaded("qys")) print "skip"; ?>
--FILE--
<?php 
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8Bhello-word/
echo "qys extension is available";
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php7/README.TESTING for further information on
  writing regression tests
*/
echo PHP_EOL;

class demo {}
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E5%88%9B%E5%BB%BA%E5%8F%98%E9%87%8F/
// $lng = 2;
// $str = "abc";
// $arr = array(1,'a' => 'b');
// $obj = new demo();

qys_define_var();
 
var_dump($lng);
var_dump($str);
var_dump($arr);
var_dump($obj);
var_dump($boo);

?>
--EXPECT--
qys extension is available
