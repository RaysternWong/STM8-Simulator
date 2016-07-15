#include "unity.h"
#include "ErrorObject.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ThrowError_throw_ERR_NOT_OPERATOR_should_get_an_error_object_containing_them(void){
  ErrorObject* err;
  Try{
    ThrowError(ERR_UNDEFINED_OPERATOR, "This operator is undefined!");
    TEST_FAIL_MESSAGE("Expecting ERR_UNDEFINED_OPERATOR but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL(ERR_UNDEFINED_OPERATOR, err->errorCode);
    TEST_ASSERT_EQUAL_STRING("This operator is undefined!",  err->errorMsg);
    freeError(err);
  }
}
