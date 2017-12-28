--TEST--
Check for qys presence
--SKIPIF--
<?php if (!extension_loaded("qys")) print "skip"; ?>
--FILE--
<?php 
// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E4%BC%A0%E5%8F%82%E4%B8%8E%E8%BF%94%E5%9B%9E%E5%80%BC/
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
var_dump(qys_default_value("int"));
var_dump(qys_default_value("int", 1));
var_dump(qys_default_value("bool"));
var_dump(qys_default_value("bool", true));
var_dump(qys_default_value("str"));
var_dump(qys_default_value("str", "a"));
var_dump(qys_default_value("array"));
?>
--EXPECT--
qys extension is available
