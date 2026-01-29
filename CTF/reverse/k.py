# 1. 提取密文数据 (来自 byte_14013B000)
# 对应汇编中的: 9Eh, 0E7h, 30h, 5Fh, 0A7h, 1, 0A6h, 53h...
cipher_data = [
    0x9E, 0xE7, 0x30, 0x5F, 0xA7, 0x01, 0xA6, 0x53, 0x59, 0x1B, 0x0A,
    0x20, 0xF1, 0x73, 0xD1, 0x0E, 0xAB, 0x09, 0x84, 0x0E, 0x8D, 0x2B
]

# 2. 定义密钥 (来自 strcpy(Str, ...))
key_str = "12345678abcdefghijklmnopqrspxyz"
key = [ord(c) for c in key_str]

# 3. 逆向第一步：处理最后的 XOR 0x22
# 因为 (RC4_Output ^ 0x22) = Cipher，所以 RC4_Output = Cipher ^ 0x22
rc4_encrypted = [b ^ 0x22 for b in cipher_data]

# 4. RC4 解密算法实现
def rc4_decrypt(data, key):
    # KSA (初始化 S-box)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % len(key)]) % 256
        S[i], S[j] = S[j], S[i]
    
    # PRGA (解密/加密)
    i = 0
    j = 0
    result = []
    for char in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        k = S[(S[i] + S[j]) % 256]
        result.append(char ^ k)
        
    return bytearray(result)

# 5. 执行解密并打印
flag = rc4_decrypt(rc4_encrypted, key)
print("Flag:", flag.decode('utf-8', errors='ignore'))