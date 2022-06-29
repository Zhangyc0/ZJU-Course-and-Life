字符串的使用

```c++
#include <string>
string str;
string str = "Hello";
string str("ssss");
string str1(str);
string str2(str, 2, 3);	// str[2]开始持续3个字符，2+3溢出了没关系，但是2溢出了会异常


cin >> str;
cout << str
```

string不是原生类型，所以不是关键字



==初始化：`int a[10] = {1};`非零的情况下只有第一个会被赋为1，其他全部为0==



```c++
char 	str1[8] = "abc";
string 	str2 	= "def";
char 	*pc 	= str1;
string 	*ps 	= &str2;
```

