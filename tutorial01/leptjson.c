#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */
//assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行。
//检验传入参数的合法性
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;// 指针指向json数据
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') //检查数据格式是否符合 ws value ws 
        p++;         //下一条数据
    c->json = p;    //在json中下一个指针 
}

//
static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

//根据指针指向数据类型返回信息
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;      //
    assert(v != NULL);   //
    c.json = json;       //const char * jason 赋值给json
    v->type = LEPT_NULL; //type设置为LEPT_NULL类型
    lept_parse_whitespace(&c); //调用函数  检查数据是否符合格式
    return lept_parse_value(&c, v);//根据指针指向数据类型返回信息
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
