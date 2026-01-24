import struct

# 1. 密钥
key = b"CTF_AIBW_Secret_Key_2025"

# 2. 从 IDA 代码中提取的整数 (注意符号)
raw_dwords = [
    197628219,
    261073938,
    2000437082,
    1605517490,
    -789204593,   # 对应 0xD0F50D0F (注意负数处理)
    -1734595264,
    -765251001,
    -1575459453
]
last_byte = -83 # 对应 0xAD

# 3. 将整数转换为字节流 (小端序 <i)
ciphertext = b''.join([struct.pack('<i', x) for x in raw_dwords])
ciphertext += struct.pack('b', last_byte)

print(f"密钥: {key}")
print(f"密文 (Hex): {ciphertext.hex()}")

def rc4_decrypt(data, key):
    # KSA (Key Scheduling Algorithm)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % len(key)]) % 256
        S[i], S[j] = S[j], S[i]

    # PRGA (Pseudo-Random Generation Algorithm)
    i = j = 0
    res = bytearray()
    for byte in data:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        res.append(byte ^ S[(S[i] + S[j]) % 256])
    return res

try:
    flag = rc4_decrypt(ciphertext, key)
    print(f"尝试 RC4 解密结果: {flag.decode('utf-8', errors='ignore')}")
except:
    print("RC4 解密失败或由乱码")