/* 
====================================================================
Copyright (c) 2008 Ian Blumel.  All rights reserved.

This software is licensed as described in the file LICENSE, which
you should have received as part of this distribution.  
====================================================================
File: mkbigtest.c

This file will generate a large "unit tests" file which can be used for
load testing.
*/

/* Keep MicroSoft compilers "quiet". */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/* This should define a fairly reasonably large test file. Files with more 
unit tests should probably be fragmented. Right now the slow down is 
basically the time it takes to compile the file. */
#if defined(WIN32) && _MSC_VER >= 1400
#define MESSAGE   ("Visual Studio 2008 is crippled trying to compile >256\n"\
                   "tests. So we are limiting it to %d tests.\n")
#define NUM_TESTS 256
#else
#define MESSAGE   "Building %d tests.\n" 
#define NUM_TESTS 1024 
#endif

#define TEST_STRING \
   "This is a really, really really long string that I thought would"\
   "give some meat to the tests. I could even make this longer by adding"\
   "more jibberish, but that would probablly be really, really silly."\
   "What I should be doing is coming up with a meater test."
#define FILE_NAME "test_big.c"

int 
main(int argc, char *argv[]) {
   int test_i =0;
   FILE *f = fopen(FILE_NAME, "wt");
   
   if ( f == NULL ) {
      fprintf(stderr, "unable to open 'test_big.c'");
      return 1;
   }

   printf(MESSAGE, NUM_TESTS);
   printf("writing '%s'...", FILE_NAME);
   fprintf(f, "/* This file was generated by mkbigtest.c */\n");
   fprintf(f, "#include \"fct.h\"\n\n");

   fprintf(f, "FCT_BGN() {\n");
   
   fprintf(f, "  FCT_SUITE_BGN(big_one) {\n");

   for (test_i =0; test_i != NUM_TESTS; ++test_i ) {
      fprintf(f, "    FCT_TEST_BGN(test_%d) {\n", test_i+1);
      
      /* Want to test something with a wee bit of meat to it. */
      fprintf(
         f, 
         "      fct_chk(strcmp(\"%s_%d_%s\", \"%s_%d_%s\")==0);\n", 
         TEST_STRING,
         test_i, 
         TEST_STRING,
         TEST_STRING,
         test_i,
         TEST_STRING
         );
      
      fprintf(f, "    } FCT_TEST_END();\n");
   }

   fprintf(f, "  } FCT_SUITE_END();\n");
   fprintf(f, "} FCT_END();\n");

   printf("OK.\n");

   fclose(f);
   f =NULL;

   return 0;
}
