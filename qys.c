/*
  +----------------------------------------------------------------------+
  | Query Yet Simple                                                       |
  +----------------------------------------------------------------------+
  | Copyright (c) 2010-2018 http://queryphp.com All rights reserved.                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Xiangmin Liu  <635750556@qq.com>                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_qys.h"

/* If you declare any globals in php_qys.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(qys)
*/

/* True global resources - no need for thread safety here */
static int le_qys;

zend_class_entry *children_ce;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("qys.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_qys_globals, qys_globals)
    STD_PHP_INI_ENTRY("qys.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_qys_globals, qys_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ children_functions[]
 *
 * Every user visible function must have an entry in children_functions[].
 */
PHP_METHOD(children, learn);

ZEND_BEGIN_ARG_INFO_EX(arginfo_children_learn, 0, 0, 1)
    ZEND_ARG_INFO(0, love)
ZEND_END_ARG_INFO()
const zend_function_entry children_methods[] = {
	PHP_ME(children, learn, arginfo_children_learn, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}	/* Must be the last line in children_functions[] */
};
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_qys_compiled(string arg)
   Return a string to confirm that the module is compiled in */

PHP_METHOD(children, learn)
{
	char *love = NULL;
	size_t love_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &love, &love_len) == FAILURE) {
		return;
	}

	zend_update_property_string(children_ce,  getThis(), "memory", sizeof("memory") - 1, love);
}

PHP_FUNCTION(qys_call_function)
{
    zval            *obj = NULL;
    zval            *fun = NULL;
    zval            *param = NULL;
    zval            retval;
    zval            args[1];

#ifndef FAST_ZPP
    /* Get function parameters and do error-checking. */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "zzz", &obj, &fun, &param) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_ZVAL(obj)
        Z_PARAM_ZVAL(fun)
        Z_PARAM_ZVAL(param)
    ZEND_PARSE_PARAMETERS_END();
#endif

    args[0] = *param;
    if (obj == NULL || Z_TYPE_P(obj) == IS_NULL) {
        call_user_function_ex(EG(function_table), NULL, fun, &retval, 1, args, 0, NULL);
    } else {
        call_user_function_ex(EG(function_table), obj, fun, &retval, 1, args, 0, NULL);
    }
    RETURN_ZVAL(&retval, 0, 1);
}

PHP_FUNCTION(confirm_qys_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "qys", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(qys_helloworld)
{
    zend_string *strg;
    strg = strpprintf(0, "hello word, my qys,YES");
    RETURN_STR(strg);
}


PHP_FUNCTION(qys_default_value)
{
    zend_string     *type;
    zval            *value = NULL;

#ifndef FAST_ZPP
    /* Get function parameters and do error-checking. */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S|z", &type, &value) == FAILURE) {
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STR(type)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL_EX(value, 0, 1)
    ZEND_PARSE_PARAMETERS_END();
#endif

    if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value == NULL) {
        RETURN_LONG(0);
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value == NULL) {
        RETURN_FALSE;
    } else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value == NULL) {
        RETURN_EMPTY_STRING();
    } else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1);
    }
    RETURN_NULL();
}

PHP_FUNCTION(qys_get_size)
{
    zval *val;
    size_t size;
    zend_string *result;
    HashTable *myht;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &val) == FAILURE) {
        return;
    }

    if (Z_TYPE_P(val) == IS_STRING) {
        result = strpprintf(0, "string size is %d", Z_STRLEN_P(val));
    } else if (Z_TYPE_P(val) == IS_ARRAY) {
        myht = Z_ARRVAL_P(val);
        result = strpprintf(0, "array size is %d", zend_array_count(myht));
    } else {
        result = strpprintf(0, "can not support");
    }

    RETURN_STR(result);
}

PHP_FUNCTION(qys_args_base)
{
	if(ZEND_NUM_ARGS() != 3){
		WRONG_PARAM_COUNT;
	}
}

// 函数参数分析 test
PHP_FUNCTION(qys_zend_parse_para) {
	int slen;
	char *str;
	zend_bool b;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "sb", &str, &slen, &b) == FAILURE) {
		return;
	}
}

void display_value(zval *zv)
{
	if(Z_TYPE_P(zv) != IS_STRING) {
		php_printf("这个变量不是字符串");
		return;
	}

	PHPWRITE(Z_STRVAL_P(zv), Z_STRLEN_P(zv));
}

// 数组参数
PHP_FUNCTION(qys_zend_parse_array) {
	zval *arg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &arg) == FAILURE) {
		return;
	}


	display_value(arg);

	// switch (Z_TYPE_P(arg)) {
	// 	case IS_NULL:
	// 		RETVAL_STRING("NULL");
	// 		break;

	// 	case IS_FALSE:
	// 	case IS_TRUE:
	// 		RETVAL_STRING("boolean");
	// 		break;

	// 	case IS_LONG:
	// 		RETVAL_STRING("integer");
	// 		break;

	// 	case IS_DOUBLE:
	// 		RETVAL_STRING("double");
	// 		break;

	// 	case IS_STRING:
	// 		RETVAL_STRING("string");
	// 		break;

	// 	case IS_ARRAY:
	// 		RETVAL_STRING("array");
	// 		break;

	// 	case IS_OBJECT:
	// 		RETVAL_STRING("object");

	// 	   {
	// 	   char *result;
	// 	   int res_len;

	// 	   res_len = sizeof("object of type ")-1 + Z_OBJCE_P(arg)->name_length;
	// 	   spprintf(&result, 0, "object of type %s", Z_OBJCE_P(arg)->name);
	// 	   RETVAL_STRINGL(result, res_len);
	// 	   efree(result);
	// 	   }

	// 		break;

	// 	case IS_RESOURCE:
	// 		{
	// 			const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RES_P(arg));

	// 			if (type_name) {
	// 				RETVAL_STRING("resource");
	// 				break;
	// 			}
	// 		}

	// 	default:
	// 		RETVAL_STRING("unknown type");
	//}
}

PHP_FUNCTION(qys_zend_parse_object) {
	zval *object;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "o!", &object) == FAILURE) {
		return;
	}
}

PHP_FUNCTION(qys_zend_args) {
	// zval *parameters_list[3];
	// int num_args = ZEND_NUM_ARGS();

	// if(num_args > 3) {
	//  	WRONG_PARAM_COUNT;
	// }

	// // //zend_get_parameters_ex
	// // //zend_get_parameters_array_ex
	// if(_zend_get_parameters_array_ex(num_args, &parameters_list) == FAILURE) {
	//  	return;
	// }

	//php_printf("%s", parameters_list[0]);
	//php_printf("%s", parameters_list[1]);
	//php_printf("%s", parameters_list[3]);

}



PHP_FUNCTION(qys_define_var)
{
	zval var_value; //变量的值
    zend_string *var_name = NULL; //变量名称

    //创建整型变量
    ZVAL_LONG(&var_value, 2);
    zend_set_local_var_str("lng", 3 , &var_value, 0); //设置本地变量
    ZVAL_NULL(&var_value);

    //创建字符串变量
    zend_string *str = NULL;
    char content[4] = "abc";
    var_name = zend_string_init("str", 3, 0); //设置变量名称
    str = zend_string_init(content, sizeof(content) - 1, 0);
    ZVAL_STR(&var_value, str); //设置变量的值
    zend_set_local_var(var_name, &var_value, 0); //设置本地变量
    zend_string_release(var_name);
    ZVAL_NULL(&var_value);

    //创建数组变量
    var_name = zend_string_init("arr", 3, 0); //设置变量名称
    array_init(&var_value);
    add_index_long(&var_value, 0, 1);
    add_assoc_stringl_ex(&var_value, "a", 1, "b", 1);
    zend_set_local_var(var_name, &var_value, 0); //设置本地变量
    zend_string_release(var_name);
    ZVAL_NULL(&var_value);

    //创建对象变量
    zend_class_entry *ce;
    zend_string *class_name;
    class_name = zend_string_init("demo", 4, 0);
    ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO); //获取类
    zend_string_release(class_name);
    object_init_ex(&var_value, ce);
    zend_set_local_var_str("obj", 3, &var_value, 0); //设置本地变量
    ZVAL_NULL(&var_value);

    // 创建BOOL变量
    ZVAL_BOOL(&var_value, 2);
    zend_set_local_var_str("boo", 3 , &var_value, 0); //设置本地变量
    ZVAL_NULL(&var_value);

}

// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%A4%84%E7%90%86/
PHP_FUNCTION(qys_str_concat)
{
	zend_string *prefix, *subject, *result;
    zval *string;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sz", &prefix, &string) == FAILURE) {
       return;
    }

    subject = zval_get_string(string);
    if (zend_binary_strncmp(ZSTR_VAL(prefix), ZSTR_LEN(prefix), ZSTR_VAL(subject), ZSTR_LEN(subject), ZSTR_LEN(prefix)) == 0) {
        RETURN_STR(subject);
    }
    result = strpprintf(0, "%s %s", ZSTR_VAL(prefix), ZSTR_VAL(subject));
    RETURN_STR(result);
}

// http://www.bo56.com/php7%E6%89%A9%E5%B1%95%E5%BC%80%E5%8F%91%E4%B9%8B%E6%95%B0%E7%BB%84%E5%A4%84%E7%90%86/
PHP_FUNCTION(qys_array_concat)
{
    zval *arr, *prefix, *entry, *prefix_entry, value;
    zend_string *string_key, *result;
    zend_ulong num_key;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &arr, &prefix) == FAILURE) {
        return;
    }

    array_init_size(return_value, zend_hash_num_elements(Z_ARRVAL_P(arr)));

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), num_key, string_key, entry) {
        if (string_key && zend_hash_exists(Z_ARRVAL_P(prefix), string_key)) {
            prefix_entry = zend_hash_find(Z_ARRVAL_P(prefix), string_key);
            if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING) {
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
                ZVAL_STR(&value, result);
                zend_hash_update(Z_ARRVAL_P(return_value), string_key, &value);
            }
        } else if (string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix), num_key)){
            prefix_entry = zend_hash_index_find(Z_ARRVAL_P(prefix), num_key);
            if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING) {
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
                ZVAL_STR(&value, result);
                zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, &value);
            }
        } else if (string_key) {
            zend_hash_update(Z_ARRVAL_P(return_value), string_key, entry);
            zval_add_ref(entry);
        } else  {
            zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, entry);
            zval_add_ref(entry);
        }
    }ZEND_HASH_FOREACH_END();

}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_qys_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_qys_init_globals(zend_qys_globals *qys_globals)
{
	qys_globals->global_value = 0;
	qys_globals->global_string = NULL;
}
*/
//增加两个方法
//释放hash
static void say_hash_destroy(HashTable *ht)
{
    zend_string *key;
    zval *element;
    if (((ht)->u.flags & HASH_FLAG_INITIALIZED)) {
        ZEND_HASH_FOREACH_STR_KEY_VAL(ht, key, element) {
            if (key) {
                free(key);
            }
            switch (Z_TYPE_P(element)) {
                case IS_STRING:
                    free(Z_PTR_P(element));
                    break;
                case IS_ARRAY:
                    say_hash_destroy(Z_ARRVAL_P(element));
                    break;
            }
        } ZEND_HASH_FOREACH_END();
        free(HT_GET_DATA_ADDR(ht));
    }
    free(ht);
}

//释放数组和字符串
static void say_entry_dtor_persistent(zval *zvalue)
{
    if (Z_TYPE_P(zvalue) == IS_ARRAY) {
        say_hash_destroy(Z_ARRVAL_P(zvalue));
    } else if (Z_TYPE_P(zvalue) == IS_STRING) {
        zend_string_release(Z_STR_P(zvalue));
    }
}

/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(qys)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/


 	zend_constant c;
    zend_string *key;
    zval value;

    // php class
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "children", children_methods);
	children_ce = zend_register_internal_class(&ce);
	zend_declare_property_null(children_ce, "memory",       sizeof("memory") - 1, ZEND_ACC_PUBLIC);
	// end class

    ZVAL_NEW_PERSISTENT_ARR(&c.value);
    zend_hash_init(Z_ARRVAL(c.value), 0, NULL,
                        (dtor_func_t)say_entry_dtor_persistent, 1);
    add_index_long(&c.value, 0, 2);
    key = zend_string_init("site", 4, 1);
    ZVAL_STR(&value, zend_string_init("www.bo56.com", 12, 1));
    zend_hash_update(Z_ARRVAL(c.value), key, &value);
    c.flags = CONST_CS|CONST_PERSISTENT;
    c.name = zend_string_init("__ARR__", 7, 1);
    c.module_number = module_number;
    zend_register_constant(&c);

    REGISTER_STRINGL_CONSTANT("__SITE__", "www.bo56.com", 12, CONST_PERSISTENT);
    REGISTER_NS_STRINGL_CONSTANT("say", "__SITE__", "bo56.com", 8, CONST_CS|CONST_PERSISTENT);


	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(qys)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/

	zval *val;
    val = zend_get_constant_str("__ARR__", 7);
    say_hash_destroy(Z_ARRVAL_P(val));
    ZVAL_NULL(val);

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(qys)
{
#if defined(COMPILE_DL_QYS) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(qys)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(qys)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "qys support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ qys_functions[]
 *
 * Every user visible function must have an entry in qys_functions[].
 */
const zend_function_entry qys_functions[] = {
	PHP_FE(confirm_qys_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(qys_helloworld,	NULL)
	PHP_FE(qys_default_value,	NULL)
	PHP_FE(qys_get_size,	NULL)
	PHP_FE(qys_define_var,	NULL)
	PHP_FE(qys_str_concat,  NULL)
	PHP_FE(qys_array_concat,  NULL)
	PHP_FE(qys_call_function,  NULL)
	PHP_FE(qys_args_base,  NULL)
	PHP_FE(qys_zend_parse_para, NULL)
	PHP_FE(qys_zend_parse_array, NULL)
	PHP_FE(qys_zend_parse_object, NULL)
	PHP_FE(qys_zend_args, NULL)
	PHP_FE_END	/* Must be the last line in qys_functions[] */
};
/* }}} */

/* {{{ qys_module_entry
 */
zend_module_entry qys_module_entry = {
	STANDARD_MODULE_HEADER,
	"qys",
	qys_functions,
	PHP_MINIT(qys),
	PHP_MSHUTDOWN(qys),
	PHP_RINIT(qys),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(qys),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(qys),
	PHP_QYS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_QYS
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(qys)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
