#include "common.h"



int main(int argc, char const *argv[]) {

   if (argc !=3 ||strcmp(argv[1],"--help")==0) 
       usageErr("usage: %s from_file to_file\n", argv[0]);
   

   return 0;
}



