#include <iostream>
#include <cstdint>
#include <iomanip>
#include <utility> // 用于 std::pair

// 定义 32 位数据块的类型，对应 Python 中的 4 字节数据
using Block = uint32_t;

/**
 * @brief 模拟 DES 的核心 F 函数（轮函数）
 * * 真实 DES 中，这里是：扩展 (E) -> 异或子密钥 (K) -> S 盒 -> P 置换
 * 在此简化示例中，我们仅用一个简单的异或操作来模拟这个混淆过程。
 * * @param right_part 当前右半部分 R_i-1
 * @param sub_key 当前轮次的 48 位子密钥（这里简化为 32 位）
 * @return Block 模拟 F 函数的输出
 */
Block f_function(Block right_part, Block sub_key) {
    // 真实场景中的复杂计算被简化为异或
    return right_part ^ sub_key;
}

/**
 * @brief 模拟 DES 的一轮 Feistel 变换
 * * 核心公式：
 * L_i = R_i-1
 * R_i = L_i-1 XOR F(R_i-1, K_i)
 * * @param L 左半部分
 * @param R 右半部分
 * @param K 子密钥
 * @param round_num 轮次编号
 * @return std::pair<Block, Block> 包含 (New_L, New_R) 的新数据块
 */
std::pair<Block, Block> des_one_round(Block L, Block R, Block K, int round_num) {
    std::cout << "\n--- 第 " << round_num << " 轮开始 ---\n";
    
    // 1. 保存旧的右半部分 R，它将成为下一轮的左半部分 L
    Block old_R = R;

    // 2. 计算 F 函数：F(R, K)
    Block f_result = f_function(R, K);

    // 3. 核心计算：New_R = Old_L XOR F(Old_R, K)
    // 使用 C++ 的位异或操作符 ^
    Block new_R = L ^ f_result;

    // 4. 新的左半部分 L = 旧的右半部分 R
    Block new_L = old_R;

    // 打印十六进制结果
    std::cout << std::hex << std::uppercase << std::setfill('0');

    std::cout << "左半部分 (L) 变化:\n";
    std::cout << "  旧 L: 0x" << std::setw(8) << L << std::endl;
    std::cout << "  新 L: 0x" << std::setw(8) << new_L << std::endl;

    std::cout << "右半部分 (R) 变化:\n";
    std::cout << "  旧 R: 0x" << std::setw(8) << R << std::endl;
    std::cout << "  新 R: 0x" << std::setw(8) << new_R << std::endl;

    return {new_L, new_R};
}

int main() {
    // 模拟数据：使用 uint32_t 类型，直接赋值十六进制常量
    // 对应 Python 中的 bytes.fromhex("11111111")
    Block L = 0x11111111; // 初始左半部分
    Block R = 0x22222222; // 初始右半部分
    Block K = 0x33333333; // 模拟子密钥 K1

    std::cout << "=== DES 单轮 Feistel 变换模拟 (C++) ===" << std::endl;
    
    // 执行一轮加密
    std::pair<Block, Block> result = des_one_round(L, R, K, 1);
    
    // 可以继续使用 result.first 和 result.second 作为下一轮的 L 和 R 输入
    // Block L_next = result.first;
    // Block R_next = result.second;
    
    std::cout << "\n--- 模拟结束 ---" << std::endl;
    
    return 0;
}