//C����ִ��shellcode�����ַ���  

#include <windows.h>  
#include <stdio.h>  

//data�οɶ�д  
#pragma comment(linker, "/section:.data,RWE")   


unsigned char shellcode[222] = {
	0x56, 0x57, 0x53, 0x55, 0x31, 0xC9, 0xF7, 0xE1, 0x50, 0x50, 0x50, 0x50, 0x50, 0xEB, 0x4B, 0x5F,
	0xB1, 0x08, 0x50, 0x57, 0xF2, 0xAE, 0xAA, 0x57, 0x66, 0xAF, 0xAA, 0x57, 0x54, 0x57, 0x41, 0xE3,
	0x22, 0x66, 0x8C, 0xE9, 0xE3, 0x36, 0x54, 0x58, 0xC1, 0xE8, 0x18, 0x74, 0x2F, 0xB0, 0x0B, 0x99,
	0x5B, 0x59, 0x52, 0x51, 0x53, 0x54, 0x66, 0x8C, 0xEF, 0x66, 0xC1, 0xEF, 0x08, 0x75, 0x02, 0xCD,
	0x80, 0xCD, 0x91, 0xB0, 0x06, 0x6A, 0xFF, 0x5F, 0x0F, 0x05, 0x3C, 0x05, 0x74, 0x0E, 0x3C, 0x08,
	0x74, 0x0A, 0x6A, 0x3B, 0x58, 0x99, 0x5F, 0x5E, 0x0F, 0x05, 0xEB, 0x75, 0x58, 0x58, 0x58, 0x58,
	0x59, 0x58, 0x40, 0x92, 0x74, 0x16, 0x50, 0x51, 0x64, 0x8B, 0x72, 0x2F, 0x8B, 0x76, 0x0C, 0x8B,
	0x76, 0x0C, 0xAD, 0x8B, 0x30, 0x8B, 0x7E, 0x18, 0xB2, 0x50, 0xEB, 0x17, 0xB2, 0x60, 0x65, 0x48,
	0x8B, 0x32, 0x48, 0x8B, 0x76, 0x18, 0x48, 0x8B, 0x76, 0x10, 0x48, 0xAD, 0x48, 0x8B, 0x30, 0x48,
	0x8B, 0x7E, 0x30, 0x03, 0x57, 0x3C, 0x8B, 0x5C, 0x17, 0x28, 0x8B, 0x74, 0x1F, 0x20, 0x48, 0x01,
	0xFE, 0x8B, 0x54, 0x1F, 0x24, 0x0F, 0xB7, 0x2C, 0x17, 0x48, 0x8D, 0x52, 0x02, 0xAD, 0x81, 0x3C,
	0x07, 0x57, 0x69, 0x6E, 0x45, 0x75, 0xEE, 0x8B, 0x74, 0x1F, 0x1C, 0x48, 0x01, 0xFE, 0x8B, 0x34,
	0xAE, 0x48, 0x01, 0xF7, 0x99, 0xFF, 0xD7, 0x58, 0x58, 0x58, 0x58, 0x58, 0x5D, 0x5B, 0x5F, 0x5E,
	0xC3, 0xE8, 0x39, 0xFF, 0xFF, 0xFF, 0x63, 0x61, 0x6C, 0x63, 0x2E, 0x65, 0x78, 0x65 };

typedef void(__stdcall* CODE) ();


//http://rshell.blog.163.com/blog/static/41619170201110302937361/  

//��һ�ַ���     
void RunShellCode_1()
{

	PVOID p = NULL;
	if ((p = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) == NULL)
		MessageBoxA(NULL, "�����ڴ�ʧ��", "����", MB_OK);
	if (!(memcpy(p, shellcode, sizeof(shellcode))))
		MessageBoxA(NULL, "д�ڴ�ʧ��", "����", MB_OK);

	CODE code = (CODE)p;

	code();

}

//�ڶ��ַ���     
void RunShellCode_2()
{
	((void(*)(void)) & shellcode)();
}

//�����ַ���  
void RunShellCode_3()
{
    __asm
    {
        lea eax, shellcode;
        jmp eax;
    }
}

//�����ַ���     
void RunShellCode_4()
{
    __asm
    {
        mov eax, offset shellcode;
        jmp eax;
    }
}

//�����ַ���     
void RunShellCode_5()
{
    __asm
    {
        mov eax, offset shellcode;
        _emit 0xFF;
        _emit 0xE0;
    }
}

void main()
{
	//RunShellCode_1();  
	//RunShellCode_2();  
	//RunShellCode_3();  
	//RunShellCode_4();  
	RunShellCode_5();
}