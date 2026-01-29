# PHP Unserialize Tool

```bash

# 扫描文件并生成 POC 脚本 (推荐)
python unser.py scan target.php --poc poc.php
```

## 2. 字符串逃逸计算 (String Escape)

用于计算反序列化字符逃逸（增多或减少）所需的 Payload 结构。

```bash
# 逃逸计算 (例如：字符 'bad' 被替换为 'good')
# --target: 你想要注入的完整序列化字符串片段
# --keyword: 原字符串中的关键字
# --replace: 替换后的字符串

python unser.py escape --target '";s:4:"pass";s:6:"hacked";}' --keyword "bad" --replace "good"
```
