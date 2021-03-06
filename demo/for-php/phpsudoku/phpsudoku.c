/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_phpsudoku.h"

/* If you declare any globals in php_phpsudoku.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(phpsudoku)
*/

/* True global resources - no need for thread safety here */
static int le_phpsudoku;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phpsudoku.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_phpsudoku_globals, phpsudoku_globals)
    STD_PHP_INI_ENTRY("phpsudoku.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_phpsudoku_globals, phpsudoku_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phpsudoku_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_phpsudoku_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "phpsudoku", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_phpsudoku_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_phpsudoku_init_globals(zend_phpsudoku_globals *phpsudoku_globals)
{
	phpsudoku_globals->global_value = 0;
	phpsudoku_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phpsudoku)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phpsudoku)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(phpsudoku)
{
#if defined(COMPILE_DL_PHPSUDOKU) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(phpsudoku)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phpsudoku)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "phpsudoku support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(PHPCreateBoolMatrix);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPCreateBoolMatrix, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPDestroyBoolMatrix);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPDestroyBoolMatrix, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPSetMatrixRowData);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPSetMatrixRowData, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPDancingLinks);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPDancingLinks, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(PHPCreateSudoku);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPCreateSudoku, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPDestroySudoku);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPDestroySudoku, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPVerifySudoku);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPVerifySudoku, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPGetKnownCount);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPGetKnownCount, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPMakeResultString);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPMakeResultString, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPCalculateSudokuAll);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPCalculateSudokuAll, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPVerifySudokuBoard);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPVerifySudokuBoard, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPSolveTypeName);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPSolveTypeName, 0)
ZEND_END_ARG_INFO()
PHP_FUNCTION(PHPImproveTypeName);
ZEND_BEGIN_ARG_INFO(ArgInfoPHPImproveTypeName, 0)
ZEND_END_ARG_INFO()

/* {{{ phpsudoku_functions[]
 *
 * Every user visible function must have an entry in phpsudoku_functions[].
 */
const zend_function_entry phpsudoku_functions[] = {
	PHP_FE(confirm_phpsudoku_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(PHPCreateBoolMatrix, ArgInfoPHPCreateBoolMatrix)
	PHP_FE(PHPDestroyBoolMatrix, ArgInfoPHPDestroyBoolMatrix)
	PHP_FE(PHPSetMatrixRowData, ArgInfoPHPSetMatrixRowData)
	PHP_FE(PHPDancingLinks, ArgInfoPHPDancingLinks)

	PHP_FE(PHPCreateSudoku, ArgInfoPHPCreateSudoku)
	PHP_FE(PHPDestroySudoku, ArgInfoPHPDestroySudoku)
	PHP_FE(PHPVerifySudoku, ArgInfoPHPVerifySudoku)
	PHP_FE(PHPGetKnownCount, ArgInfoPHPGetKnownCount)
	PHP_FE(PHPMakeResultString, ArgInfoPHPMakeResultString)
	PHP_FE(PHPCalculateSudokuAll, ArgInfoPHPCalculateSudokuAll)
	PHP_FE(PHPVerifySudokuBoard, ArgInfoPHPVerifySudokuBoard)
	PHP_FE(PHPSolveTypeName, ArgInfoPHPSolveTypeName)
	PHP_FE(PHPImproveTypeName, ArgInfoPHPImproveTypeName)

	PHP_FE_END	/* Must be the last line in phpsudoku_functions[] */
};
/* }}} */

/* {{{ phpsudoku_module_entry
 */
zend_module_entry phpsudoku_module_entry = {
	STANDARD_MODULE_HEADER,
	"phpsudoku",
	phpsudoku_functions,
	PHP_MINIT(phpsudoku),
	PHP_MSHUTDOWN(phpsudoku),
	PHP_RINIT(phpsudoku),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(phpsudoku),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(phpsudoku),
	PHP_PHPSUDOKU_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPSUDOKU
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(phpsudoku)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
