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
// echo PHP_EOL;
// echo qys_args_base(1,2,3);
// // must three args
// //echo qys_args_base(1,2);

// qys_zend_parse_para('i am stirng', true);
// //qys_zend_parse_para(true, 1);

// //qys_zend_parse_array([1]);
// //qys_zend_parse_array([2], 5);

// class demo {

// }

// qys_zend_parse_object(new demo);
// //qys_zend_parse_object(5); error
// //
// qys_zend_args(1,2,3);

//qys_zend_args(1,2,3,4);

///class demo {}

// var_dump(qys_zend_parse_array(1));
// var_dump(qys_zend_parse_array('string'));
// var_dump(qys_zend_parse_array([5]));
// var_dump(qys_zend_parse_array(new demo));
// var_dump(qys_zend_parse_array(65.5));
// var_dump(qys_zend_parse_array(null));
// var_dump(qys_zend_parse_array());
// var_dump(qys_zend_parse_array());
// var_dump(qys_zend_parse_array());
// var_dump(qys_zend_parse_array());
// var_dump(qys_zend_parse_array());
// 
qys_zend_parse_array(44);
?>
--EXPECT--
qys extension is available
