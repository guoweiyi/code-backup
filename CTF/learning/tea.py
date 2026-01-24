def tea_decrypt(v0, v1, key):
    """TEA解密函数，还原64位明文（v0, v1）"""
    delta = 0x9e3779b9  # TEA算法固定常量
    sum_ = 0xc6ef3720   # 32轮迭代后的sum初始值（delta * 32）
    k0, k1, k2, k3 = key
    for _ in range(32):  # 32轮解密
        # 逆向计算v1
        v1 = (v1 - (((v0 << 4) + k2) ^ (v0 + sum_) ^ ((v0 >> 5) + k3))) & 0xFFFFFFFF
        # 逆向计算v0
        v0 = (v0 - (((v1 << 4) + k0) ^ (v1 + sum_) ^ ((v1 >> 5) + k1))) & 0xFFFFFFFF
        sum_ = (sum_ - delta) & 0xFFFFFFFF  # 每轮sum递减delta
    return v0, v1

def dword_to_bytes(d):
    """将32位无符号整数转换为4字节（little-endian）"""
    return bytes([
        d & 0xFF,
        (d >> 8) & 0xFF,
        (d >> 16) & 0xFF,
        (d >> 24) & 0xFF
    ])

key = [0x12345678, 0x9ABCDEF0, 0x11223344, 0x55667788]

enc_groups = [
    (0x2FCB8FCE, 0x6F7AC627),
    (0x0F80E3D7, 0x7B4D77F8),
    (0x8FAF751E, 0x51B46D88),
    (0x32B14897, 0xB448E645),
    (0xFBC3CC64, 0xE9BC9C31)
]

plaintext = b""
for v0_enc, v1_enc in enc_groups:
    v0, v1 = tea_decrypt(v0_enc, v1_enc, key)
    plaintext += dword_to_bytes(v0) + dword_to_bytes(v1)

input_flag = plaintext.decode('ascii')
print(input_flag)