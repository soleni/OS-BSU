#include "header.h"

bool CALL(char *cmd){
	STARTUPINFO info = {sizeof(info)};
	PROCESS_INFORMATION processInfo;

	if (
		CreateProcess(
			NULL,
			cmd,
			NULL,
			NULL,
			TRUE,
			0,
			NULL,
			NULL,
			&info,
			&processInfo
		)
	)
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	else return false;

	CloseHandle(processInfo.hProcess);

	return true;
}

int main(int argc, char** argv){
	char BinaryFileName[50];
	char FileName[50];
	double payment;
	int LineNumber;

	printf("Enter binary file name: ");
	scanf("%49s", BinaryFileName);
	printf("Enter line number: ");
	scanf("%d", &LineNumber);
	
	char cmd[100];
	sprintf(
		cmd,
		"creator.exe %s %d",
		BinaryFileName,
		LineNumber
	);
	if(!CALL(cmd)) printf("FATAL ERROR!\n");

	printf("Enter report file name: ");
	scanf("%49s", FileName);
	printf("Enter payment value: ");
	scanf("%lf", &payment);

	sprintf(
		cmd,
		"reporter.exe %s %s %lf",
		BinaryFileName,
		FileName,
		payment
	);
	if(!CALL(cmd)) printf("FATAL ERROR!\n");

	printf("Finished!\n");
	return 0;
}
