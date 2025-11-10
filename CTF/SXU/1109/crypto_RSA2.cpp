// C++版本：使用 Boost.Multiprecision 实现与原 Python 脚本等价的 RSA 解密
// 功能：给定 p,q,e,c，计算 phi=(p-1)*(q-1)，d = e^{-1} mod phi，m = c^d mod n
// 并将 m 解释为大端字节序的原始字节串输出（等价于 Python 的 long_to_bytes）。

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include <string>

using boost::multiprecision::cpp_int;
using namespace std;

// 扩展欧几里得，返回 gcd(a,b)，并通过引用给出 x,y 满足 ax+by=g
cpp_int ext_gcd(const cpp_int &a, const cpp_int &b, cpp_int &x, cpp_int &y){
    if(b == 0){ x = 1; y = 0; return a; }
    cpp_int x1, y1;
    cpp_int g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

cpp_int modinv(const cpp_int &a, const cpp_int &m){
    cpp_int x, y;
    cpp_int g = ext_gcd(a, m, x, y);
    if(g != 1){
        throw runtime_error("modular inverse does not exist");
    }
    x %= m;
    if(x < 0) x += m;
    return x;
}

// 快速幂模：base^exp mod mod
cpp_int mod_pow(cpp_int base, cpp_int exp, const cpp_int &mod){
    cpp_int res = 1;
    base %= mod;
    while(exp > 0){
        if((exp & 1) != 0) res = (res * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return res;
}

// 将大整数 m 转为大端字节串（等价于 Python 的 long_to_bytes）
string cpp_int_to_bytes(cpp_int m){
    if(m == 0) return string(1, '\0');
    vector<unsigned char> bytes;
    while(m > 0){
        unsigned int b = static_cast<unsigned int>( (m & 0xFF).convert_to<unsigned int>() );
        bytes.push_back(static_cast<unsigned char>(b));
        m >>= 8;
    }
    reverse(bytes.begin(), bytes.end());
    return string(bytes.begin(), bytes.end());
}

int main(){
    // 原 Python 脚本中的常量
    cpp_int n = cpp_int("41069065654959614597750207738698085798765257876378561837894254544512565197793");
    cpp_int c = cpp_int("27990707239527629138352696377606718299992092729307910015562504696905353450041");
    cpp_int e = 11;

    cpp_int p = cpp_int("218538667198531171522213512860093810267");
    cpp_int q = cpp_int("187925853952657607512617865502535480179");

    cpp_int phi = (p - 1) * (q - 1);
    cpp_int d;
    try{
        d = modinv(e, phi);
    }catch(const exception &ex){
        cerr << "failed to compute modular inverse: " << ex.what() << '\n';
        return 2;
    }

    cpp_int m = mod_pow(c, d, n);
    string plain = cpp_int_to_bytes(m);

    // 输出原始字节串。如果是可打印 ASCII，会直接显示文本。
    // 注意：如果字节里包含终止符或不可见字节，终端显示可能受影响。
    cout << plain;
    return 0;
}
