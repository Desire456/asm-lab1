#include <iostream>

using namespace std;


//(4*b/c - 1)/(12*c + a - b)

int main()
{
	int a, b, c, res, res_asm, error;
	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;
	cout << "c=";
	cin >> c;
	if (c == 0 || (12 *c + a - b) == 0) {
		cerr << "Do not try to divide by zero\n";
	}
	else {
		res = (4 * b / c - 1) / (12 * c + a - b);
	}
	

	__asm
	{
		mov ecx, c;					ecx = c
		test ecx, ecx;				логическое И, чтобы проставить флаги
		jz ZF_1;					ecx = 0 ?
		imul ecx, 12;				ecx = ecx * 12
		jo OF_1;					проверка переполнения ecx

		mov eax, a;					eax = a
		add eax, ecx;				eax = eax + ecx
		jo OF_1;					проверка переполнения eax

		mov ebx, b;					ebx = b
		sub eax, ebx;				eax = eax - ebx
		jo OF_1;					проверка переполнения eax
		jz ZF_1;					eax = 0 ?
		push eax;					закидываем eax в stack


		imul ebx, 4;				ebx = ebx * 4
		jo OF_1;					проверка переполнения ebx
		mov eax, ebx;				eax = ebx
		mov ecx, c;					ecx = c
		cdq;						подготовка к делению <edx:eax>
		idiv ecx;					eax = eax / ecx
		jo OF_1;					проверка переполения eax
		dec eax;					eax = eax - 1
		jo OF_1;					проверка переполения eax

		pop ebx;					ebx = eax
		cdq;						подготовка к делению <edx:eax>
		idiv ebx;					eax = eax / ebx
		jo OF_1;					проверк переполнения eax


		jmp END;					переходим на метку END

		OF_1:
			mov error, 2;			error = 2
			jmp END;				переходим на метку END
		ZF_1:
			mov error, 1;			error = 1
			jmp END;				переходим на метку END
		END:
			mov res_asm, eax;		res_asm = eax
	}
	if (error == 1) {		
		cerr << "Division by zero\n";
		system("pause");
		return 0;
	}
	if (error == 2) {			
		cerr << "Too big quotient\n";
		system("pause");
		return 0;
	}

	cout << "res c++ : " << res << endl;
	cout << "res asm : " << res_asm << endl;
	system("pause");
	return 0;
}

