# BigNum


BigNum is a library to using bignumbers in c++ with infite digits;
you can use code of BigNum.h and BigNum.c in your project 

There is a sample main for using BigNum which you can use it with `make`






| functionality  |   |  |        |
|------------------|--------------------|------------------|------------------|
| constructors :   | `python BigNum(double n); ` | `BigNum(string n);`|     `BigNum(); `   |
|Adding two bignums|`bn3 = bn1 + bn2;`     |`bn3 += bn2; `       |                  |
|Adding bignum with a real number| `bn3 = bn2 + d;`|` bn3 = d + bn2;`|      |
| Increment |`bn++;` |` ++bn `|         |
| Assignment   | `bn1 = bn2;`  | |      |
| Symmetry |` bn2 = -bn1;`|  |  |
| Bracket|x < 0 , x >= 0| `int n = bn[x];` |     `b[x] = n `  |
| Boolean operators|`bn1 < bn2 `| `bn1 == bn2` |      |
| IO |` cout << bn; ` |``cin >> bn`|  |

