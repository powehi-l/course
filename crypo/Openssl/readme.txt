
(1) lib\libeay32.lib及lib\ssleay32.lib是已经编译好的VC6可用的静态库,
    只要把这两个文件拷到VC6的lib目录中即可。
(2) include\openssl是openssl相关的头文件, 只要把openssl这个文件夹复制到
    VC6的include目录中即可, 注意是把openssl文件夹及里面的文件都复制过去。
(3) VC6写的源程序要调用Openssl库函数时，需要做以下两步:
    ①在main()前面加上以下#include语句
    #include <openssl/xxx.h> /*其中xxx.h是某个算法相关的.h文件，如des.h, md5.h */  
    ②在main()前面加上以下#pragma语句
    #pragma comment(lib, "libeay32.lib")
    #pragma comment(lib, "ssleay32.lib")



