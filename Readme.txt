to run it normally use the following command:

                clang++ -Wall -std=c++11 main.cpp -o test  

to see the template instantiated code by c compiler
https://stackoverflow.com/questions/4448094/can-we-see-the-template-instantiated-code-by-c-compiler

use the command
        
                clang++ -Xclang -ast-print -fsyntax-only main.cpp

AST means a abstract syntax tree

-fsyntax prevents the compiler from generating any object code. 

lets take a look at output of this command


                typedef char16_t char16_t;
                typedef char32_t char32_t;
                namespace std {
                    inline namespace __1 {
                    }
                }
                typedef signed char __int8_t;
                typedef unsigned char __uint8_t;
                typedef short __int16_t;
                typedef unsigned short __uint16_t;
                typedef int __int32_t;
                typedef unsigned int __uint32_t;
                typedef long long __int64_t;
                typedef unsigned long long __uint64_t;
                typedef long __darwin_intptr_t;
                typedef unsigned int __darwin_natural_t;
                typedef int __darwin_ct_rune_t;

                ...
                ... (20000 lines ish)
                ...

                namespace std {
                    inline namespace __1 {
                        extern std::__1::istream cin __attribute__((visibility("default")));
                        extern std::__1::wistream wcin __attribute__((visibility("default")));
                        extern std::__1::ostream cout __attribute__((visibility("default")));
                        extern std::__1::wostream wcout __attribute__((visibility("default")));
                        extern std::__1::ostream cerr __attribute__((visibility("default")));
                        extern std::__1::wostream wcerr __attribute__((visibility("default")));
                        extern std::__1::ostream clog __attribute__((visibility("default")));
                        extern std::__1::wostream wclog __attribute__((visibility("default")));
                    }
                }
                using namespace std;
                template <class T> T add(T a, T b) {
                    return a + b;
                }
                template<> float add<float>(float a, float b) {
                    return a + b;
                }
                template<> int add<int>(int a, int b) {
                    return a + b;
                }
                int main() {
                    float g = add<float>(10, 2);
                    int c = add<int>(10, 2);
                    cout << c << endl;
                    cout << g << endl;
                }

I was initially wondering what is all this code above 

                using namespace std;
                template <class T> T add(T a, T b) {
                    return a + b;
                }

turns out that is exactly what "#include <iostream>" does. Previously I have only read about #include copying and pasting your header code into your file
now I have finally seen it happening.











the clang version im using is 
                

                >> clang --version
                Apple clang version 11.0.0 (clang-1100.0.33.17)
                Target: x86_64-apple-darwin19.2.0
                Thread model: posix
                InstalledDir: /Library/Developer/CommandLineTools/usr/bin

#################################################################################
################################ stdio.h vs iostream ############################
#################################################################################

so another thing is that if you just want printing functionality, you can also use printf(); as oppose to cout 
and stdio.h is massively smaller than iostream


                typedef char16_t char16_t;
                typedef char32_t char32_t;
                namespace std {
                    inline namespace __1 {
                    }
                }
                typedef signed char __int8_t;
                typedef unsigned char __uint8_t;
                typedef short __int16_t;
                typedef unsigned short __uint16_t;
                typedef int __int32_t;
                typedef unsigned int __uint32_t;
                typedef long long __int64_t;
                typedef unsigned long long __uint64_t;
                typedef long __darwin_intptr_t;
                typedef unsigned int __darwin_natural_t;
                typedef int __darwin_ct_rune_t;
                typedef union {
                    char __mbstate8[128];
                    long long _mbstateL;
                } __mbstate_t;

                ...
                ...     (300 lines is)
                ... 

                extern "C" {
                    extern const int sys_nerr;
                    extern const char *const sys_errlist[];
                    int asprintf(char **, const char *, ...) __attribute__((format(printf, 2, 3)));
                    char *ctermid_r(char *);
                    char *fgetln(FILE *, size_t *);
                    const char *fmtcheck(const char *, const char *);
                    int fpurge(FILE *);
                    void setbuffer(FILE *, char *, int);
                    int setlinebuf(FILE *);
                    int vasprintf(char **, const char *, va_list) __attribute__((format(printf, 2, 0)));
                    FILE *zopen(const char *, const char *, int);
                    FILE *funopen(const void *, int (* _Nullable)(void *, char *, int), int (* _Nullable)(void *, const char *, int), fpos_t (* _Nullable)(void *, fpos_t, int), int (* _Nullable)(void *));
                }
                using namespace std;
                template <class T> T add(T a, T b) {
                    return a + b;
                }
                int main() {
                    int c = 10 + 2;
                    float g = 10 + 2;
                    printf("%d", c);
                    printf("%f", g);
                }



I was also wondering what is the difference between the preprocessor output and this command. It seems like they are very similar
using the following command, you can see the preprocessor output 


                clang++ -E main.cpp


see output below:

                typedef signed char __int8_t;



                typedef unsigned char __uint8_t;
                typedef short __int16_t;
                typedef unsigned short __uint16_t;
                typedef int __int32_t;
                typedef unsigned int __uint32_t;
                typedef long long __int64_t;
                typedef unsigned long long __uint64_t;

                typedef long __darwin_intptr_t;
                typedef unsigned int __darwin_natural_t;
                # 70 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386/_types.h" 3 4
                typedef int __darwin_ct_rune_t;





                typedef union {
                 char __mbstate8[128];
                 long long _mbstateL;
                } __mbstate_t;

                typedef __mbstate_t __darwin_mbstate_t;



it seems like the "clang++ -Xclang -ast-print -fsyntax-only main.cpp" command pretty prints it. You can see the preprocessor has a bunch of 
empty spaces and comments in between



#################################################################################
################################ handmade hero ctime ############################
#################################################################################

So speaking of measuring build time, it reminded me of the ctime tool that was mentioned on the handmade hero stream 
https://www.youtube.com/watch?v=LdMHyGxfg6U

so i decided to run ctime on main.cpp as well.

Essentially I wrote a build_windows.bat